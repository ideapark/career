/*
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "reporter_models.h"

namespace reporter {

/*
 * The file is closed automatically when the program terminates.
 */
static FILE *null_file = fopen("/dev/null", "w");

static std::string vfmt_sql(const char *fmt, ...)
{
	int cnt;
	va_list arg;

	va_start(arg, fmt);
	cnt = vfprintf(null_file, fmt, arg);
	va_end(arg);

	char *buffer = (char *)malloc(cnt + 1);
	buffer[cnt] = '\0';

	va_start(arg, fmt);
	vsnprintf(buffer, cnt, fmt, arg);
	va_end(arg);

	std::string sql = buffer;
	free(buffer);

	return sql;
}

std::string summary_info::insert_entry_sql() const
{
	return vfmt_sql(SUMMARY_INFO_INSERT_TABLE_SQL,
			this->data_dir.c_str(),
			this->image_dir.c_str(),
			this->cpu_frequency,
			this->start_time,
			this->end_time,
			this->task_num,
			this->func_num,
			this->cpu_peak,
			this->cpu_avg);
}

std::string image_info::insert_entry_sql() const
{
	return vfmt_sql(IMAGE_INFO_INSERT_TABLE_SQL,
			this->image_private_key,
			this->unix_path.c_str(),
			this->win_path.c_str());
}

std::string event_info::insert_entry_sql() const
{
	return vfmt_sql(EVENT_INFO_INSERT_TABLE_SQL,
			this->event_private_key,
			this->event_name.c_str(),
			this->event_id,
			this->sample_count,
			this->sample_reset_value);
}

std::string process_info::insert_entry_sql() const
{
	return vfmt_sql(PROCESS_INFO_INSERT_TABLE_SQL,
			this->process_private_key,
			this->event_private_key,
			this->pid,
			this->vcpu,
			this->process_name.c_str(),
			this->sample_count,
			this->sample_ratio,
			this->peak_ratio);
}

std::string task_info::insert_entry_sql() const
{
	return vfmt_sql(TASK_INFO_INSERT_TABLE_SQL,
			this->task_private_key,
			this->event_private_key,
			this->process_private_key,
			this->tid,
			this->task_name.c_str(),
			this->sample_count,
			this->sample_ratio,
			this->peak_ratio);
}

std::string func_info::insert_entry_sql() const
{
	return vfmt_sql(FUNC_INFO_INSERT_TABLE_SQL,
			this->func_private_key,
			this->image_private_key,
			this->func_vma,
			this->func_name.c_str(),
			this->file_path.c_str(),
			this->line);
}

std::string callgraph_info::insert_entry_sql() const
{
	return vfmt_sql(CALLGRAPH_INFO_INSERT_TABLE_SQL,
			this->event_private_key,
			this->process_private_key,
			this->task_private_key,
			this->caller_func_private_key,
			this->callee_func_private_key,
			this->call_count,
			this->call_ratio);
}

std::string cpu_slice::insert_entry_sql() const
{
	return vfmt_sql(CPU_SLICE_INSERT_TABLE_SQL,
			this->slice_index,
			this->event_private_key,
			this->sample_count,
			this->sample_ratio);
}

std::string process_slice::insert_entry_sql() const
{
	return vfmt_sql(PROCESS_SLICE_INSERT_TABLE_SQL,
			this->slice_index,
			this->event_private_key,
			this->process_private_key,
			this->sample_count);
}

std::string task_slice::insert_entry_sql() const
{
	return vfmt_sql(TASK_SLICE_INSERT_TABLE_SQL,
			this->slice_index,
			this->event_private_key,
			this->process_private_key,
			this->task_private_key,
			this->sample_count);
}

std::string func_slice::insert_entry_sql() const
{
	return vfmt_sql(FUNC_SLICE_INSERT_TABLE_SQL,
			this->slice_index,
			this->event_private_key,
			this->process_private_key,
			this->task_private_key,
			this->func_private_key,
			this->sample_count,
			this->total_count);
}

std::string callgraph_slice::insert_entry_sql() const
{
	return vfmt_sql(CALLGRAPH_SLICE_INSERT_TABLE_SQL,
			this->slice_index,
			this->event_private_key,
			this->process_private_key,
			this->task_private_key,
			this->caller_func_private_key,
			this->callee_func_private_key,
			this->call_count);
}

std::string func_sample::insert_entry_sql() const
{
	return vfmt_sql(FUNC_SAMPLE_INSERT_TABLE_SQL,
			this->func_private_key,
			this->event_private_key,
			this->process_private_key,
			this->task_private_key,
			this->sample_count,
			this->sample_ratio,
			this->total_count,
			this->total_ratio);
}

std::string srcline_sample::insert_entry_sql() const
{
	return vfmt_sql(SRCLINE_SAMPLE_INSERT_TABLE_SQL,
			this->event_private_key,
			this->process_private_key,
			this->task_private_key,
			this->image_private_key,
			this->objdump_vma,
			this->sample_count);
}

std::string process_imagefile::insert_entry_sql() const
{
	return vfmt_sql(PROCESS_IMAGEFILE_INSERT_TABLE_SQL,
			this->pid,
			this->image_private_key,
			this->vma_start,
			this->vma_end);
}

} /* namespace reporter */
