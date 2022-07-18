/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         epddl_parse
#define yylex           epddl_lex
#define yyerror         epddl_error
#define yydebug         epddl_debug
#define yynerrs         epddl_nerrs

/* First part of user prologue.  */
#line 20 "epddl.y"

/* Begin C preamble code */

#include <algorithm> /* for std::reverse */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Absyn.H"

#define YYMAXDEPTH 10000000

/* The type yyscan_t is defined by flex, but we need it in the parser already. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE epddl__scan_string(const char *str, yyscan_t scanner);
extern void epddl__delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void epddl_lex_destroy(yyscan_t scanner);
extern char* epddl_get_text(yyscan_t scanner);

extern yyscan_t epddl__initialize_lexer(FILE * inp);

/* End C preamble code */

#line 105 "Parser.C"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Bison.H"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL__ERROR_ = 3,                    /* _ERROR_  */
  YYSYMBOL__LPAREN = 4,                    /* _LPAREN  */
  YYSYMBOL__RPAREN = 5,                    /* _RPAREN  */
  YYSYMBOL__MINUS = 6,                     /* _MINUS  */
  YYSYMBOL__DCOLON = 7,                    /* _DCOLON  */
  YYSYMBOL__SYMB_8 = 8,                    /* _SYMB_8  */
  YYSYMBOL__SYMB_11 = 9,                   /* _SYMB_11  */
  YYSYMBOL__SYMB_2 = 10,                   /* _SYMB_2  */
  YYSYMBOL__SYMB_22 = 11,                  /* _SYMB_22  */
  YYSYMBOL__SYMB_21 = 12,                  /* _SYMB_21  */
  YYSYMBOL__SYMB_53 = 13,                  /* _SYMB_53  */
  YYSYMBOL__SYMB_42 = 14,                  /* _SYMB_42  */
  YYSYMBOL__SYMB_17 = 15,                  /* _SYMB_17  */
  YYSYMBOL__SYMB_47 = 16,                  /* _SYMB_47  */
  YYSYMBOL__SYMB_20 = 17,                  /* _SYMB_20  */
  YYSYMBOL__SYMB_54 = 18,                  /* _SYMB_54  */
  YYSYMBOL__SYMB_44 = 19,                  /* _SYMB_44  */
  YYSYMBOL__SYMB_18 = 20,                  /* _SYMB_18  */
  YYSYMBOL__SYMB_15 = 21,                  /* _SYMB_15  */
  YYSYMBOL__SYMB_48 = 22,                  /* _SYMB_48  */
  YYSYMBOL__SYMB_26 = 23,                  /* _SYMB_26  */
  YYSYMBOL__SYMB_14 = 24,                  /* _SYMB_14  */
  YYSYMBOL__SYMB_34 = 25,                  /* _SYMB_34  */
  YYSYMBOL__SYMB_27 = 26,                  /* _SYMB_27  */
  YYSYMBOL__SYMB_55 = 27,                  /* _SYMB_55  */
  YYSYMBOL__SYMB_58 = 28,                  /* _SYMB_58  */
  YYSYMBOL__SYMB_59 = 29,                  /* _SYMB_59  */
  YYSYMBOL__SYMB_56 = 30,                  /* _SYMB_56  */
  YYSYMBOL__SYMB_57 = 31,                  /* _SYMB_57  */
  YYSYMBOL__SYMB_62 = 32,                  /* _SYMB_62  */
  YYSYMBOL__SYMB_61 = 33,                  /* _SYMB_61  */
  YYSYMBOL__SYMB_60 = 34,                  /* _SYMB_60  */
  YYSYMBOL__SYMB_51 = 35,                  /* _SYMB_51  */
  YYSYMBOL__SYMB_50 = 36,                  /* _SYMB_50  */
  YYSYMBOL__SYMB_6 = 37,                   /* _SYMB_6  */
  YYSYMBOL__SYMB_31 = 38,                  /* _SYMB_31  */
  YYSYMBOL__SYMB_28 = 39,                  /* _SYMB_28  */
  YYSYMBOL__SYMB_46 = 40,                  /* _SYMB_46  */
  YYSYMBOL__SYMB_25 = 41,                  /* _SYMB_25  */
  YYSYMBOL__SYMB_13 = 42,                  /* _SYMB_13  */
  YYSYMBOL__SYMB_7 = 43,                   /* _SYMB_7  */
  YYSYMBOL__SYMB_52 = 44,                  /* _SYMB_52  */
  YYSYMBOL__SYMB_45 = 45,                  /* _SYMB_45  */
  YYSYMBOL__SYMB_9 = 46,                   /* _SYMB_9  */
  YYSYMBOL__SYMB_19 = 47,                  /* _SYMB_19  */
  YYSYMBOL__SYMB_12 = 48,                  /* _SYMB_12  */
  YYSYMBOL__SYMB_5 = 49,                   /* _SYMB_5  */
  YYSYMBOL__SYMB_16 = 50,                  /* _SYMB_16  */
  YYSYMBOL__SYMB_3 = 51,                   /* _SYMB_3  */
  YYSYMBOL__SYMB_4 = 52,                   /* _SYMB_4  */
  YYSYMBOL__SYMB_43 = 53,                  /* _SYMB_43  */
  YYSYMBOL__SYMB_49 = 54,                  /* _SYMB_49  */
  YYSYMBOL__SYMB_33 = 55,                  /* _SYMB_33  */
  YYSYMBOL__SYMB_10 = 56,                  /* _SYMB_10  */
  YYSYMBOL__SYMB_32 = 57,                  /* _SYMB_32  */
  YYSYMBOL__LT = 58,                       /* _LT  */
  YYSYMBOL__EQ = 59,                       /* _EQ  */
  YYSYMBOL__GT = 60,                       /* _GT  */
  YYSYMBOL__SYMB_39 = 61,                  /* _SYMB_39  */
  YYSYMBOL__KW_All = 62,                   /* _KW_All  */
  YYSYMBOL__LBRACK = 63,                   /* _LBRACK  */
  YYSYMBOL__RBRACK = 64,                   /* _RBRACK  */
  YYSYMBOL__KW_agent = 65,                 /* _KW_agent  */
  YYSYMBOL__KW_and = 66,                   /* _KW_and  */
  YYSYMBOL__KW_as = 67,                    /* _KW_as  */
  YYSYMBOL__KW_define = 68,                /* _KW_define  */
  YYSYMBOL__KW_domain = 69,                /* _KW_domain  */
  YYSYMBOL__KW_false = 70,                 /* _KW_false  */
  YYSYMBOL__KW_forall = 71,                /* _KW_forall  */
  YYSYMBOL__KW_formula = 72,               /* _KW_formula  */
  YYSYMBOL__KW_if = 73,                    /* _KW_if  */
  YYSYMBOL__KW_iff = 74,                   /* _KW_iff  */
  YYSYMBOL__KW_imply = 75,                 /* _KW_imply  */
  YYSYMBOL__KW_library = 76,               /* _KW_library  */
  YYSYMBOL__KW_literal = 77,               /* _KW_literal  */
  YYSYMBOL__KW_not = 78,                   /* _KW_not  */
  YYSYMBOL__KW_or = 79,                    /* _KW_or  */
  YYSYMBOL__KW_otherwise = 80,             /* _KW_otherwise  */
  YYSYMBOL__KW_postcondition = 81,         /* _KW_postcondition  */
  YYSYMBOL__KW_predicate = 82,             /* _KW_predicate  */
  YYSYMBOL__SYMB_41 = 83,                  /* _SYMB_41  */
  YYSYMBOL__KW_problem = 84,               /* _KW_problem  */
  YYSYMBOL__KW_set = 85,                   /* _KW_set  */
  YYSYMBOL__KW_true = 86,                  /* _KW_true  */
  YYSYMBOL__LBRACE = 87,                   /* _LBRACE  */
  YYSYMBOL__RBRACE = 88,                   /* _RBRACE  */
  YYSYMBOL_T_AgentName = 89,               /* T_AgentName  */
  YYSYMBOL_T_ModalityName = 90,            /* T_ModalityName  */
  YYSYMBOL_T_Name = 91,                    /* T_Name  */
  YYSYMBOL_T_Variable = 92,                /* T_Variable  */
  YYSYMBOL__INTEGER_ = 93,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_MainDef = 95,                   /* MainDef  */
  YYSYMBOL_DomainDef = 96,                 /* DomainDef  */
  YYSYMBOL_DomainItemDef = 97,             /* DomainItemDef  */
  YYSYMBOL_ListDomainItemDef = 98,         /* ListDomainItemDef  */
  YYSYMBOL_DomainLibrariesNameDef = 99,    /* DomainLibrariesNameDef  */
  YYSYMBOL_RequireDef = 100,               /* RequireDef  */
  YYSYMBOL_TypesDef = 101,                 /* TypesDef  */
  YYSYMBOL_PredicateListDef = 102,         /* PredicateListDef  */
  YYSYMBOL_PredicateDef = 103,             /* PredicateDef  */
  YYSYMBOL_ListPredicateDef = 104,         /* ListPredicateDef  */
  YYSYMBOL_ModalitiesDef = 105,            /* ModalitiesDef  */
  YYSYMBOL_ObservabilityGroupsDef = 106,   /* ObservabilityGroupsDef  */
  YYSYMBOL_ActionDef = 107,                /* ActionDef  */
  YYSYMBOL_ActionParameterDef = 108,       /* ActionParameterDef  */
  YYSYMBOL_ActionConditionsDef = 109,      /* ActionConditionsDef  */
  YYSYMBOL_ActionTypeSignatureDef = 110,   /* ActionTypeSignatureDef  */
  YYSYMBOL_ActionPreDef = 111,             /* ActionPreDef  */
  YYSYMBOL_ActionObsDef = 112,             /* ActionObsDef  */
  YYSYMBOL_ObsConditionDef = 113,          /* ObsConditionDef  */
  YYSYMBOL_ListObsConditionDef = 114,      /* ListObsConditionDef  */
  YYSYMBOL_LibraryDef = 115,               /* LibraryDef  */
  YYSYMBOL_LibraryItemDef = 116,           /* LibraryItemDef  */
  YYSYMBOL_ListLibraryItemDef = 117,       /* ListLibraryItemDef  */
  YYSYMBOL_ActionTypeDef = 118,            /* ActionTypeDef  */
  YYSYMBOL_ActionTypeParameterDef = 119,   /* ActionTypeParameterDef  */
  YYSYMBOL_ActionTypeFrameDef = 120,       /* ActionTypeFrameDef  */
  YYSYMBOL_ActionTypeEventsDef = 121,      /* ActionTypeEventsDef  */
  YYSYMBOL_ActionTypeRelDef = 122,         /* ActionTypeRelDef  */
  YYSYMBOL_ActionTypeDesDef = 123,         /* ActionTypeDesDef  */
  YYSYMBOL_EventSignature = 124,           /* EventSignature  */
  YYSYMBOL_ListEventSignature = 125,       /* ListEventSignature  */
  YYSYMBOL_ActionRelations = 126,          /* ActionRelations  */
  YYSYMBOL_EventRelation = 127,            /* EventRelation  */
  YYSYMBOL_ListEventRelation = 128,        /* ListEventRelation  */
  YYSYMBOL_EventNamePair = 129,            /* EventNamePair  */
  YYSYMBOL_ListEventNamePair = 130,        /* ListEventNamePair  */
  YYSYMBOL_EventDef = 131,                 /* EventDef  */
  YYSYMBOL_EventParameterDef = 132,        /* EventParameterDef  */
  YYSYMBOL_EventPreDef = 133,              /* EventPreDef  */
  YYSYMBOL_EventPostDef = 134,             /* EventPostDef  */
  YYSYMBOL_EventPostconditions = 135,      /* EventPostconditions  */
  YYSYMBOL_Postcondition = 136,            /* Postcondition  */
  YYSYMBOL_ListPostcondition = 137,        /* ListPostcondition  */
  YYSYMBOL_LiteralPostcondition = 138,     /* LiteralPostcondition  */
  YYSYMBOL_ListLiteralPostcondition = 139, /* ListLiteralPostcondition  */
  YYSYMBOL_ProblemDef = 140,               /* ProblemDef  */
  YYSYMBOL_ProblemItemDef = 141,           /* ProblemItemDef  */
  YYSYMBOL_ListProblemItemDef = 142,       /* ListProblemItemDef  */
  YYSYMBOL_ProblemDomainNameDef = 143,     /* ProblemDomainNameDef  */
  YYSYMBOL_AgentNamesDef = 144,            /* AgentNamesDef  */
  YYSYMBOL_AgentGroupsListDef = 145,       /* AgentGroupsListDef  */
  YYSYMBOL_AgentGroupDef = 146,            /* AgentGroupDef  */
  YYSYMBOL_ListAgentGroupDef = 147,        /* ListAgentGroupDef  */
  YYSYMBOL_ObjectNamesDef = 148,           /* ObjectNamesDef  */
  YYSYMBOL_FactListDef = 149,              /* FactListDef  */
  YYSYMBOL_FactDef = 150,                  /* FactDef  */
  YYSYMBOL_ListFactDef = 151,              /* ListFactDef  */
  YYSYMBOL_InitDef = 152,                  /* InitDef  */
  YYSYMBOL_InitialStateDescr = 153,        /* InitialStateDescr  */
  YYSYMBOL_FTheoryFormula = 154,           /* FTheoryFormula  */
  YYSYMBOL_ListFTheoryFormula = 155,       /* ListFTheoryFormula  */
  YYSYMBOL_KPredicateFormula = 156,        /* KPredicateFormula  */
  YYSYMBOL_KWPredicateFormula = 157,       /* KWPredicateFormula  */
  YYSYMBOL_NotKWPredicateFormula = 158,    /* NotKWPredicateFormula  */
  YYSYMBOL_InitialModelDef = 159,          /* InitialModelDef  */
  YYSYMBOL_ModelWorldsDef = 160,           /* ModelWorldsDef  */
  YYSYMBOL_ModelRelDef = 161,              /* ModelRelDef  */
  YYSYMBOL_ModelValDef = 162,              /* ModelValDef  */
  YYSYMBOL_ModelDesDef = 163,              /* ModelDesDef  */
  YYSYMBOL_ModelRelations = 164,           /* ModelRelations  */
  YYSYMBOL_ModelValuation = 165,           /* ModelValuation  */
  YYSYMBOL_WorldRelation = 166,            /* WorldRelation  */
  YYSYMBOL_ListWorldRelation = 167,        /* ListWorldRelation  */
  YYSYMBOL_WorldNamePair = 168,            /* WorldNamePair  */
  YYSYMBOL_ListWorldNamePair = 169,        /* ListWorldNamePair  */
  YYSYMBOL_WorldValuation = 170,           /* WorldValuation  */
  YYSYMBOL_ListWorldValuation = 171,       /* ListWorldValuation  */
  YYSYMBOL_GoalDef = 172,                  /* GoalDef  */
  YYSYMBOL_Formula = 173,                  /* Formula  */
  YYSYMBOL_ListFormula = 174,              /* ListFormula  */
  YYSYMBOL_AtomicFormula = 175,            /* AtomicFormula  */
  YYSYMBOL_AtomicEqFormula = 176,          /* AtomicEqFormula  */
  YYSYMBOL_FormulaOrEmpty = 177,           /* FormulaOrEmpty  */
  YYSYMBOL_MetaTerm = 178,                 /* MetaTerm  */
  YYSYMBOL_ListMetaTerm = 179,             /* ListMetaTerm  */
  YYSYMBOL_Term = 180,                     /* Term  */
  YYSYMBOL_ListTerm = 181,                 /* ListTerm  */
  YYSYMBOL_GroundTerm = 182,               /* GroundTerm  */
  YYSYMBOL_ListGroundTerm = 183,           /* ListGroundTerm  */
  YYSYMBOL_Modality = 184,                 /* Modality  */
  YYSYMBOL_SingleModality = 185,           /* SingleModality  */
  YYSYMBOL_GroupModality = 186,            /* GroupModality  */
  YYSYMBOL_ModalityLabel = 187,            /* ModalityLabel  */
  YYSYMBOL_KnowsWhether = 188,             /* KnowsWhether  */
  YYSYMBOL_Literal = 189,                  /* Literal  */
  YYSYMBOL_ListLiteral = 190,              /* ListLiteral  */
  YYSYMBOL_ConditionFormula = 191,         /* ConditionFormula  */
  YYSYMBOL_Condition = 192,                /* Condition  */
  YYSYMBOL_ListCondition = 193,            /* ListCondition  */
  YYSYMBOL_AtomicCondition = 194,          /* AtomicCondition  */
  YYSYMBOL_PredicateFormula = 195,         /* PredicateFormula  */
  YYSYMBOL_ListPredicateFormula = 196,     /* ListPredicateFormula  */
  YYSYMBOL_GenericName = 197,              /* GenericName  */
  YYSYMBOL_ListGenericName = 198,          /* ListGenericName  */
  YYSYMBOL_TypedIdentList = 199,           /* TypedIdentList  */
  YYSYMBOL_TypedVariableList = 200,        /* TypedVariableList  */
  YYSYMBOL_PredicateName = 201,            /* PredicateName  */
  YYSYMBOL_ModalityAgent = 202,            /* ModalityAgent  */
  YYSYMBOL_ListModalityAgent = 203,        /* ListModalityAgent  */
  YYSYMBOL_ModalityAgentGroup = 204,       /* ModalityAgentGroup  */
  YYSYMBOL_AgentGroupName = 205,           /* AgentGroupName  */
  YYSYMBOL_ObservingAgentGroup = 206,      /* ObservingAgentGroup  */
  YYSYMBOL_ListObservingAgentGroup = 207,  /* ListObservingAgentGroup  */
  YYSYMBOL_ObservingAgent = 208,           /* ObservingAgent  */
  YYSYMBOL_AgentGroup = 209,               /* AgentGroup  */
  YYSYMBOL_AllAgents = 210,                /* AllAgents  */
  YYSYMBOL_AnonVarAgent = 211,             /* AnonVarAgent  */
  YYSYMBOL_Parameter = 212,                /* Parameter  */
  YYSYMBOL_ListParameter = 213,            /* ListParameter  */
  YYSYMBOL_ParameterValue = 214,           /* ParameterValue  */
  YYSYMBOL_PostParameterValue = 215,       /* PostParameterValue  */
  YYSYMBOL_ListPostParameterValue = 216,   /* ListPostParameterValue  */
  YYSYMBOL_Type = 217,                     /* Type  */
  YYSYMBOL_ReservedType = 218,             /* ReservedType  */
  YYSYMBOL_DomainName = 219,               /* DomainName  */
  YYSYMBOL_LibraryName = 220,              /* LibraryName  */
  YYSYMBOL_ListLibraryName = 221,          /* ListLibraryName  */
  YYSYMBOL_ProblemName = 222,              /* ProblemName  */
  YYSYMBOL_ActionName = 223,               /* ActionName  */
  YYSYMBOL_ActionTypeName = 224,           /* ActionTypeName  */
  YYSYMBOL_EventName = 225,                /* EventName  */
  YYSYMBOL_ListEventName = 226,            /* ListEventName  */
  YYSYMBOL_ModelName = 227,                /* ModelName  */
  YYSYMBOL_WorldName = 228,                /* WorldName  */
  YYSYMBOL_ListWorldName = 229,            /* ListWorldName  */
  YYSYMBOL_RequireKey = 230,               /* RequireKey  */
  YYSYMBOL_ListRequireKey = 231,           /* ListRequireKey  */
  YYSYMBOL_TrivialDef = 232,               /* TrivialDef  */
  YYSYMBOL_ListName = 233,                 /* ListName  */
  YYSYMBOL_ListAgentName = 234,            /* ListAgentName  */
  YYSYMBOL_ListModalityName = 235,         /* ListModalityName  */
  YYSYMBOL_ListVariable = 236,             /* ListVariable  */
  YYSYMBOL_Name = 237,                     /* Name  */
  YYSYMBOL_AgentName = 238,                /* AgentName  */
  YYSYMBOL_ModalityName = 239,             /* ModalityName  */
  YYSYMBOL_Variable = 240                  /* Variable  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 203 "epddl.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, epddl_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 391 "Parser.C"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   631

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  147
/* YYNRULES -- Number of rules.  */
#define YYNRULES  295
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  558

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   348


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   458,   458,   459,   460,   462,   464,   465,   466,   467,
     468,   469,   470,   472,   473,   475,   477,   479,   481,   483,
     485,   486,   488,   490,   492,   494,   496,   497,   499,   501,
     503,   504,   506,   507,   508,   510,   511,   513,   515,   516,
     517,   518,   519,   521,   522,   524,   526,   528,   529,   531,
     533,   535,   537,   539,   540,   542,   543,   545,   546,   548,
     549,   551,   553,   554,   556,   558,   560,   562,   563,   565,
     566,   568,   569,   570,   572,   573,   575,   576,   578,   579,
     581,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   594,   595,   597,   599,   601,   603,   605,   606,   608,
     610,   612,   614,   615,   617,   619,   620,   622,   623,   624,
     625,   626,   627,   629,   630,   632,   633,   635,   636,   638,
     639,   641,   643,   645,   647,   649,   651,   652,   654,   655,
     657,   658,   660,   661,   663,   665,   666,   668,   670,   671,
     673,   675,   676,   677,   678,   679,   680,   681,   682,   683,
     684,   685,   687,   688,   690,   692,   694,   695,   697,   698,
     700,   701,   703,   704,   706,   707,   709,   710,   712,   713,
     715,   716,   718,   719,   721,   722,   724,   725,   727,   729,
     730,   732,   733,   735,   736,   738,   739,   741,   742,   744,
     745,   747,   748,   749,   750,   751,   753,   754,   756,   757,
     759,   760,   762,   763,   765,   766,   768,   770,   771,   772,
     773,   775,   776,   778,   780,   781,   783,   785,   786,   788,
     789,   790,   791,   793,   794,   796,   798,   800,   802,   803,
     805,   806,   807,   809,   810,   812,   813,   815,   816,   818,
     819,   820,   821,   822,   823,   825,   827,   829,   830,   832,
     834,   836,   838,   840,   841,   843,   845,   847,   848,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   860,
     861,   862,   863,   864,   865,   866,   867,   868,   869,   870,
     871,   873,   874,   876,   878,   879,   881,   882,   884,   885,
     887,   888,   890,   892,   894,   896
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "_ERROR_", "_LPAREN",
  "_RPAREN", "_MINUS", "_DCOLON", "_SYMB_8", "_SYMB_11", "_SYMB_2",
  "_SYMB_22", "_SYMB_21", "_SYMB_53", "_SYMB_42", "_SYMB_17", "_SYMB_47",
  "_SYMB_20", "_SYMB_54", "_SYMB_44", "_SYMB_18", "_SYMB_15", "_SYMB_48",
  "_SYMB_26", "_SYMB_14", "_SYMB_34", "_SYMB_27", "_SYMB_55", "_SYMB_58",
  "_SYMB_59", "_SYMB_56", "_SYMB_57", "_SYMB_62", "_SYMB_61", "_SYMB_60",
  "_SYMB_51", "_SYMB_50", "_SYMB_6", "_SYMB_31", "_SYMB_28", "_SYMB_46",
  "_SYMB_25", "_SYMB_13", "_SYMB_7", "_SYMB_52", "_SYMB_45", "_SYMB_9",
  "_SYMB_19", "_SYMB_12", "_SYMB_5", "_SYMB_16", "_SYMB_3", "_SYMB_4",
  "_SYMB_43", "_SYMB_49", "_SYMB_33", "_SYMB_10", "_SYMB_32", "_LT", "_EQ",
  "_GT", "_SYMB_39", "_KW_All", "_LBRACK", "_RBRACK", "_KW_agent",
  "_KW_and", "_KW_as", "_KW_define", "_KW_domain", "_KW_false",
  "_KW_forall", "_KW_formula", "_KW_if", "_KW_iff", "_KW_imply",
  "_KW_library", "_KW_literal", "_KW_not", "_KW_or", "_KW_otherwise",
  "_KW_postcondition", "_KW_predicate", "_SYMB_41", "_KW_problem",
  "_KW_set", "_KW_true", "_LBRACE", "_RBRACE", "T_AgentName",
  "T_ModalityName", "T_Name", "T_Variable", "_INTEGER_", "$accept",
  "MainDef", "DomainDef", "DomainItemDef", "ListDomainItemDef",
  "DomainLibrariesNameDef", "RequireDef", "TypesDef", "PredicateListDef",
  "PredicateDef", "ListPredicateDef", "ModalitiesDef",
  "ObservabilityGroupsDef", "ActionDef", "ActionParameterDef",
  "ActionConditionsDef", "ActionTypeSignatureDef", "ActionPreDef",
  "ActionObsDef", "ObsConditionDef", "ListObsConditionDef", "LibraryDef",
  "LibraryItemDef", "ListLibraryItemDef", "ActionTypeDef",
  "ActionTypeParameterDef", "ActionTypeFrameDef", "ActionTypeEventsDef",
  "ActionTypeRelDef", "ActionTypeDesDef", "EventSignature",
  "ListEventSignature", "ActionRelations", "EventRelation",
  "ListEventRelation", "EventNamePair", "ListEventNamePair", "EventDef",
  "EventParameterDef", "EventPreDef", "EventPostDef",
  "EventPostconditions", "Postcondition", "ListPostcondition",
  "LiteralPostcondition", "ListLiteralPostcondition", "ProblemDef",
  "ProblemItemDef", "ListProblemItemDef", "ProblemDomainNameDef",
  "AgentNamesDef", "AgentGroupsListDef", "AgentGroupDef",
  "ListAgentGroupDef", "ObjectNamesDef", "FactListDef", "FactDef",
  "ListFactDef", "InitDef", "InitialStateDescr", "FTheoryFormula",
  "ListFTheoryFormula", "KPredicateFormula", "KWPredicateFormula",
  "NotKWPredicateFormula", "InitialModelDef", "ModelWorldsDef",
  "ModelRelDef", "ModelValDef", "ModelDesDef", "ModelRelations",
  "ModelValuation", "WorldRelation", "ListWorldRelation", "WorldNamePair",
  "ListWorldNamePair", "WorldValuation", "ListWorldValuation", "GoalDef",
  "Formula", "ListFormula", "AtomicFormula", "AtomicEqFormula",
  "FormulaOrEmpty", "MetaTerm", "ListMetaTerm", "Term", "ListTerm",
  "GroundTerm", "ListGroundTerm", "Modality", "SingleModality",
  "GroupModality", "ModalityLabel", "KnowsWhether", "Literal",
  "ListLiteral", "ConditionFormula", "Condition", "ListCondition",
  "AtomicCondition", "PredicateFormula", "ListPredicateFormula",
  "GenericName", "ListGenericName", "TypedIdentList", "TypedVariableList",
  "PredicateName", "ModalityAgent", "ListModalityAgent",
  "ModalityAgentGroup", "AgentGroupName", "ObservingAgentGroup",
  "ListObservingAgentGroup", "ObservingAgent", "AgentGroup", "AllAgents",
  "AnonVarAgent", "Parameter", "ListParameter", "ParameterValue",
  "PostParameterValue", "ListPostParameterValue", "Type", "ReservedType",
  "DomainName", "LibraryName", "ListLibraryName", "ProblemName",
  "ActionName", "ActionTypeName", "EventName", "ListEventName",
  "ModelName", "WorldName", "ListWorldName", "RequireKey",
  "ListRequireKey", "TrivialDef", "ListName", "ListAgentName",
  "ListModalityName", "ListVariable", "Name", "AgentName", "ModalityName",
  "Variable", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-377)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      57,     6,   119,  -377,  -377,  -377,   118,  -377,   162,    64,
      64,    64,  -377,   157,  -377,   164,  -377,   166,  -377,  -377,
    -377,  -377,    75,   185,   254,   350,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,   334,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,   380,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,    64,    64,    88,    91,
     181,   522,    64,    64,    64,  -377,    91,    64,   190,   138,
      45,    64,    64,   156,  -377,    64,   199,  -377,   211,    88,
    -377,    91,   228,  -377,    64,   181,   230,   277,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,   522,   232,   239,
    -377,    64,   167,  -377,   209,  -377,   285,   257,    91,   270,
      64,   190,   280,   442,    88,    88,  -377,  -377,   289,  -377,
    -377,   138,  -377,  -377,    73,   234,   301,    84,  -377,  -377,
     263,  -377,   319,   355,   282,  -377,  -377,  -377,  -377,  -377,
    -377,   269,  -377,  -377,  -377,   279,   283,   286,  -377,  -377,
    -377,   340,    64,   369,   351,   376,   336,   299,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,   216,   138,   138,   138,
     138,  -377,   383,  -377,   385,   306,  -377,   306,  -377,  -377,
     173,    64,   392,   392,   392,   392,   399,  -377,  -377,   344,
    -377,  -377,   405,   360,  -377,   269,   415,   411,   418,  -377,
     269,   421,   424,   433,   432,  -377,   269,   435,   422,   269,
     218,   395,    91,    20,   216,  -377,  -377,  -377,  -377,   138,
     138,   440,   138,  -377,    37,  -377,  -377,   180,   387,  -377,
    -377,  -377,  -377,   352,   384,   444,   349,   392,   392,   446,
     392,  -377,    55,    87,    64,   448,   398,   449,   225,  -377,
    -377,  -377,   453,   410,  -377,   454,   269,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,    64,  -377,  -377,   462,
      91,   464,   419,   466,   407,  -377,  -377,  -377,   468,   469,
     388,  -377,  -377,  -377,  -377,   470,   138,   473,   474,  -377,
     475,  -377,  -377,  -377,  -377,  -377,   306,  -377,  -377,  -377,
    -377,  -377,   392,   476,   479,  -377,   483,  -377,  -377,   208,
     212,  -377,  -377,  -377,   392,  -377,    64,   484,  -377,   122,
    -377,   486,  -377,  -377,   487,   477,  -377,   216,   490,   491,
    -377,    64,   218,   465,   432,  -377,  -377,  -377,   501,    64,
     464,  -377,   492,   495,  -377,  -377,    32,  -377,   507,  -377,
    -377,  -377,  -377,   451,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,    23,    96,   514,   517,   519,   461,
      91,  -377,  -377,  -377,    91,  -377,   523,  -377,  -377,   -17,
    -377,    27,  -377,   525,  -377,  -377,   526,   527,   216,   101,
     490,   -15,   532,    41,  -377,  -377,   535,   537,   269,  -377,
    -377,  -377,   122,  -377,   539,  -377,  -377,   541,   542,   544,
     550,   551,   176,  -377,   -11,   497,    88,   392,  -377,  -377,
    -377,   392,   467,    91,    27,   557,   558,   559,   502,    64,
    -377,    64,  -377,   563,   490,   564,  -377,  -377,  -377,   318,
     253,   535,  -377,  -377,  -377,   322,   566,   -17,  -377,    64,
    -377,   269,   -26,  -377,    30,  -377,   567,   568,  -377,  -377,
     458,    64,    64,  -377,  -377,  -377,  -377,   569,  -377,  -377,
    -377,   269,  -377,  -377,   306,    91,  -377,  -377,  -377,  -377,
    -377,  -377,    27,   573,   574,   575,    64,   576,   577,   579,
    -377,   218,  -377,  -377,  -377,   580,    26,  -377,   548,    91,
      24,    64,    64,  -377,  -377,  -377,  -377,  -377,   582,    64,
     583,   584,  -377,   585,  -377,   137,   586,  -377,   138,   587,
     493,   582,   588,  -377,  -377,  -377,   278,  -377,  -377,  -377,
     589,   591,  -377,  -377,   592,  -377,  -377,  -377,   594,  -377,
     -28,  -377,  -377,   269,   595,   582,   596,  -377
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     2,     3,     4,     0,     1,     0,     0,
       0,     0,   292,     0,   245,     0,   246,     0,   249,    13,
      43,    91,     0,     0,     0,     0,     5,    14,     6,     7,
       8,     9,    10,    11,    12,     0,    37,    38,    39,    40,
      44,    41,    42,     0,    80,    82,    83,    92,    81,    84,
      85,    86,    87,    88,    89,    90,     0,     0,   288,     0,
       0,     0,   284,     0,     0,    97,     0,     0,     0,     0,
       0,     0,   284,     0,   250,   247,     0,   294,     0,   288,
     293,   217,     0,   216,     0,    20,     0,     0,   271,   259,
     264,   272,   261,   265,   273,   276,   277,   274,   275,   268,
     267,   269,   263,   270,   262,   260,   266,   281,     0,     0,
     202,   284,     0,   251,     0,   252,     0,     0,   286,     0,
       0,   102,     0,     0,   177,   177,   150,   149,     0,   147,
     148,     0,   170,   171,     0,     0,     0,   113,   105,   107,
       0,   255,     0,     0,    27,   248,    15,    22,   289,   218,
      23,   290,   206,    21,    18,     0,     0,     0,   282,    16,
      17,   285,   284,     0,    48,     0,     0,     0,    95,    98,
      94,   287,    93,   200,   103,   100,     0,     0,     0,     0,
       0,   295,     0,   160,     0,     0,   176,     0,   140,   145,
       0,     0,     0,     0,     0,     0,     0,   168,   225,     0,
     104,   114,     0,     0,    99,   290,     0,     0,     0,   204,
     290,     0,     0,     0,     0,   285,   290,     0,     0,   290,
       0,    68,     0,     0,     0,   162,   166,   167,   163,     0,
       0,     0,     0,   151,     0,   146,   226,     0,     0,   210,
     209,   207,   208,     0,     0,     0,     0,     0,     0,     0,
       0,   112,     0,     0,     0,     0,     0,     0,     0,    26,
     184,   185,     0,     0,    19,   291,   290,   280,   279,   278,
     239,   243,   241,   244,   240,   242,   284,   238,   237,     0,
       0,     0,     0,     0,     0,   156,    66,   157,     0,     0,
       0,   101,   201,   198,   199,     0,   152,     0,     0,   144,
       0,   154,   161,   158,   159,   173,   211,   213,   175,   172,
     174,   106,   196,     0,     0,   194,     0,   195,   169,     0,
       0,   109,   110,   111,     0,   108,   257,     0,   256,     0,
     123,   132,   126,   127,     0,     0,    25,     0,     0,     0,
     164,     0,     0,    31,     0,   291,   203,    46,     0,     0,
      53,    49,     0,     0,    65,   283,     0,    67,    74,    69,
      72,    70,    64,     0,   155,   153,   143,   141,   142,   212,
     197,   193,   191,   192,     0,     0,     0,     0,     0,     0,
       0,   117,   258,   122,     0,   223,     0,   215,   214,     0,
     133,     0,   124,   138,   128,   129,     0,     0,     0,     0,
       0,     0,     0,     0,   228,    29,     0,     0,   290,    47,
     228,    54,     0,    50,    59,    55,    56,     0,     0,     0,
       0,     0,     0,    75,     0,     0,     0,     0,   116,   118,
     120,     0,     0,     0,     0,   135,     0,     0,     0,     0,
     139,     0,   121,     0,   187,     0,   186,   189,   165,     0,
       0,    35,    30,    24,   205,     0,     0,     0,    60,     0,
      45,   290,     0,   179,     0,    73,     0,     0,   115,   178,
       0,     0,     0,   136,   130,   131,   181,     0,   190,   188,
     183,     0,    28,   229,     0,     0,   220,   222,   219,   221,
      36,    52,     0,    62,     0,     0,   253,     0,     0,     0,
      77,     0,    96,   119,   224,     0,     0,   125,     0,     0,
       0,     0,     0,    63,    57,    58,   254,    51,     0,     0,
       0,     0,   134,     0,   182,     0,     0,    32,     0,     0,
       0,    78,     0,   180,    76,   137,     0,   234,   231,   230,
       0,   235,   232,    34,     0,    61,    79,    71,     0,   227,
       0,   236,    33,   290,     0,     0,     0,   233
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -377,  -377,  -377,  -377,  -377,  -377,   327,  -377,  -377,  -377,
     499,   342,   581,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
     120,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,  -377,
    -377,   237,  -377,  -377,   182,  -377,   106,  -377,  -377,  -377,
    -377,  -377,  -377,   244,  -275,  -357,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,  -377,  -377,  -377,  -377,   482,  -377,  -377,
     -47,   471,   353,   354,   356,  -377,  -377,  -377,  -377,  -377,
    -377,  -377,  -377,   274,  -377,   175,  -377,   219,  -377,   -64,
    -204,  -345,  -377,  -318,  -377,  -377,  -212,  -377,   359,  -377,
    -377,  -377,  -377,   488,  -319,   108,  -377,  -377,  -189,   171,
     281,  -154,  -217,  -377,  -377,   -57,  -198,   -70,  -116,   310,
     430,   194,  -310,   -62,   135,  -376,  -132,  -230,  -377,   213,
    -377,  -377,    80,   284,  -377,   555,   614,   552,  -377,  -377,
     288,   -56,   129,   439,  -174,  -303,  -377,   524,  -229,   -77,
    -112,   547,  -121,    -9,   -50,  -114,  -103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,    27,    22,    28,    29,    30,    31,    85,
      86,    32,    33,    34,   144,   207,   263,   343,   407,   451,
     452,     4,    40,    23,    41,   164,   218,   282,   353,   418,
     350,   351,   413,   414,   415,   493,   494,    42,   166,   221,
     289,   357,   358,   359,   531,   532,     5,    47,    24,    48,
      49,    50,   169,   116,    51,    52,   121,   122,    53,   136,
     137,   138,   376,   377,   378,    54,   203,   256,   335,   397,
     330,   392,   331,   332,   435,   436,   393,   394,    55,   182,
     297,   129,   130,   286,   302,   234,   224,   403,   225,   252,
     131,   132,   133,   185,   324,   464,   506,   259,   444,   445,
     261,   139,   313,   292,   223,   109,   208,   183,   306,   307,
     238,   385,    81,    82,   485,   386,   239,   240,   483,   449,
     540,   541,   542,   276,   277,    13,    75,    76,    17,    73,
     112,   496,   497,   140,   326,   327,   107,   108,   287,   110,
     117,    78,   209,   152,   227,    79,   210
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    16,    18,   199,   304,   128,   171,   257,   114,    83,
     186,   186,   295,   360,   151,   142,   118,   260,   279,   149,
     184,   283,   303,   382,   405,   291,   333,   374,   300,   527,
     462,    83,   355,   316,   161,   500,   456,   355,   247,   248,
     249,   250,   301,   548,   337,   198,   447,    74,    16,   134,
     173,   198,   499,   111,   113,   115,   427,   420,    14,   361,
     317,     1,   141,   111,   197,    12,    16,   189,   118,   237,
     384,   243,    80,   228,     6,   463,    12,   190,    80,    25,
      26,   456,   242,   360,   242,   215,   320,   196,   190,   265,
     523,   319,   365,   312,   314,   370,   312,   528,   236,   325,
     246,   425,   162,   419,   501,   395,   427,   266,   135,    80,
     290,    12,   191,   229,   230,   231,   232,   420,    12,     7,
     197,   228,     8,   416,   181,   398,    80,   355,    12,   181,
      80,   228,    12,   181,   242,   241,   135,   241,   477,   192,
     242,   536,   123,   196,    80,   345,    12,   135,   193,   400,
     320,   194,   195,   162,   520,    12,   285,   437,   312,   426,
     337,   463,    19,   266,    12,   296,   298,   226,   296,    20,
     381,    21,   118,   294,   546,   510,   197,   190,    77,   339,
      80,   184,   141,   521,   198,    84,   443,   241,   340,    35,
      36,   448,    12,   241,   120,   124,   124,   387,   556,   526,
     125,   125,   143,   242,   146,   278,   380,   126,   126,   384,
     454,    80,   374,   163,   293,   226,   147,   438,   348,   346,
     487,   249,   284,   127,   127,   226,    80,   495,    12,   181,
      83,     9,   296,   150,   228,   154,   135,   159,    10,   192,
     305,   236,   198,   226,   160,   328,    11,   419,   193,   197,
     537,   194,   195,   421,   487,   165,   241,   387,    43,    44,
     471,   420,   170,   498,    12,   438,   537,   111,   181,    80,
     379,   320,   181,   467,   192,   172,   124,   468,   285,   388,
     387,   125,   123,   193,   337,   175,   375,   195,   126,   167,
     168,   338,   387,   410,   188,   228,   198,   505,   471,    12,
     228,    80,    77,   339,   127,    80,   200,    12,   181,   155,
     156,   157,   380,   539,   236,   198,    12,   328,   486,   421,
     202,   470,   481,   482,   204,   387,   481,   491,   226,   340,
     432,   340,   113,   484,   433,   278,   124,   176,   206,   388,
     115,   125,    80,    63,   177,   181,   214,   489,   126,   548,
      37,    45,   486,   178,    64,   554,   179,   180,    56,   205,
      57,   181,   388,   420,   127,    38,    46,   236,   198,    12,
     181,    58,   211,   216,   388,   217,   212,    59,   508,   213,
     219,   489,   328,   118,   220,    61,   222,    58,   233,   226,
     235,    65,    66,    59,   226,    80,   246,    67,   181,    60,
     488,    61,    62,    68,   251,    69,    70,   388,   253,   254,
     255,   123,   355,   236,   198,   192,   309,    58,    71,   258,
     262,    72,   228,   264,   193,   328,   267,   194,   195,   268,
     328,    61,   328,   184,   488,    83,   511,   285,   269,   280,
      12,    80,   288,   281,   181,   299,   123,   308,   310,   311,
     115,   315,   329,   334,   336,   529,   511,   341,   342,    83,
     344,   538,   328,   328,   544,   124,   176,   347,   349,   352,
     125,   354,   356,   177,   362,   364,   363,   126,   366,   367,
     368,   371,   178,   115,   372,   179,   180,   115,   373,   383,
     389,   391,   396,   127,   399,   401,   412,   270,    12,   181,
     124,   176,   115,   115,   271,   125,   409,   406,   177,   272,
     417,   422,   126,   273,   274,   275,   226,   178,   424,   428,
     179,   180,   429,    12,   430,   431,    87,   434,   127,   439,
     441,   469,   442,    12,   181,    88,    89,   446,    90,   450,
      91,    92,   453,   457,    93,   459,   504,   460,   461,    94,
      95,    96,    97,    98,   462,   525,   465,    99,   100,   101,
     426,   472,   102,   474,   475,   476,   103,   104,   478,   480,
     492,   490,   502,   503,   507,   105,   106,   512,   420,   514,
     515,   517,   518,   519,   153,   522,   530,   411,   533,   534,
     535,   543,   545,   547,   549,   550,   458,   552,   553,   513,
     555,   557,   423,   174,    39,   390,   321,   322,   201,   323,
     473,   318,   440,   187,   524,   479,   369,   244,   466,   509,
     402,   551,   119,   455,    15,   516,   148,   145,   408,   404,
     245,   158
};

static const yytype_int16 yycheck[] =
{
       9,    10,    11,   135,   234,    69,   118,   205,    64,    59,
     124,   125,   224,   288,    84,    72,    66,   206,   216,    81,
     123,   219,   234,   326,   342,     5,   255,     4,   232,     5,
       4,    81,     5,   250,   111,     5,   412,     5,   192,   193,
     194,   195,     5,    71,    59,    62,     5,    56,    57,     4,
     120,    62,    78,    62,    63,    64,   375,    85,    67,   288,
       5,     4,    71,    72,   134,    91,    75,   131,   118,   185,
      87,   187,    89,   176,    68,   420,    91,     4,    89,     4,
       5,   457,   185,   358,   187,   162,    63,   134,     4,   210,
      64,     4,   296,   247,   248,   312,   250,    73,    61,   253,
       4,    78,   111,    71,    74,   334,   425,   210,    63,    89,
     222,    91,    39,   177,   178,   179,   180,    85,    91,     0,
     190,   224,     4,   352,    92,   337,    89,     5,    91,    92,
      89,   234,    91,    92,   237,   185,    63,   187,   441,    66,
     243,     4,     4,   190,    89,   266,    91,    63,    75,   338,
      63,    78,    79,   162,   499,    91,   220,   386,   312,    63,
      59,   506,     5,   266,    91,   229,   230,   176,   232,     5,
     324,     5,   222,   223,   531,   485,   246,     4,    90,    78,
      89,   284,   191,   501,    62,     4,   398,   237,   258,     4,
       5,   403,    91,   243,     4,    58,    58,   329,   555,   509,
      63,    63,    46,   306,     5,   214,   320,    70,    70,    87,
     408,    89,     4,    46,   223,   224,     5,   391,   280,   276,
     450,   375,     4,    86,    86,   234,    89,   456,    91,    92,
     280,    69,   296,     5,   337,     5,    63,     5,    76,    66,
      60,    61,    62,   252,     5,   254,    84,    71,    75,   319,
     525,    78,    79,   356,   484,    46,   306,   389,     4,     5,
     434,    85,     5,   461,    91,   439,   541,   276,    92,    89,
     320,    63,    92,   427,    66,     5,    58,   431,   342,   329,
     412,    63,     4,    75,    59,     5,    78,    79,    70,     4,
       5,    66,   424,   349,     5,   398,    62,   471,   472,    91,
     403,    89,    90,    78,    86,    89,     5,    91,    92,    32,
      33,    34,   426,   525,    61,    62,    91,   326,   450,   422,
      57,   433,     4,     5,     5,   457,     4,     5,   337,   399,
     380,   401,   341,    80,   384,   344,    58,    59,    56,   389,
     349,    63,    89,     9,    66,    92,     6,   450,    70,    71,
      23,    24,   484,    75,    20,   553,    78,    79,     8,     4,
      10,    92,   412,    85,    86,    23,    24,    61,    62,    91,
      92,    37,    93,     4,   424,    24,    93,    43,   481,    93,
       4,   484,   391,   433,    48,    51,    87,    37,     5,   398,
       5,    11,    12,    43,   403,    89,     4,    17,    92,    49,
     450,    51,    52,    23,     5,    25,    26,   457,    64,     4,
      50,     4,     5,    61,    62,    66,    64,    37,    38,     4,
       9,    41,   525,     5,    75,   434,     5,    78,    79,     5,
     439,    51,   441,   536,   484,   485,   492,   501,     5,     4,
      91,    89,    47,    21,    92,     5,     4,    60,    64,     5,
     459,     5,     4,    55,     5,   511,   512,     4,    48,   509,
       6,   525,   471,   472,   528,    58,    59,     5,     4,    50,
      63,     5,     4,    66,     5,     5,    88,    70,     5,     5,
       5,     5,    75,   492,     5,    78,    79,   496,     5,     5,
       4,     4,    15,    86,     4,     4,     4,    65,    91,    92,
      58,    59,   511,   512,    72,    63,     5,    42,    66,    77,
      15,     4,    70,    81,    82,    83,   525,    75,    67,     5,
      78,    79,     5,    91,     5,    64,     4,     4,    86,     4,
       4,    64,     5,    91,    92,    13,    14,     5,    16,     4,
      18,    19,     5,     4,    22,     4,    88,     5,     4,    27,
      28,    29,    30,    31,     4,     7,     5,    35,    36,    37,
      63,     4,    40,     5,     5,    63,    44,    45,     5,     5,
       4,   451,     5,     5,     5,    53,    54,     4,    85,     5,
       5,     5,     5,     4,    85,     5,     4,   350,     5,     5,
       5,     5,     5,     5,     5,     4,   414,     5,     4,   493,
       5,     5,   358,   121,    23,   331,   253,   253,   137,   253,
     435,   252,   393,   125,   506,   444,   306,   187,   424,   484,
     339,   541,    67,   410,    10,   496,    79,    75,   344,   341,
     191,   107
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    95,    96,   115,   140,    68,     0,     4,    69,
      76,    84,    91,   219,   237,   220,   237,   222,   237,     5,
       5,     5,    98,   117,   142,     4,     5,    97,    99,   100,
     101,   102,   105,   106,   107,     4,     5,   100,   105,   106,
     116,   118,   131,     4,     5,   100,   105,   141,   143,   144,
     145,   148,   149,   152,   159,   172,     8,    10,    37,    43,
      49,    51,    52,     9,    20,    11,    12,    17,    23,    25,
      26,    38,    41,   223,   237,   220,   221,    90,   235,   239,
      89,   206,   207,   238,     4,   103,   104,     4,    13,    14,
      16,    18,    19,    22,    27,    28,    29,    30,    31,    35,
      36,    37,    40,    44,    45,    53,    54,   230,   231,   199,
     233,   237,   224,   237,   225,   237,   147,   234,   238,   219,
       4,   150,   151,     4,    58,    63,    70,    86,   173,   175,
     176,   184,   185,   186,     4,    63,   153,   154,   155,   195,
     227,   237,   199,    46,   108,   221,     5,     5,   235,   207,
       5,   201,   237,   104,     5,    32,    33,    34,   231,     5,
       5,   233,   237,    46,   119,    46,   132,     4,     5,   146,
       5,   234,     5,   201,   151,     5,    59,    66,    75,    78,
      79,    92,   173,   201,   240,   187,   239,   187,     5,   173,
       4,    39,    66,    75,    78,    79,   154,   201,    62,   210,
       5,   155,    57,   160,     5,     4,    56,   109,   200,   236,
     240,    93,    93,    93,     6,   233,     4,    24,   120,     4,
      48,   133,    87,   198,   180,   182,   237,   238,   240,   173,
     173,   173,   173,     5,   179,     5,    61,   202,   204,   210,
     211,   238,   240,   202,   204,   227,     4,   195,   195,   195,
     195,     5,   183,    64,     4,    50,   161,   200,     4,   191,
     192,   194,     9,   110,     5,   236,   240,     5,     5,     5,
      65,    72,    77,    81,    82,    83,   217,   218,   237,   200,
       4,    21,   121,   200,     4,   173,   177,   232,    47,   134,
     234,     5,   197,   237,   238,   180,   173,   174,   173,     5,
     174,     5,   178,   180,   211,    60,   202,   203,    60,    64,
      64,     5,   195,   196,   195,     5,   196,     5,   182,     4,
      63,   156,   157,   158,   188,   195,   228,   229,   237,     4,
     164,   166,   167,   232,    55,   162,     5,    59,    66,    78,
     201,     4,    48,   111,     6,   236,   199,     5,   207,     4,
     124,   125,    50,   122,     5,     5,     4,   135,   136,   137,
     138,   232,     5,    88,     5,   174,     5,     5,     5,   203,
     196,     5,     5,     5,     4,    78,   156,   157,   158,   238,
     239,   195,   229,     5,    87,   205,   209,   210,   238,     4,
     167,     4,   165,   170,   171,   232,    15,   163,   180,     4,
     192,     4,   194,   181,   224,   177,    42,   112,   217,     5,
     225,   125,     4,   126,   127,   128,   232,    15,   123,    71,
      85,   240,     4,   137,    67,    78,    63,   188,     5,     5,
       5,    64,   238,   238,     4,   168,   169,   232,   228,     4,
     171,     4,     5,   180,   192,   193,     5,     5,   180,   213,
       4,   113,   114,     5,   200,   213,   209,     4,   128,     4,
       5,     4,     4,   175,   189,     5,   205,   195,   195,    64,
     234,   228,     4,   169,     5,     5,    63,   229,     5,   193,
       5,     4,     5,   212,    80,   208,   210,   211,   238,   240,
     114,     5,     4,   129,   130,   232,   225,   226,   200,    78,
       5,    74,     5,     5,    88,   228,   190,     5,   240,   208,
     206,   225,     4,   130,     5,     5,   226,     5,     5,     4,
     175,   177,     5,    64,   189,     7,   206,     5,    73,   225,
       4,   138,   139,     5,     5,     5,     4,   138,   173,   180,
     214,   215,   216,     5,   173,     5,   139,     5,    71,     5,
       4,   216,     5,     4,   200,     5,   139,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    95,    96,    97,    97,    97,    97,
      97,    97,    97,    98,    98,    99,   100,   101,   102,   103,
     104,   104,   105,   106,   107,   108,   109,   109,   110,   111,
     112,   112,   113,   113,   113,   114,   114,   115,   116,   116,
     116,   116,   116,   117,   117,   118,   119,   120,   120,   121,
     122,   123,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   130,   130,   131,   132,   133,   134,   134,   135,
     135,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   142,   142,   143,   144,   145,   146,   147,   147,   148,
     149,   150,   151,   151,   152,   153,   153,   154,   154,   154,
     154,   154,   154,   155,   155,   156,   156,   157,   157,   158,
     158,   159,   160,   161,   162,   163,   164,   164,   165,   165,
     166,   166,   167,   167,   168,   169,   169,   170,   171,   171,
     172,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   174,   174,   175,   176,   177,   177,   178,   178,
     179,   179,   180,   180,   181,   181,   182,   182,   183,   183,
     184,   184,   185,   185,   186,   186,   187,   187,   188,   189,
     189,   190,   190,   191,   191,   192,   192,   193,   193,   194,
     194,   195,   195,   195,   195,   195,   196,   196,   197,   197,
     198,   198,   199,   199,   200,   200,   201,   202,   202,   202,
     202,   203,   203,   204,   205,   205,   206,   207,   207,   208,
     208,   208,   208,   209,   209,   210,   211,   212,   213,   213,
     214,   214,   214,   215,   215,   216,   216,   217,   217,   218,
     218,   218,   218,   218,   218,   219,   220,   221,   221,   222,
     223,   224,   225,   226,   226,   227,   228,   229,   229,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   231,   231,   232,   233,   233,   234,   234,   235,   235,
     236,   236,   237,   238,   239,   240
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     8,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     4,     4,     4,     4,     4,
       1,     2,     4,     4,     9,     4,     2,     0,     5,     2,
       2,     0,     4,     6,     5,     1,     2,     8,     1,     1,
       1,     1,     1,     0,     2,     9,     4,     4,     0,     2,
       2,     4,     4,     1,     2,     1,     1,     4,     4,     1,
       2,     4,     1,     2,     7,     4,     2,     2,     0,     1,
       1,     7,     1,     3,     1,     2,     6,     4,     1,     2,
       8,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     4,     4,     4,     7,     0,     2,     4,
       4,     4,     1,     2,     4,     1,     4,     1,     4,     4,
       4,     4,     3,     1,     2,     4,     3,     2,     3,     5,
       3,     8,     4,     2,     2,     4,     1,     1,     1,     1,
       4,     4,     1,     2,     4,     1,     2,     6,     1,     2,
       4,     5,     5,     5,     4,     2,     3,     1,     1,     1,
       1,     3,     1,     2,     4,     5,     1,     1,     1,     1,
       0,     2,     1,     1,     0,     2,     1,     1,     0,     2,
       1,     1,     4,     4,     4,     4,     1,     0,     4,     1,
       4,     0,     2,     5,     1,     1,     4,     1,     2,     4,
       5,     5,     5,     5,     4,     4,     1,     2,     1,     1,
       0,     2,     1,     5,     1,     5,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     4,     1,     1,     5,     0,     2,
       1,     1,     1,     7,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     1,     2,     2,     0,     2,     1,     2,     0,     2,
       0,     2,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, result, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, result); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, result);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner, YYSTYPE *result)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, result);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, result); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, YYSTYPE *result)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* MainDef: DomainDef  */
#line 458 "epddl.y"
                    { (yyval.maindef_) = new Domain((yyvsp[0].domaindef_)); result->maindef_ = (yyval.maindef_); }
#line 1931 "Parser.C"
    break;

  case 3: /* MainDef: LibraryDef  */
#line 459 "epddl.y"
               { (yyval.maindef_) = new ActionTypeLibrary((yyvsp[0].librarydef_)); result->maindef_ = (yyval.maindef_); }
#line 1937 "Parser.C"
    break;

  case 4: /* MainDef: ProblemDef  */
#line 460 "epddl.y"
               { (yyval.maindef_) = new Problem((yyvsp[0].problemdef_)); result->maindef_ = (yyval.maindef_); }
#line 1943 "Parser.C"
    break;

  case 5: /* DomainDef: _LPAREN _KW_define _LPAREN _KW_domain DomainName _RPAREN ListDomainItemDef _RPAREN  */
#line 462 "epddl.y"
                                                                                               { (yyval.domaindef_) = new EPDDLDomain((yyvsp[-3].domainname_), (yyvsp[-1].listdomainitemdef_)); }
#line 1949 "Parser.C"
    break;

  case 6: /* DomainItemDef: DomainLibrariesNameDef  */
#line 464 "epddl.y"
                                       { (yyval.domainitemdef_) = new EPDDLDomLibrary((yyvsp[0].domainlibrariesnamedef_)); }
#line 1955 "Parser.C"
    break;

  case 7: /* DomainItemDef: RequireDef  */
#line 465 "epddl.y"
               { (yyval.domainitemdef_) = new EPDDLDomRequire((yyvsp[0].requiredef_)); }
#line 1961 "Parser.C"
    break;

  case 8: /* DomainItemDef: TypesDef  */
#line 466 "epddl.y"
             { (yyval.domainitemdef_) = new EPDDLDomTypes((yyvsp[0].typesdef_)); }
#line 1967 "Parser.C"
    break;

  case 9: /* DomainItemDef: PredicateListDef  */
#line 467 "epddl.y"
                     { (yyval.domainitemdef_) = new EPDDLDomPredicates((yyvsp[0].predicatelistdef_)); }
#line 1973 "Parser.C"
    break;

  case 10: /* DomainItemDef: ModalitiesDef  */
#line 468 "epddl.y"
                  { (yyval.domainitemdef_) = new EPDDLDomModalities((yyvsp[0].modalitiesdef_)); }
#line 1979 "Parser.C"
    break;

  case 11: /* DomainItemDef: ObservabilityGroupsDef  */
#line 469 "epddl.y"
                           { (yyval.domainitemdef_) = new EPDDLDomObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 1985 "Parser.C"
    break;

  case 12: /* DomainItemDef: ActionDef  */
#line 470 "epddl.y"
              { (yyval.domainitemdef_) = new EPDDLDomAction((yyvsp[0].actiondef_)); }
#line 1991 "Parser.C"
    break;

  case 13: /* ListDomainItemDef: %empty  */
#line 472 "epddl.y"
                                { (yyval.listdomainitemdef_) = new ListDomainItemDef(); }
#line 1997 "Parser.C"
    break;

  case 14: /* ListDomainItemDef: ListDomainItemDef DomainItemDef  */
#line 473 "epddl.y"
                                    { (yyvsp[-1].listdomainitemdef_)->push_back((yyvsp[0].domainitemdef_)); (yyval.listdomainitemdef_) = (yyvsp[-1].listdomainitemdef_); }
#line 2003 "Parser.C"
    break;

  case 15: /* DomainLibrariesNameDef: _LPAREN _SYMB_2 ListLibraryName _RPAREN  */
#line 475 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listlibraryname_)->begin(),(yyvsp[-1].listlibraryname_)->end()) ;(yyval.domainlibrariesnamedef_) = new EPDDLDomLibraryNames((yyvsp[-1].listlibraryname_)); }
#line 2009 "Parser.C"
    break;

  case 16: /* RequireDef: _LPAREN _SYMB_3 ListRequireKey _RPAREN  */
#line 477 "epddl.y"
                                                    { std::reverse((yyvsp[-1].listrequirekey_)->begin(),(yyvsp[-1].listrequirekey_)->end()) ;(yyval.requiredef_) = new EPDDLRequire((yyvsp[-1].listrequirekey_)); }
#line 2015 "Parser.C"
    break;

  case 17: /* TypesDef: _LPAREN _SYMB_4 TypedIdentList _RPAREN  */
#line 479 "epddl.y"
                                                  { (yyval.typesdef_) = new EPDDLTypes((yyvsp[-1].typedidentlist_)); }
#line 2021 "Parser.C"
    break;

  case 18: /* PredicateListDef: _LPAREN _SYMB_5 ListPredicateDef _RPAREN  */
#line 481 "epddl.y"
                                                            { std::reverse((yyvsp[-1].listpredicatedef_)->begin(),(yyvsp[-1].listpredicatedef_)->end()) ;(yyval.predicatelistdef_) = new EPDDLPredicateList((yyvsp[-1].listpredicatedef_)); }
#line 2027 "Parser.C"
    break;

  case 19: /* PredicateDef: _LPAREN PredicateName TypedVariableList _RPAREN  */
#line 483 "epddl.y"
                                                               { (yyval.predicatedef_) = new EPDDLPredicateDef((yyvsp[-2].predicatename_), (yyvsp[-1].typedvariablelist_)); }
#line 2033 "Parser.C"
    break;

  case 20: /* ListPredicateDef: PredicateDef  */
#line 485 "epddl.y"
                                { (yyval.listpredicatedef_) = new ListPredicateDef(); (yyval.listpredicatedef_)->push_back((yyvsp[0].predicatedef_)); }
#line 2039 "Parser.C"
    break;

  case 21: /* ListPredicateDef: PredicateDef ListPredicateDef  */
#line 486 "epddl.y"
                                  { (yyvsp[0].listpredicatedef_)->push_back((yyvsp[-1].predicatedef_)); (yyval.listpredicatedef_) = (yyvsp[0].listpredicatedef_); }
#line 2045 "Parser.C"
    break;

  case 22: /* ModalitiesDef: _LPAREN _SYMB_6 ListModalityName _RPAREN  */
#line 488 "epddl.y"
                                                         { std::reverse((yyvsp[-1].listmodalityname_)->begin(),(yyvsp[-1].listmodalityname_)->end()) ;(yyval.modalitiesdef_) = new EPDDLModalities((yyvsp[-1].listmodalityname_)); }
#line 2051 "Parser.C"
    break;

  case 23: /* ObservabilityGroupsDef: _LPAREN _SYMB_7 ListObservingAgentGroup _RPAREN  */
#line 490 "epddl.y"
                                                                         { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.observabilitygroupsdef_) = new EPDDLObsGroupsNames((yyvsp[-1].listobservingagentgroup_)); }
#line 2057 "Parser.C"
    break;

  case 24: /* ActionDef: _LPAREN _SYMB_8 ActionName ActionParameterDef ActionConditionsDef ActionTypeSignatureDef ActionPreDef ActionObsDef _RPAREN  */
#line 492 "epddl.y"
                                                                                                                                       { (yyval.actiondef_) = new EPDDLAction((yyvsp[-6].actionname_), (yyvsp[-5].actionparameterdef_), (yyvsp[-4].actionconditionsdef_), (yyvsp[-3].actiontypesignaturedef_), (yyvsp[-2].actionpredef_), (yyvsp[-1].actionobsdef_)); }
#line 2063 "Parser.C"
    break;

  case 25: /* ActionParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 494 "epddl.y"
                                                               { (yyval.actionparameterdef_) = new ActionParam((yyvsp[-1].typedvariablelist_)); }
#line 2069 "Parser.C"
    break;

  case 26: /* ActionConditionsDef: _SYMB_10 ConditionFormula  */
#line 496 "epddl.y"
                                                { (yyval.actionconditionsdef_) = new ActionCond((yyvsp[0].conditionformula_)); }
#line 2075 "Parser.C"
    break;

  case 27: /* ActionConditionsDef: %empty  */
#line 497 "epddl.y"
                { (yyval.actionconditionsdef_) = new EmptyActionCond(); }
#line 2081 "Parser.C"
    break;

  case 28: /* ActionTypeSignatureDef: _SYMB_11 _LPAREN ActionTypeName ListParameter _RPAREN  */
#line 499 "epddl.y"
                                                                               { (yyval.actiontypesignaturedef_) = new ActionSignature((yyvsp[-2].actiontypename_), (yyvsp[-1].listparameter_)); }
#line 2087 "Parser.C"
    break;

  case 29: /* ActionPreDef: _SYMB_12 FormulaOrEmpty  */
#line 501 "epddl.y"
                                       { (yyval.actionpredef_) = new ActionPre((yyvsp[0].formulaorempty_)); }
#line 2093 "Parser.C"
    break;

  case 30: /* ActionObsDef: _SYMB_13 ListObsConditionDef  */
#line 503 "epddl.y"
                                            { std::reverse((yyvsp[0].listobsconditiondef_)->begin(),(yyvsp[0].listobsconditiondef_)->end()) ;(yyval.actionobsdef_) = new ActionObs((yyvsp[0].listobsconditiondef_)); }
#line 2099 "Parser.C"
    break;

  case 31: /* ActionObsDef: %empty  */
#line 504 "epddl.y"
                { (yyval.actionobsdef_) = new EmptyActionObs(); }
#line 2105 "Parser.C"
    break;

  case 32: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _RPAREN  */
#line 506 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new EmptyObsCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2111 "Parser.C"
    break;

  case 33: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _KW_if Formula _RPAREN  */
#line 507 "epddl.y"
                                                                      { (yyval.obsconditiondef_) = new ObsCond((yyvsp[-4].observingagent_), (yyvsp[-3].observingagentgroup_), (yyvsp[-1].formula_)); }
#line 2117 "Parser.C"
    break;

  case 34: /* ObsConditionDef: _LPAREN _KW_otherwise ObservingAgent ObservingAgentGroup _RPAREN  */
#line 508 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new ObsOtherwiseCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2123 "Parser.C"
    break;

  case 35: /* ListObsConditionDef: ObsConditionDef  */
#line 510 "epddl.y"
                                      { (yyval.listobsconditiondef_) = new ListObsConditionDef(); (yyval.listobsconditiondef_)->push_back((yyvsp[0].obsconditiondef_)); }
#line 2129 "Parser.C"
    break;

  case 36: /* ListObsConditionDef: ObsConditionDef ListObsConditionDef  */
#line 511 "epddl.y"
                                        { (yyvsp[0].listobsconditiondef_)->push_back((yyvsp[-1].obsconditiondef_)); (yyval.listobsconditiondef_) = (yyvsp[0].listobsconditiondef_); }
#line 2135 "Parser.C"
    break;

  case 37: /* LibraryDef: _LPAREN _KW_define _LPAREN _KW_library LibraryName _RPAREN ListLibraryItemDef _RPAREN  */
#line 513 "epddl.y"
                                                                                                   { (yyval.librarydef_) = new EPDDLLibrary((yyvsp[-3].libraryname_), (yyvsp[-1].listlibraryitemdef_)); }
#line 2141 "Parser.C"
    break;

  case 38: /* LibraryItemDef: RequireDef  */
#line 515 "epddl.y"
                            { (yyval.libraryitemdef_) = new EPDDLLibRequire((yyvsp[0].requiredef_)); }
#line 2147 "Parser.C"
    break;

  case 39: /* LibraryItemDef: ModalitiesDef  */
#line 516 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibModalities((yyvsp[0].modalitiesdef_)); }
#line 2153 "Parser.C"
    break;

  case 40: /* LibraryItemDef: ObservabilityGroupsDef  */
#line 517 "epddl.y"
                           { (yyval.libraryitemdef_) = new EPDDLLibObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 2159 "Parser.C"
    break;

  case 41: /* LibraryItemDef: ActionTypeDef  */
#line 518 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibActionType((yyvsp[0].actiontypedef_)); }
#line 2165 "Parser.C"
    break;

  case 42: /* LibraryItemDef: EventDef  */
#line 519 "epddl.y"
             { (yyval.libraryitemdef_) = new EPDDLLibEvent((yyvsp[0].eventdef_)); }
#line 2171 "Parser.C"
    break;

  case 43: /* ListLibraryItemDef: %empty  */
#line 521 "epddl.y"
                                 { (yyval.listlibraryitemdef_) = new ListLibraryItemDef(); }
#line 2177 "Parser.C"
    break;

  case 44: /* ListLibraryItemDef: ListLibraryItemDef LibraryItemDef  */
#line 522 "epddl.y"
                                      { (yyvsp[-1].listlibraryitemdef_)->push_back((yyvsp[0].libraryitemdef_)); (yyval.listlibraryitemdef_) = (yyvsp[-1].listlibraryitemdef_); }
#line 2183 "Parser.C"
    break;

  case 45: /* ActionTypeDef: _LPAREN _SYMB_11 ActionTypeName ActionTypeParameterDef ActionTypeFrameDef ActionTypeEventsDef ActionTypeRelDef ActionTypeDesDef _RPAREN  */
#line 524 "epddl.y"
                                                                                                                                                        { (yyval.actiontypedef_) = new EPDDLActType((yyvsp[-6].actiontypename_), (yyvsp[-5].actiontypeparameterdef_), (yyvsp[-4].actiontypeframedef_), (yyvsp[-3].actiontypeeventsdef_), (yyvsp[-2].actiontypereldef_), (yyvsp[-1].actiontypedesdef_)); }
#line 2189 "Parser.C"
    break;

  case 46: /* ActionTypeParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 526 "epddl.y"
                                                                   { (yyval.actiontypeparameterdef_) = new ActTypeParam((yyvsp[-1].typedvariablelist_)); }
#line 2195 "Parser.C"
    break;

  case 47: /* ActionTypeFrameDef: _SYMB_14 _LPAREN ListObservingAgentGroup _RPAREN  */
#line 528 "epddl.y"
                                                                      { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.actiontypeframedef_) = new ActTypeFrame((yyvsp[-1].listobservingagentgroup_)); }
#line 2201 "Parser.C"
    break;

  case 48: /* ActionTypeFrameDef: %empty  */
#line 529 "epddl.y"
                { (yyval.actiontypeframedef_) = new EmptyActTypeFrame(); }
#line 2207 "Parser.C"
    break;

  case 49: /* ActionTypeEventsDef: _SYMB_15 ListEventSignature  */
#line 531 "epddl.y"
                                                  { std::reverse((yyvsp[0].listeventsignature_)->begin(),(yyvsp[0].listeventsignature_)->end()) ;(yyval.actiontypeeventsdef_) = new ActTypeEvents((yyvsp[0].listeventsignature_)); }
#line 2213 "Parser.C"
    break;

  case 50: /* ActionTypeRelDef: _SYMB_16 ActionRelations  */
#line 533 "epddl.y"
                                            { (yyval.actiontypereldef_) = new ActTypeRel((yyvsp[0].actionrelations_)); }
#line 2219 "Parser.C"
    break;

  case 51: /* ActionTypeDesDef: _SYMB_17 _LPAREN ListEventName _RPAREN  */
#line 535 "epddl.y"
                                                          { std::reverse((yyvsp[-1].listeventname_)->begin(),(yyvsp[-1].listeventname_)->end()) ;(yyval.actiontypedesdef_) = new ActTypeDes((yyvsp[-1].listeventname_)); }
#line 2225 "Parser.C"
    break;

  case 52: /* EventSignature: _LPAREN EventName ListParameter _RPAREN  */
#line 537 "epddl.y"
                                                         { (yyval.eventsignature_) = new EventSign((yyvsp[-2].eventname_), (yyvsp[-1].listparameter_)); }
#line 2231 "Parser.C"
    break;

  case 53: /* ListEventSignature: EventSignature  */
#line 539 "epddl.y"
                                    { (yyval.listeventsignature_) = new ListEventSignature(); (yyval.listeventsignature_)->push_back((yyvsp[0].eventsignature_)); }
#line 2237 "Parser.C"
    break;

  case 54: /* ListEventSignature: EventSignature ListEventSignature  */
#line 540 "epddl.y"
                                      { (yyvsp[0].listeventsignature_)->push_back((yyvsp[-1].eventsignature_)); (yyval.listeventsignature_) = (yyvsp[0].listeventsignature_); }
#line 2243 "Parser.C"
    break;

  case 55: /* ActionRelations: ListEventRelation  */
#line 542 "epddl.y"
                                    { std::reverse((yyvsp[0].listeventrelation_)->begin(),(yyvsp[0].listeventrelation_)->end()) ;(yyval.actionrelations_) = new EventsActionRel((yyvsp[0].listeventrelation_)); }
#line 2249 "Parser.C"
    break;

  case 56: /* ActionRelations: TrivialDef  */
#line 543 "epddl.y"
               { (yyval.actionrelations_) = new TrivialActionRel((yyvsp[0].trivialdef_)); }
#line 2255 "Parser.C"
    break;

  case 57: /* EventRelation: _LPAREN AgentGroup ListEventNamePair _RPAREN  */
#line 545 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listeventnamepair_)->begin(),(yyvsp[-1].listeventnamepair_)->end()) ;(yyval.eventrelation_) = new EventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listeventnamepair_)); }
#line 2261 "Parser.C"
    break;

  case 58: /* EventRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 546 "epddl.y"
                                          { (yyval.eventrelation_) = new TrivialEventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2267 "Parser.C"
    break;

  case 59: /* ListEventRelation: EventRelation  */
#line 548 "epddl.y"
                                  { (yyval.listeventrelation_) = new ListEventRelation(); (yyval.listeventrelation_)->push_back((yyvsp[0].eventrelation_)); }
#line 2273 "Parser.C"
    break;

  case 60: /* ListEventRelation: EventRelation ListEventRelation  */
#line 549 "epddl.y"
                                    { (yyvsp[0].listeventrelation_)->push_back((yyvsp[-1].eventrelation_)); (yyval.listeventrelation_) = (yyvsp[0].listeventrelation_); }
#line 2279 "Parser.C"
    break;

  case 61: /* EventNamePair: _LPAREN EventName EventName _RPAREN  */
#line 551 "epddl.y"
                                                    { (yyval.eventnamepair_) = new EventPair((yyvsp[-2].eventname_), (yyvsp[-1].eventname_)); }
#line 2285 "Parser.C"
    break;

  case 62: /* ListEventNamePair: EventNamePair  */
#line 553 "epddl.y"
                                  { (yyval.listeventnamepair_) = new ListEventNamePair(); (yyval.listeventnamepair_)->push_back((yyvsp[0].eventnamepair_)); }
#line 2291 "Parser.C"
    break;

  case 63: /* ListEventNamePair: EventNamePair ListEventNamePair  */
#line 554 "epddl.y"
                                    { (yyvsp[0].listeventnamepair_)->push_back((yyvsp[-1].eventnamepair_)); (yyval.listeventnamepair_) = (yyvsp[0].listeventnamepair_); }
#line 2297 "Parser.C"
    break;

  case 64: /* EventDef: _LPAREN _SYMB_18 EventName EventParameterDef EventPreDef EventPostDef _RPAREN  */
#line 556 "epddl.y"
                                                                                         { (yyval.eventdef_) = new EPDDLEvent((yyvsp[-4].eventname_), (yyvsp[-3].eventparameterdef_), (yyvsp[-2].eventpredef_), (yyvsp[-1].eventpostdef_)); }
#line 2303 "Parser.C"
    break;

  case 65: /* EventParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 558 "epddl.y"
                                                              { (yyval.eventparameterdef_) = new EventParam((yyvsp[-1].typedvariablelist_)); }
#line 2309 "Parser.C"
    break;

  case 66: /* EventPreDef: _SYMB_12 FormulaOrEmpty  */
#line 560 "epddl.y"
                                      { (yyval.eventpredef_) = new EventPre((yyvsp[0].formulaorempty_)); }
#line 2315 "Parser.C"
    break;

  case 67: /* EventPostDef: _SYMB_19 EventPostconditions  */
#line 562 "epddl.y"
                                            { (yyval.eventpostdef_) = new EventPost((yyvsp[0].eventpostconditions_)); }
#line 2321 "Parser.C"
    break;

  case 68: /* EventPostDef: %empty  */
#line 563 "epddl.y"
                { (yyval.eventpostdef_) = new EmptyEventPost(); }
#line 2327 "Parser.C"
    break;

  case 69: /* EventPostconditions: ListPostcondition  */
#line 565 "epddl.y"
                                        { std::reverse((yyvsp[0].listpostcondition_)->begin(),(yyvsp[0].listpostcondition_)->end()) ;(yyval.eventpostconditions_) = new Postconditions((yyvsp[0].listpostcondition_)); }
#line 2333 "Parser.C"
    break;

  case 70: /* EventPostconditions: TrivialDef  */
#line 566 "epddl.y"
               { (yyval.eventpostconditions_) = new TrivialPostconditions((yyvsp[0].trivialdef_)); }
#line 2339 "Parser.C"
    break;

  case 71: /* Postcondition: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN ListLiteralPostcondition _RPAREN  */
#line 568 "epddl.y"
                                                                                                      { std::reverse((yyvsp[-1].listliteralpostcondition_)->begin(),(yyvsp[-1].listliteralpostcondition_)->end()) ;(yyval.postcondition_) = new ForallPostcondition((yyvsp[-3].typedvariablelist_), (yyvsp[-1].listliteralpostcondition_)); }
#line 2345 "Parser.C"
    break;

  case 72: /* Postcondition: LiteralPostcondition  */
#line 569 "epddl.y"
                         { (yyval.postcondition_) = new SinglePostcondition((yyvsp[0].literalpostcondition_)); }
#line 2351 "Parser.C"
    break;

  case 73: /* Postcondition: _LPAREN Variable _RPAREN  */
#line 570 "epddl.y"
                             { (yyval.postcondition_) = new VarPostcondition((yyvsp[-1]._variable)); }
#line 2357 "Parser.C"
    break;

  case 74: /* ListPostcondition: Postcondition  */
#line 572 "epddl.y"
                                  { (yyval.listpostcondition_) = new ListPostcondition(); (yyval.listpostcondition_)->push_back((yyvsp[0].postcondition_)); }
#line 2363 "Parser.C"
    break;

  case 75: /* ListPostcondition: Postcondition ListPostcondition  */
#line 573 "epddl.y"
                                    { (yyvsp[0].listpostcondition_)->push_back((yyvsp[-1].postcondition_)); (yyval.listpostcondition_) = (yyvsp[0].listpostcondition_); }
#line 2369 "Parser.C"
    break;

  case 76: /* LiteralPostcondition: _LPAREN _KW_set Literal _KW_iff FormulaOrEmpty _RPAREN  */
#line 575 "epddl.y"
                                                                              { (yyval.literalpostcondition_) = new LiteralPost((yyvsp[-3].literal_), (yyvsp[-1].formulaorempty_)); }
#line 2375 "Parser.C"
    break;

  case 77: /* LiteralPostcondition: _LPAREN _KW_set Literal _RPAREN  */
#line 576 "epddl.y"
                                    { (yyval.literalpostcondition_) = new TrivialLiteralPost((yyvsp[-1].literal_)); }
#line 2381 "Parser.C"
    break;

  case 78: /* ListLiteralPostcondition: LiteralPostcondition  */
#line 578 "epddl.y"
                                                { (yyval.listliteralpostcondition_) = new ListLiteralPostcondition(); (yyval.listliteralpostcondition_)->push_back((yyvsp[0].literalpostcondition_)); }
#line 2387 "Parser.C"
    break;

  case 79: /* ListLiteralPostcondition: LiteralPostcondition ListLiteralPostcondition  */
#line 579 "epddl.y"
                                                  { (yyvsp[0].listliteralpostcondition_)->push_back((yyvsp[-1].literalpostcondition_)); (yyval.listliteralpostcondition_) = (yyvsp[0].listliteralpostcondition_); }
#line 2393 "Parser.C"
    break;

  case 80: /* ProblemDef: _LPAREN _KW_define _LPAREN _KW_problem ProblemName _RPAREN ListProblemItemDef _RPAREN  */
#line 581 "epddl.y"
                                                                                                   { (yyval.problemdef_) = new EPDDLProblem((yyvsp[-3].problemname_), (yyvsp[-1].listproblemitemdef_)); }
#line 2399 "Parser.C"
    break;

  case 81: /* ProblemItemDef: ProblemDomainNameDef  */
#line 583 "epddl.y"
                                      { (yyval.problemitemdef_) = new EPDDLProbDomain((yyvsp[0].problemdomainnamedef_)); }
#line 2405 "Parser.C"
    break;

  case 82: /* ProblemItemDef: RequireDef  */
#line 584 "epddl.y"
               { (yyval.problemitemdef_) = new EPDDLProbRequire((yyvsp[0].requiredef_)); }
#line 2411 "Parser.C"
    break;

  case 83: /* ProblemItemDef: ModalitiesDef  */
#line 585 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbModalities((yyvsp[0].modalitiesdef_)); }
#line 2417 "Parser.C"
    break;

  case 84: /* ProblemItemDef: AgentNamesDef  */
#line 586 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbAgents((yyvsp[0].agentnamesdef_)); }
#line 2423 "Parser.C"
    break;

  case 85: /* ProblemItemDef: AgentGroupsListDef  */
#line 587 "epddl.y"
                       { (yyval.problemitemdef_) = new EPDDLProbAgentGroups((yyvsp[0].agentgroupslistdef_)); }
#line 2429 "Parser.C"
    break;

  case 86: /* ProblemItemDef: ObjectNamesDef  */
#line 588 "epddl.y"
                   { (yyval.problemitemdef_) = new EPDDLProbObjects((yyvsp[0].objectnamesdef_)); }
#line 2435 "Parser.C"
    break;

  case 87: /* ProblemItemDef: FactListDef  */
#line 589 "epddl.y"
                { (yyval.problemitemdef_) = new EPDDLProbFacts((yyvsp[0].factlistdef_)); }
#line 2441 "Parser.C"
    break;

  case 88: /* ProblemItemDef: InitDef  */
#line 590 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbInit((yyvsp[0].initdef_)); }
#line 2447 "Parser.C"
    break;

  case 89: /* ProblemItemDef: InitialModelDef  */
#line 591 "epddl.y"
                    { (yyval.problemitemdef_) = new EPDDLProbInitModel((yyvsp[0].initialmodeldef_)); }
#line 2453 "Parser.C"
    break;

  case 90: /* ProblemItemDef: GoalDef  */
#line 592 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbGoal((yyvsp[0].goaldef_)); }
#line 2459 "Parser.C"
    break;

  case 91: /* ListProblemItemDef: %empty  */
#line 594 "epddl.y"
                                 { (yyval.listproblemitemdef_) = new ListProblemItemDef(); }
#line 2465 "Parser.C"
    break;

  case 92: /* ListProblemItemDef: ListProblemItemDef ProblemItemDef  */
#line 595 "epddl.y"
                                      { (yyvsp[-1].listproblemitemdef_)->push_back((yyvsp[0].problemitemdef_)); (yyval.listproblemitemdef_) = (yyvsp[-1].listproblemitemdef_); }
#line 2471 "Parser.C"
    break;

  case 93: /* ProblemDomainNameDef: _LPAREN _SYMB_20 DomainName _RPAREN  */
#line 597 "epddl.y"
                                                           { (yyval.problemdomainnamedef_) = new EPDDLProbDomainName((yyvsp[-1].domainname_)); }
#line 2477 "Parser.C"
    break;

  case 94: /* AgentNamesDef: _LPAREN _SYMB_21 ListAgentName _RPAREN  */
#line 599 "epddl.y"
                                                       { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentnamesdef_) = new EPDDLAgentNames((yyvsp[-1].listagentname_)); }
#line 2483 "Parser.C"
    break;

  case 95: /* AgentGroupsListDef: _LPAREN _SYMB_22 ListAgentGroupDef _RPAREN  */
#line 601 "epddl.y"
                                                                { (yyval.agentgroupslistdef_) = new EPDDLAgentGroupsList((yyvsp[-1].listagentgroupdef_)); }
#line 2489 "Parser.C"
    break;

  case 96: /* AgentGroupDef: _LPAREN _LBRACE ListAgentName _RBRACE _KW_as AgentGroupName _RPAREN  */
#line 603 "epddl.y"
                                                                                    { std::reverse((yyvsp[-4].listagentname_)->begin(),(yyvsp[-4].listagentname_)->end()) ;(yyval.agentgroupdef_) = new EPDDLAgentGroupDef((yyvsp[-4].listagentname_), (yyvsp[-1].agentgroupname_)); }
#line 2495 "Parser.C"
    break;

  case 97: /* ListAgentGroupDef: %empty  */
#line 605 "epddl.y"
                                { (yyval.listagentgroupdef_) = new ListAgentGroupDef(); }
#line 2501 "Parser.C"
    break;

  case 98: /* ListAgentGroupDef: ListAgentGroupDef AgentGroupDef  */
#line 606 "epddl.y"
                                    { (yyvsp[-1].listagentgroupdef_)->push_back((yyvsp[0].agentgroupdef_)); (yyval.listagentgroupdef_) = (yyvsp[-1].listagentgroupdef_); }
#line 2507 "Parser.C"
    break;

  case 99: /* ObjectNamesDef: _LPAREN _SYMB_25 TypedIdentList _RPAREN  */
#line 608 "epddl.y"
                                                         { (yyval.objectnamesdef_) = new EPDDLObjectNames((yyvsp[-1].typedidentlist_)); }
#line 2513 "Parser.C"
    break;

  case 100: /* FactListDef: _LPAREN _SYMB_26 ListFactDef _RPAREN  */
#line 610 "epddl.y"
                                                   { std::reverse((yyvsp[-1].listfactdef_)->begin(),(yyvsp[-1].listfactdef_)->end()) ;(yyval.factlistdef_) = new EPDDLFactList((yyvsp[-1].listfactdef_)); }
#line 2519 "Parser.C"
    break;

  case 101: /* FactDef: _LPAREN PredicateName ListGenericName _RPAREN  */
#line 612 "epddl.y"
                                                        { (yyval.factdef_) = new EPDDLFactDef((yyvsp[-2].predicatename_), (yyvsp[-1].listgenericname_)); }
#line 2525 "Parser.C"
    break;

  case 102: /* ListFactDef: FactDef  */
#line 614 "epddl.y"
                      { (yyval.listfactdef_) = new ListFactDef(); (yyval.listfactdef_)->push_back((yyvsp[0].factdef_)); }
#line 2531 "Parser.C"
    break;

  case 103: /* ListFactDef: FactDef ListFactDef  */
#line 615 "epddl.y"
                        { (yyvsp[0].listfactdef_)->push_back((yyvsp[-1].factdef_)); (yyval.listfactdef_) = (yyvsp[0].listfactdef_); }
#line 2537 "Parser.C"
    break;

  case 104: /* InitDef: _LPAREN _SYMB_27 InitialStateDescr _RPAREN  */
#line 617 "epddl.y"
                                                     { (yyval.initdef_) = new EPDDLInitialState((yyvsp[-1].initialstatedescr_)); }
#line 2543 "Parser.C"
    break;

  case 105: /* InitialStateDescr: ListFTheoryFormula  */
#line 619 "epddl.y"
                                       { std::reverse((yyvsp[0].listftheoryformula_)->begin(),(yyvsp[0].listftheoryformula_)->end()) ;(yyval.initialstatedescr_) = new FinitaryTheoryDescr((yyvsp[0].listftheoryformula_)); }
#line 2549 "Parser.C"
    break;

  case 106: /* InitialStateDescr: _LPAREN _SYMB_28 ModelName _RPAREN  */
#line 620 "epddl.y"
                                       { (yyval.initialstatedescr_) = new InitialModelDescr((yyvsp[-1].modelname_)); }
#line 2555 "Parser.C"
    break;

  case 107: /* FTheoryFormula: PredicateFormula  */
#line 622 "epddl.y"
                                  { (yyval.ftheoryformula_) = new FTheoryPredForm((yyvsp[0].predicateformula_)); }
#line 2561 "Parser.C"
    break;

  case 108: /* FTheoryFormula: _LBRACK AllAgents _RBRACK PredicateFormula  */
#line 623 "epddl.y"
                                               { (yyval.ftheoryformula_) = new FTheoryCKPredForm((yyvsp[-2].allagents_), (yyvsp[0].predicateformula_)); }
#line 2567 "Parser.C"
    break;

  case 109: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KPredicateFormula  */
#line 624 "epddl.y"
                                                { (yyval.ftheoryformula_) = new FTheoryCKKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kpredicateformula_)); }
#line 2573 "Parser.C"
    break;

  case 110: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KWPredicateFormula  */
#line 625 "epddl.y"
                                                 { (yyval.ftheoryformula_) = new FTheoryCKOrKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kwpredicateformula_)); }
#line 2579 "Parser.C"
    break;

  case 111: /* FTheoryFormula: _LBRACK AllAgents _RBRACK NotKWPredicateFormula  */
#line 626 "epddl.y"
                                                    { (yyval.ftheoryformula_) = new FTheoryCKAndKPredForm((yyvsp[-2].allagents_), (yyvsp[0].notkwpredicateformula_)); }
#line 2585 "Parser.C"
    break;

  case 112: /* FTheoryFormula: _LPAREN FTheoryFormula _RPAREN  */
#line 627 "epddl.y"
                                   { (yyval.ftheoryformula_) = (yyvsp[-1].ftheoryformula_); }
#line 2591 "Parser.C"
    break;

  case 113: /* ListFTheoryFormula: FTheoryFormula  */
#line 629 "epddl.y"
                                    { (yyval.listftheoryformula_) = new ListFTheoryFormula(); (yyval.listftheoryformula_)->push_back((yyvsp[0].ftheoryformula_)); }
#line 2597 "Parser.C"
    break;

  case 114: /* ListFTheoryFormula: FTheoryFormula ListFTheoryFormula  */
#line 630 "epddl.y"
                                      { (yyvsp[0].listftheoryformula_)->push_back((yyvsp[-1].ftheoryformula_)); (yyval.listftheoryformula_) = (yyvsp[0].listftheoryformula_); }
#line 2603 "Parser.C"
    break;

  case 115: /* KPredicateFormula: _LBRACK AgentName _RBRACK PredicateFormula  */
#line 632 "epddl.y"
                                                               { (yyval.kpredicateformula_) = new KPredFormula((yyvsp[-2]._agentname), (yyvsp[0].predicateformula_)); }
#line 2609 "Parser.C"
    break;

  case 116: /* KPredicateFormula: _LPAREN KPredicateFormula _RPAREN  */
#line 633 "epddl.y"
                                      { (yyval.kpredicateformula_) = (yyvsp[-1].kpredicateformula_); }
#line 2615 "Parser.C"
    break;

  case 117: /* KWPredicateFormula: KnowsWhether PredicateFormula  */
#line 635 "epddl.y"
                                                   { (yyval.kwpredicateformula_) = new KWPredFormula((yyvsp[-1].knowswhether_), (yyvsp[0].predicateformula_)); }
#line 2621 "Parser.C"
    break;

  case 118: /* KWPredicateFormula: _LPAREN KWPredicateFormula _RPAREN  */
#line 636 "epddl.y"
                                       { (yyval.kwpredicateformula_) = (yyvsp[-1].kwpredicateformula_); }
#line 2627 "Parser.C"
    break;

  case 119: /* NotKWPredicateFormula: _LPAREN _KW_not KnowsWhether PredicateFormula _RPAREN  */
#line 638 "epddl.y"
                                                                              { (yyval.notkwpredicateformula_) = new NotKWPredFormula((yyvsp[-2].knowswhether_), (yyvsp[-1].predicateformula_)); }
#line 2633 "Parser.C"
    break;

  case 120: /* NotKWPredicateFormula: _LPAREN NotKWPredicateFormula _RPAREN  */
#line 639 "epddl.y"
                                          { (yyval.notkwpredicateformula_) = (yyvsp[-1].notkwpredicateformula_); }
#line 2639 "Parser.C"
    break;

  case 121: /* InitialModelDef: _LPAREN _SYMB_31 ModelName ModelWorldsDef ModelRelDef ModelValDef ModelDesDef _RPAREN  */
#line 641 "epddl.y"
                                                                                                        { (yyval.initialmodeldef_) = new EPDDLInitialModel((yyvsp[-5].modelname_), (yyvsp[-4].modelworldsdef_), (yyvsp[-3].modelreldef_), (yyvsp[-2].modelvaldef_), (yyvsp[-1].modeldesdef_)); }
#line 2645 "Parser.C"
    break;

  case 122: /* ModelWorldsDef: _SYMB_32 _LPAREN ListWorldName _RPAREN  */
#line 643 "epddl.y"
                                                        { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modelworldsdef_) = new ModelWorlds((yyvsp[-1].listworldname_)); }
#line 2651 "Parser.C"
    break;

  case 123: /* ModelRelDef: _SYMB_16 ModelRelations  */
#line 645 "epddl.y"
                                      { (yyval.modelreldef_) = new ModelRel((yyvsp[0].modelrelations_)); }
#line 2657 "Parser.C"
    break;

  case 124: /* ModelValDef: _SYMB_33 ModelValuation  */
#line 647 "epddl.y"
                                      { (yyval.modelvaldef_) = new ModelVal((yyvsp[0].modelvaluation_)); }
#line 2663 "Parser.C"
    break;

  case 125: /* ModelDesDef: _SYMB_17 _LPAREN ListWorldName _RPAREN  */
#line 649 "epddl.y"
                                                     { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modeldesdef_) = new ModelDes((yyvsp[-1].listworldname_)); }
#line 2669 "Parser.C"
    break;

  case 126: /* ModelRelations: ListWorldRelation  */
#line 651 "epddl.y"
                                   { std::reverse((yyvsp[0].listworldrelation_)->begin(),(yyvsp[0].listworldrelation_)->end()) ;(yyval.modelrelations_) = new WorldsModelRel((yyvsp[0].listworldrelation_)); }
#line 2675 "Parser.C"
    break;

  case 127: /* ModelRelations: TrivialDef  */
#line 652 "epddl.y"
               { (yyval.modelrelations_) = new TrivialModelRel((yyvsp[0].trivialdef_)); }
#line 2681 "Parser.C"
    break;

  case 128: /* ModelValuation: ListWorldValuation  */
#line 654 "epddl.y"
                                    { std::reverse((yyvsp[0].listworldvaluation_)->begin(),(yyvsp[0].listworldvaluation_)->end()) ;(yyval.modelvaluation_) = new WorldsModelVal((yyvsp[0].listworldvaluation_)); }
#line 2687 "Parser.C"
    break;

  case 129: /* ModelValuation: TrivialDef  */
#line 655 "epddl.y"
               { (yyval.modelvaluation_) = new TrivialModelVal((yyvsp[0].trivialdef_)); }
#line 2693 "Parser.C"
    break;

  case 130: /* WorldRelation: _LPAREN AgentGroup ListWorldNamePair _RPAREN  */
#line 657 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listworldnamepair_)->begin(),(yyvsp[-1].listworldnamepair_)->end()) ;(yyval.worldrelation_) = new WorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listworldnamepair_)); }
#line 2699 "Parser.C"
    break;

  case 131: /* WorldRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 658 "epddl.y"
                                          { (yyval.worldrelation_) = new TrivialWorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2705 "Parser.C"
    break;

  case 132: /* ListWorldRelation: WorldRelation  */
#line 660 "epddl.y"
                                  { (yyval.listworldrelation_) = new ListWorldRelation(); (yyval.listworldrelation_)->push_back((yyvsp[0].worldrelation_)); }
#line 2711 "Parser.C"
    break;

  case 133: /* ListWorldRelation: WorldRelation ListWorldRelation  */
#line 661 "epddl.y"
                                    { (yyvsp[0].listworldrelation_)->push_back((yyvsp[-1].worldrelation_)); (yyval.listworldrelation_) = (yyvsp[0].listworldrelation_); }
#line 2717 "Parser.C"
    break;

  case 134: /* WorldNamePair: _LPAREN WorldName WorldName _RPAREN  */
#line 663 "epddl.y"
                                                    { (yyval.worldnamepair_) = new WorldPair((yyvsp[-2].worldname_), (yyvsp[-1].worldname_)); }
#line 2723 "Parser.C"
    break;

  case 135: /* ListWorldNamePair: WorldNamePair  */
#line 665 "epddl.y"
                                  { (yyval.listworldnamepair_) = new ListWorldNamePair(); (yyval.listworldnamepair_)->push_back((yyvsp[0].worldnamepair_)); }
#line 2729 "Parser.C"
    break;

  case 136: /* ListWorldNamePair: WorldNamePair ListWorldNamePair  */
#line 666 "epddl.y"
                                    { (yyvsp[0].listworldnamepair_)->push_back((yyvsp[-1].worldnamepair_)); (yyval.listworldnamepair_) = (yyvsp[0].listworldnamepair_); }
#line 2735 "Parser.C"
    break;

  case 137: /* WorldValuation: _LPAREN WorldName _LBRACK ListLiteral _RBRACK _RPAREN  */
#line 668 "epddl.y"
                                                                       { (yyval.worldvaluation_) = new WorldVal((yyvsp[-4].worldname_), (yyvsp[-2].listliteral_)); }
#line 2741 "Parser.C"
    break;

  case 138: /* ListWorldValuation: WorldValuation  */
#line 670 "epddl.y"
                                    { (yyval.listworldvaluation_) = new ListWorldValuation(); (yyval.listworldvaluation_)->push_back((yyvsp[0].worldvaluation_)); }
#line 2747 "Parser.C"
    break;

  case 139: /* ListWorldValuation: WorldValuation ListWorldValuation  */
#line 671 "epddl.y"
                                      { (yyvsp[0].listworldvaluation_)->push_back((yyvsp[-1].worldvaluation_)); (yyval.listworldvaluation_) = (yyvsp[0].listworldvaluation_); }
#line 2753 "Parser.C"
    break;

  case 140: /* GoalDef: _LPAREN _SYMB_34 Formula _RPAREN  */
#line 673 "epddl.y"
                                           { (yyval.goaldef_) = new EPDDLGoals((yyvsp[-1].formula_)); }
#line 2759 "Parser.C"
    break;

  case 141: /* Formula: _LPAREN _KW_imply Formula Formula _RPAREN  */
#line 675 "epddl.y"
                                                    { (yyval.formula_) = new ImplyFormula((yyvsp[-2].formula_), (yyvsp[-1].formula_)); }
#line 2765 "Parser.C"
    break;

  case 142: /* Formula: _LPAREN _KW_or Formula ListFormula _RPAREN  */
#line 676 "epddl.y"
                                               { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new OrFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2771 "Parser.C"
    break;

  case 143: /* Formula: _LPAREN _KW_and Formula ListFormula _RPAREN  */
#line 677 "epddl.y"
                                                { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new AndFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2777 "Parser.C"
    break;

  case 144: /* Formula: _LPAREN _KW_not Formula _RPAREN  */
#line 678 "epddl.y"
                                    { (yyval.formula_) = new NotFormula((yyvsp[-1].formula_)); }
#line 2783 "Parser.C"
    break;

  case 145: /* Formula: Modality Formula  */
#line 679 "epddl.y"
                     { (yyval.formula_) = new ModalFormula((yyvsp[-1].modality_), (yyvsp[0].formula_)); }
#line 2789 "Parser.C"
    break;

  case 146: /* Formula: _LPAREN Variable _RPAREN  */
#line 680 "epddl.y"
                             { (yyval.formula_) = new VarFormula((yyvsp[-1]._variable)); }
#line 2795 "Parser.C"
    break;

  case 147: /* Formula: AtomicFormula  */
#line 681 "epddl.y"
                  { (yyval.formula_) = new AtmFormula((yyvsp[0].atomicformula_)); }
#line 2801 "Parser.C"
    break;

  case 148: /* Formula: AtomicEqFormula  */
#line 682 "epddl.y"
                    { (yyval.formula_) = new AtmEqFormula((yyvsp[0].atomiceqformula_)); }
#line 2807 "Parser.C"
    break;

  case 149: /* Formula: _KW_true  */
#line 683 "epddl.y"
             { (yyval.formula_) = new TrueFormula(); }
#line 2813 "Parser.C"
    break;

  case 150: /* Formula: _KW_false  */
#line 684 "epddl.y"
              { (yyval.formula_) = new FalseFormula(); }
#line 2819 "Parser.C"
    break;

  case 151: /* Formula: _LPAREN Formula _RPAREN  */
#line 685 "epddl.y"
                            { (yyval.formula_) = (yyvsp[-1].formula_); }
#line 2825 "Parser.C"
    break;

  case 152: /* ListFormula: Formula  */
#line 687 "epddl.y"
                      { (yyval.listformula_) = new ListFormula(); (yyval.listformula_)->push_back((yyvsp[0].formula_)); }
#line 2831 "Parser.C"
    break;

  case 153: /* ListFormula: Formula ListFormula  */
#line 688 "epddl.y"
                        { (yyvsp[0].listformula_)->push_back((yyvsp[-1].formula_)); (yyval.listformula_) = (yyvsp[0].listformula_); }
#line 2837 "Parser.C"
    break;

  case 154: /* AtomicFormula: _LPAREN PredicateName ListMetaTerm _RPAREN  */
#line 690 "epddl.y"
                                                           { (yyval.atomicformula_) = new Predicate((yyvsp[-2].predicatename_), (yyvsp[-1].listmetaterm_)); }
#line 2843 "Parser.C"
    break;

  case 155: /* AtomicEqFormula: _LPAREN _EQ Term Term _RPAREN  */
#line 692 "epddl.y"
                                                { (yyval.atomiceqformula_) = new EqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 2849 "Parser.C"
    break;

  case 156: /* FormulaOrEmpty: Formula  */
#line 694 "epddl.y"
                         { (yyval.formulaorempty_) = new NonTrivialFormula((yyvsp[0].formula_)); }
#line 2855 "Parser.C"
    break;

  case 157: /* FormulaOrEmpty: TrivialDef  */
#line 695 "epddl.y"
               { (yyval.formulaorempty_) = new TrivialFormula((yyvsp[0].trivialdef_)); }
#line 2861 "Parser.C"
    break;

  case 158: /* MetaTerm: Term  */
#line 697 "epddl.y"
                { (yyval.metaterm_) = new EPDDLMetaTerm((yyvsp[0].term_)); }
#line 2867 "Parser.C"
    break;

  case 159: /* MetaTerm: AnonVarAgent  */
#line 698 "epddl.y"
                 { (yyval.metaterm_) = new EPDDLMetaTermAnonVar((yyvsp[0].anonvaragent_)); }
#line 2873 "Parser.C"
    break;

  case 160: /* ListMetaTerm: %empty  */
#line 700 "epddl.y"
                           { (yyval.listmetaterm_) = new ListMetaTerm(); }
#line 2879 "Parser.C"
    break;

  case 161: /* ListMetaTerm: ListMetaTerm MetaTerm  */
#line 701 "epddl.y"
                          { (yyvsp[-1].listmetaterm_)->push_back((yyvsp[0].metaterm_)); (yyval.listmetaterm_) = (yyvsp[-1].listmetaterm_); }
#line 2885 "Parser.C"
    break;

  case 162: /* Term: GroundTerm  */
#line 703 "epddl.y"
                  { (yyval.term_) = new EPDDLGroundTerm((yyvsp[0].groundterm_)); }
#line 2891 "Parser.C"
    break;

  case 163: /* Term: Variable  */
#line 704 "epddl.y"
             { (yyval.term_) = new EPDDLTermVar((yyvsp[0]._variable)); }
#line 2897 "Parser.C"
    break;

  case 164: /* ListTerm: %empty  */
#line 706 "epddl.y"
                       { (yyval.listterm_) = new ListTerm(); }
#line 2903 "Parser.C"
    break;

  case 165: /* ListTerm: ListTerm Term  */
#line 707 "epddl.y"
                  { (yyvsp[-1].listterm_)->push_back((yyvsp[0].term_)); (yyval.listterm_) = (yyvsp[-1].listterm_); }
#line 2909 "Parser.C"
    break;

  case 166: /* GroundTerm: Name  */
#line 709 "epddl.y"
                  { (yyval.groundterm_) = new EPDDLGroundTermName((yyvsp[0]._name)); }
#line 2915 "Parser.C"
    break;

  case 167: /* GroundTerm: AgentName  */
#line 710 "epddl.y"
              { (yyval.groundterm_) = new EPDDLGroundTermAgName((yyvsp[0]._agentname)); }
#line 2921 "Parser.C"
    break;

  case 168: /* ListGroundTerm: %empty  */
#line 712 "epddl.y"
                             { (yyval.listgroundterm_) = new ListGroundTerm(); }
#line 2927 "Parser.C"
    break;

  case 169: /* ListGroundTerm: ListGroundTerm GroundTerm  */
#line 713 "epddl.y"
                              { (yyvsp[-1].listgroundterm_)->push_back((yyvsp[0].groundterm_)); (yyval.listgroundterm_) = (yyvsp[-1].listgroundterm_); }
#line 2933 "Parser.C"
    break;

  case 170: /* Modality: SingleModality  */
#line 715 "epddl.y"
                          { (yyval.modality_) = new EPDDLLabeledMod((yyvsp[0].singlemodality_)); }
#line 2939 "Parser.C"
    break;

  case 171: /* Modality: GroupModality  */
#line 716 "epddl.y"
                  { (yyval.modality_) = new EPDDLLabeledGroupMod((yyvsp[0].groupmodality_)); }
#line 2945 "Parser.C"
    break;

  case 172: /* SingleModality: _LBRACK ModalityLabel ModalityAgent _RBRACK  */
#line 718 "epddl.y"
                                                             { (yyval.singlemodality_) = new LabBoxMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2951 "Parser.C"
    break;

  case 173: /* SingleModality: _LT ModalityLabel ModalityAgent _GT  */
#line 719 "epddl.y"
                                        { (yyval.singlemodality_) = new LabDiamondMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2957 "Parser.C"
    break;

  case 174: /* GroupModality: _LBRACK ModalityLabel ModalityAgentGroup _RBRACK  */
#line 721 "epddl.y"
                                                                 { (yyval.groupmodality_) = new LabBoxGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2963 "Parser.C"
    break;

  case 175: /* GroupModality: _LT ModalityLabel ModalityAgentGroup _GT  */
#line 722 "epddl.y"
                                             { (yyval.groupmodality_) = new LabDiamondGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2969 "Parser.C"
    break;

  case 176: /* ModalityLabel: ModalityName  */
#line 724 "epddl.y"
                             { (yyval.modalitylabel_) = new ModLabel((yyvsp[0]._modalityname)); }
#line 2975 "Parser.C"
    break;

  case 177: /* ModalityLabel: %empty  */
#line 725 "epddl.y"
                { (yyval.modalitylabel_) = new EmptyModLabel(); }
#line 2981 "Parser.C"
    break;

  case 178: /* KnowsWhether: _LBRACK ModalityName AgentName _RBRACK  */
#line 727 "epddl.y"
                                                      { (yyval.knowswhether_) = new KnowsWhetherMod((yyvsp[-2]._modalityname), (yyvsp[-1]._agentname)); }
#line 2987 "Parser.C"
    break;

  case 179: /* Literal: AtomicFormula  */
#line 729 "epddl.y"
                        { (yyval.literal_) = new PosLiteral((yyvsp[0].atomicformula_)); }
#line 2993 "Parser.C"
    break;

  case 180: /* Literal: _LPAREN _KW_not AtomicFormula _RPAREN  */
#line 730 "epddl.y"
                                          { (yyval.literal_) = new NegLiteral((yyvsp[-1].atomicformula_)); }
#line 2999 "Parser.C"
    break;

  case 181: /* ListLiteral: %empty  */
#line 732 "epddl.y"
                          { (yyval.listliteral_) = new ListLiteral(); }
#line 3005 "Parser.C"
    break;

  case 182: /* ListLiteral: ListLiteral Literal  */
#line 733 "epddl.y"
                        { (yyvsp[-1].listliteral_)->push_back((yyvsp[0].literal_)); (yyval.listliteral_) = (yyvsp[-1].listliteral_); }
#line 3011 "Parser.C"
    break;

  case 183: /* ConditionFormula: _LPAREN _KW_and Condition ListCondition _RPAREN  */
#line 735 "epddl.y"
                                                                   { std::reverse((yyvsp[-1].listcondition_)->begin(),(yyvsp[-1].listcondition_)->end()) ;(yyval.conditionformula_) = new AndCondFomula((yyvsp[-2].condition_), (yyvsp[-1].listcondition_)); }
#line 3017 "Parser.C"
    break;

  case 184: /* ConditionFormula: Condition  */
#line 736 "epddl.y"
              { (yyval.conditionformula_) = new CondFomula((yyvsp[0].condition_)); }
#line 3023 "Parser.C"
    break;

  case 185: /* Condition: AtomicCondition  */
#line 738 "epddl.y"
                            { (yyval.condition_) = new AtmCond((yyvsp[0].atomiccondition_)); }
#line 3029 "Parser.C"
    break;

  case 186: /* Condition: _LPAREN _KW_not AtomicCondition _RPAREN  */
#line 739 "epddl.y"
                                            { (yyval.condition_) = new NotAtmCond((yyvsp[-1].atomiccondition_)); }
#line 3035 "Parser.C"
    break;

  case 187: /* ListCondition: Condition  */
#line 741 "epddl.y"
                          { (yyval.listcondition_) = new ListCondition(); (yyval.listcondition_)->push_back((yyvsp[0].condition_)); }
#line 3041 "Parser.C"
    break;

  case 188: /* ListCondition: Condition ListCondition  */
#line 742 "epddl.y"
                            { (yyvsp[0].listcondition_)->push_back((yyvsp[-1].condition_)); (yyval.listcondition_) = (yyvsp[0].listcondition_); }
#line 3047 "Parser.C"
    break;

  case 189: /* AtomicCondition: _LPAREN PredicateName ListTerm _RPAREN  */
#line 744 "epddl.y"
                                                         { (yyval.atomiccondition_) = new AtmCondPredicate((yyvsp[-2].predicatename_), (yyvsp[-1].listterm_)); }
#line 3053 "Parser.C"
    break;

  case 190: /* AtomicCondition: _LPAREN _EQ Term Term _RPAREN  */
#line 745 "epddl.y"
                                  { (yyval.atomiccondition_) = new AtmCondEqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 3059 "Parser.C"
    break;

  case 191: /* PredicateFormula: _LPAREN _KW_imply PredicateFormula PredicateFormula _RPAREN  */
#line 747 "epddl.y"
                                                                               { (yyval.predicateformula_) = new ImplyPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].predicateformula_)); }
#line 3065 "Parser.C"
    break;

  case 192: /* PredicateFormula: _LPAREN _KW_or PredicateFormula ListPredicateFormula _RPAREN  */
#line 748 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new OrPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3071 "Parser.C"
    break;

  case 193: /* PredicateFormula: _LPAREN _KW_and PredicateFormula ListPredicateFormula _RPAREN  */
#line 749 "epddl.y"
                                                                  { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new AndPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3077 "Parser.C"
    break;

  case 194: /* PredicateFormula: _LPAREN _KW_not PredicateFormula _RPAREN  */
#line 750 "epddl.y"
                                             { (yyval.predicateformula_) = new NotPredFormula((yyvsp[-1].predicateformula_)); }
#line 3083 "Parser.C"
    break;

  case 195: /* PredicateFormula: _LPAREN PredicateName ListGroundTerm _RPAREN  */
#line 751 "epddl.y"
                                                 { (yyval.predicateformula_) = new AtmPredFormula((yyvsp[-2].predicatename_), (yyvsp[-1].listgroundterm_)); }
#line 3089 "Parser.C"
    break;

  case 196: /* ListPredicateFormula: PredicateFormula  */
#line 753 "epddl.y"
                                        { (yyval.listpredicateformula_) = new ListPredicateFormula(); (yyval.listpredicateformula_)->push_back((yyvsp[0].predicateformula_)); }
#line 3095 "Parser.C"
    break;

  case 197: /* ListPredicateFormula: PredicateFormula ListPredicateFormula  */
#line 754 "epddl.y"
                                          { (yyvsp[0].listpredicateformula_)->push_back((yyvsp[-1].predicateformula_)); (yyval.listpredicateformula_) = (yyvsp[0].listpredicateformula_); }
#line 3101 "Parser.C"
    break;

  case 198: /* GenericName: Name  */
#line 756 "epddl.y"
                   { (yyval.genericname_) = new EPDDLGenericNameObj((yyvsp[0]._name)); }
#line 3107 "Parser.C"
    break;

  case 199: /* GenericName: AgentName  */
#line 757 "epddl.y"
              { (yyval.genericname_) = new EPDDLGenericNameAg((yyvsp[0]._agentname)); }
#line 3113 "Parser.C"
    break;

  case 200: /* ListGenericName: %empty  */
#line 759 "epddl.y"
                              { (yyval.listgenericname_) = new ListGenericName(); }
#line 3119 "Parser.C"
    break;

  case 201: /* ListGenericName: ListGenericName GenericName  */
#line 760 "epddl.y"
                                { (yyvsp[-1].listgenericname_)->push_back((yyvsp[0].genericname_)); (yyval.listgenericname_) = (yyvsp[-1].listgenericname_); }
#line 3125 "Parser.C"
    break;

  case 202: /* TypedIdentList: ListName  */
#line 762 "epddl.y"
                          { std::reverse((yyvsp[0].listname_)->begin(),(yyvsp[0].listname_)->end()) ;(yyval.typedidentlist_) = new IdList((yyvsp[0].listname_)); }
#line 3131 "Parser.C"
    break;

  case 203: /* TypedIdentList: Name ListName _MINUS Type TypedIdentList  */
#line 763 "epddl.y"
                                             { std::reverse((yyvsp[-3].listname_)->begin(),(yyvsp[-3].listname_)->end()) ;(yyval.typedidentlist_) = new TypedIdList((yyvsp[-4]._name), (yyvsp[-3].listname_), (yyvsp[-1].type_), (yyvsp[0].typedidentlist_)); }
#line 3137 "Parser.C"
    break;

  case 204: /* TypedVariableList: ListVariable  */
#line 765 "epddl.y"
                                 { std::reverse((yyvsp[0].listvariable_)->begin(),(yyvsp[0].listvariable_)->end()) ;(yyval.typedvariablelist_) = new VarList((yyvsp[0].listvariable_)); }
#line 3143 "Parser.C"
    break;

  case 205: /* TypedVariableList: Variable ListVariable _MINUS Type TypedVariableList  */
#line 766 "epddl.y"
                                                        { std::reverse((yyvsp[-3].listvariable_)->begin(),(yyvsp[-3].listvariable_)->end()) ;(yyval.typedvariablelist_) = new TypedVarList((yyvsp[-4]._variable), (yyvsp[-3].listvariable_), (yyvsp[-1].type_), (yyvsp[0].typedvariablelist_)); }
#line 3149 "Parser.C"
    break;

  case 206: /* PredicateName: Name  */
#line 768 "epddl.y"
                     { (yyval.predicatename_) = new EPDDLPredicate((yyvsp[0]._name)); }
#line 3155 "Parser.C"
    break;

  case 207: /* ModalityAgent: AgentName  */
#line 770 "epddl.y"
                          { (yyval.modalityagent_) = new EPDDLModAgent((yyvsp[0]._agentname)); }
#line 3161 "Parser.C"
    break;

  case 208: /* ModalityAgent: Variable  */
#line 771 "epddl.y"
             { (yyval.modalityagent_) = new EPDDLModVarAgent((yyvsp[0]._variable)); }
#line 3167 "Parser.C"
    break;

  case 209: /* ModalityAgent: AnonVarAgent  */
#line 772 "epddl.y"
                 { (yyval.modalityagent_) = new EPDDLModAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 3173 "Parser.C"
    break;

  case 210: /* ModalityAgent: AllAgents  */
#line 773 "epddl.y"
              { (yyval.modalityagent_) = new EPDDLModAllAgents((yyvsp[0].allagents_)); }
#line 3179 "Parser.C"
    break;

  case 211: /* ListModalityAgent: ModalityAgent  */
#line 775 "epddl.y"
                                  { (yyval.listmodalityagent_) = new ListModalityAgent(); (yyval.listmodalityagent_)->push_back((yyvsp[0].modalityagent_)); }
#line 3185 "Parser.C"
    break;

  case 212: /* ListModalityAgent: ModalityAgent ListModalityAgent  */
#line 776 "epddl.y"
                                    { (yyvsp[0].listmodalityagent_)->push_back((yyvsp[-1].modalityagent_)); (yyval.listmodalityagent_) = (yyvsp[0].listmodalityagent_); }
#line 3191 "Parser.C"
    break;

  case 213: /* ModalityAgentGroup: ModalityAgent ListModalityAgent  */
#line 778 "epddl.y"
                                                     { std::reverse((yyvsp[0].listmodalityagent_)->begin(),(yyvsp[0].listmodalityagent_)->end()) ;(yyval.modalityagentgroup_) = new EPDDLModAgList((yyvsp[-1].modalityagent_), (yyvsp[0].listmodalityagent_)); }
#line 3197 "Parser.C"
    break;

  case 214: /* AgentGroupName: AgentName  */
#line 780 "epddl.y"
                           { (yyval.agentgroupname_) = new EPDDLSingleAgentGroup((yyvsp[0]._agentname)); }
#line 3203 "Parser.C"
    break;

  case 215: /* AgentGroupName: AllAgents  */
#line 781 "epddl.y"
              { (yyval.agentgroupname_) = new EPDDLAllAgentsGroup((yyvsp[0].allagents_)); }
#line 3209 "Parser.C"
    break;

  case 216: /* ObservingAgentGroup: AgentName  */
#line 783 "epddl.y"
                                { (yyval.observingagentgroup_) = new EPDDLObsAgentGroup((yyvsp[0]._agentname)); }
#line 3215 "Parser.C"
    break;

  case 217: /* ListObservingAgentGroup: ObservingAgentGroup  */
#line 785 "epddl.y"
                                              { (yyval.listobservingagentgroup_) = new ListObservingAgentGroup(); (yyval.listobservingagentgroup_)->push_back((yyvsp[0].observingagentgroup_)); }
#line 3221 "Parser.C"
    break;

  case 218: /* ListObservingAgentGroup: ObservingAgentGroup ListObservingAgentGroup  */
#line 786 "epddl.y"
                                                { (yyvsp[0].listobservingagentgroup_)->push_back((yyvsp[-1].observingagentgroup_)); (yyval.listobservingagentgroup_) = (yyvsp[0].listobservingagentgroup_); }
#line 3227 "Parser.C"
    break;

  case 219: /* ObservingAgent: AgentName  */
#line 788 "epddl.y"
                           { (yyval.observingagent_) = new EPDDLObsAgent((yyvsp[0]._agentname)); }
#line 3233 "Parser.C"
    break;

  case 220: /* ObservingAgent: AllAgents  */
#line 789 "epddl.y"
              { (yyval.observingagent_) = new EPDDLObsAllAgents((yyvsp[0].allagents_)); }
#line 3239 "Parser.C"
    break;

  case 221: /* ObservingAgent: Variable  */
#line 790 "epddl.y"
             { (yyval.observingagent_) = new EPDDLObsVarAgent((yyvsp[0]._variable)); }
#line 3245 "Parser.C"
    break;

  case 222: /* ObservingAgent: AnonVarAgent  */
#line 791 "epddl.y"
                 { (yyval.observingagent_) = new EPDDLObsAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 3251 "Parser.C"
    break;

  case 223: /* AgentGroup: AgentGroupName  */
#line 793 "epddl.y"
                            { (yyval.agentgroup_) = new EPDDLAgentGroup((yyvsp[0].agentgroupname_)); }
#line 3257 "Parser.C"
    break;

  case 224: /* AgentGroup: _LBRACE AgentName ListAgentName _RBRACE  */
#line 794 "epddl.y"
                                            { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentgroup_) = new EPDDLAgentNameGroup((yyvsp[-2]._agentname), (yyvsp[-1].listagentname_)); }
#line 3263 "Parser.C"
    break;

  case 225: /* AllAgents: _KW_All  */
#line 796 "epddl.y"
                    { (yyval.allagents_) = new EPDDLAllAgents(); }
#line 3269 "Parser.C"
    break;

  case 226: /* AnonVarAgent: _SYMB_39  */
#line 798 "epddl.y"
                        { (yyval.anonvaragent_) = new EPDDLAnonVarAgent(); }
#line 3275 "Parser.C"
    break;

  case 227: /* Parameter: _LPAREN Variable _DCOLON ParameterValue _RPAREN  */
#line 800 "epddl.y"
                                                            { (yyval.parameter_) = new EPDDLParam((yyvsp[-3]._variable), (yyvsp[-1].parametervalue_)); }
#line 3281 "Parser.C"
    break;

  case 228: /* ListParameter: %empty  */
#line 802 "epddl.y"
                            { (yyval.listparameter_) = new ListParameter(); }
#line 3287 "Parser.C"
    break;

  case 229: /* ListParameter: ListParameter Parameter  */
#line 803 "epddl.y"
                            { (yyvsp[-1].listparameter_)->push_back((yyvsp[0].parameter_)); (yyval.listparameter_) = (yyvsp[-1].listparameter_); }
#line 3293 "Parser.C"
    break;

  case 230: /* ParameterValue: Term  */
#line 805 "epddl.y"
                      { (yyval.parametervalue_) = new EPDDLTermParam((yyvsp[0].term_)); }
#line 3299 "Parser.C"
    break;

  case 231: /* ParameterValue: Formula  */
#line 806 "epddl.y"
            { (yyval.parametervalue_) = new EPDDLFormulaParam((yyvsp[0].formula_)); }
#line 3305 "Parser.C"
    break;

  case 232: /* ParameterValue: ListPostParameterValue  */
#line 807 "epddl.y"
                           { std::reverse((yyvsp[0].listpostparametervalue_)->begin(),(yyvsp[0].listpostparametervalue_)->end()) ;(yyval.parametervalue_) = new EPDDLPostParam((yyvsp[0].listpostparametervalue_)); }
#line 3311 "Parser.C"
    break;

  case 233: /* PostParameterValue: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN ListLiteralPostcondition _RPAREN  */
#line 809 "epddl.y"
                                                                                                           { std::reverse((yyvsp[-1].listliteralpostcondition_)->begin(),(yyvsp[-1].listliteralpostcondition_)->end()) ;(yyval.postparametervalue_) = new PostParamForall((yyvsp[-3].typedvariablelist_), (yyvsp[-1].listliteralpostcondition_)); }
#line 3317 "Parser.C"
    break;

  case 234: /* PostParameterValue: LiteralPostcondition  */
#line 810 "epddl.y"
                         { (yyval.postparametervalue_) = new PostParamLiteral((yyvsp[0].literalpostcondition_)); }
#line 3323 "Parser.C"
    break;

  case 235: /* ListPostParameterValue: PostParameterValue  */
#line 812 "epddl.y"
                                            { (yyval.listpostparametervalue_) = new ListPostParameterValue(); (yyval.listpostparametervalue_)->push_back((yyvsp[0].postparametervalue_)); }
#line 3329 "Parser.C"
    break;

  case 236: /* ListPostParameterValue: PostParameterValue ListPostParameterValue  */
#line 813 "epddl.y"
                                              { (yyvsp[0].listpostparametervalue_)->push_back((yyvsp[-1].postparametervalue_)); (yyval.listpostparametervalue_) = (yyvsp[0].listpostparametervalue_); }
#line 3335 "Parser.C"
    break;

  case 237: /* Type: Name  */
#line 815 "epddl.y"
            { (yyval.type_) = new EPDDLTypeName((yyvsp[0]._name)); }
#line 3341 "Parser.C"
    break;

  case 238: /* Type: ReservedType  */
#line 816 "epddl.y"
                 { (yyval.type_) = new EPDDLResType((yyvsp[0].reservedtype_)); }
#line 3347 "Parser.C"
    break;

  case 239: /* ReservedType: _KW_agent  */
#line 818 "epddl.y"
                         { (yyval.reservedtype_) = new ResAgentType(); }
#line 3353 "Parser.C"
    break;

  case 240: /* ReservedType: _KW_predicate  */
#line 819 "epddl.y"
                  { (yyval.reservedtype_) = new PredicateType(); }
#line 3359 "Parser.C"
    break;

  case 241: /* ReservedType: _KW_literal  */
#line 820 "epddl.y"
                { (yyval.reservedtype_) = new LiteralType(); }
#line 3365 "Parser.C"
    break;

  case 242: /* ReservedType: _SYMB_41  */
#line 821 "epddl.y"
             { (yyval.reservedtype_) = new PredFormulaType(); }
#line 3371 "Parser.C"
    break;

  case 243: /* ReservedType: _KW_formula  */
#line 822 "epddl.y"
                { (yyval.reservedtype_) = new FormulaType(); }
#line 3377 "Parser.C"
    break;

  case 244: /* ReservedType: _KW_postcondition  */
#line 823 "epddl.y"
                      { (yyval.reservedtype_) = new PostconditionType(); }
#line 3383 "Parser.C"
    break;

  case 245: /* DomainName: Name  */
#line 825 "epddl.y"
                  { (yyval.domainname_) = new EPDDLDomainName((yyvsp[0]._name)); }
#line 3389 "Parser.C"
    break;

  case 246: /* LibraryName: Name  */
#line 827 "epddl.y"
                   { (yyval.libraryname_) = new EPDDLLibraryName((yyvsp[0]._name)); }
#line 3395 "Parser.C"
    break;

  case 247: /* ListLibraryName: LibraryName  */
#line 829 "epddl.y"
                              { (yyval.listlibraryname_) = new ListLibraryName(); (yyval.listlibraryname_)->push_back((yyvsp[0].libraryname_)); }
#line 3401 "Parser.C"
    break;

  case 248: /* ListLibraryName: LibraryName ListLibraryName  */
#line 830 "epddl.y"
                                { (yyvsp[0].listlibraryname_)->push_back((yyvsp[-1].libraryname_)); (yyval.listlibraryname_) = (yyvsp[0].listlibraryname_); }
#line 3407 "Parser.C"
    break;

  case 249: /* ProblemName: Name  */
#line 832 "epddl.y"
                   { (yyval.problemname_) = new EPDDLProblemName((yyvsp[0]._name)); }
#line 3413 "Parser.C"
    break;

  case 250: /* ActionName: Name  */
#line 834 "epddl.y"
                  { (yyval.actionname_) = new EPDDLActionName((yyvsp[0]._name)); }
#line 3419 "Parser.C"
    break;

  case 251: /* ActionTypeName: Name  */
#line 836 "epddl.y"
                      { (yyval.actiontypename_) = new EPDDLActTypeName((yyvsp[0]._name)); }
#line 3425 "Parser.C"
    break;

  case 252: /* EventName: Name  */
#line 838 "epddl.y"
                 { (yyval.eventname_) = new EPDDLEventName((yyvsp[0]._name)); }
#line 3431 "Parser.C"
    break;

  case 253: /* ListEventName: EventName  */
#line 840 "epddl.y"
                          { (yyval.listeventname_) = new ListEventName(); (yyval.listeventname_)->push_back((yyvsp[0].eventname_)); }
#line 3437 "Parser.C"
    break;

  case 254: /* ListEventName: EventName ListEventName  */
#line 841 "epddl.y"
                            { (yyvsp[0].listeventname_)->push_back((yyvsp[-1].eventname_)); (yyval.listeventname_) = (yyvsp[0].listeventname_); }
#line 3443 "Parser.C"
    break;

  case 255: /* ModelName: Name  */
#line 843 "epddl.y"
                 { (yyval.modelname_) = new EPDDLModelName((yyvsp[0]._name)); }
#line 3449 "Parser.C"
    break;

  case 256: /* WorldName: Name  */
#line 845 "epddl.y"
                 { (yyval.worldname_) = new EPDDLWorldName((yyvsp[0]._name)); }
#line 3455 "Parser.C"
    break;

  case 257: /* ListWorldName: WorldName  */
#line 847 "epddl.y"
                          { (yyval.listworldname_) = new ListWorldName(); (yyval.listworldname_)->push_back((yyvsp[0].worldname_)); }
#line 3461 "Parser.C"
    break;

  case 258: /* ListWorldName: WorldName ListWorldName  */
#line 848 "epddl.y"
                            { (yyvsp[0].listworldname_)->push_back((yyvsp[-1].worldname_)); (yyval.listworldname_) = (yyvsp[0].listworldname_); }
#line 3467 "Parser.C"
    break;

  case 259: /* RequireKey: _SYMB_42  */
#line 850 "epddl.y"
                      { (yyval.requirekey_) = new EPDDLReqDel(); }
#line 3473 "Parser.C"
    break;

  case 260: /* RequireKey: _SYMB_43  */
#line 851 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqTyping(); }
#line 3479 "Parser.C"
    break;

  case 261: /* RequireKey: _SYMB_44  */
#line 852 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqEquality(); }
#line 3485 "Parser.C"
    break;

  case 262: /* RequireKey: _SYMB_45  */
#line 853 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqParamList(); }
#line 3491 "Parser.C"
    break;

  case 263: /* RequireKey: _SYMB_46  */
#line 854 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqNegPre(); }
#line 3497 "Parser.C"
    break;

  case 264: /* RequireKey: _SYMB_47  */
#line 855 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqDisPre(); }
#line 3503 "Parser.C"
    break;

  case 265: /* RequireKey: _SYMB_48  */
#line 856 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqExiPre(); }
#line 3509 "Parser.C"
    break;

  case 266: /* RequireKey: _SYMB_49  */
#line 857 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqUniPre(); }
#line 3515 "Parser.C"
    break;

  case 267: /* RequireKey: _SYMB_50  */
#line 858 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPre(); }
#line 3521 "Parser.C"
    break;

  case 268: /* RequireKey: _SYMB_51  */
#line 859 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPost(); }
#line 3527 "Parser.C"
    break;

  case 269: /* RequireKey: _SYMB_6  */
#line 860 "epddl.y"
            { (yyval.requirekey_) = new EPDDLReqModalities(); }
#line 3533 "Parser.C"
    break;

  case 270: /* RequireKey: _SYMB_52  */
#line 861 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOnticChange(); }
#line 3539 "Parser.C"
    break;

  case 271: /* RequireKey: _SYMB_53  */
#line 862 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqCK(); }
#line 3545 "Parser.C"
    break;

  case 272: /* RequireKey: _SYMB_54  */
#line 863 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqDynCK(); }
#line 3551 "Parser.C"
    break;

  case 273: /* RequireKey: _SYMB_55  */
#line 864 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqMAStar(); }
#line 3557 "Parser.C"
    break;

  case 274: /* RequireKey: _SYMB_56  */
#line 865 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOntic(); }
#line 3563 "Parser.C"
    break;

  case 275: /* RequireKey: _SYMB_57  */
#line 866 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqSensing(); }
#line 3569 "Parser.C"
    break;

  case 276: /* RequireKey: _SYMB_58  */
#line 867 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqAnnouncement(); }
#line 3575 "Parser.C"
    break;

  case 277: /* RequireKey: _SYMB_59  */
#line 868 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqFTheory(); }
#line 3581 "Parser.C"
    break;

  case 278: /* RequireKey: _LPAREN _SYMB_60 _INTEGER_ _RPAREN  */
#line 869 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPreDepth((yyvsp[-1]._int)); }
#line 3587 "Parser.C"
    break;

  case 279: /* RequireKey: _LPAREN _SYMB_61 _INTEGER_ _RPAREN  */
#line 870 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPostDepth((yyvsp[-1]._int)); }
#line 3593 "Parser.C"
    break;

  case 280: /* RequireKey: _LPAREN _SYMB_62 _INTEGER_ _RPAREN  */
#line 871 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxDepth((yyvsp[-1]._int)); }
#line 3599 "Parser.C"
    break;

  case 281: /* ListRequireKey: RequireKey  */
#line 873 "epddl.y"
                            { (yyval.listrequirekey_) = new ListRequireKey(); (yyval.listrequirekey_)->push_back((yyvsp[0].requirekey_)); }
#line 3605 "Parser.C"
    break;

  case 282: /* ListRequireKey: RequireKey ListRequireKey  */
#line 874 "epddl.y"
                              { (yyvsp[0].listrequirekey_)->push_back((yyvsp[-1].requirekey_)); (yyval.listrequirekey_) = (yyvsp[0].listrequirekey_); }
#line 3611 "Parser.C"
    break;

  case 283: /* TrivialDef: _LPAREN _RPAREN  */
#line 876 "epddl.y"
                             { (yyval.trivialdef_) = new EPDDLTrivialDef(); }
#line 3617 "Parser.C"
    break;

  case 284: /* ListName: %empty  */
#line 878 "epddl.y"
                       { (yyval.listname_) = new ListName(); }
#line 3623 "Parser.C"
    break;

  case 285: /* ListName: Name ListName  */
#line 879 "epddl.y"
                  { (yyvsp[0].listname_)->push_back((yyvsp[-1]._name)); (yyval.listname_) = (yyvsp[0].listname_); }
#line 3629 "Parser.C"
    break;

  case 286: /* ListAgentName: AgentName  */
#line 881 "epddl.y"
                          { (yyval.listagentname_) = new ListAgentName(); (yyval.listagentname_)->push_back((yyvsp[0]._agentname)); }
#line 3635 "Parser.C"
    break;

  case 287: /* ListAgentName: AgentName ListAgentName  */
#line 882 "epddl.y"
                            { (yyvsp[0].listagentname_)->push_back((yyvsp[-1]._agentname)); (yyval.listagentname_) = (yyvsp[0].listagentname_); }
#line 3641 "Parser.C"
    break;

  case 288: /* ListModalityName: %empty  */
#line 884 "epddl.y"
                               { (yyval.listmodalityname_) = new ListModalityName(); }
#line 3647 "Parser.C"
    break;

  case 289: /* ListModalityName: ModalityName ListModalityName  */
#line 885 "epddl.y"
                                  { (yyvsp[0].listmodalityname_)->push_back((yyvsp[-1]._modalityname)); (yyval.listmodalityname_) = (yyvsp[0].listmodalityname_); }
#line 3653 "Parser.C"
    break;

  case 290: /* ListVariable: %empty  */
#line 887 "epddl.y"
                           { (yyval.listvariable_) = new ListVariable(); }
#line 3659 "Parser.C"
    break;

  case 291: /* ListVariable: Variable ListVariable  */
#line 888 "epddl.y"
                          { (yyvsp[0].listvariable_)->push_back((yyvsp[-1]._variable)); (yyval.listvariable_) = (yyvsp[0].listvariable_); }
#line 3665 "Parser.C"
    break;

  case 292: /* Name: T_Name  */
#line 890 "epddl.y"
              { (yyval._name) = new Name((yyvsp[0]._string), (yyloc).first_line); }
#line 3671 "Parser.C"
    break;

  case 293: /* AgentName: T_AgentName  */
#line 892 "epddl.y"
                        { (yyval._agentname) = new AgentName((yyvsp[0]._string), (yyloc).first_line); }
#line 3677 "Parser.C"
    break;

  case 294: /* ModalityName: T_ModalityName  */
#line 894 "epddl.y"
                              { (yyval._modalityname) = new ModalityName((yyvsp[0]._string), (yyloc).first_line); }
#line 3683 "Parser.C"
    break;

  case 295: /* Variable: T_Variable  */
#line 896 "epddl.y"
                      { (yyval._variable) = new Variable((yyvsp[0]._string), (yyloc).first_line); }
#line 3689 "Parser.C"
    break;


#line 3693 "Parser.C"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (&yylloc, scanner, result, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner, result);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, result, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, result);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 899 "epddl.y"



/* Entrypoint: parse MainDef* from file. */
MainDef* pMainDef(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = epddl__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  epddl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.maindef_;
  }
}

/* Entrypoint: parse MainDef* from string. */
MainDef* psMainDef(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = epddl__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = epddl__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  epddl__delete_buffer(buf, scanner);
  epddl_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.maindef_;
  }
}



