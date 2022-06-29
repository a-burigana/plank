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
  YYSYMBOL__SYMB_7 = 7,                    /* _SYMB_7  */
  YYSYMBOL__SYMB_9 = 8,                    /* _SYMB_9  */
  YYSYMBOL__SYMB_2 = 9,                    /* _SYMB_2  */
  YYSYMBOL__SYMB_20 = 10,                  /* _SYMB_20  */
  YYSYMBOL__SYMB_19 = 11,                  /* _SYMB_19  */
  YYSYMBOL__SYMB_51 = 12,                  /* _SYMB_51  */
  YYSYMBOL__SYMB_40 = 13,                  /* _SYMB_40  */
  YYSYMBOL__SYMB_15 = 14,                  /* _SYMB_15  */
  YYSYMBOL__SYMB_45 = 15,                  /* _SYMB_45  */
  YYSYMBOL__SYMB_18 = 16,                  /* _SYMB_18  */
  YYSYMBOL__SYMB_52 = 17,                  /* _SYMB_52  */
  YYSYMBOL__SYMB_42 = 18,                  /* _SYMB_42  */
  YYSYMBOL__SYMB_16 = 19,                  /* _SYMB_16  */
  YYSYMBOL__SYMB_13 = 20,                  /* _SYMB_13  */
  YYSYMBOL__SYMB_46 = 21,                  /* _SYMB_46  */
  YYSYMBOL__SYMB_12 = 22,                  /* _SYMB_12  */
  YYSYMBOL__SYMB_29 = 23,                  /* _SYMB_29  */
  YYSYMBOL__SYMB_24 = 24,                  /* _SYMB_24  */
  YYSYMBOL__SYMB_53 = 25,                  /* _SYMB_53  */
  YYSYMBOL__SYMB_56 = 26,                  /* _SYMB_56  */
  YYSYMBOL__SYMB_57 = 27,                  /* _SYMB_57  */
  YYSYMBOL__SYMB_54 = 28,                  /* _SYMB_54  */
  YYSYMBOL__SYMB_55 = 29,                  /* _SYMB_55  */
  YYSYMBOL__SYMB_60 = 30,                  /* _SYMB_60  */
  YYSYMBOL__SYMB_59 = 31,                  /* _SYMB_59  */
  YYSYMBOL__SYMB_58 = 32,                  /* _SYMB_58  */
  YYSYMBOL__SYMB_49 = 33,                  /* _SYMB_49  */
  YYSYMBOL__SYMB_48 = 34,                  /* _SYMB_48  */
  YYSYMBOL__SYMB_26 = 35,                  /* _SYMB_26  */
  YYSYMBOL__SYMB_25 = 36,                  /* _SYMB_25  */
  YYSYMBOL__SYMB_44 = 37,                  /* _SYMB_44  */
  YYSYMBOL__SYMB_23 = 38,                  /* _SYMB_23  */
  YYSYMBOL__SYMB_11 = 39,                  /* _SYMB_11  */
  YYSYMBOL__SYMB_6 = 40,                   /* _SYMB_6  */
  YYSYMBOL__SYMB_50 = 41,                  /* _SYMB_50  */
  YYSYMBOL__SYMB_43 = 42,                  /* _SYMB_43  */
  YYSYMBOL__SYMB_8 = 43,                   /* _SYMB_8  */
  YYSYMBOL__SYMB_17 = 44,                  /* _SYMB_17  */
  YYSYMBOL__SYMB_10 = 45,                  /* _SYMB_10  */
  YYSYMBOL__SYMB_5 = 46,                   /* _SYMB_5  */
  YYSYMBOL__SYMB_14 = 47,                  /* _SYMB_14  */
  YYSYMBOL__SYMB_3 = 48,                   /* _SYMB_3  */
  YYSYMBOL__SYMB_4 = 49,                   /* _SYMB_4  */
  YYSYMBOL__SYMB_41 = 50,                  /* _SYMB_41  */
  YYSYMBOL__SYMB_47 = 51,                  /* _SYMB_47  */
  YYSYMBOL__SYMB_28 = 52,                  /* _SYMB_28  */
  YYSYMBOL__SYMB_27 = 53,                  /* _SYMB_27  */
  YYSYMBOL__LT = 54,                       /* _LT  */
  YYSYMBOL__EQ = 55,                       /* _EQ  */
  YYSYMBOL__GT = 56,                       /* _GT  */
  YYSYMBOL__SYMB_37 = 57,                  /* _SYMB_37  */
  YYSYMBOL__KW_All = 58,                   /* _KW_All  */
  YYSYMBOL__LBRACK = 59,                   /* _LBRACK  */
  YYSYMBOL__RBRACK = 60,                   /* _RBRACK  */
  YYSYMBOL__KW_agent = 61,                 /* _KW_agent  */
  YYSYMBOL__KW_and = 62,                   /* _KW_and  */
  YYSYMBOL__KW_announcement = 63,          /* _KW_announcement  */
  YYSYMBOL__KW_as = 64,                    /* _KW_as  */
  YYSYMBOL__KW_define = 65,                /* _KW_define  */
  YYSYMBOL__KW_domain = 66,                /* _KW_domain  */
  YYSYMBOL__SYMB_34 = 67,                  /* _SYMB_34  */
  YYSYMBOL__KW_false = 68,                 /* _KW_false  */
  YYSYMBOL__KW_formula = 69,               /* _KW_formula  */
  YYSYMBOL__SYMB_39 = 70,                  /* _SYMB_39  */
  YYSYMBOL__KW_if = 71,                    /* _KW_if  */
  YYSYMBOL__KW_imply = 72,                 /* _KW_imply  */
  YYSYMBOL__SYMB_33 = 73,                  /* _SYMB_33  */
  YYSYMBOL__KW_library = 74,               /* _KW_library  */
  YYSYMBOL__KW_literal = 75,               /* _KW_literal  */
  YYSYMBOL__KW_not = 76,                   /* _KW_not  */
  YYSYMBOL__KW_ontic = 77,                 /* _KW_ontic  */
  YYSYMBOL__KW_or = 78,                    /* _KW_or  */
  YYSYMBOL__KW_otherwise = 79,             /* _KW_otherwise  */
  YYSYMBOL__KW_predicate = 80,             /* _KW_predicate  */
  YYSYMBOL__SYMB_38 = 81,                  /* _SYMB_38  */
  YYSYMBOL__KW_problem = 82,               /* _KW_problem  */
  YYSYMBOL__SYMB_35 = 83,                  /* _SYMB_35  */
  YYSYMBOL__KW_sensing = 84,               /* _KW_sensing  */
  YYSYMBOL__KW_true = 85,                  /* _KW_true  */
  YYSYMBOL_T_AgentName = 86,               /* T_AgentName  */
  YYSYMBOL_T_ModalityName = 87,            /* T_ModalityName  */
  YYSYMBOL_T_Name = 88,                    /* T_Name  */
  YYSYMBOL_T_Variable = 89,                /* T_Variable  */
  YYSYMBOL__INTEGER_ = 90,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 91,                  /* $accept  */
  YYSYMBOL_MainDef = 92,                   /* MainDef  */
  YYSYMBOL_DomainDef = 93,                 /* DomainDef  */
  YYSYMBOL_DomainItemDef = 94,             /* DomainItemDef  */
  YYSYMBOL_ListDomainItemDef = 95,         /* ListDomainItemDef  */
  YYSYMBOL_DomainLibrariesNameDef = 96,    /* DomainLibrariesNameDef  */
  YYSYMBOL_RequireDef = 97,                /* RequireDef  */
  YYSYMBOL_TypesDef = 98,                  /* TypesDef  */
  YYSYMBOL_PredicateListDef = 99,          /* PredicateListDef  */
  YYSYMBOL_PredicateDef = 100,             /* PredicateDef  */
  YYSYMBOL_ListPredicateDef = 101,         /* ListPredicateDef  */
  YYSYMBOL_ObservabilityGroupsDef = 102,   /* ObservabilityGroupsDef  */
  YYSYMBOL_ActionDef = 103,                /* ActionDef  */
  YYSYMBOL_ActionParameterDef = 104,       /* ActionParameterDef  */
  YYSYMBOL_ActionTypeSignatureDef = 105,   /* ActionTypeSignatureDef  */
  YYSYMBOL_ActionPreDef = 106,             /* ActionPreDef  */
  YYSYMBOL_Precondition = 107,             /* Precondition  */
  YYSYMBOL_ActionObsDef = 108,             /* ActionObsDef  */
  YYSYMBOL_ObsConditionDef = 109,          /* ObsConditionDef  */
  YYSYMBOL_ListObsConditionDef = 110,      /* ListObsConditionDef  */
  YYSYMBOL_LibraryDef = 111,               /* LibraryDef  */
  YYSYMBOL_LibraryItemDef = 112,           /* LibraryItemDef  */
  YYSYMBOL_ListLibraryItemDef = 113,       /* ListLibraryItemDef  */
  YYSYMBOL_ActionTypeDef = 114,            /* ActionTypeDef  */
  YYSYMBOL_ActionTypeParameterDef = 115,   /* ActionTypeParameterDef  */
  YYSYMBOL_ActionTypeFrameDef = 116,       /* ActionTypeFrameDef  */
  YYSYMBOL_ActionTypeEventsDef = 117,      /* ActionTypeEventsDef  */
  YYSYMBOL_ActionTypeRelDef = 118,         /* ActionTypeRelDef  */
  YYSYMBOL_ActionTypeDesDef = 119,         /* ActionTypeDesDef  */
  YYSYMBOL_EventSignature = 120,           /* EventSignature  */
  YYSYMBOL_ListEventSignature = 121,       /* ListEventSignature  */
  YYSYMBOL_ActionRelations = 122,          /* ActionRelations  */
  YYSYMBOL_EventRelation = 123,            /* EventRelation  */
  YYSYMBOL_ListEventRelation = 124,        /* ListEventRelation  */
  YYSYMBOL_EventNamePair = 125,            /* EventNamePair  */
  YYSYMBOL_ListEventNamePair = 126,        /* ListEventNamePair  */
  YYSYMBOL_EventDef = 127,                 /* EventDef  */
  YYSYMBOL_EventParameterDef = 128,        /* EventParameterDef  */
  YYSYMBOL_EventPreDef = 129,              /* EventPreDef  */
  YYSYMBOL_EventPostDef = 130,             /* EventPostDef  */
  YYSYMBOL_EventPostconditions = 131,      /* EventPostconditions  */
  YYSYMBOL_LiteralPostcondition = 132,     /* LiteralPostcondition  */
  YYSYMBOL_ListLiteralPostcondition = 133, /* ListLiteralPostcondition  */
  YYSYMBOL_Postcondition = 134,            /* Postcondition  */
  YYSYMBOL_ProblemDef = 135,               /* ProblemDef  */
  YYSYMBOL_ProblemItemDef = 136,           /* ProblemItemDef  */
  YYSYMBOL_ListProblemItemDef = 137,       /* ListProblemItemDef  */
  YYSYMBOL_ProblemDomainNameDef = 138,     /* ProblemDomainNameDef  */
  YYSYMBOL_AgentNamesDef = 139,            /* AgentNamesDef  */
  YYSYMBOL_AgentGroupsListDef = 140,       /* AgentGroupsListDef  */
  YYSYMBOL_AgentGroupDef = 141,            /* AgentGroupDef  */
  YYSYMBOL_ListAgentGroupDef = 142,        /* ListAgentGroupDef  */
  YYSYMBOL_ObjectNamesDef = 143,           /* ObjectNamesDef  */
  YYSYMBOL_InitDef = 144,                  /* InitDef  */
  YYSYMBOL_InitialStateDescr = 145,        /* InitialStateDescr  */
  YYSYMBOL_FTheoryFormula = 146,           /* FTheoryFormula  */
  YYSYMBOL_ListFTheoryFormula = 147,       /* ListFTheoryFormula  */
  YYSYMBOL_KPredicateFormula = 148,        /* KPredicateFormula  */
  YYSYMBOL_KWPredicateFormula = 149,       /* KWPredicateFormula  */
  YYSYMBOL_NotKWPredicateFormula = 150,    /* NotKWPredicateFormula  */
  YYSYMBOL_InitialModelDef = 151,          /* InitialModelDef  */
  YYSYMBOL_ModelWorldsDef = 152,           /* ModelWorldsDef  */
  YYSYMBOL_ModelRelDef = 153,              /* ModelRelDef  */
  YYSYMBOL_ModelValDef = 154,              /* ModelValDef  */
  YYSYMBOL_ModelDesDef = 155,              /* ModelDesDef  */
  YYSYMBOL_ModelRelations = 156,           /* ModelRelations  */
  YYSYMBOL_ModelValuation = 157,           /* ModelValuation  */
  YYSYMBOL_WorldRelation = 158,            /* WorldRelation  */
  YYSYMBOL_ListWorldRelation = 159,        /* ListWorldRelation  */
  YYSYMBOL_WorldNamePair = 160,            /* WorldNamePair  */
  YYSYMBOL_ListWorldNamePair = 161,        /* ListWorldNamePair  */
  YYSYMBOL_WorldValuation = 162,           /* WorldValuation  */
  YYSYMBOL_ListWorldValuation = 163,       /* ListWorldValuation  */
  YYSYMBOL_GoalDef = 164,                  /* GoalDef  */
  YYSYMBOL_Formula = 165,                  /* Formula  */
  YYSYMBOL_ListFormula = 166,              /* ListFormula  */
  YYSYMBOL_AtomicFormula = 167,            /* AtomicFormula  */
  YYSYMBOL_AtomicEqFormula = 168,          /* AtomicEqFormula  */
  YYSYMBOL_MetaTerm = 169,                 /* MetaTerm  */
  YYSYMBOL_ListMetaTerm = 170,             /* ListMetaTerm  */
  YYSYMBOL_Term = 171,                     /* Term  */
  YYSYMBOL_Modality = 172,                 /* Modality  */
  YYSYMBOL_SingleModality = 173,           /* SingleModality  */
  YYSYMBOL_GroupModality = 174,            /* GroupModality  */
  YYSYMBOL_ModalityLabel = 175,            /* ModalityLabel  */
  YYSYMBOL_KnowsWhether = 176,             /* KnowsWhether  */
  YYSYMBOL_Literal = 177,                  /* Literal  */
  YYSYMBOL_ListLiteral = 178,              /* ListLiteral  */
  YYSYMBOL_PredicateFormula = 179,         /* PredicateFormula  */
  YYSYMBOL_ListPredicateFormula = 180,     /* ListPredicateFormula  */
  YYSYMBOL_BasicTypedIdentList = 181,      /* BasicTypedIdentList  */
  YYSYMBOL_BasicTypedVariableList = 182,   /* BasicTypedVariableList  */
  YYSYMBOL_TypedVariableList = 183,        /* TypedVariableList  */
  YYSYMBOL_PredicateName = 184,            /* PredicateName  */
  YYSYMBOL_ModalityAgent = 185,            /* ModalityAgent  */
  YYSYMBOL_ListModalityAgent = 186,        /* ListModalityAgent  */
  YYSYMBOL_ModalityAgentGroup = 187,       /* ModalityAgentGroup  */
  YYSYMBOL_AgentGroupName = 188,           /* AgentGroupName  */
  YYSYMBOL_ObservingAgentGroup = 189,      /* ObservingAgentGroup  */
  YYSYMBOL_ListObservingAgentGroup = 190,  /* ListObservingAgentGroup  */
  YYSYMBOL_ObservingAgent = 191,           /* ObservingAgent  */
  YYSYMBOL_AgentList = 192,                /* AgentList  */
  YYSYMBOL_AllAgents = 193,                /* AllAgents  */
  YYSYMBOL_AnonVarAgent = 194,             /* AnonVarAgent  */
  YYSYMBOL_Parameter = 195,                /* Parameter  */
  YYSYMBOL_ListParameter = 196,            /* ListParameter  */
  YYSYMBOL_BasicParameter = 197,           /* BasicParameter  */
  YYSYMBOL_Type = 198,                     /* Type  */
  YYSYMBOL_BasicType = 199,                /* BasicType  */
  YYSYMBOL_CompoundType = 200,             /* CompoundType  */
  YYSYMBOL_ReservedBasicType = 201,        /* ReservedBasicType  */
  YYSYMBOL_ReservedFormulaType = 202,      /* ReservedFormulaType  */
  YYSYMBOL_LibraryName = 203,              /* LibraryName  */
  YYSYMBOL_ListLibraryName = 204,          /* ListLibraryName  */
  YYSYMBOL_ActionTypeName = 205,           /* ActionTypeName  */
  YYSYMBOL_ReservedActionTypeName = 206,   /* ReservedActionTypeName  */
  YYSYMBOL_EventName = 207,                /* EventName  */
  YYSYMBOL_ListEventName = 208,            /* ListEventName  */
  YYSYMBOL_ReservedEventName = 209,        /* ReservedEventName  */
  YYSYMBOL_ActionName = 210,               /* ActionName  */
  YYSYMBOL_ModelName = 211,                /* ModelName  */
  YYSYMBOL_WorldName = 212,                /* WorldName  */
  YYSYMBOL_ListWorldName = 213,            /* ListWorldName  */
  YYSYMBOL_RequireKey = 214,               /* RequireKey  */
  YYSYMBOL_ListRequireKey = 215,           /* ListRequireKey  */
  YYSYMBOL_TrivialDef = 216,               /* TrivialDef  */
  YYSYMBOL_ListName = 217,                 /* ListName  */
  YYSYMBOL_ListAgentName = 218,            /* ListAgentName  */
  YYSYMBOL_ListVariable = 219,             /* ListVariable  */
  YYSYMBOL_Name = 220,                     /* Name  */
  YYSYMBOL_AgentName = 221,                /* AgentName  */
  YYSYMBOL_ModalityName = 222,             /* ModalityName  */
  YYSYMBOL_Variable = 223                  /* Variable  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 189 "epddl.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, epddl_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 374 "Parser.C"


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
#define YYLAST   585

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  133
/* YYNRULES -- Number of rules.  */
#define YYNRULES  270
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  504

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   345


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
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   427,   427,   428,   429,   431,   433,   434,   435,   436,
     437,   438,   440,   441,   443,   445,   447,   449,   451,   453,
     454,   456,   458,   460,   462,   464,   466,   467,   469,   470,
     472,   473,   474,   476,   477,   479,   481,   482,   483,   484,
     486,   487,   489,   491,   493,   494,   496,   498,   500,   502,
     504,   505,   507,   508,   510,   511,   513,   514,   516,   518,
     519,   521,   523,   525,   527,   528,   530,   531,   533,   534,
     536,   537,   539,   540,   542,   544,   545,   546,   547,   548,
     549,   550,   551,   553,   554,   556,   558,   560,   562,   564,
     565,   567,   569,   571,   572,   574,   575,   576,   577,   578,
     579,   581,   582,   584,   585,   587,   588,   590,   591,   593,
     595,   597,   599,   601,   603,   604,   606,   607,   609,   610,
     612,   613,   615,   617,   618,   620,   622,   623,   625,   627,
     628,   629,   630,   631,   632,   633,   634,   635,   636,   638,
     639,   641,   642,   644,   646,   647,   649,   650,   652,   653,
     654,   656,   657,   659,   660,   662,   663,   665,   666,   667,
     668,   669,   671,   673,   674,   676,   677,   679,   680,   681,
     682,   683,   685,   686,   688,   689,   691,   692,   694,   695,
     697,   699,   700,   701,   702,   704,   705,   707,   709,   710,
     712,   714,   715,   717,   718,   719,   721,   722,   723,   725,
     727,   729,   730,   732,   733,   735,   736,   737,   739,   740,
     742,   743,   745,   747,   748,   750,   751,   752,   753,   755,
     757,   758,   760,   761,   763,   764,   765,   767,   768,   770,
     771,   773,   775,   777,   779,   781,   782,   784,   785,   786,
     787,   788,   789,   790,   791,   792,   793,   794,   795,   796,
     797,   798,   799,   800,   801,   802,   803,   804,   806,   807,
     809,   811,   812,   814,   815,   817,   818,   820,   822,   824,
     826
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
  "_RPAREN", "_MINUS", "_SYMB_7", "_SYMB_9", "_SYMB_2", "_SYMB_20",
  "_SYMB_19", "_SYMB_51", "_SYMB_40", "_SYMB_15", "_SYMB_45", "_SYMB_18",
  "_SYMB_52", "_SYMB_42", "_SYMB_16", "_SYMB_13", "_SYMB_46", "_SYMB_12",
  "_SYMB_29", "_SYMB_24", "_SYMB_53", "_SYMB_56", "_SYMB_57", "_SYMB_54",
  "_SYMB_55", "_SYMB_60", "_SYMB_59", "_SYMB_58", "_SYMB_49", "_SYMB_48",
  "_SYMB_26", "_SYMB_25", "_SYMB_44", "_SYMB_23", "_SYMB_11", "_SYMB_6",
  "_SYMB_50", "_SYMB_43", "_SYMB_8", "_SYMB_17", "_SYMB_10", "_SYMB_5",
  "_SYMB_14", "_SYMB_3", "_SYMB_4", "_SYMB_41", "_SYMB_47", "_SYMB_28",
  "_SYMB_27", "_LT", "_EQ", "_GT", "_SYMB_37", "_KW_All", "_LBRACK",
  "_RBRACK", "_KW_agent", "_KW_and", "_KW_announcement", "_KW_as",
  "_KW_define", "_KW_domain", "_SYMB_34", "_KW_false", "_KW_formula",
  "_SYMB_39", "_KW_if", "_KW_imply", "_SYMB_33", "_KW_library",
  "_KW_literal", "_KW_not", "_KW_ontic", "_KW_or", "_KW_otherwise",
  "_KW_predicate", "_SYMB_38", "_KW_problem", "_SYMB_35", "_KW_sensing",
  "_KW_true", "T_AgentName", "T_ModalityName", "T_Name", "T_Variable",
  "_INTEGER_", "$accept", "MainDef", "DomainDef", "DomainItemDef",
  "ListDomainItemDef", "DomainLibrariesNameDef", "RequireDef", "TypesDef",
  "PredicateListDef", "PredicateDef", "ListPredicateDef",
  "ObservabilityGroupsDef", "ActionDef", "ActionParameterDef",
  "ActionTypeSignatureDef", "ActionPreDef", "Precondition", "ActionObsDef",
  "ObsConditionDef", "ListObsConditionDef", "LibraryDef", "LibraryItemDef",
  "ListLibraryItemDef", "ActionTypeDef", "ActionTypeParameterDef",
  "ActionTypeFrameDef", "ActionTypeEventsDef", "ActionTypeRelDef",
  "ActionTypeDesDef", "EventSignature", "ListEventSignature",
  "ActionRelations", "EventRelation", "ListEventRelation", "EventNamePair",
  "ListEventNamePair", "EventDef", "EventParameterDef", "EventPreDef",
  "EventPostDef", "EventPostconditions", "LiteralPostcondition",
  "ListLiteralPostcondition", "Postcondition", "ProblemDef",
  "ProblemItemDef", "ListProblemItemDef", "ProblemDomainNameDef",
  "AgentNamesDef", "AgentGroupsListDef", "AgentGroupDef",
  "ListAgentGroupDef", "ObjectNamesDef", "InitDef", "InitialStateDescr",
  "FTheoryFormula", "ListFTheoryFormula", "KPredicateFormula",
  "KWPredicateFormula", "NotKWPredicateFormula", "InitialModelDef",
  "ModelWorldsDef", "ModelRelDef", "ModelValDef", "ModelDesDef",
  "ModelRelations", "ModelValuation", "WorldRelation", "ListWorldRelation",
  "WorldNamePair", "ListWorldNamePair", "WorldValuation",
  "ListWorldValuation", "GoalDef", "Formula", "ListFormula",
  "AtomicFormula", "AtomicEqFormula", "MetaTerm", "ListMetaTerm", "Term",
  "Modality", "SingleModality", "GroupModality", "ModalityLabel",
  "KnowsWhether", "Literal", "ListLiteral", "PredicateFormula",
  "ListPredicateFormula", "BasicTypedIdentList", "BasicTypedVariableList",
  "TypedVariableList", "PredicateName", "ModalityAgent",
  "ListModalityAgent", "ModalityAgentGroup", "AgentGroupName",
  "ObservingAgentGroup", "ListObservingAgentGroup", "ObservingAgent",
  "AgentList", "AllAgents", "AnonVarAgent", "Parameter", "ListParameter",
  "BasicParameter", "Type", "BasicType", "CompoundType",
  "ReservedBasicType", "ReservedFormulaType", "LibraryName",
  "ListLibraryName", "ActionTypeName", "ReservedActionTypeName",
  "EventName", "ListEventName", "ReservedEventName", "ActionName",
  "ModelName", "WorldName", "ListWorldName", "RequireKey",
  "ListRequireKey", "TrivialDef", "ListName", "ListAgentName",
  "ListVariable", "Name", "AgentName", "ModalityName", "Variable", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-391)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,   -38,    32,  -391,  -391,  -391,    59,  -391,   -30,    52,
      52,    52,  -391,   144,   157,   166,  -391,  -391,  -391,   128,
     278,   307,   139,  -391,  -391,  -391,  -391,  -391,  -391,  -391,
    -391,   237,  -391,  -391,  -391,  -391,  -391,  -391,   257,  -391,
    -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,    52,
      52,    81,   178,   454,    52,   340,    66,  -391,    81,    52,
     164,    38,    52,    52,   147,  -391,    52,   196,  -391,  -391,
      81,   210,  -391,    52,   178,   215,   303,  -391,  -391,  -391,
    -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,
    -391,  -391,  -391,  -391,  -391,   454,   217,   226,  -391,    52,
    -391,  -391,  -391,   203,  -391,  -391,  -391,   223,  -391,  -391,
     342,   255,    81,   284,   286,   318,   318,  -391,  -391,   289,
    -391,  -391,   164,  -391,  -391,   162,   233,   291,    62,  -391,
    -391,   251,  -391,   302,   320,   319,  -391,  -391,  -391,  -391,
     266,  -391,  -391,  -391,   271,   273,   275,  -391,  -391,  -391,
     363,    52,   377,   368,   382,   348,   339,  -391,  -391,  -391,
    -391,  -391,   352,   164,   164,   164,   164,  -391,   395,  -391,
     404,  -391,  -391,  -391,  -391,   326,  -391,   326,  -391,  -391,
      17,    52,   412,   412,   412,   412,   417,    52,  -391,   365,
    -391,  -391,   423,   388,  -391,   266,   435,   400,   439,  -391,
     266,   443,   448,   449,   256,  -391,   266,   452,   437,   266,
     189,   416,    81,   352,  -391,  -391,  -391,   164,   164,   456,
     164,  -391,    15,  -391,  -391,   321,   407,  -391,  -391,  -391,
    -391,   100,   405,   459,   374,   412,   412,   463,   412,  -391,
     465,    76,    52,   469,   422,   471,   340,   189,   445,  -391,
     479,   266,  -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,
      52,  -391,  -391,  -391,   481,  -391,   266,    81,   485,   446,
     487,   254,  -391,  -391,  -391,   486,   489,   438,   492,   164,
     494,   495,  -391,   496,  -391,  -391,  -391,  -391,  -391,   326,
    -391,  -391,  -391,  -391,  -391,   412,   497,   498,  -391,   501,
    -391,   294,   169,  -391,  -391,  -391,   412,  -391,    52,   502,
    -391,    33,  -391,   504,  -391,  -391,   505,   499,  -391,  -391,
    -391,   506,   507,   256,  -391,  -391,  -391,   508,   510,    66,
     485,  -391,   512,   503,  -391,  -391,   347,  -391,   514,  -391,
    -391,  -391,   447,  -391,  -391,  -391,  -391,  -391,  -391,  -391,
    -391,  -391,  -391,    71,    84,   515,   516,   517,    81,   464,
    -391,  -391,  -391,    81,   519,  -391,  -391,   211,  -391,    19,
    -391,   521,  -391,  -391,   522,   523,   140,   214,   506,  -391,
    -391,   266,   333,  -391,  -391,  -391,    33,  -391,   525,  -391,
    -391,   526,   527,   199,  -391,    46,   529,  -391,   -24,   460,
     458,   412,  -391,  -391,  -391,   467,   412,    81,    19,   530,
     531,   532,   476,    52,  -391,    52,  -391,  -391,   364,  -391,
    -391,  -391,  -391,  -391,   116,    81,  -391,  -391,  -391,  -391,
    -391,   -32,   266,  -391,  -391,   176,   534,   211,  -391,    66,
    -391,   535,  -391,   189,   536,  -391,  -391,   537,  -391,  -391,
     480,    52,    52,  -391,  -391,  -391,  -391,   538,   484,    81,
      51,   488,  -391,  -391,    28,   541,   542,   544,    66,   545,
     308,   546,   547,  -391,  -391,  -391,  -391,  -391,   548,    64,
    -391,  -391,   549,  -391,   164,  -391,    66,    66,  -391,  -391,
    -391,  -391,  -391,  -391,  -391,  -391,   550,  -391,  -391,   551,
     552,  -391,  -391,  -391
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     2,     3,     4,     0,     1,     0,     0,
       0,     0,   267,     0,     0,     0,    12,    40,    83,     0,
       0,     0,     0,     5,    13,     6,     7,     8,     9,    10,
      11,     0,    35,    36,    37,    41,    38,    39,     0,    74,
      76,    84,    75,    77,    78,    79,    80,    81,    82,     0,
       0,     0,     0,     0,   261,     0,     0,    89,     0,     0,
       0,     0,     0,   261,     0,   232,   220,     0,   219,   268,
     191,     0,   190,     0,    19,     0,     0,   248,   237,   242,
     249,   239,   243,   250,   253,   254,   251,   252,   246,   245,
     241,   247,   240,   238,   244,   258,     0,     0,   174,   261,
     226,   224,   225,     0,   222,   223,   231,     0,   227,   228,
       0,     0,   263,     0,     0,   161,   161,   137,   136,     0,
     134,   135,     0,   151,   152,     0,     0,     0,   101,    93,
      95,     0,   233,     0,     0,     0,   221,    14,   192,    21,
     265,   180,    20,    17,     0,     0,     0,   259,    15,    16,
     262,   261,     0,    45,     0,     0,     0,    87,    90,    86,
     264,    85,     0,     0,     0,     0,     0,   270,     0,   146,
       0,   159,   158,   160,   269,     0,   157,     0,   128,   133,
       0,     0,     0,     0,     0,     0,     0,   261,   199,     0,
      92,   102,     0,     0,    91,   265,     0,     0,     0,   176,
     265,     0,     0,     0,     0,   262,   265,     0,     0,   265,
       0,    65,     0,     0,   148,   149,   150,     0,     0,     0,
       0,   138,     0,   142,   200,     0,     0,   184,   183,   181,
     182,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    18,
     266,   265,   257,   256,   255,   214,   218,   216,   215,   217,
     261,   211,   213,   210,     0,   178,   265,     0,     0,     0,
       0,     0,    63,    26,    27,     0,     0,     0,     0,   139,
       0,     0,   132,     0,   141,   147,   144,   145,   154,   185,
     187,   156,   153,   155,    94,   172,     0,     0,   170,     0,
     171,     0,     0,    97,    98,    99,     0,    96,   235,     0,
     234,     0,   111,   120,   114,   115,     0,     0,    23,   203,
      25,     0,     0,     0,   266,   175,    43,   266,     0,     0,
      50,    46,     0,     0,    62,   260,     0,    64,    70,    66,
      67,    61,     0,   143,   140,   131,   129,   130,   186,   173,
     169,   167,   168,     0,     0,     0,     0,     0,     0,     0,
     105,   236,   110,     0,     0,   198,   196,     0,   121,     0,
     112,   126,   116,   117,     0,     0,     0,     0,    33,    28,
      22,   265,     0,    44,   203,    51,     0,    47,    56,    52,
      53,     0,     0,     0,   163,     0,     0,    71,     0,     0,
       0,     0,   104,   106,   108,     0,     0,     0,     0,   123,
       0,     0,     0,     0,   127,     0,   109,    24,   161,   206,
     205,   204,   201,   207,     0,     0,   195,   193,   194,    34,
     177,     0,   265,   208,   209,     0,     0,     0,    57,     0,
      42,     0,    69,     0,     0,   189,   188,     0,   162,   103,
       0,     0,     0,   124,   118,   119,   165,     0,     0,     0,
       0,     0,   179,    49,     0,    59,     0,     0,   229,     0,
       0,     0,     0,    72,    73,    88,   107,   197,     0,     0,
     113,   202,     0,    30,     0,   212,     0,     0,    60,    54,
      55,   230,    48,   164,    68,   122,     0,   166,    32,     0,
       0,   125,    31,    58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -391,  -391,  -391,  -391,  -391,  -391,   399,  -391,  -391,  -391,
     472,   539,  -391,  -391,  -391,  -391,   311,  -391,  -391,   182,
    -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,
     231,  -391,  -391,   174,  -391,    98,  -391,  -391,  -391,  -391,
    -391,  -391,   227,  -391,  -391,  -391,  -391,  -391,  -391,  -391,
    -391,  -391,  -391,  -391,  -391,   -29,   436,   325,   327,   328,
    -391,  -391,  -391,  -391,  -391,  -391,  -391,  -391,   258,  -391,
     158,  -391,   201,  -391,   -55,  -209,  -318,  -391,  -391,  -391,
    -139,  -391,  -391,  -391,   455,  -215,    94,  -391,  -154,  -167,
     -54,  -178,  -205,   -65,    35,   285,   398,  -391,  -390,   -56,
     152,  -325,  -114,  -207,  -391,   193,  -391,  -391,  -297,  -391,
    -391,   148,  -391,   518,   332,  -391,   -53,   112,  -391,  -391,
     401,  -314,  -289,  -391,   490,  -157,   -74,  -106,  -193,    -9,
     -48,  -391,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,    24,    19,    25,    26,    27,    28,    74,
      75,    29,    30,   135,   197,   248,   272,   322,   378,   379,
       4,    35,    20,    36,   153,   208,   269,   333,   392,   330,
     331,   387,   388,   389,   465,   466,    37,   155,   211,   276,
     337,   338,   339,   472,     5,    41,    21,    42,    43,    44,
     158,   110,    45,    46,   127,   128,   129,   355,   356,   357,
      47,   193,   244,   317,   375,   312,   370,   313,   314,   409,
     410,   371,   372,    48,   279,   280,   120,   121,   285,   222,
     420,   122,   123,   124,   177,   306,   395,   479,   130,   296,
      97,   198,   264,   169,   289,   290,   226,   444,    70,    71,
     425,   364,   227,   228,   421,   376,   422,   432,   260,   434,
     261,   262,    66,    67,   103,   104,   468,   469,   108,    64,
     131,   308,   309,    95,    96,   274,    98,   111,   199,   141,
      72,   176,   216
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    14,    15,   107,   270,   119,   160,   250,   140,   133,
     112,   283,   189,   265,   138,   287,   265,   245,   394,   361,
     284,   180,     1,   213,   335,   150,   381,     6,   235,   236,
     237,   238,     7,   335,   188,   460,     9,   256,   335,   170,
      65,    68,   125,   257,    10,    99,   105,   109,   258,   259,
     113,   442,    11,   132,    99,   412,   483,    68,   324,   168,
     187,   436,    69,     8,   112,   200,   180,   179,   393,   482,
     344,   299,   224,   327,   278,   353,   126,   205,   394,   182,
     301,   295,   297,   286,   295,   433,   315,   307,   234,   183,
     151,   188,   363,   184,   451,   185,   186,   126,   106,   412,
     230,    69,   230,    12,   167,    12,   277,    12,   217,   218,
     219,   220,   436,   240,   215,   187,    12,   443,   340,    69,
     200,   126,   484,   471,   496,   251,   457,   229,   349,   229,
     302,   266,    22,    23,   266,   302,   106,   478,   451,   401,
      12,   295,   151,   400,   271,   417,    49,   399,    50,    16,
     230,   186,   360,   214,    12,   273,   230,   224,   188,   373,
     292,   394,    17,   281,   112,   215,   180,    69,   114,   187,
     426,    18,   132,   224,   215,   390,   251,   229,   151,    51,
     271,   463,    73,   229,   401,    52,    69,    53,    54,   167,
     134,   251,   273,   271,   115,   263,   170,   365,   181,   418,
     237,   137,    69,   430,   214,   167,   325,   411,   117,   458,
     225,   328,   231,   214,   230,   139,   168,   426,   115,   423,
     143,   126,   148,   116,   182,   118,    69,   462,    12,   167,
     115,   149,   117,   310,   183,   418,   187,   105,   184,   265,
     185,   229,   358,   115,   117,    55,   152,   447,   116,   118,
      12,    99,   449,   365,   359,    69,    56,   117,   114,   335,
     159,   118,    69,   366,    12,   167,   154,    57,    58,   188,
     363,   224,   365,    59,   118,   441,   384,    51,   423,   467,
      60,    61,    31,    32,   445,    53,   474,    12,   167,   161,
     114,   188,    62,   424,   178,    63,   190,    69,   353,   310,
      69,   450,   428,   167,   192,    53,   200,   194,   115,   162,
     405,    38,    39,   116,   263,   407,   163,   255,   170,   366,
     109,   419,   117,   365,   195,   256,   164,   196,   215,   427,
     165,   257,   166,   144,   145,   146,   258,   259,   366,   118,
     115,   162,    12,   167,    12,   116,   156,   157,   163,   428,
     446,   393,   335,   302,   117,   167,   182,   266,   164,   112,
     310,   201,   165,   202,   166,   203,   183,   214,   114,   204,
     354,   118,   185,   263,    12,   167,   427,   288,   224,   188,
     419,   206,    12,   224,   188,   171,   209,   215,   473,   366,
     207,   172,   431,   210,   255,   170,    12,   167,   212,   310,
     221,   173,   256,   100,   310,   174,   310,    69,   257,   223,
     167,   486,    69,   258,   259,   167,   234,   101,   115,    33,
      40,    12,   239,   116,   102,   241,   214,   242,    12,   499,
     109,   171,   117,   500,   486,   243,   182,   172,    69,   246,
      12,   167,   310,   310,   249,   247,   183,   173,   252,   118,
     184,   174,   185,   253,   254,   109,   267,   268,    76,   109,
     275,   282,    12,   291,   294,   293,    77,    78,   298,    79,
     300,    80,    81,   311,   316,    82,   318,   109,   109,    83,
      84,    85,    86,    87,   321,   323,   326,    88,    89,   329,
     336,    90,   334,   332,   341,    91,    92,   343,   342,   345,
     346,   347,   350,   351,    93,    94,   352,   362,   367,   369,
     377,   398,   380,   374,   382,   383,   386,   391,   396,   400,
     402,   403,   404,   408,   406,   413,   415,   448,   416,   437,
     439,   358,   440,   393,   452,   456,   454,   455,   464,   470,
     477,   475,   476,   480,   481,   487,   142,   489,   485,   490,
     492,   493,   494,   495,   498,   501,   502,   503,   320,    34,
     429,   385,   438,   488,   191,   397,   303,   453,   304,   305,
     175,   368,   414,   497,   348,   232,   459,   435,   319,   461,
     491,     0,   233,     0,   136,   147
};

static const yytype_int16 yycheck[] =
{
       9,    10,    11,    56,   209,    60,   112,   200,    73,    63,
      58,   220,   126,   206,    70,   222,   209,   195,   336,   308,
       5,     4,     4,   162,     5,    99,   323,    65,   182,   183,
     184,   185,     0,     5,    58,   425,    66,    69,     5,   114,
      49,    50,     4,    75,    74,    54,    55,    56,    80,    81,
      59,     5,    82,    62,    63,   369,     5,    66,   251,   114,
     125,   386,    86,     4,   112,   140,     4,   122,     4,   459,
     279,   238,    57,   266,   213,     4,    59,   151,   396,    62,
       4,   235,   236,   222,   238,   382,   243,   241,     4,    72,
      99,    58,    59,    76,   408,    78,   125,    59,    70,   413,
     175,    86,   177,    88,    89,    88,   212,    88,   163,   164,
     165,   166,   437,   187,   162,   180,    88,    71,   275,    86,
     195,    59,    71,   441,    60,   200,   415,   175,   295,   177,
      59,   206,     4,     5,   209,    59,    70,   451,   452,   354,
      88,   295,   151,    59,     4,     5,     7,    76,     9,     5,
     225,   180,   306,   162,    88,   210,   231,    57,    58,   316,
      60,   479,     5,   218,   212,   213,     4,    86,     4,   234,
     377,     5,   181,    57,   222,   332,   251,   225,   187,    40,
       4,     5,     4,   231,   399,    46,    86,    48,    49,    89,
      43,   266,   247,     4,    54,   204,   271,   311,    36,    59,
     354,     5,    86,   381,   213,    89,   260,   364,    68,   418,
     175,   267,   177,   222,   289,     5,   271,   424,    54,   376,
       5,    59,     5,    59,    62,    85,    86,   432,    88,    89,
      54,     5,    68,   242,    72,    59,   301,   246,    76,   432,
      78,   289,    73,    54,    68,     8,    43,   401,    59,    85,
      88,   260,   406,   367,   302,    86,    19,    68,     4,     5,
       5,    85,    86,   311,    88,    89,    43,    10,    11,    58,
      59,    57,   386,    16,    85,    76,   329,    40,   435,   436,
      23,    24,     4,     5,   398,    48,   443,    88,    89,     5,
       4,    58,    35,    79,     5,    38,     5,    86,     4,   308,
      86,   407,   377,    89,    53,    48,   381,     5,    54,    55,
     358,     4,     5,    59,   323,   363,    62,    61,   393,   367,
     329,   376,    68,   437,     4,    69,    72,     8,   376,   377,
      76,    75,    78,    30,    31,    32,    80,    81,   386,    85,
      54,    55,    88,    89,    88,    59,     4,     5,    62,   424,
     398,     4,     5,    59,    68,    89,    62,   432,    72,   407,
     369,    90,    76,    90,    78,    90,    72,   376,     4,     6,
      76,    85,    78,   382,    88,    89,   424,    56,    57,    58,
     435,     4,    88,    57,    58,    67,     4,   435,   443,   437,
      22,    73,    59,    45,    61,   470,    88,    89,    59,   408,
       5,    83,    69,    63,   413,    87,   415,    86,    75,     5,
      89,   464,    86,    80,    81,    89,     4,    77,    54,    20,
      21,    88,     5,    59,    84,    60,   435,     4,    88,   484,
     439,    67,    68,   486,   487,    47,    62,    73,    86,     4,
      88,    89,   451,   452,     5,    45,    72,    83,     5,    85,
      76,    87,    78,     5,     5,   464,     4,    20,     4,   468,
      44,     5,    88,    56,     5,    60,    12,    13,     5,    15,
       5,    17,    18,     4,    52,    21,     5,   486,   487,    25,
      26,    27,    28,    29,    39,     6,     5,    33,    34,     4,
       4,    37,     5,    47,     5,    41,    42,     5,    60,     5,
       5,     5,     5,     5,    50,    51,     5,     5,     4,     4,
       4,    64,     5,    14,     6,     5,     4,    14,     4,    59,
       5,     5,     5,     4,    60,     4,     4,    60,     5,     4,
       4,    73,     5,     4,     4,    59,     5,     5,     4,     4,
      60,     5,     5,     5,    60,     4,    74,     5,    60,     5,
       5,     5,     5,     5,     5,     5,     5,     5,   247,    20,
     378,   330,   388,   465,   128,   338,   241,   409,   241,   241,
     115,   313,   371,   479,   289,   177,   424,   384,   246,   431,
     468,    -1,   181,    -1,    66,    95
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    92,    93,   111,   135,    65,     0,     4,    66,
      74,    82,    88,   220,   220,   220,     5,     5,     5,    95,
     113,   137,     4,     5,    94,    96,    97,    98,    99,   102,
     103,     4,     5,    97,   102,   112,   114,   127,     4,     5,
      97,   136,   138,   139,   140,   143,   144,   151,   164,     7,
       9,    40,    46,    48,    49,     8,    19,    10,    11,    16,
      23,    24,    35,    38,   210,   220,   203,   204,   220,    86,
     189,   190,   221,     4,   100,   101,     4,    12,    13,    15,
      17,    18,    21,    25,    26,    27,    28,    29,    33,    34,
      37,    41,    42,    50,    51,   214,   215,   181,   217,   220,
      63,    77,    84,   205,   206,   220,    70,   207,   209,   220,
     142,   218,   221,   220,     4,    54,    59,    68,    85,   165,
     167,   168,   172,   173,   174,     4,    59,   145,   146,   147,
     179,   211,   220,   181,    43,   104,   204,     5,   190,     5,
     184,   220,   101,     5,    30,    31,    32,   215,     5,     5,
     217,   220,    43,   115,    43,   128,     4,     5,   141,     5,
     218,     5,    55,    62,    72,    76,    78,    89,   165,   184,
     223,    67,    73,    83,    87,   175,   222,   175,     5,   165,
       4,    36,    62,    72,    76,    78,   146,   184,    58,   193,
       5,   147,    53,   152,     5,     4,     8,   105,   182,   219,
     223,    90,    90,    90,     6,   217,     4,    22,   116,     4,
      45,   129,    59,   171,   220,   221,   223,   165,   165,   165,
     165,     5,   170,     5,    57,   185,   187,   193,   194,   221,
     223,   185,   187,   211,     4,   179,   179,   179,   179,     5,
     217,    60,     4,    47,   153,   182,     4,    45,   106,     5,
     219,   223,     5,     5,     5,    61,    69,    75,    80,    81,
     199,   201,   202,   220,   183,   219,   223,     4,    20,   117,
     183,     4,   107,   165,   216,    44,   130,   218,   171,   165,
     166,   165,     5,   166,     5,   169,   171,   194,    56,   185,
     186,    56,    60,    60,     5,   179,   180,   179,     5,   180,
       5,     4,    59,   148,   149,   150,   176,   179,   212,   213,
     220,     4,   156,   158,   159,   216,    52,   154,     5,   205,
     107,    39,   108,     6,   219,   181,     5,   219,   190,     4,
     120,   121,    47,   118,     5,     5,     4,   131,   132,   133,
     216,     5,    60,     5,   166,     5,     5,     5,   186,   180,
       5,     5,     5,     4,    76,   148,   149,   150,    73,   221,
     179,   213,     5,    59,   192,   193,   221,     4,   159,     4,
     157,   162,   163,   216,    14,   155,   196,     4,   109,   110,
       5,   199,     6,     5,   207,   121,     4,   122,   123,   124,
     216,    14,   119,     4,   167,   177,     4,   133,    64,    76,
      59,   176,     5,     5,     5,   221,    60,   221,     4,   160,
     161,   216,   212,     4,   163,     4,     5,     5,    59,   165,
     171,   195,   197,   216,    79,   191,   194,   221,   223,   110,
     182,    59,   198,   199,   200,   196,   192,     4,   124,     4,
       5,    76,     5,    71,   188,   193,   221,   179,    60,   179,
     218,   212,     4,   161,     5,     5,    59,   213,   166,   191,
     189,   202,   183,     5,     4,   125,   126,   216,   207,   208,
       4,   167,   134,   165,   216,     5,     5,    60,   212,   178,
       5,    60,   189,     5,    71,    60,   207,     4,   126,     5,
       5,   208,     5,     5,     5,     5,    60,   177,     5,   165,
     207,     5,     5,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    92,    92,    93,    94,    94,    94,    94,
      94,    94,    95,    95,    96,    97,    98,    99,   100,   101,
     101,   102,   103,   104,   105,   106,   107,   107,   108,   108,
     109,   109,   109,   110,   110,   111,   112,   112,   112,   112,
     113,   113,   114,   115,   116,   116,   117,   118,   119,   120,
     121,   121,   122,   122,   123,   123,   124,   124,   125,   126,
     126,   127,   128,   129,   130,   130,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   137,   138,   139,   140,   141,   142,
     142,   143,   144,   145,   145,   146,   146,   146,   146,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150,   151,
     152,   153,   154,   155,   156,   156,   157,   157,   158,   158,
     159,   159,   160,   161,   161,   162,   163,   163,   164,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   166,
     166,   167,   167,   168,   169,   169,   170,   170,   171,   171,
     171,   172,   172,   173,   173,   174,   174,   175,   175,   175,
     175,   175,   176,   177,   177,   178,   178,   179,   179,   179,
     179,   179,   180,   180,   181,   181,   182,   182,   183,   183,
     184,   185,   185,   185,   185,   186,   186,   187,   188,   188,
     189,   190,   190,   191,   191,   191,   192,   192,   192,   193,
     194,   195,   195,   196,   196,   197,   197,   197,   198,   198,
     199,   199,   200,   201,   201,   202,   202,   202,   202,   203,
     204,   204,   205,   205,   206,   206,   206,   207,   207,   208,
     208,   209,   210,   211,   212,   213,   213,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   215,   215,
     216,   217,   217,   218,   218,   219,   219,   220,   221,   222,
     223
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     8,     1,     1,     1,     1,
       1,     1,     0,     2,     4,     4,     4,     4,     4,     1,
       2,     4,     8,     4,     5,     2,     1,     1,     2,     0,
       4,     6,     5,     1,     2,     8,     1,     1,     1,     1,
       0,     2,     9,     4,     4,     0,     2,     2,     4,     4,
       1,     2,     1,     1,     4,     4,     1,     2,     4,     1,
       2,     7,     4,     2,     2,     0,     1,     1,     5,     3,
       1,     2,     1,     1,     8,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     4,     4,     4,     7,     0,
       2,     4,     4,     1,     4,     1,     4,     4,     4,     4,
       3,     1,     2,     4,     3,     2,     3,     5,     3,     8,
       4,     2,     2,     4,     1,     1,     1,     1,     4,     4,
       1,     2,     4,     1,     2,     6,     1,     2,     4,     5,
       5,     5,     4,     2,     1,     1,     1,     1,     3,     1,
       2,     4,     3,     5,     1,     1,     0,     2,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     1,     1,     1,
       1,     0,     4,     1,     4,     0,     2,     5,     5,     5,
       4,     4,     1,     2,     1,     5,     1,     5,     1,     5,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     4,     1,     1,
       1,     1,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     4,     1,     2,
       2,     0,     2,     1,     2,     0,     2,     1,     1,     1,
       1
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
#line 427 "epddl.y"
                    { (yyval.maindef_) = new Domain((yyvsp[0].domaindef_)); result->maindef_ = (yyval.maindef_); }
#line 1876 "Parser.C"
    break;

  case 3: /* MainDef: LibraryDef  */
#line 428 "epddl.y"
               { (yyval.maindef_) = new ActionTypeLibrary((yyvsp[0].librarydef_)); result->maindef_ = (yyval.maindef_); }
#line 1882 "Parser.C"
    break;

  case 4: /* MainDef: ProblemDef  */
#line 429 "epddl.y"
               { (yyval.maindef_) = new Problem((yyvsp[0].problemdef_)); result->maindef_ = (yyval.maindef_); }
#line 1888 "Parser.C"
    break;

  case 5: /* DomainDef: _LPAREN _KW_define _LPAREN _KW_domain Name _RPAREN ListDomainItemDef _RPAREN  */
#line 431 "epddl.y"
                                                                                         { (yyval.domaindef_) = new EPDDLDomain((yyvsp[-3]._name), (yyvsp[-1].listdomainitemdef_)); }
#line 1894 "Parser.C"
    break;

  case 6: /* DomainItemDef: DomainLibrariesNameDef  */
#line 433 "epddl.y"
                                       { (yyval.domainitemdef_) = new EPDDLDomLibrary((yyvsp[0].domainlibrariesnamedef_)); }
#line 1900 "Parser.C"
    break;

  case 7: /* DomainItemDef: RequireDef  */
#line 434 "epddl.y"
               { (yyval.domainitemdef_) = new EPDDLDomRequire((yyvsp[0].requiredef_)); }
#line 1906 "Parser.C"
    break;

  case 8: /* DomainItemDef: TypesDef  */
#line 435 "epddl.y"
             { (yyval.domainitemdef_) = new EPDDLDomTypes((yyvsp[0].typesdef_)); }
#line 1912 "Parser.C"
    break;

  case 9: /* DomainItemDef: PredicateListDef  */
#line 436 "epddl.y"
                     { (yyval.domainitemdef_) = new EPDDLDomPredicates((yyvsp[0].predicatelistdef_)); }
#line 1918 "Parser.C"
    break;

  case 10: /* DomainItemDef: ObservabilityGroupsDef  */
#line 437 "epddl.y"
                           { (yyval.domainitemdef_) = new EPDDLDomObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 1924 "Parser.C"
    break;

  case 11: /* DomainItemDef: ActionDef  */
#line 438 "epddl.y"
              { (yyval.domainitemdef_) = new EPDDLDomAction((yyvsp[0].actiondef_)); }
#line 1930 "Parser.C"
    break;

  case 12: /* ListDomainItemDef: %empty  */
#line 440 "epddl.y"
                                { (yyval.listdomainitemdef_) = new ListDomainItemDef(); }
#line 1936 "Parser.C"
    break;

  case 13: /* ListDomainItemDef: ListDomainItemDef DomainItemDef  */
#line 441 "epddl.y"
                                    { (yyvsp[-1].listdomainitemdef_)->push_back((yyvsp[0].domainitemdef_)); (yyval.listdomainitemdef_) = (yyvsp[-1].listdomainitemdef_); }
#line 1942 "Parser.C"
    break;

  case 14: /* DomainLibrariesNameDef: _LPAREN _SYMB_2 ListLibraryName _RPAREN  */
#line 443 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listlibraryname_)->begin(),(yyvsp[-1].listlibraryname_)->end()) ;(yyval.domainlibrariesnamedef_) = new EPDDLDomLibraryNames((yyvsp[-1].listlibraryname_)); }
#line 1948 "Parser.C"
    break;

  case 15: /* RequireDef: _LPAREN _SYMB_3 ListRequireKey _RPAREN  */
#line 445 "epddl.y"
                                                    { std::reverse((yyvsp[-1].listrequirekey_)->begin(),(yyvsp[-1].listrequirekey_)->end()) ;(yyval.requiredef_) = new EPDDLRequire((yyvsp[-1].listrequirekey_)); }
#line 1954 "Parser.C"
    break;

  case 16: /* TypesDef: _LPAREN _SYMB_4 BasicTypedIdentList _RPAREN  */
#line 447 "epddl.y"
                                                       { (yyval.typesdef_) = new EPDDLTypes((yyvsp[-1].basictypedidentlist_)); }
#line 1960 "Parser.C"
    break;

  case 17: /* PredicateListDef: _LPAREN _SYMB_5 ListPredicateDef _RPAREN  */
#line 449 "epddl.y"
                                                            { std::reverse((yyvsp[-1].listpredicatedef_)->begin(),(yyvsp[-1].listpredicatedef_)->end()) ;(yyval.predicatelistdef_) = new EPDDLPredicateList((yyvsp[-1].listpredicatedef_)); }
#line 1966 "Parser.C"
    break;

  case 18: /* PredicateDef: _LPAREN PredicateName BasicTypedVariableList _RPAREN  */
#line 451 "epddl.y"
                                                                    { (yyval.predicatedef_) = new EPDDLPredicateDef((yyvsp[-2].predicatename_), (yyvsp[-1].basictypedvariablelist_)); }
#line 1972 "Parser.C"
    break;

  case 19: /* ListPredicateDef: PredicateDef  */
#line 453 "epddl.y"
                                { (yyval.listpredicatedef_) = new ListPredicateDef(); (yyval.listpredicatedef_)->push_back((yyvsp[0].predicatedef_)); }
#line 1978 "Parser.C"
    break;

  case 20: /* ListPredicateDef: PredicateDef ListPredicateDef  */
#line 454 "epddl.y"
                                  { (yyvsp[0].listpredicatedef_)->push_back((yyvsp[-1].predicatedef_)); (yyval.listpredicatedef_) = (yyvsp[0].listpredicatedef_); }
#line 1984 "Parser.C"
    break;

  case 21: /* ObservabilityGroupsDef: _LPAREN _SYMB_6 ListObservingAgentGroup _RPAREN  */
#line 456 "epddl.y"
                                                                         { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.observabilitygroupsdef_) = new EPDDLObsGroupsNames((yyvsp[-1].listobservingagentgroup_)); }
#line 1990 "Parser.C"
    break;

  case 22: /* ActionDef: _LPAREN _SYMB_7 ActionName ActionParameterDef ActionTypeSignatureDef ActionPreDef ActionObsDef _RPAREN  */
#line 458 "epddl.y"
                                                                                                                   { (yyval.actiondef_) = new EPDDLAction((yyvsp[-5].actionname_), (yyvsp[-4].actionparameterdef_), (yyvsp[-3].actiontypesignaturedef_), (yyvsp[-2].actionpredef_), (yyvsp[-1].actionobsdef_)); }
#line 1996 "Parser.C"
    break;

  case 23: /* ActionParameterDef: _SYMB_8 _LPAREN BasicTypedVariableList _RPAREN  */
#line 460 "epddl.y"
                                                                    { (yyval.actionparameterdef_) = new ActionPar((yyvsp[-1].basictypedvariablelist_)); }
#line 2002 "Parser.C"
    break;

  case 24: /* ActionTypeSignatureDef: _SYMB_9 _LPAREN ActionTypeName ListParameter _RPAREN  */
#line 462 "epddl.y"
                                                                              { (yyval.actiontypesignaturedef_) = new ActionSignature((yyvsp[-2].actiontypename_), (yyvsp[-1].listparameter_)); }
#line 2008 "Parser.C"
    break;

  case 25: /* ActionPreDef: _SYMB_10 Precondition  */
#line 464 "epddl.y"
                                     { (yyval.actionpredef_) = new ActionPre((yyvsp[0].precondition_)); }
#line 2014 "Parser.C"
    break;

  case 26: /* Precondition: Formula  */
#line 466 "epddl.y"
                       { (yyval.precondition_) = new FormulaPrecondition((yyvsp[0].formula_)); }
#line 2020 "Parser.C"
    break;

  case 27: /* Precondition: TrivialDef  */
#line 467 "epddl.y"
               { (yyval.precondition_) = new TrivialPrecondition((yyvsp[0].trivialdef_)); }
#line 2026 "Parser.C"
    break;

  case 28: /* ActionObsDef: _SYMB_11 ListObsConditionDef  */
#line 469 "epddl.y"
                                            { std::reverse((yyvsp[0].listobsconditiondef_)->begin(),(yyvsp[0].listobsconditiondef_)->end()) ;(yyval.actionobsdef_) = new ActionObs((yyvsp[0].listobsconditiondef_)); }
#line 2032 "Parser.C"
    break;

  case 29: /* ActionObsDef: %empty  */
#line 470 "epddl.y"
                { (yyval.actionobsdef_) = new EmptyActionObs(); }
#line 2038 "Parser.C"
    break;

  case 30: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _RPAREN  */
#line 472 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new EmptyObsCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2044 "Parser.C"
    break;

  case 31: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _KW_if Formula _RPAREN  */
#line 473 "epddl.y"
                                                                      { (yyval.obsconditiondef_) = new ObsCond((yyvsp[-4].observingagent_), (yyvsp[-3].observingagentgroup_), (yyvsp[-1].formula_)); }
#line 2050 "Parser.C"
    break;

  case 32: /* ObsConditionDef: _LPAREN _KW_otherwise ObservingAgent ObservingAgentGroup _RPAREN  */
#line 474 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new ObsOtherwiseCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2056 "Parser.C"
    break;

  case 33: /* ListObsConditionDef: ObsConditionDef  */
#line 476 "epddl.y"
                                      { (yyval.listobsconditiondef_) = new ListObsConditionDef(); (yyval.listobsconditiondef_)->push_back((yyvsp[0].obsconditiondef_)); }
#line 2062 "Parser.C"
    break;

  case 34: /* ListObsConditionDef: ObsConditionDef ListObsConditionDef  */
#line 477 "epddl.y"
                                        { (yyvsp[0].listobsconditiondef_)->push_back((yyvsp[-1].obsconditiondef_)); (yyval.listobsconditiondef_) = (yyvsp[0].listobsconditiondef_); }
#line 2068 "Parser.C"
    break;

  case 35: /* LibraryDef: _LPAREN _KW_define _LPAREN _KW_library Name _RPAREN ListLibraryItemDef _RPAREN  */
#line 479 "epddl.y"
                                                                                            { (yyval.librarydef_) = new EPDDLLibrary((yyvsp[-3]._name), (yyvsp[-1].listlibraryitemdef_)); }
#line 2074 "Parser.C"
    break;

  case 36: /* LibraryItemDef: RequireDef  */
#line 481 "epddl.y"
                            { (yyval.libraryitemdef_) = new EPDDLLibRequire((yyvsp[0].requiredef_)); }
#line 2080 "Parser.C"
    break;

  case 37: /* LibraryItemDef: ObservabilityGroupsDef  */
#line 482 "epddl.y"
                           { (yyval.libraryitemdef_) = new EPDDLLibObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 2086 "Parser.C"
    break;

  case 38: /* LibraryItemDef: ActionTypeDef  */
#line 483 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibActionType((yyvsp[0].actiontypedef_)); }
#line 2092 "Parser.C"
    break;

  case 39: /* LibraryItemDef: EventDef  */
#line 484 "epddl.y"
             { (yyval.libraryitemdef_) = new EPDDLLibEvent((yyvsp[0].eventdef_)); }
#line 2098 "Parser.C"
    break;

  case 40: /* ListLibraryItemDef: %empty  */
#line 486 "epddl.y"
                                 { (yyval.listlibraryitemdef_) = new ListLibraryItemDef(); }
#line 2104 "Parser.C"
    break;

  case 41: /* ListLibraryItemDef: ListLibraryItemDef LibraryItemDef  */
#line 487 "epddl.y"
                                      { (yyvsp[-1].listlibraryitemdef_)->push_back((yyvsp[0].libraryitemdef_)); (yyval.listlibraryitemdef_) = (yyvsp[-1].listlibraryitemdef_); }
#line 2110 "Parser.C"
    break;

  case 42: /* ActionTypeDef: _LPAREN _SYMB_9 ActionTypeName ActionTypeParameterDef ActionTypeFrameDef ActionTypeEventsDef ActionTypeRelDef ActionTypeDesDef _RPAREN  */
#line 489 "epddl.y"
                                                                                                                                                       { (yyval.actiontypedef_) = new EPDDLActType((yyvsp[-6].actiontypename_), (yyvsp[-5].actiontypeparameterdef_), (yyvsp[-4].actiontypeframedef_), (yyvsp[-3].actiontypeeventsdef_), (yyvsp[-2].actiontypereldef_), (yyvsp[-1].actiontypedesdef_)); }
#line 2116 "Parser.C"
    break;

  case 43: /* ActionTypeParameterDef: _SYMB_8 _LPAREN TypedVariableList _RPAREN  */
#line 491 "epddl.y"
                                                                   { (yyval.actiontypeparameterdef_) = new ActTypePar((yyvsp[-1].typedvariablelist_)); }
#line 2122 "Parser.C"
    break;

  case 44: /* ActionTypeFrameDef: _SYMB_12 _LPAREN ListObservingAgentGroup _RPAREN  */
#line 493 "epddl.y"
                                                                      { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.actiontypeframedef_) = new ActTypeFrame((yyvsp[-1].listobservingagentgroup_)); }
#line 2128 "Parser.C"
    break;

  case 45: /* ActionTypeFrameDef: %empty  */
#line 494 "epddl.y"
                { (yyval.actiontypeframedef_) = new EmptyActTypeFrame(); }
#line 2134 "Parser.C"
    break;

  case 46: /* ActionTypeEventsDef: _SYMB_13 ListEventSignature  */
#line 496 "epddl.y"
                                                  { std::reverse((yyvsp[0].listeventsignature_)->begin(),(yyvsp[0].listeventsignature_)->end()) ;(yyval.actiontypeeventsdef_) = new ActTypeEvents((yyvsp[0].listeventsignature_)); }
#line 2140 "Parser.C"
    break;

  case 47: /* ActionTypeRelDef: _SYMB_14 ActionRelations  */
#line 498 "epddl.y"
                                            { (yyval.actiontypereldef_) = new ActTypeRel((yyvsp[0].actionrelations_)); }
#line 2146 "Parser.C"
    break;

  case 48: /* ActionTypeDesDef: _SYMB_15 _LPAREN ListEventName _RPAREN  */
#line 500 "epddl.y"
                                                          { std::reverse((yyvsp[-1].listeventname_)->begin(),(yyvsp[-1].listeventname_)->end()) ;(yyval.actiontypedesdef_) = new ActTypeDes((yyvsp[-1].listeventname_)); }
#line 2152 "Parser.C"
    break;

  case 49: /* EventSignature: _LPAREN EventName ListParameter _RPAREN  */
#line 502 "epddl.y"
                                                         { (yyval.eventsignature_) = new EventSign((yyvsp[-2].eventname_), (yyvsp[-1].listparameter_)); }
#line 2158 "Parser.C"
    break;

  case 50: /* ListEventSignature: EventSignature  */
#line 504 "epddl.y"
                                    { (yyval.listeventsignature_) = new ListEventSignature(); (yyval.listeventsignature_)->push_back((yyvsp[0].eventsignature_)); }
#line 2164 "Parser.C"
    break;

  case 51: /* ListEventSignature: EventSignature ListEventSignature  */
#line 505 "epddl.y"
                                      { (yyvsp[0].listeventsignature_)->push_back((yyvsp[-1].eventsignature_)); (yyval.listeventsignature_) = (yyvsp[0].listeventsignature_); }
#line 2170 "Parser.C"
    break;

  case 52: /* ActionRelations: ListEventRelation  */
#line 507 "epddl.y"
                                    { std::reverse((yyvsp[0].listeventrelation_)->begin(),(yyvsp[0].listeventrelation_)->end()) ;(yyval.actionrelations_) = new EventsActionRel((yyvsp[0].listeventrelation_)); }
#line 2176 "Parser.C"
    break;

  case 53: /* ActionRelations: TrivialDef  */
#line 508 "epddl.y"
               { (yyval.actionrelations_) = new TrivialActionRel((yyvsp[0].trivialdef_)); }
#line 2182 "Parser.C"
    break;

  case 54: /* EventRelation: _LPAREN AgentList ListEventNamePair _RPAREN  */
#line 510 "epddl.y"
                                                            { std::reverse((yyvsp[-1].listeventnamepair_)->begin(),(yyvsp[-1].listeventnamepair_)->end()) ;(yyval.eventrelation_) = new EventRel((yyvsp[-2].agentlist_), (yyvsp[-1].listeventnamepair_)); }
#line 2188 "Parser.C"
    break;

  case 55: /* EventRelation: _LPAREN AgentList TrivialDef _RPAREN  */
#line 511 "epddl.y"
                                         { (yyval.eventrelation_) = new TrivialEventRel((yyvsp[-2].agentlist_), (yyvsp[-1].trivialdef_)); }
#line 2194 "Parser.C"
    break;

  case 56: /* ListEventRelation: EventRelation  */
#line 513 "epddl.y"
                                  { (yyval.listeventrelation_) = new ListEventRelation(); (yyval.listeventrelation_)->push_back((yyvsp[0].eventrelation_)); }
#line 2200 "Parser.C"
    break;

  case 57: /* ListEventRelation: EventRelation ListEventRelation  */
#line 514 "epddl.y"
                                    { (yyvsp[0].listeventrelation_)->push_back((yyvsp[-1].eventrelation_)); (yyval.listeventrelation_) = (yyvsp[0].listeventrelation_); }
#line 2206 "Parser.C"
    break;

  case 58: /* EventNamePair: _LPAREN EventName EventName _RPAREN  */
#line 516 "epddl.y"
                                                    { (yyval.eventnamepair_) = new EventPair((yyvsp[-2].eventname_), (yyvsp[-1].eventname_)); }
#line 2212 "Parser.C"
    break;

  case 59: /* ListEventNamePair: EventNamePair  */
#line 518 "epddl.y"
                                  { (yyval.listeventnamepair_) = new ListEventNamePair(); (yyval.listeventnamepair_)->push_back((yyvsp[0].eventnamepair_)); }
#line 2218 "Parser.C"
    break;

  case 60: /* ListEventNamePair: EventNamePair ListEventNamePair  */
#line 519 "epddl.y"
                                    { (yyvsp[0].listeventnamepair_)->push_back((yyvsp[-1].eventnamepair_)); (yyval.listeventnamepair_) = (yyvsp[0].listeventnamepair_); }
#line 2224 "Parser.C"
    break;

  case 61: /* EventDef: _LPAREN _SYMB_16 EventName EventParameterDef EventPreDef EventPostDef _RPAREN  */
#line 521 "epddl.y"
                                                                                         { (yyval.eventdef_) = new EPDDLEvent((yyvsp[-4].eventname_), (yyvsp[-3].eventparameterdef_), (yyvsp[-2].eventpredef_), (yyvsp[-1].eventpostdef_)); }
#line 2230 "Parser.C"
    break;

  case 62: /* EventParameterDef: _SYMB_8 _LPAREN TypedVariableList _RPAREN  */
#line 523 "epddl.y"
                                                              { (yyval.eventparameterdef_) = new EventPar((yyvsp[-1].typedvariablelist_)); }
#line 2236 "Parser.C"
    break;

  case 63: /* EventPreDef: _SYMB_10 Precondition  */
#line 525 "epddl.y"
                                    { (yyval.eventpredef_) = new EventPre((yyvsp[0].precondition_)); }
#line 2242 "Parser.C"
    break;

  case 64: /* EventPostDef: _SYMB_17 EventPostconditions  */
#line 527 "epddl.y"
                                            { (yyval.eventpostdef_) = new EventPost((yyvsp[0].eventpostconditions_)); }
#line 2248 "Parser.C"
    break;

  case 65: /* EventPostDef: %empty  */
#line 528 "epddl.y"
                { (yyval.eventpostdef_) = new EmptyEventPost(); }
#line 2254 "Parser.C"
    break;

  case 66: /* EventPostconditions: ListLiteralPostcondition  */
#line 530 "epddl.y"
                                               { std::reverse((yyvsp[0].listliteralpostcondition_)->begin(),(yyvsp[0].listliteralpostcondition_)->end()) ;(yyval.eventpostconditions_) = new Postconditions((yyvsp[0].listliteralpostcondition_)); }
#line 2260 "Parser.C"
    break;

  case 67: /* EventPostconditions: TrivialDef  */
#line 531 "epddl.y"
               { (yyval.eventpostconditions_) = new TrivialPostconditions((yyvsp[0].trivialdef_)); }
#line 2266 "Parser.C"
    break;

  case 68: /* LiteralPostcondition: _LPAREN Literal _KW_if Postcondition _RPAREN  */
#line 533 "epddl.y"
                                                                    { (yyval.literalpostcondition_) = new LiteralPost((yyvsp[-3].literal_), (yyvsp[-1].postcondition_)); }
#line 2272 "Parser.C"
    break;

  case 69: /* LiteralPostcondition: _LPAREN Literal _RPAREN  */
#line 534 "epddl.y"
                            { (yyval.literalpostcondition_) = new TrivialLiteralPost((yyvsp[-1].literal_)); }
#line 2278 "Parser.C"
    break;

  case 70: /* ListLiteralPostcondition: LiteralPostcondition  */
#line 536 "epddl.y"
                                                { (yyval.listliteralpostcondition_) = new ListLiteralPostcondition(); (yyval.listliteralpostcondition_)->push_back((yyvsp[0].literalpostcondition_)); }
#line 2284 "Parser.C"
    break;

  case 71: /* ListLiteralPostcondition: LiteralPostcondition ListLiteralPostcondition  */
#line 537 "epddl.y"
                                                  { (yyvsp[0].listliteralpostcondition_)->push_back((yyvsp[-1].literalpostcondition_)); (yyval.listliteralpostcondition_) = (yyvsp[0].listliteralpostcondition_); }
#line 2290 "Parser.C"
    break;

  case 72: /* Postcondition: Formula  */
#line 539 "epddl.y"
                        { (yyval.postcondition_) = new FormulaPostcondition((yyvsp[0].formula_)); }
#line 2296 "Parser.C"
    break;

  case 73: /* Postcondition: TrivialDef  */
#line 540 "epddl.y"
               { (yyval.postcondition_) = new TrivialPostcondition((yyvsp[0].trivialdef_)); }
#line 2302 "Parser.C"
    break;

  case 74: /* ProblemDef: _LPAREN _KW_define _LPAREN _KW_problem Name _RPAREN ListProblemItemDef _RPAREN  */
#line 542 "epddl.y"
                                                                                            { (yyval.problemdef_) = new EPDDLProblem((yyvsp[-3]._name), (yyvsp[-1].listproblemitemdef_)); }
#line 2308 "Parser.C"
    break;

  case 75: /* ProblemItemDef: ProblemDomainNameDef  */
#line 544 "epddl.y"
                                      { (yyval.problemitemdef_) = new EPDDLProbDomain((yyvsp[0].problemdomainnamedef_)); }
#line 2314 "Parser.C"
    break;

  case 76: /* ProblemItemDef: RequireDef  */
#line 545 "epddl.y"
               { (yyval.problemitemdef_) = new EPDDLProbRequire((yyvsp[0].requiredef_)); }
#line 2320 "Parser.C"
    break;

  case 77: /* ProblemItemDef: AgentNamesDef  */
#line 546 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbAgents((yyvsp[0].agentnamesdef_)); }
#line 2326 "Parser.C"
    break;

  case 78: /* ProblemItemDef: AgentGroupsListDef  */
#line 547 "epddl.y"
                       { (yyval.problemitemdef_) = new EPDDLProbAgentGroups((yyvsp[0].agentgroupslistdef_)); }
#line 2332 "Parser.C"
    break;

  case 79: /* ProblemItemDef: ObjectNamesDef  */
#line 548 "epddl.y"
                   { (yyval.problemitemdef_) = new EPDDLProbObjects((yyvsp[0].objectnamesdef_)); }
#line 2338 "Parser.C"
    break;

  case 80: /* ProblemItemDef: InitDef  */
#line 549 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbInit((yyvsp[0].initdef_)); }
#line 2344 "Parser.C"
    break;

  case 81: /* ProblemItemDef: InitialModelDef  */
#line 550 "epddl.y"
                    { (yyval.problemitemdef_) = new EPDDLProbInitModel((yyvsp[0].initialmodeldef_)); }
#line 2350 "Parser.C"
    break;

  case 82: /* ProblemItemDef: GoalDef  */
#line 551 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbGoal((yyvsp[0].goaldef_)); }
#line 2356 "Parser.C"
    break;

  case 83: /* ListProblemItemDef: %empty  */
#line 553 "epddl.y"
                                 { (yyval.listproblemitemdef_) = new ListProblemItemDef(); }
#line 2362 "Parser.C"
    break;

  case 84: /* ListProblemItemDef: ListProblemItemDef ProblemItemDef  */
#line 554 "epddl.y"
                                      { (yyvsp[-1].listproblemitemdef_)->push_back((yyvsp[0].problemitemdef_)); (yyval.listproblemitemdef_) = (yyvsp[-1].listproblemitemdef_); }
#line 2368 "Parser.C"
    break;

  case 85: /* ProblemDomainNameDef: _LPAREN _SYMB_18 Name _RPAREN  */
#line 556 "epddl.y"
                                                     { (yyval.problemdomainnamedef_) = new EPDDLDomainName((yyvsp[-1]._name)); }
#line 2374 "Parser.C"
    break;

  case 86: /* AgentNamesDef: _LPAREN _SYMB_19 ListAgentName _RPAREN  */
#line 558 "epddl.y"
                                                       { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentnamesdef_) = new EPDDLAgentNames((yyvsp[-1].listagentname_)); }
#line 2380 "Parser.C"
    break;

  case 87: /* AgentGroupsListDef: _LPAREN _SYMB_20 ListAgentGroupDef _RPAREN  */
#line 560 "epddl.y"
                                                                { (yyval.agentgroupslistdef_) = new EPDDLAgentGroupsList((yyvsp[-1].listagentgroupdef_)); }
#line 2386 "Parser.C"
    break;

  case 88: /* AgentGroupDef: _LPAREN _LBRACK ListAgentName _RBRACK _KW_as AgentGroupName _RPAREN  */
#line 562 "epddl.y"
                                                                                    { std::reverse((yyvsp[-4].listagentname_)->begin(),(yyvsp[-4].listagentname_)->end()) ;(yyval.agentgroupdef_) = new EPDDLAgentGroupDef((yyvsp[-4].listagentname_), (yyvsp[-1].agentgroupname_)); }
#line 2392 "Parser.C"
    break;

  case 89: /* ListAgentGroupDef: %empty  */
#line 564 "epddl.y"
                                { (yyval.listagentgroupdef_) = new ListAgentGroupDef(); }
#line 2398 "Parser.C"
    break;

  case 90: /* ListAgentGroupDef: ListAgentGroupDef AgentGroupDef  */
#line 565 "epddl.y"
                                    { (yyvsp[-1].listagentgroupdef_)->push_back((yyvsp[0].agentgroupdef_)); (yyval.listagentgroupdef_) = (yyvsp[-1].listagentgroupdef_); }
#line 2404 "Parser.C"
    break;

  case 91: /* ObjectNamesDef: _LPAREN _SYMB_23 BasicTypedIdentList _RPAREN  */
#line 567 "epddl.y"
                                                              { (yyval.objectnamesdef_) = new EPDDLObjectNames((yyvsp[-1].basictypedidentlist_)); }
#line 2410 "Parser.C"
    break;

  case 92: /* InitDef: _LPAREN _SYMB_24 InitialStateDescr _RPAREN  */
#line 569 "epddl.y"
                                                     { (yyval.initdef_) = new EPDDLInitialState((yyvsp[-1].initialstatedescr_)); }
#line 2416 "Parser.C"
    break;

  case 93: /* InitialStateDescr: ListFTheoryFormula  */
#line 571 "epddl.y"
                                       { std::reverse((yyvsp[0].listftheoryformula_)->begin(),(yyvsp[0].listftheoryformula_)->end()) ;(yyval.initialstatedescr_) = new FinitaryTheoryDescr((yyvsp[0].listftheoryformula_)); }
#line 2422 "Parser.C"
    break;

  case 94: /* InitialStateDescr: _LPAREN _SYMB_25 ModelName _RPAREN  */
#line 572 "epddl.y"
                                       { (yyval.initialstatedescr_) = new InitialModelDescr((yyvsp[-1].modelname_)); }
#line 2428 "Parser.C"
    break;

  case 95: /* FTheoryFormula: PredicateFormula  */
#line 574 "epddl.y"
                                  { (yyval.ftheoryformula_) = new FTheoryPredForm((yyvsp[0].predicateformula_)); }
#line 2434 "Parser.C"
    break;

  case 96: /* FTheoryFormula: _LBRACK AllAgents _RBRACK PredicateFormula  */
#line 575 "epddl.y"
                                               { (yyval.ftheoryformula_) = new FTheoryCKPredForm((yyvsp[-2].allagents_), (yyvsp[0].predicateformula_)); }
#line 2440 "Parser.C"
    break;

  case 97: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KPredicateFormula  */
#line 576 "epddl.y"
                                                { (yyval.ftheoryformula_) = new FTheoryCKKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kpredicateformula_)); }
#line 2446 "Parser.C"
    break;

  case 98: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KWPredicateFormula  */
#line 577 "epddl.y"
                                                 { (yyval.ftheoryformula_) = new FTheoryCKOrKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kwpredicateformula_)); }
#line 2452 "Parser.C"
    break;

  case 99: /* FTheoryFormula: _LBRACK AllAgents _RBRACK NotKWPredicateFormula  */
#line 578 "epddl.y"
                                                    { (yyval.ftheoryformula_) = new FTheoryCKAndKPredForm((yyvsp[-2].allagents_), (yyvsp[0].notkwpredicateformula_)); }
#line 2458 "Parser.C"
    break;

  case 100: /* FTheoryFormula: _LPAREN FTheoryFormula _RPAREN  */
#line 579 "epddl.y"
                                   { (yyval.ftheoryformula_) = (yyvsp[-1].ftheoryformula_); }
#line 2464 "Parser.C"
    break;

  case 101: /* ListFTheoryFormula: FTheoryFormula  */
#line 581 "epddl.y"
                                    { (yyval.listftheoryformula_) = new ListFTheoryFormula(); (yyval.listftheoryformula_)->push_back((yyvsp[0].ftheoryformula_)); }
#line 2470 "Parser.C"
    break;

  case 102: /* ListFTheoryFormula: FTheoryFormula ListFTheoryFormula  */
#line 582 "epddl.y"
                                      { (yyvsp[0].listftheoryformula_)->push_back((yyvsp[-1].ftheoryformula_)); (yyval.listftheoryformula_) = (yyvsp[0].listftheoryformula_); }
#line 2476 "Parser.C"
    break;

  case 103: /* KPredicateFormula: _LBRACK AgentName _RBRACK PredicateFormula  */
#line 584 "epddl.y"
                                                               { (yyval.kpredicateformula_) = new KPredFormula((yyvsp[-2]._agentname), (yyvsp[0].predicateformula_)); }
#line 2482 "Parser.C"
    break;

  case 104: /* KPredicateFormula: _LPAREN KPredicateFormula _RPAREN  */
#line 585 "epddl.y"
                                      { (yyval.kpredicateformula_) = (yyvsp[-1].kpredicateformula_); }
#line 2488 "Parser.C"
    break;

  case 105: /* KWPredicateFormula: KnowsWhether PredicateFormula  */
#line 587 "epddl.y"
                                                   { (yyval.kwpredicateformula_) = new KWPredFormula((yyvsp[-1].knowswhether_), (yyvsp[0].predicateformula_)); }
#line 2494 "Parser.C"
    break;

  case 106: /* KWPredicateFormula: _LPAREN KWPredicateFormula _RPAREN  */
#line 588 "epddl.y"
                                       { (yyval.kwpredicateformula_) = (yyvsp[-1].kwpredicateformula_); }
#line 2500 "Parser.C"
    break;

  case 107: /* NotKWPredicateFormula: _LPAREN _KW_not KnowsWhether PredicateFormula _RPAREN  */
#line 590 "epddl.y"
                                                                              { (yyval.notkwpredicateformula_) = new NotKWPredFormula((yyvsp[-2].knowswhether_), (yyvsp[-1].predicateformula_)); }
#line 2506 "Parser.C"
    break;

  case 108: /* NotKWPredicateFormula: _LPAREN NotKWPredicateFormula _RPAREN  */
#line 591 "epddl.y"
                                          { (yyval.notkwpredicateformula_) = (yyvsp[-1].notkwpredicateformula_); }
#line 2512 "Parser.C"
    break;

  case 109: /* InitialModelDef: _LPAREN _SYMB_26 ModelName ModelWorldsDef ModelRelDef ModelValDef ModelDesDef _RPAREN  */
#line 593 "epddl.y"
                                                                                                        { (yyval.initialmodeldef_) = new EPDDLInitialModel((yyvsp[-5].modelname_), (yyvsp[-4].modelworldsdef_), (yyvsp[-3].modelreldef_), (yyvsp[-2].modelvaldef_), (yyvsp[-1].modeldesdef_)); }
#line 2518 "Parser.C"
    break;

  case 110: /* ModelWorldsDef: _SYMB_27 _LPAREN ListWorldName _RPAREN  */
#line 595 "epddl.y"
                                                        { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modelworldsdef_) = new ModelWorlds((yyvsp[-1].listworldname_)); }
#line 2524 "Parser.C"
    break;

  case 111: /* ModelRelDef: _SYMB_14 ModelRelations  */
#line 597 "epddl.y"
                                      { (yyval.modelreldef_) = new ModelRel((yyvsp[0].modelrelations_)); }
#line 2530 "Parser.C"
    break;

  case 112: /* ModelValDef: _SYMB_28 ModelValuation  */
#line 599 "epddl.y"
                                      { (yyval.modelvaldef_) = new ModelVal((yyvsp[0].modelvaluation_)); }
#line 2536 "Parser.C"
    break;

  case 113: /* ModelDesDef: _SYMB_15 _LPAREN ListWorldName _RPAREN  */
#line 601 "epddl.y"
                                                     { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modeldesdef_) = new ModelDes((yyvsp[-1].listworldname_)); }
#line 2542 "Parser.C"
    break;

  case 114: /* ModelRelations: ListWorldRelation  */
#line 603 "epddl.y"
                                   { std::reverse((yyvsp[0].listworldrelation_)->begin(),(yyvsp[0].listworldrelation_)->end()) ;(yyval.modelrelations_) = new WorldsModelRel((yyvsp[0].listworldrelation_)); }
#line 2548 "Parser.C"
    break;

  case 115: /* ModelRelations: TrivialDef  */
#line 604 "epddl.y"
               { (yyval.modelrelations_) = new TrivialModelRel((yyvsp[0].trivialdef_)); }
#line 2554 "Parser.C"
    break;

  case 116: /* ModelValuation: ListWorldValuation  */
#line 606 "epddl.y"
                                    { std::reverse((yyvsp[0].listworldvaluation_)->begin(),(yyvsp[0].listworldvaluation_)->end()) ;(yyval.modelvaluation_) = new WorldsModelVal((yyvsp[0].listworldvaluation_)); }
#line 2560 "Parser.C"
    break;

  case 117: /* ModelValuation: TrivialDef  */
#line 607 "epddl.y"
               { (yyval.modelvaluation_) = new TrivialModelVal((yyvsp[0].trivialdef_)); }
#line 2566 "Parser.C"
    break;

  case 118: /* WorldRelation: _LPAREN AgentList ListWorldNamePair _RPAREN  */
#line 609 "epddl.y"
                                                            { std::reverse((yyvsp[-1].listworldnamepair_)->begin(),(yyvsp[-1].listworldnamepair_)->end()) ;(yyval.worldrelation_) = new WorldRel((yyvsp[-2].agentlist_), (yyvsp[-1].listworldnamepair_)); }
#line 2572 "Parser.C"
    break;

  case 119: /* WorldRelation: _LPAREN AgentList TrivialDef _RPAREN  */
#line 610 "epddl.y"
                                         { (yyval.worldrelation_) = new TrivialWorldRel((yyvsp[-2].agentlist_), (yyvsp[-1].trivialdef_)); }
#line 2578 "Parser.C"
    break;

  case 120: /* ListWorldRelation: WorldRelation  */
#line 612 "epddl.y"
                                  { (yyval.listworldrelation_) = new ListWorldRelation(); (yyval.listworldrelation_)->push_back((yyvsp[0].worldrelation_)); }
#line 2584 "Parser.C"
    break;

  case 121: /* ListWorldRelation: WorldRelation ListWorldRelation  */
#line 613 "epddl.y"
                                    { (yyvsp[0].listworldrelation_)->push_back((yyvsp[-1].worldrelation_)); (yyval.listworldrelation_) = (yyvsp[0].listworldrelation_); }
#line 2590 "Parser.C"
    break;

  case 122: /* WorldNamePair: _LPAREN WorldName WorldName _RPAREN  */
#line 615 "epddl.y"
                                                    { (yyval.worldnamepair_) = new WorldPair((yyvsp[-2].worldname_), (yyvsp[-1].worldname_)); }
#line 2596 "Parser.C"
    break;

  case 123: /* ListWorldNamePair: WorldNamePair  */
#line 617 "epddl.y"
                                  { (yyval.listworldnamepair_) = new ListWorldNamePair(); (yyval.listworldnamepair_)->push_back((yyvsp[0].worldnamepair_)); }
#line 2602 "Parser.C"
    break;

  case 124: /* ListWorldNamePair: WorldNamePair ListWorldNamePair  */
#line 618 "epddl.y"
                                    { (yyvsp[0].listworldnamepair_)->push_back((yyvsp[-1].worldnamepair_)); (yyval.listworldnamepair_) = (yyvsp[0].listworldnamepair_); }
#line 2608 "Parser.C"
    break;

  case 125: /* WorldValuation: _LPAREN WorldName _LBRACK ListLiteral _RBRACK _RPAREN  */
#line 620 "epddl.y"
                                                                       { (yyval.worldvaluation_) = new WorldVal((yyvsp[-4].worldname_), (yyvsp[-2].listliteral_)); }
#line 2614 "Parser.C"
    break;

  case 126: /* ListWorldValuation: WorldValuation  */
#line 622 "epddl.y"
                                    { (yyval.listworldvaluation_) = new ListWorldValuation(); (yyval.listworldvaluation_)->push_back((yyvsp[0].worldvaluation_)); }
#line 2620 "Parser.C"
    break;

  case 127: /* ListWorldValuation: WorldValuation ListWorldValuation  */
#line 623 "epddl.y"
                                      { (yyvsp[0].listworldvaluation_)->push_back((yyvsp[-1].worldvaluation_)); (yyval.listworldvaluation_) = (yyvsp[0].listworldvaluation_); }
#line 2626 "Parser.C"
    break;

  case 128: /* GoalDef: _LPAREN _SYMB_29 Formula _RPAREN  */
#line 625 "epddl.y"
                                           { (yyval.goaldef_) = new EPDDLGoals((yyvsp[-1].formula_)); }
#line 2632 "Parser.C"
    break;

  case 129: /* Formula: _LPAREN _KW_imply Formula Formula _RPAREN  */
#line 627 "epddl.y"
                                                    { (yyval.formula_) = new ImplyFormula((yyvsp[-2].formula_), (yyvsp[-1].formula_)); }
#line 2638 "Parser.C"
    break;

  case 130: /* Formula: _LPAREN _KW_or Formula ListFormula _RPAREN  */
#line 628 "epddl.y"
                                               { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new OrFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2644 "Parser.C"
    break;

  case 131: /* Formula: _LPAREN _KW_and Formula ListFormula _RPAREN  */
#line 629 "epddl.y"
                                                { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new AndFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2650 "Parser.C"
    break;

  case 132: /* Formula: _LPAREN _KW_not Formula _RPAREN  */
#line 630 "epddl.y"
                                    { (yyval.formula_) = new NotFormula((yyvsp[-1].formula_)); }
#line 2656 "Parser.C"
    break;

  case 133: /* Formula: Modality Formula  */
#line 631 "epddl.y"
                     { (yyval.formula_) = new ModalFormula((yyvsp[-1].modality_), (yyvsp[0].formula_)); }
#line 2662 "Parser.C"
    break;

  case 134: /* Formula: AtomicFormula  */
#line 632 "epddl.y"
                  { (yyval.formula_) = new AtmFormula((yyvsp[0].atomicformula_)); }
#line 2668 "Parser.C"
    break;

  case 135: /* Formula: AtomicEqFormula  */
#line 633 "epddl.y"
                    { (yyval.formula_) = new AtmEqFormula((yyvsp[0].atomiceqformula_)); }
#line 2674 "Parser.C"
    break;

  case 136: /* Formula: _KW_true  */
#line 634 "epddl.y"
             { (yyval.formula_) = new TrueFormula(); }
#line 2680 "Parser.C"
    break;

  case 137: /* Formula: _KW_false  */
#line 635 "epddl.y"
              { (yyval.formula_) = new FalseFormula(); }
#line 2686 "Parser.C"
    break;

  case 138: /* Formula: _LPAREN Formula _RPAREN  */
#line 636 "epddl.y"
                            { (yyval.formula_) = (yyvsp[-1].formula_); }
#line 2692 "Parser.C"
    break;

  case 139: /* ListFormula: Formula  */
#line 638 "epddl.y"
                      { (yyval.listformula_) = new ListFormula(); (yyval.listformula_)->push_back((yyvsp[0].formula_)); }
#line 2698 "Parser.C"
    break;

  case 140: /* ListFormula: Formula ListFormula  */
#line 639 "epddl.y"
                        { (yyvsp[0].listformula_)->push_back((yyvsp[-1].formula_)); (yyval.listformula_) = (yyvsp[0].listformula_); }
#line 2704 "Parser.C"
    break;

  case 141: /* AtomicFormula: _LPAREN PredicateName ListMetaTerm _RPAREN  */
#line 641 "epddl.y"
                                                           { (yyval.atomicformula_) = new Predicate((yyvsp[-2].predicatename_), (yyvsp[-1].listmetaterm_)); }
#line 2710 "Parser.C"
    break;

  case 142: /* AtomicFormula: _LPAREN Variable _RPAREN  */
#line 642 "epddl.y"
                             { (yyval.atomicformula_) = new VarFormula((yyvsp[-1]._variable)); }
#line 2716 "Parser.C"
    break;

  case 143: /* AtomicEqFormula: _LPAREN _EQ Term Term _RPAREN  */
#line 644 "epddl.y"
                                                { (yyval.atomiceqformula_) = new EqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 2722 "Parser.C"
    break;

  case 144: /* MetaTerm: Term  */
#line 646 "epddl.y"
                { (yyval.metaterm_) = new EPDDLMetaTerm((yyvsp[0].term_)); }
#line 2728 "Parser.C"
    break;

  case 145: /* MetaTerm: AnonVarAgent  */
#line 647 "epddl.y"
                 { (yyval.metaterm_) = new EPDDLMetaTermAnonVar((yyvsp[0].anonvaragent_)); }
#line 2734 "Parser.C"
    break;

  case 146: /* ListMetaTerm: %empty  */
#line 649 "epddl.y"
                           { (yyval.listmetaterm_) = new ListMetaTerm(); }
#line 2740 "Parser.C"
    break;

  case 147: /* ListMetaTerm: ListMetaTerm MetaTerm  */
#line 650 "epddl.y"
                          { (yyvsp[-1].listmetaterm_)->push_back((yyvsp[0].metaterm_)); (yyval.listmetaterm_) = (yyvsp[-1].listmetaterm_); }
#line 2746 "Parser.C"
    break;

  case 148: /* Term: Name  */
#line 652 "epddl.y"
            { (yyval.term_) = new EPDDLTermName((yyvsp[0]._name)); }
#line 2752 "Parser.C"
    break;

  case 149: /* Term: AgentName  */
#line 653 "epddl.y"
              { (yyval.term_) = new EPDDLTermAgentName((yyvsp[0]._agentname)); }
#line 2758 "Parser.C"
    break;

  case 150: /* Term: Variable  */
#line 654 "epddl.y"
             { (yyval.term_) = new EPDDLTermVar((yyvsp[0]._variable)); }
#line 2764 "Parser.C"
    break;

  case 151: /* Modality: SingleModality  */
#line 656 "epddl.y"
                          { (yyval.modality_) = new EPDDLLabeledMod((yyvsp[0].singlemodality_)); }
#line 2770 "Parser.C"
    break;

  case 152: /* Modality: GroupModality  */
#line 657 "epddl.y"
                  { (yyval.modality_) = new EPDDLLabeledGroupMod((yyvsp[0].groupmodality_)); }
#line 2776 "Parser.C"
    break;

  case 153: /* SingleModality: _LBRACK ModalityLabel ModalityAgent _RBRACK  */
#line 659 "epddl.y"
                                                             { (yyval.singlemodality_) = new LabBoxMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2782 "Parser.C"
    break;

  case 154: /* SingleModality: _LT ModalityLabel ModalityAgent _GT  */
#line 660 "epddl.y"
                                        { (yyval.singlemodality_) = new LabDiamondMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2788 "Parser.C"
    break;

  case 155: /* GroupModality: _LBRACK ModalityLabel ModalityAgentGroup _RBRACK  */
#line 662 "epddl.y"
                                                                 { (yyval.groupmodality_) = new LabBoxGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2794 "Parser.C"
    break;

  case 156: /* GroupModality: _LT ModalityLabel ModalityAgentGroup _GT  */
#line 663 "epddl.y"
                                             { (yyval.groupmodality_) = new LabDiamondGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2800 "Parser.C"
    break;

  case 157: /* ModalityLabel: ModalityName  */
#line 665 "epddl.y"
                             { (yyval.modalitylabel_) = new ModLabel((yyvsp[0]._modalityname)); }
#line 2806 "Parser.C"
    break;

  case 158: /* ModalityLabel: _SYMB_33  */
#line 666 "epddl.y"
             { (yyval.modalitylabel_) = new KnowsWhetherLabel(); }
#line 2812 "Parser.C"
    break;

  case 159: /* ModalityLabel: _SYMB_34  */
#line 667 "epddl.y"
             { (yyval.modalitylabel_) = new EverybodyKnowsLabel(); }
#line 2818 "Parser.C"
    break;

  case 160: /* ModalityLabel: _SYMB_35  */
#line 668 "epddl.y"
             { (yyval.modalitylabel_) = new SomeoneKnowsLabel(); }
#line 2824 "Parser.C"
    break;

  case 161: /* ModalityLabel: %empty  */
#line 669 "epddl.y"
                { (yyval.modalitylabel_) = new EmptyModLabel(); }
#line 2830 "Parser.C"
    break;

  case 162: /* KnowsWhether: _LBRACK _SYMB_33 AgentName _RBRACK  */
#line 671 "epddl.y"
                                                  { (yyval.knowswhether_) = new KnowsWhetherMod((yyvsp[-1]._agentname)); }
#line 2836 "Parser.C"
    break;

  case 163: /* Literal: AtomicFormula  */
#line 673 "epddl.y"
                        { (yyval.literal_) = new PosLiteral((yyvsp[0].atomicformula_)); }
#line 2842 "Parser.C"
    break;

  case 164: /* Literal: _LPAREN _KW_not AtomicFormula _RPAREN  */
#line 674 "epddl.y"
                                          { (yyval.literal_) = new NegLiteral((yyvsp[-1].atomicformula_)); }
#line 2848 "Parser.C"
    break;

  case 165: /* ListLiteral: %empty  */
#line 676 "epddl.y"
                          { (yyval.listliteral_) = new ListLiteral(); }
#line 2854 "Parser.C"
    break;

  case 166: /* ListLiteral: ListLiteral Literal  */
#line 677 "epddl.y"
                        { (yyvsp[-1].listliteral_)->push_back((yyvsp[0].literal_)); (yyval.listliteral_) = (yyvsp[-1].listliteral_); }
#line 2860 "Parser.C"
    break;

  case 167: /* PredicateFormula: _LPAREN _KW_imply PredicateFormula PredicateFormula _RPAREN  */
#line 679 "epddl.y"
                                                                               { (yyval.predicateformula_) = new ImplyPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].predicateformula_)); }
#line 2866 "Parser.C"
    break;

  case 168: /* PredicateFormula: _LPAREN _KW_or PredicateFormula ListPredicateFormula _RPAREN  */
#line 680 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new OrPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 2872 "Parser.C"
    break;

  case 169: /* PredicateFormula: _LPAREN _KW_and PredicateFormula ListPredicateFormula _RPAREN  */
#line 681 "epddl.y"
                                                                  { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new AndPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 2878 "Parser.C"
    break;

  case 170: /* PredicateFormula: _LPAREN _KW_not PredicateFormula _RPAREN  */
#line 682 "epddl.y"
                                             { (yyval.predicateformula_) = new NotPredFormula((yyvsp[-1].predicateformula_)); }
#line 2884 "Parser.C"
    break;

  case 171: /* PredicateFormula: _LPAREN PredicateName ListName _RPAREN  */
#line 683 "epddl.y"
                                           { std::reverse((yyvsp[-1].listname_)->begin(),(yyvsp[-1].listname_)->end()) ;(yyval.predicateformula_) = new LitPredFormula((yyvsp[-2].predicatename_), (yyvsp[-1].listname_)); }
#line 2890 "Parser.C"
    break;

  case 172: /* ListPredicateFormula: PredicateFormula  */
#line 685 "epddl.y"
                                        { (yyval.listpredicateformula_) = new ListPredicateFormula(); (yyval.listpredicateformula_)->push_back((yyvsp[0].predicateformula_)); }
#line 2896 "Parser.C"
    break;

  case 173: /* ListPredicateFormula: PredicateFormula ListPredicateFormula  */
#line 686 "epddl.y"
                                          { (yyvsp[0].listpredicateformula_)->push_back((yyvsp[-1].predicateformula_)); (yyval.listpredicateformula_) = (yyvsp[0].listpredicateformula_); }
#line 2902 "Parser.C"
    break;

  case 174: /* BasicTypedIdentList: ListName  */
#line 688 "epddl.y"
                               { std::reverse((yyvsp[0].listname_)->begin(),(yyvsp[0].listname_)->end()) ;(yyval.basictypedidentlist_) = new IdList((yyvsp[0].listname_)); }
#line 2908 "Parser.C"
    break;

  case 175: /* BasicTypedIdentList: Name ListName _MINUS BasicType BasicTypedIdentList  */
#line 689 "epddl.y"
                                                       { std::reverse((yyvsp[-3].listname_)->begin(),(yyvsp[-3].listname_)->end()) ;(yyval.basictypedidentlist_) = new TypedIdList((yyvsp[-4]._name), (yyvsp[-3].listname_), (yyvsp[-1].basictype_), (yyvsp[0].basictypedidentlist_)); }
#line 2914 "Parser.C"
    break;

  case 176: /* BasicTypedVariableList: ListVariable  */
#line 691 "epddl.y"
                                      { std::reverse((yyvsp[0].listvariable_)->begin(),(yyvsp[0].listvariable_)->end()) ;(yyval.basictypedvariablelist_) = new BasicVarList((yyvsp[0].listvariable_)); }
#line 2920 "Parser.C"
    break;

  case 177: /* BasicTypedVariableList: Variable ListVariable _MINUS BasicType BasicTypedVariableList  */
#line 692 "epddl.y"
                                                                  { std::reverse((yyvsp[-3].listvariable_)->begin(),(yyvsp[-3].listvariable_)->end()) ;(yyval.basictypedvariablelist_) = new BasicTypedVarList((yyvsp[-4]._variable), (yyvsp[-3].listvariable_), (yyvsp[-1].basictype_), (yyvsp[0].basictypedvariablelist_)); }
#line 2926 "Parser.C"
    break;

  case 178: /* TypedVariableList: ListVariable  */
#line 694 "epddl.y"
                                 { std::reverse((yyvsp[0].listvariable_)->begin(),(yyvsp[0].listvariable_)->end()) ;(yyval.typedvariablelist_) = new VarList((yyvsp[0].listvariable_)); }
#line 2932 "Parser.C"
    break;

  case 179: /* TypedVariableList: Variable ListVariable _MINUS Type TypedVariableList  */
#line 695 "epddl.y"
                                                        { std::reverse((yyvsp[-3].listvariable_)->begin(),(yyvsp[-3].listvariable_)->end()) ;(yyval.typedvariablelist_) = new TypedVarList((yyvsp[-4]._variable), (yyvsp[-3].listvariable_), (yyvsp[-1].type_), (yyvsp[0].typedvariablelist_)); }
#line 2938 "Parser.C"
    break;

  case 180: /* PredicateName: Name  */
#line 697 "epddl.y"
                     { (yyval.predicatename_) = new EPDDLPredicate((yyvsp[0]._name)); }
#line 2944 "Parser.C"
    break;

  case 181: /* ModalityAgent: AgentName  */
#line 699 "epddl.y"
                          { (yyval.modalityagent_) = new EPDDLModAgent((yyvsp[0]._agentname)); }
#line 2950 "Parser.C"
    break;

  case 182: /* ModalityAgent: Variable  */
#line 700 "epddl.y"
             { (yyval.modalityagent_) = new EPDDLModVarAgent((yyvsp[0]._variable)); }
#line 2956 "Parser.C"
    break;

  case 183: /* ModalityAgent: AnonVarAgent  */
#line 701 "epddl.y"
                 { (yyval.modalityagent_) = new EPDDLModAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 2962 "Parser.C"
    break;

  case 184: /* ModalityAgent: AllAgents  */
#line 702 "epddl.y"
              { (yyval.modalityagent_) = new EPDDLModAllAgents((yyvsp[0].allagents_)); }
#line 2968 "Parser.C"
    break;

  case 185: /* ListModalityAgent: ModalityAgent  */
#line 704 "epddl.y"
                                  { (yyval.listmodalityagent_) = new ListModalityAgent(); (yyval.listmodalityagent_)->push_back((yyvsp[0].modalityagent_)); }
#line 2974 "Parser.C"
    break;

  case 186: /* ListModalityAgent: ModalityAgent ListModalityAgent  */
#line 705 "epddl.y"
                                    { (yyvsp[0].listmodalityagent_)->push_back((yyvsp[-1].modalityagent_)); (yyval.listmodalityagent_) = (yyvsp[0].listmodalityagent_); }
#line 2980 "Parser.C"
    break;

  case 187: /* ModalityAgentGroup: ModalityAgent ListModalityAgent  */
#line 707 "epddl.y"
                                                     { std::reverse((yyvsp[0].listmodalityagent_)->begin(),(yyvsp[0].listmodalityagent_)->end()) ;(yyval.modalityagentgroup_) = new EPDDLModAgList((yyvsp[-1].modalityagent_), (yyvsp[0].listmodalityagent_)); }
#line 2986 "Parser.C"
    break;

  case 188: /* AgentGroupName: AgentName  */
#line 709 "epddl.y"
                           { (yyval.agentgroupname_) = new EPDDLAgentGroup((yyvsp[0]._agentname)); }
#line 2992 "Parser.C"
    break;

  case 189: /* AgentGroupName: AllAgents  */
#line 710 "epddl.y"
              { (yyval.agentgroupname_) = new EPDDLAllAgentsGroup((yyvsp[0].allagents_)); }
#line 2998 "Parser.C"
    break;

  case 190: /* ObservingAgentGroup: AgentName  */
#line 712 "epddl.y"
                                { (yyval.observingagentgroup_) = new EPDDLObsAgentGroup((yyvsp[0]._agentname)); }
#line 3004 "Parser.C"
    break;

  case 191: /* ListObservingAgentGroup: ObservingAgentGroup  */
#line 714 "epddl.y"
                                              { (yyval.listobservingagentgroup_) = new ListObservingAgentGroup(); (yyval.listobservingagentgroup_)->push_back((yyvsp[0].observingagentgroup_)); }
#line 3010 "Parser.C"
    break;

  case 192: /* ListObservingAgentGroup: ObservingAgentGroup ListObservingAgentGroup  */
#line 715 "epddl.y"
                                                { (yyvsp[0].listobservingagentgroup_)->push_back((yyvsp[-1].observingagentgroup_)); (yyval.listobservingagentgroup_) = (yyvsp[0].listobservingagentgroup_); }
#line 3016 "Parser.C"
    break;

  case 193: /* ObservingAgent: AgentName  */
#line 717 "epddl.y"
                           { (yyval.observingagent_) = new EPDDLObsAgent((yyvsp[0]._agentname)); }
#line 3022 "Parser.C"
    break;

  case 194: /* ObservingAgent: Variable  */
#line 718 "epddl.y"
             { (yyval.observingagent_) = new EPDDLObsVarAgent((yyvsp[0]._variable)); }
#line 3028 "Parser.C"
    break;

  case 195: /* ObservingAgent: AnonVarAgent  */
#line 719 "epddl.y"
                 { (yyval.observingagent_) = new EPDDLObsAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 3034 "Parser.C"
    break;

  case 196: /* AgentList: AgentName  */
#line 721 "epddl.y"
                      { (yyval.agentlist_) = new EPDDLSingleAgentList((yyvsp[0]._agentname)); }
#line 3040 "Parser.C"
    break;

  case 197: /* AgentList: _LBRACK AgentName ListAgentName _RBRACK  */
#line 722 "epddl.y"
                                            { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentlist_) = new EPDDLAgentNameList((yyvsp[-2]._agentname), (yyvsp[-1].listagentname_)); }
#line 3046 "Parser.C"
    break;

  case 198: /* AgentList: AllAgents  */
#line 723 "epddl.y"
              { (yyval.agentlist_) = new EPDDLAllAgentsList((yyvsp[0].allagents_)); }
#line 3052 "Parser.C"
    break;

  case 199: /* AllAgents: _KW_All  */
#line 725 "epddl.y"
                    { (yyval.allagents_) = new EPDDLAllAgents(); }
#line 3058 "Parser.C"
    break;

  case 200: /* AnonVarAgent: _SYMB_37  */
#line 727 "epddl.y"
                        { (yyval.anonvaragent_) = new EPDDLAnonVarAgent(); }
#line 3064 "Parser.C"
    break;

  case 201: /* Parameter: BasicParameter  */
#line 729 "epddl.y"
                           { (yyval.parameter_) = new EPDDLBasicParam((yyvsp[0].basicparameter_)); }
#line 3070 "Parser.C"
    break;

  case 202: /* Parameter: _LBRACK ListFormula _RBRACK  */
#line 730 "epddl.y"
                                { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.parameter_) = new EPDDLListParam((yyvsp[-1].listformula_)); }
#line 3076 "Parser.C"
    break;

  case 203: /* ListParameter: %empty  */
#line 732 "epddl.y"
                            { (yyval.listparameter_) = new ListParameter(); }
#line 3082 "Parser.C"
    break;

  case 204: /* ListParameter: ListParameter Parameter  */
#line 733 "epddl.y"
                            { (yyvsp[-1].listparameter_)->push_back((yyvsp[0].parameter_)); (yyval.listparameter_) = (yyvsp[-1].listparameter_); }
#line 3088 "Parser.C"
    break;

  case 205: /* BasicParameter: Term  */
#line 735 "epddl.y"
                      { (yyval.basicparameter_) = new EPDDLTermParam((yyvsp[0].term_)); }
#line 3094 "Parser.C"
    break;

  case 206: /* BasicParameter: Formula  */
#line 736 "epddl.y"
            { (yyval.basicparameter_) = new EPDDLFormulaParam((yyvsp[0].formula_)); }
#line 3100 "Parser.C"
    break;

  case 207: /* BasicParameter: TrivialDef  */
#line 737 "epddl.y"
               { (yyval.basicparameter_) = new EPDDLTrivialParam((yyvsp[0].trivialdef_)); }
#line 3106 "Parser.C"
    break;

  case 208: /* Type: BasicType  */
#line 739 "epddl.y"
                 { (yyval.type_) = new EPDDLBasicType((yyvsp[0].basictype_)); }
#line 3112 "Parser.C"
    break;

  case 209: /* Type: CompoundType  */
#line 740 "epddl.y"
                 { (yyval.type_) = new EPDDLCompoundType((yyvsp[0].compoundtype_)); }
#line 3118 "Parser.C"
    break;

  case 210: /* BasicType: Name  */
#line 742 "epddl.y"
                 { (yyval.basictype_) = new EPDDLBasicTypeName((yyvsp[0]._name)); }
#line 3124 "Parser.C"
    break;

  case 211: /* BasicType: ReservedBasicType  */
#line 743 "epddl.y"
                      { (yyval.basictype_) = new EPDDLBasicResType((yyvsp[0].reservedbasictype_)); }
#line 3130 "Parser.C"
    break;

  case 212: /* CompoundType: _LBRACK ReservedFormulaType _RBRACK  */
#line 745 "epddl.y"
                                                   { (yyval.compoundtype_) = new EPDDLFormulaListType((yyvsp[-1].reservedformulatype_)); }
#line 3136 "Parser.C"
    break;

  case 213: /* ReservedBasicType: ReservedFormulaType  */
#line 747 "epddl.y"
                                        { (yyval.reservedbasictype_) = new ResFormulaType((yyvsp[0].reservedformulatype_)); }
#line 3142 "Parser.C"
    break;

  case 214: /* ReservedBasicType: _KW_agent  */
#line 748 "epddl.y"
              { (yyval.reservedbasictype_) = new ResAgentType(); }
#line 3148 "Parser.C"
    break;

  case 215: /* ReservedFormulaType: _KW_predicate  */
#line 750 "epddl.y"
                                    { (yyval.reservedformulatype_) = new PredicateType(); }
#line 3154 "Parser.C"
    break;

  case 216: /* ReservedFormulaType: _KW_literal  */
#line 751 "epddl.y"
                { (yyval.reservedformulatype_) = new LiteralType(); }
#line 3160 "Parser.C"
    break;

  case 217: /* ReservedFormulaType: _SYMB_38  */
#line 752 "epddl.y"
             { (yyval.reservedformulatype_) = new PredFormulaType(); }
#line 3166 "Parser.C"
    break;

  case 218: /* ReservedFormulaType: _KW_formula  */
#line 753 "epddl.y"
                { (yyval.reservedformulatype_) = new FormulaType(); }
#line 3172 "Parser.C"
    break;

  case 219: /* LibraryName: Name  */
#line 755 "epddl.y"
                   { (yyval.libraryname_) = new EPDDLLibraryName((yyvsp[0]._name)); }
#line 3178 "Parser.C"
    break;

  case 220: /* ListLibraryName: LibraryName  */
#line 757 "epddl.y"
                              { (yyval.listlibraryname_) = new ListLibraryName(); (yyval.listlibraryname_)->push_back((yyvsp[0].libraryname_)); }
#line 3184 "Parser.C"
    break;

  case 221: /* ListLibraryName: LibraryName ListLibraryName  */
#line 758 "epddl.y"
                                { (yyvsp[0].listlibraryname_)->push_back((yyvsp[-1].libraryname_)); (yyval.listlibraryname_) = (yyvsp[0].listlibraryname_); }
#line 3190 "Parser.C"
    break;

  case 222: /* ActionTypeName: ReservedActionTypeName  */
#line 760 "epddl.y"
                                        { (yyval.actiontypename_) = new EPDDLResActTypeName((yyvsp[0].reservedactiontypename_)); }
#line 3196 "Parser.C"
    break;

  case 223: /* ActionTypeName: Name  */
#line 761 "epddl.y"
         { (yyval.actiontypename_) = new EPDDLActTypeName((yyvsp[0]._name)); }
#line 3202 "Parser.C"
    break;

  case 224: /* ReservedActionTypeName: _KW_ontic  */
#line 763 "epddl.y"
                                   { (yyval.reservedactiontypename_) = new OntActTypeName(); }
#line 3208 "Parser.C"
    break;

  case 225: /* ReservedActionTypeName: _KW_sensing  */
#line 764 "epddl.y"
                { (yyval.reservedactiontypename_) = new SenActTypeName(); }
#line 3214 "Parser.C"
    break;

  case 226: /* ReservedActionTypeName: _KW_announcement  */
#line 765 "epddl.y"
                     { (yyval.reservedactiontypename_) = new AnnActTypeName(); }
#line 3220 "Parser.C"
    break;

  case 227: /* EventName: ReservedEventName  */
#line 767 "epddl.y"
                              { (yyval.eventname_) = new EPDDLResEventName((yyvsp[0].reservedeventname_)); }
#line 3226 "Parser.C"
    break;

  case 228: /* EventName: Name  */
#line 768 "epddl.y"
         { (yyval.eventname_) = new EPDDLEventName((yyvsp[0]._name)); }
#line 3232 "Parser.C"
    break;

  case 229: /* ListEventName: EventName  */
#line 770 "epddl.y"
                          { (yyval.listeventname_) = new ListEventName(); (yyval.listeventname_)->push_back((yyvsp[0].eventname_)); }
#line 3238 "Parser.C"
    break;

  case 230: /* ListEventName: EventName ListEventName  */
#line 771 "epddl.y"
                            { (yyvsp[0].listeventname_)->push_back((yyvsp[-1].eventname_)); (yyval.listeventname_) = (yyvsp[0].listeventname_); }
#line 3244 "Parser.C"
    break;

  case 231: /* ReservedEventName: _SYMB_39  */
#line 773 "epddl.y"
                             { (yyval.reservedeventname_) = new IdleEvent(); }
#line 3250 "Parser.C"
    break;

  case 232: /* ActionName: Name  */
#line 775 "epddl.y"
                  { (yyval.actionname_) = new EPDDLActionName((yyvsp[0]._name)); }
#line 3256 "Parser.C"
    break;

  case 233: /* ModelName: Name  */
#line 777 "epddl.y"
                 { (yyval.modelname_) = new EPDDLModelName((yyvsp[0]._name)); }
#line 3262 "Parser.C"
    break;

  case 234: /* WorldName: Name  */
#line 779 "epddl.y"
                 { (yyval.worldname_) = new EPDDLWorldName((yyvsp[0]._name)); }
#line 3268 "Parser.C"
    break;

  case 235: /* ListWorldName: WorldName  */
#line 781 "epddl.y"
                          { (yyval.listworldname_) = new ListWorldName(); (yyval.listworldname_)->push_back((yyvsp[0].worldname_)); }
#line 3274 "Parser.C"
    break;

  case 236: /* ListWorldName: WorldName ListWorldName  */
#line 782 "epddl.y"
                            { (yyvsp[0].listworldname_)->push_back((yyvsp[-1].worldname_)); (yyval.listworldname_) = (yyvsp[0].listworldname_); }
#line 3280 "Parser.C"
    break;

  case 237: /* RequireKey: _SYMB_40  */
#line 784 "epddl.y"
                      { (yyval.requirekey_) = new EPDDLReqDel(); }
#line 3286 "Parser.C"
    break;

  case 238: /* RequireKey: _SYMB_41  */
#line 785 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqTyping(); }
#line 3292 "Parser.C"
    break;

  case 239: /* RequireKey: _SYMB_42  */
#line 786 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqEquality(); }
#line 3298 "Parser.C"
    break;

  case 240: /* RequireKey: _SYMB_43  */
#line 787 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqParamList(); }
#line 3304 "Parser.C"
    break;

  case 241: /* RequireKey: _SYMB_44  */
#line 788 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqNegPre(); }
#line 3310 "Parser.C"
    break;

  case 242: /* RequireKey: _SYMB_45  */
#line 789 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqDisPre(); }
#line 3316 "Parser.C"
    break;

  case 243: /* RequireKey: _SYMB_46  */
#line 790 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqExiPre(); }
#line 3322 "Parser.C"
    break;

  case 244: /* RequireKey: _SYMB_47  */
#line 791 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqUniPre(); }
#line 3328 "Parser.C"
    break;

  case 245: /* RequireKey: _SYMB_48  */
#line 792 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPre(); }
#line 3334 "Parser.C"
    break;

  case 246: /* RequireKey: _SYMB_49  */
#line 793 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPost(); }
#line 3340 "Parser.C"
    break;

  case 247: /* RequireKey: _SYMB_50  */
#line 794 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOnticChange(); }
#line 3346 "Parser.C"
    break;

  case 248: /* RequireKey: _SYMB_51  */
#line 795 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqCK(); }
#line 3352 "Parser.C"
    break;

  case 249: /* RequireKey: _SYMB_52  */
#line 796 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqDynCK(); }
#line 3358 "Parser.C"
    break;

  case 250: /* RequireKey: _SYMB_53  */
#line 797 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqMAStar(); }
#line 3364 "Parser.C"
    break;

  case 251: /* RequireKey: _SYMB_54  */
#line 798 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOntic(); }
#line 3370 "Parser.C"
    break;

  case 252: /* RequireKey: _SYMB_55  */
#line 799 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqSensing(); }
#line 3376 "Parser.C"
    break;

  case 253: /* RequireKey: _SYMB_56  */
#line 800 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqAnnouncement(); }
#line 3382 "Parser.C"
    break;

  case 254: /* RequireKey: _SYMB_57  */
#line 801 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqFTheory(); }
#line 3388 "Parser.C"
    break;

  case 255: /* RequireKey: _LPAREN _SYMB_58 _INTEGER_ _RPAREN  */
#line 802 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPreDepth((yyvsp[-1]._int)); }
#line 3394 "Parser.C"
    break;

  case 256: /* RequireKey: _LPAREN _SYMB_59 _INTEGER_ _RPAREN  */
#line 803 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPostDepth((yyvsp[-1]._int)); }
#line 3400 "Parser.C"
    break;

  case 257: /* RequireKey: _LPAREN _SYMB_60 _INTEGER_ _RPAREN  */
#line 804 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxDepth((yyvsp[-1]._int)); }
#line 3406 "Parser.C"
    break;

  case 258: /* ListRequireKey: RequireKey  */
#line 806 "epddl.y"
                            { (yyval.listrequirekey_) = new ListRequireKey(); (yyval.listrequirekey_)->push_back((yyvsp[0].requirekey_)); }
#line 3412 "Parser.C"
    break;

  case 259: /* ListRequireKey: RequireKey ListRequireKey  */
#line 807 "epddl.y"
                              { (yyvsp[0].listrequirekey_)->push_back((yyvsp[-1].requirekey_)); (yyval.listrequirekey_) = (yyvsp[0].listrequirekey_); }
#line 3418 "Parser.C"
    break;

  case 260: /* TrivialDef: _LPAREN _RPAREN  */
#line 809 "epddl.y"
                             { (yyval.trivialdef_) = new EPDDLTrivialDef(); }
#line 3424 "Parser.C"
    break;

  case 261: /* ListName: %empty  */
#line 811 "epddl.y"
                       { (yyval.listname_) = new ListName(); }
#line 3430 "Parser.C"
    break;

  case 262: /* ListName: Name ListName  */
#line 812 "epddl.y"
                  { (yyvsp[0].listname_)->push_back((yyvsp[-1]._name)); (yyval.listname_) = (yyvsp[0].listname_); }
#line 3436 "Parser.C"
    break;

  case 263: /* ListAgentName: AgentName  */
#line 814 "epddl.y"
                          { (yyval.listagentname_) = new ListAgentName(); (yyval.listagentname_)->push_back((yyvsp[0]._agentname)); }
#line 3442 "Parser.C"
    break;

  case 264: /* ListAgentName: AgentName ListAgentName  */
#line 815 "epddl.y"
                            { (yyvsp[0].listagentname_)->push_back((yyvsp[-1]._agentname)); (yyval.listagentname_) = (yyvsp[0].listagentname_); }
#line 3448 "Parser.C"
    break;

  case 265: /* ListVariable: %empty  */
#line 817 "epddl.y"
                           { (yyval.listvariable_) = new ListVariable(); }
#line 3454 "Parser.C"
    break;

  case 266: /* ListVariable: Variable ListVariable  */
#line 818 "epddl.y"
                          { (yyvsp[0].listvariable_)->push_back((yyvsp[-1]._variable)); (yyval.listvariable_) = (yyvsp[0].listvariable_); }
#line 3460 "Parser.C"
    break;

  case 267: /* Name: T_Name  */
#line 820 "epddl.y"
              { (yyval._name) = new Name((yyvsp[0]._string), (yyloc).first_line); }
#line 3466 "Parser.C"
    break;

  case 268: /* AgentName: T_AgentName  */
#line 822 "epddl.y"
                        { (yyval._agentname) = new AgentName((yyvsp[0]._string), (yyloc).first_line); }
#line 3472 "Parser.C"
    break;

  case 269: /* ModalityName: T_ModalityName  */
#line 824 "epddl.y"
                              { (yyval._modalityname) = new ModalityName((yyvsp[0]._string), (yyloc).first_line); }
#line 3478 "Parser.C"
    break;

  case 270: /* Variable: T_Variable  */
#line 826 "epddl.y"
                      { (yyval._variable) = new Variable((yyvsp[0]._string), (yyloc).first_line); }
#line 3484 "Parser.C"
    break;


#line 3488 "Parser.C"

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

#line 829 "epddl.y"



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



