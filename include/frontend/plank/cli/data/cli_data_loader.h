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

#ifndef PLANK_CLI_DATA_LOADER_H
#define PLANK_CLI_DATA_LOADER_H

#include "cli_data.h"
#include "../cli_types.h"
#include "../../utils/json_parser.h"
#include "cli_task_data.h"
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

using namespace nlohmann;
namespace fs = std::filesystem;

namespace plank {
    class cli_data_loader {
    public:
        static bool load_from_file(std::ostream &out, cli_data &data, const fs::path &session_file) {
            std::ifstream file(session_file);
            json session = json::parse(file);
            std::string err_prefix = "In file" + cli_utils::quote(session_file.string());

            json_parser::parsing_f f = JSON_PARSE_FUNCTION(task_data_json) {
                return cli_data_loader::load_task_data(out, data, task_data_json, err_prefix);
            };

            return json_parser::parse_array(out, session, err_prefix, "task session data", f);
        }

        static bool load_specification(std::ostream &out, cli_task_data &task_data,
                                       const json &spec, const std::string &err_prefix) {
            json_parser::parsing_f f = JSON_PARSE_FUNCTION(spec_item_json) {
                return cli_data_loader::load_specification_item(out, task_data, spec_item_json, err_prefix);
            };

            bool result = json_parser::parse_array(out, spec, err_prefix, "EPDDL components paths", f);

            // Making sure we build the language to later parse states and formulas
            if (result)
                task_data.build_info(out, PLANK_NAME, true);
            return result;
        }

    private:
        static bool load_task_data(std::ostream &out, cli_data &data, const json &task_data_json,
                                   const std::string &err_prefix) {
            json_parser::parsing_f f = JSON_PARSE_FUNCTION(task_data_item_json) {
                return cli_data_loader::load_task_data_item(out, data, task_data_item_json, err_prefix);
            };

            return json_parser::parse_array(out, task_data_json, err_prefix, "task data", f);
        }

        static bool load_task_data_item(std::ostream &out, cli_data &data, const json &task_data_item_json,
                                        const std::string &err_prefix) {
            cli_task_data task_data;
            std::string task_name;

            json_parser::parsing_f
                    parse_task_name = JSON_PARSE_FUNCTION(name_json) {
                return json_parser::parse_string(out, name_json, err_prefix, "task name", task_name);
            },
                    parse_task_paths = JSON_PARSE_FUNCTION(paths_json) {
                return cli_data_loader::load_specification(out, task_data, paths_json, err_prefix);
            },
                    parse_task_states = JSON_PARSE_FUNCTION(states_json) {
                return cli_data_loader::load_task_states(out, task_data, states_json, err_prefix);
            },
                    parse_task_formulas = JSON_PARSE_FUNCTION(formulas_json) {
                return cli_data_loader::load_formulas(out, task_data, formulas_json, err_prefix);
            };

            if (not json_parser::parse_object(
                    out, task_data_item_json, err_prefix, "task data item",
                    json_parser::parsing_f_map{
                            {"name",     parse_task_name},
                            {"paths",    parse_task_paths},
                            {"states",   parse_task_states},
                            {"formulas", parse_task_formulas}
                    }))
                return false;

            data.add_task_data(task_name, std::move(task_data));
            return true;
        }

        static bool load_specification_item(std::ostream &out, cli_task_data &task_data,
                                            const json &spec_item_json, const std::string &err_prefix) {
            auto spec_paths = epddl::parser::specification_paths{};

            json_parser::parsing_f
                    parse_problem_path = JSON_PARSE_FUNCTION(problem_json) {
                return cli_data_loader::load_component(out, "problem", problem_json, spec_paths, err_prefix);
            },
                    parse_domain_path = JSON_PARSE_FUNCTION(domain_json) {
                return cli_data_loader::load_component(out, "domain", domain_json, spec_paths, err_prefix);
            },
                    parse_libraries_paths = JSON_PARSE_FUNCTION(libraries_json) {
                return cli_data_loader::load_libraries(out, libraries_json, spec_paths, err_prefix);
            };

            if (not json_parser::parse_object(
                    out, spec_item_json, err_prefix, "EPDDL component path",
                    json_parser::parsing_f_map{
                            {"problem",               parse_problem_path},
                            {"domain",                parse_domain_path},
                            {"action-type-libraries", parse_libraries_paths}
                    }, false))
                return false;

            task_data.set_spec_paths(std::move(spec_paths));
            return true;
        }

        static bool load_component(std::ostream &out, const std::string &component, const json &component_json,
                                   epddl::parser::specification_paths &spec_paths,
                                   const std::string &err_prefix) {
            if (component_json.empty()) {
                out << err_prefix << ": missing " << component << " path." << std::endl;
                return false;
            } else {
                if (not cli_data_loader::load_path(
                        out, component, component_json,
                        [&](const std::string &path) {
                            if (component == "problem")
                                spec_paths.problem_path = path;
                            else
                                spec_paths.domain_path = path;
                        }, err_prefix))
                    return false;
            }
            return true;
        }

        static bool load_libraries(std::ostream &out, const json &libraries_json,
                                   epddl::parser::specification_paths &spec_paths,
                                   const std::string &err_prefix) {
            if (libraries_json.empty()) {
                out << err_prefix << ": missing action type libraries paths." << std::endl;
                return false;
            } else {
                if (not libraries_json.is_array()) {
                    out << err_prefix << ": expected array of action type libraries paths." << std::endl;
                    return false;
                }

                for (const auto &library_json: libraries_json)
                    if (not cli_data_loader::load_path(
                            out, "action type library", library_json,
                            [&](const std::string &path) {
                                spec_paths.libraries_paths.emplace_back(path);
                            }, err_prefix))
                        return false;

                // Removing accidental duplicates from library paths
                spec_paths.libraries_paths.erase(
                        std::unique(spec_paths.libraries_paths.begin(), spec_paths.libraries_paths.end()),
                        spec_paths.libraries_paths.end());

                return true;
            }
        }

        static bool load_path(std::ostream &out, const std::string &component, const json &component_json,
                              const std::function<void(const std::string &)> &load_f,
                              const std::string &err_prefix) {
            std::string component_path;

            if (not json_parser::parse_string(out, component_json, err_prefix, component, component_path))
                return false;

            if (not fs::is_regular_file(component_path)) {
                out << err_prefix << ": no such file "
                    << cli_utils::quote(component_path) << "." << std::endl;
                return false;
            }

            load_f(component_path);
            return true;
        }

        static bool load_task_states(std::ostream &out, cli_task_data &task_data, const json &task_states_json,
                                     const std::string &err_prefix) {
            json_parser::parsing_f f = JSON_PARSE_FUNCTION(task_states_item_json) {
                return cli_data_loader::load_task_states_item(out, task_data, task_states_item_json, err_prefix);
            };

            return json_parser::parse_array(out, task_states_json, err_prefix, "state data", f);
        }

        static bool load_task_states_item(std::ostream &out, cli_task_data &task_data,
                                          const json &task_states_item_json, const std::string &err_prefix) {
            std::string state_name, state_desc;
            del::state_ptr s;

            json_parser::parsing_f
                    parse_state_name = JSON_PARSE_FUNCTION(name_json) {
                return json_parser::parse_string(out, name_json, err_prefix, "state name", state_name);
            },
                    parse_state = JSON_PARSE_FUNCTION(states_json) {
                return cli_data_loader::load_state(out, task_data, states_json, err_prefix, s);
            },
                    parse_state_desc = JSON_PARSE_FUNCTION(desc_json) {
                return json_parser::parse_string(out, desc_json, err_prefix, "state description", state_desc);
            };

            if (not json_parser::parse_object(
                    out, task_states_item_json, err_prefix, "state data item",
                    json_parser::parsing_f_map{
                            {"name",   parse_state_name},
                            {"paths",  parse_state},
                            {"states", parse_state_desc}
                    }))
                return false;

            task_data.add_state(state_name, s, state_desc);
            return true;
        }

        static bool load_state(std::ostream &out, cli_task_data &task_data, const json &state_json,
                               const std::string &err_prefix, del::state_ptr &s) {
            json_parser::parsing_f f = JSON_PARSE_FUNCTION(state_item_json) {
                return cli_data_loader::load_state_item(out, task_data, state_item_json, err_prefix, s);
            };

            return json_parser::parse_array(out, state_json, err_prefix, "state data", f);
        }

        static bool load_state_item(std::ostream &out, cli_task_data &task_data, const json &state_json,
                                    const std::string &err_prefix, del::state_ptr &s) {
            std::unordered_map<std::string, del::world_id> world_id_map;
            del::relations r;
            del::label_vector l;
            del::world_bitset designated;

            json_parser::parsing_f
                parse_state_worlds = JSON_PARSE_FUNCTION(worlds_json) {
                    return cli_data_loader::load_world_id_map(out, task_data, worlds_json, err_prefix, world_id_map);
                },
                parse_state_relations = JSON_PARSE_FUNCTION(relations_json) {
                    return cli_data_loader::load_relations(out, task_data, relations_json, err_prefix, r, world_id_map);
                },
                parse_state_labels = JSON_PARSE_FUNCTION(labels_json) {
                    return cli_data_loader::load_labels(out, task_data, labels_json, err_prefix, l);
                },
                parse_state_designated = JSON_PARSE_FUNCTION(designated_json) {
                    return cli_data_loader::load_designated(out, task_data, designated_json, err_prefix, designated);
                };

            if (not json_parser::parse_object(
                out, state_json, err_prefix, "state component",
                json_parser::parsing_f_map{
                    {"worlds",     parse_state_worlds},
                    {"relations",  parse_state_relations},
                    {"labels",     parse_state_labels},
                    {"designated", parse_state_designated}
                }))
                return false;

            s = std::make_shared<del::state>(task_data.get_info().language, world_id_map.size(),
                                             std::move(r), std::move(l), std::move(designated));
            return true;
        }

        static bool load_world_id_map(std::ostream &out, cli_task_data &task_data, const json &worlds_json,
                                      const std::string &err_prefix,
                                      std::unordered_map<std::string, del::world_id> &world_id_map) {
            del::world_id w = 0;

            json_parser::parsing_f f = JSON_PARSE_FUNCTION(world_json) {
                std::string world_name;
                bool result = json_parser::parse_string(out, world_json, err_prefix, "world name", world_name);

                world_id_map[world_name] = w++;
                return result;
            };

            return json_parser::parse_array(out, worlds_json, err_prefix, "world names", f);
        }

        static bool load_relations(std::ostream &out, cli_task_data &task_data, const json &relations_json,
                                   const std::string &err_prefix, del::relations &r,
                                   std::unordered_map<std::string, del::world_id> &world_id_map) {
            r = del::relations(task_data.get_info().language->get_agents_number());

            for (auto &r_i : r) {
                r_i = del::agent_relation(world_id_map.size());

                for (auto &r_i_w : r_i)
                    r_i_w = del::world_bitset(world_id_map.size());
            }

            json_parser::parsing_f f = JSON_PARSE_FUNCTION(ag_relation_json) {
                return cli_data_loader::load_agent_relation(out, task_data, ag_relation_json,
                                                            err_prefix, r, world_id_map);
            };

            return json_parser::parse_array(out, relations_json, err_prefix, "state relations", f);
        }

        static bool load_agent_relation(std::ostream &out, cli_task_data &task_data, const json &ag_relation_json,
                                        const std::string &err_prefix, del::relations &r,
                                        std::unordered_map<std::string, del::world_id> &world_id_map) {
            json_parser::parsing_f_map f_map;

            for (const auto &ag_name : task_data.get_info().language->get_agents_names())
                f_map[ag_name] =
                        JSON_PARSE_FUNCTION(adj_list_json) {
                            return cli_data_loader::load_agent_relation(out, task_data, adj_list_json,
                                                                        err_prefix, r, world_id_map);
                        };

            return json_parser::parse_object(out, ag_relation_json, err_prefix, "agent relation", f_map);
        }



        static bool load_labels(std::ostream &out, cli_task_data &task_data, const json &state_json,
                                   const std::string &err_prefix, del::label_vector &l) {
            return false;
        }

        static bool load_designated(std::ostream &out, cli_task_data &task_data, const json &state_json,
                                   const std::string &err_prefix, del::world_bitset &designated) {
            return false;
        }

        static bool load_formulas(std::ostream &out, cli_task_data &data, const json &formulas_json,
                                  const std::string &err_prefix) {
            bool good_json = formulas_json.is_array();

            if (not good_json) {
                out << err_prefix << ": expected array of state data." << std::endl;
                return false;
            }

            json name_json, formula_json;

            for (const auto &[_, item_json] : formulas_json.items()) {
                if (not item_json.is_object() or item_json.size() != 1)
                    good_json = false;
                else
                    for (const auto &[key, value]: item_json.items())
                        if (key == "name")
                            name_json = value;
                        else if (key == "formula")
                            formula_json = value;
                        else  {
                            out << err_prefix << ": unexpected formula data "
                                << cli_utils::quote(key) << "." << std::endl;
                            return false;
                        }
            }

            if (not name_json.is_string()) {
                out << err_prefix << ": formula name must be a string." << std::endl;
                return false;
            }

            const std::string state_name = to_string(name_json);

            return true;
        }
    };
}

#endif //PLANK_CLI_DATA_LOADER_H
