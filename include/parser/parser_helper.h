#ifndef EPDDL_PARSER_HELPER_H
#define EPDDL_PARSER_HELPER_H

#include "../lexer/lexer.h"
#include "../../include/utils/traits.h"
#include "../ast/main_decl_ast.h"
#include <deque>
#include <list>
#include <memory>
#include <optional>
#include <stack>

namespace epddl {
    template<typename node_type>
    using choice = std::pair<token_type, const std::function<node_type()>>;

    class parser_helper {
    public:
        explicit parser_helper(const std::string &path);
//        parser_helper() = default;

        ast::main_decl parse();

        [[nodiscard]] const token_ptr &get_current_token() const;
//        const token_ptr &get_next_token() const;

        template<typename required_tok_type>
        void check_next_token(bool discard = true) {
            if (not m_is_choice_point) {
                read_next_token();
                check_current_token<required_tok_type>(discard);
            } else {
                peek_next_token();
                check_currently_peeked_token<required_tok_type>();
            }
        }

        void read_next_token();
        const token_ptr &peek_next_token();

        token_ptr get_leaf_from_current_token() {
            token_ptr leaf = std::move(*m_current_token);       // std::move(parser_utils::unwrap_variant_type<token_variant, token<token_type>>(**m_current_token));

            m_current_token->reset();
            m_current_token = std::nullopt;

            return leaf;
        }

        template<typename required_tok_type>
        token_ptr get_leaf_from_next_token(bool is_optional = false) {
            token_ptr leaf;
            bool consume_token = true;

            if (m_is_choice_point or is_optional) {
                if (not m_next_token.has_value())
//                if (m_buffer.empty())
                    peek_next_token();

                if (get_last_peeked_token()->has_type<required_tok_type>())  // If the last token we scanned has the correct
                    read_next_token();                                  // type, then we move it to the current token
                else
                    consume_token = false;
            } else {
                check_next_token<required_tok_type>(false);
            }

            if (consume_token)
                return get_leaf_from_current_token();

            throw_error(get_last_peeked_token());
            return {};
        }

        template<class node_type, typename... delimiter_tok_types> //  = punctuation_token::rpar
        std::list<node_type> parse_list(const std::function<node_type()> &parse_elem, bool is_optional_list = false) {
            std::list<node_type> elems;
            bool is_empty_list = true;
            peek_next_token();

            while (not get_last_peeked_token()->has_either_type<punctuation_token::rpar, delimiter_tok_types...>()) {
                // If we do not peek the list delimiter, we parse the element and, if we are successful, we add it to the list.
                // We assume that parse_elem() takes care of its relative syntax errors.
                elems.push_back(std::move(parse_elem()));
                is_empty_list = false;
                peek_next_token();
            }

            if (not is_optional_list and is_empty_list)
                throw_error(get_last_peeked_token(), std::string{""}, std::string{"Empty list."});
            // todo: create better error description
            return elems;
        }

        template<class node_type, typename... first_tok_types>
        std::optional<node_type> parse_optional(const std::function<node_type()> &parse_elem) {
            const token_ptr &tok = peek_next_token();
            std::optional<node_type> elem = std::nullopt;

            if (tok->has_either_type<first_tok_types...>()) elem.emplace(parse_elem());
            return elem;
        }

//        template<class node_type>
//        node_type parse_node(const std::function<node_type()> &parse_elem) {
//            if (m_is_choice_point) exit_choice_point();
//            return parse_elem();
//        }

        /*template<typename node_type, typename required_tok_type>
        auto get_choice_parser(const token_ptr &tok, const std::function<node_type()> &parse_elem) {
            return [&] () {
                std::unique_ptr<node_type> elem_ptr;

                if (tok->get_type().index() == required_tok->get_type().index()) {
                    exit_choice_point();
                    elem_ptr = std::make_unique<std::move(parse_elem())>;
                }
                return elem_ptr;
            };
        }


        template<typename node_type>
        std::unique_ptr<node_type> parse_choice(const token_ptr &tok, const choice<node_type> &choice) {
            const auto &[required_tok, parse_elem] = choice;
            std::unique_ptr<node_type> elem_ptr;

            if (tok->get_type().index() == required_tok->get_type().index()) {
                exit_choice_point();
                elem_ptr = std::make_unique<std::move(parse_elem())>;
            }
            return elem_ptr;
        }

        template<typename node_type>
        std::unique_ptr<node_type> parse_choice_point(const std::function<void()> &parse_common_prefix,
                                                      const std::deque<choice<node_type>> &choices,
                                                      const std::function<void()> &parse_common_suffix) {
            parse_common_prefix();

            node_type elem;
            bool stop = false;

            enter_choice_point();
            unsigned long current_choice_point = m_choice_point_count;

            const token_ptr &tok = peek_next_token();
            auto it = choices.cbegin();

            while (not stop) {
                auto elem_ptr = parse_choice(tok, *it++);   // Important assumption: each alternative in a choice point
                if (elem_ptr) stop = true;                  // must be uniquely identifiable by its first token!!!
                else if (it == choices.cend()) {
                    // todo: handle error
                }
            }
            parse_common_suffix();
            return std::make_unique<node_type>(std::move(elem));
        }*/

    private:
        lexer m_lex;
        std::optional<token_ptr> m_current_token, m_next_token;
//        std::deque<token_ptr> m_buffer;
//        unsigned int m_buffer_cursor;
        bool m_is_choice_point, m_is_optional_node;
        std::function<void()> m_open_par, m_close_par;

        std::stack<std::pair<unsigned long, const token_ptr*>> m_scopes;
        unsigned long m_choice_point_count, m_lpar_count;

        unsigned long enter_choice_point();
        unsigned long exit_choice_point();
        [[nodiscard]] bool is_inside_choice_point(unsigned long current_choice_point) const;
//        void reset_choice_point();

        void enter_optional_node();
        void exit_optional_node();

        void throw_error(const token_ptr& token, const std::string& file = "", const std::string& error = "") const;
        template<typename required_tok_type>
        void throw_token_error(const token_ptr& token) {
            if (not token->has_type<required_tok_type>()) {
                // We only check for identifiers, punctuation and valid keywords
                // todo: check behaviour for all token types
                #define epddl_token_type(token_type) token_type
                std::string required_tok_type_str = std::is_same_v<get_super_t<required_tok_type>, epddl_pattern_token_type>
                        ? std::string{required_tok_type::name}
                        : std::string{required_tok_type::lexeme};
//                = std::visit([](auto &&tok_var_type) {
//                    using tok_type = typename std::remove_reference<decltype(tok_var_type)>::type;
//                    return std::is_same_v<epddl_pattern_token_type, get_super_t<tok_type>>
//                    ? std::string{tok_type::name}
//                    : std::string{tok_type::lexeme};
//                }, token->get_type());
                #undef epddl_token_type

                throw_error(token, std::string{""}, std::string{"Expected '"} + required_tok_type_str +
                                                    std::string{"'. Found '"} + token->get_lexeme() + std::string{"'."});
            }
        }

//        bool is_end_list();
//        void peek_next_token();
        void reset_next_token();
//        token_ptr& get_last_peeked_token(bool move_next = true);

        void read_from_buffer();
        [[nodiscard]] const token_ptr& get_last_peeked_token() const;

        template<typename required_tok_type>
        void check_token(const token_ptr &tok) {
            if (not tok->has_type<required_tok_type>())
                throw_token_error<required_tok_type>(*m_current_token);
        }

        template<typename required_tok_type>
        void check_current_token(bool discard = true) {
            check_token<required_tok_type>(*m_current_token);

            // After successfully verifying that the current token has the correct type, we can delete it
            if (discard) {
                m_current_token->reset();
                m_current_token = std::nullopt;
            }
        }

        template<typename required_tok_type>
        void check_currently_peeked_token() {
            check_token<required_tok_type>(get_last_peeked_token());
        }

        void update_scopes(const token_ptr& token);
    };
}

#endif //EPDDL_PARSER_HELPER_H
