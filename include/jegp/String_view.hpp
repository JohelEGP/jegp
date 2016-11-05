#ifndef JEGP_STRING_VIEW_HPP
#define JEGP_STRING_VIEW_HPP

#include <string>   // char_traits
#include <iterator> // reverse_iterator
#include <string_view>

namespace jegp {

template <class charT, class traits = std::char_traits<charT>>
class Basic_string_view : public std::basic_string_view<charT,traits> {
private:
    using Base = std::basic_string_view<charT,traits>;

    constexpr Basic_string_view(Base) noexcept;
public:
    using typename Base::pointer;
    using typename Base::reference;
    using iterator = pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using typename Base::size_type;

    constexpr Basic_string_view() noexcept = default;
    constexpr Basic_string_view(charT* str);
    constexpr Basic_string_view(charT* str, size_type len);

    using Base::begin;
    using Base::end;
    constexpr iterator begin() noexcept;
    constexpr iterator end() noexcept;

    using Base::rbegin;
    using Base::rend;
    constexpr reverse_iterator rbegin() noexcept;
    constexpr reverse_iterator rend() noexcept;

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

    constexpr Basic_string_view substr(
        size_type pos = 0, size_type n = Base::npos) const;
};

using    String_view = Basic_string_view<char>;
using u16String_view = Basic_string_view<char16_t>;
using u32String_view = Basic_string_view<char32_t>;
using   wString_view = Basic_string_view<wchar_t>;

} // jegp namespace

//------------------------------------------------------------------------------
// "String_view.ipp" -----------------------------------------------------------
//------------------------------------------------------------------------------

namespace jegp {

template <class C, class T>
constexpr Basic_string_view<C,T>::Basic_string_view(Base b) noexcept
  : Base{b}
{
}

// Construction ----------------------------------------------------------------

template <class charT, class T>
constexpr Basic_string_view<charT,T>::Basic_string_view(charT* str)
  : Base{str}
{
}
template <class charT, class T>
constexpr Basic_string_view<charT,T>::Basic_string_view(
    charT* str, size_type len)
  : Base{str,len}
{
}

// Iterator support ------------------------------------------------------------

template <class C, class T>
constexpr auto Basic_string_view<C,T>::begin() noexcept -> iterator
{
    return data();
}
template <class C, class T>
constexpr auto Basic_string_view<C,T>::end() noexcept -> iterator
{
    return begin() + Base::size();
}

template <class C, class T>
constexpr auto Basic_string_view<C,T>::rbegin() noexcept -> reverse_iterator
{
    return reverse_iterator{end()};
}
template <class C, class T>
constexpr auto Basic_string_view<C,T>::rend() noexcept -> reverse_iterator
{
    return reverse_iterator{begin()};
}

// Element access --------------------------------------------------------------

template <class C, class T>
constexpr auto Basic_string_view<C,T>::operator[](size_type pos) -> reference
{
    return const_cast<reference>(Base::operator[](pos));
}
template <class C, class T>
constexpr auto Basic_string_view<C,T>::at(size_type pos) -> reference
{
    return const_cast<reference>(Base::at(pos));
}

template <class C, class T>
constexpr auto Basic_string_view<C,T>::front() -> reference
{
    return const_cast<reference>(Base::front());
}
template <class C, class T>
constexpr auto Basic_string_view<C,T>::back() -> reference
{
    return const_cast<reference>(Base::back());
}

template <class C, class T>
constexpr auto Basic_string_view<C,T>::data() noexcept -> pointer
{
    return const_cast<pointer>(Base::data());
}

// String operations -----------------------------------------------------------

template <class C, class T>
constexpr auto Basic_string_view<C,T>::substr(size_type pos, size_type n) const
    -> Basic_string_view
{
    return Base::substr(pos,n);
}

} // jegp namespace

#endif // JEGP_STRING_VIEW_HPP
