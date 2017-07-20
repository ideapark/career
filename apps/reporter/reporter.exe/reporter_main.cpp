/*
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#include <iostream>
#include <string>
#include <vector>

#include "popt_options.h"
#include "reporter_options.h"
#include "reporter_transfer.h"

int main(int argc, char const * argv[])
{
	reporter::get_options(argc, argv);

	reporter::transfer transfer(reporter::options::data_dir,
				reporter::options::image_dir,
				reporter::options::output_dir,
				reporter::options::cpu_frequency);

	transfer.transfer_engine();

	return 0;
}
