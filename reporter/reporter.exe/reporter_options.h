/*
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#ifndef REPORTER_OPTIONS_H
#define REPORTER_OPTIONS_H

namespace reporter {

namespace options {
  extern std::string data_dir;
  extern std::string image_dir;
  extern std::string output_dir;
  extern int cpu_frequency;
}

void get_options(int argc, const char *argv[]);

} /* namespace reporter */

#endif // REPORTER_OPTIONS_H
