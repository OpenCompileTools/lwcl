#pragma once
#include <atomic>
#include <vector>
#include <mutex>
#include <vector>
#include <cstdio>
#include <ostream>

#include "log_level.hpp"

namespace oct {
namespace lwcl{
	//Variables are mutexed (or atomic to resemble a mutex) solely to prevent data races and concurrent access
	//- Since each set/get is only dealing with one variable, the memory order doesn't matter
	//- Even if you use both a set and a get in two threads, the order isnt garaunteed anyway 
	struct options {
		static inline log_level program_log_level();
		static inline log_level program_log_level(log_level new_val);
		

		static inline bool log_prefix();
		static inline bool log_prefix(bool new_val);

		static inline bool sync_with_stdio();
		static inline bool sync_with_stdio(bool new_val);

	private:
		static inline std::atomic<ll>& local_pll();

		static inline std::atomic<bool>& local_prefix();

		static inline std::atomic<bool>& local_sync();


	public:
		static inline std::vector<std::FILE*> output_c_streams();
		template<typename... CStreams>
		static inline std::vector<std::FILE*> output_c_streams(CStreams*... new_streams);

		static inline std::vector<std::ostream*> output_cpp_streams();
		template<typename... OStreams>
		static inline std::vector<std::ostream*> output_cpp_streams(OStreams&... new_streams);

	private:
		static inline std::vector<std::FILE*>& local_c_streams();
		static inline std::mutex& c_stream_mutex();

		static inline std::vector<std::ostream*>& local_cpp_streams();
		static inline std::mutex& cpp_stream_mutex();
	};
}
}

namespace oct {
namespace lwcl{
	namespace impl{
		using default_construct = void;

		template<typename T, typename InitValTy>
		struct local {
			template<typename ForTy = void>
			static T& get(InitValTy init_val);
		};
		
		template<typename T>
		struct local<T, default_construct> {
			template<typename ForTy = void>
			static T& get();
		};
	}
}
}

#include "../src/logger_options.inl"