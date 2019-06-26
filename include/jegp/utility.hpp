#ifndef JEGP_UTILITY_HPP
#define JEGP_UTILITY_HPP

#include <climits>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>
#include <concepts/concepts.hpp>

namespace jegp
{
template <class T>
inline constexpr std::size_t bitsof{sizeof(T) * CHAR_BIT};

template <class Enum, std::enable_if_t<std::is_enum_v<Enum>>* = nullptr>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template <class... Args, std::enable_if_t<sizeof...(Args) >= 2>* = nullptr>
constexpr auto hash_combine(const Args&... args) noexcept(noexcept(
    (..., std::hash<Args>{}(args)))) -> decltype((..., std::hash<Args>{}(args)))
{
    std::size_t seed{};
    return (..., (seed ^= std::hash<Args>{}(args) + (seed << 6) + (seed >> 2)));
}

template <
    class Derived, class Base,
    std::enable_if_t<
        std::is_reference_v<Derived> &&
        !std::is_same_v<std::decay_t<Derived>, std::decay_t<Base>> &&
        concepts::DerivedFrom<
            std::remove_reference_t<Derived>, std::remove_reference_t<Base>>>* =
        nullptr>
constexpr auto static_downcast(Base&& b) noexcept
    -> decltype(static_cast<Derived>(std::forward<Base>(b)))
{
    return static_cast<Derived>(std::forward<Base>(b));
}

} // namespace jegp

#endif // JEGP_UTILITY_HPP
