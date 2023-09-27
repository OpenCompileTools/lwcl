#include "logger_options.hpp"


#ifndef OCT_LWCL_INITIAL_LOG_LEVEL 
#define OCT_LWCL_INITIAL_LOG_LEVEL static_cast<std::size_t>(3)
#endif

#ifndef OCT_LWCL_INITIAL_DEFAULT_THREAD_NAME
#define OCT_LWCL_INITIAL_DEFAULT_THREAD_NAME "main"
#endif


namespace oct {
namespace lwcl{
	log_level options::program_log_level() {
		return local_pll().load(std::memory_order_relaxed);
	}

	log_level options::program_log_level(log_level new_val) {
		return local_pll().exchange(new_val, std::memory_order_relaxed);
	}


	std::atomic<ll>& options::local_pll() {
		return impl::local<std::atomic<ll>, ll>::get<>(static_cast<ll>(OCT_LWCL_INITIAL_LOG_LEVEL));
	}
}
}


namespace oct {
namespace lwcl{
	bool options::prefix_enabled() {
		return local_prefix().load(std::memory_order_relaxed);
	}

	bool options::prefix_enabled(bool new_val) {
		return local_prefix().exchange(new_val, std::memory_order_relaxed);
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
		std::unique_lock<std::mutex> lk(
			impl::local<std::mutex, impl::default_construct>::get<std::ios_base>()
		);
		std::ios_base::sync_with_stdio(new_val);
		lk.unlock();
		return local_sync().exchange(new_val, std::memory_order_relaxed);
	}


	std::atomic<bool>& options::local_sync() {
		return impl::local<std::atomic<bool>, bool>::get<std::ios_base>(false);
	}
}
}


namespace oct {
namespace lwcl{
	std::string options::default_thread_name() {
		std::unique_lock<std::mutex> lk(dtn_mutex());
		return local_dtn();
	}

	template<typename StringTy>
	std::string options::default_thread_name(StringTy&& new_val) {
		std::unique_lock<std::mutex> lk(dtn_mutex());
		return std::exchange(local_dtn(), std::forward<StringTy>(new_val));
	}


	std::string& options::local_dtn() {
		constexpr static std::size_t init_size = sizeof(OCT_LWCL_INITIAL_DEFAULT_THREAD_NAME) / sizeof(OCT_LWCL_INITIAL_DEFAULT_THREAD_NAME[0]);
		return impl::local<std::string, const char[init_size]>::get<>(OCT_LWCL_INITIAL_DEFAULT_THREAD_NAME);
	}

	std::mutex& options::dtn_mutex() {
		return impl::local<std::mutex, impl::default_construct>::get<std::string>();
	}
}
}



namespace oct {
namespace lwcl{
	std::vector<std::FILE*> options::c_ostreams() {
		std::unique_lock<std::mutex> lk(c_stream_mutex());
		return local_c_streams();
	}

	template<typename... CStreams>
	std::vector<std::FILE*> options::c_ostreams(CStreams*... new_streams) {
		std::vector<std::FILE*> new_val;
		new_val.reserve(sizeof...(CStreams));
		(void)std::initializer_list<int> { ((void)(
			new_val.push_back(new_streams)
		), 0)...};
		std::unique_lock<std::mutex> lk(c_stream_mutex());
		return std::exchange(local_c_streams(), new_val);
	}


	std::vector<std::ostream*> options::cpp_ostreams() {
		std::unique_lock<std::mutex> lk(cpp_stream_mutex());
		return local_cpp_streams();
	}

	template<typename... OStreams>
	std::vector<std::ostream*> options::cpp_ostreams(OStreams&... new_streams){
		std::vector<std::ostream*> new_val;
		new_val.reserve(sizeof...(OStreams));
		(void)std::initializer_list<int> { ((void)(
			new_val.push_back(&new_streams)
		), 0)...};
		std::unique_lock<std::mutex> lk(cpp_stream_mutex());
		return std::exchange(local_cpp_streams(), new_val);
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


		template<typename T, typename InitArrayTy, std::size_t ArraySize>
		template<typename ForTy>
		T& local<T, InitArrayTy[ArraySize]>::get(InitArrayTy (&init_val)[ArraySize]) {
			static T t(init_val);
			return t;
		}
	}
}
}
