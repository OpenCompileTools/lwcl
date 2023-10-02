#pragma once
#include <cstdint>
#include <ctime>

#include "source_location.hpp"
#include "modifiers.hpp"
#include "color.hpp"
#include "style.hpp"
#include "log_level.hpp"


namespace oct {
namespace lwcl {
    template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
    void log(Args&&... args);

	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void log(Args&&... args);


	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void log_line(Args&&... args);

	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void log_line(Args&&... args);


	//template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	//void logf(const char* format, Args&&... args);
	// 
	//template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	//void logf(const char* format, Args&&... args);
}
}


namespace oct {
namespace lwcl {
	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void thread_log(const std::string& thread_name, Args&&... args);

	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void thread_log(const std::string& thread_name, Args&&... args);


	template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	void thread_log_line(const std::string& thread_name, Args&&... args);

	template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	void thread_log_line(const std::string& thread_name, Args&&... args);


	//template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
	//void thread_logf(const char* format, Args&&... args);
	// 
	//template<log_level msg_level, std::uint8_t... Ms, typename... Args>
	//void thread_logf(const char* format, Args&&... args);
}
}


namespace oct {
namespace lwcl {
    #define L(name, ...) \
    template<typename MTy, std::uint8_t... Ms, typename... Args>              \
    void name(Args&&... args);                                                \
                                                                              \
    template<std::uint8_t... Ms, typename... Args>                            \
    void name(Args&&... args);                                                \
                                                                              \
                                                                              \
    template<typename MTy, std::uint8_t... Ms, typename... Args>              \
    void name##_line(Args&&... args);                                         \
                                                                              \
    template<std::uint8_t... Ms, typename... Args>                            \
    void name##_line(Args&&... args);                                         \
                                                                              \
                                                                              \
                                                                              \
    template<typename MTy, std::uint8_t... Ms, typename... Args>              \
    void thread_##name(const std::string& thread_name, Args&&... args);       \
                                                                              \
    template<std::uint8_t... Ms, typename... Args>                            \
    void thread_##name(const std::string& thread_name, Args&&... args);       \
                                                                              \
                                                                              \
    template<typename MTy, std::uint8_t... Ms, typename... Args>              \
    void thread_##name##_line(const std::string& thread_name, Args&&... args);\
                                                                              \
    template<std::uint8_t... Ms, typename... Args>                            \
    void thread_##name##_line(const std::string& thread_name, Args&&... args);\
                                                                              \
                                                                              \
    namespace impl {                                                          \
        template<typename MTy, std::uint8_t... Ms>                            \
        void log_##name##_modifiers();                                        \
                                                                              \
        template<std::uint8_t... Ms>                                          \
        void log_##name##_modifiers();                                        \
    }

    OCT_LWCL_LOG_LEVELS
    #undef L
}
}


namespace oct {
namespace lwcl {
    namespace impl {
        template<log_level msg_level, typename MTy, std::uint8_t... Ms, typename... Args>
        void print(const std::string& thread_name, Args&&... args);
    }

    namespace impl {
        template<typename Arg, bool val>
        using enable_if_src_loc = typename std::enable_if<
            std::is_convertible<typename std::decay<Arg>::type, oct::lwcl::source_location>::value == val
        >::type;

        template<typename Arg>
        enable_if_src_loc<Arg, true>
        print_src_loc(std::ostringstream& oss, Arg&& arg);

        
        template<typename Arg>
        enable_if_src_loc<Arg, false>
        print_src_loc(std::ostringstream& oss, Arg&& arg);
    }
}
}



namespace oct {
namespace lwcl {
    namespace impl {
        std::tm* localtime(std::time_t* time, std::tm* buf);
    }
}
}



#include "../src/log.inl"
