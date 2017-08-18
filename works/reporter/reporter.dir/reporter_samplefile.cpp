/*
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <cstdlib>
#include <string>
#include <iostream>

#include "reporter_utility.h"
#include "reporter_samplefile.h"

namespace reporter {

sample_file::sample_file(const std::string &file_path)
{
	if ((fd = open(file_path.c_str(), O_RDONLY, 0644)) < 0) {
		std::cerr << file_path << ": open failed." << std::endl;
		std::exit(-1);
	}

	extract_head();

	nr_record = 0;
	nr_module = 0;
	nr_vma = 0;
}

sample_file::~sample_file()
{
	if (fd >= 0)
		close(fd);
}

int sample_file::record_entry(struct record_entry &record)
{
	ssize_t nread;
	off_t off;

	IF_EQUAL_RETURN_VAL(nr_record, fhead.index, 0);

	off = sizeof(struct file_head) + nr_record * sizeof(struct record_entry);
	lseek(fd, off, SEEK_SET);

	nread = read(fd, &record, sizeof(struct record_entry));
	IF_NOT_EQUAL_RETURN_VAL(nread, sizeof(struct record_entry), 0);

	nr_record++;
	endian_record(record);

	return 1;
}

int sample_file::module_entry(struct module_entry &module)
{
	ssize_t nread;
	off_t off;

	IF_EQUAL_RETURN_VAL(nr_module, mhead.num, 0);

	off = sizeof(struct file_head) + fhead.index * sizeof(struct record_entry)
		+ sizeof(struct module_head) + nr_module * sizeof(struct module_entry);
	lseek(fd, off, SEEK_SET);

	nread = read(fd, &module, sizeof(struct module_entry));
	IF_NOT_EQUAL_RETURN_VAL(nread, sizeof(struct module_entry), 0);

	nr_module++;
	endian_module(module);

	return 1;
}

int sample_file::vma_entry(struct vma_entry &vma)
{
	ssize_t nread;
	off_t off;

	IF_EQUAL_RETURN_VAL(nr_vma, vhead.num, 0);

	off = sizeof(struct file_head) + fhead.index * sizeof(struct record_entry)
		+ sizeof(struct module_head) + mhead.num * sizeof(struct module_entry)
		+ sizeof(struct vma_head) + nr_vma * sizeof(struct vma_entry);
	lseek(fd, off, SEEK_SET);

	nread = read(fd, &vma, sizeof(struct vma_entry));
	IF_NOT_EQUAL_RETURN_VAL(nread, sizeof(struct vma_entry), 0);

	nr_vma++;
	endian_vma(vma);

	return 1;
}

void sample_file::extract_head()
{
	ssize_t nread;
	off_t off;

	nread = read(fd, &fhead, sizeof(struct file_head));
	IF_NOT_EQUAL_RETURN(nread, sizeof(struct file_head));
	endian_filehead();

	off = sizeof(struct file_head) + fhead.index * sizeof(struct record_entry);
	lseek(fd, off, SEEK_SET);

	nread = read(fd, &mhead, sizeof(struct module_head));
	IF_NOT_EQUAL_RETURN(nread, sizeof(struct module_head));
	endian_modulehead();

	off = sizeof(struct file_head) + fhead.index * sizeof(struct record_entry)
		+ sizeof(struct module_head) + mhead.num * sizeof(struct module_entry);
	lseek(fd, off, SEEK_SET);

	nread = read(fd, &vhead, sizeof(struct vma_head));
	IF_NOT_EQUAL_RETURN(nread, sizeof(struct vma_head));
	endian_vmahead();
}

void sample_file::endian_filehead()
{
	int cflag = (fhead.magic != FILE_HEAD_MAGIC);

	fhead.index = op_htonl(fhead.index, cflag);
	fhead.begintime.tv_sec = op_htonl(fhead.begintime.tv_sec, cflag);
	fhead.begintime.tv_usec = op_htonl(fhead.begintime.tv_usec , cflag);
	fhead.endtime.tv_sec = op_htonl(fhead.endtime.tv_sec, cflag);
	fhead.endtime.tv_usec = op_htonl(fhead.endtime.tv_usec, cflag);
	fhead.stBeginTime = op_htonl64(fhead.stBeginTime, cflag);
	fhead.stEndTime = op_htonl64(fhead.stEndTime, cflag);
	fhead.reset_value = op_htonl64(fhead.reset_value, cflag);
	fhead.cputype = op_htonl(fhead.cputype, cflag);
	fhead.reverved = op_htonl(fhead.reverved, cflag);
}

void sample_file::endian_modulehead()
{
	int cflag = (mhead.magic != MODULE_HEAD_MAGIC);

	mhead.num = op_htonl(mhead.num, cflag);
}

void sample_file::endian_vmahead()
{
	int cflag = (vhead.magic != VMA_HEAD_MAGIC);

	vhead.num = op_htonl(vhead.num, cflag);
}

void sample_file::endian_record(struct record_entry &record)
{
	int cflag = (fhead.magic != FILE_HEAD_MAGIC);

	record.user = op_htonl(record.user, cflag);
	record.pid = op_htonl(record.pid, cflag);
	record.tid = op_htonl(record.tid, cflag);
	record.time_diff = op_htonl(record.time_diff, cflag);
	record.pmc_index = op_htonl(record.pmc_index, cflag);
	record.cs_layer = op_htonl(record.cs_layer, cflag);
	record.event = op_htonl(record.event, cflag);
	record.unitmask = op_htonl(record.unitmask, cflag);
	record.pc = op_htonl(record.pc, cflag);
	for (int i = 0; i < MAX_CALL_DEPTH; i++)
		record.cs[i] = op_htonl(record.cs[i], cflag);
}

void sample_file::endian_module(struct module_entry &module)
{
	int cflag = (mhead.magic != MODULE_HEAD_MAGIC);

	module.start = op_htonl(module.start, cflag);
	module.end = op_htonl(module.end, cflag);
}

void sample_file::endian_vma(struct vma_entry &vma)
{
	int cflag = (vhead.magic != VMA_HEAD_MAGIC);

	vma.pid = op_htonl(vma.pid, cflag);
	vma.is_sre = op_htonl(vma.is_sre, cflag);
	vma.vm_start = op_htonl(vma.vm_start, cflag);
	vma.vm_end = op_htonl(vma.vm_end, cflag);
}

} /* namespace reporter */
