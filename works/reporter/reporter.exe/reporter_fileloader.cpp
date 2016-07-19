/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

#include "reporter_bfdsupport.h"
#include "reporter_fileloader.h"

namespace reporter {

file_loader::file_loader(const std::string data_dir,
		const std::string image_dir)
{
	this->load_threads(data_dir + "/pid_info");
	this->load_images(image_dir);
	this->load_samples(data_dir);
}

void file_loader::load_threads(const std::string pid_info)
{
	std::string line;
	std::ifstream infile(pid_info.c_str());

	while (std::getline(infile, line)) {
		int pid, tid;
		std::string tty, time, name;
		std::istringstream iss(line);

		/*
		 * LINE FORMAT:
		 *
		 * pid   tid   tty   time       name
		 * 1     1     ?     00:00:01   linuxrc
		 */
		if ((iss >> pid >> tid >> tty >> time >> name)) {
			this->threads.insert(std::make_pair(tid, name));
		}
	}
}

void file_loader::load_images(const std::string image_dir,
		const std::string unix_dir)
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(image_dir.c_str())) == NULL) {
		std::cerr << image_dir << ": open failed." << std::endl;
		return;
	}

	while ((ent = readdir(dir)) != NULL) {
		std::string fname = ent->d_name;

		if (fname == "." || fname == "..")
			continue;

		std::string win_path = image_dir + "/" + fname;
		std::string unix_path = unix_dir + "/" + fname;

		if (ent->d_type == DT_REG) {
			key_path key_path;
			key_path.bfd_key = generate_key();
			key_path.win_path = win_path;
			this->images.insert(std::make_pair(unix_path, key_path));
		} else if (ent->d_type == DT_DIR) {
			load_images(win_path, unix_path);
		} else {
			std::cerr << win_path << ": not recongized file type." << std::endl;
		}
	}

	closedir(dir);
}

void file_loader::load_samples(const std::string data_dir)
{
	static const std::string filename_prefix = "sample_cpu_";

	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(data_dir.c_str())) == NULL) {
		std::cerr << data_dir << ": open failed." << std::endl;
		return;
	}

	while ((ent = readdir(dir)) != NULL) {
		std::string fname = ent->d_name;

		/*
		 * NAME FORMAT:
		 *
		 * sample_cpu_0_20150716_130220
		 */
		if (ent->d_type == DT_REG && fname.find(filename_prefix) == 0) {
			int vcpu = -1;
			sscanf(fname.c_str(), "sample_cpu_%d_", &vcpu);
			this->samples.insert(std::make_pair(vcpu, data_dir + "/" + fname));
		}
	}

	closedir(dir);
}

} /* namespace reporter */
