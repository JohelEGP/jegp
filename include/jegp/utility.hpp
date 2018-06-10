#ifndef JEGP_UTILITY_HPP
#define JEGP_UTILITY_HPP

#include <climits>
#include <cstddef>
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

} // namespace jegp

#endif // JEGP_UTILITY_HPP
