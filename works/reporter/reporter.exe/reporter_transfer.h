/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef REPORTER_TRANSFER_H
#define REPORTER_TRANSFER_H

#include <map>
#include <string>

#include "reporter_bfdsymbol.h"
#include "reporter_fileloader.h"
#include "reporter_samplefile.h"
#include "reporter_models.h"
#include "reporter_sqlite.h"

namespace reporter {

class transfer
{
public:
	transfer(std::string data_dir, std::string image_dir,
		 std::string output_dir, int cpu_frequency);
	~transfer();

public:
	void transfer_engine();

private:
	void do_transfer(int vcpu, struct record_entry &record);

	void transfer_record(int vcpu, const sym_info &sym_info,
			     const struct record_entry &record,
			     bool deduced=false /* deduced from call stack? */);

	void transfer_callgraph(int vcpu,
				const struct record_entry &record,
				const sym_info &caller_sym_info,
				const sym_info &callee_sym_info);

	void do_calculate();
	void do_output();

private:
	file_loader fileLoader;
	sample_file *curr_sample_file;
	bfd_symbol *curr_bfd_symbol;

private:
	summary_info summaryInfo;

	std::map<std::string, image_info *> image_infos;
	std::map<std::string, event_info *> event_infos;
	std::map<std::string, process_info *> process_infos;
	std::map<std::string, task_info *> task_infos;
	std::map<std::string, func_info *> func_infos;
	std::map<std::string, callgraph_info *> callgraph_infos;
	std::map<std::string, func_sample *> func_samples;
	std::map<std::string, srcline_sample *> srcline_samples;

	std::map<std::string, cpu_slice *> cpu_slices;
	std::map<std::string, process_slice *> process_slices;
	std::map<std::string, task_slice *> task_slices;
	std::map<std::string, func_slice *> func_slices;
	std::map<std::string, callgraph_slice *> callgraph_slices;
	std::map<std::string, process_imagefile *> process_imagefiles;
};

} /* namespace reporter */

#endif /* REPORTER_TRANSFER_H */
