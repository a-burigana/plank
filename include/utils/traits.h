// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
