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
  YYSYMBOL__COLON = 7,                     /* _COLON  */
  YYSYMBOL__DCOLON = 8,                    /* _DCOLON  */
  YYSYMBOL__SYMB_7 = 9,                    /* _SYMB_7  */
  YYSYMBOL__SYMB_10 = 10,                  /* _SYMB_10  */
  YYSYMBOL__SYMB_2 = 11,                   /* _SYMB_2  */
  YYSYMBOL__SYMB_23 = 12,                  /* _SYMB_23  */
  YYSYMBOL__SYMB_22 = 13,                  /* _SYMB_22  */
  YYSYMBOL__SYMB_50 = 14,                  /* _SYMB_50  */
  YYSYMBOL__SYMB_41 = 15,                  /* _SYMB_41  */
  YYSYMBOL__SYMB_17 = 16,                  /* _SYMB_17  */
  YYSYMBOL__SYMB_21 = 17,                  /* _SYMB_21  */
  YYSYMBOL__SYMB_51 = 18,                  /* _SYMB_51  */
  YYSYMBOL__SYMB_43 = 19,                  /* _SYMB_43  */
  YYSYMBOL__SYMB_18 = 20,                  /* _SYMB_18  */
  YYSYMBOL__SYMB_15 = 21,                  /* _SYMB_15  */
  YYSYMBOL__SYMB_44 = 22,                  /* _SYMB_44  */
  YYSYMBOL__SYMB_52 = 23,                  /* _SYMB_52  */
  YYSYMBOL__SYMB_35 = 24,                  /* _SYMB_35  */
  YYSYMBOL__SYMB_28 = 25,                  /* _SYMB_28  */
  YYSYMBOL__SYMB_55 = 26,                  /* _SYMB_55  */
  YYSYMBOL__SYMB_54 = 27,                  /* _SYMB_54  */
  YYSYMBOL__SYMB_53 = 28,                  /* _SYMB_53  */
  YYSYMBOL__SYMB_48 = 29,                  /* _SYMB_48  */
  YYSYMBOL__SYMB_47 = 30,                  /* _SYMB_47  */
  YYSYMBOL__SYMB_6 = 31,                   /* _SYMB_6  */
  YYSYMBOL__SYMB_26 = 32,                  /* _SYMB_26  */
  YYSYMBOL__SYMB_12 = 33,                  /* _SYMB_12  */
  YYSYMBOL__SYMB_14 = 34,                  /* _SYMB_14  */
  YYSYMBOL__SYMB_49 = 35,                  /* _SYMB_49  */
  YYSYMBOL__SYMB_8 = 36,                   /* _SYMB_8  */
  YYSYMBOL__SYMB_19 = 37,                  /* _SYMB_19  */
  YYSYMBOL__SYMB_11 = 38,                  /* _SYMB_11  */
  YYSYMBOL__SYMB_5 = 39,                   /* _SYMB_5  */
  YYSYMBOL__SYMB_16 = 40,                  /* _SYMB_16  */
  YYSYMBOL__SYMB_3 = 41,                   /* _SYMB_3  */
  YYSYMBOL__SYMB_32 = 42,                  /* _SYMB_32  */
  YYSYMBOL__SYMB_29 = 43,                  /* _SYMB_29  */
  YYSYMBOL__SYMB_27 = 44,                  /* _SYMB_27  */
  YYSYMBOL__SYMB_4 = 45,                   /* _SYMB_4  */
  YYSYMBOL__SYMB_42 = 46,                  /* _SYMB_42  */
  YYSYMBOL__SYMB_45 = 47,                  /* _SYMB_45  */
  YYSYMBOL__SYMB_46 = 48,                  /* _SYMB_46  */
  YYSYMBOL__SYMB_34 = 49,                  /* _SYMB_34  */
  YYSYMBOL__SYMB_9 = 50,                   /* _SYMB_9  */
  YYSYMBOL__SYMB_33 = 51,                  /* _SYMB_33  */
  YYSYMBOL__LT = 52,                       /* _LT  */
  YYSYMBOL__EQ = 53,                       /* _EQ  */
  YYSYMBOL__GT = 54,                       /* _GT  */
  YYSYMBOL__KW_All = 55,                   /* _KW_All  */
  YYSYMBOL__LBRACK = 56,                   /* _LBRACK  */
  YYSYMBOL__RBRACK = 57,                   /* _RBRACK  */
  YYSYMBOL__KW_agent = 58,                 /* _KW_agent  */
  YYSYMBOL__KW_and = 59,                   /* _KW_and  */
  YYSYMBOL__KW_as = 60,                    /* _KW_as  */
  YYSYMBOL__KW_define = 61,                /* _KW_define  */
  YYSYMBOL__KW_domain = 62,                /* _KW_domain  */
  YYSYMBOL__KW_exists = 63,                /* _KW_exists  */
  YYSYMBOL__KW_false = 64,                 /* _KW_false  */
  YYSYMBOL__KW_forall = 65,                /* _KW_forall  */
  YYSYMBOL__KW_formula = 66,               /* _KW_formula  */
  YYSYMBOL__KW_if = 67,                    /* _KW_if  */
  YYSYMBOL__KW_iff = 68,                   /* _KW_iff  */
  YYSYMBOL__KW_imply = 69,                 /* _KW_imply  */
  YYSYMBOL__KW_library = 70,               /* _KW_library  */
  YYSYMBOL__KW_literal = 71,               /* _KW_literal  */
  YYSYMBOL__KW_not = 72,                   /* _KW_not  */
  YYSYMBOL__KW_or = 73,                    /* _KW_or  */
  YYSYMBOL__KW_otherwise = 74,             /* _KW_otherwise  */
  YYSYMBOL__KW_postcondition = 75,         /* _KW_postcondition  */
  YYSYMBOL__KW_predicate = 76,             /* _KW_predicate  */
  YYSYMBOL__SYMB_40 = 77,                  /* _SYMB_40  */
  YYSYMBOL__KW_problem = 78,               /* _KW_problem  */
  YYSYMBOL__KW_true = 79,                  /* _KW_true  */
  YYSYMBOL__KW_when = 80,                  /* _KW_when  */
  YYSYMBOL__LBRACE = 81,                   /* _LBRACE  */
  YYSYMBOL__RBRACE = 82,                   /* _RBRACE  */
  YYSYMBOL_T_AgentName = 83,               /* T_AgentName  */
  YYSYMBOL_T_ModalityName = 84,            /* T_ModalityName  */
  YYSYMBOL_T_Name = 85,                    /* T_Name  */
  YYSYMBOL_T_Variable = 86,                /* T_Variable  */
  YYSYMBOL__INTEGER_ = 87,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_MainDef = 89,                   /* MainDef  */
  YYSYMBOL_DomainDef = 90,                 /* DomainDef  */
  YYSYMBOL_DomainItemDef = 91,             /* DomainItemDef  */
  YYSYMBOL_ListDomainItemDef = 92,         /* ListDomainItemDef  */
  YYSYMBOL_DomainLibrariesNameDef = 93,    /* DomainLibrariesNameDef  */
  YYSYMBOL_RequireDef = 94,                /* RequireDef  */
  YYSYMBOL_TypesDef = 95,                  /* TypesDef  */
  YYSYMBOL_PredicateListDef = 96,          /* PredicateListDef  */
  YYSYMBOL_PredicateDef = 97,              /* PredicateDef  */
  YYSYMBOL_ListPredicateDef = 98,          /* ListPredicateDef  */
  YYSYMBOL_ModalitiesDef = 99,             /* ModalitiesDef  */
  YYSYMBOL_ActionDef = 100,                /* ActionDef  */
  YYSYMBOL_ParametersDef = 101,            /* ParametersDef  */
  YYSYMBOL_ActionConditionDef = 102,       /* ActionConditionDef  */
  YYSYMBOL_ActionTypeSignatureDef = 103,   /* ActionTypeSignatureDef  */
  YYSYMBOL_ActionPreDef = 104,             /* ActionPreDef  */
  YYSYMBOL_ActionObsDef = 105,             /* ActionObsDef  */
  YYSYMBOL_ObsConditionDef = 106,          /* ObsConditionDef  */
  YYSYMBOL_ListObsConditionDef = 107,      /* ListObsConditionDef  */
  YYSYMBOL_ObsCondition = 108,             /* ObsCondition  */
  YYSYMBOL_ListObsCondition = 109,         /* ListObsCondition  */
  YYSYMBOL_LibraryDef = 110,               /* LibraryDef  */
  YYSYMBOL_LibraryItemDef = 111,           /* LibraryItemDef  */
  YYSYMBOL_ListLibraryItemDef = 112,       /* ListLibraryItemDef  */
  YYSYMBOL_ObservabilityGroupsDef = 113,   /* ObservabilityGroupsDef  */
  YYSYMBOL_ActionTypeDef = 114,            /* ActionTypeDef  */
  YYSYMBOL_ActionTypeGroupsDef = 115,      /* ActionTypeGroupsDef  */
  YYSYMBOL_ActionTypeEventsDef = 116,      /* ActionTypeEventsDef  */
  YYSYMBOL_EventSignature = 117,           /* EventSignature  */
  YYSYMBOL_ListEventSignature = 118,       /* ListEventSignature  */
  YYSYMBOL_ActionTypeRelDef = 119,         /* ActionTypeRelDef  */
  YYSYMBOL_ActionRelations = 120,          /* ActionRelations  */
  YYSYMBOL_EventRelation = 121,            /* EventRelation  */
  YYSYMBOL_ListEventRelation = 122,        /* ListEventRelation  */
  YYSYMBOL_EventNamePair = 123,            /* EventNamePair  */
  YYSYMBOL_ListEventNamePair = 124,        /* ListEventNamePair  */
  YYSYMBOL_ActionTypeDesignDef = 125,      /* ActionTypeDesignDef  */
  YYSYMBOL_EventDef = 126,                 /* EventDef  */
  YYSYMBOL_EventPreDef = 127,              /* EventPreDef  */
  YYSYMBOL_EventPostDef = 128,             /* EventPostDef  */
  YYSYMBOL_PostconditionBlock = 129,       /* PostconditionBlock  */
  YYSYMBOL_Postcondition = 130,            /* Postcondition  */
  YYSYMBOL_ListPostcondition = 131,        /* ListPostcondition  */
  YYSYMBOL_SimplePostcondition = 132,      /* SimplePostcondition  */
  YYSYMBOL_ListSimplePostcondition = 133,  /* ListSimplePostcondition  */
  YYSYMBOL_ProblemDef = 134,               /* ProblemDef  */
  YYSYMBOL_ProblemItemDef = 135,           /* ProblemItemDef  */
  YYSYMBOL_ListProblemItemDef = 136,       /* ListProblemItemDef  */
  YYSYMBOL_ProblemDomainNameDef = 137,     /* ProblemDomainNameDef  */
  YYSYMBOL_AgentNamesDef = 138,            /* AgentNamesDef  */
  YYSYMBOL_AgentGroupsListDef = 139,       /* AgentGroupsListDef  */
  YYSYMBOL_AgentGroupDef = 140,            /* AgentGroupDef  */
  YYSYMBOL_ListAgentGroupDef = 141,        /* ListAgentGroupDef  */
  YYSYMBOL_ObjectNamesDef = 142,           /* ObjectNamesDef  */
  YYSYMBOL_StaticPredListDef = 143,        /* StaticPredListDef  */
  YYSYMBOL_StaticPredDef = 144,            /* StaticPredDef  */
  YYSYMBOL_ListStaticPredDef = 145,        /* ListStaticPredDef  */
  YYSYMBOL_InitDef = 146,                  /* InitDef  */
  YYSYMBOL_InitialStateDescr = 147,        /* InitialStateDescr  */
  YYSYMBOL_FTheoryFormula = 148,           /* FTheoryFormula  */
  YYSYMBOL_ListFTheoryFormula = 149,       /* ListFTheoryFormula  */
  YYSYMBOL_SimpleFTheoryFormula = 150,     /* SimpleFTheoryFormula  */
  YYSYMBOL_StateDef = 151,                 /* StateDef  */
  YYSYMBOL_StateWorldsDef = 152,           /* StateWorldsDef  */
  YYSYMBOL_StateRelDef = 153,              /* StateRelDef  */
  YYSYMBOL_StateRelations = 154,           /* StateRelations  */
  YYSYMBOL_WorldRelation = 155,            /* WorldRelation  */
  YYSYMBOL_ListWorldRelation = 156,        /* ListWorldRelation  */
  YYSYMBOL_WorldNamePair = 157,            /* WorldNamePair  */
  YYSYMBOL_ListWorldNamePair = 158,        /* ListWorldNamePair  */
  YYSYMBOL_StateValDef = 159,              /* StateValDef  */
  YYSYMBOL_StateValuation = 160,           /* StateValuation  */
  YYSYMBOL_WorldValuation = 161,           /* WorldValuation  */
  YYSYMBOL_ListWorldValuation = 162,       /* ListWorldValuation  */
  YYSYMBOL_StateDesignDef = 163,           /* StateDesignDef  */
  YYSYMBOL_GoalDef = 164,                  /* GoalDef  */
  YYSYMBOL_Formula = 165,                  /* Formula  */
  YYSYMBOL_ListFormula = 166,              /* ListFormula  */
  YYSYMBOL_AtomicFormula = 167,            /* AtomicFormula  */
  YYSYMBOL_Predicate = 168,                /* Predicate  */
  YYSYMBOL_AtomicEqFormula = 169,          /* AtomicEqFormula  */
  YYSYMBOL_FormulaOrEmpty = 170,           /* FormulaOrEmpty  */
  YYSYMBOL_Term = 171,                     /* Term  */
  YYSYMBOL_ListTerm = 172,                 /* ListTerm  */
  YYSYMBOL_GroundTerm = 173,               /* GroundTerm  */
  YYSYMBOL_ListGroundTerm = 174,           /* ListGroundTerm  */
  YYSYMBOL_Modality = 175,                 /* Modality  */
  YYSYMBOL_SingleModality = 176,           /* SingleModality  */
  YYSYMBOL_GroupModality = 177,            /* GroupModality  */
  YYSYMBOL_ModalityLabel = 178,            /* ModalityLabel  */
  YYSYMBOL_KnowsWhether = 179,             /* KnowsWhether  */
  YYSYMBOL_Literal = 180,                  /* Literal  */
  YYSYMBOL_ListLiteral = 181,              /* ListLiteral  */
  YYSYMBOL_ConditionFormula = 182,         /* ConditionFormula  */
  YYSYMBOL_Condition = 183,                /* Condition  */
  YYSYMBOL_ListCondition = 184,            /* ListCondition  */
  YYSYMBOL_AtomicCondition = 185,          /* AtomicCondition  */
  YYSYMBOL_PredicateFormula = 186,         /* PredicateFormula  */
  YYSYMBOL_ListPredicateFormula = 187,     /* ListPredicateFormula  */
  YYSYMBOL_GenericName = 188,              /* GenericName  */
  YYSYMBOL_ListGenericName = 189,          /* ListGenericName  */
  YYSYMBOL_TypedIdentList = 190,           /* TypedIdentList  */
  YYSYMBOL_TypedAgentList = 191,           /* TypedAgentList  */
  YYSYMBOL_TypedVariableList = 192,        /* TypedVariableList  */
  YYSYMBOL_PredicateName = 193,            /* PredicateName  */
  YYSYMBOL_ModalityAgent = 194,            /* ModalityAgent  */
  YYSYMBOL_ListModalityAgent = 195,        /* ListModalityAgent  */
  YYSYMBOL_ModalityAgentGroup = 196,       /* ModalityAgentGroup  */
  YYSYMBOL_AgentGroupName = 197,           /* AgentGroupName  */
  YYSYMBOL_ObservingAgentGroup = 198,      /* ObservingAgentGroup  */
  YYSYMBOL_ListObservingAgentGroup = 199,  /* ListObservingAgentGroup  */
  YYSYMBOL_ObservingAgent = 200,           /* ObservingAgent  */
  YYSYMBOL_AgentGroup = 201,               /* AgentGroup  */
  YYSYMBOL_AllAgents = 202,                /* AllAgents  */
  YYSYMBOL_Parameter = 203,                /* Parameter  */
  YYSYMBOL_ListParameter = 204,            /* ListParameter  */
  YYSYMBOL_Expression = 205,               /* Expression  */
  YYSYMBOL_Type = 206,                     /* Type  */
  YYSYMBOL_ReservedType = 207,             /* ReservedType  */
  YYSYMBOL_DomainName = 208,               /* DomainName  */
  YYSYMBOL_LibraryName = 209,              /* LibraryName  */
  YYSYMBOL_ListLibraryName = 210,          /* ListLibraryName  */
  YYSYMBOL_ProblemName = 211,              /* ProblemName  */
  YYSYMBOL_ActionName = 212,               /* ActionName  */
  YYSYMBOL_ActionTypeName = 213,           /* ActionTypeName  */
  YYSYMBOL_EventName = 214,                /* EventName  */
  YYSYMBOL_ListEventName = 215,            /* ListEventName  */
  YYSYMBOL_StateName = 216,                /* StateName  */
  YYSYMBOL_WorldName = 217,                /* WorldName  */
  YYSYMBOL_ListWorldName = 218,            /* ListWorldName  */
  YYSYMBOL_RequirementKey = 219,           /* RequirementKey  */
  YYSYMBOL_ListRequirementKey = 220,       /* ListRequirementKey  */
  YYSYMBOL_TrivialDef = 221,               /* TrivialDef  */
  YYSYMBOL_ListName = 222,                 /* ListName  */
  YYSYMBOL_ListAgentName = 223,            /* ListAgentName  */
  YYSYMBOL_ListModalityName = 224,         /* ListModalityName  */
  YYSYMBOL_ListVariable = 225,             /* ListVariable  */
  YYSYMBOL_Name = 226,                     /* Name  */
  YYSYMBOL_AgentName = 227,                /* AgentName  */
  YYSYMBOL_ModalityName = 228,             /* ModalityName  */
  YYSYMBOL_Variable = 229                  /* Variable  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 198 "epddl.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, epddl_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 380 "Parser.C"


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
#define YYLAST   649

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  142
/* YYNRULES -- Number of rules.  */
#define YYNRULES  279
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  559

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   342


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
      85,    86,    87
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   442,   442,   443,   444,   446,   448,   449,   450,   451,
     452,   453,   455,   456,   458,   460,   462,   464,   466,   468,
     469,   471,   473,   475,   477,   478,   480,   482,   484,   485,
     487,   488,   490,   491,   493,   494,   495,   497,   498,   500,
     502,   503,   504,   505,   506,   508,   509,   511,   513,   515,
     516,   518,   520,   522,   523,   525,   527,   528,   530,   531,
     533,   534,   536,   538,   539,   541,   543,   545,   547,   548,
     550,   552,   553,   554,   556,   557,   559,   560,   561,   563,
     564,   566,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   579,   580,   582,   584,   586,   588,   590,   591,
     593,   595,   597,   599,   600,   602,   604,   605,   607,   608,
     610,   611,   613,   614,   615,   616,   617,   619,   621,   623,
     625,   626,   628,   629,   631,   632,   634,   636,   637,   639,
     641,   642,   644,   646,   647,   649,   651,   653,   654,   655,
     656,   657,   658,   659,   660,   661,   662,   663,   664,   666,
     667,   669,   670,   672,   674,   676,   677,   679,   680,   682,
     683,   685,   686,   688,   689,   691,   692,   694,   695,   697,
     698,   700,   701,   703,   705,   706,   708,   709,   711,   712,
     714,   715,   717,   718,   720,   721,   723,   724,   725,   726,
     727,   729,   730,   732,   733,   735,   736,   738,   739,   741,
     742,   744,   745,   747,   749,   750,   751,   753,   754,   756,
     758,   759,   761,   763,   764,   766,   767,   768,   770,   771,
     773,   775,   777,   778,   780,   781,   782,   784,   785,   787,
     788,   789,   790,   791,   792,   794,   796,   798,   799,   801,
     803,   805,   807,   809,   810,   812,   814,   816,   817,   819,
     820,   821,   822,   823,   824,   825,   826,   827,   828,   829,
     830,   831,   832,   833,   834,   836,   837,   839,   841,   842,
     844,   845,   847,   848,   850,   851,   853,   855,   857,   859
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
  "_RPAREN", "_MINUS", "_COLON", "_DCOLON", "_SYMB_7", "_SYMB_10",
  "_SYMB_2", "_SYMB_23", "_SYMB_22", "_SYMB_50", "_SYMB_41", "_SYMB_17",
  "_SYMB_21", "_SYMB_51", "_SYMB_43", "_SYMB_18", "_SYMB_15", "_SYMB_44",
  "_SYMB_52", "_SYMB_35", "_SYMB_28", "_SYMB_55", "_SYMB_54", "_SYMB_53",
  "_SYMB_48", "_SYMB_47", "_SYMB_6", "_SYMB_26", "_SYMB_12", "_SYMB_14",
  "_SYMB_49", "_SYMB_8", "_SYMB_19", "_SYMB_11", "_SYMB_5", "_SYMB_16",
  "_SYMB_3", "_SYMB_32", "_SYMB_29", "_SYMB_27", "_SYMB_4", "_SYMB_42",
  "_SYMB_45", "_SYMB_46", "_SYMB_34", "_SYMB_9", "_SYMB_33", "_LT", "_EQ",
  "_GT", "_KW_All", "_LBRACK", "_RBRACK", "_KW_agent", "_KW_and", "_KW_as",
  "_KW_define", "_KW_domain", "_KW_exists", "_KW_false", "_KW_forall",
  "_KW_formula", "_KW_if", "_KW_iff", "_KW_imply", "_KW_library",
  "_KW_literal", "_KW_not", "_KW_or", "_KW_otherwise", "_KW_postcondition",
  "_KW_predicate", "_SYMB_40", "_KW_problem", "_KW_true", "_KW_when",
  "_LBRACE", "_RBRACE", "T_AgentName", "T_ModalityName", "T_Name",
  "T_Variable", "_INTEGER_", "$accept", "MainDef", "DomainDef",
  "DomainItemDef", "ListDomainItemDef", "DomainLibrariesNameDef",
  "RequireDef", "TypesDef", "PredicateListDef", "PredicateDef",
  "ListPredicateDef", "ModalitiesDef", "ActionDef", "ParametersDef",
  "ActionConditionDef", "ActionTypeSignatureDef", "ActionPreDef",
  "ActionObsDef", "ObsConditionDef", "ListObsConditionDef", "ObsCondition",
  "ListObsCondition", "LibraryDef", "LibraryItemDef", "ListLibraryItemDef",
  "ObservabilityGroupsDef", "ActionTypeDef", "ActionTypeGroupsDef",
  "ActionTypeEventsDef", "EventSignature", "ListEventSignature",
  "ActionTypeRelDef", "ActionRelations", "EventRelation",
  "ListEventRelation", "EventNamePair", "ListEventNamePair",
  "ActionTypeDesignDef", "EventDef", "EventPreDef", "EventPostDef",
  "PostconditionBlock", "Postcondition", "ListPostcondition",
  "SimplePostcondition", "ListSimplePostcondition", "ProblemDef",
  "ProblemItemDef", "ListProblemItemDef", "ProblemDomainNameDef",
  "AgentNamesDef", "AgentGroupsListDef", "AgentGroupDef",
  "ListAgentGroupDef", "ObjectNamesDef", "StaticPredListDef",
  "StaticPredDef", "ListStaticPredDef", "InitDef", "InitialStateDescr",
  "FTheoryFormula", "ListFTheoryFormula", "SimpleFTheoryFormula",
  "StateDef", "StateWorldsDef", "StateRelDef", "StateRelations",
  "WorldRelation", "ListWorldRelation", "WorldNamePair",
  "ListWorldNamePair", "StateValDef", "StateValuation", "WorldValuation",
  "ListWorldValuation", "StateDesignDef", "GoalDef", "Formula",
  "ListFormula", "AtomicFormula", "Predicate", "AtomicEqFormula",
  "FormulaOrEmpty", "Term", "ListTerm", "GroundTerm", "ListGroundTerm",
  "Modality", "SingleModality", "GroupModality", "ModalityLabel",
  "KnowsWhether", "Literal", "ListLiteral", "ConditionFormula",
  "Condition", "ListCondition", "AtomicCondition", "PredicateFormula",
  "ListPredicateFormula", "GenericName", "ListGenericName",
  "TypedIdentList", "TypedAgentList", "TypedVariableList", "PredicateName",
  "ModalityAgent", "ListModalityAgent", "ModalityAgentGroup",
  "AgentGroupName", "ObservingAgentGroup", "ListObservingAgentGroup",
  "ObservingAgent", "AgentGroup", "AllAgents", "Parameter",
  "ListParameter", "Expression", "Type", "ReservedType", "DomainName",
  "LibraryName", "ListLibraryName", "ProblemName", "ActionName",
  "ActionTypeName", "EventName", "ListEventName", "StateName", "WorldName",
  "ListWorldName", "RequirementKey", "ListRequirementKey", "TrivialDef",
  "ListName", "ListAgentName", "ListModalityName", "ListVariable", "Name",
  "AgentName", "ModalityName", "Variable", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-435)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,    -3,    32,  -435,  -435,  -435,    85,  -435,   138,     8,
       8,     8,  -435,   102,  -435,   149,  -435,   152,  -435,  -435,
    -435,  -435,   267,   290,   305,   311,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,   338,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,   489,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,     8,     8,    87,   175,   451,
       8,     8,     8,   106,  -435,   106,     8,    15,    64,     8,
       8,   209,   182,  -435,     8,   220,  -435,   232,    87,     8,
     175,   254,   278,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,   451,   256,   269,  -435,
       8,   182,  -435,   182,  -435,  -435,   106,   282,  -435,   331,
     287,  -435,   106,   296,   352,    87,    87,  -435,  -435,   302,
    -435,  -435,  -435,    15,  -435,  -435,   162,   228,   309,    65,
    -435,  -435,  -435,   323,   246,  -435,     8,   209,   326,   329,
     288,  -435,  -435,  -435,  -435,   257,  -435,  -435,  -435,   253,
     266,   268,  -435,  -435,  -435,   343,     8,   336,   325,  -435,
    -435,   294,  -435,  -435,  -435,   367,   106,  -435,   168,    15,
     364,   381,    15,    15,    15,  -435,    15,  -435,   377,   205,
    -435,   205,  -435,  -435,     8,   384,   394,   384,   384,   384,
    -435,  -435,   339,  -435,   292,  -435,  -435,   406,   383,  -435,
    -435,  -435,   257,   422,   417,   424,  -435,   257,   427,   428,
     430,   452,  -435,   439,   423,    86,   410,   106,   452,  -435,
     168,  -435,  -435,  -435,  -435,    15,   257,   257,    15,   443,
      15,   445,    25,  -435,   195,   397,  -435,  -435,  -435,   243,
     395,   448,   420,   384,   257,   384,   449,   384,    34,    88,
       8,   454,   407,    54,   470,   173,  -435,  -435,  -435,   455,
     446,  -435,   462,   257,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,     8,  -435,  -435,   106,   481,   447,   217,
    -435,  -435,  -435,   484,   495,   106,   106,   498,    15,   499,
     503,   504,   506,  -435,   507,  -435,  -435,  -435,  -435,   205,
    -435,  -435,  -435,  -435,  -435,   384,   510,   511,   512,  -435,
     519,  -435,  -435,   463,   262,   384,  -435,     8,   521,  -435,
      72,  -435,   490,  -435,  -435,   530,   522,  -435,  -435,  -435,
    -435,  -435,   168,   535,   536,  -435,     8,    86,   508,   452,
    -435,  -435,   537,     8,   481,  -435,   539,   528,  -435,   538,
    -435,  -435,   464,  -435,  -435,  -435,  -435,    15,    15,  -435,
    -435,  -435,  -435,  -435,   114,  -435,  -435,   147,   492,   106,
    -435,  -435,  -435,   106,  -435,   543,  -435,  -435,   112,  -435,
      28,  -435,   546,  -435,  -435,   547,   548,   168,   -22,   535,
      -5,   549,    29,  -435,  -435,   551,   552,   257,  -435,  -435,
    -435,    72,  -435,   554,  -435,  -435,   555,   556,  -435,   496,
     557,   558,   559,    87,   384,   384,   509,   106,    28,   561,
     562,   563,   513,     8,  -435,     8,  -435,   565,   535,   566,
    -435,  -435,   362,   210,   551,  -435,  -435,  -435,  -435,   376,
     568,   112,  -435,     8,  -435,   387,   -10,  -435,  -435,  -435,
     569,  -435,  -435,   478,     8,     8,  -435,  -435,  -435,  -435,
     570,  -435,  -435,  -435,   257,  -435,  -435,   572,    15,   205,
     106,  -435,  -435,  -435,  -435,  -435,    28,   573,   574,   575,
       8,   576,   392,  -435,  -435,  -435,  -435,  -435,   577,  -435,
    -435,   578,    40,  -435,   544,   257,   205,   106,   579,     8,
       8,  -435,  -435,  -435,  -435,  -435,   581,    86,   582,    86,
     583,  -435,  -435,   -29,   584,  -435,    20,   567,   106,   585,
    -435,   586,   257,   588,     8,   589,   588,  -435,  -435,   334,
    -435,  -435,  -435,   590,   452,   591,  -435,  -435,   592,   593,
    -435,   594,  -435,   595,  -435,   597,  -435,  -435,   598,    84,
     597,   599,   169,   598,   600,  -435,  -435,  -435,  -435
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     2,     3,     4,     0,     1,     0,     0,
       0,     0,   276,     0,   235,     0,   236,     0,   239,    12,
      45,    92,     0,     0,     0,     0,     5,    13,     6,     7,
       8,     9,    10,    11,     0,    39,    40,    41,    46,    42,
      43,    44,     0,    81,    83,    84,    93,    82,    85,    86,
      87,    88,    89,    90,    91,     0,     0,   272,     0,     0,
     268,     0,     0,     0,    98,   270,     0,     0,     0,   268,
       0,     0,     0,   240,   237,     0,   278,     0,   272,     0,
      19,     0,     0,   259,   249,   260,   251,   252,   261,   256,
     255,   257,   258,   250,   253,   254,   265,     0,     0,   197,
     268,     0,   241,     0,   242,   277,   213,     0,   212,     0,
       0,   199,   270,     0,     0,   172,   172,   148,   147,     0,
     145,   151,   146,     0,   165,   166,     0,     0,     0,   110,
     106,   108,   112,     0,     0,   245,     0,   103,     0,     0,
      25,   238,    14,    21,   273,   274,   203,    20,    17,     0,
       0,     0,   266,    15,    16,   269,   268,    50,     0,   214,
      47,     0,    96,    99,    95,   271,   270,    94,     0,     0,
       0,     0,     0,     0,     0,   279,     0,   159,     0,     0,
     171,     0,   136,   143,     0,     0,     0,     0,     0,     0,
     163,   220,     0,   105,     0,   111,   100,     0,     0,   195,
     104,   101,   274,     0,     0,     0,   201,   274,     0,     0,
       0,     0,   269,     0,     0,     0,    69,     0,     0,   271,
       0,   157,   161,   162,   158,     0,   274,   274,     0,     0,
       0,     0,     0,   152,     0,     0,   206,   204,   205,     0,
       0,     0,     0,     0,   274,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    24,   179,   180,     0,
       0,    18,   275,   274,   264,   263,   262,   229,   233,   231,
     234,   230,   232,   268,   228,   227,     0,     0,     0,     0,
     155,    67,   156,     0,     0,   270,   270,     0,   149,     0,
       0,     0,     0,   140,     0,   144,   153,   160,   168,   207,
     209,   170,   167,   169,   107,   191,     0,     0,     0,   189,
       0,   190,   164,     0,     0,     0,   113,   247,     0,   246,
       0,   119,   124,   120,   121,     0,     0,   102,   196,   193,
     194,    23,     0,     0,     0,   159,     0,     0,    29,     0,
     275,   198,     0,     0,    53,    51,     0,     0,   267,     0,
      68,    66,     0,   200,   154,   150,   139,     0,     0,   137,
     138,   208,   192,   188,     0,   186,   187,     0,     0,     0,
     115,   248,   118,     0,   218,     0,   211,   210,     0,   125,
       0,   129,   133,   130,   131,     0,     0,     0,     0,     0,
       0,     0,     0,   222,    27,     0,     0,   274,    49,   222,
      54,     0,    55,    60,    56,    57,     0,     0,    74,     0,
       0,     0,     0,     0,     0,     0,     0,   270,     0,   127,
       0,     0,     0,     0,   134,     0,   117,     0,   182,     0,
     181,   184,     0,     0,    32,    28,    31,    22,   202,     0,
       0,     0,    61,     0,    48,     0,     0,   141,   142,   109,
       0,   114,   173,     0,     0,     0,   128,   122,   123,   176,
       0,   185,   183,   178,     0,    26,   223,     0,     0,     0,
       0,   216,   215,   217,    33,    52,     0,    63,     0,     0,
     243,     0,     0,    70,    75,    71,   174,    78,     0,   116,
     219,     0,     0,   135,     0,     0,     0,     0,     0,     0,
       0,    64,    58,    59,   244,    65,     0,     0,     0,     0,
       0,    97,   126,     0,     0,   177,     0,     0,     0,     0,
      34,     0,   274,     0,     0,     0,     0,    73,   132,     0,
     226,   225,   224,     0,     0,     0,    36,    62,     0,     0,
     175,     0,   221,     0,    35,     0,    76,    77,     0,     0,
      79,     0,     0,    37,     0,    80,    72,    38,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -435,  -435,  -435,  -435,  -435,  -435,   371,  -435,  -435,  -435,
     523,   378,  -435,    83,  -435,  -435,  -435,  -435,  -435,   144,
    -387,    53,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
     249,  -435,  -435,  -435,   184,  -435,   130,  -435,  -435,  -435,
    -435,    92,  -435,  -435,   164,    60,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,  -435,   474,  -435,  -435,
    -435,   483,   250,  -435,  -435,  -435,  -435,  -435,   291,  -435,
     196,  -435,  -435,  -435,   234,  -435,  -435,   -40,  -210,  -435,
    -422,  -435,  -315,  -154,   283,   369,  -435,  -107,  -435,  -435,
     505,   252,  -311,  -435,  -435,  -192,   192,   289,  -147,  -218,
    -435,  -435,   -56,   340,  -190,   -51,    59,   328,   441,   178,
    -321,  -103,  -434,  -261,  -122,  -435,   226,  -435,  -209,  -435,
     564,   618,   560,  -435,  -435,   293,   -58,   151,   453,  -292,
    -300,  -435,   540,  -230,   -82,  -102,   571,  -181,    -9,   -57,
    -100,   -33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,    27,    22,    28,    29,    30,    31,    80,
      81,    32,    33,   140,   204,   260,   338,   396,   434,   435,
     436,   554,     4,    38,    23,    39,    40,   214,   278,   344,
     345,   347,   402,   403,   404,   477,   478,   407,    41,   216,
     284,   350,   484,   445,   550,   551,     5,    46,    24,    47,
      48,    49,   163,   109,    50,    51,   137,   138,    52,   128,
     129,   130,   131,    53,   198,   252,   321,   322,   323,   419,
     420,   326,   381,   382,   383,   386,    54,   280,   289,   120,
     121,   122,   281,   297,   232,   221,   248,   123,   124,   125,
     179,   315,   487,   492,   256,   428,   429,   258,   132,   306,
     328,   253,    98,   110,   205,   177,   299,   300,   235,   374,
     106,   107,   470,   375,   236,   466,   432,   533,   273,   274,
      13,    74,    75,    17,    72,   101,   480,   481,   134,   317,
     318,    96,    97,   282,    99,   111,    77,   206,   146,   223,
      78,   207
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    16,    18,   159,   103,   192,   108,   176,   112,   286,
     165,   257,   254,   133,   220,   180,   180,   371,   155,   114,
     294,   324,   394,   486,   529,     1,   262,   119,   145,   310,
     296,   332,     7,   348,   431,   497,   290,   291,   243,   311,
     245,   246,   247,   508,   513,   191,    73,    16,   332,   108,
     334,   100,   102,   104,   307,   166,    12,    14,     6,   327,
     100,   135,   518,    12,   219,    16,   287,   115,   126,   194,
     486,   116,   115,   105,   212,   190,   116,   348,   355,   117,
      12,   178,   340,   183,   117,   199,   525,   362,   422,     8,
     279,   156,   313,    12,   118,   384,   305,   514,   308,   118,
     305,   486,   316,   105,   486,    12,   175,    19,   105,   166,
      12,   175,   105,    12,    12,   175,   405,   105,   242,    12,
     127,   127,   237,   486,   237,   460,   454,   191,   486,   225,
     397,   422,   228,   229,   230,   224,   231,   105,   115,    12,
     440,   389,   116,   190,   314,   421,   238,   156,   238,   498,
     117,   242,   507,   373,    20,   105,   508,    21,   305,   222,
     285,   553,   491,   454,   509,   118,   553,   191,   370,    12,
     127,    76,   176,   342,   263,   135,   519,   237,   387,    79,
     440,   515,   237,   352,   157,   288,   158,   224,   292,   105,
     288,   190,   523,   373,   526,   105,   330,   535,   376,   224,
       9,   238,   275,   413,   335,   184,   238,   438,    10,   275,
     479,   222,   539,   136,   369,   541,    11,   341,   139,   108,
     246,   185,   348,   222,   191,   142,   332,   186,   166,   112,
     263,   187,   333,   427,   188,   189,   468,   143,   234,   222,
     239,   319,   237,   469,   329,   334,   178,    12,   288,   298,
     191,   105,   105,    12,   175,   175,   376,   368,    12,   148,
     191,   153,   190,   377,   100,   191,   238,   450,   451,   115,
     168,    25,    26,   116,   154,   467,   169,   468,   105,   376,
     170,   175,   171,   191,   469,   399,   172,   160,   105,   173,
     174,   175,   164,   105,    34,    35,   175,   197,   191,   224,
     302,   167,    12,   175,   149,   150,   151,   182,   319,    42,
      43,   471,   416,   369,   193,   453,   417,   410,   411,   376,
      55,   377,    56,   222,   376,   543,   105,   102,   196,   175,
     275,   201,   538,   202,   104,   161,   162,   335,   203,   335,
     208,   408,    57,   175,   377,   105,    76,   471,    61,   211,
      58,   185,    59,   209,   224,   210,    60,   186,    62,   224,
     166,   187,   532,   215,   188,   189,   464,   465,   226,    57,
     213,   319,    63,   218,   471,   217,   472,    12,   222,    59,
     464,   475,   233,   222,   377,   227,   115,   168,   242,   377,
     116,   482,   483,   169,    36,    44,   249,   170,   244,   171,
     473,    37,    45,   172,   115,   168,   173,   174,   116,   319,
     250,   169,   472,   108,   319,   170,   319,   171,   499,    12,
     175,   172,   176,   251,   173,   174,   255,   259,   496,   261,
     471,   494,   264,   265,   104,   266,   473,    12,   175,   472,
     108,   521,   499,   276,   277,   319,   319,   283,   293,   510,
     295,   301,   303,   304,   309,    82,   325,   506,   320,   336,
     507,   108,   517,   473,   508,    83,    84,   104,   339,    85,
      86,   104,   509,    87,    88,   331,   531,    12,   175,   185,
      89,    90,    91,   224,   337,   343,    92,   346,   349,   187,
     104,   104,   188,   189,   378,   472,   178,    93,    94,    95,
     351,    64,    65,   354,   356,    12,    66,   222,   357,   358,
     267,   359,   360,    67,    68,   363,   364,   365,   268,   473,
      57,    69,   185,   269,   366,   275,   372,   270,   271,   272,
      59,    70,   187,    71,   380,   367,   189,    12,   385,   388,
     390,   395,   398,   401,   406,   408,   409,   418,    12,   415,
     423,   425,   516,   426,   430,   433,   446,   437,   441,   443,
     490,   444,   447,   448,   449,   455,   452,   457,   458,   459,
     461,   463,   476,   534,   489,   493,   495,   500,   474,   502,
     503,   505,   511,   512,   520,   522,   524,   442,   527,   528,
     536,   537,   513,   400,   540,   542,   544,   545,   546,   547,
     548,   549,   552,   147,   556,   558,   557,   501,   530,   485,
     555,   200,   195,   379,   412,   456,   424,   312,   392,   414,
     462,   181,   240,   391,   488,   439,   353,   361,    15,   393,
     113,   504,     0,     0,   141,     0,   152,   241,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   144
};

static const yytype_int16 yycheck[] =
{
       9,    10,    11,   106,    62,   127,    63,   114,    65,   218,
     112,   203,   202,    69,   168,   115,   116,   317,   100,     4,
     230,   251,   337,   445,     4,     4,   207,    67,    79,   247,
       5,    53,     0,     5,     5,   469,   226,   227,   185,     5,
     187,   188,   189,    72,     4,    55,    55,    56,    53,   106,
      72,    60,    61,    62,   244,   112,    85,    66,    61,     5,
      69,    70,   496,    85,   166,    74,   220,    52,     4,     4,
     492,    56,    52,    83,   156,   126,    56,     5,   288,    64,
      85,   114,   263,   123,    64,   136,   508,   305,   380,     4,
       4,   100,     4,    85,    79,   325,   243,    57,   245,    79,
     247,   523,   249,    83,   526,    85,    86,     5,    83,   166,
      85,    86,    83,    85,    85,    86,   346,    83,     4,    85,
      56,    56,   179,   545,   181,   425,   418,    55,   550,   169,
     339,   423,   172,   173,   174,   168,   176,    83,    52,    85,
     401,   333,    56,   194,    56,   375,   179,   156,   181,   470,
      64,     4,    68,    81,     5,    83,    72,     5,   305,   168,
     217,   548,   454,   455,    80,    79,   553,    55,   315,    85,
      56,    84,   279,   276,   207,   184,   497,   234,   332,     4,
     441,   492,   239,   285,   101,   225,   103,   220,   228,    83,
     230,   242,   507,    81,   509,    83,   253,   518,   320,   232,
      62,   234,   211,    56,   255,    43,   239,   397,    70,   218,
     440,   220,   523,     4,   314,   526,    78,   273,    36,   276,
     367,    59,     5,   232,    55,     5,    53,    65,   285,   286,
     263,    69,    59,   387,    72,    73,    67,     5,   179,   248,
     181,   250,   299,    74,   253,    72,   279,    85,   288,    54,
      55,    83,    83,    85,    86,    86,   378,   314,    85,     5,
      55,     5,   313,   320,   273,    55,   299,   414,   415,    52,
      53,     4,     5,    56,     5,    65,    59,    67,    83,   401,
      63,    86,    65,    55,    74,   343,    69,     5,    83,    72,
      73,    86,     5,    83,     4,     5,    86,    51,    55,   332,
      57,     5,    85,    86,    26,    27,    28,     5,   317,     4,
       5,   433,   369,   413,     5,   417,   373,   357,   358,   441,
       9,   378,    11,   332,   446,   534,    83,   336,     5,    86,
     339,     5,   522,     4,   343,     4,     5,   388,    50,   390,
      87,     7,    31,    86,   401,    83,    84,   469,    10,     6,
      39,    59,    41,    87,   387,    87,    45,    65,    20,   392,
     417,    69,   516,    38,    72,    73,     4,     5,     4,    31,
      34,   380,    34,     6,   496,    81,   433,    85,   387,    41,
       4,     5,     5,   392,   441,     4,    52,    53,     4,   446,
      56,     4,     5,    59,    23,    24,    57,    63,     4,    65,
     433,    23,    24,    69,    52,    53,    72,    73,    56,   418,
       4,    59,   469,   470,   423,    63,   425,    65,   476,    85,
      86,    69,   529,    40,    72,    73,     4,    10,   468,     5,
     552,   464,     5,     5,   443,     5,   469,    85,    86,   496,
     497,   499,   500,     4,    21,   454,   455,    37,     5,   482,
       5,    54,    57,     5,     5,     4,    49,    65,     4,     4,
      68,   518,   495,   496,    72,    14,    15,   476,     6,    18,
      19,   480,    80,    22,    23,     5,   516,    85,    86,    59,
      29,    30,    31,   516,    38,     4,    35,    40,     4,    69,
     499,   500,    72,    73,     4,   552,   529,    46,    47,    48,
       5,    12,    13,     5,     5,    85,    17,   516,     5,     5,
      58,     5,     5,    24,    25,     5,     5,     5,    66,   552,
      31,    32,    59,    71,     5,   534,     5,    75,    76,    77,
      41,    42,    69,    44,     4,    72,    73,    85,    16,     4,
       4,    33,     5,     4,    16,     7,    82,     4,    85,    57,
       4,     4,     8,     5,     5,     4,    60,     5,     4,     4,
      82,     5,     5,     5,     5,     4,    57,     5,     5,    56,
       5,     5,     4,     6,     5,     5,     4,     4,   434,     5,
       5,     5,     5,     5,     5,     4,     4,   403,     5,     5,
       5,     5,     4,   344,     5,     5,     5,     5,     5,     5,
       5,     4,     4,    80,     5,     5,   553,   477,   516,   445,
     550,   137,   129,   322,   364,   419,   382,   248,   335,   367,
     428,   116,   181,   334,   446,   399,   286,   299,    10,   336,
      66,   480,    -1,    -1,    74,    -1,    96,   184,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    89,    90,   110,   134,    61,     0,     4,    62,
      70,    78,    85,   208,   226,   209,   226,   211,   226,     5,
       5,     5,    92,   112,   136,     4,     5,    91,    93,    94,
      95,    96,    99,   100,     4,     5,    94,    99,   111,   113,
     114,   126,     4,     5,    94,    99,   135,   137,   138,   139,
     142,   143,   146,   151,   164,     9,    11,    31,    39,    41,
      45,    10,    20,    34,    12,    13,    17,    24,    25,    32,
      42,    44,   212,   226,   209,   210,    84,   224,   228,     4,
      97,    98,     4,    14,    15,    18,    19,    22,    23,    29,
      30,    31,    35,    46,    47,    48,   219,   220,   190,   222,
     226,   213,   226,   214,   226,    83,   198,   199,   227,   141,
     191,   223,   227,   208,     4,    52,    56,    64,    79,   165,
     167,   168,   169,   175,   176,   177,     4,    56,   147,   148,
     149,   150,   186,   190,   216,   226,     4,   144,   145,    36,
     101,   210,     5,     5,   224,   193,   226,    98,     5,    26,
      27,    28,   220,     5,     5,   222,   226,   101,   101,   199,
       5,     4,     5,   140,     5,   223,   227,     5,    53,    59,
      63,    65,    69,    72,    73,    86,   175,   193,   229,   178,
     228,   178,     5,   165,    43,    59,    65,    69,    72,    73,
     193,    55,   202,     5,     4,   149,     5,    51,   152,   193,
     145,     5,     4,    50,   102,   192,   225,   229,    87,    87,
      87,     6,   222,    34,   115,    38,   127,    81,     6,   223,
     171,   173,   226,   227,   229,   165,     4,     4,   165,   165,
     165,   165,   172,     5,   194,   196,   202,   227,   229,   194,
     196,   216,     4,   186,     4,   186,   186,   186,   174,    57,
       4,    40,   153,   189,   192,     4,   182,   183,   185,    10,
     103,     5,   225,   229,     5,     5,     5,    58,    66,    71,
      75,    76,    77,   206,   207,   226,     4,    21,   116,     4,
     165,   170,   221,    37,   128,   227,   206,   171,   165,   166,
     192,   192,   165,     5,   166,     5,     5,   171,    54,   194,
     195,    54,    57,    57,     5,   186,   187,   192,   186,     5,
     187,     5,   173,     4,    56,   179,   186,   217,   218,   226,
       4,   154,   155,   156,   221,    49,   159,     5,   188,   226,
     227,     5,    53,    59,    72,   193,     4,    38,   104,     6,
     225,   190,   199,     4,   117,   118,    40,   119,     5,     4,
     129,     5,   223,   191,     5,   166,     5,     5,     5,     5,
       5,   195,   187,     5,     5,     5,     5,    72,   227,   228,
     186,   218,     5,    81,   197,   201,   202,   227,     4,   156,
       4,   160,   161,   162,   221,    16,   163,   171,     4,   183,
       4,   185,   172,   213,   170,    33,   105,   206,     5,   214,
     118,     4,   120,   121,   122,   221,    16,   125,     7,    82,
     165,   165,   150,    56,   179,    57,   227,   227,     4,   157,
     158,   221,   217,     4,   162,     4,     5,   171,   183,   184,
       5,     5,   204,     4,   106,   107,   108,     5,   192,   204,
     201,     4,   122,     4,     5,   131,    60,     5,     5,     5,
     186,   186,    57,   223,   217,     4,   158,     5,     5,    56,
     218,     5,   184,     5,     4,     5,   203,    65,    67,    74,
     200,   202,   227,   229,   107,     5,     4,   123,   124,   221,
     214,   215,     4,     5,   130,   132,   168,   180,   197,     5,
      82,   217,   181,     5,   229,     4,   165,   200,   198,   214,
       4,   124,     5,     5,   215,     5,    65,    68,    72,    80,
     229,     5,     5,     4,    57,   180,     8,   229,   200,   198,
       5,   214,     4,   170,     4,   168,   170,     5,     5,     4,
     129,   165,   171,   205,     6,   198,     5,     5,   192,   180,
       5,   180,     5,   206,     5,     5,     5,     5,     5,     4,
     132,   133,     4,   108,   109,   133,     5,   109,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    89,    89,    90,    91,    91,    91,    91,
      91,    91,    92,    92,    93,    94,    95,    96,    97,    98,
      98,    99,   100,   101,   102,   102,   103,   104,   105,   105,
     106,   106,   107,   107,   108,   108,   108,   109,   109,   110,
     111,   111,   111,   111,   111,   112,   112,   113,   114,   115,
     115,   116,   117,   118,   118,   119,   120,   120,   121,   121,
     122,   122,   123,   124,   124,   125,   126,   127,   128,   128,
     129,   130,   130,   130,   131,   131,   132,   132,   132,   133,
     133,   134,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   136,   137,   138,   139,   140,   141,   141,
     142,   143,   144,   145,   145,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   150,   150,   150,   151,   152,   153,
     154,   154,   155,   155,   156,   156,   157,   158,   158,   159,
     160,   160,   161,   162,   162,   163,   164,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   166,
     166,   167,   167,   168,   169,   170,   170,   171,   171,   172,
     172,   173,   173,   174,   174,   175,   175,   176,   176,   177,
     177,   178,   178,   179,   180,   180,   181,   181,   182,   182,
     183,   183,   184,   184,   185,   185,   186,   186,   186,   186,
     186,   187,   187,   188,   188,   189,   189,   190,   190,   191,
     191,   192,   192,   193,   194,   194,   194,   195,   195,   196,
     197,   197,   198,   199,   199,   200,   200,   200,   201,   201,
     202,   203,   204,   204,   205,   205,   205,   206,   206,   207,
     207,   207,   207,   207,   207,   208,   209,   210,   210,   211,
     212,   213,   214,   215,   215,   216,   217,   218,   218,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   220,   220,   221,   222,   222,
     223,   223,   224,   224,   225,   225,   226,   227,   228,   229
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     8,     1,     1,     1,     1,
       1,     1,     0,     2,     4,     4,     4,     4,     4,     1,
       2,     4,     9,     4,     2,     0,     5,     2,     2,     0,
       9,     1,     1,     2,     4,     6,     5,     1,     2,     8,
       1,     1,     1,     1,     1,     0,     2,     4,     9,     4,
       0,     2,     4,     1,     2,     2,     1,     1,     4,     4,
       1,     2,     4,     1,     2,     4,     7,     2,     2,     0,
       4,     1,     7,     3,     0,     2,     5,     5,     1,     1,
       2,     8,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     4,     4,     4,     8,     0,     2,
       4,     4,     4,     1,     2,     4,     1,     4,     1,     7,
       1,     2,     1,     4,     7,     5,     8,     8,     4,     2,
       1,     1,     4,     4,     1,     2,     4,     1,     2,     2,
       1,     1,     6,     1,     2,     4,     4,     5,     5,     5,
       4,     7,     7,     2,     4,     1,     1,     1,     1,     1,
       2,     1,     3,     4,     5,     1,     1,     1,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     4,     4,     4,
       4,     1,     0,     4,     1,     4,     0,     2,     5,     1,
       1,     4,     1,     2,     4,     5,     5,     5,     5,     4,
       4,     1,     2,     1,     1,     0,     2,     1,     5,     1,
       5,     1,     5,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     4,
       1,     5,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     1,     2,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     1,     1,     1,     1
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
#line 442 "epddl.y"
                    { (yyval.maindef_) = new Domain((yyvsp[0].domaindef_)); result->maindef_ = (yyval.maindef_); }
#line 1912 "Parser.C"
    break;

  case 3: /* MainDef: LibraryDef  */
#line 443 "epddl.y"
               { (yyval.maindef_) = new ActionTypeLibrary((yyvsp[0].librarydef_)); result->maindef_ = (yyval.maindef_); }
#line 1918 "Parser.C"
    break;

  case 4: /* MainDef: ProblemDef  */
#line 444 "epddl.y"
               { (yyval.maindef_) = new Problem((yyvsp[0].problemdef_)); result->maindef_ = (yyval.maindef_); }
#line 1924 "Parser.C"
    break;

  case 5: /* DomainDef: _LPAREN _KW_define _LPAREN _KW_domain DomainName _RPAREN ListDomainItemDef _RPAREN  */
#line 446 "epddl.y"
                                                                                               { (yyval.domaindef_) = new EPDDLDomain((yyvsp[-3].domainname_), (yyvsp[-1].listdomainitemdef_)); }
#line 1930 "Parser.C"
    break;

  case 6: /* DomainItemDef: DomainLibrariesNameDef  */
#line 448 "epddl.y"
                                       { (yyval.domainitemdef_) = new EPDDLDomLibrary((yyvsp[0].domainlibrariesnamedef_)); }
#line 1936 "Parser.C"
    break;

  case 7: /* DomainItemDef: RequireDef  */
#line 449 "epddl.y"
               { (yyval.domainitemdef_) = new EPDDLDomRequire((yyvsp[0].requiredef_)); }
#line 1942 "Parser.C"
    break;

  case 8: /* DomainItemDef: TypesDef  */
#line 450 "epddl.y"
             { (yyval.domainitemdef_) = new EPDDLDomTypes((yyvsp[0].typesdef_)); }
#line 1948 "Parser.C"
    break;

  case 9: /* DomainItemDef: PredicateListDef  */
#line 451 "epddl.y"
                     { (yyval.domainitemdef_) = new EPDDLDomPredicates((yyvsp[0].predicatelistdef_)); }
#line 1954 "Parser.C"
    break;

  case 10: /* DomainItemDef: ModalitiesDef  */
#line 452 "epddl.y"
                  { (yyval.domainitemdef_) = new EPDDLDomModalities((yyvsp[0].modalitiesdef_)); }
#line 1960 "Parser.C"
    break;

  case 11: /* DomainItemDef: ActionDef  */
#line 453 "epddl.y"
              { (yyval.domainitemdef_) = new EPDDLDomAction((yyvsp[0].actiondef_)); }
#line 1966 "Parser.C"
    break;

  case 12: /* ListDomainItemDef: %empty  */
#line 455 "epddl.y"
                                { (yyval.listdomainitemdef_) = new ListDomainItemDef(); }
#line 1972 "Parser.C"
    break;

  case 13: /* ListDomainItemDef: ListDomainItemDef DomainItemDef  */
#line 456 "epddl.y"
                                    { (yyvsp[-1].listdomainitemdef_)->push_back((yyvsp[0].domainitemdef_)); (yyval.listdomainitemdef_) = (yyvsp[-1].listdomainitemdef_); }
#line 1978 "Parser.C"
    break;

  case 14: /* DomainLibrariesNameDef: _LPAREN _SYMB_2 ListLibraryName _RPAREN  */
#line 458 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listlibraryname_)->begin(),(yyvsp[-1].listlibraryname_)->end()) ;(yyval.domainlibrariesnamedef_) = new EPDDLDomLibraryNames((yyvsp[-1].listlibraryname_)); }
#line 1984 "Parser.C"
    break;

  case 15: /* RequireDef: _LPAREN _SYMB_3 ListRequirementKey _RPAREN  */
#line 460 "epddl.y"
                                                        { std::reverse((yyvsp[-1].listrequirementkey_)->begin(),(yyvsp[-1].listrequirementkey_)->end()) ;(yyval.requiredef_) = new EPDDLRequire((yyvsp[-1].listrequirementkey_)); }
#line 1990 "Parser.C"
    break;

  case 16: /* TypesDef: _LPAREN _SYMB_4 TypedIdentList _RPAREN  */
#line 462 "epddl.y"
                                                  { (yyval.typesdef_) = new EPDDLTypes((yyvsp[-1].typedidentlist_)); }
#line 1996 "Parser.C"
    break;

  case 17: /* PredicateListDef: _LPAREN _SYMB_5 ListPredicateDef _RPAREN  */
#line 464 "epddl.y"
                                                            { std::reverse((yyvsp[-1].listpredicatedef_)->begin(),(yyvsp[-1].listpredicatedef_)->end()) ;(yyval.predicatelistdef_) = new EPDDLPredicateList((yyvsp[-1].listpredicatedef_)); }
#line 2002 "Parser.C"
    break;

  case 18: /* PredicateDef: _LPAREN PredicateName TypedVariableList _RPAREN  */
#line 466 "epddl.y"
                                                               { (yyval.predicatedef_) = new EPDDLPredicateDef((yyvsp[-2].predicatename_), (yyvsp[-1].typedvariablelist_)); }
#line 2008 "Parser.C"
    break;

  case 19: /* ListPredicateDef: PredicateDef  */
#line 468 "epddl.y"
                                { (yyval.listpredicatedef_) = new ListPredicateDef(); (yyval.listpredicatedef_)->push_back((yyvsp[0].predicatedef_)); }
#line 2014 "Parser.C"
    break;

  case 20: /* ListPredicateDef: PredicateDef ListPredicateDef  */
#line 469 "epddl.y"
                                  { (yyvsp[0].listpredicatedef_)->push_back((yyvsp[-1].predicatedef_)); (yyval.listpredicatedef_) = (yyvsp[0].listpredicatedef_); }
#line 2020 "Parser.C"
    break;

  case 21: /* ModalitiesDef: _LPAREN _SYMB_6 ListModalityName _RPAREN  */
#line 471 "epddl.y"
                                                         { std::reverse((yyvsp[-1].listmodalityname_)->begin(),(yyvsp[-1].listmodalityname_)->end()) ;(yyval.modalitiesdef_) = new EPDDLModalities((yyvsp[-1].listmodalityname_)); }
#line 2026 "Parser.C"
    break;

  case 22: /* ActionDef: _LPAREN _SYMB_7 ActionName ParametersDef ActionConditionDef ActionTypeSignatureDef ActionPreDef ActionObsDef _RPAREN  */
#line 473 "epddl.y"
                                                                                                                                 { (yyval.actiondef_) = new EPDDLAction((yyvsp[-6].actionname_), (yyvsp[-5].parametersdef_), (yyvsp[-4].actionconditiondef_), (yyvsp[-3].actiontypesignaturedef_), (yyvsp[-2].actionpredef_), (yyvsp[-1].actionobsdef_)); }
#line 2032 "Parser.C"
    break;

  case 23: /* ParametersDef: _SYMB_8 _LPAREN TypedVariableList _RPAREN  */
#line 475 "epddl.y"
                                                          { (yyval.parametersdef_) = new Parameters((yyvsp[-1].typedvariablelist_)); }
#line 2038 "Parser.C"
    break;

  case 24: /* ActionConditionDef: _SYMB_9 ConditionFormula  */
#line 477 "epddl.y"
                                              { (yyval.actionconditiondef_) = new ActionCond((yyvsp[0].conditionformula_)); }
#line 2044 "Parser.C"
    break;

  case 25: /* ActionConditionDef: %empty  */
#line 478 "epddl.y"
                { (yyval.actionconditiondef_) = new EmptyActionCond(); }
#line 2050 "Parser.C"
    break;

  case 26: /* ActionTypeSignatureDef: _SYMB_10 _LPAREN ActionTypeName ListParameter _RPAREN  */
#line 480 "epddl.y"
                                                                               { (yyval.actiontypesignaturedef_) = new ActionSignature((yyvsp[-2].actiontypename_), (yyvsp[-1].listparameter_)); }
#line 2056 "Parser.C"
    break;

  case 27: /* ActionPreDef: _SYMB_11 FormulaOrEmpty  */
#line 482 "epddl.y"
                                       { (yyval.actionpredef_) = new ActionPre((yyvsp[0].formulaorempty_)); }
#line 2062 "Parser.C"
    break;

  case 28: /* ActionObsDef: _SYMB_12 ListObsConditionDef  */
#line 484 "epddl.y"
                                            { std::reverse((yyvsp[0].listobsconditiondef_)->begin(),(yyvsp[0].listobsconditiondef_)->end()) ;(yyval.actionobsdef_) = new ActionObs((yyvsp[0].listobsconditiondef_)); }
#line 2068 "Parser.C"
    break;

  case 29: /* ActionObsDef: %empty  */
#line 485 "epddl.y"
                { (yyval.actionobsdef_) = new EmptyActionObs(); }
#line 2074 "Parser.C"
    break;

  case 30: /* ObsConditionDef: _LPAREN _KW_forall _LPAREN Variable _MINUS Type _RPAREN ListObsCondition _RPAREN  */
#line 487 "epddl.y"
                                                                                                   { std::reverse((yyvsp[-1].listobscondition_)->begin(),(yyvsp[-1].listobscondition_)->end()) ;(yyval.obsconditiondef_) = new UniversalObsCond((yyvsp[-5]._variable), (yyvsp[-3].type_), (yyvsp[-1].listobscondition_)); }
#line 2080 "Parser.C"
    break;

  case 31: /* ObsConditionDef: ObsCondition  */
#line 488 "epddl.y"
                 { (yyval.obsconditiondef_) = new ObsCond((yyvsp[0].obscondition_)); }
#line 2086 "Parser.C"
    break;

  case 32: /* ListObsConditionDef: ObsConditionDef  */
#line 490 "epddl.y"
                                      { (yyval.listobsconditiondef_) = new ListObsConditionDef(); (yyval.listobsconditiondef_)->push_back((yyvsp[0].obsconditiondef_)); }
#line 2092 "Parser.C"
    break;

  case 33: /* ListObsConditionDef: ObsConditionDef ListObsConditionDef  */
#line 491 "epddl.y"
                                        { (yyvsp[0].listobsconditiondef_)->push_back((yyvsp[-1].obsconditiondef_)); (yyval.listobsconditiondef_) = (yyvsp[0].listobsconditiondef_); }
#line 2098 "Parser.C"
    break;

  case 34: /* ObsCondition: _LPAREN ObservingAgent ObservingAgentGroup _RPAREN  */
#line 493 "epddl.y"
                                                                  { (yyval.obscondition_) = new TrivialObsCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2104 "Parser.C"
    break;

  case 35: /* ObsCondition: _LPAREN _KW_if Formula ObservingAgent ObservingAgentGroup _RPAREN  */
#line 494 "epddl.y"
                                                                      { (yyval.obscondition_) = new IfObsCond((yyvsp[-3].formula_), (yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2110 "Parser.C"
    break;

  case 36: /* ObsCondition: _LPAREN _KW_otherwise ObservingAgent ObservingAgentGroup _RPAREN  */
#line 495 "epddl.y"
                                                                     { (yyval.obscondition_) = new OtherwiseObsCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2116 "Parser.C"
    break;

  case 37: /* ListObsCondition: ObsCondition  */
#line 497 "epddl.y"
                                { (yyval.listobscondition_) = new ListObsCondition(); (yyval.listobscondition_)->push_back((yyvsp[0].obscondition_)); }
#line 2122 "Parser.C"
    break;

  case 38: /* ListObsCondition: ObsCondition ListObsCondition  */
#line 498 "epddl.y"
                                  { (yyvsp[0].listobscondition_)->push_back((yyvsp[-1].obscondition_)); (yyval.listobscondition_) = (yyvsp[0].listobscondition_); }
#line 2128 "Parser.C"
    break;

  case 39: /* LibraryDef: _LPAREN _KW_define _LPAREN _KW_library LibraryName _RPAREN ListLibraryItemDef _RPAREN  */
#line 500 "epddl.y"
                                                                                                   { (yyval.librarydef_) = new EPDDLLibrary((yyvsp[-3].libraryname_), (yyvsp[-1].listlibraryitemdef_)); }
#line 2134 "Parser.C"
    break;

  case 40: /* LibraryItemDef: RequireDef  */
#line 502 "epddl.y"
                            { (yyval.libraryitemdef_) = new EPDDLLibRequire((yyvsp[0].requiredef_)); }
#line 2140 "Parser.C"
    break;

  case 41: /* LibraryItemDef: ModalitiesDef  */
#line 503 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibModalities((yyvsp[0].modalitiesdef_)); }
#line 2146 "Parser.C"
    break;

  case 42: /* LibraryItemDef: ObservabilityGroupsDef  */
#line 504 "epddl.y"
                           { (yyval.libraryitemdef_) = new EPDDLLibObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 2152 "Parser.C"
    break;

  case 43: /* LibraryItemDef: ActionTypeDef  */
#line 505 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibActionType((yyvsp[0].actiontypedef_)); }
#line 2158 "Parser.C"
    break;

  case 44: /* LibraryItemDef: EventDef  */
#line 506 "epddl.y"
             { (yyval.libraryitemdef_) = new EPDDLLibEvent((yyvsp[0].eventdef_)); }
#line 2164 "Parser.C"
    break;

  case 45: /* ListLibraryItemDef: %empty  */
#line 508 "epddl.y"
                                 { (yyval.listlibraryitemdef_) = new ListLibraryItemDef(); }
#line 2170 "Parser.C"
    break;

  case 46: /* ListLibraryItemDef: ListLibraryItemDef LibraryItemDef  */
#line 509 "epddl.y"
                                      { (yyvsp[-1].listlibraryitemdef_)->push_back((yyvsp[0].libraryitemdef_)); (yyval.listlibraryitemdef_) = (yyvsp[-1].listlibraryitemdef_); }
#line 2176 "Parser.C"
    break;

  case 47: /* ObservabilityGroupsDef: _LPAREN _SYMB_14 ListObservingAgentGroup _RPAREN  */
#line 511 "epddl.y"
                                                                          { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.observabilitygroupsdef_) = new EPDDLObsGroupsNames((yyvsp[-1].listobservingagentgroup_)); }
#line 2182 "Parser.C"
    break;

  case 48: /* ActionTypeDef: _LPAREN _SYMB_10 ActionTypeName ParametersDef ActionTypeGroupsDef ActionTypeEventsDef ActionTypeRelDef ActionTypeDesignDef _RPAREN  */
#line 513 "epddl.y"
                                                                                                                                                   { (yyval.actiontypedef_) = new EPDDLActType((yyvsp[-6].actiontypename_), (yyvsp[-5].parametersdef_), (yyvsp[-4].actiontypegroupsdef_), (yyvsp[-3].actiontypeeventsdef_), (yyvsp[-2].actiontypereldef_), (yyvsp[-1].actiontypedesigndef_)); }
#line 2188 "Parser.C"
    break;

  case 49: /* ActionTypeGroupsDef: _SYMB_14 _LPAREN ListObservingAgentGroup _RPAREN  */
#line 515 "epddl.y"
                                                                       { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.actiontypegroupsdef_) = new ActTypeGroups((yyvsp[-1].listobservingagentgroup_)); }
#line 2194 "Parser.C"
    break;

  case 50: /* ActionTypeGroupsDef: %empty  */
#line 516 "epddl.y"
                { (yyval.actiontypegroupsdef_) = new EmptyActTypeGroups(); }
#line 2200 "Parser.C"
    break;

  case 51: /* ActionTypeEventsDef: _SYMB_15 ListEventSignature  */
#line 518 "epddl.y"
                                                  { std::reverse((yyvsp[0].listeventsignature_)->begin(),(yyvsp[0].listeventsignature_)->end()) ;(yyval.actiontypeeventsdef_) = new ActTypeEvents((yyvsp[0].listeventsignature_)); }
#line 2206 "Parser.C"
    break;

  case 52: /* EventSignature: _LPAREN EventName ListParameter _RPAREN  */
#line 520 "epddl.y"
                                                         { (yyval.eventsignature_) = new EventSign((yyvsp[-2].eventname_), (yyvsp[-1].listparameter_)); }
#line 2212 "Parser.C"
    break;

  case 53: /* ListEventSignature: EventSignature  */
#line 522 "epddl.y"
                                    { (yyval.listeventsignature_) = new ListEventSignature(); (yyval.listeventsignature_)->push_back((yyvsp[0].eventsignature_)); }
#line 2218 "Parser.C"
    break;

  case 54: /* ListEventSignature: EventSignature ListEventSignature  */
#line 523 "epddl.y"
                                      { (yyvsp[0].listeventsignature_)->push_back((yyvsp[-1].eventsignature_)); (yyval.listeventsignature_) = (yyvsp[0].listeventsignature_); }
#line 2224 "Parser.C"
    break;

  case 55: /* ActionTypeRelDef: _SYMB_16 ActionRelations  */
#line 525 "epddl.y"
                                            { (yyval.actiontypereldef_) = new ActTypeRel((yyvsp[0].actionrelations_)); }
#line 2230 "Parser.C"
    break;

  case 56: /* ActionRelations: ListEventRelation  */
#line 527 "epddl.y"
                                    { std::reverse((yyvsp[0].listeventrelation_)->begin(),(yyvsp[0].listeventrelation_)->end()) ;(yyval.actionrelations_) = new EventsActionRel((yyvsp[0].listeventrelation_)); }
#line 2236 "Parser.C"
    break;

  case 57: /* ActionRelations: TrivialDef  */
#line 528 "epddl.y"
               { (yyval.actionrelations_) = new TrivialActionRel((yyvsp[0].trivialdef_)); }
#line 2242 "Parser.C"
    break;

  case 58: /* EventRelation: _LPAREN AgentGroup ListEventNamePair _RPAREN  */
#line 530 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listeventnamepair_)->begin(),(yyvsp[-1].listeventnamepair_)->end()) ;(yyval.eventrelation_) = new EventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listeventnamepair_)); }
#line 2248 "Parser.C"
    break;

  case 59: /* EventRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 531 "epddl.y"
                                          { (yyval.eventrelation_) = new TrivialEventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2254 "Parser.C"
    break;

  case 60: /* ListEventRelation: EventRelation  */
#line 533 "epddl.y"
                                  { (yyval.listeventrelation_) = new ListEventRelation(); (yyval.listeventrelation_)->push_back((yyvsp[0].eventrelation_)); }
#line 2260 "Parser.C"
    break;

  case 61: /* ListEventRelation: EventRelation ListEventRelation  */
#line 534 "epddl.y"
                                    { (yyvsp[0].listeventrelation_)->push_back((yyvsp[-1].eventrelation_)); (yyval.listeventrelation_) = (yyvsp[0].listeventrelation_); }
#line 2266 "Parser.C"
    break;

  case 62: /* EventNamePair: _LPAREN EventName EventName _RPAREN  */
#line 536 "epddl.y"
                                                    { (yyval.eventnamepair_) = new EventPair((yyvsp[-2].eventname_), (yyvsp[-1].eventname_)); }
#line 2272 "Parser.C"
    break;

  case 63: /* ListEventNamePair: EventNamePair  */
#line 538 "epddl.y"
                                  { (yyval.listeventnamepair_) = new ListEventNamePair(); (yyval.listeventnamepair_)->push_back((yyvsp[0].eventnamepair_)); }
#line 2278 "Parser.C"
    break;

  case 64: /* ListEventNamePair: EventNamePair ListEventNamePair  */
#line 539 "epddl.y"
                                    { (yyvsp[0].listeventnamepair_)->push_back((yyvsp[-1].eventnamepair_)); (yyval.listeventnamepair_) = (yyvsp[0].listeventnamepair_); }
#line 2284 "Parser.C"
    break;

  case 65: /* ActionTypeDesignDef: _SYMB_17 _LPAREN ListEventName _RPAREN  */
#line 541 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listeventname_)->begin(),(yyvsp[-1].listeventname_)->end()) ;(yyval.actiontypedesigndef_) = new ActTypeDesign((yyvsp[-1].listeventname_)); }
#line 2290 "Parser.C"
    break;

  case 66: /* EventDef: _LPAREN _SYMB_18 EventName ParametersDef EventPreDef EventPostDef _RPAREN  */
#line 543 "epddl.y"
                                                                                     { (yyval.eventdef_) = new EPDDLEvent((yyvsp[-4].eventname_), (yyvsp[-3].parametersdef_), (yyvsp[-2].eventpredef_), (yyvsp[-1].eventpostdef_)); }
#line 2296 "Parser.C"
    break;

  case 67: /* EventPreDef: _SYMB_11 FormulaOrEmpty  */
#line 545 "epddl.y"
                                      { (yyval.eventpredef_) = new EventPre((yyvsp[0].formulaorempty_)); }
#line 2302 "Parser.C"
    break;

  case 68: /* EventPostDef: _SYMB_19 PostconditionBlock  */
#line 547 "epddl.y"
                                           { (yyval.eventpostdef_) = new EventPost((yyvsp[0].postconditionblock_)); }
#line 2308 "Parser.C"
    break;

  case 69: /* EventPostDef: %empty  */
#line 548 "epddl.y"
                { (yyval.eventpostdef_) = new EmptyEventPost(); }
#line 2314 "Parser.C"
    break;

  case 70: /* PostconditionBlock: _LPAREN _COLON ListPostcondition _RPAREN  */
#line 550 "epddl.y"
                                                              { (yyval.postconditionblock_) = new PostAnonBlock((yyvsp[-1].listpostcondition_)); }
#line 2320 "Parser.C"
    break;

  case 71: /* Postcondition: SimplePostcondition  */
#line 552 "epddl.y"
                                    { (yyval.postcondition_) = new SimplePost((yyvsp[0].simplepostcondition_)); }
#line 2326 "Parser.C"
    break;

  case 72: /* Postcondition: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN ListSimplePostcondition _RPAREN  */
#line 553 "epddl.y"
                                                                                         { std::reverse((yyvsp[-1].listsimplepostcondition_)->begin(),(yyvsp[-1].listsimplepostcondition_)->end()) ;(yyval.postcondition_) = new UniversalPost((yyvsp[-3].typedvariablelist_), (yyvsp[-1].listsimplepostcondition_)); }
#line 2332 "Parser.C"
    break;

  case 73: /* Postcondition: _LPAREN Variable _RPAREN  */
#line 554 "epddl.y"
                             { (yyval.postcondition_) = new VarPost((yyvsp[-1]._variable)); }
#line 2338 "Parser.C"
    break;

  case 74: /* ListPostcondition: %empty  */
#line 556 "epddl.y"
                                { (yyval.listpostcondition_) = new ListPostcondition(); }
#line 2344 "Parser.C"
    break;

  case 75: /* ListPostcondition: ListPostcondition Postcondition  */
#line 557 "epddl.y"
                                    { (yyvsp[-1].listpostcondition_)->push_back((yyvsp[0].postcondition_)); (yyval.listpostcondition_) = (yyvsp[-1].listpostcondition_); }
#line 2350 "Parser.C"
    break;

  case 76: /* SimplePostcondition: _LPAREN _KW_iff FormulaOrEmpty Literal _RPAREN  */
#line 559 "epddl.y"
                                                                     { (yyval.simplepostcondition_) = new IffPost((yyvsp[-2].formulaorempty_), (yyvsp[-1].literal_)); }
#line 2356 "Parser.C"
    break;

  case 77: /* SimplePostcondition: _LPAREN _KW_when FormulaOrEmpty Literal _RPAREN  */
#line 560 "epddl.y"
                                                    { (yyval.simplepostcondition_) = new WhenPost((yyvsp[-2].formulaorempty_), (yyvsp[-1].literal_)); }
#line 2362 "Parser.C"
    break;

  case 78: /* SimplePostcondition: Literal  */
#line 561 "epddl.y"
            { (yyval.simplepostcondition_) = new TrivialLiteralPost((yyvsp[0].literal_)); }
#line 2368 "Parser.C"
    break;

  case 79: /* ListSimplePostcondition: SimplePostcondition  */
#line 563 "epddl.y"
                                              { (yyval.listsimplepostcondition_) = new ListSimplePostcondition(); (yyval.listsimplepostcondition_)->push_back((yyvsp[0].simplepostcondition_)); }
#line 2374 "Parser.C"
    break;

  case 80: /* ListSimplePostcondition: SimplePostcondition ListSimplePostcondition  */
#line 564 "epddl.y"
                                                { (yyvsp[0].listsimplepostcondition_)->push_back((yyvsp[-1].simplepostcondition_)); (yyval.listsimplepostcondition_) = (yyvsp[0].listsimplepostcondition_); }
#line 2380 "Parser.C"
    break;

  case 81: /* ProblemDef: _LPAREN _KW_define _LPAREN _KW_problem ProblemName _RPAREN ListProblemItemDef _RPAREN  */
#line 566 "epddl.y"
                                                                                                   { (yyval.problemdef_) = new EPDDLProblem((yyvsp[-3].problemname_), (yyvsp[-1].listproblemitemdef_)); }
#line 2386 "Parser.C"
    break;

  case 82: /* ProblemItemDef: ProblemDomainNameDef  */
#line 568 "epddl.y"
                                      { (yyval.problemitemdef_) = new EPDDLProbDomain((yyvsp[0].problemdomainnamedef_)); }
#line 2392 "Parser.C"
    break;

  case 83: /* ProblemItemDef: RequireDef  */
#line 569 "epddl.y"
               { (yyval.problemitemdef_) = new EPDDLProbRequire((yyvsp[0].requiredef_)); }
#line 2398 "Parser.C"
    break;

  case 84: /* ProblemItemDef: ModalitiesDef  */
#line 570 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbModalities((yyvsp[0].modalitiesdef_)); }
#line 2404 "Parser.C"
    break;

  case 85: /* ProblemItemDef: AgentNamesDef  */
#line 571 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbAgents((yyvsp[0].agentnamesdef_)); }
#line 2410 "Parser.C"
    break;

  case 86: /* ProblemItemDef: AgentGroupsListDef  */
#line 572 "epddl.y"
                       { (yyval.problemitemdef_) = new EPDDLProbAgentGroups((yyvsp[0].agentgroupslistdef_)); }
#line 2416 "Parser.C"
    break;

  case 87: /* ProblemItemDef: ObjectNamesDef  */
#line 573 "epddl.y"
                   { (yyval.problemitemdef_) = new EPDDLProbObjects((yyvsp[0].objectnamesdef_)); }
#line 2422 "Parser.C"
    break;

  case 88: /* ProblemItemDef: StaticPredListDef  */
#line 574 "epddl.y"
                      { (yyval.problemitemdef_) = new EPDDLProbStaticPred((yyvsp[0].staticpredlistdef_)); }
#line 2428 "Parser.C"
    break;

  case 89: /* ProblemItemDef: InitDef  */
#line 575 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbInit((yyvsp[0].initdef_)); }
#line 2434 "Parser.C"
    break;

  case 90: /* ProblemItemDef: StateDef  */
#line 576 "epddl.y"
             { (yyval.problemitemdef_) = new EPDDLProbInitState((yyvsp[0].statedef_)); }
#line 2440 "Parser.C"
    break;

  case 91: /* ProblemItemDef: GoalDef  */
#line 577 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbGoal((yyvsp[0].goaldef_)); }
#line 2446 "Parser.C"
    break;

  case 92: /* ListProblemItemDef: %empty  */
#line 579 "epddl.y"
                                 { (yyval.listproblemitemdef_) = new ListProblemItemDef(); }
#line 2452 "Parser.C"
    break;

  case 93: /* ListProblemItemDef: ListProblemItemDef ProblemItemDef  */
#line 580 "epddl.y"
                                      { (yyvsp[-1].listproblemitemdef_)->push_back((yyvsp[0].problemitemdef_)); (yyval.listproblemitemdef_) = (yyvsp[-1].listproblemitemdef_); }
#line 2458 "Parser.C"
    break;

  case 94: /* ProblemDomainNameDef: _LPAREN _SYMB_21 DomainName _RPAREN  */
#line 582 "epddl.y"
                                                           { (yyval.problemdomainnamedef_) = new EPDDLProbDomainName((yyvsp[-1].domainname_)); }
#line 2464 "Parser.C"
    break;

  case 95: /* AgentNamesDef: _LPAREN _SYMB_22 TypedAgentList _RPAREN  */
#line 584 "epddl.y"
                                                        { (yyval.agentnamesdef_) = new EPDDLAgentNames((yyvsp[-1].typedagentlist_)); }
#line 2470 "Parser.C"
    break;

  case 96: /* AgentGroupsListDef: _LPAREN _SYMB_23 ListAgentGroupDef _RPAREN  */
#line 586 "epddl.y"
                                                                { (yyval.agentgroupslistdef_) = new EPDDLAgentGroupsList((yyvsp[-1].listagentgroupdef_)); }
#line 2476 "Parser.C"
    break;

  case 97: /* AgentGroupDef: _LPAREN _LBRACE AgentName ListAgentName _RBRACE _KW_as AgentGroupName _RPAREN  */
#line 588 "epddl.y"
                                                                                              { std::reverse((yyvsp[-4].listagentname_)->begin(),(yyvsp[-4].listagentname_)->end()) ;(yyval.agentgroupdef_) = new EPDDLAgentGroupDef((yyvsp[-5]._agentname), (yyvsp[-4].listagentname_), (yyvsp[-1].agentgroupname_)); }
#line 2482 "Parser.C"
    break;

  case 98: /* ListAgentGroupDef: %empty  */
#line 590 "epddl.y"
                                { (yyval.listagentgroupdef_) = new ListAgentGroupDef(); }
#line 2488 "Parser.C"
    break;

  case 99: /* ListAgentGroupDef: ListAgentGroupDef AgentGroupDef  */
#line 591 "epddl.y"
                                    { (yyvsp[-1].listagentgroupdef_)->push_back((yyvsp[0].agentgroupdef_)); (yyval.listagentgroupdef_) = (yyvsp[-1].listagentgroupdef_); }
#line 2494 "Parser.C"
    break;

  case 100: /* ObjectNamesDef: _LPAREN _SYMB_26 TypedIdentList _RPAREN  */
#line 593 "epddl.y"
                                                         { (yyval.objectnamesdef_) = new EPDDLObjectNames((yyvsp[-1].typedidentlist_)); }
#line 2500 "Parser.C"
    break;

  case 101: /* StaticPredListDef: _LPAREN _SYMB_27 ListStaticPredDef _RPAREN  */
#line 595 "epddl.y"
                                                               { std::reverse((yyvsp[-1].liststaticpreddef_)->begin(),(yyvsp[-1].liststaticpreddef_)->end()) ;(yyval.staticpredlistdef_) = new EPDDLStaticPredList((yyvsp[-1].liststaticpreddef_)); }
#line 2506 "Parser.C"
    break;

  case 102: /* StaticPredDef: _LPAREN PredicateName ListGenericName _RPAREN  */
#line 597 "epddl.y"
                                                              { (yyval.staticpreddef_) = new EPDDLStaticPredDef((yyvsp[-2].predicatename_), (yyvsp[-1].listgenericname_)); }
#line 2512 "Parser.C"
    break;

  case 103: /* ListStaticPredDef: StaticPredDef  */
#line 599 "epddl.y"
                                  { (yyval.liststaticpreddef_) = new ListStaticPredDef(); (yyval.liststaticpreddef_)->push_back((yyvsp[0].staticpreddef_)); }
#line 2518 "Parser.C"
    break;

  case 104: /* ListStaticPredDef: StaticPredDef ListStaticPredDef  */
#line 600 "epddl.y"
                                    { (yyvsp[0].liststaticpreddef_)->push_back((yyvsp[-1].staticpreddef_)); (yyval.liststaticpreddef_) = (yyvsp[0].liststaticpreddef_); }
#line 2524 "Parser.C"
    break;

  case 105: /* InitDef: _LPAREN _SYMB_28 InitialStateDescr _RPAREN  */
#line 602 "epddl.y"
                                                     { (yyval.initdef_) = new EPDDLInitialState((yyvsp[-1].initialstatedescr_)); }
#line 2530 "Parser.C"
    break;

  case 106: /* InitialStateDescr: ListFTheoryFormula  */
#line 604 "epddl.y"
                                       { std::reverse((yyvsp[0].listftheoryformula_)->begin(),(yyvsp[0].listftheoryformula_)->end()) ;(yyval.initialstatedescr_) = new FinitaryTheoryDescr((yyvsp[0].listftheoryformula_)); }
#line 2536 "Parser.C"
    break;

  case 107: /* InitialStateDescr: _LPAREN _SYMB_29 StateName _RPAREN  */
#line 605 "epddl.y"
                                       { (yyval.initialstatedescr_) = new InitStateNameDescr((yyvsp[-1].statename_)); }
#line 2542 "Parser.C"
    break;

  case 108: /* FTheoryFormula: SimpleFTheoryFormula  */
#line 607 "epddl.y"
                                      { (yyval.ftheoryformula_) = new SimpleFTheoryForm((yyvsp[0].simpleftheoryformula_)); }
#line 2548 "Parser.C"
    break;

  case 109: /* FTheoryFormula: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN SimpleFTheoryFormula _RPAREN  */
#line 608 "epddl.y"
                                                                                      { (yyval.ftheoryformula_) = new UniversalFTheoryForm((yyvsp[-3].typedvariablelist_), (yyvsp[-1].simpleftheoryformula_)); }
#line 2554 "Parser.C"
    break;

  case 110: /* ListFTheoryFormula: FTheoryFormula  */
#line 610 "epddl.y"
                                    { (yyval.listftheoryformula_) = new ListFTheoryFormula(); (yyval.listftheoryformula_)->push_back((yyvsp[0].ftheoryformula_)); }
#line 2560 "Parser.C"
    break;

  case 111: /* ListFTheoryFormula: FTheoryFormula ListFTheoryFormula  */
#line 611 "epddl.y"
                                      { (yyvsp[0].listftheoryformula_)->push_back((yyvsp[-1].ftheoryformula_)); (yyval.listftheoryformula_) = (yyvsp[0].listftheoryformula_); }
#line 2566 "Parser.C"
    break;

  case 112: /* SimpleFTheoryFormula: PredicateFormula  */
#line 613 "epddl.y"
                                        { (yyval.simpleftheoryformula_) = new FTheoryPredForm((yyvsp[0].predicateformula_)); }
#line 2572 "Parser.C"
    break;

  case 113: /* SimpleFTheoryFormula: _LBRACK AllAgents _RBRACK PredicateFormula  */
#line 614 "epddl.y"
                                               { (yyval.simpleftheoryformula_) = new FTheoryCKPredForm((yyvsp[-2].allagents_), (yyvsp[0].predicateformula_)); }
#line 2578 "Parser.C"
    break;

  case 114: /* SimpleFTheoryFormula: _LBRACK AllAgents _RBRACK _LBRACK AgentName _RBRACK PredicateFormula  */
#line 615 "epddl.y"
                                                                         { (yyval.simpleftheoryformula_) = new FTheoryCKKPredForm((yyvsp[-5].allagents_), (yyvsp[-2]._agentname), (yyvsp[0].predicateformula_)); }
#line 2584 "Parser.C"
    break;

  case 115: /* SimpleFTheoryFormula: _LBRACK AllAgents _RBRACK KnowsWhether PredicateFormula  */
#line 616 "epddl.y"
                                                            { (yyval.simpleftheoryformula_) = new FTheoryCKOrKPredForm((yyvsp[-3].allagents_), (yyvsp[-1].knowswhether_), (yyvsp[0].predicateformula_)); }
#line 2590 "Parser.C"
    break;

  case 116: /* SimpleFTheoryFormula: _LBRACK AllAgents _RBRACK _LPAREN _KW_not KnowsWhether PredicateFormula _RPAREN  */
#line 617 "epddl.y"
                                                                                    { (yyval.simpleftheoryformula_) = new FTheoryCKAndKPredForm((yyvsp[-6].allagents_), (yyvsp[-2].knowswhether_), (yyvsp[-1].predicateformula_)); }
#line 2596 "Parser.C"
    break;

  case 117: /* StateDef: _LPAREN _SYMB_32 StateName StateWorldsDef StateRelDef StateValDef StateDesignDef _RPAREN  */
#line 619 "epddl.y"
                                                                                                    { (yyval.statedef_) = new EPDDLExplicitState((yyvsp[-5].statename_), (yyvsp[-4].stateworldsdef_), (yyvsp[-3].statereldef_), (yyvsp[-2].statevaldef_), (yyvsp[-1].statedesigndef_)); }
#line 2602 "Parser.C"
    break;

  case 118: /* StateWorldsDef: _SYMB_33 _LPAREN ListWorldName _RPAREN  */
#line 621 "epddl.y"
                                                        { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.stateworldsdef_) = new StateWorlds((yyvsp[-1].listworldname_)); }
#line 2608 "Parser.C"
    break;

  case 119: /* StateRelDef: _SYMB_16 StateRelations  */
#line 623 "epddl.y"
                                      { (yyval.statereldef_) = new StateRel((yyvsp[0].staterelations_)); }
#line 2614 "Parser.C"
    break;

  case 120: /* StateRelations: ListWorldRelation  */
#line 625 "epddl.y"
                                   { std::reverse((yyvsp[0].listworldrelation_)->begin(),(yyvsp[0].listworldrelation_)->end()) ;(yyval.staterelations_) = new WorldsStateRel((yyvsp[0].listworldrelation_)); }
#line 2620 "Parser.C"
    break;

  case 121: /* StateRelations: TrivialDef  */
#line 626 "epddl.y"
               { (yyval.staterelations_) = new TrivialStateRel((yyvsp[0].trivialdef_)); }
#line 2626 "Parser.C"
    break;

  case 122: /* WorldRelation: _LPAREN AgentGroup ListWorldNamePair _RPAREN  */
#line 628 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listworldnamepair_)->begin(),(yyvsp[-1].listworldnamepair_)->end()) ;(yyval.worldrelation_) = new WorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listworldnamepair_)); }
#line 2632 "Parser.C"
    break;

  case 123: /* WorldRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 629 "epddl.y"
                                          { (yyval.worldrelation_) = new TrivialWorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2638 "Parser.C"
    break;

  case 124: /* ListWorldRelation: WorldRelation  */
#line 631 "epddl.y"
                                  { (yyval.listworldrelation_) = new ListWorldRelation(); (yyval.listworldrelation_)->push_back((yyvsp[0].worldrelation_)); }
#line 2644 "Parser.C"
    break;

  case 125: /* ListWorldRelation: WorldRelation ListWorldRelation  */
#line 632 "epddl.y"
                                    { (yyvsp[0].listworldrelation_)->push_back((yyvsp[-1].worldrelation_)); (yyval.listworldrelation_) = (yyvsp[0].listworldrelation_); }
#line 2650 "Parser.C"
    break;

  case 126: /* WorldNamePair: _LPAREN WorldName WorldName _RPAREN  */
#line 634 "epddl.y"
                                                    { (yyval.worldnamepair_) = new WorldPair((yyvsp[-2].worldname_), (yyvsp[-1].worldname_)); }
#line 2656 "Parser.C"
    break;

  case 127: /* ListWorldNamePair: WorldNamePair  */
#line 636 "epddl.y"
                                  { (yyval.listworldnamepair_) = new ListWorldNamePair(); (yyval.listworldnamepair_)->push_back((yyvsp[0].worldnamepair_)); }
#line 2662 "Parser.C"
    break;

  case 128: /* ListWorldNamePair: WorldNamePair ListWorldNamePair  */
#line 637 "epddl.y"
                                    { (yyvsp[0].listworldnamepair_)->push_back((yyvsp[-1].worldnamepair_)); (yyval.listworldnamepair_) = (yyvsp[0].listworldnamepair_); }
#line 2668 "Parser.C"
    break;

  case 129: /* StateValDef: _SYMB_34 StateValuation  */
#line 639 "epddl.y"
                                      { (yyval.statevaldef_) = new StateVal((yyvsp[0].statevaluation_)); }
#line 2674 "Parser.C"
    break;

  case 130: /* StateValuation: ListWorldValuation  */
#line 641 "epddl.y"
                                    { std::reverse((yyvsp[0].listworldvaluation_)->begin(),(yyvsp[0].listworldvaluation_)->end()) ;(yyval.statevaluation_) = new WorldsStateVal((yyvsp[0].listworldvaluation_)); }
#line 2680 "Parser.C"
    break;

  case 131: /* StateValuation: TrivialDef  */
#line 642 "epddl.y"
               { (yyval.statevaluation_) = new TrivialStateVal((yyvsp[0].trivialdef_)); }
#line 2686 "Parser.C"
    break;

  case 132: /* WorldValuation: _LPAREN WorldName _LBRACK ListLiteral _RBRACK _RPAREN  */
#line 644 "epddl.y"
                                                                       { (yyval.worldvaluation_) = new WorldVal((yyvsp[-4].worldname_), (yyvsp[-2].listliteral_)); }
#line 2692 "Parser.C"
    break;

  case 133: /* ListWorldValuation: WorldValuation  */
#line 646 "epddl.y"
                                    { (yyval.listworldvaluation_) = new ListWorldValuation(); (yyval.listworldvaluation_)->push_back((yyvsp[0].worldvaluation_)); }
#line 2698 "Parser.C"
    break;

  case 134: /* ListWorldValuation: WorldValuation ListWorldValuation  */
#line 647 "epddl.y"
                                      { (yyvsp[0].listworldvaluation_)->push_back((yyvsp[-1].worldvaluation_)); (yyval.listworldvaluation_) = (yyvsp[0].listworldvaluation_); }
#line 2704 "Parser.C"
    break;

  case 135: /* StateDesignDef: _SYMB_17 _LPAREN ListWorldName _RPAREN  */
#line 649 "epddl.y"
                                                        { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.statedesigndef_) = new StateDesign((yyvsp[-1].listworldname_)); }
#line 2710 "Parser.C"
    break;

  case 136: /* GoalDef: _LPAREN _SYMB_35 Formula _RPAREN  */
#line 651 "epddl.y"
                                           { (yyval.goaldef_) = new EPDDLGoals((yyvsp[-1].formula_)); }
#line 2716 "Parser.C"
    break;

  case 137: /* Formula: _LPAREN _KW_imply Formula Formula _RPAREN  */
#line 653 "epddl.y"
                                                    { (yyval.formula_) = new ImplyFormula((yyvsp[-2].formula_), (yyvsp[-1].formula_)); }
#line 2722 "Parser.C"
    break;

  case 138: /* Formula: _LPAREN _KW_or Formula ListFormula _RPAREN  */
#line 654 "epddl.y"
                                               { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new OrFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2728 "Parser.C"
    break;

  case 139: /* Formula: _LPAREN _KW_and Formula ListFormula _RPAREN  */
#line 655 "epddl.y"
                                                { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new AndFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2734 "Parser.C"
    break;

  case 140: /* Formula: _LPAREN _KW_not Formula _RPAREN  */
#line 656 "epddl.y"
                                    { (yyval.formula_) = new NotFormula((yyvsp[-1].formula_)); }
#line 2740 "Parser.C"
    break;

  case 141: /* Formula: _LPAREN _KW_exists _LPAREN TypedVariableList _RPAREN Formula _RPAREN  */
#line 657 "epddl.y"
                                                                         { (yyval.formula_) = new ExistsFormula((yyvsp[-3].typedvariablelist_), (yyvsp[-1].formula_)); }
#line 2746 "Parser.C"
    break;

  case 142: /* Formula: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN Formula _RPAREN  */
#line 658 "epddl.y"
                                                                         { (yyval.formula_) = new ForAllFormula((yyvsp[-3].typedvariablelist_), (yyvsp[-1].formula_)); }
#line 2752 "Parser.C"
    break;

  case 143: /* Formula: Modality Formula  */
#line 659 "epddl.y"
                     { (yyval.formula_) = new ModalFormula((yyvsp[-1].modality_), (yyvsp[0].formula_)); }
#line 2758 "Parser.C"
    break;

  case 144: /* Formula: _LPAREN Modality Formula _RPAREN  */
#line 660 "epddl.y"
                                     { (yyval.formula_) = new ModalFormulaPar((yyvsp[-2].modality_), (yyvsp[-1].formula_)); }
#line 2764 "Parser.C"
    break;

  case 145: /* Formula: AtomicFormula  */
#line 661 "epddl.y"
                  { (yyval.formula_) = new AtmFormula((yyvsp[0].atomicformula_)); }
#line 2770 "Parser.C"
    break;

  case 146: /* Formula: AtomicEqFormula  */
#line 662 "epddl.y"
                    { (yyval.formula_) = new AtmEqFormula((yyvsp[0].atomiceqformula_)); }
#line 2776 "Parser.C"
    break;

  case 147: /* Formula: _KW_true  */
#line 663 "epddl.y"
             { (yyval.formula_) = new TrueFormula(); }
#line 2782 "Parser.C"
    break;

  case 148: /* Formula: _KW_false  */
#line 664 "epddl.y"
              { (yyval.formula_) = new FalseFormula(); }
#line 2788 "Parser.C"
    break;

  case 149: /* ListFormula: Formula  */
#line 666 "epddl.y"
                      { (yyval.listformula_) = new ListFormula(); (yyval.listformula_)->push_back((yyvsp[0].formula_)); }
#line 2794 "Parser.C"
    break;

  case 150: /* ListFormula: Formula ListFormula  */
#line 667 "epddl.y"
                        { (yyvsp[0].listformula_)->push_back((yyvsp[-1].formula_)); (yyval.listformula_) = (yyvsp[0].listformula_); }
#line 2800 "Parser.C"
    break;

  case 151: /* AtomicFormula: Predicate  */
#line 669 "epddl.y"
                          { (yyval.atomicformula_) = new GroundAtmForm((yyvsp[0].predicate_)); }
#line 2806 "Parser.C"
    break;

  case 152: /* AtomicFormula: _LPAREN Variable _RPAREN  */
#line 670 "epddl.y"
                             { (yyval.atomicformula_) = new VarAtmForm((yyvsp[-1]._variable)); }
#line 2812 "Parser.C"
    break;

  case 153: /* Predicate: _LPAREN PredicateName ListTerm _RPAREN  */
#line 672 "epddl.y"
                                                   { (yyval.predicate_) = new PredicateAtmForm((yyvsp[-2].predicatename_), (yyvsp[-1].listterm_)); }
#line 2818 "Parser.C"
    break;

  case 154: /* AtomicEqFormula: _LPAREN _EQ Term Term _RPAREN  */
#line 674 "epddl.y"
                                                { (yyval.atomiceqformula_) = new EqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 2824 "Parser.C"
    break;

  case 155: /* FormulaOrEmpty: Formula  */
#line 676 "epddl.y"
                         { (yyval.formulaorempty_) = new NonTrivialFormula((yyvsp[0].formula_)); }
#line 2830 "Parser.C"
    break;

  case 156: /* FormulaOrEmpty: TrivialDef  */
#line 677 "epddl.y"
               { (yyval.formulaorempty_) = new TrivialFormula((yyvsp[0].trivialdef_)); }
#line 2836 "Parser.C"
    break;

  case 157: /* Term: GroundTerm  */
#line 679 "epddl.y"
                  { (yyval.term_) = new EPDDLGroundTerm((yyvsp[0].groundterm_)); }
#line 2842 "Parser.C"
    break;

  case 158: /* Term: Variable  */
#line 680 "epddl.y"
             { (yyval.term_) = new EPDDLTermVar((yyvsp[0]._variable)); }
#line 2848 "Parser.C"
    break;

  case 159: /* ListTerm: %empty  */
#line 682 "epddl.y"
                       { (yyval.listterm_) = new ListTerm(); }
#line 2854 "Parser.C"
    break;

  case 160: /* ListTerm: ListTerm Term  */
#line 683 "epddl.y"
                  { (yyvsp[-1].listterm_)->push_back((yyvsp[0].term_)); (yyval.listterm_) = (yyvsp[-1].listterm_); }
#line 2860 "Parser.C"
    break;

  case 161: /* GroundTerm: Name  */
#line 685 "epddl.y"
                  { (yyval.groundterm_) = new EPDDLGroundTermName((yyvsp[0]._name)); }
#line 2866 "Parser.C"
    break;

  case 162: /* GroundTerm: AgentName  */
#line 686 "epddl.y"
              { (yyval.groundterm_) = new EPDDLGroundTermAgName((yyvsp[0]._agentname)); }
#line 2872 "Parser.C"
    break;

  case 163: /* ListGroundTerm: %empty  */
#line 688 "epddl.y"
                             { (yyval.listgroundterm_) = new ListGroundTerm(); }
#line 2878 "Parser.C"
    break;

  case 164: /* ListGroundTerm: ListGroundTerm GroundTerm  */
#line 689 "epddl.y"
                              { (yyvsp[-1].listgroundterm_)->push_back((yyvsp[0].groundterm_)); (yyval.listgroundterm_) = (yyvsp[-1].listgroundterm_); }
#line 2884 "Parser.C"
    break;

  case 165: /* Modality: SingleModality  */
#line 691 "epddl.y"
                          { (yyval.modality_) = new EPDDLLabeledMod((yyvsp[0].singlemodality_)); }
#line 2890 "Parser.C"
    break;

  case 166: /* Modality: GroupModality  */
#line 692 "epddl.y"
                  { (yyval.modality_) = new EPDDLLabeledGroupMod((yyvsp[0].groupmodality_)); }
#line 2896 "Parser.C"
    break;

  case 167: /* SingleModality: _LBRACK ModalityLabel ModalityAgent _RBRACK  */
#line 694 "epddl.y"
                                                             { (yyval.singlemodality_) = new LabBoxMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2902 "Parser.C"
    break;

  case 168: /* SingleModality: _LT ModalityLabel ModalityAgent _GT  */
#line 695 "epddl.y"
                                        { (yyval.singlemodality_) = new LabDiamondMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2908 "Parser.C"
    break;

  case 169: /* GroupModality: _LBRACK ModalityLabel ModalityAgentGroup _RBRACK  */
#line 697 "epddl.y"
                                                                 { (yyval.groupmodality_) = new LabBoxGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2914 "Parser.C"
    break;

  case 170: /* GroupModality: _LT ModalityLabel ModalityAgentGroup _GT  */
#line 698 "epddl.y"
                                             { (yyval.groupmodality_) = new LabDiamondGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2920 "Parser.C"
    break;

  case 171: /* ModalityLabel: ModalityName  */
#line 700 "epddl.y"
                             { (yyval.modalitylabel_) = new ModLabel((yyvsp[0]._modalityname)); }
#line 2926 "Parser.C"
    break;

  case 172: /* ModalityLabel: %empty  */
#line 701 "epddl.y"
                { (yyval.modalitylabel_) = new EmptyModLabel(); }
#line 2932 "Parser.C"
    break;

  case 173: /* KnowsWhether: _LBRACK ModalityName AgentName _RBRACK  */
#line 703 "epddl.y"
                                                      { (yyval.knowswhether_) = new KnowsWhetherMod((yyvsp[-2]._modalityname), (yyvsp[-1]._agentname)); }
#line 2938 "Parser.C"
    break;

  case 174: /* Literal: Predicate  */
#line 705 "epddl.y"
                    { (yyval.literal_) = new PosLiteral((yyvsp[0].predicate_)); }
#line 2944 "Parser.C"
    break;

  case 175: /* Literal: _LPAREN _KW_not Predicate _RPAREN  */
#line 706 "epddl.y"
                                      { (yyval.literal_) = new NegLiteral((yyvsp[-1].predicate_)); }
#line 2950 "Parser.C"
    break;

  case 176: /* ListLiteral: %empty  */
#line 708 "epddl.y"
                          { (yyval.listliteral_) = new ListLiteral(); }
#line 2956 "Parser.C"
    break;

  case 177: /* ListLiteral: ListLiteral Literal  */
#line 709 "epddl.y"
                        { (yyvsp[-1].listliteral_)->push_back((yyvsp[0].literal_)); (yyval.listliteral_) = (yyvsp[-1].listliteral_); }
#line 2962 "Parser.C"
    break;

  case 178: /* ConditionFormula: _LPAREN _KW_and Condition ListCondition _RPAREN  */
#line 711 "epddl.y"
                                                                   { std::reverse((yyvsp[-1].listcondition_)->begin(),(yyvsp[-1].listcondition_)->end()) ;(yyval.conditionformula_) = new AndCondFomula((yyvsp[-2].condition_), (yyvsp[-1].listcondition_)); }
#line 2968 "Parser.C"
    break;

  case 179: /* ConditionFormula: Condition  */
#line 712 "epddl.y"
              { (yyval.conditionformula_) = new CondFomula((yyvsp[0].condition_)); }
#line 2974 "Parser.C"
    break;

  case 180: /* Condition: AtomicCondition  */
#line 714 "epddl.y"
                            { (yyval.condition_) = new AtmCond((yyvsp[0].atomiccondition_)); }
#line 2980 "Parser.C"
    break;

  case 181: /* Condition: _LPAREN _KW_not AtomicCondition _RPAREN  */
#line 715 "epddl.y"
                                            { (yyval.condition_) = new NotAtmCond((yyvsp[-1].atomiccondition_)); }
#line 2986 "Parser.C"
    break;

  case 182: /* ListCondition: Condition  */
#line 717 "epddl.y"
                          { (yyval.listcondition_) = new ListCondition(); (yyval.listcondition_)->push_back((yyvsp[0].condition_)); }
#line 2992 "Parser.C"
    break;

  case 183: /* ListCondition: Condition ListCondition  */
#line 718 "epddl.y"
                            { (yyvsp[0].listcondition_)->push_back((yyvsp[-1].condition_)); (yyval.listcondition_) = (yyvsp[0].listcondition_); }
#line 2998 "Parser.C"
    break;

  case 184: /* AtomicCondition: _LPAREN PredicateName ListTerm _RPAREN  */
#line 720 "epddl.y"
                                                         { (yyval.atomiccondition_) = new AtmCondPredicate((yyvsp[-2].predicatename_), (yyvsp[-1].listterm_)); }
#line 3004 "Parser.C"
    break;

  case 185: /* AtomicCondition: _LPAREN _EQ Term Term _RPAREN  */
#line 721 "epddl.y"
                                  { (yyval.atomiccondition_) = new AtmCondEqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 3010 "Parser.C"
    break;

  case 186: /* PredicateFormula: _LPAREN _KW_imply PredicateFormula PredicateFormula _RPAREN  */
#line 723 "epddl.y"
                                                                               { (yyval.predicateformula_) = new ImplyPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].predicateformula_)); }
#line 3016 "Parser.C"
    break;

  case 187: /* PredicateFormula: _LPAREN _KW_or PredicateFormula ListPredicateFormula _RPAREN  */
#line 724 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new OrPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3022 "Parser.C"
    break;

  case 188: /* PredicateFormula: _LPAREN _KW_and PredicateFormula ListPredicateFormula _RPAREN  */
#line 725 "epddl.y"
                                                                  { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new AndPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3028 "Parser.C"
    break;

  case 189: /* PredicateFormula: _LPAREN _KW_not PredicateFormula _RPAREN  */
#line 726 "epddl.y"
                                             { (yyval.predicateformula_) = new NotPredFormula((yyvsp[-1].predicateformula_)); }
#line 3034 "Parser.C"
    break;

  case 190: /* PredicateFormula: _LPAREN PredicateName ListGroundTerm _RPAREN  */
#line 727 "epddl.y"
                                                 { (yyval.predicateformula_) = new AtmPredFormula((yyvsp[-2].predicatename_), (yyvsp[-1].listgroundterm_)); }
#line 3040 "Parser.C"
    break;

  case 191: /* ListPredicateFormula: PredicateFormula  */
#line 729 "epddl.y"
                                        { (yyval.listpredicateformula_) = new ListPredicateFormula(); (yyval.listpredicateformula_)->push_back((yyvsp[0].predicateformula_)); }
#line 3046 "Parser.C"
    break;

  case 192: /* ListPredicateFormula: PredicateFormula ListPredicateFormula  */
#line 730 "epddl.y"
                                          { (yyvsp[0].listpredicateformula_)->push_back((yyvsp[-1].predicateformula_)); (yyval.listpredicateformula_) = (yyvsp[0].listpredicateformula_); }
#line 3052 "Parser.C"
    break;

  case 193: /* GenericName: Name  */
#line 732 "epddl.y"
                   { (yyval.genericname_) = new EPDDLGenericNameObj((yyvsp[0]._name)); }
#line 3058 "Parser.C"
    break;

  case 194: /* GenericName: AgentName  */
#line 733 "epddl.y"
              { (yyval.genericname_) = new EPDDLGenericNameAg((yyvsp[0]._agentname)); }
#line 3064 "Parser.C"
    break;

  case 195: /* ListGenericName: %empty  */
#line 735 "epddl.y"
                              { (yyval.listgenericname_) = new ListGenericName(); }
#line 3070 "Parser.C"
    break;

  case 196: /* ListGenericName: ListGenericName GenericName  */
#line 736 "epddl.y"
                                { (yyvsp[-1].listgenericname_)->push_back((yyvsp[0].genericname_)); (yyval.listgenericname_) = (yyvsp[-1].listgenericname_); }
#line 3076 "Parser.C"
    break;

  case 197: /* TypedIdentList: ListName  */
#line 738 "epddl.y"
                          { std::reverse((yyvsp[0].listname_)->begin(),(yyvsp[0].listname_)->end()) ;(yyval.typedidentlist_) = new IdList((yyvsp[0].listname_)); }
#line 3082 "Parser.C"
    break;

  case 198: /* TypedIdentList: Name ListName _MINUS Type TypedIdentList  */
#line 739 "epddl.y"
                                             { std::reverse((yyvsp[-3].listname_)->begin(),(yyvsp[-3].listname_)->end()) ;(yyval.typedidentlist_) = new TypedIdList((yyvsp[-4]._name), (yyvsp[-3].listname_), (yyvsp[-1].type_), (yyvsp[0].typedidentlist_)); }
#line 3088 "Parser.C"
    break;

  case 199: /* TypedAgentList: ListAgentName  */
#line 741 "epddl.y"
                               { std::reverse((yyvsp[0].listagentname_)->begin(),(yyvsp[0].listagentname_)->end()) ;(yyval.typedagentlist_) = new AgList((yyvsp[0].listagentname_)); }
#line 3094 "Parser.C"
    break;

  case 200: /* TypedAgentList: AgentName ListAgentName _MINUS Type TypedAgentList  */
#line 742 "epddl.y"
                                                       { std::reverse((yyvsp[-3].listagentname_)->begin(),(yyvsp[-3].listagentname_)->end()) ;(yyval.typedagentlist_) = new TypedAgList((yyvsp[-4]._agentname), (yyvsp[-3].listagentname_), (yyvsp[-1].type_), (yyvsp[0].typedagentlist_)); }
#line 3100 "Parser.C"
    break;

  case 201: /* TypedVariableList: ListVariable  */
#line 744 "epddl.y"
                                 { std::reverse((yyvsp[0].listvariable_)->begin(),(yyvsp[0].listvariable_)->end()) ;(yyval.typedvariablelist_) = new VarList((yyvsp[0].listvariable_)); }
#line 3106 "Parser.C"
    break;

  case 202: /* TypedVariableList: Variable ListVariable _MINUS Type TypedVariableList  */
#line 745 "epddl.y"
                                                        { std::reverse((yyvsp[-3].listvariable_)->begin(),(yyvsp[-3].listvariable_)->end()) ;(yyval.typedvariablelist_) = new TypedVarList((yyvsp[-4]._variable), (yyvsp[-3].listvariable_), (yyvsp[-1].type_), (yyvsp[0].typedvariablelist_)); }
#line 3112 "Parser.C"
    break;

  case 203: /* PredicateName: Name  */
#line 747 "epddl.y"
                     { (yyval.predicatename_) = new EPDDLPredicate((yyvsp[0]._name)); }
#line 3118 "Parser.C"
    break;

  case 204: /* ModalityAgent: AgentName  */
#line 749 "epddl.y"
                          { (yyval.modalityagent_) = new EPDDLModAgent((yyvsp[0]._agentname)); }
#line 3124 "Parser.C"
    break;

  case 205: /* ModalityAgent: Variable  */
#line 750 "epddl.y"
             { (yyval.modalityagent_) = new EPDDLModVarAgent((yyvsp[0]._variable)); }
#line 3130 "Parser.C"
    break;

  case 206: /* ModalityAgent: AllAgents  */
#line 751 "epddl.y"
              { (yyval.modalityagent_) = new EPDDLModAllAgents((yyvsp[0].allagents_)); }
#line 3136 "Parser.C"
    break;

  case 207: /* ListModalityAgent: ModalityAgent  */
#line 753 "epddl.y"
                                  { (yyval.listmodalityagent_) = new ListModalityAgent(); (yyval.listmodalityagent_)->push_back((yyvsp[0].modalityagent_)); }
#line 3142 "Parser.C"
    break;

  case 208: /* ListModalityAgent: ModalityAgent ListModalityAgent  */
#line 754 "epddl.y"
                                    { (yyvsp[0].listmodalityagent_)->push_back((yyvsp[-1].modalityagent_)); (yyval.listmodalityagent_) = (yyvsp[0].listmodalityagent_); }
#line 3148 "Parser.C"
    break;

  case 209: /* ModalityAgentGroup: ModalityAgent ListModalityAgent  */
#line 756 "epddl.y"
                                                     { std::reverse((yyvsp[0].listmodalityagent_)->begin(),(yyvsp[0].listmodalityagent_)->end()) ;(yyval.modalityagentgroup_) = new EPDDLModAgList((yyvsp[-1].modalityagent_), (yyvsp[0].listmodalityagent_)); }
#line 3154 "Parser.C"
    break;

  case 210: /* AgentGroupName: AgentName  */
#line 758 "epddl.y"
                           { (yyval.agentgroupname_) = new EPDDLSingleAgentGroup((yyvsp[0]._agentname)); }
#line 3160 "Parser.C"
    break;

  case 211: /* AgentGroupName: AllAgents  */
#line 759 "epddl.y"
              { (yyval.agentgroupname_) = new EPDDLAllAgentsGroup((yyvsp[0].allagents_)); }
#line 3166 "Parser.C"
    break;

  case 212: /* ObservingAgentGroup: AgentName  */
#line 761 "epddl.y"
                                { (yyval.observingagentgroup_) = new EPDDLObsAgentGroup((yyvsp[0]._agentname)); }
#line 3172 "Parser.C"
    break;

  case 213: /* ListObservingAgentGroup: ObservingAgentGroup  */
#line 763 "epddl.y"
                                              { (yyval.listobservingagentgroup_) = new ListObservingAgentGroup(); (yyval.listobservingagentgroup_)->push_back((yyvsp[0].observingagentgroup_)); }
#line 3178 "Parser.C"
    break;

  case 214: /* ListObservingAgentGroup: ObservingAgentGroup ListObservingAgentGroup  */
#line 764 "epddl.y"
                                                { (yyvsp[0].listobservingagentgroup_)->push_back((yyvsp[-1].observingagentgroup_)); (yyval.listobservingagentgroup_) = (yyvsp[0].listobservingagentgroup_); }
#line 3184 "Parser.C"
    break;

  case 215: /* ObservingAgent: AgentName  */
#line 766 "epddl.y"
                           { (yyval.observingagent_) = new EPDDLObsAgent((yyvsp[0]._agentname)); }
#line 3190 "Parser.C"
    break;

  case 216: /* ObservingAgent: AllAgents  */
#line 767 "epddl.y"
              { (yyval.observingagent_) = new EPDDLObsAllAgents((yyvsp[0].allagents_)); }
#line 3196 "Parser.C"
    break;

  case 217: /* ObservingAgent: Variable  */
#line 768 "epddl.y"
             { (yyval.observingagent_) = new EPDDLObsVarAgent((yyvsp[0]._variable)); }
#line 3202 "Parser.C"
    break;

  case 218: /* AgentGroup: AgentGroupName  */
#line 770 "epddl.y"
                            { (yyval.agentgroup_) = new EPDDLAgentGroup((yyvsp[0].agentgroupname_)); }
#line 3208 "Parser.C"
    break;

  case 219: /* AgentGroup: _LBRACE AgentName ListAgentName _RBRACE  */
#line 771 "epddl.y"
                                            { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentgroup_) = new EPDDLAgentNameGroup((yyvsp[-2]._agentname), (yyvsp[-1].listagentname_)); }
#line 3214 "Parser.C"
    break;

  case 220: /* AllAgents: _KW_All  */
#line 773 "epddl.y"
                    { (yyval.allagents_) = new EPDDLAllAgents(); }
#line 3220 "Parser.C"
    break;

  case 221: /* Parameter: _LPAREN Variable _DCOLON Expression _RPAREN  */
#line 775 "epddl.y"
                                                        { (yyval.parameter_) = new EPDDLParam((yyvsp[-3]._variable), (yyvsp[-1].expression_)); }
#line 3226 "Parser.C"
    break;

  case 222: /* ListParameter: %empty  */
#line 777 "epddl.y"
                            { (yyval.listparameter_) = new ListParameter(); }
#line 3232 "Parser.C"
    break;

  case 223: /* ListParameter: ListParameter Parameter  */
#line 778 "epddl.y"
                            { (yyvsp[-1].listparameter_)->push_back((yyvsp[0].parameter_)); (yyval.listparameter_) = (yyvsp[-1].listparameter_); }
#line 3238 "Parser.C"
    break;

  case 224: /* Expression: Term  */
#line 780 "epddl.y"
                  { (yyval.expression_) = new EPDDLTermExpr((yyvsp[0].term_)); }
#line 3244 "Parser.C"
    break;

  case 225: /* Expression: Formula  */
#line 781 "epddl.y"
            { (yyval.expression_) = new EPDDLFormulaExpr((yyvsp[0].formula_)); }
#line 3250 "Parser.C"
    break;

  case 226: /* Expression: PostconditionBlock  */
#line 782 "epddl.y"
                       { (yyval.expression_) = new EPDDLPostExpr((yyvsp[0].postconditionblock_)); }
#line 3256 "Parser.C"
    break;

  case 227: /* Type: Name  */
#line 784 "epddl.y"
            { (yyval.type_) = new EPDDLTypeName((yyvsp[0]._name)); }
#line 3262 "Parser.C"
    break;

  case 228: /* Type: ReservedType  */
#line 785 "epddl.y"
                 { (yyval.type_) = new EPDDLResType((yyvsp[0].reservedtype_)); }
#line 3268 "Parser.C"
    break;

  case 229: /* ReservedType: _KW_agent  */
#line 787 "epddl.y"
                         { (yyval.reservedtype_) = new ResAgentType(); }
#line 3274 "Parser.C"
    break;

  case 230: /* ReservedType: _KW_predicate  */
#line 788 "epddl.y"
                  { (yyval.reservedtype_) = new PredicateType(); }
#line 3280 "Parser.C"
    break;

  case 231: /* ReservedType: _KW_literal  */
#line 789 "epddl.y"
                { (yyval.reservedtype_) = new LiteralType(); }
#line 3286 "Parser.C"
    break;

  case 232: /* ReservedType: _SYMB_40  */
#line 790 "epddl.y"
             { (yyval.reservedtype_) = new PredFormulaType(); }
#line 3292 "Parser.C"
    break;

  case 233: /* ReservedType: _KW_formula  */
#line 791 "epddl.y"
                { (yyval.reservedtype_) = new FormulaType(); }
#line 3298 "Parser.C"
    break;

  case 234: /* ReservedType: _KW_postcondition  */
#line 792 "epddl.y"
                      { (yyval.reservedtype_) = new PostconditionType(); }
#line 3304 "Parser.C"
    break;

  case 235: /* DomainName: Name  */
#line 794 "epddl.y"
                  { (yyval.domainname_) = new EPDDLDomainName((yyvsp[0]._name)); }
#line 3310 "Parser.C"
    break;

  case 236: /* LibraryName: Name  */
#line 796 "epddl.y"
                   { (yyval.libraryname_) = new EPDDLLibraryName((yyvsp[0]._name)); }
#line 3316 "Parser.C"
    break;

  case 237: /* ListLibraryName: LibraryName  */
#line 798 "epddl.y"
                              { (yyval.listlibraryname_) = new ListLibraryName(); (yyval.listlibraryname_)->push_back((yyvsp[0].libraryname_)); }
#line 3322 "Parser.C"
    break;

  case 238: /* ListLibraryName: LibraryName ListLibraryName  */
#line 799 "epddl.y"
                                { (yyvsp[0].listlibraryname_)->push_back((yyvsp[-1].libraryname_)); (yyval.listlibraryname_) = (yyvsp[0].listlibraryname_); }
#line 3328 "Parser.C"
    break;

  case 239: /* ProblemName: Name  */
#line 801 "epddl.y"
                   { (yyval.problemname_) = new EPDDLProblemName((yyvsp[0]._name)); }
#line 3334 "Parser.C"
    break;

  case 240: /* ActionName: Name  */
#line 803 "epddl.y"
                  { (yyval.actionname_) = new EPDDLActionName((yyvsp[0]._name)); }
#line 3340 "Parser.C"
    break;

  case 241: /* ActionTypeName: Name  */
#line 805 "epddl.y"
                      { (yyval.actiontypename_) = new EPDDLActTypeName((yyvsp[0]._name)); }
#line 3346 "Parser.C"
    break;

  case 242: /* EventName: Name  */
#line 807 "epddl.y"
                 { (yyval.eventname_) = new EPDDLEventName((yyvsp[0]._name)); }
#line 3352 "Parser.C"
    break;

  case 243: /* ListEventName: EventName  */
#line 809 "epddl.y"
                          { (yyval.listeventname_) = new ListEventName(); (yyval.listeventname_)->push_back((yyvsp[0].eventname_)); }
#line 3358 "Parser.C"
    break;

  case 244: /* ListEventName: EventName ListEventName  */
#line 810 "epddl.y"
                            { (yyvsp[0].listeventname_)->push_back((yyvsp[-1].eventname_)); (yyval.listeventname_) = (yyvsp[0].listeventname_); }
#line 3364 "Parser.C"
    break;

  case 245: /* StateName: Name  */
#line 812 "epddl.y"
                 { (yyval.statename_) = new EPDDLStateName((yyvsp[0]._name)); }
#line 3370 "Parser.C"
    break;

  case 246: /* WorldName: Name  */
#line 814 "epddl.y"
                 { (yyval.worldname_) = new EPDDLWorldName((yyvsp[0]._name)); }
#line 3376 "Parser.C"
    break;

  case 247: /* ListWorldName: WorldName  */
#line 816 "epddl.y"
                          { (yyval.listworldname_) = new ListWorldName(); (yyval.listworldname_)->push_back((yyvsp[0].worldname_)); }
#line 3382 "Parser.C"
    break;

  case 248: /* ListWorldName: WorldName ListWorldName  */
#line 817 "epddl.y"
                            { (yyvsp[0].listworldname_)->push_back((yyvsp[-1].worldname_)); (yyval.listworldname_) = (yyvsp[0].listworldname_); }
#line 3388 "Parser.C"
    break;

  case 249: /* RequirementKey: _SYMB_41  */
#line 819 "epddl.y"
                          { (yyval.requirementkey_) = new EPDDLReqDel(); }
#line 3394 "Parser.C"
    break;

  case 250: /* RequirementKey: _SYMB_42  */
#line 820 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqTyping(); }
#line 3400 "Parser.C"
    break;

  case 251: /* RequirementKey: _SYMB_43  */
#line 821 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqEquality(); }
#line 3406 "Parser.C"
    break;

  case 252: /* RequirementKey: _SYMB_44  */
#line 822 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqExiForm(); }
#line 3412 "Parser.C"
    break;

  case 253: /* RequirementKey: _SYMB_45  */
#line 823 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqUniForm(); }
#line 3418 "Parser.C"
    break;

  case 254: /* RequirementKey: _SYMB_46  */
#line 824 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqUniPost(); }
#line 3424 "Parser.C"
    break;

  case 255: /* RequirementKey: _SYMB_47  */
#line 825 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqModPre(); }
#line 3430 "Parser.C"
    break;

  case 256: /* RequirementKey: _SYMB_48  */
#line 826 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqModPost(); }
#line 3436 "Parser.C"
    break;

  case 257: /* RequirementKey: _SYMB_6  */
#line 827 "epddl.y"
            { (yyval.requirementkey_) = new EPDDLReqModalities(); }
#line 3442 "Parser.C"
    break;

  case 258: /* RequirementKey: _SYMB_49  */
#line 828 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqOnticChange(); }
#line 3448 "Parser.C"
    break;

  case 259: /* RequirementKey: _SYMB_50  */
#line 829 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqCK(); }
#line 3454 "Parser.C"
    break;

  case 260: /* RequirementKey: _SYMB_51  */
#line 830 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqDynCK(); }
#line 3460 "Parser.C"
    break;

  case 261: /* RequirementKey: _SYMB_52  */
#line 831 "epddl.y"
             { (yyval.requirementkey_) = new EPDDLReqFTheory(); }
#line 3466 "Parser.C"
    break;

  case 262: /* RequirementKey: _LPAREN _SYMB_53 _INTEGER_ _RPAREN  */
#line 832 "epddl.y"
                                       { (yyval.requirementkey_) = new EPDDLReqMaxPreDepth((yyvsp[-1]._int)); }
#line 3472 "Parser.C"
    break;

  case 263: /* RequirementKey: _LPAREN _SYMB_54 _INTEGER_ _RPAREN  */
#line 833 "epddl.y"
                                       { (yyval.requirementkey_) = new EPDDLReqMaxPostDepth((yyvsp[-1]._int)); }
#line 3478 "Parser.C"
    break;

  case 264: /* RequirementKey: _LPAREN _SYMB_55 _INTEGER_ _RPAREN  */
#line 834 "epddl.y"
                                       { (yyval.requirementkey_) = new EPDDLReqMaxDepth((yyvsp[-1]._int)); }
#line 3484 "Parser.C"
    break;

  case 265: /* ListRequirementKey: RequirementKey  */
#line 836 "epddl.y"
                                    { (yyval.listrequirementkey_) = new ListRequirementKey(); (yyval.listrequirementkey_)->push_back((yyvsp[0].requirementkey_)); }
#line 3490 "Parser.C"
    break;

  case 266: /* ListRequirementKey: RequirementKey ListRequirementKey  */
#line 837 "epddl.y"
                                      { (yyvsp[0].listrequirementkey_)->push_back((yyvsp[-1].requirementkey_)); (yyval.listrequirementkey_) = (yyvsp[0].listrequirementkey_); }
#line 3496 "Parser.C"
    break;

  case 267: /* TrivialDef: _LPAREN _RPAREN  */
#line 839 "epddl.y"
                             { (yyval.trivialdef_) = new EPDDLTrivialDef(); }
#line 3502 "Parser.C"
    break;

  case 268: /* ListName: %empty  */
#line 841 "epddl.y"
                       { (yyval.listname_) = new ListName(); }
#line 3508 "Parser.C"
    break;

  case 269: /* ListName: Name ListName  */
#line 842 "epddl.y"
                  { (yyvsp[0].listname_)->push_back((yyvsp[-1]._name)); (yyval.listname_) = (yyvsp[0].listname_); }
#line 3514 "Parser.C"
    break;

  case 270: /* ListAgentName: %empty  */
#line 844 "epddl.y"
                            { (yyval.listagentname_) = new ListAgentName(); }
#line 3520 "Parser.C"
    break;

  case 271: /* ListAgentName: AgentName ListAgentName  */
#line 845 "epddl.y"
                            { (yyvsp[0].listagentname_)->push_back((yyvsp[-1]._agentname)); (yyval.listagentname_) = (yyvsp[0].listagentname_); }
#line 3526 "Parser.C"
    break;

  case 272: /* ListModalityName: %empty  */
#line 847 "epddl.y"
                               { (yyval.listmodalityname_) = new ListModalityName(); }
#line 3532 "Parser.C"
    break;

  case 273: /* ListModalityName: ModalityName ListModalityName  */
#line 848 "epddl.y"
                                  { (yyvsp[0].listmodalityname_)->push_back((yyvsp[-1]._modalityname)); (yyval.listmodalityname_) = (yyvsp[0].listmodalityname_); }
#line 3538 "Parser.C"
    break;

  case 274: /* ListVariable: %empty  */
#line 850 "epddl.y"
                           { (yyval.listvariable_) = new ListVariable(); }
#line 3544 "Parser.C"
    break;

  case 275: /* ListVariable: Variable ListVariable  */
#line 851 "epddl.y"
                          { (yyvsp[0].listvariable_)->push_back((yyvsp[-1]._variable)); (yyval.listvariable_) = (yyvsp[0].listvariable_); }
#line 3550 "Parser.C"
    break;

  case 276: /* Name: T_Name  */
#line 853 "epddl.y"
              { (yyval._name) = new Name((yyvsp[0]._string), (yyloc).first_line); }
#line 3556 "Parser.C"
    break;

  case 277: /* AgentName: T_AgentName  */
#line 855 "epddl.y"
                        { (yyval._agentname) = new AgentName((yyvsp[0]._string), (yyloc).first_line); }
#line 3562 "Parser.C"
    break;

  case 278: /* ModalityName: T_ModalityName  */
#line 857 "epddl.y"
                              { (yyval._modalityname) = new ModalityName((yyvsp[0]._string), (yyloc).first_line); }
#line 3568 "Parser.C"
    break;

  case 279: /* Variable: T_Variable  */
#line 859 "epddl.y"
                      { (yyval._variable) = new Variable((yyvsp[0]._string), (yyloc).first_line); }
#line 3574 "Parser.C"
    break;


#line 3578 "Parser.C"

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

#line 862 "epddl.y"



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



