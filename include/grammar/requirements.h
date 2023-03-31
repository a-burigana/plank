#ifndef EPDDL_REQUIREMENTS_H
#define EPDDL_REQUIREMENTS_H

#define REQUIREMENTS \
    REQ(":common-knowledge")         \
    REQ(":del")                      \
    REQ(":dynamic-common-knowledge") \
    REQ(":equality")                 \
    REQ(":existential-formulae")     \
    REQ(":finitary-S5-theory")        \
    REQ(":modal-postconditions")     \
    REQ(":modal-preconditions")      \
    REQ(":ontic-change")             \
    REQ(":typing")                   \
    REQ(":universal-formulae")       \
    REQ(":universal-postconditions")

#define VAL_REQUIREMENTS \
    REQ(":maximum-modal-depth")          \
    REQ(":maximum-postconditions-depth") \
    REQ(":maximum-preconditions-depth")

#endif //EPDDL_REQUIREMENTS_H
