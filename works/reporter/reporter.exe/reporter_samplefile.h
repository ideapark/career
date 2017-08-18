/*
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#ifndef REPORTER_SAMPLEFILE_H
#define REPORTER_SAMPLEFILE_H

#include <inttypes.h>
#include <string>

#define MAX_PATH_LENGTH  256
#define MAX_CALL_DEPTH   5

#define FILE_HEAD_MAGIC    0x12344321
#define MODULE_HEAD_MAGIC  0x8746abcd
#define VMA_HEAD_MAGIC     0xbcdf9283

namespace reporter {

struct timeval {
	uint32_t tv_sec;
	uint32_t tv_usec;
};

struct file_head {
	uint32_t magic;                    /* FILE_HEAD_MAGIC */
	uint32_t index;                    /* sample total count */
	struct timeval begintime;          /* start time: timeval */
	struct timeval endtime;            /* end time: timeval */
	uint64_t stBeginTime;              /* start time: tick */
	uint64_t stEndTime;                /* end time: tick */
	uint64_t reset_value;              /* sample interval */
	uint32_t cputype;                  /* cpu type */
	uint32_t reverved;                 /* reserved */
};

struct record_entry {
	int user;                          /* is user space */
	int pid;
	int tid;
	int time_diff;                     /* sample time interval */
	int pmc_index;                     /* pmc counter */
	int cs_layer;                      /* cs valid levels */
	uint32_t event;                    /* event id */
	uint32_t unitmask;                 /* event mask */
	uint32_t pc;                       /* program counter address */
	uint32_t cs[MAX_CALL_DEPTH];       /* call stack deduced from pc */
};

struct module_head {
	uint32_t magic;                    /* MODULE_HEAD_MAGIC */
	uint32_t num;                      /* module_entry count */
};

struct module_entry {
	uint32_t start;                    /* text section start */
	uint32_t end;                      /* text section end */
	char module_name[MAX_PATH_LENGTH]; /* kernel module file */
};

struct vma_head {
	uint32_t magic;                    /* VMA_HEAD_MAGIC */
	uint32_t num;                      /* vma_text_info count */
};

struct vma_entry {
	int pid;
	int is_sre;                        /* is SRE */
	uint32_t vm_start;                 /* mapped text section vma start */
	uint32_t vm_end;                   /* mapped text section vma start */
	char vm_file[MAX_PATH_LENGTH];     /* process image file or so */
};

class sample_file
{
public:
	sample_file(const std::string &file_path);
	~sample_file();

public:
	void get_file_sample_time(long &start, long &end) {
		start = this->fhead.begintime.tv_sec;
		end = this->fhead.endtime.tv_sec;
	}

	long get_reset_value() {return fhead.reset_value;}

public:
	int record_entry(struct record_entry &record);
	int module_entry(struct module_entry &module);
	int vma_entry(struct vma_entry &vma);

private:
	void extract_head();

	void endian_filehead();
	void endian_modulehead();
	void endian_vmahead();

	void endian_record(struct record_entry &record);
	void endian_module(struct module_entry &module);
	void endian_vma(struct vma_entry &vma);

private:
	struct file_head fhead;
	struct module_head mhead;
	struct vma_head vhead;

private:
	int fd;
	int nr_record;
	int nr_module;
	int nr_vma;
};

} /* namespace reporter */

#endif /* REPORTER_SAMPLEFILE_H */
