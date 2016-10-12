# jegp

Generic library components for my C++ projects.

## Dependencies

* A partial implementation of the upcoming standard following C++14
    - Variable type traits
* Technical Specifications
    - Library Fundamentals
        + `<experimental/string_view>`

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
#include <experimental/string_view>

namespace jegp {

class String_view;

} // jegp namespace
```

#### 2.1 Class `String_view`

A mutable string view.

```C++
class String_view : public std::experimental::string_view {
    using Base = std::experimental::string_view; // exposition only
public:
    using iterator = pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;

    constexpr String_view() noexcept = default;
    constexpr String_view(char* str);
    constexpr String_view(char* str, size_type len);

    using Base::begin;
    using Base::end;
    constexpr iterator begin() noexcept;
    constexpr iterator end() noexcept;

    using Base::rbegin;
    using Base::rend;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    using Base::operator[];
    using Base::at;
    constexpr reference operator[](size_type pos);
    constexpr reference at(size_type pos);

    using Base::front;
    using Base::back;
    constexpr reference front();
    constexpr reference back();

    using Base::data;
    constexpr pointer data() noexcept;

    constexpr String_view substr(size_type pos = 0, size_type n = npos) const;
};
```

##### 2.1.1 Construction

```C++
constexpr String_view(char* str);
constexpr String_view(char* str, size_type len);
```
Effects: Initializes the base with the same argument list.

##### 2.1.2 Iterator support

```C++
constexpr iterator begin() noexcept;
```
Returns: `data()`.

```C++
constexpr iterator end() noexcept;
```
Returns: `begin() + size()`.

```C++
reverse_iterator rbegin() noexcept;
```
Returns: `reverse_iterator{end()}`.

```C++
reverse_iterator rend() noexcept;
```
Returns: `reverse_iterator{begin()}`.

##### 2.1.3 Element access

```C++
constexpr reference operator[](size_type pos);
```
Effects: Equivalent to `return const_cast<reference>(Base::operator[](pos));`.

```C++
constexpr reference at(size_type pos);
```
Effects: Equivalent to `return const_cast<reference>(Base::at(pos));`.

```C++
constexpr reference front();
```
Effects: Equivalent to `return const_cast<reference>(Base::front());`.

```C++
constexpr reference back();
```
Effects: Equivalent to `return const_cast<reference>(Base::back());`.

```C++
constexpr pointer data() noexcept;
```
Returns: `const_cast<pointer>(Base::data())`.

##### 2.1.4 String operations

```C++
constexpr String_view substr(size_type pos = 0, size_type n = npos) const;
```
Returns: A string view that equals the value of `Base::substr(pos,n)`.
