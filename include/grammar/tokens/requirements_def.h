#ifndef EPDDL_REQUIREMENTS_DEF_H
#define EPDDL_REQUIREMENTS_DEF_H

#define epddl_requirement_keywords \
    epddl_req_keyword(":common-knowledge")          \
    epddl_req_keyword(":conditional-effects")       \
    epddl_req_keyword(":del")                       \
    epddl_req_keyword(":disjunctive-preconditions") \
    epddl_req_keyword(":equality")                  \
    epddl_req_keyword(":existential-preconditions") \
    epddl_req_keyword(":finitary-S5-theory")        \
    epddl_req_keyword(":full-del")                  \
    epddl_req_keyword(":modal-postconditions")      \
    epddl_req_keyword(":modal-preconditions")       \
    epddl_req_keyword(":multi-agent")               \
    epddl_req_keyword(":negative-preconditions")    \
    epddl_req_keyword(":non-deterministic-actions") \
    epddl_req_keyword(":observability-conditions")  \
    epddl_req_keyword(":ontic-actions")             \
    epddl_req_keyword(":pal")                       \
    epddl_req_keyword(":quantified-preconditions")  \
    epddl_req_keyword(":static-common-knowledge")   \
    epddl_req_keyword(":static-predicates")         \
    epddl_req_keyword(":typing")                    \
    epddl_req_keyword(":universal-preconditions")

#define epddl_val_requirement_keywords \
    epddl_req_keyword(":max-modal-depth")          \
    epddl_req_keyword(":max-postconditions-depth") \
    epddl_req_keyword(":max-preconditions-depth")

#endif //EPDDL_REQUIREMENTS_DEF_H
