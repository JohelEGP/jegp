# General utilities library                                          [utilities]

## General                                                   [utilities.general]

This clause describes generally useful utilities.
These utilities are summarized in [tab:utilities.summary].

   General utilities library summary [tab:utilities.summary]

   |           | Subclause          | Header               |
   | --------- | :----------------- | :------------------- |
   | [utility] | Utility components | `<jegp/utility.hpp>` |

## Utility components                                                  [utility]

### Header `<jegp/utility.hpp>` synopsis                           [utility.syn]

This header contains some basic constructs.

```C++
namespace jegp
{
template <class T>
inline constexpr std::size_t bitsof{sizeof(T) * CHAR_BIT};

// [utility.underlying], `underlying`
template <class Enum>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept;

// [static.downcast], `static_downcast`
template <class DerivedRef, class Base>
constexpr DerivedRef static_downcast(Base&& b) noexcept;

// [hash.combine], `hash_combine`
template <class... Args>
constexpr std::size_t hash_combine(const Args&... args) noexcept(/*see below*/);

} // namespace jegp
```

### `underlying`                                            [utility.underlying]

```C++
template <class Enum>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept;
```
_Constraints:_ `std::is_enum_v<Enum>` is `true`.

_Returns:_ `static_cast<std::underlying_type_t<Enum>>(e)`.

### `static_downcast`                                          [static.downcast]

A `static_cast` that performs a downcast.

```C++
template <class DerivedRef, class Base>
constexpr DerivedRef static_downcast(Base&& b) noexcept;
```
_Constraints:_
- `std::is_reference_v<DerivedRef>` is `true`.
- `std::is_same_v<std::remove_cvref_t<DerivedRef>,
  std::remove_cvref_t<Base>>` is `false`.
- `std::derived_from<std::remove_reference_t<DerivedRef>,
  std::remove_reference_t<Base>>` is `true`.
- `static_cast<DerivedRef>(std::forward<Base>(b))` is well-formed.

_Preconditions:_ `b` is a base class subobject
of an object of type `std::remove_cvref_t<DerivedRef>`.

_Returns:_ `static_cast<DerivedRef>(std::forward<Base>(b))`.

### `hash_combine`                                                [hash.combine]

Insipred by [Boost.ContainerHash].
Useful in the specializations of `std::hash`
whose `Key`'s salient parts consist of two or more objects.

[Boost.ContainerHash]:
https://www.boost.org/doc/libs/release/doc/html/hash.html

```C++
template <class... Args>
constexpr std::size_t hash_combine(const Args&... args) noexcept(/*see below*/);
```
_Constraints:_
- `sizeof...(Args) >= 2` is `true`.
- `std::hash<Args>` is enabled (C++ Standard's [unord.hash]) for all `Args`.

_Effects:_ Equivalent to:
```C++
std::size_t seed{0};
return (..., (seed ^= std::hash<Args>{}(args) + (seed << 6) + (seed >> 2)));
```
_Remarks:_ The expression inside `noexcept` is equivalent to
`noexcept((..., std::hash<Args>{}(args)))`.
