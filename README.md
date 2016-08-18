# jegp
Generic library components for my C++ projects.

This project uses [Semantic Versioning 2.0.0](http://semver.org/spec/v2.0.0.html).

The public API is the following synopsis.

## Header "utility.hpp" synopsis

```C++
template <class Enum>
constexpr auto jegp::underlying_value(Enum e) noexcept;
```
Casts an enumeration value to its underlying type.<br/>
Returns: `static_cast<std::underlying_type_t<Enum>>(e)`.<br/>
Remarks: This function shall not participate in overload resolution unless `std::is_enum_v<Enum>` is `true`.
