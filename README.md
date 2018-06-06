# jegp

Generic library components for my C++ projects.

## Getting started

### Dependencies

* C++17

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
constexpr auto bitsof{sizeof(T) * CHAR_BIT};

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
