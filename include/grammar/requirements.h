#ifndef EPDDL_REQUIREMENTS_H
#define EPDDL_REQUIREMENTS_H

#define epddl_requirements \
    epddl_req(":common-knowledge")         \
    epddl_req(":del")                      \
    epddl_req(":dynamic-common-knowledge") \
    epddl_req(":equality")                 \
    epddl_req(":existential-formulae")     \
    epddl_req(":finitary-S5-theory")       \
    epddl_req(":modal-postconditions")     \
    epddl_req(":modal-preconditions")      \
    epddl_req(":ontic-change")             \
    epddl_req(":typing")                   \
    epddl_req(":universal-formulae")       \
    epddl_req(":universal-postconditions")

#define epddl_val_requirements \
    epddl_req(":maximum-modal-depth")          \
    epddl_req(":maximum-postconditions-depth") \
    epddl_req(":maximum-preconditions-depth")

#endif //EPDDL_REQUIREMENTS_H
