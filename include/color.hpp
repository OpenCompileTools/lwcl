#pragma once
#include <cstdint>

#include "modifiers.hpp"

namespace oct {
namespace lwcl {
	namespace color {
		namespace foreground {
			enum : uint_fast8_t {
				black = 30,
				dark_red,
				dark_green,
				dark_yellow,
				dark_blue,
				dark_magenta,
				dark_cyan,
				light_gray,

				dark_gray = black + 60,
				red,
				green,
				yellow,
				blue,
				magenta,
				cyan,
				white,
			};


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
			enum : uint_fast8_t {
				black = 40,
				dark_red,
				dark_green,
				dark_yellow,
				dark_blue,
				dark_magenta,
				dark_cyan,
				light_gray,

				dark_gray = black + 60,
				red,
				green,
				yellow,
				blue,
				magenta,
				cyan,
				white,
			};
			

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