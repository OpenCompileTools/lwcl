#include "source_location.hpp"

#ifdef OCT_HAS_SOURCE_LOCATION
namespace oct {
namespace lwcl {
	constexpr source_location::source_location(
		std::uint_least32_t line, std::uint_least32_t column,
		const char* const file_name, const char* const function_name
	) noexcept :
		_line(line), _column(column), _file_name(file_name), _function_name(function_name),
		custom_values(true) {}
}
}
#else
namespace oct {
namespace lwcl {
	constexpr source_location::source_location(
		std::uint_least32_t line, std::uint_least32_t column,
		const char* const file_name, const char* const function_name
	) noexcept :
		_line(line), _column(column), _file_name(file_name), _function_name(function_name) {}
}
}
#endif


#ifdef OCT_HAS_SOURCE_LOCATION
namespace oct {
namespace lwcl {
	#if defined(__clang__) || defined(__GNUC__)
	_Pragma("GCC diagnostic push") \
	_Pragma("GCC diagnostic ignored \"-Wpre-c++14-compat\"")
	#endif

	constexpr source_location::source_location(std::source_location loc) noexcept :
		std::source_location(loc) {}

	constexpr source_location& source_location::operator=(std::source_location loc) noexcept {
		std::source_location::operator=(loc);
		return *this;
	}
	#if defined(__clang__) || defined(__GNUC__)
	_Pragma("GCC diagnostic pop")
	#endif
}
}
#endif


#ifndef OCT_HAS_SOURCE_LOCATION
namespace oct {
namespace lwcl {
	OCT_CPP20_CONSTEVAL source_location source_location::current(
		std::uint_least32_t line,
		std::uint_least32_t column,
		const char* const file_name,
		const char* const function_name
	) noexcept {
		return { line, column, file_name, function_name };
	}
}
}
#endif


#if defined(OCT_HAS_SOURCE_LOCATION_BUILTINS) || defined(OCT_HAS_SOURCE_LOCATION)
namespace oct {
namespace lwcl {
	OCT_CPP20_CONSTEVAL source_location source_location::current_or(
		std::uint_least32_t, std::uint_least32_t,
		const char* const, const char* const,
		source_location loc
	) noexcept {
		return loc;
	}
}
}
#else
namespace oct {
namespace lwcl {
	OCT_CPP20_CONSTEVAL source_location source_location::current_or(
		std::uint_least32_t line,
		std::uint_least32_t column,
		const char* const file_name,
		const char* const function_name,
		source_location
	) noexcept {
		return { line, column, file_name, function_name };
	}
}
}
#endif


#ifdef OCT_HAS_SOURCE_LOCATION
namespace oct {
namespace lwcl {
	constexpr std::uint_least32_t source_location::line() const noexcept {
		return custom_values ? _line : std::source_location::line();
	}

	constexpr std::uint_least32_t source_location::column() const noexcept {
		return custom_values ? _column : std::source_location::column();
	}

	constexpr const char* source_location::file_name() const noexcept {
		return custom_values ? _file_name : std::source_location::file_name();
	}

	constexpr const char* source_location::function_name() const noexcept {
		return custom_values ? _function_name : std::source_location::function_name();
	}


	constexpr bool source_location::line_valid() const noexcept {
		return !custom_values || _line != 0;
	}

	constexpr bool source_location::file_valid() const noexcept {
		return !custom_values || _file_name[0] != '\0';
	}
	
	constexpr bool source_location::column_valid() const noexcept {
		return !custom_values || _column != 0;
	}
}
}
#else
namespace oct {
namespace lwcl {
	constexpr std::uint_least32_t source_location::line() const noexcept {
		return _line;
	}

	constexpr std::uint_least32_t source_location::column() const noexcept {
		return _column;
	}

	constexpr const char* source_location::file_name() const noexcept {
		return _file_name;
	}

	constexpr const char* source_location::function_name() const noexcept {
		return _function_name;
	}


	constexpr bool source_location::line_valid() const noexcept {
		return _line != 0;
	}

	constexpr bool source_location::file_valid() const noexcept {
		return _file_name[0] != '\0';
	}

	constexpr bool source_location::column_valid() const noexcept {
		return  _column != 0;
	}
}
}
#endif