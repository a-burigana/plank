#ifndef EPDDL_AST_GEN_H
#define EPDDL_AST_GEN_H

#define unique_ptr0(type) type##_ptr
#define unique_ptr(type)  unique_ptr0(type)

#define list0(type) std::list<type>
#define list_(type)  list0(type)

#define optional0(type) std::optional<type>
#define optional_(type)  optional0(type)

#include "ast_forward_decl_gen.h"
#include "ast_variant_elements_gen.h"
#include "ast_classes_gen.h"
//#include "ast_aliases_gen.h"

#endif //EPDDL_AST_GEN_H
