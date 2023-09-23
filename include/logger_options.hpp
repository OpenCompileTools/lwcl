#pragma once
#include <atomic>

#include "log_level.hpp"

namespace oct {
namespace lwcl{
	//Variables are mutex'd (or atomic to resemble a mutex) solely to prevent data races
	//- Since each set/get is only dealing with one variable, the memory order doesn't matter
	//- Even if you use both a set and a get in two threads, the order isnt garaunteed anyway 
	struct options {
		static inline log_level program_log_level();
		static inline log_level program_log_level(log_level new_val);
		

		static inline bool log_prefix();
		static inline bool log_prefix(bool new_val);

	private:
		static inline std::atomic<ll>& local_pll();

		static inline std::atomic<bool>& local_prefix();
	};
}
}

#include "../src/logger_options.inl"