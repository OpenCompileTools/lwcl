#pragma once
#include <cstdint>
#include <ostream>

#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L
#	include <source_location>
#	define OCT_HAS_SOURCE_LOCATION true
#elif defined(__has_builtin)
#	if __has_builtin(__builtin_FILE) && __has_builtin(__builtin_LINE)
#		define OCT_HAS_SOURCE_LOCATION_BUILTINS true
#		if __has_builtin(__builtin_COLUMN)
#			define OCT_HAS_SOURCE_LOCATION_COLUMN true
#		endif
#	endif
#elif !defined(__apple_build_version__) && defined(__clang__) && (__clang_major__ >= 9)
#	define OCT_HAS_SOURCE_LOCATION_BUILTINS true
#	define OCT_HAS_SOURCE_LOCATION_COLUMN true
#elif defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)) //GCC 4.8 has builtins, but they're incorrect
#	define OCT_HAS_SOURCE_LOCATION_BUILTINS true
#endif


#ifdef OCT_HAS_SOURCE_LOCATION_BUILTINS
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_LINE __builtin_LINE()
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_FILE __builtin_FILE()
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_FUNCTION __builtin_FUNCTION()
#else 
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_LINE 0
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_FILE ""
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_FUNCTION ""
#endif

#ifdef OCT_HAS_SOURCE_LOCATION_COLUMN
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_COLUMN __builtin_COLUMN()
#else 
#	define OCT_LWCL_DEFAULT_SOURCE_LOCATION_COLUMN 0
#endif



#if defined(__cpp_consteval)  && __cpp_consteval >= 201811L
#	define OCT_CPP20_CONSTEVAL consteval
#else 
#	define OCT_CPP20_CONSTEVAL constexpr
#endif

#ifdef OCT_HAS_SOURCE_LOCATION
namespace oct { namespace lwcl { namespace impl {
	using std_source_location = std::source_location;
}}}
#else
namespace oct { namespace lwcl { namespace impl {
	struct std_source_location {};
}}}
#endif


namespace oct {
namespace lwcl {
	struct source_location : impl::std_source_location {
		constexpr source_location() noexcept = default;
		constexpr source_location(
			std::uint_least32_t line, std::uint_least32_t column,
			const char* const file_name, const char* const function_name
		) noexcept;


		#ifdef OCT_HAS_SOURCE_LOCATION
		constexpr source_location(std::source_location loc) noexcept;
		constexpr source_location& operator=(std::source_location loc) noexcept;


		using std::source_location::current;
		#else 

		OCT_CPP20_CONSTEVAL static source_location current(
			std::uint_least32_t line = OCT_LWCL_DEFAULT_SOURCE_LOCATION_LINE,
			std::uint_least32_t column = OCT_LWCL_DEFAULT_SOURCE_LOCATION_COLUMN,
			const char* const file_name = OCT_LWCL_DEFAULT_SOURCE_LOCATION_FILE,
			const char* const function_name = OCT_LWCL_DEFAULT_SOURCE_LOCATION_FUNCTION
		) noexcept;
		#endif

		OCT_CPP20_CONSTEVAL static source_location current_or(
			std::uint_least32_t line,
			std::uint_least32_t column,
			const char* const file_name,
			const char* const function_name,
			source_location loc = current()
		) noexcept;


		constexpr std::uint_least32_t line() const noexcept;
		constexpr std::uint_least32_t column() const noexcept;
		constexpr const char* file_name() const noexcept;
		constexpr const char* function_name() const noexcept;

		constexpr bool line_valid() const noexcept;
		constexpr bool file_valid() const noexcept;
		constexpr bool column_valid() const noexcept;


	private:
		std::uint_least32_t _line{};
		std::uint_least32_t _column{};
		const char* _file_name = "";
		const char* _function_name = "";

		#ifdef OCT_HAS_SOURCE_LOCATION
		bool custom_values = false;
		#endif
	};
}
}


namespace oct {
namespace lwcl{
	std::ostream& operator<<(std::ostream& os, source_location loc) {
		if (!loc.file_valid() && !loc.line_valid()) return os;
		os << '<';

		if (!loc.file_valid()) goto line; 
		{
		std::string file_str(loc.file_name());
		size_t last_slash = std::max(file_str.find_last_of('/'), file_str.find_last_of('\\'));
		os << file_str.substr(last_slash == std::string::npos ? 0 : last_slash);
		}

	line:
		if (!loc.line_valid()) goto end;
		os << '(' << loc.line();
		if (loc.column_valid()) os << ',' << loc.column();
		os << ')';
	end:
		return os << '>';
	}
}
}


#define OCT_LWCL_INPLACE_LOCATION_PARAMS __LINE__, 0, __FILE__, __func__
#define OCT_LWCL_INPLACE_LOCATION oct::lwcl::source_location::current_or(OCT_LWCL_INPLACE_LOCATION_PARAMS)


#if defined(__cpp_deduction_guides) && __cpp_deduction_guides >= 201703L
#define OCT_HAS_CTAD true
#endif


#include "../src/source_location.inl"