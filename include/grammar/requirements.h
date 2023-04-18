#ifndef EPDDL_REQUIREMENTS_H
#define EPDDL_REQUIREMENTS_H

#define epddl_requirement_keywords \
    epddl_req_keyword(":common-knowledge")         \
    epddl_req_keyword(":del")                      \
    epddl_req_keyword(":dynamic-common-knowledge") \
    epddl_req_keyword(":equality")                 \
    epddl_req_keyword(":existential-formulae")     \
    epddl_req_keyword(":finitary-S5-theory")       \
    epddl_req_keyword(":modal-postconditions")     \
    epddl_req_keyword(":modal-preconditions")      \
    epddl_req_keyword(":ontic-change")             \
    epddl_req_keyword(":typing")                   \
    epddl_req_keyword(":universal-formulae")       \
    epddl_req_keyword(":universal-postconditions")

#define epddl_val_requirement_keywords \
    epddl_req_keyword(":maximum-modal-depth")          \
    epddl_req_keyword(":maximum-postconditions-depth") \
    epddl_req_keyword(":maximum-preconditions-depth")

#endif //EPDDL_REQUIREMENTS_H
