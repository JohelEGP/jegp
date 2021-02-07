#ifndef JEGP_UTILITY_HPP
#define JEGP_UTILITY_HPP

#include <concepts>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

namespace jegp {

template <class Enum> [[nodiscard]] constexpr std::underlying_type_t<Enum> to_underlying(Enum e) noexcept //
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template <class... Args>
    requires(sizeof...(Args) >= 2)
[[nodiscard]] constexpr auto hash_combine(const Args&... args) noexcept(noexcept((..., std::hash<Args>{}(args))))
    -> decltype((..., std::hash<Args>{}(args))) //
{
    std::size_t seed{0};
    return (..., (seed ^= std::hash<Args>{}(args) + (seed << 6) + (seed >> 2)));
}

template <class DerivedRef, class Base>
    requires(
        std::is_reference_v<DerivedRef> and
        not std::is_same_v<std::remove_cvref_t<DerivedRef>, std::remove_cvref_t<Base>> and
        std::derived_from<std::remove_reference_t<DerivedRef>, std::remove_reference_t<Base>>)
[[nodiscard]] constexpr auto static_downcast(Base&& b) noexcept
    -> decltype(static_cast<DerivedRef>(std::forward<Base>(b))) {
    return static_cast<DerivedRef>(std::forward<Base>(b));
}

} // namespace jegp

#endif // JEGP_UTILITY_HPP
