#pragma once
#include <cstdint>

#include "modifiers.hpp"


#define OCT_LWCL_COLORS(black_val) \
C(black, = black_val)	   \
C(dark_red,)			   \
C(dark_green,)			   \
C(dark_yellow,)			   \
C(dark_blue,)			   \
C(dark_magenta,)		   \
C(dark_cyan,)			   \
C(light_gray,)			   \
						   \
C(dark_gray, = black + 60) \
C(red,)					   \
C(green,)				   \
C(yellow,)				   \
C(blue,)				   \
C(magenta,)				   \
C(cyan,)				   \
C(white,)				   


namespace oct {
namespace lwcl {
	namespace color {
		namespace foreground {
			enum class values : uint_fast8_t {
				#define C(name, ...) name __VA_ARGS__,
				OCT_LWCL_COLORS(30)
				#undef C
			};
			
			#define C(name, ...) using name = modifiers<static_cast<uint_fast8_t>(values::name)>;
			OCT_LWCL_COLORS(30)
			#undef C


			template<uint8_t byte_value>
			using indexed = modifiers<38, 5, byte_value>;

			template<uint8_t red, uint8_t green, uint8_t blue>
			using rgb = modifiers<38, 2, red, green, blue>;

			template<uint32_t rgb_hex_value>
			using rgb_hex = rgb<(rgb_hex_value >> 16) & 0xFF, (rgb_hex_value >> 8) & 0xFF, rgb_hex_value & 0xFF>;
		}

		namespace fg = foreground;
	}
}
}

namespace oct {
namespace lwcl {
	namespace color {
		namespace background {
			enum class values : uint_fast8_t {
				#define C(name, ...) name  __VA_ARGS__,
				OCT_LWCL_COLORS(40)
				#undef C
			};
			
			#define C(name, ...) using name = modifiers<static_cast<uint_fast8_t>(values::name)>;
			OCT_LWCL_COLORS(40)
			#undef C
			

			template<uint8_t byte_value>
			using indexed = modifiers<48, 5, byte_value>;

			template<uint8_t red, uint8_t green, uint8_t blue>
			using rgb = modifiers<48, 2, red, green, blue>;

			template<uint32_t rgb_hex_value>
			using rgb_hex = rgb<(rgb_hex_value >> 16) & 0xFF, (rgb_hex_value >> 8) & 0xFF, rgb_hex_value & 0xFF>;
		}

		namespace bg = background;
	}
}
}