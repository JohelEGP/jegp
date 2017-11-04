#ifndef JEGP_BIT_HPP
#define JEGP_BIT_HPP

#include <climits>
#include <type_traits>

namespace jegp {

template <class T>
constexpr auto bitsof{sizeof(T) * CHAR_BIT};

template <
    class UnsignedInteger, class = std::enable_if_t<
                               std::is_unsigned_v<UnsignedInteger> &&
                               std::is_integral_v<UnsignedInteger>>>
constexpr bool is_power_of_2(UnsignedInteger x) noexcept
{
    return (x != 0) && (x & (x - 1)) == 0;
}

} // namespace jegp

#endif // JEGP_BIT_HPP
