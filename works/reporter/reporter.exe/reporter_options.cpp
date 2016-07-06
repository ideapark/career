/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <unistd.h>
#include <sys/stat.h>

#include <string>
#include <cstdlib>
#include <iostream>

#include "popt_options.h"
#include "reporter_options.h"

namespace reporter {

namespace options {
  std::string data_dir   = ".";
  std::string image_dir  = ".";
  std::string output_dir = ".";
  int cpu_frequency      = -1;
}

namespace {
  popt::option options_array[] = {
    popt::option(options::data_dir, "data_dir", 'd', "aps sample data directory", "path string"),
    popt::option(options::image_dir, "image_dir", 'i', "aps sample elf directory", "path string"),
    popt::option(options::output_dir, "output_dir", 'o', "directory to store result database", "path string"),
    popt::option(options::cpu_frequency, "cpu_frequency", 'f', "sample host cpu frequency", "integer"),
  };
}

static void check_dir(const std::string dir)
{
  struct stat statbuf;

  if (stat(dir.c_str(), &statbuf) != 0 || !S_ISDIR(statbuf.st_mode)) {
    std::cerr << dir << ": does not exists or not a directory" << std::endl;
    std::exit(-1);
  }
}

void get_options(int argc, const char *argv[])
{
  std::vector<std::string> non_options;
  popt::parse_options(argc, argv, non_options);

  check_dir(options::data_dir);
  check_dir(options::image_dir);
  check_dir(options::output_dir);

  if (options::cpu_frequency <= 0) {
    std::cerr << "cpu_frequency should be >= 1" << std::endl;
    std::exit(-1);
  }

  std::cout << "------- reporter.exe -------" << std::endl;
  std::cout << "     data_dir: " << options::data_dir << std::endl;
  std::cout << "    image_dir: " << options::image_dir << std::endl;
  std::cout << "   output_dir: " << options::output_dir << std::endl;
  std::cout << "cpu_frequency: " << options::cpu_frequency << std::endl;
}

} /* namespace reporter */
