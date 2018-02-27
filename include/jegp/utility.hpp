#ifndef JEGP_UTILITY_HPP
#define JEGP_UTILITY_HPP

#include <type_traits>

namespace jegp {

template <class T>
[[deprecated]] using Value_type = typename T::value_type;

template <class Enum, class = std::enable_if_t<std::is_enum_v<Enum>>>
constexpr auto underlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

} // namespace jegp

#endif // JEGP_UTILITY_HPP
