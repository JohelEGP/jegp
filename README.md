# jegp

Generic library components for my C++ projects.

## Dependencies

* Partial C++17 support
    - Variable type traits
    - `<string_view>`

## Specification

This project uses [Semantic Versioning 2.0.0](http://semver.org/).

This specification is the public API.

### 1 Header `<jegp/utility.hpp>` synopsis

```C++
namespace jegp {

template <class Enum>
constexpr auto underlying_value(Enum e) noexcept;

} // jegp namespace
```

#### 1.1 `underlying_value`

Casts an enumeration value to its underlying type.

```C++
template <class Enum>
constexpr auto underlying_value(Enum e) noexcept;
```
Returns: `static_cast<std::underlying_type_t<Enum>>(e)`.<br/>
Remarks: This function shall not participate in overload resolution unless `std::is_enum_v<Enum>` is `true`.

### 2 Header `<jegp/String_view.hpp>` synopsis

```C++
#include <string_view>

namespace jegp {

template <class charT, class traits = std::char_traits<charT>>
class Basic_string_view;

using    String_view = Basic_string_view<char>;
using u16String_view = Basic_string_view<char16_t>;
using u32String_view = Basic_string_view<char32_t>;
using   wString_view = Basic_string_view<wchar_t>;

} // jegp namespace
```

#### 2.1 Class template `Basic_string_view`

Describes a mutable string view.

```C++
template <class charT, class traits = std::char_traits<charT>>
class Basic_string_view : public std::basic_string_view<charT,traits> {
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

##### 2.1.1 Construction

```C++
constexpr Basic_string_view(charT* str);
constexpr Basic_string_view(charT* str, size_type len);
```
Effects: Initializes the base with the same argument list.

##### 2.1.2 Iterator support

```C++
constexpr iterator begin() const noexcept;
constexpr iterator cbegin() const noexcept;
```
Returns: `data()`.

```C++
constexpr iterator end() const noexcept;
constexpr iterator cend() const noexcept;
```
Returns: `begin() + Base::size()`.

```C++
constexpr reverse_iterator rbegin() const noexcept;
constexpr reverse_iterator crbegin() const noexcept;
```
Returns: `reverse_iterator{end()}`.

```C++
constexpr reverse_iterator rend() const noexcept;
constexpr reverse_iterator crend() const noexcept;
```
Returns: `reverse_iterator{begin()}`.

##### 2.1.3 Element access

```C++
constexpr reference operator[](size_type pos) const;
```
Effects: Equivalent to `return const_cast<reference>(Base::operator[](pos));`.

```C++
constexpr reference at(size_type pos) const;
```
Effects: Equivalent to `return const_cast<reference>(Base::at(pos));`.

```C++
constexpr reference front() const;
```
Effects: Equivalent to `return const_cast<reference>(Base::front());`.

```C++
constexpr reference back() const;
```
Effects: Equivalent to `return const_cast<reference>(Base::back());`.

```C++
constexpr pointer data() const noexcept;
```
Returns: `const_cast<pointer>(Base::data())`.

##### 2.1.4 String operations

```C++
constexpr Basic_string_view substr(size_type pos = 0, size_type n = Base::npos)
    const;
```
Returns: A string view that equals the value of `Base::substr(pos,n)`.
