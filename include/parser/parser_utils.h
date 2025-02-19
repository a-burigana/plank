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

#ifndef EPDDL_PARSER_UTILS_H
#define EPDDL_PARSER_UTILS_H

#include <memory>
#include <variant>

namespace epddl::parser {
    class parser_utils {
    public:
        template<class variant_type, class element_type>
        static std::unique_ptr<element_type> unwrap_variant_type(variant_type& elem) {
            std::unique_ptr<element_type> unwrapped_elem;       // Here we store the value of 'elem' after we unwrap it from its variant type

            std::visit([&unwrapped_elem](auto &&e) {
                using e_type = std::decay_t<decltype(e)>;

                if constexpr (std::is_same_v<element_type, e_type>) {
                    unwrapped_elem = std::move(std::make_unique<e_type>(std::forward<e_type>(e)));      // Unwrapping variant
                }
            }, elem);
            return unwrapped_elem;
        }

        template<class variant_from, class variant_to, class element_type>
        static std::unique_ptr<variant_to> convert_variant_type(variant_from& elem) {
            std::unique_ptr<element_type> unwrapped_elem = unwrap_variant_type<variant_from, element_type>(elem);
            return std::make_unique<variant_to>(std::move(unwrapped_elem));     // Wrapping back with 'variant_to' variant type
        }
    };
}

#endif //EPDDL_PARSER_UTILS_H
