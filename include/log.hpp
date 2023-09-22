#pragma once
#include <cstdint>

#include "modifiers.hpp"
#include "color.hpp"
#include "style.hpp"
#include "log_level.hpp"

namespace oct {
namespace lwcl {
	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void log(Args&&... args);

	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void log(Args&&... args);


	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void log_line(Args&&... args);

	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void log_line(Args&&... args);


	//template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	//void logf(const char* format, Args&&... args);
	// 
	//template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	//void logf(const char* format, Args&&... args);
}
}


namespace oct {
namespace lwcl {
	#define L(name, ...) \
	template<typename MTy, std::uint8_t... Ms, typename... Args>     \
	void name(Args&&... args);					                 	 \
                                                                 	 \
	template<std::uint8_t... Ms, typename... Args>               	 \
	void name(Args&&... args);                                   	 \
                                                                 	 \
																     \
	template<typename MTy, std::uint8_t... Ms, typename... Args> 	 \
	void name##_line(Args&&... args);					         	 \
																 	 \
	template<std::uint8_t... Ms, typename... Args>               	 \
	void name##_line(Args&&... args);     							 \
																	 \
																	 \
	namespace impl {												 \
		template<typename MTy, std::uint8_t... Ms>					 \
		void log_##name##_modifiers();								 \
																	 \
		template<std::uint8_t... Ms>								 \
		void log_##name##_modifiers();								 \
	}

	OCT_LWCL_LOG_LEVELS
	#undef L
}
}


#include "../src/log.inl"