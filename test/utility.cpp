#include <cassert>
#include <cstddef>
#include <experimental/type_traits>
#include <functional>
#include <utility>
#include <jegp/utility.hpp>

namespace {

struct X {
    int v;
};

struct Y {
};

struct Z {
};

} // namespace

namespace std {

template <>
struct hash<X> {
    constexpr std::size_t operator()(X x) const noexcept
    {
        return x.v;
    }
};

template <>
struct hash<Y> {
    std::size_t operator()(Y) const
    {
        return 0;
    }
};

template <>
struct hash<Z> : hash<void> {
};

} // namespace std

namespace {

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

constexpr int test()
{
    test_hash_combine();
    return 0;
}

} // namespace

int main()
{
    constexpr int ret{test()};
    return ret;
}
