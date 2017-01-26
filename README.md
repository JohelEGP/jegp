# jegp

Generic library components for my C++ projects.

## Dependencies

* Partial C++17 support
    - Variable type traits
    - `<string_view>`
* [Boost.Hana](http://www.boost.org/doc/libs/release/libs/hana/doc/html/index.html)

## Specification

This project uses [Semantic Versioning 2.0.0](http://semver.org/).

This specification is the public API.

### 1 Header `<jegp/utility.hpp>` synopsis

```C++
namespace jegp {

template <class Enum>
constexpr auto underlying(Enum e) noexcept;

} // namespace jegp
```

#### 1.1 `underlying`

Casts an enumeration value to its underlying type.

```C++
template <class Enum>
constexpr auto underlying(Enum e) noexcept;
```
_Returns:_ `static_cast<std::underlying_type_t<Enum>>(e)`.<br/>
_Remarks:_ This function shall not participate in overload resolution unless `std::is_enum_v<Enum>` is `true`.

### 2 Header `<jegp/Literal_constant.hpp>` synopsis

```C++
namespace jegp {

template <class T>
struct Literal_constant_tag;

template <class T, class... Constants>
struct Literal_constant;

} // namespace jegp
```

#### 2.1 Class template `Literal_constant`

Class template `Literal_constant` wraps a `constexpr` value of type `T` initialized from Boost.Hana [`Constant`](http://www.boost.org/doc/libs/1_62_0/libs/hana/doc/html/group__group-Constant.html)s. `Literal_constant` is itself a Boost.Hana `Constant`.

```C++
template <class T, class... Constants>
struct Literal_constant {
    static constexpr T value {boost::hana::value<Constants>()...};
    using value_type = T;
    using type       = Literal_constant<T,Constants...>;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }

    using hana_tag = Literal_constant_tag<T>;
};
```

### Deprecated.1 Header `<jegp/utility.hpp>` synopsis

```C++
namespace jegp {

template <class Enum>
constexpr auto underlying_value(Enum e) noexcept;

} // namespace jegp
```

#### 1.1 `underlying_value`

This component has been deprecated and replaced by `underlying`.

### Deprecated.2 Header `<jegp/String_view.hpp>` synopsis

[ _Note:_ This component has been deprecated because a "view" is supposed to reflect something inmutable in the standard, and I would not like to deviate from that meaning. It will be renamed or removed some time in the future. -- _end note_ ]

```C++
namespace jegp {

template <class charT, class traits = std::char_traits<charT>>
class Basic_string_view;

using    String_view = Basic_string_view<char>;
using u16String_view = Basic_string_view<char16_t>;
using u32String_view = Basic_string_view<char32_t>;
using   wString_view = Basic_string_view<wchar_t>;

} // namespace jegp
```

#### Deprecated.2.1 Class template `Basic_string_view`

Describes a mutable string view.

```C++
template <class charT, class traits = std::char_traits<charT>>
class Basic_string_view
  : public std::basic_string_view<charT,traits> // exposition only
{
private:
    using Base = std::basic_string_view<charT,traits>; // exposition only
public:
    using typename Base::pointer;
    using typename Base::reference;
    using iterator               = pointer;
    using const_iterator         = iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = reverse_iterator;
    using typename Base::size_type;

    constexpr Basic_string_view() noexcept = default;
    constexpr Basic_string_view(charT* str);
    constexpr Basic_string_view(charT* str, size_type len);

    template <class T>
    explicit constexpr operator T() const noexcept(/*see below*/);

    constexpr iterator begin() const noexcept;
    constexpr iterator end() const noexcept;
    constexpr iterator cbegin() const noexcept;
    constexpr iterator cend() const noexcept;

    constexpr reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator rend() const noexcept;
    constexpr reverse_iterator crbegin() const noexcept;
    constexpr reverse_iterator crend() const noexcept;

    constexpr reference operator[](size_type pos) const;
    constexpr reference at(size_type pos) const;

    constexpr reference front() const;
    constexpr reference back() const;

    constexpr pointer data() const noexcept;

    constexpr Basic_string_view substr(
        size_type pos = 0, size_type n = Base::npos) const;
};
```

##### Deprecated.2.1.1 Construction

```C++
constexpr Basic_string_view(charT* str);
constexpr Basic_string_view(charT* str, size_type len);
```
_Effects:_ Initializes the base with the same argument list.

```C++
template <class T>
explicit constexpr operator T() const noexcept(/*see below*/);
```
_Returns:_ `T{static_cast<Base>(*this)}`.<br/>
_Remarks:_ The expression inside `noexcept` is equivalent to `std::is_nothrow_constructible_v<T,Base>`. This function shall not participate in overload resolution unless `std::is_constructible_v<T,Base>` is `true`.<br/>
_Notes:_ This allows conversion from `String_view` to `std::string`, just like `std::string_view`.

##### Deprecated.2.1.2 Iterator support

```C++
constexpr iterator begin() const noexcept;
constexpr iterator cbegin() const noexcept;
```
_Returns:_ `data()`.

```C++
constexpr iterator end() const noexcept;
constexpr iterator cend() const noexcept;
```
_Returns:_ `begin() + Base::size()`.

```C++
constexpr reverse_iterator rbegin() const noexcept;
constexpr reverse_iterator crbegin() const noexcept;
```
_Returns:_ `reverse_iterator{end()}`.

```C++
constexpr reverse_iterator rend() const noexcept;
constexpr reverse_iterator crend() const noexcept;
```
_Returns:_ `reverse_iterator{begin()}`.

##### Deprecated.2.1.3 Element access

```C++
constexpr reference operator[](size_type pos) const;
```
_Effects:_ Equivalent to `return const_cast<reference>(Base::operator[](pos));`

```C++
constexpr reference at(size_type pos) const;
```
_Effects:_ Equivalent to `return const_cast<reference>(Base::at(pos));`

```C++
constexpr reference front() const;
```
_Effects:_ Equivalent to `return const_cast<reference>(Base::front());`

```C++
constexpr reference back() const;
```
_Effects:_ Equivalent to `return const_cast<reference>(Base::back());`

```C++
constexpr pointer data() const noexcept;
```
_Returns:_ `const_cast<pointer>(Base::data())`.

##### Deprecated.2.1.4 String operations

```C++
constexpr Basic_string_view substr(size_type pos = 0, size_type n = Base::npos)
    const;
```
_Returns:_ A string view that equals the value of `Base::substr(pos,n)`.
