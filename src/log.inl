#include "log.hpp"

#include <initializer_list>
#include <chrono>
#include <ctime>
#include <sstream>
#include <mutex>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "logger_options.hpp"

namespace oct {
namespace lwcl {
	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void log(Args&&... args) {
		if (options::program_log_level() < msg_level) return;

		std::ostringstream msg;

		msg << MTy{} << modifiers<Ms...>{};
		
		if(!std::is_same<MTy, no_prefix>::value && options::log_prefix()){
			#ifndef OCT_LWCL_NO_TIMESTAMP
			static std::mutex time_mutex;
			std::unique_lock<std::mutex> t_lk(time_mutex);
			std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			msg << std::put_time(std::localtime(&now_time), "[%m/%d/%y|%H:%M:%S]");
			t_lk.unlock();
			#endif


			msg << '[' << log_level_names[static_cast<std::size_t>(msg_level)] << "]: ";
		}

		(void)std::initializer_list<int> { ((void)(
			msg << std::forward<Args>(args)
		), 0)... };

		//msg << typename MTy::undo_type{} << typename modifiers<Ms...>::undo_type{};
		
		std::string msg_str(msg.str());
		if(!msg_str.empty()){
			static std::mutex output_mutex;
			std::unique_lock<std::mutex> o_lk(output_mutex);
			//Enable ansi escape codes in windows cmd
			#ifdef _WIN32
			SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
			#endif

			std::cout << msg_str;
		}
	}

	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void log(Args&&... args) {
		return log<msg_level, empty_modifiers, Ms...>(std::forward<Args>(args)...);
	}
}
}


namespace oct {
namespace lwcl {
	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void log_line(Args&&... args) {
		log<msg_level, MTy, Ms...>(std::forward<Args>(args)..., '\n', reset_modifiers{});
		return;
	}


	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void log_line(Args&&... args) {
		return log_line<msg_level, empty_modifiers, Ms...>(std::forward<Args>(args)...);
	}
}
}


namespace oct {
namespace lwcl {
	#define L(name, ...) \
	template<typename MTy, std::uint8_t... Ms, typename... Args> 				 \
	void name(Args&&... args) {													 \
		impl::log_##name##_modifiers<__VA_ARGS__>();							 \
		return log<ll::name, MTy, Ms...>(std::forward<Args>(args)...);           \
	}																			 \
	                                                                             \
	template<std::uint8_t... Ms, typename... Args>                               \
	void name(Args&&... args) {													 \
		return name<empty_modifiers, Ms...>(std::forward<Args>(args)...);		 \
	}                                   										 \
       																			 \
	                                                                             \
	template<typename MTy, std::uint8_t... Ms, typename... Args> 				 \
	void name##_line(Args&&... args) {											 \
		impl::log_##name##_modifiers<__VA_ARGS__>();							 \
		return log_line<ll::name, MTy, Ms...>(std::forward<Args>(args)...);		 \
	}																			 \
                                                                 				 \
	template<std::uint8_t... Ms, typename... Args>               				 \
	void name##_line(Args&&... args) {											 \
		return name##_line<empty_modifiers, Ms...>(std::forward<Args>(args)...); \
	}																			 \
																				 \
																				 \
	namespace impl {															 \
		template<typename MTy, std::uint8_t... Ms>								 \
		void log_##name##_modifiers() {											 \
			log<ll::name, ::oct::lwcl::no_prefix>(MTy{}, modifiers<Ms...>{});	 \
			return;																 \
		}																		 \
																				 \
		template<std::uint8_t... Ms>											 \
		void log_##name##_modifiers() {											 \
			return log_##name##_modifiers<empty_modifiers, Ms...>();			 \
		}																		 \
	}

	OCT_LWCL_LOG_LEVELS
	#undef L
}
}