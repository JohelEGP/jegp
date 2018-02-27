#ifndef JEGP_STRONG_TYPEDEF_HPP
#define JEGP_STRONG_TYPEDEF_HPP

#include <type_safe/strong_typedef.hpp>

namespace jegp {

template <class T, class Phantom>
class[[deprecated]] Strong_typedef
  : public type_safe::strong_typedef<Phantom, T>
  , public type_safe::strong_typedef_op::equality_comparison<
        Strong_typedef<T, Phantom>>
  , public type_safe::strong_typedef_op::relational_comparison<
        Strong_typedef<T, Phantom>>
{
public:
    using type_safe::strong_typedef<Phantom, T>::strong_typedef;
};

} // namespace jegp

#endif // JEGP_STRONG_TYPEDEF_HPP
