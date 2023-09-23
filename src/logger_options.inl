#include "logger_options.hpp"


#ifndef OCT_LWCL_DEFAULT_LOG_LEVEL 
#define OCT_LWCL_DEFAULT_LOG_LEVEL info
#endif

namespace oct {
namespace lwcl{
	log_level options::program_log_level() {
		return local_pll().load(std::memory_order_relaxed);
	}

	log_level options::program_log_level(log_level new_val) {
		local_pll().store(new_val, std::memory_order_relaxed);
		return new_val;
	}


	std::atomic<ll>& options::local_pll() {
		static std::atomic<ll> pll(ll::OCT_LWCL_DEFAULT_LOG_LEVEL);
		return pll;
	}
}
}


namespace oct {
namespace lwcl{
	bool options::log_prefix() {
		return local_prefix().load(std::memory_order_relaxed);
	}

	bool options::log_prefix(bool new_val) {
		local_prefix().store(new_val, std::memory_order_relaxed);
		return new_val;
	}


	std::atomic<bool>& options::local_prefix() {
		static std::atomic<bool> p(true);
		return p;
	}
}
}


//namespace oct {
//namespace lwcl{
//	
//}
//}
