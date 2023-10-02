#pragma once
#include <cstdint>

#include "modifiers.hpp"


#define OCT_LWCL_STYLES \
S(bold, = 1)			  \
S(light,)				  \
S(italic,)				  \
S(underline,)			  \
S(strikethrough, = 9)	  \
						  \
S(primary_font,)		  \
S(alt_font_1,)			  \
S(alt_font_2,)			  \
S(alt_font_3,)			  \
S(alt_font_4,)			  \
S(alt_font_5,)			  \
S(alt_font_6,)			  \
S(alt_font_7,)			  \
S(alt_font_8,)			  \
S(alt_font_9,)			  \
						  \
S(double_underline, = 21) \
						  \
S(framed, = 51)			  \
S(encircled,)			  \
S(overlined,)


namespace oct {
namespace lwcl {
	namespace style {
		enum class values : uint_fast8_t {
			#define S(name, ...) name __VA_ARGS__,
			OCT_LWCL_STYLES
			#undef S
		};
		
		#define S(name, ...) using name = modifiers<static_cast<uint_fast8_t>(values::name)>;
		OCT_LWCL_STYLES
		#undef S
	}
}
}