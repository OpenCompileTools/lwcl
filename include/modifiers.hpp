#pragma once
#include <cstdint>
#include <iostream>
#include <string>

#include "../src/ansi_seq.hpp"

namespace oct {
namespace lwcl {
    template<std::uint8_t... Is>
    struct modifiers;

    //namespace impl {
    //    template<std::uint8_t... Is>
    //    struct undo_modifiers : modifiers<0> {};

    //    template<>
    //    struct undo_modifiers<> : modifiers<> {};
    //}


    template<std::uint8_t... Is>
    struct modifiers : impl::ansi_seq<Is...> {
        constexpr static std::array<std::uint8_t, sizeof...(Is)> values = { Is... };
        
        //using undo_type = impl::undo_modifiers<Is...>;
    };

    using reset_modifiers = modifiers<0>;

    using empty_modifiers = modifiers<>;
}
}


namespace oct {
namespace lwcl {
    std::ostream& operator<<(std::ostream& os, modifiers<>);
    

    template<std::uint8_t M1, std::uint8_t... Ms>
    std::ostream& operator<<(std::ostream& os, modifiers<M1, Ms...>);
}
}


namespace oct {
namespace lwcl {
    template<typename... UIntTys>
    std::string modify(std::uint8_t first_value, UIntTys&&... modifier_values);
}
}

#include "../src/modifiers.inl"