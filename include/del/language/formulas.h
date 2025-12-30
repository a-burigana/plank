// MIT License
//
// Copyright (c) 2022 Alessandro Burigana and Francesco Fabiano_
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

#ifndef PLANK_FORMULAS_H
#define PLANK_FORMULAS_H

#include "language_types.h"
#include <cstdint>
#include <deque>
#include <memory>
#include <variant>

namespace del {
    enum class formula_type : uint8_t {
        true_formula,
        false_formula,
        atom_formula,
        not_formula,
        and_formula,
        or_formula,
        imply_formula,
        box_formula,
        diamond_formula,
        kw_box_formula,
        kw_diamond_formula,
        c_box_formula,
        c_diamond_formula
    };

    class true_formula;
    class false_formula;
    class atom_formula;
    class not_formula;
    class and_formula;
    class or_formula;
    class imply_formula;
    class box_formula;
    class diamond_formula;
    class kw_box_formula;
    class kw_diamond_formula;
    class c_box_formula;
    class c_diamond_formula;

    using true_formula_ptr       = std::shared_ptr<true_formula>;
    using false_formula_ptr      = std::shared_ptr<false_formula>;
    using atom_formula_ptr       = std::shared_ptr<atom_formula>;
    using not_formula_ptr        = std::shared_ptr<not_formula>;
    using and_formula_ptr        = std::shared_ptr<and_formula>;
    using or_formula_ptr         = std::shared_ptr<or_formula>;
    using imply_formula_ptr      = std::shared_ptr<imply_formula>;
    using box_formula_ptr        = std::shared_ptr<box_formula>;
    using diamond_formula_ptr    = std::shared_ptr<diamond_formula>;
    using kw_box_formula_ptr     = std::shared_ptr<kw_box_formula>;
    using kw_diamond_formula_ptr = std::shared_ptr<kw_diamond_formula>;
    using c_box_formula_ptr      = std::shared_ptr<c_box_formula>;
    using c_diamond_formula_ptr  = std::shared_ptr<c_diamond_formula>;

    using formula_ptr            = std::variant<true_formula_ptr, false_formula_ptr, atom_formula_ptr, not_formula_ptr,
                                                and_formula_ptr, or_formula_ptr, imply_formula_ptr, box_formula_ptr,
                                                diamond_formula_ptr, kw_box_formula_ptr, kw_diamond_formula_ptr,
                                                c_box_formula_ptr, c_diamond_formula_ptr>;

    using formula_deque          = std::deque<formula_ptr>;

    class true_formula {
    public:
        true_formula();

        true_formula(const true_formula&) = delete;
        true_formula& operator=(const true_formula&) = delete;

        true_formula(true_formula&&) = default;
        true_formula& operator=(true_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return true; }

        bool operator==(const true_formula &rhs) const;
        bool operator!=(const true_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
    };

    class false_formula {
    public:
        false_formula();

        false_formula(const false_formula&) = delete;
        false_formula& operator=(const false_formula&) = delete;

        false_formula(false_formula&&) = default;
        false_formula& operator=(false_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return true; }

        bool operator==(const false_formula &rhs) const;
        bool operator!=(const false_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
    };

    class atom_formula {
    public:
        explicit atom_formula(atom atom);

        atom_formula(const atom_formula&) = delete;
        atom_formula& operator=(const atom_formula&) = delete;

        atom_formula(atom_formula&&) = default;
        atom_formula& operator=(atom_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return true; }

        [[nodiscard]] const atom &get_atom() const { return m_atom; }

        bool operator==(const atom_formula &rhs) const;
        bool operator!=(const atom_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        atom m_atom;
    };

    class not_formula {
    public:
        explicit not_formula(formula_ptr f);

        not_formula(const not_formula&) = delete;
        not_formula& operator=(const not_formula&) = delete;

        not_formula(not_formula&&) = default;
        not_formula& operator=(not_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }

        bool operator==(const not_formula &rhs) const;
        bool operator!=(const not_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_ptr m_f;
    };

    class and_formula {
    public:
        explicit and_formula(formula_deque fs);

        and_formula(const and_formula&) = delete;
        and_formula& operator=(const and_formula&) = delete;

        and_formula(and_formula&&) = default;
        and_formula& operator=(and_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_deque &get_formulas() const { return m_fs; }

        bool operator==(const and_formula &rhs) const;
        bool operator!=(const and_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_deque m_fs;
    };

    class or_formula {
    public:
        explicit or_formula(formula_deque fs);

        or_formula(const or_formula&) = delete;
        or_formula& operator=(const or_formula&) = delete;

        or_formula(or_formula&&) = default;
        or_formula& operator=(or_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_deque &get_formulas() const { return m_fs; }

        bool operator==(const or_formula &rhs) const;
        bool operator!=(const or_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_deque m_fs;
    };

    class imply_formula {
    public:
        imply_formula(formula_ptr f1, formula_ptr f2);

        imply_formula(const imply_formula&) = delete;
        imply_formula& operator=(const imply_formula&) = delete;

        imply_formula(imply_formula&&) = default;
        imply_formula& operator=(imply_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_ptr &get_first_formula() const { return m_f1; }
        [[nodiscard]] const formula_ptr &get_second_formula() const { return m_f2; }

        bool operator==(const imply_formula &rhs) const;
        bool operator!=(const imply_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_ptr m_f1, m_f2;
    };

    class box_formula {
    public:
        box_formula(agent_set ags, formula_ptr f);

        box_formula(const box_formula&) = delete;
        box_formula& operator=(const box_formula&) = delete;

        box_formula(box_formula&&) = default;
        box_formula& operator=(box_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula()  const { return m_f;  }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const box_formula &rhs) const;
        bool operator!=(const box_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
    };

    class diamond_formula {
    public:
        diamond_formula(agent_set ags, formula_ptr f);

        diamond_formula(const diamond_formula&) = delete;
        diamond_formula& operator=(const diamond_formula&) = delete;

        diamond_formula(diamond_formula&&) = default;
        diamond_formula& operator=(diamond_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula()  const { return m_f;  }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const diamond_formula &rhs) const;
        bool operator!=(const diamond_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
    };

    class kw_box_formula {
    public:
        kw_box_formula(agent_set ags, formula_ptr f);

        kw_box_formula(const kw_box_formula&) = delete;
        kw_box_formula& operator=(const kw_box_formula&) = delete;

        kw_box_formula(kw_box_formula&&) = default;
        kw_box_formula& operator=(kw_box_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula()  const { return m_f;  }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const kw_box_formula &rhs) const;
        bool operator!=(const kw_box_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
    };

    class kw_diamond_formula {
    public:
        kw_diamond_formula(agent_set ags, formula_ptr f);

        kw_diamond_formula(const kw_diamond_formula&) = delete;
        kw_diamond_formula& operator=(const kw_diamond_formula&) = delete;

        kw_diamond_formula(kw_diamond_formula&&) = default;
        kw_diamond_formula& operator=(kw_diamond_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula()  const { return m_f;  }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const kw_diamond_formula &rhs) const;
        bool operator!=(const kw_diamond_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
    };

    class c_box_formula {
    public:
        c_box_formula(agent_set ags, formula_ptr f);

        c_box_formula(const c_box_formula&) = delete;
        c_box_formula& operator=(const c_box_formula&) = delete;

        c_box_formula(c_box_formula&&) = default;
        c_box_formula& operator=(c_box_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula()  const { return m_f;  }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const c_box_formula &rhs) const;
        bool operator!=(const c_box_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
    };

    class c_diamond_formula {
    public:
        c_diamond_formula(agent_set ags, formula_ptr f);

        c_diamond_formula(const c_diamond_formula&) = delete;
        c_diamond_formula& operator=(const c_diamond_formula&) = delete;

        c_diamond_formula(c_diamond_formula&&) = default;
        c_diamond_formula& operator=(c_diamond_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula()  const { return m_f;  }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const c_diamond_formula &rhs) const;
        bool operator!=(const c_diamond_formula &rhs) const;

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
    };

    class formulas_utils {
    public:
        [[nodiscard]] static unsigned long get_modal_depth(const formula_ptr &f);
        [[nodiscard]] static unsigned long get_size(const formula_ptr &f);
        [[nodiscard]] static formula_type get_type(const formula_ptr &f);

        [[nodiscard]] static bool are_equal(const formula_ptr &f1, const formula_ptr &f2);
        [[nodiscard]] static bool are_equal(const formula_deque &fs1, const formula_deque &fs2);
        [[nodiscard]] static bool covers(const formula_deque &fs1, const formula_deque &fs2);
    };
}

#endif //PLANK_FORMULAS_H
