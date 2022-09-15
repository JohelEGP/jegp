#include <cassert>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>
#include <jegp/utility.hpp>

// [hash.combine]

struct X {
    int v;
};
struct Y { };
struct Z { };

template <> struct std::hash<X> {
    constexpr std::size_t operator()(X x) const noexcept { return x.v; }
};
template <> struct std::hash<Y> {
    std::size_t operator()(Y) const { return 0; }
};
template <> struct std::hash<Z> : std::hash<void> { };

template <class... Args> constexpr bool is_hash_combinable = requires { jegp::hash_combine(std::declval<Args>()...); };

constexpr void test_hash_combine() {
    static_assert(not is_hash_combinable<>);
    static_assert(not is_hash_combinable<int>);
    static_assert(not is_hash_combinable<X>);
    static_assert(not is_hash_combinable<Y>);
    static_assert(not is_hash_combinable<Z>);
    static_assert(is_hash_combinable<int, int>);
    static_assert(is_hash_combinable<int, X>);
    static_assert(is_hash_combinable<X, int>);
    static_assert(is_hash_combinable<X, X>);
    static_assert(is_hash_combinable<int, Y>);
    static_assert(is_hash_combinable<Y, int>);
    static_assert(is_hash_combinable<Y, Y>);
    static_assert(not is_hash_combinable<int, Z>);
    static_assert(not is_hash_combinable<Z, int>);
    static_assert(not is_hash_combinable<Z, Z>);

    static_assert(noexcept(jegp::hash_combine(0, 0)));
    static_assert(noexcept(jegp::hash_combine(0, X{})));
    static_assert(noexcept(jegp::hash_combine(X{}, 0)));
    static_assert(noexcept(jegp::hash_combine(X{}, X{})));
    static_assert(not noexcept(jegp::hash_combine(0, Y{})));
    static_assert(not noexcept(jegp::hash_combine(Y{}, 0)));
    static_assert(not noexcept(jegp::hash_combine(Y{}, Y{})));

    const X x[]{17, 20, -23};

    std::size_t seed{0};

    seed ^= x[0].v;
    seed ^= x[1].v + (seed << 6) + (seed >> 2);

    assert(seed == jegp::hash_combine(x[0], x[1]));

    seed ^= x[2].v + (seed << 6) + (seed >> 2);

    assert(seed == jegp::hash_combine(x[0], x[1], x[2]));
}

// [static.downcast]

template <class DerivedRef, class Base> constexpr bool is_static_downcastable = requires {
    jegp::static_downcast<DerivedRef>(std::declval<Base>());
};

template <class Derived, class Base, bool ExpectedToPass = true>
    requires(
        std::is_same_v<Derived, std::remove_cvref_t<Derived>>and std::is_same_v<Base, std::remove_cvref_t<Base>> and
        not std::is_same_v<Derived, Base> and std::is_base_of_v<Base, Derived>)
constexpr void assert_is_static_downcastable() {
    auto ok = [](bool b) { return b == ExpectedToPass; };

    static_assert(ok(is_static_downcastable<Derived&, Base&>));
    static_assert(ok(is_static_downcastable<const Derived&, Base&>));
    static_assert(ok(is_static_downcastable<Derived&&, Base&>));
    static_assert(ok(is_static_downcastable<const Derived&&, Base&>));

    static_assert(not is_static_downcastable<Derived&, const Base&>);
    static_assert(ok(is_static_downcastable<const Derived&, const Base&>));
    static_assert(not is_static_downcastable<Derived&&, const Base&>);
    static_assert(ok(is_static_downcastable<const Derived&&, const Base&>));

    static_assert(not is_static_downcastable<Derived&, Base>);
    static_assert(not is_static_downcastable<const Derived&, Base>);
    static_assert(ok(is_static_downcastable<Derived&&, Base>));
    static_assert(ok(is_static_downcastable<const Derived&&, Base>));

    static_assert(not is_static_downcastable<Derived&, const Base>);
    static_assert(not is_static_downcastable<const Derived&, const Base>);
    static_assert(not is_static_downcastable<Derived&&, const Base>);
    static_assert(ok(is_static_downcastable<const Derived&&, const Base>));

    static_assert(not is_static_downcastable<Derived, Base&>);
    static_assert(not is_static_downcastable<Derived, const Base&>);
    static_assert(not is_static_downcastable<Derived, Base>);
    static_assert(not is_static_downcastable<Derived, const Base>);
}

constexpr void test_static_downcast() {
    struct B { };
    struct D : B { };
    struct D2 : private B { };
    struct D3 : D, B { };
    struct D4 : virtual B { };
    assert_is_static_downcastable<D, B>();
    assert_is_static_downcastable<D2, B, false>();
    assert_is_static_downcastable<D3, B, false>();
    assert_is_static_downcastable<D4, B, false>();
}

consteval void test() {
    test_hash_combine();
    test_static_downcast();
}

int main() { test(); } ////
