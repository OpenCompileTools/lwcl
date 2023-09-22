#pragma once
#include <cstdint>

namespace oct {
namespace lwcl {
    namespace impl{
    #if defined(OCT_INT_SEQ)
        #include "integer_sequence.hpp"
        template<std::uint8_t... Is>
        using ansi_seq = oct::integer_sequence<std::uint8_t, Is...>;
    #elif defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304L
        #include <utility>
        template<std::uint8_t... Is>
        using ansi_seq = std::integer_sequence<std::uint8_t, Is...>;
    #else
        template<std::uint8_t... Is>
        struct ansi_seq {};
    #endif
    }
}
}