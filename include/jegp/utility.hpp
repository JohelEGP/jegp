#ifndef JEGP_UTILITY_HPP
#define JEGP_UTILITY_HPP

#include <climits>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <range/v3/utility/concepts.hpp>

namespace jegp {

template <class T>
inline constexpr std::size_t bitsof{sizeof(T) * CHAR_BIT};

template <class Enum, CONCEPT_REQUIRES_(std::is_enum_v<Enum>)>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template <class... Args, CONCEPT_REQUIRES_(sizeof...(Args) >= 2)>
constexpr auto hash_combine(const Args&... args) noexcept(noexcept(
    (..., std::hash<Args>{}(args)))) -> decltype((..., std::hash<Args>{}(args)))
{
    std::size_t seed{};
    return (..., (seed ^= std::hash<Args>{}(args) + (seed << 6) + (seed >> 2)));
}

} // namespace jegp

#endif // JEGP_UTILITY_HPP
