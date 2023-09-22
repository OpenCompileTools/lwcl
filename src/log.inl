#include "log.hpp"

#include <initializer_list>
#include <chrono>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "logger_options.hpp"

namespace oct {
namespace lwcl {
	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void log(Args&&... args) {
		if (options::program_log_level < msg_level) return;

		//Enable ansi escape codes in windows cmd
		#ifdef _WIN32
		SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
		#endif

		std::cout << MTy{} << modifiers<Ms...>{};
		
		if(options::log_prefix){
			#ifndef OCT_LWCL_NO_TIMESTAMP
			std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << std::put_time(std::localtime(&now_time), "[%m/%d/%y|%H:%M:%S]");
			#endif


			std::cout << '[' << log_level_names[static_cast<std::size_t>(msg_level)] << "]: ";
		}

		(void)std::initializer_list<int> { ((void)(
			std::cout << std::forward<Args>(args)
		), 0)... };

		//std::cout << typename MTy::undo_type{} << typename modifiers<Ms...>::undo_type{};
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
			::oct::lwcl::options::log_prefix = false;							 \
			log<ll::name, MTy, Ms...>();									     \
			::oct::lwcl::options::log_prefix = true;							 \
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