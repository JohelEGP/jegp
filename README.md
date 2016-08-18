# jegp
Generic library components for my C++ projects.

This project uses [Semantic Versioning 2.0.0](http://semver.org/spec/v2.0.0.html).

The public API is the following specification.

## Header "utility.hpp" synopsis
```C++
namespace jegp {

template <class Enum>
constexpr auto underlying_value(Enum e) noexcept;

} // jegp namespace
```

### underlying_value
Casts an enumeration value to its underlying type.
```C++
template <class Enum>
constexpr auto underlying_value(Enum e) noexcept;
```
Returns: `static_cast<std::underlying_type_t<Enum>>(e)`.<br/>
Remarks: This function shall not participate in overload resolution unless `std::is_enum_v<Enum>` is `true`.
