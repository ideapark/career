/*
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <unistd.h>
#include <stdio.h>
#include <functional>

#include "reporter_utility.h"
#include "reporter_options.h"
#include "reporter_bfdsymbol.h"
#include "reporter_transfer.h"
#include "reporter_models.h"
#include "reporter_sqlite.h"
#include "reporter_consts.h"

namespace reporter {

/*
 * SOME USEFUL TEMPLATE METHODS FOR CODE GENERATION, WHICH CAN SAVE
 * PLENTY OF BUSINESS CODE.
 *
 * NOTE:
 *   gcc does *NOT* support tempalte method declaration and definition
 *   are distributed across two different files, so we put them togethor.
 */

template <typename T>
static T *get_or_create(const std::string &key, std::map<std::string, T*> &infos,
                        bool &create)
{
  typename std::map<std::string, T*>::iterator iter = infos.find(key),
                                                end = infos.end();
  if (iter != end) {
    create = false;
    return iter->second;
  } else {
    create = true;
    T *info = new T();
    infos.insert(std::make_pair(key, info));
    return info;
  }
}

template <typename T>
static void exec_sql(sqlite_t *database, T *ptr)
{
  sqlite_exec(database, ptr->insert_entry_sql().c_str());
}

template <typename T>
static void delete_object(T *ptr) {delete ptr;}

template <typename T, typename UnaryPredicate>
static void for_each_map_value(std::map<std::string, T *> infos,
                               UnaryPredicate traverse)
{
  typename std::map<std::string, T *>::iterator iter = infos.begin(),
                                                 end = infos.end();
  while (iter != end) {
    T *info = iter->second;
    traverse(info);
    iter++;
  }
}

transfer::transfer(std::string data_dir, std::string image_dir,
                   std::string output_dir, int cpu_frequency)
  : fileLoader(data_dir, image_dir)
{
  summaryInfo.data_dir = data_dir;
  summaryInfo.image_dir = image_dir;
  summaryInfo.cpu_frequency = cpu_frequency;

  curr_sample_file = 0;
  curr_bfd_symbol = 0;

  /*
   * image_info
   */
  std::map<std::string, key_path>::const_iterator
    iter = fileLoader.get_images().begin(),
     end = fileLoader.get_images().end();

  while(iter != end) {
    bool create;
    const std::string &unix_path = iter->first;

    image_info *image_info = get_or_create(unix_path, image_infos, create);

    if (create) {
      const key_path &key_path = iter->second;
      image_info->image_private_key = key_path.bfd_key;
      image_info->unix_path         = unix_path;
      image_info->win_path          = key_path.win_path;
    }
    iter++;
  }
}

transfer::~transfer()
{
  /*
   * delete all 'new'ed objects
   */
  for_each_map_value(image_infos, delete_object<image_info>);
  for_each_map_value(event_infos, delete_object<event_info>);
  for_each_map_value(process_infos, delete_object<process_info>);
  for_each_map_value(task_infos, delete_object<task_info>);
  for_each_map_value(func_infos, delete_object<func_info>);
  for_each_map_value(callgraph_infos, delete_object<callgraph_info>);
  for_each_map_value(func_samples, delete_object<func_sample>);
  for_each_map_value(cachemiss_samples, delete_object<cachemiss_sample>);

  for_each_map_value(cpu_slices, delete_object<cpu_slice>);
  for_each_map_value(process_slices, delete_object<process_slice>);
  for_each_map_value(task_slices, delete_object<task_slice>);
  for_each_map_value(func_slices, delete_object<func_slice>);
  for_each_map_value(callgraph_slices, delete_object<callgraph_slice>);
}

void transfer::transfer_engine()
{
  std::map<int, std::string>::const_iterator iter = fileLoader.get_samples().begin(),
                                              end = fileLoader.get_samples().end();
  while (iter != end) {
    int vcpu = iter->first;
    std::string file_path = iter->second;

    curr_sample_file = new sample_file(file_path);
    curr_bfd_symbol = new bfd_symbol(*curr_sample_file, fileLoader.get_images());

    curr_sample_file->get_file_sample_time(summaryInfo.start_time,
                                           summaryInfo.end_time);

    struct record_entry record;

    while (curr_sample_file->record_entry(record))
      do_transfer(vcpu, record);

    delete curr_sample_file;
    delete curr_bfd_symbol;

    iter++;
  }

  do_calculate();
  do_output();
}

void transfer::do_transfer(int vcpu, struct record_entry &record)
{
  struct record_entry callee_record = record,
                      caller_record = record;
  sym_info callee_sym_info,
           caller_sym_info;

  if (!curr_bfd_symbol->demangle_symbol(callee_record, callee_sym_info))
    return;

  transfer_record(vcpu, callee_sym_info, callee_record);

  for (int i = 0; i < record.cs_layer; i++) {
    caller_record.pc = record.cs[i];

    if (!curr_bfd_symbol->demangle_symbol(caller_record, caller_sym_info))
      break;

    transfer_record(vcpu, caller_sym_info, caller_record, true);
    transfer_callgraph(vcpu, record, caller_sym_info, callee_sym_info);

    callee_record = caller_record;
    callee_sym_info = caller_sym_info;
  }
}

void transfer::transfer_record(int vcpu, const sym_info &sym_info,
                               const struct record_entry &record,
                               bool deduced /* deduced from call stack? */)
{
  bool create;
  std::string key;

  /*
   * event_info
   */
  key = to_string(record.event);

  event_info *event_info = get_or_create(key, event_infos, create);
  if (create) {
    event_info->event_name = lookup_event_name(record.event);
    event_info->sample_reset_value = curr_sample_file->get_reset_value();
  }

  /*
   * process_info
   */
  key = to_string(vcpu)       + "|" +
        to_string(record.pid) + "|" +
        to_string(event_info->event_private_key);

  process_info *process_info = get_or_create(key, process_infos, create);

  if (create) {
    process_info->event_private_key = event_info->event_private_key;
    process_info->pid               = record.pid;
    process_info->vcpu              = vcpu;
    process_info->process_name = curr_bfd_symbol->get_execfile(record.pid) +
                                 "@" + to_string(record.pid);
  }

  /*
   * task_info
   */
  key = to_string(process_info->process_private_key) + "|" +
        to_string(record.tid)                        + "|" +
        to_string(event_info->event_private_key);

  task_info *task_info = get_or_create(key, task_infos, create);

  if (create) {
    task_info->event_private_key   = event_info->event_private_key;
    task_info->process_private_key = process_info->process_private_key;
    task_info->tid                 = record.tid;
    task_info->task_name           = fileLoader.get_thread_name(record.tid);
    summaryInfo.task_num++;
  }

  /*
   * func_info
   */
  key = to_string(sym_info.bfd_key) + "|" +
        to_string(sym_info.vma_start);

  func_info *func_info = get_or_create(key, func_infos, create);

  if (create) {
    func_info->image_private_key = sym_info.bfd_key;
    func_info->func_vma          = sym_info.vma_start;
    curr_bfd_symbol->get_syminfo(sym_info,
                                 func_info->func_name,
                                 func_info->file_path,
                                 func_info->line);
    summaryInfo.func_num++;
  }

  /*
   * func_sample
   */
  key = to_string(event_info->event_private_key)     + "|" +
        to_string(process_info->process_private_key) + "|" +
        to_string(task_info->task_private_key)       + "|" +
        to_string(func_info->func_private_key);

  func_sample *func_sample = get_or_create(key, func_samples, create);

  if (create) {
    func_sample->event_private_key   = event_info->event_private_key;
    func_sample->process_private_key = process_info->process_private_key;
    func_sample->task_private_key    = task_info->task_private_key;
    func_sample->func_private_key    = func_info->func_private_key;
  }

  func_sample->total_count++;

  if (!deduced) {
    event_info->sample_count++;
    process_info->sample_count++;
    task_info->sample_count++;
    func_sample->sample_count++;
  }

  /*
   * do not count first and last slice, because they
   * may be not complete one sample interval.
   */
  if (record.time_diff == 0 ||
      record.time_diff == (summaryInfo.end_time - summaryInfo.start_time))
    return;

  /*
   * cpu_slice
   */
  key = to_string(record.time_diff) + "|" +
        to_string(event_info->event_private_key);

  cpu_slice *cpu_slice = get_or_create(key, cpu_slices, create);

  if (create) {
    cpu_slice->slice_index       = record.time_diff;
    cpu_slice->event_private_key = event_info->event_private_key;
  }

  /*
   * process_slice
   */
  key = to_string(record.time_diff)              + "|" +
        to_string(event_info->event_private_key) + "|" +
        to_string(process_info->process_private_key);

  process_slice *process_slice = get_or_create(key, process_slices, create);

  if (create) {
    process_slice->slice_index         = record.time_diff;
    process_slice->event_private_key   = event_info->event_private_key;
    process_slice->process_private_key = process_info->process_private_key;
  }

  /*
   * task_slice
   */
  key = to_string(record.time_diff)                  + "|" +
        to_string(event_info->event_private_key)     + "|" +
        to_string(process_info->process_private_key) + "|" +
        to_string(task_info->task_private_key);

  task_slice *task_slice = get_or_create(key, task_slices, create);

  if (create) {
    task_slice->slice_index         = record.time_diff;
    task_slice->event_private_key   = event_info->event_private_key;
    task_slice->process_private_key = process_info->process_private_key;
    task_slice->task_private_key    = task_info->task_private_key;
  }

  /*
   * func_slice
   */
  key = to_string(record.time_diff)                  + "|" +
        to_string(event_info->event_private_key)     + "|" +
        to_string(process_info->process_private_key) + "|" +
        to_string(task_info->task_private_key)       + "|" +
        to_string(func_info->func_private_key);

  func_slice *func_slice = get_or_create(key, func_slices, create);

  if (create) {
    func_slice->slice_index         = record.time_diff;
    func_slice->event_private_key   = event_info->event_private_key;
    func_slice->process_private_key = process_info->process_private_key;
    func_slice->task_private_key    = task_info->task_private_key;
    func_slice->func_private_key    = func_info->func_private_key;
  }

  func_slice->total_count++;

  if (!deduced) {
    /* pid 0 is an idle process, we don't count its cpu cost */
    if (record.pid != 0)
      cpu_slice->sample_count++;

    process_slice->sample_count++;
    task_slice->sample_count++;
    func_slice->sample_count++;
  }
}

void transfer::transfer_callgraph(int vcpu,
                                  const struct record_entry &record,
                                  const sym_info &caller_sym_info,
                                  const sym_info &callee_sym_info)
{
  bool create;
  std::string key;

  key = to_string(record.event);
  event_info *event_info = get_or_create(key, event_infos, create);

  key = to_string(vcpu)       + "|" +
        to_string(record.pid) + "|" +
        to_string(event_info->event_private_key);

  process_info *process_info = get_or_create(key, process_infos, create);

  key = to_string(process_info->process_private_key) + "|" +
        to_string(record.tid)                        + "|" +
        to_string(event_info->event_private_key);

  task_info *task_info = get_or_create(key, task_infos, create);

  key = to_string(caller_sym_info.bfd_key) + "|" +
        to_string(caller_sym_info.vma_start);

  func_info *caller_func_info = get_or_create(key, func_infos, create);

  key = to_string(callee_sym_info.bfd_key) + "|" +
        to_string(callee_sym_info.vma_start);

  func_info *callee_func_info = get_or_create(key, func_infos, create);

  /*
   * callgraph_info
   */
  key = to_string(event_info->event_private_key)      + "|" +
        to_string(process_info->process_private_key)  + "|" +
        to_string(task_info->task_private_key)        + "|" +
        to_string(caller_func_info->func_private_key) + "|" +
        to_string(callee_func_info->func_private_key);

  callgraph_info *callgraph_info = get_or_create(key, callgraph_infos, create);

  if (create) {
    callgraph_info->event_private_key       = event_info->event_private_key;
    callgraph_info->process_private_key     = process_info->process_private_key;
    callgraph_info->task_private_key        = task_info->task_private_key;
    callgraph_info->caller_func_private_key = caller_func_info->func_private_key;
    callgraph_info->callee_func_private_key = callee_func_info->func_private_key;
  }
  callgraph_info->call_count++;

  /*
   * do not count first and last slice, because they
   * may be not complete one sample interval.
   */
  if (record.time_diff == 0 ||
      record.time_diff == (summaryInfo.end_time - summaryInfo.start_time))
    return;

  /*
   * callgraph_slice
   */
  key = to_string(record.time_diff)                   + "|" +
        to_string(event_info->event_private_key)      + "|" +
        to_string(process_info->process_private_key)  + "|" +
        to_string(task_info->task_private_key)        + "|" +
        to_string(caller_func_info->func_private_key) + "|" +
        to_string(callee_func_info->func_private_key);

  callgraph_slice *callgraph_slice = get_or_create(key, callgraph_slices, create);

  if (create) {
    callgraph_slice->slice_index             = record.time_diff;
    callgraph_slice->event_private_key       = event_info->event_private_key;
    callgraph_slice->process_private_key     = process_info->process_private_key;
    callgraph_slice->task_private_key        = task_info->task_private_key;
    callgraph_slice->caller_func_private_key = caller_func_info->func_private_key;
    callgraph_slice->callee_func_private_key = callee_func_info->func_private_key;
  }
  callgraph_slice->call_count++;
}

/*
 * please refer to [Documentation/ratio-calculation-formula.txt]
 * for how calculation happens.
 */
void transfer::do_calculate()
{
  const long long theory_cps = summaryInfo.cpu_frequency * COUNTS_PER_HERTZ;
  const int seconds = summaryInfo.end_time - summaryInfo.start_time;
  const long long theory_c = theory_cps * seconds;

  std::map<std::string, event_info *>::iterator e_iter = event_infos.begin(),
                                                 e_end = event_infos.end();
  while (e_iter != e_end) {
    event_info *event_info = e_iter->second;

    const long long theory_cpse = theory_cps / event_info->sample_reset_value;
    const long long theory_ce = theory_c / event_info->sample_reset_value;

    summaryInfo.cpu_avg = (event_info->sample_count * 100.0) / theory_ce;

    /*
     * cpu_slice
     */
    std::map<std::string, cpu_slice *>::iterator cs_iter = cpu_slices.begin(),
                                                  cs_end = cpu_slices.end();
    while (cs_iter != cs_end) {
      cpu_slice *cpu_slice = cs_iter->second;

      if (cpu_slice->event_private_key == event_info->event_private_key) {
        cpu_slice->sample_ratio =
          (cpu_slice->sample_count * 100.0) / theory_cpse;

        summaryInfo.cpu_peak = std::max(summaryInfo.cpu_peak,
                                        cpu_slice->sample_ratio);
      }
      cs_iter++;
    }

    /*
     * process_info
     */
    std::map<std::string, process_info *>::iterator
      pi_iter = process_infos.begin(),
       pi_end = process_infos.end();

    while (pi_iter != pi_end) {
      process_info *process_info = pi_iter->second;

      if (process_info->event_private_key == event_info->event_private_key) {

        process_info->sample_ratio =
          (process_info->sample_count * 100.0) / theory_ce;

        /*
         * process_slice
         */
        std::map<std::string, process_slice *>::iterator
          ps_iter = process_slices.begin(),
           ps_end = process_slices.end();

        while (ps_iter != ps_end) {
          process_slice *process_slice = ps_iter->second;

          if (process_slice->event_private_key == event_info->event_private_key &&
              process_slice->process_private_key == process_info->process_private_key) {

            process_info->peak_ratio =
              std::max<float>(process_info->peak_ratio,
                              (process_slice->sample_count * 100.0) / theory_cpse);
          }
          ps_iter++;
        }

        /*
         * task_info
         */
        std::map<std::string, task_info *>::iterator
          ti_iter = task_infos.begin(),
           ti_end = task_infos.end();

        while (ti_iter != ti_end) {
          task_info *task_info = ti_iter->second;

          if (task_info->event_private_key == event_info->event_private_key &&
              task_info->process_private_key == process_info->process_private_key) {

            task_info->sample_ratio = (task_info->sample_count * 100.0) / theory_ce;

            /*
             * task_slice
             */
            std::map<std::string, task_slice *>::iterator
              ts_iter = task_slices.begin(),
               ts_end = task_slices.end();

            while (ts_iter != ts_end) {
              task_slice *task_slice = ts_iter->second;

              if (task_slice->event_private_key == event_info->event_private_key &&
                  task_slice->process_private_key == process_info->process_private_key &&
                  task_slice->task_private_key == task_info->task_private_key) {

                task_info->peak_ratio =
                  std::max<float>(task_info->peak_ratio,
                                  (task_slice->sample_count * 100.0) / theory_cpse);
              }
              ts_iter++;
            }
          }
          ti_iter++;
        }
      }
      pi_iter++;
    }

    /*
     * func_sample
     */
    std::map<std::string, func_sample *>::iterator
      fs_iter = func_samples.begin(),
       fs_end = func_samples.end();

    while (fs_iter != fs_end) {
      func_sample *func_sample = fs_iter->second;
      if (func_sample->event_private_key == event_info->event_private_key) {
        func_sample->sample_ratio = func_sample->sample_count * 100.0 / theory_ce;
        func_sample->total_ratio = func_sample->total_count * 100.0 / theory_ce;
      }
      fs_iter++;
    }

    e_iter++;
  }
}

void transfer::do_output()
{
  sqlite_t database;
  std::string temp_database = options::output_dir + "/" + tmpname();
  std::string dest_database = options::output_dir + "/" +
                              to_dbname(summaryInfo.start_time);

  sqlite_open(&database, temp_database.c_str());

  /* create table */
  sqlite_exec(&database, summary_info::create_table_sql().c_str());
  sqlite_exec(&database, image_info::create_table_sql().c_str());
  sqlite_exec(&database, event_info::create_table_sql().c_str());
  sqlite_exec(&database, process_info::create_table_sql().c_str());
  sqlite_exec(&database, task_info::create_table_sql().c_str());
  sqlite_exec(&database, func_info::create_table_sql().c_str());
  sqlite_exec(&database, callgraph_info::create_table_sql().c_str());
  sqlite_exec(&database, func_sample::create_table_sql().c_str());
  sqlite_exec(&database, cachemiss_sample::create_table_sql().c_str());

  sqlite_exec(&database, cpu_slice::create_table_sql().c_str());
  sqlite_exec(&database, process_slice::create_table_sql().c_str());
  sqlite_exec(&database, task_slice::create_table_sql().c_str());
  sqlite_exec(&database, func_slice::create_table_sql().c_str());
  sqlite_exec(&database, callgraph_slice::create_table_sql().c_str());

  /* insert data */
  sqlite_exec(&database, summaryInfo.insert_entry_sql().c_str());

  for_each_map_value(image_infos, std::bind1st(std::ptr_fun(exec_sql<image_info>), &database));
  for_each_map_value(event_infos, std::bind1st(std::ptr_fun(exec_sql<event_info>), &database));
  for_each_map_value(process_infos, std::bind1st(std::ptr_fun(exec_sql<process_info>), &database));
  for_each_map_value(task_infos, std::bind1st(std::ptr_fun(exec_sql<task_info>), &database));
  for_each_map_value(func_infos, std::bind1st(std::ptr_fun(exec_sql<func_info>), &database));
  for_each_map_value(callgraph_infos, std::bind1st(std::ptr_fun(exec_sql<callgraph_info>), &database));
  for_each_map_value(func_samples, std::bind1st(std::ptr_fun(exec_sql<func_sample>), &database));
  for_each_map_value(cachemiss_samples, std::bind1st(std::ptr_fun(exec_sql<cachemiss_sample>), &database));

  for_each_map_value(cpu_slices, std::bind1st(std::ptr_fun(exec_sql<cpu_slice>), &database));
  for_each_map_value(process_slices, std::bind1st(std::ptr_fun(exec_sql<process_slice>), &database));
  for_each_map_value(task_slices, std::bind1st(std::ptr_fun(exec_sql<task_slice>), &database));
  for_each_map_value(func_slices, std::bind1st(std::ptr_fun(exec_sql<func_slice>), &database));
  for_each_map_value(callgraph_slices, std::bind1st(std::ptr_fun(exec_sql<callgraph_slice>), &database));

  sqlite_close(&database);

  unlink(dest_database.c_str());
  rename(temp_database.c_str(), dest_database.c_str());
}

} /* namespace reporter */
