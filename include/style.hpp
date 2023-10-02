#pragma once
#include <cstdint>

#include "modifiers.hpp"


namespace oct {
namespace lwcl {
	namespace style {
		using bold          = modifiers<1>;
		using light         = modifiers<2>;
		using italic        = modifiers<3>;
		using underline     = modifiers<4>;
		using strikethrough = modifiers<9>;

		constexpr std::uint8_t font_base = 10;
		using primary_font = modifiers<font_base + 0>;
		using alt_font_1   = modifiers<font_base + 1>;
		using alt_font_2   = modifiers<font_base + 2>;
		using alt_font_3   = modifiers<font_base + 3>;
		using alt_font_4   = modifiers<font_base + 4>;
		using alt_font_5   = modifiers<font_base + 5>;
		using alt_font_6   = modifiers<font_base + 6>;
		using alt_font_7   = modifiers<font_base + 7>;
		using alt_font_8   = modifiers<font_base + 8>;
		using alt_font_9   = modifiers<font_base + 9>;

		using double_underline = modifiers<21>; 

		using framed    = modifiers<51>;
		using encircled = modifiers<52>;
		using overlined = modifiers<53>;
	}
}
}