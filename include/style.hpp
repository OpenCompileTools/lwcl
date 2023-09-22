#pragma once
#include <cstdint>

namespace oct {
namespace lwcl {
	namespace style {
		enum : uint_fast8_t {
			bold = 1,
			light,
			italic,
			underline,
			strikethrough = 9,

			primary_font,
			alt_font_1,
			alt_font_2,
			alt_font_3,
			alt_font_4,
			alt_font_5,
			alt_font_6,
			alt_font_7,
			alt_font_8,
			alt_font_9,

			double_underline = 21,

			framed = 51,
			encircled,
			overlined,
		};
	}
}
}