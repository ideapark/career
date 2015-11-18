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
