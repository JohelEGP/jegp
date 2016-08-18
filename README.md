# jegp
Generic library components for my C++ projects.

## Header "utility.hpp" synopsis

```C++
template <class Enum>
constexpr auto jegp::underlying_value(Enum e) noexcept;
```
Casts an enumeration value to its underlying type.<br/>
Returns: `static_cast<std::underlying_type_t<Enum>>(e)`.<br/>
Remarks: This function shall not participate in overload resolution unless `std::is_enum_v<Enum>` is `true`.
