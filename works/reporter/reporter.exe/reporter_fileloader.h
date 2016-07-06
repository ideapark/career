/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef REPORTER_FILELOADER_H
#define REPORTER_FILELOADER_H

#include <string>
#include <map>

#include "reporter_utility.h"
#include "reporter_bfdsupport.h"

namespace reporter {

class file_loader
{
  public:
    file_loader(const std::string data_dir, const std::string image_dir);

  public:
    std::string get_thread_name(int tid) {
      std::map<int, std::string>::const_iterator iter = threads.find(tid),
                                                  end = threads.end();
      if (iter != end)
        return "#" + iter->second;
      else
        return "#" + to_string(tid);
    }

    const std::map<int, std::string> &get_samples(){return samples;}
    const std::map<std::string, key_path> &get_images(){return images;}

  private:
    std::map<int, std::string> threads;
    std::map<int, std::string> samples;
    std::map<std::string, key_path> images;

  private:
    void load_threads(const std::string pid_info);
    void load_samples(const std::string data_dir);
    void load_images(const std::string image_dir, const std::string unix_dir = "");

  private:
    static int generate_key() {static int key = 0; return key++;}
};

} /* namespace reporter */

#endif /* REPORTER_FILELOADER_H */
