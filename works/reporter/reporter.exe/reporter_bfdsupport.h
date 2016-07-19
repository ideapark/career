/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef REPORTER_BFDSUPPORT_H
#define REPORTER_BFDSUPPORT_H

#include <string>
#include "op_bfd.h"

namespace reporter {

class module_node {
public:
	uint32_t vma_begin;
	uint32_t vma_end;
	int bfd_key;

	std::string unix_path;
};

class vma_node {
public:
	uint32_t vma_begin;
	uint32_t vma_end;
	int bfd_key;

	std::string unix_path;

	vma_node *left;
	vma_node *right;
};

class bfd_node {
public:
	bool is_sre;
	std::string win_path;
	op_bfd *pbfd; /* This member must be `newed`, NOT `malloced` */

public:
	virtual ~bfd_node() {
		if (pbfd != 0) {
			delete pbfd;
			pbfd = 0;
		}
	}
};

class key_path {
public:
	int bfd_key;
	std::string win_path;
};

class sym_info {
public:
	int bfd_key;
	uint32_t sym_index;
	uint32_t vma_start;
	uint32_t objdump_vma;
};

} /* namespace reporter */

#endif /* REPORTER_BFDSUPPORT_H */
