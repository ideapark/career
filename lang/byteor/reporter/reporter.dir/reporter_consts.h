/*
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#ifndef REPORTER_CONSTS_H
#define REPORTER_CONSTS_H

#include <inttypes.h>
#include <string>

#define COUNTS_PER_HERTZ  1000000

namespace reporter {

std::string lookup_event_name(uint32_t event_id);

} /* namespace reporter */

#endif /* REPORTER_CONSTS_H */
