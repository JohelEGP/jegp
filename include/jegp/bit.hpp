#ifndef JEGP_BIT_HPP
#define JEGP_BIT_HPP

#include <climits>

namespace jegp {

template <class T>
constexpr auto bitsof{sizeof(T) * CHAR_BIT};

} // namespace jegp

#endif // JEGP_BIT_HPP
