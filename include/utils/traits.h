#ifndef EPDDL_TRAITS_H
#define EPDDL_TRAITS_H

#include <type_traits>

namespace epddl {
    template<typename TokenType>
    using get_super_t = typename TokenType::super_type;

    /*
     * Trait for 'extracting' the argument of a unary template class
     * This is used to get the type of a token while parsing
     */
    template<class T>
    struct get_argument;

    template <template<typename> class Container, typename Argument>
    struct get_argument<Container<Argument>> {
        using type = Argument;
    };

    template <template<typename> class Container, typename Argument>
    struct get_argument<Container<Argument>&> {
        using type = Argument;
    };

    template <class T>
    using get_argument_t = typename get_argument<T>::type;
}

#endif //EPDDL_TRAITS_H
