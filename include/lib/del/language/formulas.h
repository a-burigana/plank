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

#include <algorithm>
#include <cstdint>
#include <deque>
#include <memory>
#include <variant>
#include "language_types.h"
#include "utils/storage.h"

using namespace plank::utils;

namespace plank::del {
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

    using formula                = std::variant<true_formula, false_formula, atom_formula, not_formula,
                                                and_formula, or_formula, imply_formula, box_formula,
                                                diamond_formula, kw_box_formula, kw_diamond_formula,
                                                c_box_formula, c_diamond_formula>;

    using formula_ptr            = std::shared_ptr<formula>;
    using formula_deque          = std::deque<formula_ptr>;

    using formula_id             = unsigned long long;
    using formula_id_deque       = std::deque<formula_id>;

    using formula_storage        = storage<formula>;
    using formula_storage_ptr    = std::shared_ptr<formula_storage>;

    /*struct formula_storages_handler {
        storage<true_formula>       true_formula_storage;
        storage<false_formula>      false_formula_storage;
        storage<atom_formula>       atom_formula_storage;
        storage<not_formula>        not_formula_storage;
        storage<and_formula>        and_formula_storage;
        storage<or_formula>         or_formula_storage;
        storage<imply_formula>      imply_formula_storage;
        storage<box_formula>        box_formula_storage;
        storage<diamond_formula>    diamond_formula_storage;
        storage<kw_box_formula>     kw_box_formula_storage;
        storage<kw_diamond_formula> kw_diamond_formula_storage;
        storage<c_box_formula>      c_box_formula_storage;
        storage<c_diamond_formula>  c_diamond_formula_storage;
    };

    using formula_storages_handler_ptr = std::shared_ptr<formula_storages_handler>;*/

    class true_formula {
    public:
        true_formula();

        true_formula(const true_formula&) = default;
        true_formula& operator=(const true_formula&) = default;

        true_formula(true_formula&&) = default;
        true_formula& operator=(true_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return true; }

        bool operator==(const true_formula &rhs) const { return true;  }
        bool operator!=(const true_formula &rhs) const { return false; }

        friend bool operator< (const true_formula &lhs, const true_formula &rhs) { return false; }
        friend bool operator<=(const true_formula &lhs, const true_formula &rhs) { return true;  }
        friend bool operator> (const true_formula &lhs, const true_formula &rhs) { return false; }
        friend bool operator>=(const true_formula &lhs, const true_formula &rhs) { return true;  }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
    };

    class false_formula {
    public:
        false_formula();

        false_formula(const false_formula&) = default;
        false_formula& operator=(const false_formula&) = default;

        false_formula(false_formula&&) = default;
        false_formula& operator=(false_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return true; }

        bool operator==(const false_formula &rhs) const { return true;  }
        bool operator!=(const false_formula &rhs) const { return false; }

        friend bool operator< (const false_formula &lhs, const false_formula &rhs) { return false; }
        friend bool operator<=(const false_formula &lhs, const false_formula &rhs) { return true;  }
        friend bool operator> (const false_formula &lhs, const false_formula &rhs) { return false; }
        friend bool operator>=(const false_formula &lhs, const false_formula &rhs) { return true;  }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
    };

    class atom_formula {
    public:
        explicit atom_formula(atom atom);

        atom_formula(const atom_formula&) = default;
        atom_formula& operator=(const atom_formula&) = default;

        atom_formula(atom_formula&&) = default;
        atom_formula& operator=(atom_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return true; }

        [[nodiscard]] const atom &get_atom() const { return m_atom; }

        bool operator==(const atom_formula &rhs) const { return m_atom == rhs.m_atom; }
        bool operator!=(const atom_formula &rhs) const { return not (*this == rhs); }

        friend bool operator< (const atom_formula &lhs, const atom_formula &rhs) { return lhs.m_atom < rhs.m_atom; }
        friend bool operator<=(const atom_formula &lhs, const atom_formula &rhs) { return not (rhs < lhs); }
        friend bool operator> (const atom_formula &lhs, const atom_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const atom_formula &lhs, const atom_formula &rhs) { return not (lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        atom m_atom;
    };

    class not_formula {
    public:
        explicit not_formula(formula_id f_id, const formula_storage_ptr &storage);

        not_formula(const not_formula&) = default;
        not_formula& operator=(const not_formula&) = default;

        not_formula(not_formula&&) = default;
        not_formula& operator=(not_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }
        [[nodiscard]] formula_id get_formula_id() const { return m_f_id; }

        bool operator==(const not_formula &rhs) const { return m_f_id == rhs.m_f_id; }
        bool operator!=(const not_formula &rhs) const { return not (*this == rhs); }

        friend bool operator< (const not_formula &lhs, const not_formula &rhs) { return lhs.m_f_id < rhs.m_f_id; }
        friend bool operator<=(const not_formula &lhs, const not_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const not_formula &lhs, const not_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const not_formula &lhs, const not_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_ptr m_f;
        formula_id m_f_id;
    };

    class and_formula {
    public:
        explicit and_formula(formula_id_deque fs_ids, const formula_storage_ptr &storage);

        and_formula(const and_formula&) = default;
        and_formula& operator=(const and_formula&) = default;

        and_formula(and_formula&&) = default;
        and_formula& operator=(and_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_deque &get_formulas() const { return m_fs; }
        [[nodiscard]] const formula_id_deque &get_formulas_ids() const { return m_fs_ids; }

        bool operator==(const and_formula &rhs) const {
            return
                std::includes(m_fs_ids.begin(), m_fs_ids.end(), rhs.m_fs_ids.begin(), rhs.m_fs_ids.end()) and
                std::includes(rhs.m_fs_ids.begin(), rhs.m_fs_ids.end(), m_fs_ids.begin(), m_fs_ids.end());
        }

        bool operator!=(const and_formula &rhs) const { return not (*this == rhs); }

        friend bool operator< (const and_formula &lhs, const and_formula &rhs) { return lhs.m_fs_ids < rhs.m_fs_ids; }
        friend bool operator<=(const and_formula &lhs, const and_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const and_formula &lhs, const and_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const and_formula &lhs, const and_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_deque m_fs;
        formula_id_deque m_fs_ids;
    };

    class or_formula {
    public:
        explicit or_formula(formula_id_deque fs_ids, const formula_storage_ptr &storage);

        or_formula(const or_formula&) = default;
        or_formula& operator=(const or_formula&) = default;

        or_formula(or_formula&&) = default;
        or_formula& operator=(or_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_deque &get_formulas() const { return m_fs; }
        [[nodiscard]] const formula_id_deque &get_formulas_ids() const { return m_fs_ids; }

        bool operator==(const or_formula &rhs) const {
            return
                std::includes(m_fs_ids.begin(), m_fs_ids.end(), rhs.m_fs_ids.begin(), rhs.m_fs_ids.end()) and
                std::includes(rhs.m_fs_ids.begin(), rhs.m_fs_ids.end(), m_fs_ids.begin(), m_fs_ids.end());
        }

        bool operator!=(const or_formula &rhs) const { return not (*this == rhs); }

        friend bool operator< (const or_formula &lhs, const or_formula &rhs) { return lhs.m_fs_ids < rhs.m_fs_ids; }
        friend bool operator<=(const or_formula &lhs, const or_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const or_formula &lhs, const or_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const or_formula &lhs, const or_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_deque m_fs;
        formula_id_deque m_fs_ids;
    };

    class imply_formula {
    public:
        imply_formula(formula_id f1_id, formula_id f2_id, const formula_storage_ptr &storage);

        imply_formula(const imply_formula&) = default;
        imply_formula& operator=(const imply_formula&) = default;

        imply_formula(imply_formula&&) = default;
        imply_formula& operator=(imply_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] bool is_propositional() const { return m_modal_depth == 0; }

        [[nodiscard]] const formula_ptr &get_first_formula() const { return m_f1; }
        [[nodiscard]] const formula_ptr &get_second_formula() const { return m_f2; }
        [[nodiscard]] formula_id get_first_formula_id() const { return m_f1_id; }
        [[nodiscard]] formula_id get_second_formula_id() const { return m_f2_id; }

        bool operator==(const imply_formula &rhs) const { return m_f1_id == rhs.m_f1_id and m_f2_id == rhs.m_f2_id; }
        bool operator!=(const imply_formula &rhs) const { return not (*this == rhs); }

        friend bool operator<(const imply_formula &lhs, const imply_formula &rhs) {
            if (lhs.m_f1_id < rhs.m_f1_id) return true;
            if (rhs.m_f1_id < lhs.m_f1_id) return false;

            return lhs.m_f2_id < rhs.m_f2_id;
        }

        friend bool operator<=(const imply_formula &lhs, const imply_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const imply_formula &lhs, const imply_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const imply_formula &lhs, const imply_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        formula_ptr m_f1, m_f2;
        formula_id m_f1_id, m_f2_id;
    };

    class box_formula {
    public:
        box_formula(agent_set ags, formula_id f_id, const formula_storage_ptr &storage);

        box_formula(const box_formula&) = default;
        box_formula& operator=(const box_formula&) = default;

        box_formula(box_formula&&) = default;
        box_formula& operator=(box_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }
        [[nodiscard]] formula_id get_formula_id() const { return m_f_id; }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const box_formula &rhs) const { return m_ags == rhs.m_ags and m_f_id == rhs.m_f_id; }
        bool operator!=(const box_formula &rhs) const { return not (*this == rhs); }

        friend bool operator<(const box_formula &lhs, const box_formula &rhs) {
            if (lhs.m_ags < rhs.m_ags) return true;
            if (rhs.m_ags < lhs.m_ags) return false;

            return lhs.m_f_id < rhs.m_f_id;
        }

        friend bool operator<=(const box_formula &lhs, const box_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const box_formula &lhs, const box_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const box_formula &lhs, const box_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
        formula_id m_f_id;
    };

    class diamond_formula {
    public:
        diamond_formula(agent_set ags, formula_id f_id, const formula_storage_ptr &storage);

        diamond_formula(const diamond_formula&) = default;
        diamond_formula& operator=(const diamond_formula&) = default;

        diamond_formula(diamond_formula&&) = default;
        diamond_formula& operator=(diamond_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }
        [[nodiscard]] formula_id get_formula_id() const { return m_f_id; }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const diamond_formula &rhs) const { return m_ags == rhs.m_ags and m_f_id == rhs.m_f_id; }
        bool operator!=(const diamond_formula &rhs) const { return not (*this == rhs); }

        friend bool operator<(const diamond_formula &lhs, const diamond_formula &rhs) {
            if (lhs.m_ags < rhs.m_ags) return true;
            if (rhs.m_ags < lhs.m_ags) return false;

            return lhs.m_f_id < rhs.m_f_id;
        }

        friend bool operator<=(const diamond_formula &lhs, const diamond_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const diamond_formula &lhs, const diamond_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const diamond_formula &lhs, const diamond_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
        formula_id m_f_id;
    };

    class kw_box_formula {
    public:
        kw_box_formula(agent_set ags, formula_id f_id, const formula_storage_ptr &storage);

        kw_box_formula(const kw_box_formula&) = default;
        kw_box_formula& operator=(const kw_box_formula&) = default;

        kw_box_formula(kw_box_formula&&) = default;
        kw_box_formula& operator=(kw_box_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }
        [[nodiscard]] formula_id get_formula_id() const { return m_f_id; }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const kw_box_formula &rhs) const { return m_ags == rhs.m_ags and m_f_id == rhs.m_f_id; }
        bool operator!=(const kw_box_formula &rhs) const { return not (*this == rhs); }

        friend bool operator<(const kw_box_formula &lhs, const kw_box_formula &rhs) {
            if (lhs.m_ags < rhs.m_ags) return true;
            if (rhs.m_ags < lhs.m_ags) return false;

            return lhs.m_f_id < rhs.m_f_id;
        }

        friend bool operator<=(const kw_box_formula &lhs, const kw_box_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const kw_box_formula &lhs, const kw_box_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const kw_box_formula &lhs, const kw_box_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
        formula_id m_f_id;
    };

    class kw_diamond_formula {
    public:
        kw_diamond_formula(agent_set ags, formula_id f_id, const formula_storage_ptr &storage);

        kw_diamond_formula(const kw_diamond_formula&) = default;
        kw_diamond_formula& operator=(const kw_diamond_formula&) = default;

        kw_diamond_formula(kw_diamond_formula&&) = default;
        kw_diamond_formula& operator=(kw_diamond_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }
        [[nodiscard]] formula_id get_formula_id() const { return m_f_id; }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const kw_diamond_formula &rhs) const { return m_ags == rhs.m_ags and m_f_id == rhs.m_f_id; }
        bool operator!=(const kw_diamond_formula &rhs) const { return not (*this == rhs); }

        friend bool operator<(const kw_diamond_formula &lhs, const kw_diamond_formula &rhs) {
            if (lhs.m_ags < rhs.m_ags) return true;
            if (rhs.m_ags < lhs.m_ags) return false;

            return lhs.m_f_id < rhs.m_f_id;
        }

        friend bool operator<=(const kw_diamond_formula &lhs, const kw_diamond_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const kw_diamond_formula &lhs, const kw_diamond_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const kw_diamond_formula &lhs, const kw_diamond_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
        formula_id m_f_id;
    };

    class c_box_formula {
    public:
        c_box_formula(agent_set ags, formula_id f_id, const formula_storage_ptr &storage);

        c_box_formula(const c_box_formula&) = default;
        c_box_formula& operator=(const c_box_formula&) = default;

        c_box_formula(c_box_formula&&) = default;
        c_box_formula& operator=(c_box_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }
        [[nodiscard]] formula_id get_formula_id() const { return m_f_id; }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const c_box_formula &rhs) const { return m_ags == rhs.m_ags and m_f_id == rhs.m_f_id; }
        bool operator!=(const c_box_formula &rhs) const { return not (*this == rhs); }

        friend bool operator<(const c_box_formula &lhs, const c_box_formula &rhs) {
            if (lhs.m_ags < rhs.m_ags) return true;
            if (rhs.m_ags < lhs.m_ags) return false;

            return lhs.m_f_id < rhs.m_f_id;
        }

        friend bool operator<=(const c_box_formula &lhs, const c_box_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const c_box_formula &lhs, const c_box_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const c_box_formula &lhs, const c_box_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
        formula_id m_f_id;
    };

    class c_diamond_formula {
    public:
        c_diamond_formula(agent_set ags, formula_id f_id, const formula_storage_ptr &storage);

        c_diamond_formula(const c_diamond_formula&) = default;
        c_diamond_formula& operator=(const c_diamond_formula&) = default;

        c_diamond_formula(c_diamond_formula&&) = default;
        c_diamond_formula& operator=(c_diamond_formula&&) = default;

        [[nodiscard]] formula_type get_type() const { return m_type; }
        [[nodiscard]] unsigned long get_modal_depth() const { return m_modal_depth; }
        [[nodiscard]] unsigned long get_size() const { return m_size; }
        [[nodiscard]] static bool is_propositional() { return false; }

        [[nodiscard]] const formula_ptr &get_formula() const { return m_f; }
        [[nodiscard]] formula_id get_formula_id() const { return m_f_id; }
        [[nodiscard]] const agent_set &get_mod_index() const { return m_ags; }

        bool operator==(const c_diamond_formula &rhs) const { return m_ags == rhs.m_ags and m_f_id == rhs.m_f_id; }
        bool operator!=(const c_diamond_formula &rhs) const { return not (*this == rhs); }

        friend bool operator<(const c_diamond_formula &lhs, const c_diamond_formula &rhs) {
            if (lhs.m_ags < rhs.m_ags) return true;
            if (rhs.m_ags < lhs.m_ags) return false;

            return lhs.m_f_id < rhs.m_f_id;
        }

        friend bool operator<=(const c_diamond_formula &lhs, const c_diamond_formula &rhs) { return !(rhs < lhs); }
        friend bool operator> (const c_diamond_formula &lhs, const c_diamond_formula &rhs) { return rhs < lhs; }
        friend bool operator>=(const c_diamond_formula &lhs, const c_diamond_formula &rhs) { return !(lhs < rhs); }

    private:
        formula_type m_type;
        unsigned long m_modal_depth, m_size;
        agent_set m_ags;
        formula_ptr m_f;
        formula_id m_f_id;
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
