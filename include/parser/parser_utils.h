#ifndef EPDDL_PARSER_UTILS_H
#define EPDDL_PARSER_UTILS_H

#include <memory>
#include <variant>

namespace epddl {
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
