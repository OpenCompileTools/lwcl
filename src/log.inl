#include "log.hpp"

#include <initializer_list>
#include <chrono>
#include <sstream>
#include <mutex>

#include "logger_options.hpp"

namespace oct {
namespace lwcl {
namespace impl {
    template<log_level msg_level, typename... MTys, typename... Args>
    void print(const std::string& thread_name, Args&&... args) {
        if (options::program_log_level() < msg_level) return;


		static std::atomic<bool> sync_val_init(false);
		if (!sync_val_init.exchange(true, std::memory_order_relaxed))
			options::sync_with_stdio(false);


        bool prefix = true;
        (void)std::initializer_list<int> { ((void)(
            impl::set_prefix<MTys>(prefix)
        ), 0)... };
        if (prefix) prefix = options::prefix_enabled();


		std::ostringstream msg;

        (void)std::initializer_list<int> { ((void)(
            msg << MTys{}
        ), 0)... };
		
		if(prefix) {
			#define OCT_LWCL_PREFIX_TIMESTAMP \
            static std::mutex time_mutex;                                                                  \
            std::unique_lock<std::mutex> t_lk(time_mutex);                                                 \
            std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
            std::tm dummy;                                                                                 \
            msg << std::put_time(impl::localtime(&now_time, &dummy), OCT_LWCL_PREFIX_TIMESTAMP_FORMAT);    \
			t_lk.unlock();

			#define OCT_LWCL_PREFIX_THREAD \
			msg << '[' << thread_name << ']';

            #define OCT_LWCL_PREFIX_LEVEL \
			msg << '[' << log_level_names[static_cast<std::size_t>(msg_level)] << ']';

            OCT_LWCL_PREFIX_FORMAT


            (void)std::initializer_list<int> { ((void)(
                print_src_loc(msg, std::forward<Args>(args))
            ), 0)... };
            
            msg << ": ";
		}

		(void)std::initializer_list<int> { ((void)(
			msg << std::forward<Args>(args)
		), 0)... };

		//msg << typename MTy::undo_type{} << typename modifiers<Ms...>::undo_type{};
		
		std::string msg_str(msg.str());
		if(!msg_str.empty()){
			static std::mutex output_mutex;
			std::unique_lock<std::mutex> o_lk(output_mutex);
			for(std::ostream* os : options::cpp_ostreams())
				os->write(msg_str.c_str(), msg_str.size());

			for (std::FILE* f : options::c_ostreams())
				std::fwrite(msg_str.c_str(), sizeof(typename std::ostringstream::char_type), msg_str.size(), f);
		}
    }
}
}
}


namespace oct {
namespace lwcl {
	template<log_level msg_level, typename... MTys, typename... Args>
	void log(Args&&... args) {
		return thread_log<msg_level, MTys...>(options::default_thread_name(), std::forward<Args>(args)...);
	}
}
}


namespace oct {
namespace lwcl {
	template<log_level msg_level, typename... MTys, typename... Args>
	void log_line(Args&&... args) {
		return thread_log_line<msg_level, MTys...>(options::default_thread_name(), std::forward<Args>(args)...);
	}
}
}


namespace oct {
namespace lwcl {
	//All log functions redirect to this one, which calls print
	template<log_level msg_level, typename... MTys, typename... Args>
	void thread_log(const std::string& thread_name, Args&&... args) {
        return impl::print<msg_level, MTys...>(thread_name, std::forward<Args>(args)...);
	}
}
}


namespace oct {
namespace lwcl {
	template<log_level msg_level, typename... MTys, typename... Args>
	void thread_log_line(const std::string& thread_name, Args&&... args) {
		thread_log<msg_level, MTys...>(thread_name, std::forward<Args>(args)..., '\n', reset_modifiers{});
		return;
	}
}
}


namespace oct {
namespace lwcl {
    #define L(name, ...) \
    template<typename... MTys, typename... Args>                                                       \
    void thread_##name(const std::string& thread_name, Args&&... args) {                               \
        impl::log_##name##_modifiers<__VA_ARGS__>();                                                   \
        return thread_log<ll::name, MTys...>(thread_name, std::forward<Args>(args)...);                \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    template<typename... MTys, typename... Args>                                                       \
    void thread_##name##_line(const std::string& thread_name, Args&&... args) {                        \
        impl::log_##name##_modifiers<__VA_ARGS__>();                                                   \
        return thread_log_line<ll::name, MTys...>(thread_name, std::forward<Args>(args)...);           \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
                                                                                                       \
    template<typename... MTys, typename... Args>                                                       \
    void name(Args&&... args) {                                                                        \
        impl::log_##name##_modifiers<__VA_ARGS__>();                                                   \
        return log<ll::name, MTys...>(std::forward<Args>(args)...);                                    \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    template<typename... MTys, typename... Args>                                                       \
    void name##_line(Args&&... args) {                                                                 \
        impl::log_##name##_modifiers<__VA_ARGS__>();                                                   \
        return log_line<ll::name, MTys...>(std::forward<Args>(args)...);                               \
    }                                                                                                  \
                                                                                                       \
                                                                                                       \
    namespace impl {                                                                                   \
        template<typename... MTys>                                                                     \
        void log_##name##_modifiers() {                                                                \
            log<ll::name, ::oct::lwcl::no_prefix, MTys...>();                                          \
            return;                                                                                    \
        }                                                                                              \
    }
    
    OCT_LWCL_LOG_LEVELS
    #undef L
}
}



namespace oct {
namespace lwcl {
    namespace impl {
        template<typename Arg>
        enable_if_src_loc<Arg, true>
        print_src_loc(std::ostringstream& oss, Arg&& arg){
            oss << std::forward<Arg>(arg);
            return;
        }

        
        template<typename Arg>
        enable_if_src_loc<Arg, false>
        print_src_loc(std::ostringstream& oss, Arg&&) {
            return;
        }
    }
}
}


namespace oct {
namespace lwcl {
    namespace impl {
        template<typename MTy>
        void set_prefix(bool& prefix) {
            return;
        }

        template<>
        void set_prefix<oct::lwcl::no_prefix>(bool& prefix) {
            prefix = false;
            return;
        }
    }
}
}


namespace oct {
namespace lwcl {
    #if defined(__unix__) || (defined (__APPLE__) && defined (__MACH__))
    #   include <unistd.h>
    #   ifdef _POSIX_VERSION
    #       define OCT_LWCL_HAS_POSIX
    #   endif
    #endif

    namespace impl {
        std::tm* localtime(std::time_t* time, std::tm* buf) {
            #if defined(_MSC_VER)
            localtime_s(buf, time);
            return buf;
            #elif defined(OCT_LWCL_HAS_POSIX)
            return localtime_r(time, buf);
            #else
            return (buf = std::localtime(time));
            #endif
        }
    }
}
}
