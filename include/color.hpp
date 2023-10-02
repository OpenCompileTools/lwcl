#pragma once
#include <cstdint>

#include "modifiers.hpp"


namespace oct {
namespace lwcl {
	namespace color {
		namespace foreground {
			constexpr std::uint8_t base = 30; //This is the only difference between foreground and background
			using black        = modifiers<base + 0>;
			using dark_red     = modifiers<base + 1>;
			using dark_green   = modifiers<base + 2>;
			using dark_yellow  = modifiers<base + 3>;
			using dark_blue    = modifiers<base + 4>;
			using dark_magenta = modifiers<base + 5>;
			using dark_cyan    = modifiers<base + 6>;
			using dark_white   = modifiers<base + 7>;

			constexpr std::uint8_t light_base = base + 60;
			using light_black  = modifiers<light_base + 0>;
			using red          = modifiers<light_base + 1>;
			using green        = modifiers<light_base + 2>;
			using yellow       = modifiers<light_base + 3>;
			using blue         = modifiers<light_base + 4>;
			using magenta      = modifiers<light_base + 5>;
			using cyan         = modifiers<light_base + 6>;
			using white        = modifiers<light_base + 7>;

			using light_gray = dark_white;
			using dark_gray  = light_black;


			template<uint8_t byte_value>
			using indexed = modifiers<base + 8, 5, byte_value>;


			template<uint8_t red, uint8_t green, uint8_t blue>
			using rgb = modifiers<base + 8, 2, red, green, blue>;

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
			constexpr std::uint8_t base = 40; //This is the only difference between foreground and background
			using black        = modifiers<base + 0>;
			using dark_red     = modifiers<base + 1>;
			using dark_green   = modifiers<base + 2>;
			using dark_yellow  = modifiers<base + 3>;
			using dark_blue    = modifiers<base + 4>;
			using dark_magenta = modifiers<base + 5>;
			using dark_cyan    = modifiers<base + 6>;
			using dark_white   = modifiers<base + 7>;

			constexpr std::uint8_t light_base = base + 60;
			using light_black  = modifiers<light_base + 0>;
			using red          = modifiers<light_base + 1>;
			using green        = modifiers<light_base + 2>;
			using yellow       = modifiers<light_base + 3>;
			using blue         = modifiers<light_base + 4>;
			using magenta      = modifiers<light_base + 5>;
			using cyan         = modifiers<light_base + 6>;
			using white        = modifiers<light_base + 7>;

			using light_gray = dark_white;
			using dark_gray  = light_black;
			

			template<uint8_t byte_value>
			using indexed = modifiers<base + 8, 5, byte_value>;


			template<uint8_t red, uint8_t green, uint8_t blue>
			using rgb = modifiers<base + 8, 2, red, green, blue>;

			template<uint32_t rgb_hex_value>
			using rgb_hex = rgb<(rgb_hex_value >> 16) & 0xFF, (rgb_hex_value >> 8) & 0xFF, rgb_hex_value & 0xFF>;
		}

		namespace bg = background;
	}
}
}