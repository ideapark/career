/*
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 */
#ifndef REPORTER_MODELS_H
#define REPORTER_MODELS_H

#include <string>

namespace reporter {

#define SUMMARY_INFO_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS summary_info_table(\n" \
  "    data_dir            TEXT,                 \n" \
  "    image_dir           TEXT,                 \n" \
  "    cpu_frequency       INTEGER,              \n" \
  "    start_time          INTEGER,              \n" \
  "    end_time            INTEGER,              \n" \
  "    task_num            INTEGER,              \n" \
  "    func_num            INTEGER,              \n" \
  "    cpu_peak            REAL,                 \n" \
  "    cpu_avg             REAL                  \n" \
  ");\n"

#define SUMMARY_INFO_INSERT_TABLE_SQL \
  "INSERT INTO summary_info_table(\n" \
  "    data_dir,                  \n" \
  "    image_dir,                 \n" \
  "    cpu_frequency,             \n" \
  "    start_time,                \n" \
  "    end_time,                  \n" \
  "    task_num,                  \n" \
  "    func_num,                  \n" \
  "    cpu_peak,                  \n" \
  "    cpu_avg                    \n" \
  ") VALUES (                     \n" \
  "    '%s',                      \n" \
  "    '%s',                      \n" \
  "    %d,                        \n" \
  "    %ld,                       \n" \
  "    %ld,                       \n" \
  "    %d,                        \n" \
  "    %d,                        \n" \
  "    %f,                        \n" \
  "    %f                         \n" \
  ");\n"

class summary_info {
  public:
    std::string data_dir;
    std::string image_dir;
    int cpu_frequency;
    long start_time;
    long end_time;
    int task_num;
    int func_num;
    float cpu_peak;
    float cpu_avg;

  public:
    summary_info() {
      data_dir      = "";
      image_dir     = "";
      cpu_frequency = -1;
      start_time    = -1;
      end_time      = -1;
      task_num      = 0;
      func_num      = 0;
      cpu_peak      = 0.0;
      cpu_avg       = 0.0;
    }

  public:
    static std::string create_table_sql(){return SUMMARY_INFO_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define IMAGE_INFO_CREATE_TABLE_SQL  \
  "CREATE TABLE IF NOT EXISTS image_info_table(\n" \
  "    image_private_key  INTEGER PRIMARY KEY, \n" \
  "    unix_path          TEXT,                \n" \
  "    win_path           TEXT                 \n" \
  ");\n"

#define IMAGE_INFO_INSERT_TABLE_SQL \
  "INSERT INTO image_info_table(\n" \
  "    image_private_key,       \n" \
  "    unix_path,               \n" \
  "    win_path                 \n" \
  ") VALUES (                   \n" \
  "    %d,                      \n" \
  "    '%s',                    \n" \
  "    '%s'                     \n" \
  ");\n"

class image_info {
  public:
    int image_private_key;
    std::string unix_path;
    std::string win_path;

  public:
    image_info() {
        image_private_key = image_info::genkey();
        unix_path         = "";
        win_path          = "";
    }

  public:
    static int genkey(){static int key = 0; return key++;}
    static std::string create_table_sql(){return IMAGE_INFO_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define EVENT_INFO_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS event_info_table(\n" \
  "    event_private_key  INTEGER PRIMARY KEY, \n" \
  "    event_name         TEXT,                \n" \
  "    sample_count       INTEGER,             \n" \
  "    sample_reset_value INTEGER              \n" \
  ");\n"

#define EVENT_INFO_INSERT_TABLE_SQL \
  "INSERT INTO event_info_table(\n" \
  "    event_private_key,       \n" \
  "    event_name,              \n" \
  "    sample_count,            \n" \
  "    sample_reset_value       \n" \
  ") VALUES (                   \n" \
  "    %d,                      \n" \
  "    '%s',                    \n" \
  "    %d,                      \n" \
  "    %d                       \n" \
  ");\n"

class event_info {
  public:
    int event_private_key;
    std::string event_name;
    int sample_count;
    int sample_reset_value;

  public:
    event_info() {
      event_private_key  = event_info::genkey();
      event_name         = "";
      sample_count       = 0;
      sample_reset_value = 0;
    }

  public:
    static int genkey(){static int key = 0; return key++;}
    static std::string create_table_sql(){return EVENT_INFO_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define PROCESS_INFO_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS process_info_table(\n" \
  "    process_private_key   INTEGER PRIMARY KEY,\n" \
  "    event_private_key     INTEGER,            \n" \
  "    pid                   INTEGER,            \n" \
  "    vcpu                  INTEGER,            \n" \
  "    process_name          TEXT,               \n" \
  "    sample_count          INTEGER,            \n" \
  "    sample_ratio          REAL,               \n" \
  "    peak_ratio            REAL                \n" \
  ");\n"

#define PROCESS_INFO_INSERT_TABLE_SQL \
  "INSERT INTO process_info_table(\n" \
  "    process_private_key,       \n" \
  "    event_private_key,         \n" \
  "    pid,                       \n" \
  "    vcpu,                      \n" \
  "    process_name,              \n" \
  "    sample_count,              \n" \
  "    sample_ratio,              \n" \
  "    peak_ratio                 \n" \
  ") VALUES (                     \n" \
  "    %d,                        \n" \
  "    %d,                        \n" \
  "    %d,                        \n" \
  "    %d,                        \n" \
  "    '%s',                      \n" \
  "    %d,                        \n" \
  "    %f,                        \n" \
  "    %f                         \n" \
  ");\n"

class process_info {
  public:
    int process_private_key;
    int event_private_key;
    int pid;
    int vcpu;
    std::string process_name;
    int sample_count;
    float sample_ratio;
    float peak_ratio;

  public:
    process_info() {
      process_private_key = process_info::genkey();
      event_private_key   = -1;
      pid                 = -1;
      vcpu                = -1;
      process_name        = "";
      sample_count        = 0;
      sample_ratio        = 0.0;
      peak_ratio          = 0.0;
    }

  public:
    static int genkey(){static int key = 0; return key++;}
    static std::string create_table_sql(){return PROCESS_INFO_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define TASK_INFO_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS task_info_table(\n" \
  "    task_private_key      INTEGER,         \n" \
  "    event_private_key     INTEGER,         \n" \
  "    process_private_key   INTEGER,         \n" \
  "    tid                   INTEGER,         \n" \
  "    task_name             TEXT,            \n" \
  "    sample_count          INTEGER,         \n" \
  "    sample_ratio          REAL,            \n" \
  "    peak_ratio            REAL,            \n" \
  "    UNIQUE(                                \n" \
  "        process_private_key,               \n" \
  "        task_private_key                   \n" \
  "    )                                      \n" \
  ");\n"

#define TASK_INFO_INSERT_TABLE_SQL \
  "INSERT INTO task_info_table(\n" \
  "    task_private_key,       \n" \
  "    event_private_key,      \n" \
  "    process_private_key,    \n" \
  "    tid,                    \n" \
  "    task_name,              \n" \
  "    sample_count,           \n" \
  "    sample_ratio,           \n" \
  "    peak_ratio              \n" \
  ") VALUES (                  \n" \
  "    %d,                     \n" \
  "    %d,                     \n" \
  "    %d,                     \n" \
  "    %d,                     \n" \
  "    '%s',                   \n" \
  "    %d,                     \n" \
  "    %f,                     \n" \
  "    %f                      \n" \
  ");\n"

class task_info {
  public:
    int task_private_key;
    int event_private_key;
    int process_private_key;
    int tid;
    std::string task_name;
    int sample_count;
    float sample_ratio;
    float peak_ratio;

  public:
    task_info() {
      task_private_key     = task_info::genkey();
      event_private_key    = -1;
      process_private_key  = -1;
      tid                  = -1;
      task_name            = "";
      sample_count         = 0;
      sample_ratio         = 0.0;
      peak_ratio           = 0.0;
    }

  public:
    static int genkey(){static int key = 0; return key++;}
    static std::string create_table_sql(){return TASK_INFO_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define FUNC_INFO_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS func_info_table(\n" \
  "    func_private_key   INTEGER PRIMARY KEY,\n" \
  "    image_private_key  INTEGER,            \n" \
  "    func_vma           INTEGER,            \n" \
  "    func_name          TEXT,               \n" \
  "    file_path          TEXT,               \n" \
  "    line               INTEGER             \n" \
  ");\n"

#define FUNC_INFO_INSERT_TABLE_SQL \
  "INSERT INTO func_info_table(\n" \
  "    func_private_key,       \n" \
  "    image_private_key,      \n" \
  "    func_vma,               \n" \
  "    func_name,              \n" \
  "    file_path,              \n" \
  "    line                    \n" \
  ") VALUES (                  \n" \
  "    %d,                     \n" \
  "    %d,                     \n" \
  "    %u,                     \n" \
  "    '%s',                   \n" \
  "    '%s',                   \n" \
  "    %u                      \n" \
  ");\n"

class func_info {
  public:
    int func_private_key;
    int image_private_key;
    unsigned long func_vma;
    std::string func_name;
    std::string file_path;
    unsigned int line;

  public:
    func_info() {
      func_private_key   = func_info::genkey();
      image_private_key  = -1;
      func_vma           = -1;
      func_name          = "";
      file_path          = "";
      line               = 0;
    }

  public:
    static int genkey(){static int key = 0; return key++;}
    static std::string create_table_sql(){return FUNC_INFO_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define CALLGRAPH_INFO_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS callgraph_info_table(\n" \
  "    event_private_key         INTEGER,          \n" \
  "    process_private_key       INTEGER,          \n" \
  "    task_private_key          INTEGER,          \n" \
  "    caller_func_private_key   INTEGER,          \n" \
  "    callee_func_private_key   INTEGER,          \n" \
  "    call_count                INTEGER,          \n" \
  "    call_ratio                REAL,             \n" \
  "    UNIQUE(                                     \n" \
  "        process_private_key,                    \n" \
  "        task_private_key,                       \n" \
  "        caller_func_private_key,                \n" \
  "        callee_func_private_key                 \n" \
  "    )                                           \n" \
  ");\n"

#define CALLGRAPH_INFO_INSERT_TABLE_SQL \
  "INSERT INTO callgraph_info_table(\n" \
  "    event_private_key,           \n" \
  "    process_private_key,         \n" \
  "    task_private_key,            \n" \
  "    caller_func_private_key,     \n" \
  "    callee_func_private_key,     \n" \
  "    call_count,                  \n" \
  "    call_ratio                   \n" \
  ") VALUES (                       \n" \
  "    %d,                          \n" \
  "    %d,                          \n" \
  "    %d,                          \n" \
  "    %d,                          \n" \
  "    %d,                          \n" \
  "    %d,                          \n" \
  "    %f                           \n" \
  ");\n"

class callgraph_info {
  public:
    int event_private_key;
    int process_private_key;
    int task_private_key;
    int caller_func_private_key;
    int callee_func_private_key;
    int call_count;
    float call_ratio;

  public:
    callgraph_info() {
      event_private_key       = -1;
      process_private_key     = -1;
      task_private_key        = -1;
      caller_func_private_key = -1;
      callee_func_private_key = -1;
      call_count              = 0;
      call_ratio              = 0.0;
    }

  public:
    static std::string create_table_sql(){return CALLGRAPH_INFO_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define CPU_SLICE_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS cpu_slice_table(\n" \
  "    slice_index        INTEGER PRIMARY KEY,\n" \
  "    event_private_key  INTEGER,            \n" \
  "    sample_count       INTEGER,            \n" \
  "    sample_ratio       REAL                \n" \
  ");\n"

#define CPU_SLICE_INSERT_TABLE_SQL \
  "INSERT INTO cpu_slice_table(\n" \
  "    slice_index,            \n" \
  "    event_private_key,      \n" \
  "    sample_count,           \n" \
  "    sample_ratio            \n" \
  ") VALUES (                  \n" \
  "    %d,                     \n" \
  "    %d,                     \n" \
  "    %d,                     \n" \
  "    %f                      \n" \
  ");\n"

class cpu_slice {
  public:
    int slice_index;
    int event_private_key;
    int sample_count;
    float sample_ratio;

  public:
    cpu_slice() {
      slice_index       = -1;
      event_private_key = -1;
      sample_count      = 0;
      sample_ratio      = 0.0;
    }

  public:
    static std::string create_table_sql(){return CPU_SLICE_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define PROCESS_SLICE_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS process_slice_table(\n" \
  "    slice_index               INTEGER,         \n" \
  "    event_private_key         INTEGER,         \n" \
  "    process_private_key       INTEGER,         \n" \
  "    sample_count              INTEGER,         \n" \
  "    UNIQUE(                                    \n" \
  "        slice_index,                           \n" \
  "        process_private_key                    \n" \
  "    )                                          \n" \
  ");\n"

#define PROCESS_SLICE_INSERT_TABLE_SQL \
  "INSERT INTO process_slice_table(\n" \
  "    slice_index,                \n" \
  "    event_private_key,          \n" \
  "    process_private_key,        \n" \
  "    sample_count                \n" \
  ") VALUES (                      \n" \
  "    %d,                         \n" \
  "    %d,                         \n" \
  "    %d,                         \n" \
  "    %d                          \n" \
  ");\n"

class process_slice {
  public:
    int slice_index;
    int event_private_key;
    int process_private_key;
    int sample_count;

  public:
    process_slice() {
      slice_index         = -1;
      event_private_key   = -1;
      process_private_key = -1;
      sample_count        = 0;
    }

  public:
    static std::string create_table_sql(){return PROCESS_SLICE_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define TASK_SLICE_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS task_slice_table(\n" \
  "    slice_index            INTEGER,         \n" \
  "    event_private_key      INTEGER,         \n" \
  "    process_private_key    INTEGER,         \n" \
  "    task_private_key       INTEGER,         \n" \
  "    sample_count           INTEGER,         \n" \
  "    UNIQUE(                                 \n" \
  "        slice_index,                        \n" \
  "        process_private_key,                \n" \
  "        task_private_key                    \n" \
  "    )                                       \n" \
  ");\n"

#define TASK_SLICE_INSERT_TABLE_SQL \
  "INSERT INTO task_slice_table(\n" \
  "    slice_index,             \n" \
  "    event_private_key,       \n" \
  "    process_private_key,     \n" \
  "    task_private_key,        \n" \
  "    sample_count             \n" \
  ") VALUES (                   \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d                       \n" \
  ");\n"

class task_slice {
  public:
    int slice_index;
    int event_private_key;
    int process_private_key;
    int task_private_key;
    int sample_count;

  public:
    task_slice() {
      slice_index         = -1;
      event_private_key   = -1;
      process_private_key = -1;
      task_private_key    = -1;
      sample_count        = 0;
    }

  public:
    static std::string create_table_sql(){return TASK_SLICE_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define FUNC_SLICE_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS func_slice_table(\n" \
  "    slice_index            INTEGER,         \n" \
  "    event_private_key      INTEGER,         \n" \
  "    process_private_key    INTEGER,         \n" \
  "    task_private_key       INTEGER,         \n" \
  "    func_private_key       INTEGER,         \n" \
  "    sample_count           INTEGER,         \n" \
  "    total_count            INTEGER,         \n" \
  "    UNIQUE(                                 \n" \
  "        slice_index,                        \n" \
  "        process_private_key,                \n" \
  "        task_private_key,                   \n" \
  "        func_private_key                    \n" \
  "    )                                       \n" \
  ");\n"

#define FUNC_SLICE_INSERT_TABLE_SQL \
  "INSERT INTO func_slice_table(\n" \
  "    slice_index,             \n" \
  "    event_private_key,       \n" \
  "    process_private_key,     \n" \
  "    task_private_key,        \n" \
  "    func_private_key,        \n" \
  "    sample_count,            \n" \
  "    total_count              \n" \
  ") VALUES (                   \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d,                      \n" \
  "    %d                       \n" \
  ");\n"

class func_slice {
  public:
    int slice_index;
    int event_private_key;
    int process_private_key;
    int task_private_key;
    int func_private_key;
    int sample_count;
    int total_count;

  public:
    func_slice() {
      slice_index         = -1;
      event_private_key   = -1;
      process_private_key = -1;
      task_private_key    = -1;
      func_private_key    = -1;
      sample_count        = 0;
      total_count         = 0;
    }

  public:
    static std::string create_table_sql(){return FUNC_SLICE_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define CALLGRAPH_SLICE_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS callgraph_slice_table(\n" \
  "    slice_index               INTEGER,           \n" \
  "    event_private_key         INTEGER,           \n" \
  "    process_private_key       INTEGER,           \n" \
  "    task_private_key          INTEGER,           \n" \
  "    caller_func_private_key   INTEGER,           \n" \
  "    callee_func_private_key   INTEGER,           \n" \
  "    call_count                INTEGER,           \n" \
  "    UNIQUE(                                      \n" \
  "        slice_index,                             \n" \
  "        process_private_key,                     \n" \
  "        task_private_key,                        \n" \
  "        caller_func_private_key,                 \n" \
  "        callee_func_private_key                  \n" \
  "    )                                            \n" \
  ");\n"

#define CALLGRAPH_SLICE_INSERT_TABLE_SQL \
  "INSERT INTO callgraph_slice_table(\n" \
  "    slice_index,                  \n" \
  "    event_private_key,            \n" \
  "    process_private_key,          \n" \
  "    task_private_key,             \n" \
  "    caller_func_private_key,      \n" \
  "    callee_func_private_key,      \n" \
  "    call_count                    \n" \
  ") VALUES (                        \n" \
  "    %d,                           \n" \
  "    %d,                           \n" \
  "    %d,                           \n" \
  "    %d,                           \n" \
  "    %d,                           \n" \
  "    %d,                           \n" \
  "    %d                            \n" \
  ");\n"

class callgraph_slice {
  public:
    int slice_index;
    int event_private_key;
    int process_private_key;
    int task_private_key;
    int caller_func_private_key;
    int callee_func_private_key;
    int call_count;

  public:
    callgraph_slice() {
      slice_index             = -1;
      event_private_key       = -1;
      process_private_key     = -1;
      task_private_key        = -1;
      caller_func_private_key = -1;
      callee_func_private_key = -1;
      call_count              = 0;
    }

  public:
    static std::string create_table_sql(){return CALLGRAPH_SLICE_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define FUNC_SAMPLE_CREATE_TABLE_SQL    \
  "CREATE TABLE IF NOT EXISTS func_sample_table(\n" \
  "    func_private_key      INTEGER,           \n" \
  "    event_private_key     INTEGER,           \n" \
  "    process_private_key   INTEGER,           \n" \
  "    task_private_key      INTEGER,           \n" \
  "    sample_count          INTEGER,           \n" \
  "    sample_ratio          REAL,              \n" \
  "    total_count           INTEGER,           \n" \
  "    total_ratio           REAL,              \n" \
  "    UNIQUE(                                  \n" \
  "        process_private_key,                 \n" \
  "        task_private_key,                    \n" \
  "        func_private_key                     \n" \
  "    )                                        \n" \
  ");\n"

#define FUNC_SAMPLE_INSERT_TABLE_SQL \
  "INSERT INTO func_sample_table(\n" \
  "    func_private_key,         \n" \
  "    event_private_key,        \n" \
  "    process_private_key,      \n" \
  "    task_private_key,         \n" \
  "    sample_count,             \n" \
  "    sample_ratio,             \n" \
  "    total_count,              \n" \
  "    total_ratio               \n" \
  ") VALUES (                    \n" \
  "    %d,                       \n" \
  "    %d,                       \n" \
  "    %d,                       \n" \
  "    %d,                       \n" \
  "    %d,                       \n" \
  "    %f,                       \n" \
  "    %d,                       \n" \
  "    %f                        \n" \
  ");\n"

class func_sample {
  public:
    int func_private_key;
    int event_private_key;
    int process_private_key;
    int task_private_key;
    int sample_count;
    float sample_ratio;
    int total_count;
    float total_ratio;

  public:
    func_sample() {
      func_private_key    = -1;
      event_private_key   = -1;
      process_private_key = -1;
      task_private_key    = -1;
      sample_count        = 0;
      sample_ratio        = 0.0;
      total_count         = 0;
      total_ratio         = 0.0;
    }

  public:
    static std::string create_table_sql(){return FUNC_SAMPLE_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

#define CACHEMISS_SAMPLE_CREATE_TABLE_SQL \
  "CREATE TABLE IF NOT EXISTS cachemiss_sample_table(\n" \
  "    event_private_key        INTEGER,             \n" \
  "    process_private_key      INTEGER,             \n" \
  "    task_private_key         INTEGER,             \n" \
  "    image_private_key        INTEGER,             \n" \
  "    offset                   INTEGER,             \n" \
  "    sample_count             INTEGER,             \n" \
  "    UNIQUE(                                       \n" \
  "        event_private_key,                        \n" \
  "        process_private_key,                      \n" \
  "        task_private_key,                         \n" \
  "        image_private_key,                        \n" \
  "        offset                                    \n" \
  "    )                                             \n" \
  ");\n"

#define CACHEMISS_SAMPLE_INSERT_TABLE_SQL \
  "INSERT INTO cachemiss_sample_table(\n" \
  "    event_private_key,             \n" \
  "    process_private_key,           \n" \
  "    task_private_key,              \n" \
  "    image_private_key,             \n" \
  "    offset,                        \n" \
  "    sample_count                   \n" \
  ") VALUES (                         \n" \
  "    %d,                            \n" \
  "    %d,                            \n" \
  "    %d,                            \n" \
  "    %d,                            \n" \
  "    %d,                            \n" \
  "    %d                             \n" \
  ");\n"

class cachemiss_sample {
  public:
    int event_private_key;
    int process_private_key;
    int task_private_key;
    int image_private_key;
    int offset;
    int sample_count;

  public:
    cachemiss_sample() {
      event_private_key   = -1;
      process_private_key = -1;
      task_private_key    = -1;
      image_private_key   = -1;
      offset              = -1;
      sample_count        = 0;
    }

  public:
    static std::string create_table_sql(){return CACHEMISS_SAMPLE_CREATE_TABLE_SQL;}
    std::string insert_entry_sql() const;
};

} /* namespace reporter */

#endif /* REPORTER_MODELS_H */
