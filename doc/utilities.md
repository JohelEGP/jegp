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

template <class T>
inline constexpr std::size_t bitsof{sizeof(T) * CHAR_BIT};

// \[utility.underlying], `underlying`
template <class Enum>
constexpr std::underlying_type_t<Enum> underlying(Enum e) noexcept;

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
unless `sizeof...(Args) >= 2` is `true` and
`std::hash<Args>` is enabled for all `Args`.

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
        return mia::hash_combine(pt.x, pt.y);
    }
};

template <class T>
struct hash<Pair<T>> : private hash<T> {
    constexpr auto operator()(const Pair<T>& p) const
        noexcept(noexcept(mia::hash_combine(p.first, p.second)))
            -> decltype(mia::hash_combine(p.first, p.second))
    {
        return mia::hash_combine(p.first, p.second);
    }
};

} // namespace std
```
Both specializations meet the requirements of `std::hash`.
The second one is also disabled,
or enabled and its `operator()` `noexcept`
and calls to it can appear in constant expressions,
just like the underlying `std::hash`. -- _end example_ ]
