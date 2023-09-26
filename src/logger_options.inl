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
		return impl::local<std::atomic<ll>, ll>::get<>(ll::OCT_LWCL_DEFAULT_LOG_LEVEL);
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
		return impl::local<std::atomic<bool>, bool>::get<bool>(true);
	}
}
}


namespace oct {
namespace lwcl{
	bool options::sync_with_stdio() {
		return local_sync().load(std::memory_order_relaxed);
	}

	bool options::sync_with_stdio(bool new_val) {
		local_sync().store(new_val, std::memory_order_relaxed);
		std::unique_lock<std::mutex> lk(
			impl::local<std::mutex, impl::default_construct>::get<std::ios_base>()
		);
		return std::ios_base::sync_with_stdio(new_val);
	}


	std::atomic<bool>& options::local_sync() {
		return impl::local<std::atomic<bool>, bool>::get<std::ios_base>(false);
	}
}
}



namespace oct {
namespace lwcl{
	std::vector<std::FILE*> options::output_c_streams() {
		std::unique_lock<std::mutex> lk(c_stream_mutex());
		return local_c_streams();
	}

	template<typename... CStreams>
	std::vector<std::FILE*> options::output_c_streams(CStreams*... new_streams) {
		std::unique_lock<std::mutex> lk(c_stream_mutex());
		local_c_streams().clear();
		(void)std::initializer_list<int> { ((void)(
			local_c_streams().push_back(new_streams)
		), 0)...};
		return local_c_streams();
	}


	std::vector<std::ostream*> options::output_cpp_streams() {
		std::unique_lock<std::mutex> lk(cpp_stream_mutex());
		return local_cpp_streams();
	}

	template<typename... OStreams>
	std::vector<std::ostream*> options::output_cpp_streams(OStreams&... new_streams){
		std::unique_lock<std::mutex> lk(cpp_stream_mutex());
		local_cpp_streams().clear();
		(void)std::initializer_list<int> { ((void)(
			local_cpp_streams().push_back(&new_streams)
		), 0)...};
		return local_cpp_streams();
	}
	


	std::vector<std::FILE*>& options::local_c_streams() {
		return impl::local<std::vector<std::FILE*>, impl::default_construct>::get<>();
	}

	std::mutex& options::c_stream_mutex() {
		return impl::local<std::mutex, impl::default_construct>::get<std::FILE>();
	}


	std::vector<std::ostream*>& options::local_cpp_streams() {
		return impl::local<std::vector<std::ostream*>, std::initializer_list<std::ostream*>>::get<>({&std::cout});
	}

	std::mutex& options::cpp_stream_mutex() {
		return impl::local<std::mutex, impl::default_construct>::get<std::ostream>();

	}
}
}

namespace oct {
namespace lwcl {
	namespace impl {
		template<typename T, typename InitValTy>
		template<typename ForTy>
		T& local<T, InitValTy>::get(InitValTy init_val) {
			static T t(init_val);
			return t;
		}

		template<typename T>
		template<typename ForTy>
		T& local<T, default_construct>::get() {
			static T t;
			return t;
		}
	}
}
}
