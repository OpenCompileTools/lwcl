#pragma once
#include <atomic>
#include <vector>
#include <mutex>
#include <vector>
#include <cstdio>
#include <ostream>

#include "log_level.hpp"


#ifndef OCT_LWCL_PREFIX_FORMAT
#define OCT_LWCL_PREFIX_FORMAT OCT_LWCL_PREFIX_TIMESTAMP OCT_LWCL_PREFIX_THREAD OCT_LWCL_PREFIX_LEVEL
#endif

#ifndef OCT_LWCL_PREFIX_TIMESTAMP_FORMAT
#define OCT_LWCL_PREFIX_TIMESTAMP_FORMAT "[%m/%d/%y|%H:%M:%S]"
#endif


namespace oct {
namespace lwcl{
	//Variables are mutexed (or atomic to resemble a mutex) solely to prevent data races and concurrent access
	//- Since each set/get is only dealing with one variable, the memory order doesn't matter
	//- Even if you use both a set and a get in two threads, the order isnt garaunteed anyway 
	struct options {
		static inline log_level program_log_level();
		static inline log_level program_log_level(log_level new_val);
		
		
		static inline bool prefix_enabled();
		static inline bool prefix_enabled(bool new_val);

		
		static inline bool sync_with_stdio();
		static inline bool sync_with_stdio(bool new_val);


		static inline std::string default_thread_name();
		template<typename StringTy>
		static inline std::string default_thread_name(StringTy&& new_val);


		static inline std::vector<std::FILE*> c_ostreams();
		template<typename... CStreams>
		static inline std::vector<std::FILE*> c_ostreams(CStreams*... new_streams);

		
		static inline std::vector<std::ostream*> cpp_ostreams();
		template<typename... OStreams>
		static inline std::vector<std::ostream*> cpp_ostreams(OStreams&... new_streams);


	private:
		static inline std::atomic<ll>& local_pll();

		static inline std::atomic<bool>& local_prefix();

		static inline std::atomic<bool>& local_sync();

		static inline std::string& local_dtn();
		static inline std::mutex& dtn_mutex();


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


		template<typename T, typename InitArrayTy, std::size_t ArraySize>
		struct local<T, InitArrayTy[ArraySize]> {
			template<typename ForTy = void>
			static T& get(InitArrayTy (&init_val)[ArraySize]);
		};
	}
}
}

#include "../src/logger_options.inl"