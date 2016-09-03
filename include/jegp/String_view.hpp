#ifndef JEGP_STRING_VIEW_HPP
#define JEGP_STRING_VIEW_HPP

#include <iterator>
#include <experimental/string_view>

namespace jegp {

class String_view : public std::experimental::string_view {
    using Base = std::experimental::string_view;

    constexpr String_view(Base) noexcept;
public:
    constexpr String_view() noexcept = default;
    constexpr String_view(char* str);
    constexpr String_view(char* str, size_type len);

    using iterator = pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;

    using Base::begin;
    using Base::end;
    constexpr iterator begin() noexcept;
    constexpr iterator end() noexcept;

    using Base::rbegin;
    using Base::rend;
    /*constexpr*/ reverse_iterator rbegin() noexcept;
    /*constexpr*/ reverse_iterator rend() noexcept;

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

} // jegp namespace

//------------------------------------------------------------------------------
// "String_view.ipp" -----------------------------------------------------------
//------------------------------------------------------------------------------

namespace jegp {

constexpr String_view::String_view(Base b) noexcept
  : std::experimental::string_view{b}
{
}

// Construction ----------------------------------------------------------------

constexpr String_view::String_view(char* str)
  : std::experimental::string_view{str}
{
}
constexpr String_view::String_view(char* str, size_type len)
  : std::experimental::string_view{str,len}
{
}

// Iterator support ------------------------------------------------------------

constexpr auto String_view::begin() noexcept -> iterator
{
    return data();
}
constexpr auto String_view::end() noexcept -> iterator
{
    return begin() + size();
}

inline /*constexpr*/ auto String_view::rbegin() noexcept -> reverse_iterator
{
    return reverse_iterator{end()};
}
inline /*constexpr*/ auto String_view::rend() noexcept -> reverse_iterator
{
    return reverse_iterator{begin()};
}

// Element access --------------------------------------------------------------

constexpr auto String_view::operator[](size_type pos) -> reference
{
    return const_cast<reference>(Base::operator[](pos));
}
constexpr auto String_view::at(size_type pos) -> reference
{
    return const_cast<reference>(Base::at(pos));
}

constexpr auto String_view::front() -> reference
{
    return const_cast<reference>(Base::front());
}
constexpr auto String_view::back() -> reference
{
    return const_cast<reference>(Base::back());
}

constexpr auto String_view::data() noexcept -> pointer
{
    return const_cast<pointer>(Base::data());
}

// String operations -----------------------------------------------------------

constexpr String_view String_view::substr(size_type pos, size_type n) const
{
    return Base::substr(pos,n);
}

} // jegp namespace

#endif // JEGP_STRING_VIEW_HPP
