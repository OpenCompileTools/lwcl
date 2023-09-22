#include "modifiers.hpp"

#include <initializer_list>

namespace oct {
namespace lwcl {
    std::ostream& operator<<(std::ostream& os, modifiers<>) {
        return os;
    }

    
    template<std::uint8_t M1, std::uint8_t... Ms>
    std::ostream& operator<<(std::ostream& os, modifiers<M1, Ms...>) {
        os << "\x1B[" << static_cast<unsigned>(M1);

        (void)std::initializer_list<int> { ((void)(
            os << ';' << static_cast<unsigned>(Ms)
        ), 0)... };
        
        os << 'm';
        return os;
    }
}
}


namespace oct {
namespace lwcl {
    template<typename... UIntTys>
    std::string modify(std::uint8_t first_value, UIntTys&&... modifier_values) {
        std::string ret;
        ret.reserve((sizeof...(UIntTys) * 4) + 4 + (sizeof(std::uint8_t) * 3));
        ret += "\x1B[";

        ret += std::to_string(first_value);
        (void)std::initializer_list<std::string> { (
            ret += ';', ret += std::to_string(static_cast<unsigned>(std::forward<UIntTys>(modifier_values)))
        )... };
    
        ret += 'm';
        return ret;
    }
}
}