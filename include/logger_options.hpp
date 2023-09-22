#pragma once

#include "log_level.hpp"


#ifndef OCT_LWCL_DEFAULT_LOG_LEVEL 
#define OCT_LWCL_DEFAULT_LOG_LEVEL info
#endif

namespace oct {
namespace lwcl{
	//TODO make these local static variables with thread safety
	namespace options {
		log_level program_log_level = ll::OCT_LWCL_DEFAULT_LOG_LEVEL;

		bool log_prefix = true;
	}
}
}