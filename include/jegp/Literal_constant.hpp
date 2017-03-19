#ifndef JEGP_LITERAL_CONSTANT_HPP
#define JEGP_LITERAL_CONSTANT_HPP

#include <boost/hana/core/to.hpp>
#include <boost/hana/value.hpp>

namespace jegp {

template <class T>
struct Literal_constant_tag;

template <class T, class... Constants>
struct Literal_constant {
    static constexpr T value{boost::hana::value<Constants>()...};

    using value_type = T;
    using type       = Literal_constant<T, Constants...>;

    constexpr operator value_type() const noexcept
    {
        return value;
    }
    constexpr value_type operator()() const noexcept
    {
        return value;
    }

    using hana_tag = Literal_constant_tag<T>;
};

} // namespace jegp

namespace boost::hana {

template <class T>
struct value_impl<jegp::Literal_constant_tag<T>> {
    template <class U>
    static constexpr auto apply() noexcept
    {
        return U::value;
    }
};

template <class T, class From>
struct to_impl<jegp::Literal_constant_tag<T>, From>
  : embedding<is_embedded<typename From::value_type, T>::value> {
    template <class U>
    static constexpr auto apply(const U&) noexcept
    {
        return jegp::Literal_constant<T, U>{};
    }
};

} // namespace boost::hana

#endif // JEGP_LITERAL_CONSTANT_HPP
