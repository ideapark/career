/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef REPORTER_BFDSYMBOL_H
#define REPORTER_BFDSYMBOL_H

#include <inttypes.h>
#include <map>
#include <list>
#include <string>
#include <sstream>

#include "reporter_bfdsupport.h"
#include "reporter_avltree.h"
#include "reporter_samplefile.h"
#include "reporter_fileloader.h"

namespace reporter {

class bfd_symbol
{
public:
	bfd_symbol(reporter::sample_file &sample_file,
		   const std::map<std::string, key_path> &images);
	~bfd_symbol();

public:
	std::string get_execfile(int pid);
	bool get_syminfo(const sym_info &sym_info, std::string &symbname,
			 std::string &filename, unsigned int &linenr);
	bool demangle_symbol(const struct record_entry &record, sym_info &sym_info);

public:
	const std::map<int, avl_tree> &get_pid_tree(){return pid_vmatree;}
	const std::list<module_node *> &get_modules(){return module_lst;}

public:
	void debug_print_vmatree();
	void debug_print_moduleinfo();
	void debug_print_syminfo(const sym_info &sym_info);

private:
	bool demangle_user_symbol(const struct record_entry &record,
				  sym_info &sym_info);

	bool demangle_kernel_symbol(const struct record_entry &record,
				    sym_info &sym_info);

	void add_vma_entry(const struct vma_entry &vma,
			   const std::map<std::string, key_path> &images);

	void add_module_entry(const struct module_entry &module,
			      const std::map<std::string, key_path> &images);

	int get_module_bfd_key(const struct module_entry &module,
			       const std::map<std::string, key_path> &images);

	int get_vma_bfd_key(const struct vma_entry &vma,
			    const std::map<std::string, key_path> &images);

	void put_bfd(const key_path &key_path, bool is_sre);

private:
	std::map<int, avl_tree> pid_vmatree;
	std::list<module_node *> module_lst;
	std::map<int, bfd_node *> bfd_objects;

private:
	struct ModuleNodeBfdKeyFinder {
		ModuleNodeBfdKeyFinder(int bfd_key) : to_find(bfd_key){}
		int to_find;
		bool operator()(const module_node *node) const {
			return (to_find == node->bfd_key);
		}
	};
	struct ModuleNodeVmaFinder {
		ModuleNodeVmaFinder(uint32_t vma) : to_find(vma){}
		uint32_t to_find;
		bool operator()(const module_node *node) const {
			return ((to_find >= node->vma_begin) &&
				(to_find <= node->vma_end));
		}
	};
	static bool VmaBeginEndCmp(const module_node *lhs, const module_node *rhs) {
		return (lhs->vma_end < rhs->vma_begin);
	}
};

} /* namespace reporter */

#endif /* REPORTER_BFDSYMBOL_H */
