#include <cassert>
#include <cstddef>
#include <functional>
#include <utility>
#include <experimental/type_traits>
#include <jegp/utility.hpp>

// \[hash.combine]

namespace
{
struct X
{
    int v;
};

struct Y
{
};

struct Z
{
};

} // namespace

namespace std
{
template <>
struct hash<X>
{
    constexpr std::size_t operator()(X x) const noexcept
    {
        return x.v;
    }
};

template <>
struct hash<Y>
{
    std::size_t operator()(Y) const
    {
        return 0;
    }
};

template <>
struct hash<Z> : hash<void>
{
};

} // namespace std

namespace
{
template <class... Args>
using hash_combine_t = decltype(jegp::hash_combine(std::declval<Args>()...));

template <class... Args>
constexpr bool is_hash_combinable{
    std::experimental::is_detected_v<hash_combine_t, Args...>};

constexpr void test_hash_combine()
{
    static_assert(!is_hash_combinable<>);
    static_assert(!is_hash_combinable<int>);
    static_assert(!is_hash_combinable<X>);
    static_assert(!is_hash_combinable<Y>);
    static_assert(!is_hash_combinable<Z>);
    static_assert(is_hash_combinable<int, int>);
    static_assert(is_hash_combinable<int, X>);
    static_assert(is_hash_combinable<X, int>);
    static_assert(is_hash_combinable<X, X>);
    static_assert(is_hash_combinable<int, Y>);
    static_assert(is_hash_combinable<Y, int>);
    static_assert(is_hash_combinable<Y, Y>);
    static_assert(!is_hash_combinable<int, Z>);
    static_assert(!is_hash_combinable<Z, int>);
    static_assert(!is_hash_combinable<Z, Z>);

    static_assert(noexcept(jegp::hash_combine(0, 0)));
    static_assert(noexcept(jegp::hash_combine(0, X{})));
    static_assert(noexcept(jegp::hash_combine(X{}, 0)));
    static_assert(noexcept(jegp::hash_combine(X{}, X{})));
    static_assert(!noexcept(jegp::hash_combine(0, Y{})));
    static_assert(!noexcept(jegp::hash_combine(Y{}, 0)));
    static_assert(!noexcept(jegp::hash_combine(Y{}, Y{})));

    const X x[]{42, 17, -20};

    std::size_t seed{};

    seed ^= x[0].v;
    seed ^= x[1].v + (seed << 6) + (seed >> 2);

    assert(seed == jegp::hash_combine(x[0], x[1]));

    seed ^= x[2].v + (seed << 6) + (seed >> 2);

    assert(seed == jegp::hash_combine(x[0], x[1], x[2]));
}

// \[static.downcast]

template <class Derived, class Base>
using static_downcast_t =
    decltype(jegp::static_downcast<Derived>(std::declval<Base>()));

template <class DerivedRef, class Base>
constexpr bool is_static_downcastable{
    std::experimental::is_detected_v<static_downcast_t, DerivedRef, Base>};

template <class Derived, class Base>
constexpr bool is_static_downcast_assertable{
    std::is_same_v<Derived, std::decay_t<Derived>> &&
    std::is_same_v<Base, std::decay_t<Base>> &&
    !std::is_same_v<Derived, Base> && std::is_base_of_v<Base, Derived>};

template <
    class Derived, class Base, bool ExpectedToPass = true,
    std::enable_if_t<is_static_downcast_assertable<Derived, Base>>* = nullptr>
constexpr void assert_is_static_downcastable()
{
    auto ok = [](bool b) { return b == ExpectedToPass; };

    static_assert(ok(is_static_downcastable<Derived&, Base&>));
    static_assert(ok(is_static_downcastable<const Derived&, Base&>));
    static_assert(ok(is_static_downcastable<Derived&&, Base&>));
    static_assert(ok(is_static_downcastable<const Derived&&, Base&>));

    static_assert(!is_static_downcastable<Derived&, const Base&>);
    static_assert(ok(is_static_downcastable<const Derived&, const Base&>));
    static_assert(!is_static_downcastable<Derived&&, const Base&>);
    static_assert(ok(is_static_downcastable<const Derived&&, const Base&>));

    static_assert(!is_static_downcastable<Derived&, Base>);
    static_assert(!is_static_downcastable<const Derived&, Base>);
    static_assert(ok(is_static_downcastable<Derived&&, Base>));
    static_assert(ok(is_static_downcastable<const Derived&&, Base>));

    static_assert(!is_static_downcastable<Derived&, const Base>);
    static_assert(!is_static_downcastable<const Derived&, const Base>);
    static_assert(!is_static_downcastable<Derived&&, const Base>);
    static_assert(ok(is_static_downcastable<const Derived&&, const Base>));

    static_assert(!is_static_downcastable<Derived, Base&>);
    static_assert(!is_static_downcastable<Derived, const Base&>);
    static_assert(!is_static_downcastable<Derived, Base>);
    static_assert(!is_static_downcastable<Derived, const Base>);
}

constexpr void test_static_downcast()
{
    struct B
    {
    };

    struct D : B
    {
    };

    assert_is_static_downcastable<D, B>();

    struct D2 : private B
    {
    };

    assert_is_static_downcastable<D2, B, false>();

    struct D3 : D, B
    {
    };

    assert_is_static_downcastable<D3, B, false>();

    struct D4 : virtual B
    {
    };

    assert_is_static_downcastable<D4, B, false>();
}

constexpr int test()
{
    test_hash_combine();
    test_static_downcast();
    return 0;
}

} // namespace

int main()
{
    constexpr int ret{test()};
    return ret;
}
