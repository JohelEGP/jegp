#ifndef JEGP_UTILITY_HPP
#define JEGP_UTILITY_HPP

#include <climits>
#include <cstddef>
#include <type_traits>
#include <range/v3/utility/concepts.hpp>

namespace jegp {

/// # General utilities library \[utilities]
///
/// ## General \[utilities.general]
///
/// This clause describes generally useful utilities. These utilities are
/// summarized in Table \[utilities].
///
/// Table \[utilities] -- General utilities library summary
///
/// |            | Subclause          | Header(s)            |
/// | ---------- | ------------------ | -------------------- |
/// | \[utility] | Utility components | `<jegp/utility.hpp>` |

/// ## Utility components \[utility]
///
/// ### Header `<jegp/utility.hpp>` synopsis \[utility.syn]
///
/// This header contains some basic constructs.
///
/// ```C++
/// namespace jegp {
///
/// template <class T>
/// inline constexpr std::size_t bitsof{sizeof(T) * CHAR_BIT};
///
/// // \[utility.underlying], `underlying`
/// template <class Enum>
/// constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept;
///
/// } // namespace jegp
/// ```

template <class T>
inline constexpr std::size_t bitsof{sizeof(T) * CHAR_BIT};

/// ### `underlying` \[utility.underlying]
///
/// _Declaration:_
/// ```C++
/// template <class Enum>
/// constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept;
/// ```
/// _Returns:_ `static_cast<std::underlying_type_t<Enum>>(e)`.
///
/// _Remarks:_ This function shall not participate in overload resolution unless
/// `Enum` is an enumeration.
template <class Enum, CONCEPT_REQUIRES_(std::is_enum_v<Enum>)>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

} // namespace jegp

#endif // JEGP_UTILITY_HPP
