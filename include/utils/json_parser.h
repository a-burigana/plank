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

#ifndef PLANK_JSON_PARSER_H
#define PLANK_JSON_PARSER_H

#include "../../ext/json.hpp"
#include "../plank/cli_utils.h"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define JSON_PARSE_FUNCTION(json_name) \
    [&](std::ostream &out,             \
        const json &json_name,         \
        const std::string &err_prefix, \
        const std::string &err_msg     \
    ) -> bool

using namespace nlohmann;

class json_parser {
public:
    using json_map = std::unordered_map<std::string, json>;

    using parsing_f = std::function<bool(
            std::ostream &,
            const json &,
            const std::string &,
            const std::string &)>;

    using parsing_f_map = std::unordered_map<std::string, parsing_f>;

    static bool parse_string(std::ostream &out, const json &string_json,
                             const std::string &err_prefix, const std::string &err_msg,
                             std::string &result) {
        if (not string_json.is_string()) {
            out << err_prefix << ": expected string for " << err_msg << "." << std::endl;
            return false;
        }

        result = to_string(string_json);
        result = result.substr(1, result.length()-2);
        return true;
    }

    static bool parse_array(std::ostream &out, const json &array_json,
                            const std::string &err_prefix, const std::string &err_msg,
                            const parsing_f &f) {
        if (not array_json.is_array()) {
            out << err_prefix << ": expected array of " << err_msg << "." << std::endl;
            return false;
        }

        for (const auto &[_, item_json] : array_json.items())
            if (not f(out, item_json, err_prefix, err_msg))
                return false;

        return true;
    }

    static bool parse_object(std::ostream &out, const json &object_json,
                            const std::string &err_prefix, const std::string &err_msg,
                            const parsing_f_map &f_map, bool must_contain_all_keys = true) {
        if (not object_json.is_object()) {
            out << err_prefix << ": expected object for " << err_msg << "." << std::endl;
            return false;
        }

        std::unordered_set<std::string> visited;

        for (const auto &[key, value_json] : object_json.items())
            if (f_map.find(key) == f_map.end()) {
                out << err_prefix << ": unexpected object key "
                    << plank::cli_utils::quote(key) << "." << std::endl;
                return false;
            } else if (not f_map.at(key)(out, value_json, err_prefix, err_msg))
                return false;
            else
                visited.emplace(key);

        if (must_contain_all_keys)
            for (const auto &[key, _] : f_map)
                if (visited.find(key) == visited.end()) {
                    out << err_prefix << ": missing object key "
                        << plank::cli_utils::quote(key) << "." << std::endl;
                    return false;
                }

        return true;
    }
};

#endif //PLANK_JSON_PARSER_H
