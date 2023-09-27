#pragma once
#include <cstdint>
#include <array>


#ifndef OCT_LWCL_LOG_LEVELS
#define OCT_LWCL_LOG_LEVELS \
L(fatal,  color::fg::dark_red, style::bold) \
L(error,  color::fg::red)                   \
L(warn,   color::fg::yellow)                \
L(info)                                     \
L(system, color::fg::cyan)                  \
L(debug,  color::fg::light_gray)            \
L(trace,  color::fg::dark_gray)             \
L(loops,  color::fg::blue)
#endif


namespace oct {
namespace lwcl {
	#ifndef OCT_LWCL_LOG_LEVEL_ENUM
	#define OCT_LWCL_LOG_LEVEL_ENUM
	
	enum class log_level : std::size_t {
		#define L(name, ...) name,
		OCT_LWCL_LOG_LEVELS
		#undef L


		num_levels,

		everything = num_levels
	};

	#else
	OCT_LWCL_LOG_LEVEL_ENUM
	#endif

	using ll = log_level;
}
}


namespace oct {
namespace lwcl {
	#define L(name, ...) #name,
	constexpr std::array<const char* const, static_cast<std::size_t>(ll::num_levels)> log_level_names = { OCT_LWCL_LOG_LEVELS };
	#undef L
}
}