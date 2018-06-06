# jegp

Generic library components for my C++ projects.

## Getting started

### Dependencies

* C++17
* [Boost.Hana](http://www.boost.org/doc/libs/release/libs/hana/doc/html/index.html)
* [type_safe](https://github.com/foonathan/type_safe)

### Installation

We support [CMake](https://cmake.org/). Just execute these commands from the root of the project:

```
cmake -E make_directory build
cmake -E chdir build cmake ..
```

And optionally install the library:

```
cmake --build build --target install
```

### Using

After building jegp, you can use it by adding the following to your `CMakeLists.txt`.

    find_package(jegp)
    target_link_libraries(<your_target> jegp::jegp)

## Specification

This project uses [Semantic Versioning 2.0.0](http://semver.org/).

This specification is the public API.

### 1 Header `<jegp/utility.hpp>` synopsis

```C++
namespace jegp {

template <class T>
using Value_type = typename T::value_type;

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

### 2 Header `<jegp/bit.hpp>` synopsis

```C++
namespace jegp {

template <class T>
constexpr auto bitsof{sizeof(T) * CHAR_BIT};

template <class UnsignedInteger>
constexpr bool is_power_of_2(UnsignedInteger x) noexcept;

} // namespace jegp
```

#### 2.1 `is_power_of_2`

Checks if a value is a power of 2.

```C++
template <class UnsignedInteger>
constexpr bool is_power_of_2(UnsignedInteger x) noexcept;
```
_Returns:_ `true` if `x` is a power of 2, and `false` otherwise.<br/>
_Remarks:_ This function shall not participate in overload resolution unless `std::is_unsigned_v<UnsignedInteger>` is `true` and `std::is_integral_v<UnsignedInteger>` is `true`.

### 3 Header `<jegp/Literal_constant.hpp>` synopsis

```C++
namespace jegp {

template <class T>
struct Literal_constant_tag;

template <class T, class... Constants>
struct Literal_constant;

} // namespace jegp
```

#### 3.1 Class template `Literal_constant`

Class template `Literal_constant` wraps a `constexpr` value of type `T` initialized from Boost.Hana [`Constant`](http://www.boost.org/doc/libs/release/libs/hana/doc/html/group__group-Constant.html)s. `Literal_constant` is itself a Boost.Hana `Constant`.

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

### 4 Header `<jegp/Strong_typedef.hpp>` synopsis

```C++
#include <type_safe/strong_typedef.hpp>

namespace jegp {

template <class T, class Phantom>
class Strong_typedef;

} // namespace jegp
```

#### 4.1 Class template `Strong_typedef`

The class template `Strong_typedef` is a convenience wrapper over [`type_safe::strong_typedef`](http://foonathan.net/doc/type_safe/doc_strong_typedef.html#ts::strong_typedef-Tag,T-).

```C++
template <class T, class Phantom>
class Strong_typedef
  : public type_safe::strong_typedef<Phantom, T>
  , public type_safe::strong_typedef_op::equality_comparison<
        Strong_typedef<T, Phantom>>
  , public type_safe::strong_typedef_op::relational_comparison<
        Strong_typedef<T, Phantom>> {
public:
    using type_safe::strong_typedef<Phantom, T>::strong_typedef;
};
```

### 5 Header `<jegp/String_ref.hpp>` synopsis

```C++
namespace jegp {

template <class charT, class traits = std::char_traits<charT>>
class Basic_string_ref;

using    String_ref = Basic_string_ref<char>;
using u16String_ref = Basic_string_ref<char16_t>;
using u32String_ref = Basic_string_ref<char32_t>;
using   wString_ref = Basic_string_ref<wchar_t>;

} // namespace jegp
```

#### 5.1 Class template `Basic_string_ref`

Describes a mutable string reference.

```C++
template <class charT, class traits = std::char_traits<charT>>
class Basic_string_ref
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

    constexpr Basic_string_ref() noexcept = default;
    constexpr Basic_string_ref(charT* str);
    constexpr Basic_string_ref(charT* str, size_type len);

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

    constexpr Basic_string_ref substr(
        size_type pos = 0, size_type n = Base::npos) const;
};
```

##### 5.1.1 Construction

```C++
constexpr Basic_string_ref(charT* str);
constexpr Basic_string_ref(charT* str, size_type len);
```
_Effects:_ Initializes the base with the same argument list.

```C++
template <class T>
explicit constexpr operator T() const noexcept(/*see below*/);
```
_Returns:_ `T{static_cast<Base>(*this)}`.<br/>
_Remarks:_ The expression inside `noexcept` is equivalent to `std::is_nothrow_constructible_v<T,Base>`. This function shall not participate in overload resolution unless `std::is_constructible_v<T,Base>` is `true`.<br/>
_Notes:_ This allows conversion from `String_ref` to `std::string`, just like `std::string_view`.

##### 5.1.2 Iterator support

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

##### 5.1.3 Element access

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

##### 5.1.4 String operations

```C++
constexpr Basic_string_ref substr(size_type pos = 0, size_type n = Base::npos)
    const;
```
_Returns:_ A string reference that equals the value of `Base::substr(pos,n)`.
