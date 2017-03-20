/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#include <inttypes.h>
#include <string>
#include <map>

#include "reporter_consts.h"
#include "reporter_utility.h"

namespace reporter {

typedef std::map<uint32_t, std::string> EventNameMap;

static const EventNameMap::value_type event_names[] = {
	EventNameMap::value_type(3, "L1D_CACHE_REFILL"),
	EventNameMap::value_type(5, "L1D_TLB_REFILL"),
	EventNameMap::value_type(17, "CPU_CYCLES"),
	/* Add event_id : event_name Here */
};

static const EventNameMap APS_EVENT_NAMES(event_names, event_names+ARRAY_LENGTH(event_names));

std::string lookup_event_name(uint32_t event_id)
{
	EventNameMap::const_iterator iter = APS_EVENT_NAMES.find(event_id),
					end = APS_EVENT_NAMES.end();
	if (iter != end)
		return iter->second;
	else
		return "event@" + to_string(event_id);
}

} /* namespace reporter */
