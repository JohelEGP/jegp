# General utilities library \[utilities]

## General \[utilities.general]

This clause describes generally useful utilities.
These utilities are summarized in Table \[utilities].

Table \[utilities] -- General utilities library summary

|            | Subclause          | Header(s)            |
| ---------- | ------------------ | -------------------- |
| \[utility] | Utility components | `<jegp/utility.hpp>` |

## Utility components \[utility]

### Header `<jegp/utility.hpp>` synopsis \[utility.syn]

This header contains some basic constructs.

```C++
namespace jegp {

// \[utility.underlying], `underlying`
template <class Enum>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept;

// \[static.downcast], `static_downcast`
template <class Derived, class Base>
constexpr Derived static_downcast(Base&& b) noexcept;

// \[hash.combine], `hash_combine`
template <class... Args>
constexpr std::size_t hash_combine(const Args&... args) noexcept(/*see below*/);

} // namespace jegp
```

### `underlying` \[utility.underlying]

```C++
template <class Enum>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept;
```
_Returns:_ `static_cast<std::underlying_type_t<Enum>>(e)`.

_Remarks:_ This function shall not participate in overload resolution
unless `std::is_enum_v<Enum>` is `true`.

### `static_downcast` \[static.downcast]

A statically constrained `static_cast`
that ensures it does a downcast.
\[ _Note:_ If `b` isn't a base class subobject of type `Derived`,
the behaviour is undefined. -- _end note_ ]

```C++
template <class Derived, class Base>
constexpr Derived static_downcast(Base&& b) noexcept;
```
_Returns:_ `static_cast<Derived>(std::forward<Base>(b))`.

_Remarks:_ This function shall not participate in overload resolution
unless `std::is_reference_v<Derived>` is `true`
and `std::is_same_v<std::decay_t<Derived>, std::decay_t<Base>>` is `false`
and `ranges::DerivedFrom<std::remove_reference_t<Derived>,
std::remove_reference_t<Base>>()` is `true`
and the expression in the _Returns:_ element is well-formed.

### `hash_combine` \[hash.combine]

Insipred by [Boost.ContainerHash].
Useful in the specializations of `std::hash`
whose `Key`'s salient parts consist of two or more objects.

[Boost.ContainerHash]:
https://www.boost.org/doc/libs/release/doc/html/hash.html

```C++
template <class... Args>
constexpr std::size_t hash_combine(const Args&... args) noexcept(/*see below*/);
```
_Effects:_ Equivalent to:
```C++
std::size_t seed{};
return (..., (seed ^= std::hash<Args>{}(args) + (seed << 6) + (seed >> 2)));
```
_Remarks:_ The expression inside `noexcept` is equivalent to
the logical AND of `noexcept(std::hash<Args>{}(args))` for all `Args`.
This function shall not participate in overload resolution
unless `sizeof...(Args) >= 2`
and `std::hash<Args>` is enabled for all `Args`.

\[ _Example:_
```C++
struct Point {
    int x;
    int y;
};

template <class T>
struct Pair {
    T first;
    T second;
};

namespace std {

template <>
struct hash<Point> {
    std::size_t operator()(Point pt) const
    {
        return jegp::hash_combine(pt.x, pt.y);
    }
};

template <class T>
struct hash<Pair<T>> : private hash<T> {
    constexpr auto operator()(const Pair<T>& p) const
        noexcept(noexcept(jegp::hash_combine(p.first, p.second)))
            -> decltype(jegp::hash_combine(p.first, p.second))
    {
        return jegp::hash_combine(p.first, p.second);
    }
};

} // namespace std
```
Both specializations meet the requirements of `std::hash`.
The second one is also disabled,
or enabled and its `operator()` `noexcept`
and calls to it can appear in constant expressions,
just like the underlying `std::hash`. -- _end example_ ]
