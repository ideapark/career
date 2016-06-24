/*
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 */
#include <iostream>
#include <algorithm>

#include "op_bfd.h"
#include "locate_images.h"
#include "string_filter.h"

#include "reporter_utility.h"
#include "reporter_samplefile.h"
#include "reporter_bfdsymbol.h"
#include "reporter_bfdsupport.h"

namespace reporter {

bfd_symbol::bfd_symbol(reporter::sample_file &sample_file,
                       const std::map<std::string, key_path> &images)
{
  struct module_entry module;
  struct vma_entry vma;

  while (sample_file.module_entry(module))
    this->add_module_entry(module, images);

  while (sample_file.vma_entry(vma))
    this->add_vma_entry(vma, images);
}

bfd_symbol::~bfd_symbol()
{
#if DEBUG
  debug_print_vmatree();
  debug_print_moduleinfo();
#endif

  std::list<module_node *>::iterator m_iter = module_lst.begin(),
                                      m_end = module_lst.end();
  while (m_iter != m_end) {
    delete (*m_iter);
    m_iter++;
  }
  module_lst.clear();

  std::map<int, avl_tree>::iterator t_iter = pid_vmatree.begin(),
                                     t_end = pid_vmatree.end();
  while (t_iter != t_end) {
    avl_tree &tree = t_iter->second;
    vma_node *temp;

    while ((temp = tree.rmnode(tree.root_node)))
      delete temp;

    t_iter++;
  }
  pid_vmatree.clear();

  std::map<int, bfd_node *>::iterator b_iter = bfd_objects.begin(),
                                       b_end = bfd_objects.end();
  while (b_iter != b_end) {
    delete b_iter->second;
    b_iter++;
  }
  bfd_objects.clear();
}

void bfd_symbol::add_vma_entry(const vma_entry &vma,
                               const std::map<std::string, key_path> &images)
{
  reporter::vma_node *node = new reporter::vma_node();

  node->vma_begin = vma.vm_start;
  node->vma_end   = vma.vm_end;
  node->unix_path = vma.vm_file;
  node->left      = 0;
  node->right     = 0;
  node->bfd_key   = get_vma_bfd_key(vma, images);

  std::map<int, avl_tree>::iterator iter = pid_vmatree.find(vma.pid),
                                     end = pid_vmatree.end();
  if (iter != end) {
    avl_tree &tree = iter->second;
    tree.insert(tree.root_node, node);
  } else {
    avl_tree tree;
    tree.insert(tree.root_node, node);
    pid_vmatree.insert(std::make_pair<int, avl_tree>(vma.pid, tree));
  }
}

void bfd_symbol::add_module_entry(const module_entry &module,
                                  const std::map<std::string, key_path> &images)
{
  reporter::module_node *node = new reporter::module_node();

  node->vma_begin = module.start;
  node->vma_end   = module.end;
  node->unix_path = module.module_name;
  node->bfd_key   = get_module_bfd_key(module, images);

  /*
   * Some module have more than one module_entry (like 'vmlinux'),
   * we only keep the biggest one
   */
  std::list<module_node *>::iterator iter = std::find_if(module_lst.begin(),
                                                         module_lst.end(),
                                                         ModuleNodeBfdKeyFinder(node->bfd_key));
  if (iter != module_lst.end()) { /* update */
    (*iter)->vma_begin = std::min((*iter)->vma_begin, node->vma_begin);
    (*iter)->vma_end = std::max((*iter)->vma_end, node->vma_end);
    delete node;
  } else { /* insert new node */
    module_lst.insert(module_lst.end(), node);
  }

  /* Sort nodes by vma_begin/vma_end */
  module_lst.sort(VmaBeginEndCmp);
}

int bfd_symbol::get_module_bfd_key(const module_entry &module,
                                   const std::map<std::string, key_path> &images)
{
  const std::string vmlinux = "vmlinux"; /* has no suffix .ko */

  std::string name = std::string(module.module_name);
  std::string ko_name = (name != vmlinux)
                      ? (name + ".ko") /* append suffix .ko */
                      : vmlinux;

  std::map<std::string, key_path>::const_iterator iter = images.begin(),
                                                   end = images.end();
  while (iter != end) {
    std::string unix_path = iter->first;

    if (unix_path.rfind(ko_name) != std::string::npos) {
      const key_path &key_path = iter->second;
      put_bfd(key_path, false);
      return key_path.bfd_key;
    }

    iter++;
  }
  return -1;
}

int bfd_symbol::get_vma_bfd_key(const vma_entry &vma,
                                const std::map<std::string, key_path> &images)
{
  std::string elf_path = vma.vm_file;

  /*
   * WARNING: Linux path char ':' will be replaced by '_' on windows.
   */
  for (unsigned int i = 0; i < elf_path.size(); i++)
    if (elf_path[i] == ':')
      elf_path[i] = '_';

  std::map<std::string, key_path>::const_iterator iter = images.find(elf_path),
                                                   end = images.end();
  if (iter != end) {
    const key_path &key_path = iter->second;
    put_bfd(key_path, vma.is_sre);
    return key_path.bfd_key;
  }
  return -1;
}

void bfd_symbol::put_bfd(const key_path &key_path, bool is_sre)
{
  std::map<int, bfd_node *>::iterator bfd_iter = bfd_objects.find(key_path.bfd_key),
                                       bfd_end = bfd_objects.end();
  if (bfd_iter == bfd_end) {
    reporter::bfd_node *bfd_node = new reporter::bfd_node();
    bfd_node->pbfd = 0;
    bfd_node->is_sre = is_sre;
    bfd_node->win_path = key_path.win_path;
    bfd_objects.insert(std::make_pair(key_path.bfd_key, bfd_node));
  }
}

/*
 * This method is based on the fact below:
 *    On linux system, our main exec('/path/to/exectuable/file') always
 *    has the lowest virtual memory address mapping.
 */
std::string bfd_symbol::get_execfile(int pid)
{
  std::map<int, avl_tree>::iterator iter = pid_vmatree.find(pid),
                                     end = pid_vmatree.end();
  if (iter != end) {
    avl_tree &tree = iter->second;
    vma_node *vma_node = tree.leftmost(tree.root_node);
    if (vma_node != 0)
      return vma_node->unix_path;
  }
  return ""; /* find failed */
}

bool bfd_symbol::get_syminfo(const sym_info &sym_info, std::string &symbname,
                             std::string &filename, unsigned int &linenr)
{
  std::map<int, bfd_node *>::iterator iter = bfd_objects.find(sym_info.bfd_key),
                                       end = bfd_objects.end();
  if (iter == end)
    return false;

  bfd_node *bfd_node = iter->second;
  bfd_node->pbfd->get_linenr(sym_info.sym_index, sym_info.vma_start,
                             filename, linenr);
  symbname = bfd_node->pbfd->get_symname(sym_info.sym_index);
  return true;
}

bool bfd_symbol::demangle_symbol(const struct record_entry &record,
                                 sym_info &sym_info)
{
  if (record.user)
    return demangle_user_symbol(record, sym_info);
  else
    return demangle_kernel_symbol(record, sym_info);
}

bool bfd_symbol::demangle_user_symbol(const struct record_entry &record,
                                      sym_info &sym_info)
{
  const std::map<int, avl_tree>::iterator tree_iter = pid_vmatree.find(record.pid),
                                           tree_end = pid_vmatree.end();
  if (tree_iter == tree_end)
    return false; /* process vma tree not found */

  avl_tree &tree = tree_iter->second;
  vma_node *vma_node = tree.find(tree.root_node, record.pc);

  if (vma_node == 0)
    return false; /* vma tree has no such vma node */

  std::map<int, bfd_node *>::iterator bfd_iter = bfd_objects.find(vma_node->bfd_key),
                                       bfd_end = bfd_objects.end();
  if (bfd_iter == bfd_end)
    return false; /* no such bfd node */

  bfd_node *bfd_node = bfd_iter->second;

  if (bfd_node->pbfd == 0)
    bfd_node->pbfd = new op_bfd(bfd_node->win_path, bfd_node->is_sre);

  unsigned long long file_offset = record.pc - vma_node->vma_begin + 1;

  uint32_t sym_index = bfd_node->pbfd->get_symindex(file_offset);
  uint32_t vma_start = bfd_node->pbfd->start_vma(sym_index);
  uint32_t objdump_vma = bfd_node->pbfd->objdump_vma(file_offset);

  if (sym_index == APS_INVALID_SYMBOL_INDEX || vma_start == APS_INVALID_VMA)
    return false;

  sym_info.bfd_key = vma_node->bfd_key;
  sym_info.sym_index = sym_index;
  sym_info.vma_start = vma_start;
  sym_info.objdump_vma = objdump_vma;

  return true;
}

bool bfd_symbol::demangle_kernel_symbol(const struct record_entry &record,
                                        sym_info &sym_info)
{
  const std::string vmlinux = "vmlinux";

  std::list<module_node *>::iterator iter = std::find_if(module_lst.begin(),
                                                         module_lst.end(),
                                                         ModuleNodeVmaFinder(record.pc));
  if (iter == module_lst.end())
    return false;

  module_node *module_node = *iter;

  std::map<int, bfd_node *>::iterator bfd_iter = bfd_objects.find(module_node->bfd_key),
                                       bfd_end = bfd_objects.end();
  if (bfd_iter == bfd_end)
    return false; /* no such bfd node */

  bfd_node *bfd_node = bfd_iter->second;

  if (bfd_node->pbfd == 0)
    bfd_node->pbfd = new op_bfd(bfd_node->win_path, false);

  unsigned long long file_offset = (module_node->unix_path.rfind(vmlinux) != std::string::npos)
                                 ? record.pc
                                 : (record.pc - module_node->vma_begin + 1);

  uint32_t sym_index = bfd_node->pbfd->get_symindex(file_offset);
  uint32_t vma_start = bfd_node->pbfd->start_vma(sym_index);
  uint32_t objdump_vma = (module_node->unix_path.rfind(vmlinux) != std::string::npos)
                       ? file_offset
                       : bfd_node->pbfd->objdump_vma(file_offset);

  if (sym_index == APS_INVALID_SYMBOL_INDEX || vma_start == APS_INVALID_VMA)
    return false;

  sym_info.bfd_key = module_node->bfd_key;
  sym_info.sym_index = sym_index;
  sym_info.vma_start = vma_start;
  sym_info.objdump_vma = objdump_vma;

  return true;
}

void bfd_symbol::debug_print_vmatree()
{
  std::cout << "------- reporter.exe -------" << std::endl;
  std::cout << "---------- out/so address mapping ----------" << std::endl;
  std::map<int, avl_tree>::iterator iter = pid_vmatree.begin(),
                                     end = pid_vmatree.end();
  while (iter != end) {
    int pid = iter->first;
    const avl_tree &tree = iter->second;

    std::cout << "pid: " << pid << std::endl;
    tree.debug_print(tree.root_node);

    iter++;
  }
}

void bfd_symbol::debug_print_moduleinfo()
{
  std::cout << "------- reporter.exe -------" << std::endl;
  std::cout << "---------- module address mapping ----------" << std::endl;
  std::list<module_node *>::iterator iter = module_lst.begin(),
                                      end = module_lst.end();
  while (iter != end) {
    std::cout << "[" << (*iter)->vma_begin << ", "
              << (*iter)->vma_end << "] -> "
              << (*iter)->unix_path << " (" << (*iter)->bfd_key << ")" << std::endl;
    iter++;
  }
}

void bfd_symbol::debug_print_syminfo(const sym_info &sym_info)
{
  std::map<int, bfd_node *>::iterator iter = bfd_objects.find(sym_info.bfd_key),
                                       end = bfd_objects.end();
  if (iter !=  end) {
    const bfd_node *bfd_node = iter->second;
    std::cout << bfd_node->pbfd->get_symname(sym_info.sym_index)
              << std::endl;
  } else {
    std::cout << "symbol info invalid." << std::endl;
  }
}

} /* namespace reporter */
