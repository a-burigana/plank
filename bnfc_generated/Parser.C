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
  YYSYMBOL__SYMB_52 = 13,                  /* _SYMB_52  */
  YYSYMBOL__SYMB_42 = 14,                  /* _SYMB_42  */
  YYSYMBOL__SYMB_17 = 15,                  /* _SYMB_17  */
  YYSYMBOL__SYMB_20 = 16,                  /* _SYMB_20  */
  YYSYMBOL__SYMB_53 = 17,                  /* _SYMB_53  */
  YYSYMBOL__SYMB_44 = 18,                  /* _SYMB_44  */
  YYSYMBOL__SYMB_18 = 19,                  /* _SYMB_18  */
  YYSYMBOL__SYMB_15 = 20,                  /* _SYMB_15  */
  YYSYMBOL__SYMB_46 = 21,                  /* _SYMB_46  */
  YYSYMBOL__SYMB_14 = 22,                  /* _SYMB_14  */
  YYSYMBOL__SYMB_34 = 23,                  /* _SYMB_34  */
  YYSYMBOL__SYMB_27 = 24,                  /* _SYMB_27  */
  YYSYMBOL__SYMB_54 = 25,                  /* _SYMB_54  */
  YYSYMBOL__SYMB_57 = 26,                  /* _SYMB_57  */
  YYSYMBOL__SYMB_58 = 27,                  /* _SYMB_58  */
  YYSYMBOL__SYMB_55 = 28,                  /* _SYMB_55  */
  YYSYMBOL__SYMB_56 = 29,                  /* _SYMB_56  */
  YYSYMBOL__SYMB_61 = 30,                  /* _SYMB_61  */
  YYSYMBOL__SYMB_60 = 31,                  /* _SYMB_60  */
  YYSYMBOL__SYMB_59 = 32,                  /* _SYMB_59  */
  YYSYMBOL__SYMB_50 = 33,                  /* _SYMB_50  */
  YYSYMBOL__SYMB_49 = 34,                  /* _SYMB_49  */
  YYSYMBOL__SYMB_6 = 35,                   /* _SYMB_6  */
  YYSYMBOL__SYMB_31 = 36,                  /* _SYMB_31  */
  YYSYMBOL__SYMB_28 = 37,                  /* _SYMB_28  */
  YYSYMBOL__SYMB_25 = 38,                  /* _SYMB_25  */
  YYSYMBOL__SYMB_13 = 39,                  /* _SYMB_13  */
  YYSYMBOL__SYMB_7 = 40,                   /* _SYMB_7  */
  YYSYMBOL__SYMB_51 = 41,                  /* _SYMB_51  */
  YYSYMBOL__SYMB_45 = 42,                  /* _SYMB_45  */
  YYSYMBOL__SYMB_9 = 43,                   /* _SYMB_9  */
  YYSYMBOL__SYMB_19 = 44,                  /* _SYMB_19  */
  YYSYMBOL__SYMB_12 = 45,                  /* _SYMB_12  */
  YYSYMBOL__SYMB_5 = 46,                   /* _SYMB_5  */
  YYSYMBOL__SYMB_16 = 47,                  /* _SYMB_16  */
  YYSYMBOL__SYMB_3 = 48,                   /* _SYMB_3  */
  YYSYMBOL__SYMB_26 = 49,                  /* _SYMB_26  */
  YYSYMBOL__SYMB_4 = 50,                   /* _SYMB_4  */
  YYSYMBOL__SYMB_43 = 51,                  /* _SYMB_43  */
  YYSYMBOL__SYMB_47 = 52,                  /* _SYMB_47  */
  YYSYMBOL__SYMB_48 = 53,                  /* _SYMB_48  */
  YYSYMBOL__SYMB_33 = 54,                  /* _SYMB_33  */
  YYSYMBOL__SYMB_10 = 55,                  /* _SYMB_10  */
  YYSYMBOL__SYMB_32 = 56,                  /* _SYMB_32  */
  YYSYMBOL__LT = 57,                       /* _LT  */
  YYSYMBOL__EQ = 58,                       /* _EQ  */
  YYSYMBOL__GT = 59,                       /* _GT  */
  YYSYMBOL__SYMB_39 = 60,                  /* _SYMB_39  */
  YYSYMBOL__KW_All = 61,                   /* _KW_All  */
  YYSYMBOL__LBRACK = 62,                   /* _LBRACK  */
  YYSYMBOL__RBRACK = 63,                   /* _RBRACK  */
  YYSYMBOL__KW_agent = 64,                 /* _KW_agent  */
  YYSYMBOL__KW_and = 65,                   /* _KW_and  */
  YYSYMBOL__KW_as = 66,                    /* _KW_as  */
  YYSYMBOL__KW_define = 67,                /* _KW_define  */
  YYSYMBOL__KW_domain = 68,                /* _KW_domain  */
  YYSYMBOL__KW_exists = 69,                /* _KW_exists  */
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
  YYSYMBOL_StaticPredListDef = 149,        /* StaticPredListDef  */
  YYSYMBOL_StaticPredDef = 150,            /* StaticPredDef  */
  YYSYMBOL_ListStaticPredDef = 151,        /* ListStaticPredDef  */
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
  YYSYMBOL_TypedAgentList = 200,           /* TypedAgentList  */
  YYSYMBOL_TypedVariableList = 201,        /* TypedVariableList  */
  YYSYMBOL_PredicateName = 202,            /* PredicateName  */
  YYSYMBOL_ModalityAgent = 203,            /* ModalityAgent  */
  YYSYMBOL_ListModalityAgent = 204,        /* ListModalityAgent  */
  YYSYMBOL_ModalityAgentGroup = 205,       /* ModalityAgentGroup  */
  YYSYMBOL_AgentGroupName = 206,           /* AgentGroupName  */
  YYSYMBOL_ObservingAgentGroup = 207,      /* ObservingAgentGroup  */
  YYSYMBOL_ListObservingAgentGroup = 208,  /* ListObservingAgentGroup  */
  YYSYMBOL_ObservingAgent = 209,           /* ObservingAgent  */
  YYSYMBOL_AgentGroup = 210,               /* AgentGroup  */
  YYSYMBOL_AllAgents = 211,                /* AllAgents  */
  YYSYMBOL_AnonVarAgent = 212,             /* AnonVarAgent  */
  YYSYMBOL_Parameter = 213,                /* Parameter  */
  YYSYMBOL_ListParameter = 214,            /* ListParameter  */
  YYSYMBOL_ParameterValue = 215,           /* ParameterValue  */
  YYSYMBOL_PostParameterValue = 216,       /* PostParameterValue  */
  YYSYMBOL_ListPostParameterValue = 217,   /* ListPostParameterValue  */
  YYSYMBOL_Type = 218,                     /* Type  */
  YYSYMBOL_ReservedType = 219,             /* ReservedType  */
  YYSYMBOL_DomainName = 220,               /* DomainName  */
  YYSYMBOL_LibraryName = 221,              /* LibraryName  */
  YYSYMBOL_ListLibraryName = 222,          /* ListLibraryName  */
  YYSYMBOL_ProblemName = 223,              /* ProblemName  */
  YYSYMBOL_ActionName = 224,               /* ActionName  */
  YYSYMBOL_ActionTypeName = 225,           /* ActionTypeName  */
  YYSYMBOL_EventName = 226,                /* EventName  */
  YYSYMBOL_ListEventName = 227,            /* ListEventName  */
  YYSYMBOL_ModelName = 228,                /* ModelName  */
  YYSYMBOL_WorldName = 229,                /* WorldName  */
  YYSYMBOL_ListWorldName = 230,            /* ListWorldName  */
  YYSYMBOL_RequireKey = 231,               /* RequireKey  */
  YYSYMBOL_ListRequireKey = 232,           /* ListRequireKey  */
  YYSYMBOL_TrivialDef = 233,               /* TrivialDef  */
  YYSYMBOL_ListName = 234,                 /* ListName  */
  YYSYMBOL_ListAgentName = 235,            /* ListAgentName  */
  YYSYMBOL_ListModalityName = 236,         /* ListModalityName  */
  YYSYMBOL_ListVariable = 237,             /* ListVariable  */
  YYSYMBOL_Name = 238,                     /* Name  */
  YYSYMBOL_AgentName = 239,                /* AgentName  */
  YYSYMBOL_ModalityName = 240,             /* ModalityName  */
  YYSYMBOL_Variable = 241                  /* Variable  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 204 "epddl.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, epddl_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 392 "Parser.C"


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
#define YYLAST   680

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  148
/* YYNRULES -- Number of rules.  */
#define YYNRULES  298
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  581

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
       0,   460,   460,   461,   462,   464,   466,   467,   468,   469,
     470,   471,   472,   474,   475,   477,   479,   481,   483,   485,
     487,   488,   490,   492,   494,   496,   498,   499,   501,   503,
     505,   506,   508,   509,   510,   512,   513,   515,   517,   518,
     519,   520,   521,   523,   524,   526,   528,   530,   531,   533,
     535,   537,   539,   541,   542,   544,   545,   547,   548,   550,
     551,   553,   555,   556,   558,   560,   562,   564,   565,   567,
     568,   570,   571,   572,   574,   575,   577,   578,   580,   581,
     583,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   596,   597,   599,   601,   603,   605,   607,   608,   610,
     612,   614,   616,   617,   619,   621,   622,   624,   625,   626,
     627,   628,   629,   631,   632,   634,   635,   637,   638,   640,
     641,   643,   645,   647,   649,   651,   653,   654,   656,   657,
     659,   660,   662,   663,   665,   667,   668,   670,   672,   673,
     675,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   687,   688,   689,   691,   692,   694,   696,   698,   699,
     701,   702,   704,   705,   707,   708,   710,   711,   713,   714,
     716,   717,   719,   720,   722,   723,   725,   726,   728,   729,
     731,   733,   734,   736,   737,   739,   740,   742,   743,   745,
     746,   748,   749,   751,   752,   753,   754,   755,   757,   758,
     760,   761,   763,   764,   766,   767,   769,   770,   772,   773,
     775,   777,   778,   779,   780,   782,   783,   785,   787,   788,
     790,   792,   793,   795,   796,   797,   798,   800,   801,   803,
     805,   807,   809,   810,   812,   813,   814,   816,   817,   819,
     820,   822,   823,   825,   826,   827,   828,   829,   830,   832,
     834,   836,   837,   839,   841,   843,   845,   847,   848,   850,
     852,   854,   855,   857,   858,   859,   860,   861,   862,   863,
     864,   865,   866,   867,   868,   869,   870,   871,   872,   873,
     874,   875,   876,   877,   879,   880,   882,   884,   885,   887,
     888,   890,   891,   893,   894,   896,   898,   900,   902
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
  "_SYMB_22", "_SYMB_21", "_SYMB_52", "_SYMB_42", "_SYMB_17", "_SYMB_20",
  "_SYMB_53", "_SYMB_44", "_SYMB_18", "_SYMB_15", "_SYMB_46", "_SYMB_14",
  "_SYMB_34", "_SYMB_27", "_SYMB_54", "_SYMB_57", "_SYMB_58", "_SYMB_55",
  "_SYMB_56", "_SYMB_61", "_SYMB_60", "_SYMB_59", "_SYMB_50", "_SYMB_49",
  "_SYMB_6", "_SYMB_31", "_SYMB_28", "_SYMB_25", "_SYMB_13", "_SYMB_7",
  "_SYMB_51", "_SYMB_45", "_SYMB_9", "_SYMB_19", "_SYMB_12", "_SYMB_5",
  "_SYMB_16", "_SYMB_3", "_SYMB_26", "_SYMB_4", "_SYMB_43", "_SYMB_47",
  "_SYMB_48", "_SYMB_33", "_SYMB_10", "_SYMB_32", "_LT", "_EQ", "_GT",
  "_SYMB_39", "_KW_All", "_LBRACK", "_RBRACK", "_KW_agent", "_KW_and",
  "_KW_as", "_KW_define", "_KW_domain", "_KW_exists", "_KW_false",
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
  "ListAgentGroupDef", "ObjectNamesDef", "StaticPredListDef",
  "StaticPredDef", "ListStaticPredDef", "InitDef", "InitialStateDescr",
  "FTheoryFormula", "ListFTheoryFormula", "KPredicateFormula",
  "KWPredicateFormula", "NotKWPredicateFormula", "InitialModelDef",
  "ModelWorldsDef", "ModelRelDef", "ModelValDef", "ModelDesDef",
  "ModelRelations", "ModelValuation", "WorldRelation", "ListWorldRelation",
  "WorldNamePair", "ListWorldNamePair", "WorldValuation",
  "ListWorldValuation", "GoalDef", "Formula", "ListFormula",
  "AtomicFormula", "AtomicEqFormula", "FormulaOrEmpty", "MetaTerm",
  "ListMetaTerm", "Term", "ListTerm", "GroundTerm", "ListGroundTerm",
  "Modality", "SingleModality", "GroupModality", "ModalityLabel",
  "KnowsWhether", "Literal", "ListLiteral", "ConditionFormula",
  "Condition", "ListCondition", "AtomicCondition", "PredicateFormula",
  "ListPredicateFormula", "GenericName", "ListGenericName",
  "TypedIdentList", "TypedAgentList", "TypedVariableList", "PredicateName",
  "ModalityAgent", "ListModalityAgent", "ModalityAgentGroup",
  "AgentGroupName", "ObservingAgentGroup", "ListObservingAgentGroup",
  "ObservingAgent", "AgentGroup", "AllAgents", "AnonVarAgent", "Parameter",
  "ListParameter", "ParameterValue", "PostParameterValue",
  "ListPostParameterValue", "Type", "ReservedType", "DomainName",
  "LibraryName", "ListLibraryName", "ProblemName", "ActionName",
  "ActionTypeName", "EventName", "ListEventName", "ModelName", "WorldName",
  "ListWorldName", "RequireKey", "ListRequireKey", "TrivialDef",
  "ListName", "ListAgentName", "ListModalityName", "ListVariable", "Name",
  "AgentName", "ModalityName", "Variable", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-446)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      37,   -22,    80,  -446,  -446,  -446,   113,  -446,   110,     1,
       1,     1,  -446,   142,  -446,   202,  -446,   213,  -446,  -446,
    -446,  -446,    47,   152,   255,   260,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,   263,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,   579,  -446,  -446,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,  -446,     1,     1,    77,   121,
     230,   571,     1,     1,     1,  -446,   121,     1,    25,   162,
       1,     1,   234,   184,  -446,     1,   241,  -446,   272,    77,
    -446,   121,   274,  -446,     1,   230,   283,   351,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,  -446,   571,   297,   300,  -446,
       1,   264,  -446,   266,  -446,   262,   315,  -446,   121,   317,
     487,    77,    77,  -446,  -446,   339,  -446,  -446,    25,  -446,
    -446,   123,   303,   353,   168,  -446,  -446,   310,  -446,   364,
       1,   234,   366,   370,   321,  -446,  -446,  -446,  -446,  -446,
    -446,   286,  -446,  -446,  -446,   291,   301,   316,  -446,  -446,
    -446,   373,     1,   392,   379,   399,   367,   329,  -446,  -446,
    -446,   402,   121,  -446,   205,    25,   407,   413,    25,    25,
      25,  -446,   414,  -446,   419,   223,  -446,   223,  -446,  -446,
      61,     1,   421,   421,   421,   421,   423,  -446,  -446,   369,
    -446,  -446,   425,   371,  -446,  -446,  -446,  -446,   286,   431,
     427,   432,  -446,   286,   433,   434,   438,   308,  -446,   286,
     440,   428,   286,    26,   406,   121,   308,  -446,   205,  -446,
    -446,  -446,  -446,    25,   286,   286,    25,   449,    25,  -446,
      72,  -446,  -446,   232,   396,  -446,  -446,  -446,  -446,   271,
     393,   452,   355,   421,   421,   453,   421,  -446,    88,   177,
       1,   455,   408,   101,   456,   268,  -446,  -446,  -446,   459,
     415,  -446,   458,   286,  -446,  -446,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,     1,  -446,  -446,   461,   121,   463,   424,
     465,   335,  -446,  -446,  -446,   469,   470,   121,   121,   472,
      25,   477,   478,   479,   480,  -446,   481,  -446,  -446,  -446,
    -446,  -446,   223,  -446,  -446,  -446,  -446,  -446,   421,   483,
     484,  -446,   485,  -446,  -446,    63,   228,  -446,  -446,  -446,
     421,  -446,     1,   488,  -446,    59,  -446,   492,  -446,  -446,
     493,   486,  -446,  -446,  -446,  -446,  -446,   205,   494,   499,
    -446,     1,    26,   435,   308,  -446,  -446,  -446,   500,     1,
     463,  -446,   505,   498,  -446,  -446,    84,  -446,   510,  -446,
    -446,  -446,  -446,   429,  -446,  -446,  -446,  -446,    25,    25,
    -446,  -446,  -446,  -446,  -446,  -446,  -446,    24,   179,   513,
     516,   519,   464,   121,  -446,  -446,  -446,   121,  -446,   527,
    -446,  -446,   -11,  -446,    27,  -446,   528,  -446,  -446,   531,
     535,   205,   131,   494,   -16,   537,   114,  -446,  -446,   532,
     543,   286,  -446,  -446,  -446,    59,  -446,   546,  -446,  -446,
     547,   550,   557,   559,   562,   141,  -446,   502,   564,   565,
     509,    77,   421,  -446,  -446,  -446,   421,   501,   121,    27,
     568,   575,   576,   514,     1,  -446,     1,  -446,   577,   494,
     578,  -446,  -446,  -446,   324,   276,   532,  -446,  -446,  -446,
     350,   582,   -11,  -446,     1,  -446,   286,   -18,  -446,    30,
    -446,   -17,  -446,  -446,   588,  -446,  -446,   506,     1,     1,
    -446,  -446,  -446,  -446,   596,  -446,  -446,  -446,   286,  -446,
    -446,   223,   121,  -446,  -446,  -446,  -446,  -446,  -446,    27,
     583,   602,   603,     1,   604,   605,   607,  -446,    26,   611,
    -446,  -446,   613,    67,  -446,   614,   121,    51,     1,     1,
    -446,  -446,  -446,  -446,  -446,   616,     1,   620,   621,  -446,
    -446,   624,  -446,   166,   626,  -446,    25,   627,   548,   616,
     629,  -446,  -446,  -446,   437,  -446,  -446,  -446,   630,   632,
    -446,  -446,   633,  -446,  -446,  -446,   635,  -446,   158,  -446,
    -446,   286,   636,   637,   286,   183,   638,   468,   639,   616,
    -446
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     2,     3,     4,     0,     1,     0,     0,
       0,     0,   295,     0,   249,     0,   250,     0,   253,    13,
      43,    91,     0,     0,     0,     0,     5,    14,     6,     7,
       8,     9,    10,    11,    12,     0,    37,    38,    39,    40,
      44,    41,    42,     0,    80,    82,    83,    92,    81,    84,
      85,    86,    87,    88,    89,    90,     0,     0,   291,     0,
       0,     0,   287,     0,     0,    97,   289,     0,     0,     0,
       0,   287,     0,     0,   254,   251,     0,   297,     0,   291,
     296,   221,     0,   220,     0,    20,     0,     0,   274,   263,
     275,   265,   267,   276,   279,   280,   277,   278,   271,   270,
     272,   273,   266,   264,   268,   269,   284,     0,     0,   204,
     287,     0,   255,     0,   256,     0,     0,   206,   289,     0,
       0,   179,   179,   152,   151,     0,   149,   150,     0,   172,
     173,     0,     0,     0,   113,   105,   107,     0,   259,     0,
       0,   102,     0,     0,    27,   252,    15,    22,   292,   222,
      23,   293,   210,    21,    18,     0,     0,     0,   285,    16,
      17,   288,   287,     0,    48,     0,     0,     0,    95,    98,
      94,   290,   289,    93,     0,     0,     0,     0,     0,     0,
       0,   298,     0,   162,     0,     0,   178,     0,   140,   147,
       0,     0,     0,     0,     0,     0,     0,   170,   229,     0,
     104,   114,     0,     0,    99,   202,   103,   100,   293,     0,
       0,     0,   208,   293,     0,     0,     0,     0,   288,   293,
       0,     0,   293,     0,    68,     0,     0,   290,     0,   164,
     168,   169,   165,     0,   293,   293,     0,     0,     0,   153,
       0,   148,   230,     0,     0,   214,   213,   211,   212,     0,
       0,     0,     0,     0,     0,     0,     0,   112,     0,     0,
       0,     0,     0,     0,     0,     0,    26,   186,   187,     0,
       0,    19,   294,   293,   283,   282,   281,   243,   247,   245,
     248,   244,   246,   287,   242,   241,     0,     0,     0,     0,
       0,     0,   158,    66,   159,     0,     0,   289,   289,     0,
     154,     0,     0,     0,     0,   144,     0,   156,   163,   160,
     161,   175,   215,   217,   177,   174,   176,   106,   198,     0,
       0,   196,     0,   197,   171,     0,     0,   109,   110,   111,
       0,   108,   261,     0,   260,     0,   123,   132,   126,   127,
       0,     0,   101,   203,   200,   201,    25,     0,     0,     0,
     166,     0,     0,    31,     0,   294,   205,    46,     0,     0,
      53,    49,     0,     0,    65,   286,     0,    67,    74,    69,
      72,    70,    64,     0,   207,   157,   155,   143,     0,     0,
     141,   142,   216,   199,   195,   193,   194,     0,     0,     0,
       0,     0,     0,     0,   117,   262,   122,     0,   227,     0,
     219,   218,     0,   133,     0,   124,   138,   128,   129,     0,
       0,     0,     0,     0,     0,     0,     0,   232,    29,     0,
       0,   293,    47,   232,    54,     0,    50,    59,    55,    56,
       0,     0,     0,     0,     0,     0,    75,     0,     0,     0,
       0,     0,     0,   116,   118,   120,     0,     0,   289,     0,
     135,     0,     0,     0,     0,   139,     0,   121,     0,   189,
       0,   188,   191,   167,     0,     0,    35,    30,    24,   209,
       0,     0,     0,    60,     0,    45,   293,     0,   181,     0,
      73,     0,   145,   146,     0,   115,   180,     0,     0,     0,
     136,   130,   131,   183,     0,   192,   190,   185,     0,    28,
     233,     0,     0,   224,   226,   223,   225,    36,    52,     0,
      62,     0,     0,   257,     0,     0,     0,    77,     0,     0,
     119,   228,     0,     0,   125,     0,     0,     0,     0,     0,
      63,    57,    58,   258,    51,     0,     0,     0,     0,    96,
     134,     0,   184,     0,     0,    32,     0,     0,     0,    78,
       0,   182,    76,   137,     0,   238,   235,   234,     0,   239,
     236,    34,     0,    61,    79,    71,     0,   231,     0,   240,
      33,   293,     0,     0,   293,     0,     0,     0,     0,     0,
     237
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -446,  -446,  -446,  -446,  -446,  -446,   338,  -446,  -446,  -446,
     552,   363,   618,  -446,  -446,  -446,  -446,  -446,  -446,  -446,
     180,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,  -446,
    -446,   285,  -446,  -446,   220,  -446,   138,  -446,  -446,  -446,
    -446,  -446,  -446,   281,  -278,  -293,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,  -446,  -446,  -446,  -446,   511,  -446,  -446,
     -47,   517,   391,   395,   397,  -446,  -446,  -446,  -446,  -446,
    -446,  -446,  -446,   318,  -446,   207,  -446,   252,  -446,   -65,
    -195,  -407,  -446,  -338,  -446,  -446,  -216,  -446,   401,  -446,
    -446,  -446,  -446,   538,  -319,   139,  -446,  -446,  -189,   204,
     312,  -156,  -210,  -446,  -446,   -58,   368,  -201,   -61,    86,
     352,   482,   186,  -445,   -66,   164,  -398,  -124,  -221,  -446,
     245,  -446,  -446,   111,  -204,  -446,   606,   661,   597,  -446,
    -446,   323,   -60,   163,   489,  -355,  -307,  -446,   569,  -255,
      35,  -113,   598,  -122,    -9,   -50,  -111,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,    27,    22,    28,    29,    30,    31,    85,
      86,    32,    33,    34,   144,   210,   270,   353,   420,   466,
     467,     4,    40,    23,    41,   164,   221,   289,   363,   431,
     360,   361,   426,   427,   428,   510,   511,    42,   166,   224,
     296,   367,   368,   369,   549,   578,     5,    47,    24,    48,
      49,    50,   169,   115,    51,    52,   141,   142,    53,   133,
     134,   135,   389,   390,   391,    54,   203,   262,   341,   410,
     336,   405,   337,   338,   450,   451,   406,   407,    55,   182,
     301,   126,   127,   293,   308,   240,   228,   416,   229,   258,
     128,   129,   130,   185,   330,   479,   523,   266,   459,   460,
     268,   136,   319,   343,   263,   108,   116,   211,   183,   312,
     313,   244,   398,    81,    82,   502,   399,   245,   246,   500,
     464,   558,   559,   560,   283,   284,    13,    75,    76,    17,
      73,   111,   513,   514,   137,   332,   333,   106,   107,   294,
     109,   117,    78,   212,   152,   231,    79,   213
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    16,    18,   125,   113,   171,   339,   264,   199,    83,
     186,   186,   299,   139,   418,   149,   118,   370,   286,   310,
     267,   290,   298,   151,   309,   395,   478,   471,   387,   120,
     291,    83,   365,   302,   303,   517,   253,   254,   255,   256,
     371,     1,   347,   306,   198,     6,   322,    74,    16,   453,
     198,    25,    26,   110,   112,   114,   545,   527,    14,   227,
     516,   138,   110,   189,   365,   190,    16,   387,   172,   442,
     197,   477,    80,    12,   471,    12,   397,   307,    80,   205,
       7,   544,   121,   121,   196,   408,   326,   122,   122,   365,
     370,   272,    12,   323,   488,   123,   123,   318,   320,   453,
     318,   162,   440,   331,   518,   376,   342,   429,   383,   537,
     233,   124,   124,   236,   237,   238,   478,     8,    12,   462,
     198,   442,   172,   132,   546,   326,   192,   190,   192,   197,
     541,   411,   242,   522,   488,   247,   193,   247,   193,   194,
     195,   388,   195,   196,   452,   161,   397,    19,    80,   494,
     421,   355,    12,   162,    12,   432,    35,    36,   292,   413,
     191,    80,   318,    12,   181,   230,   131,    77,   300,   433,
     554,   304,   190,   300,   394,   297,   181,    80,     9,    12,
     538,   325,   138,   252,   373,   132,    10,   577,   192,   347,
      80,   197,    12,   247,    11,   458,   184,   218,   193,   247,
     463,   194,   195,    80,   350,    12,   181,    20,   285,   349,
      80,   400,   432,   345,    12,   393,   512,   285,    21,   230,
     469,   358,    12,   121,   132,   356,   433,   143,   122,   572,
     132,   230,   255,   181,    84,   300,   123,    83,   140,   326,
     121,   441,   550,   433,   504,   122,   146,   172,   118,   230,
     232,   334,   124,   123,   344,    80,   564,    12,   181,    43,
      44,   248,   247,   248,   197,   555,   167,   168,    56,   124,
      57,   243,    63,   249,   110,   515,   392,   147,   400,   150,
     504,   555,    64,   242,   198,   401,   484,   292,   154,   273,
     485,   311,   242,   198,    80,    58,    12,   181,    58,   423,
      59,   400,   159,    59,   232,   160,    60,   163,    61,   165,
      62,    61,    80,   438,   439,   181,   232,    80,    77,   248,
     170,    80,   173,   334,   181,   248,   347,   557,   498,   499,
     393,   242,   198,   348,   315,   487,   242,   198,   230,   120,
     365,   503,   112,   447,   188,   285,   349,   448,   400,   273,
     114,   350,   401,   350,   498,   508,   501,   400,   200,    12,
      80,    37,    45,   181,   198,    80,   202,   184,   181,   204,
     573,   207,   277,   576,   208,   401,   209,   503,   181,   217,
     278,   155,   156,   157,   214,   279,    38,    46,   248,   280,
     281,   282,   121,   174,   215,   334,   219,   122,   172,    12,
     175,   220,   230,   222,   176,   123,   177,   230,   226,   216,
     178,   234,   223,   179,   180,   505,   225,   235,   261,   239,
     192,   124,   401,   232,   241,   252,    12,   181,   257,   260,
     193,   401,   259,   194,   195,   265,   269,   271,   274,   275,
     334,   120,   434,   276,   287,   334,    12,   334,   288,   528,
     295,   505,    83,   292,   305,   314,   316,   317,   321,   335,
     352,   346,   340,   351,   354,   114,   357,   359,   547,   528,
     364,   362,   120,   366,   419,   372,    83,   375,   556,   334,
     334,   562,   377,   378,   379,   380,   381,   232,   384,   385,
     386,   120,   232,   396,   121,   174,   402,   404,   412,   122,
     114,   409,   175,   414,   114,   422,   176,   123,   566,   425,
     439,   434,   178,   430,   435,   179,   180,   437,   443,   114,
     114,   444,   433,   124,   445,   121,   174,   446,    12,   181,
     122,   449,   454,   175,   230,   456,   465,   176,   123,   177,
     457,   506,   461,   178,   121,   174,   179,   180,   468,   122,
     472,   474,   175,   433,   124,   475,   176,   123,   177,    12,
     181,   476,   178,   477,   486,   179,   180,   480,   481,   482,
     483,   441,   489,   124,   525,    87,   493,   506,    12,   181,
     491,   492,   495,   497,    88,    89,   509,   529,    90,    91,
      65,    66,    92,   520,   521,    67,    93,    94,    95,    96,
      97,   524,    68,    69,    98,    99,   100,   531,   532,   534,
     535,   536,   101,   102,    58,    70,   539,    71,   540,   232,
     548,   543,   103,   104,   105,   551,   552,    61,    72,   553,
     184,   561,   563,   433,   565,   567,   568,   153,   570,   571,
     574,    39,   575,   579,   580,   424,   507,   473,   530,   436,
     327,   201,   206,   184,   328,   403,   329,   490,   455,   324,
     187,   415,   542,   496,   382,   526,   374,   519,   470,   250,
     569,    15,   145,   119,   417,   158,   533,   148,     0,     0,
     251
};

static const yytype_int16 yycheck[] =
{
       9,    10,    11,    68,    64,   118,   261,   208,   132,    59,
     121,   122,   228,    71,   352,    81,    66,   295,   219,   240,
     209,   222,   226,    84,   240,   332,   433,   425,     4,     4,
       4,    81,     5,   234,   235,     5,   192,   193,   194,   195,
     295,     4,    58,   238,    61,    67,   256,    56,    57,   404,
      61,     4,     5,    62,    63,    64,     5,   502,    67,   172,
      78,    70,    71,   128,     5,     4,    75,     4,   118,   388,
     131,     4,    89,    91,   472,    91,    87,     5,    89,   140,
       0,   526,    57,    57,   131,   340,    62,    62,    62,     5,
     368,   213,    91,     5,   449,    70,    70,   253,   254,   454,
     256,   110,    78,   259,    74,   300,     5,   362,   318,   516,
     175,    86,    86,   178,   179,   180,   523,     4,    91,     5,
      61,   440,   172,    62,    73,    62,    65,     4,    65,   190,
      63,   347,    60,   488,   489,   185,    75,   187,    75,    78,
      79,    78,    79,   190,   399,   110,    87,     5,    89,   456,
     354,   273,    91,   162,    91,    71,     4,     5,   223,   348,
      37,    89,   318,    91,    92,   174,     4,    90,   233,    85,
       4,   236,     4,   238,   330,   225,    92,    89,    68,    91,
     518,     4,   191,     4,   297,    62,    76,     4,    65,    58,
      89,   252,    91,   243,    84,   411,   120,   162,    75,   249,
     416,    78,    79,    89,   265,    91,    92,     5,   217,    78,
      89,   335,    71,   263,    91,   326,   471,   226,     5,   228,
     421,   287,    91,    57,    62,   283,    85,    43,    62,    71,
      62,   240,   388,    92,     4,   300,    70,   287,     4,    62,
      57,    62,   535,    85,   465,    62,     5,   297,   298,   258,
     174,   260,    86,    70,   263,    89,   549,    91,    92,     4,
       5,   185,   312,   187,   325,   543,     4,     5,     8,    86,
      10,   185,     9,   187,   283,   476,   326,     5,   402,     5,
     501,   559,    19,    60,    61,   335,   442,   352,     5,   213,
     446,    59,    60,    61,    89,    35,    91,    92,    35,   359,
      40,   425,     5,    40,   228,     5,    46,    43,    48,    43,
      50,    48,    89,   378,   379,    92,   240,    89,    90,   243,
       5,    89,     5,   332,    92,   249,    58,   543,     4,     5,
     441,    60,    61,    65,    63,   448,    60,    61,   347,     4,
       5,   465,   351,   393,     5,   354,    78,   397,   472,   273,
     359,   412,   402,   414,     4,     5,    80,   481,     5,    91,
      89,    23,    24,    92,    61,    89,    56,   291,    92,     5,
     571,     5,    64,   574,     4,   425,    55,   501,    92,     6,
      72,    30,    31,    32,    93,    77,    23,    24,   312,    81,
      82,    83,    57,    58,    93,   404,     4,    62,   448,    91,
      65,    22,   411,     4,    69,    70,    71,   416,     6,    93,
      75,     4,    45,    78,    79,   465,    87,     4,    47,     5,
      65,    86,   472,   347,     5,     4,    91,    92,     5,     4,
      75,   481,    63,    78,    79,     4,     9,     5,     5,     5,
     449,     4,   366,     5,     4,   454,    91,   456,    20,   509,
      44,   501,   502,   518,     5,    59,    63,     5,     5,     4,
      45,     5,    54,     4,     6,   474,     5,     4,   528,   529,
       5,    47,     4,     4,    39,     5,   526,     5,   543,   488,
     489,   546,     5,     5,     5,     5,     5,   411,     5,     5,
       5,     4,   416,     5,    57,    58,     4,     4,     4,    62,
     509,    15,    65,     4,   513,     5,    69,    70,    71,     4,
     575,   435,    75,    15,     4,    78,    79,    88,     5,   528,
     529,     5,    85,    86,     5,    57,    58,    63,    91,    92,
      62,     4,     4,    65,   543,     4,     4,    69,    70,    71,
       5,   465,     5,    75,    57,    58,    78,    79,     5,    62,
       4,     4,    65,    85,    86,     5,    69,    70,    71,    91,
      92,     4,    75,     4,    63,    78,    79,     5,    66,     5,
       5,    62,     4,    86,   498,     4,    62,   501,    91,    92,
       5,     5,     5,     5,    13,    14,     4,     4,    17,    18,
      11,    12,    21,     5,    88,    16,    25,    26,    27,    28,
      29,     5,    23,    24,    33,    34,    35,     5,     5,     5,
       5,     4,    41,    42,    35,    36,     5,    38,     5,   543,
       4,     7,    51,    52,    53,     5,     5,    48,    49,     5,
     554,     5,     5,    85,     5,     5,     4,    85,     5,     4,
       4,    23,     5,     5,     5,   360,   466,   427,   510,   368,
     259,   134,   141,   577,   259,   337,   259,   450,   406,   258,
     122,   349,   523,   459,   312,   501,   298,   481,   423,   187,
     559,    10,    75,    67,   351,   106,   513,    79,    -1,    -1,
     191
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    95,    96,   115,   140,    67,     0,     4,    68,
      76,    84,    91,   220,   238,   221,   238,   223,   238,     5,
       5,     5,    98,   117,   142,     4,     5,    97,    99,   100,
     101,   102,   105,   106,   107,     4,     5,   100,   105,   106,
     116,   118,   131,     4,     5,   100,   105,   141,   143,   144,
     145,   148,   149,   152,   159,   172,     8,    10,    35,    40,
      46,    48,    50,     9,    19,    11,    12,    16,    23,    24,
      36,    38,    49,   224,   238,   221,   222,    90,   236,   240,
      89,   207,   208,   239,     4,   103,   104,     4,    13,    14,
      17,    18,    21,    25,    26,    27,    28,    29,    33,    34,
      35,    41,    42,    51,    52,    53,   231,   232,   199,   234,
     238,   225,   238,   226,   238,   147,   200,   235,   239,   220,
       4,    57,    62,    70,    86,   173,   175,   176,   184,   185,
     186,     4,    62,   153,   154,   155,   195,   228,   238,   199,
       4,   150,   151,    43,   108,   222,     5,     5,   236,   208,
       5,   202,   238,   104,     5,    30,    31,    32,   232,     5,
       5,   234,   238,    43,   119,    43,   132,     4,     5,   146,
       5,   235,   239,     5,    58,    65,    69,    71,    75,    78,
      79,    92,   173,   202,   241,   187,   240,   187,     5,   173,
       4,    37,    65,    75,    78,    79,   154,   202,    61,   211,
       5,   155,    56,   160,     5,   202,   151,     5,     4,    55,
     109,   201,   237,   241,    93,    93,    93,     6,   234,     4,
      22,   120,     4,    45,   133,    87,     6,   235,   180,   182,
     238,   239,   241,   173,     4,     4,   173,   173,   173,     5,
     179,     5,    60,   203,   205,   211,   212,   239,   241,   203,
     205,   228,     4,   195,   195,   195,   195,     5,   183,    63,
       4,    47,   161,   198,   201,     4,   191,   192,   194,     9,
     110,     5,   237,   241,     5,     5,     5,    64,    72,    77,
      81,    82,    83,   218,   219,   238,   201,     4,    20,   121,
     201,     4,   173,   177,   233,    44,   134,   239,   218,   180,
     173,   174,   201,   201,   173,     5,   174,     5,   178,   180,
     212,    59,   203,   204,    59,    63,    63,     5,   195,   196,
     195,     5,   196,     5,   182,     4,    62,   156,   157,   158,
     188,   195,   229,   230,   238,     4,   164,   166,   167,   233,
      54,   162,     5,   197,   238,   239,     5,    58,    65,    78,
     202,     4,    45,   111,     6,   237,   199,     5,   208,     4,
     124,   125,    47,   122,     5,     5,     4,   135,   136,   137,
     138,   233,     5,   235,   200,     5,   174,     5,     5,     5,
       5,     5,   204,   196,     5,     5,     5,     4,    78,   156,
     157,   158,   239,   240,   195,   230,     5,    87,   206,   210,
     211,   239,     4,   167,     4,   165,   170,   171,   233,    15,
     163,   180,     4,   192,     4,   194,   181,   225,   177,    39,
     112,   218,     5,   226,   125,     4,   126,   127,   128,   233,
      15,   123,    71,    85,   241,     4,   137,    88,   173,   173,
      78,    62,   188,     5,     5,     5,    63,   239,   239,     4,
     168,   169,   233,   229,     4,   171,     4,     5,   180,   192,
     193,     5,     5,   180,   214,     4,   113,   114,     5,   201,
     214,   210,     4,   128,     4,     5,     4,     4,   175,   189,
       5,    66,     5,     5,   195,   195,    63,   235,   229,     4,
     169,     5,     5,    62,   230,     5,   193,     5,     4,     5,
     213,    80,   209,   211,   212,   239,   241,   114,     5,     4,
     129,   130,   233,   226,   227,   201,    78,     5,    74,   206,
       5,    88,   229,   190,     5,   241,   209,   207,   226,     4,
     130,     5,     5,   227,     5,     5,     4,   175,   177,     5,
       5,    63,   189,     7,   207,     5,    73,   226,     4,   138,
     139,     5,     5,     5,     4,   138,   173,   180,   215,   216,
     217,     5,   173,     5,   139,     5,    71,     5,     4,   217,
       5,     4,    71,   201,     4,     5,   201,     4,   139,     5,
       5
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
     173,   173,   173,   173,   174,   174,   175,   176,   177,   177,
     178,   178,   179,   179,   180,   180,   181,   181,   182,   182,
     183,   183,   184,   184,   185,   185,   186,   186,   187,   187,
     188,   189,   189,   190,   190,   191,   191,   192,   192,   193,
     193,   194,   194,   195,   195,   195,   195,   195,   196,   196,
     197,   197,   198,   198,   199,   199,   200,   200,   201,   201,
     202,   203,   203,   203,   203,   204,   204,   205,   206,   206,
     207,   208,   208,   209,   209,   209,   209,   210,   210,   211,
     212,   213,   214,   214,   215,   215,   215,   216,   216,   217,
     217,   218,   218,   219,   219,   219,   219,   219,   219,   220,
     221,   222,   222,   223,   224,   225,   226,   227,   227,   228,
     229,   230,   230,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   232,   232,   233,   234,   234,   235,
     235,   236,   236,   237,   237,   238,   239,   240,   241
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
       1,     0,     2,     4,     4,     4,     8,     0,     2,     4,
       4,     4,     1,     2,     4,     1,     4,     1,     4,     4,
       4,     4,     3,     1,     2,     4,     3,     2,     3,     5,
       3,     8,     4,     2,     2,     4,     1,     1,     1,     1,
       4,     4,     1,     2,     4,     1,     2,     6,     1,     2,
       4,     5,     5,     5,     4,     7,     7,     2,     3,     1,
       1,     1,     1,     3,     1,     2,     4,     5,     1,     1,
       1,     1,     0,     2,     1,     1,     0,     2,     1,     1,
       0,     2,     1,     1,     4,     4,     4,     4,     1,     0,
       4,     1,     4,     0,     2,     5,     1,     1,     4,     1,
       2,     4,     5,     5,     5,     5,     4,     4,     1,     2,
       1,     1,     0,     2,     1,     5,     1,     5,     1,     5,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     4,     1,
       1,     5,     0,     2,     1,     1,     1,     7,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     4,     1,     2,     2,     0,     2,     0,
       2,     0,     2,     0,     2,     1,     1,     1,     1
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
#line 460 "epddl.y"
                    { (yyval.maindef_) = new Domain((yyvsp[0].domaindef_)); result->maindef_ = (yyval.maindef_); }
#line 1951 "Parser.C"
    break;

  case 3: /* MainDef: LibraryDef  */
#line 461 "epddl.y"
               { (yyval.maindef_) = new ActionTypeLibrary((yyvsp[0].librarydef_)); result->maindef_ = (yyval.maindef_); }
#line 1957 "Parser.C"
    break;

  case 4: /* MainDef: ProblemDef  */
#line 462 "epddl.y"
               { (yyval.maindef_) = new Problem((yyvsp[0].problemdef_)); result->maindef_ = (yyval.maindef_); }
#line 1963 "Parser.C"
    break;

  case 5: /* DomainDef: _LPAREN _KW_define _LPAREN _KW_domain DomainName _RPAREN ListDomainItemDef _RPAREN  */
#line 464 "epddl.y"
                                                                                               { (yyval.domaindef_) = new EPDDLDomain((yyvsp[-3].domainname_), (yyvsp[-1].listdomainitemdef_)); }
#line 1969 "Parser.C"
    break;

  case 6: /* DomainItemDef: DomainLibrariesNameDef  */
#line 466 "epddl.y"
                                       { (yyval.domainitemdef_) = new EPDDLDomLibrary((yyvsp[0].domainlibrariesnamedef_)); }
#line 1975 "Parser.C"
    break;

  case 7: /* DomainItemDef: RequireDef  */
#line 467 "epddl.y"
               { (yyval.domainitemdef_) = new EPDDLDomRequire((yyvsp[0].requiredef_)); }
#line 1981 "Parser.C"
    break;

  case 8: /* DomainItemDef: TypesDef  */
#line 468 "epddl.y"
             { (yyval.domainitemdef_) = new EPDDLDomTypes((yyvsp[0].typesdef_)); }
#line 1987 "Parser.C"
    break;

  case 9: /* DomainItemDef: PredicateListDef  */
#line 469 "epddl.y"
                     { (yyval.domainitemdef_) = new EPDDLDomPredicates((yyvsp[0].predicatelistdef_)); }
#line 1993 "Parser.C"
    break;

  case 10: /* DomainItemDef: ModalitiesDef  */
#line 470 "epddl.y"
                  { (yyval.domainitemdef_) = new EPDDLDomModalities((yyvsp[0].modalitiesdef_)); }
#line 1999 "Parser.C"
    break;

  case 11: /* DomainItemDef: ObservabilityGroupsDef  */
#line 471 "epddl.y"
                           { (yyval.domainitemdef_) = new EPDDLDomObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 2005 "Parser.C"
    break;

  case 12: /* DomainItemDef: ActionDef  */
#line 472 "epddl.y"
              { (yyval.domainitemdef_) = new EPDDLDomAction((yyvsp[0].actiondef_)); }
#line 2011 "Parser.C"
    break;

  case 13: /* ListDomainItemDef: %empty  */
#line 474 "epddl.y"
                                { (yyval.listdomainitemdef_) = new ListDomainItemDef(); }
#line 2017 "Parser.C"
    break;

  case 14: /* ListDomainItemDef: ListDomainItemDef DomainItemDef  */
#line 475 "epddl.y"
                                    { (yyvsp[-1].listdomainitemdef_)->push_back((yyvsp[0].domainitemdef_)); (yyval.listdomainitemdef_) = (yyvsp[-1].listdomainitemdef_); }
#line 2023 "Parser.C"
    break;

  case 15: /* DomainLibrariesNameDef: _LPAREN _SYMB_2 ListLibraryName _RPAREN  */
#line 477 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listlibraryname_)->begin(),(yyvsp[-1].listlibraryname_)->end()) ;(yyval.domainlibrariesnamedef_) = new EPDDLDomLibraryNames((yyvsp[-1].listlibraryname_)); }
#line 2029 "Parser.C"
    break;

  case 16: /* RequireDef: _LPAREN _SYMB_3 ListRequireKey _RPAREN  */
#line 479 "epddl.y"
                                                    { std::reverse((yyvsp[-1].listrequirekey_)->begin(),(yyvsp[-1].listrequirekey_)->end()) ;(yyval.requiredef_) = new EPDDLRequire((yyvsp[-1].listrequirekey_)); }
#line 2035 "Parser.C"
    break;

  case 17: /* TypesDef: _LPAREN _SYMB_4 TypedIdentList _RPAREN  */
#line 481 "epddl.y"
                                                  { (yyval.typesdef_) = new EPDDLTypes((yyvsp[-1].typedidentlist_)); }
#line 2041 "Parser.C"
    break;

  case 18: /* PredicateListDef: _LPAREN _SYMB_5 ListPredicateDef _RPAREN  */
#line 483 "epddl.y"
                                                            { std::reverse((yyvsp[-1].listpredicatedef_)->begin(),(yyvsp[-1].listpredicatedef_)->end()) ;(yyval.predicatelistdef_) = new EPDDLPredicateList((yyvsp[-1].listpredicatedef_)); }
#line 2047 "Parser.C"
    break;

  case 19: /* PredicateDef: _LPAREN PredicateName TypedVariableList _RPAREN  */
#line 485 "epddl.y"
                                                               { (yyval.predicatedef_) = new EPDDLPredicateDef((yyvsp[-2].predicatename_), (yyvsp[-1].typedvariablelist_)); }
#line 2053 "Parser.C"
    break;

  case 20: /* ListPredicateDef: PredicateDef  */
#line 487 "epddl.y"
                                { (yyval.listpredicatedef_) = new ListPredicateDef(); (yyval.listpredicatedef_)->push_back((yyvsp[0].predicatedef_)); }
#line 2059 "Parser.C"
    break;

  case 21: /* ListPredicateDef: PredicateDef ListPredicateDef  */
#line 488 "epddl.y"
                                  { (yyvsp[0].listpredicatedef_)->push_back((yyvsp[-1].predicatedef_)); (yyval.listpredicatedef_) = (yyvsp[0].listpredicatedef_); }
#line 2065 "Parser.C"
    break;

  case 22: /* ModalitiesDef: _LPAREN _SYMB_6 ListModalityName _RPAREN  */
#line 490 "epddl.y"
                                                         { std::reverse((yyvsp[-1].listmodalityname_)->begin(),(yyvsp[-1].listmodalityname_)->end()) ;(yyval.modalitiesdef_) = new EPDDLModalities((yyvsp[-1].listmodalityname_)); }
#line 2071 "Parser.C"
    break;

  case 23: /* ObservabilityGroupsDef: _LPAREN _SYMB_7 ListObservingAgentGroup _RPAREN  */
#line 492 "epddl.y"
                                                                         { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.observabilitygroupsdef_) = new EPDDLObsGroupsNames((yyvsp[-1].listobservingagentgroup_)); }
#line 2077 "Parser.C"
    break;

  case 24: /* ActionDef: _LPAREN _SYMB_8 ActionName ActionParameterDef ActionConditionsDef ActionTypeSignatureDef ActionPreDef ActionObsDef _RPAREN  */
#line 494 "epddl.y"
                                                                                                                                       { (yyval.actiondef_) = new EPDDLAction((yyvsp[-6].actionname_), (yyvsp[-5].actionparameterdef_), (yyvsp[-4].actionconditionsdef_), (yyvsp[-3].actiontypesignaturedef_), (yyvsp[-2].actionpredef_), (yyvsp[-1].actionobsdef_)); }
#line 2083 "Parser.C"
    break;

  case 25: /* ActionParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 496 "epddl.y"
                                                               { (yyval.actionparameterdef_) = new ActionParam((yyvsp[-1].typedvariablelist_)); }
#line 2089 "Parser.C"
    break;

  case 26: /* ActionConditionsDef: _SYMB_10 ConditionFormula  */
#line 498 "epddl.y"
                                                { (yyval.actionconditionsdef_) = new ActionCond((yyvsp[0].conditionformula_)); }
#line 2095 "Parser.C"
    break;

  case 27: /* ActionConditionsDef: %empty  */
#line 499 "epddl.y"
                { (yyval.actionconditionsdef_) = new EmptyActionCond(); }
#line 2101 "Parser.C"
    break;

  case 28: /* ActionTypeSignatureDef: _SYMB_11 _LPAREN ActionTypeName ListParameter _RPAREN  */
#line 501 "epddl.y"
                                                                               { (yyval.actiontypesignaturedef_) = new ActionSignature((yyvsp[-2].actiontypename_), (yyvsp[-1].listparameter_)); }
#line 2107 "Parser.C"
    break;

  case 29: /* ActionPreDef: _SYMB_12 FormulaOrEmpty  */
#line 503 "epddl.y"
                                       { (yyval.actionpredef_) = new ActionPre((yyvsp[0].formulaorempty_)); }
#line 2113 "Parser.C"
    break;

  case 30: /* ActionObsDef: _SYMB_13 ListObsConditionDef  */
#line 505 "epddl.y"
                                            { std::reverse((yyvsp[0].listobsconditiondef_)->begin(),(yyvsp[0].listobsconditiondef_)->end()) ;(yyval.actionobsdef_) = new ActionObs((yyvsp[0].listobsconditiondef_)); }
#line 2119 "Parser.C"
    break;

  case 31: /* ActionObsDef: %empty  */
#line 506 "epddl.y"
                { (yyval.actionobsdef_) = new EmptyActionObs(); }
#line 2125 "Parser.C"
    break;

  case 32: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _RPAREN  */
#line 508 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new EmptyObsCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2131 "Parser.C"
    break;

  case 33: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _KW_if Formula _RPAREN  */
#line 509 "epddl.y"
                                                                      { (yyval.obsconditiondef_) = new ObsCond((yyvsp[-4].observingagent_), (yyvsp[-3].observingagentgroup_), (yyvsp[-1].formula_)); }
#line 2137 "Parser.C"
    break;

  case 34: /* ObsConditionDef: _LPAREN _KW_otherwise ObservingAgent ObservingAgentGroup _RPAREN  */
#line 510 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new ObsOtherwiseCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2143 "Parser.C"
    break;

  case 35: /* ListObsConditionDef: ObsConditionDef  */
#line 512 "epddl.y"
                                      { (yyval.listobsconditiondef_) = new ListObsConditionDef(); (yyval.listobsconditiondef_)->push_back((yyvsp[0].obsconditiondef_)); }
#line 2149 "Parser.C"
    break;

  case 36: /* ListObsConditionDef: ObsConditionDef ListObsConditionDef  */
#line 513 "epddl.y"
                                        { (yyvsp[0].listobsconditiondef_)->push_back((yyvsp[-1].obsconditiondef_)); (yyval.listobsconditiondef_) = (yyvsp[0].listobsconditiondef_); }
#line 2155 "Parser.C"
    break;

  case 37: /* LibraryDef: _LPAREN _KW_define _LPAREN _KW_library LibraryName _RPAREN ListLibraryItemDef _RPAREN  */
#line 515 "epddl.y"
                                                                                                   { (yyval.librarydef_) = new EPDDLLibrary((yyvsp[-3].libraryname_), (yyvsp[-1].listlibraryitemdef_)); }
#line 2161 "Parser.C"
    break;

  case 38: /* LibraryItemDef: RequireDef  */
#line 517 "epddl.y"
                            { (yyval.libraryitemdef_) = new EPDDLLibRequire((yyvsp[0].requiredef_)); }
#line 2167 "Parser.C"
    break;

  case 39: /* LibraryItemDef: ModalitiesDef  */
#line 518 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibModalities((yyvsp[0].modalitiesdef_)); }
#line 2173 "Parser.C"
    break;

  case 40: /* LibraryItemDef: ObservabilityGroupsDef  */
#line 519 "epddl.y"
                           { (yyval.libraryitemdef_) = new EPDDLLibObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 2179 "Parser.C"
    break;

  case 41: /* LibraryItemDef: ActionTypeDef  */
#line 520 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibActionType((yyvsp[0].actiontypedef_)); }
#line 2185 "Parser.C"
    break;

  case 42: /* LibraryItemDef: EventDef  */
#line 521 "epddl.y"
             { (yyval.libraryitemdef_) = new EPDDLLibEvent((yyvsp[0].eventdef_)); }
#line 2191 "Parser.C"
    break;

  case 43: /* ListLibraryItemDef: %empty  */
#line 523 "epddl.y"
                                 { (yyval.listlibraryitemdef_) = new ListLibraryItemDef(); }
#line 2197 "Parser.C"
    break;

  case 44: /* ListLibraryItemDef: ListLibraryItemDef LibraryItemDef  */
#line 524 "epddl.y"
                                      { (yyvsp[-1].listlibraryitemdef_)->push_back((yyvsp[0].libraryitemdef_)); (yyval.listlibraryitemdef_) = (yyvsp[-1].listlibraryitemdef_); }
#line 2203 "Parser.C"
    break;

  case 45: /* ActionTypeDef: _LPAREN _SYMB_11 ActionTypeName ActionTypeParameterDef ActionTypeFrameDef ActionTypeEventsDef ActionTypeRelDef ActionTypeDesDef _RPAREN  */
#line 526 "epddl.y"
                                                                                                                                                        { (yyval.actiontypedef_) = new EPDDLActType((yyvsp[-6].actiontypename_), (yyvsp[-5].actiontypeparameterdef_), (yyvsp[-4].actiontypeframedef_), (yyvsp[-3].actiontypeeventsdef_), (yyvsp[-2].actiontypereldef_), (yyvsp[-1].actiontypedesdef_)); }
#line 2209 "Parser.C"
    break;

  case 46: /* ActionTypeParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 528 "epddl.y"
                                                                   { (yyval.actiontypeparameterdef_) = new ActTypeParam((yyvsp[-1].typedvariablelist_)); }
#line 2215 "Parser.C"
    break;

  case 47: /* ActionTypeFrameDef: _SYMB_14 _LPAREN ListObservingAgentGroup _RPAREN  */
#line 530 "epddl.y"
                                                                      { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.actiontypeframedef_) = new ActTypeFrame((yyvsp[-1].listobservingagentgroup_)); }
#line 2221 "Parser.C"
    break;

  case 48: /* ActionTypeFrameDef: %empty  */
#line 531 "epddl.y"
                { (yyval.actiontypeframedef_) = new EmptyActTypeFrame(); }
#line 2227 "Parser.C"
    break;

  case 49: /* ActionTypeEventsDef: _SYMB_15 ListEventSignature  */
#line 533 "epddl.y"
                                                  { std::reverse((yyvsp[0].listeventsignature_)->begin(),(yyvsp[0].listeventsignature_)->end()) ;(yyval.actiontypeeventsdef_) = new ActTypeEvents((yyvsp[0].listeventsignature_)); }
#line 2233 "Parser.C"
    break;

  case 50: /* ActionTypeRelDef: _SYMB_16 ActionRelations  */
#line 535 "epddl.y"
                                            { (yyval.actiontypereldef_) = new ActTypeRel((yyvsp[0].actionrelations_)); }
#line 2239 "Parser.C"
    break;

  case 51: /* ActionTypeDesDef: _SYMB_17 _LPAREN ListEventName _RPAREN  */
#line 537 "epddl.y"
                                                          { std::reverse((yyvsp[-1].listeventname_)->begin(),(yyvsp[-1].listeventname_)->end()) ;(yyval.actiontypedesdef_) = new ActTypeDes((yyvsp[-1].listeventname_)); }
#line 2245 "Parser.C"
    break;

  case 52: /* EventSignature: _LPAREN EventName ListParameter _RPAREN  */
#line 539 "epddl.y"
                                                         { (yyval.eventsignature_) = new EventSign((yyvsp[-2].eventname_), (yyvsp[-1].listparameter_)); }
#line 2251 "Parser.C"
    break;

  case 53: /* ListEventSignature: EventSignature  */
#line 541 "epddl.y"
                                    { (yyval.listeventsignature_) = new ListEventSignature(); (yyval.listeventsignature_)->push_back((yyvsp[0].eventsignature_)); }
#line 2257 "Parser.C"
    break;

  case 54: /* ListEventSignature: EventSignature ListEventSignature  */
#line 542 "epddl.y"
                                      { (yyvsp[0].listeventsignature_)->push_back((yyvsp[-1].eventsignature_)); (yyval.listeventsignature_) = (yyvsp[0].listeventsignature_); }
#line 2263 "Parser.C"
    break;

  case 55: /* ActionRelations: ListEventRelation  */
#line 544 "epddl.y"
                                    { std::reverse((yyvsp[0].listeventrelation_)->begin(),(yyvsp[0].listeventrelation_)->end()) ;(yyval.actionrelations_) = new EventsActionRel((yyvsp[0].listeventrelation_)); }
#line 2269 "Parser.C"
    break;

  case 56: /* ActionRelations: TrivialDef  */
#line 545 "epddl.y"
               { (yyval.actionrelations_) = new TrivialActionRel((yyvsp[0].trivialdef_)); }
#line 2275 "Parser.C"
    break;

  case 57: /* EventRelation: _LPAREN AgentGroup ListEventNamePair _RPAREN  */
#line 547 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listeventnamepair_)->begin(),(yyvsp[-1].listeventnamepair_)->end()) ;(yyval.eventrelation_) = new EventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listeventnamepair_)); }
#line 2281 "Parser.C"
    break;

  case 58: /* EventRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 548 "epddl.y"
                                          { (yyval.eventrelation_) = new TrivialEventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2287 "Parser.C"
    break;

  case 59: /* ListEventRelation: EventRelation  */
#line 550 "epddl.y"
                                  { (yyval.listeventrelation_) = new ListEventRelation(); (yyval.listeventrelation_)->push_back((yyvsp[0].eventrelation_)); }
#line 2293 "Parser.C"
    break;

  case 60: /* ListEventRelation: EventRelation ListEventRelation  */
#line 551 "epddl.y"
                                    { (yyvsp[0].listeventrelation_)->push_back((yyvsp[-1].eventrelation_)); (yyval.listeventrelation_) = (yyvsp[0].listeventrelation_); }
#line 2299 "Parser.C"
    break;

  case 61: /* EventNamePair: _LPAREN EventName EventName _RPAREN  */
#line 553 "epddl.y"
                                                    { (yyval.eventnamepair_) = new EventPair((yyvsp[-2].eventname_), (yyvsp[-1].eventname_)); }
#line 2305 "Parser.C"
    break;

  case 62: /* ListEventNamePair: EventNamePair  */
#line 555 "epddl.y"
                                  { (yyval.listeventnamepair_) = new ListEventNamePair(); (yyval.listeventnamepair_)->push_back((yyvsp[0].eventnamepair_)); }
#line 2311 "Parser.C"
    break;

  case 63: /* ListEventNamePair: EventNamePair ListEventNamePair  */
#line 556 "epddl.y"
                                    { (yyvsp[0].listeventnamepair_)->push_back((yyvsp[-1].eventnamepair_)); (yyval.listeventnamepair_) = (yyvsp[0].listeventnamepair_); }
#line 2317 "Parser.C"
    break;

  case 64: /* EventDef: _LPAREN _SYMB_18 EventName EventParameterDef EventPreDef EventPostDef _RPAREN  */
#line 558 "epddl.y"
                                                                                         { (yyval.eventdef_) = new EPDDLEvent((yyvsp[-4].eventname_), (yyvsp[-3].eventparameterdef_), (yyvsp[-2].eventpredef_), (yyvsp[-1].eventpostdef_)); }
#line 2323 "Parser.C"
    break;

  case 65: /* EventParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 560 "epddl.y"
                                                              { (yyval.eventparameterdef_) = new EventParam((yyvsp[-1].typedvariablelist_)); }
#line 2329 "Parser.C"
    break;

  case 66: /* EventPreDef: _SYMB_12 FormulaOrEmpty  */
#line 562 "epddl.y"
                                      { (yyval.eventpredef_) = new EventPre((yyvsp[0].formulaorempty_)); }
#line 2335 "Parser.C"
    break;

  case 67: /* EventPostDef: _SYMB_19 EventPostconditions  */
#line 564 "epddl.y"
                                            { (yyval.eventpostdef_) = new EventPost((yyvsp[0].eventpostconditions_)); }
#line 2341 "Parser.C"
    break;

  case 68: /* EventPostDef: %empty  */
#line 565 "epddl.y"
                { (yyval.eventpostdef_) = new EmptyEventPost(); }
#line 2347 "Parser.C"
    break;

  case 69: /* EventPostconditions: ListPostcondition  */
#line 567 "epddl.y"
                                        { std::reverse((yyvsp[0].listpostcondition_)->begin(),(yyvsp[0].listpostcondition_)->end()) ;(yyval.eventpostconditions_) = new Postconditions((yyvsp[0].listpostcondition_)); }
#line 2353 "Parser.C"
    break;

  case 70: /* EventPostconditions: TrivialDef  */
#line 568 "epddl.y"
               { (yyval.eventpostconditions_) = new TrivialPostconditions((yyvsp[0].trivialdef_)); }
#line 2359 "Parser.C"
    break;

  case 71: /* Postcondition: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN ListLiteralPostcondition _RPAREN  */
#line 570 "epddl.y"
                                                                                                      { std::reverse((yyvsp[-1].listliteralpostcondition_)->begin(),(yyvsp[-1].listliteralpostcondition_)->end()) ;(yyval.postcondition_) = new ForallPostcondition((yyvsp[-3].typedvariablelist_), (yyvsp[-1].listliteralpostcondition_)); }
#line 2365 "Parser.C"
    break;

  case 72: /* Postcondition: LiteralPostcondition  */
#line 571 "epddl.y"
                         { (yyval.postcondition_) = new SinglePostcondition((yyvsp[0].literalpostcondition_)); }
#line 2371 "Parser.C"
    break;

  case 73: /* Postcondition: _LPAREN Variable _RPAREN  */
#line 572 "epddl.y"
                             { (yyval.postcondition_) = new VarPostcondition((yyvsp[-1]._variable)); }
#line 2377 "Parser.C"
    break;

  case 74: /* ListPostcondition: Postcondition  */
#line 574 "epddl.y"
                                  { (yyval.listpostcondition_) = new ListPostcondition(); (yyval.listpostcondition_)->push_back((yyvsp[0].postcondition_)); }
#line 2383 "Parser.C"
    break;

  case 75: /* ListPostcondition: Postcondition ListPostcondition  */
#line 575 "epddl.y"
                                    { (yyvsp[0].listpostcondition_)->push_back((yyvsp[-1].postcondition_)); (yyval.listpostcondition_) = (yyvsp[0].listpostcondition_); }
#line 2389 "Parser.C"
    break;

  case 76: /* LiteralPostcondition: _LPAREN _KW_set Literal _KW_iff FormulaOrEmpty _RPAREN  */
#line 577 "epddl.y"
                                                                              { (yyval.literalpostcondition_) = new LiteralPost((yyvsp[-3].literal_), (yyvsp[-1].formulaorempty_)); }
#line 2395 "Parser.C"
    break;

  case 77: /* LiteralPostcondition: _LPAREN _KW_set Literal _RPAREN  */
#line 578 "epddl.y"
                                    { (yyval.literalpostcondition_) = new TrivialLiteralPost((yyvsp[-1].literal_)); }
#line 2401 "Parser.C"
    break;

  case 78: /* ListLiteralPostcondition: LiteralPostcondition  */
#line 580 "epddl.y"
                                                { (yyval.listliteralpostcondition_) = new ListLiteralPostcondition(); (yyval.listliteralpostcondition_)->push_back((yyvsp[0].literalpostcondition_)); }
#line 2407 "Parser.C"
    break;

  case 79: /* ListLiteralPostcondition: LiteralPostcondition ListLiteralPostcondition  */
#line 581 "epddl.y"
                                                  { (yyvsp[0].listliteralpostcondition_)->push_back((yyvsp[-1].literalpostcondition_)); (yyval.listliteralpostcondition_) = (yyvsp[0].listliteralpostcondition_); }
#line 2413 "Parser.C"
    break;

  case 80: /* ProblemDef: _LPAREN _KW_define _LPAREN _KW_problem ProblemName _RPAREN ListProblemItemDef _RPAREN  */
#line 583 "epddl.y"
                                                                                                   { (yyval.problemdef_) = new EPDDLProblem((yyvsp[-3].problemname_), (yyvsp[-1].listproblemitemdef_)); }
#line 2419 "Parser.C"
    break;

  case 81: /* ProblemItemDef: ProblemDomainNameDef  */
#line 585 "epddl.y"
                                      { (yyval.problemitemdef_) = new EPDDLProbDomain((yyvsp[0].problemdomainnamedef_)); }
#line 2425 "Parser.C"
    break;

  case 82: /* ProblemItemDef: RequireDef  */
#line 586 "epddl.y"
               { (yyval.problemitemdef_) = new EPDDLProbRequire((yyvsp[0].requiredef_)); }
#line 2431 "Parser.C"
    break;

  case 83: /* ProblemItemDef: ModalitiesDef  */
#line 587 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbModalities((yyvsp[0].modalitiesdef_)); }
#line 2437 "Parser.C"
    break;

  case 84: /* ProblemItemDef: AgentNamesDef  */
#line 588 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbAgents((yyvsp[0].agentnamesdef_)); }
#line 2443 "Parser.C"
    break;

  case 85: /* ProblemItemDef: AgentGroupsListDef  */
#line 589 "epddl.y"
                       { (yyval.problemitemdef_) = new EPDDLProbAgentGroups((yyvsp[0].agentgroupslistdef_)); }
#line 2449 "Parser.C"
    break;

  case 86: /* ProblemItemDef: ObjectNamesDef  */
#line 590 "epddl.y"
                   { (yyval.problemitemdef_) = new EPDDLProbObjects((yyvsp[0].objectnamesdef_)); }
#line 2455 "Parser.C"
    break;

  case 87: /* ProblemItemDef: StaticPredListDef  */
#line 591 "epddl.y"
                      { (yyval.problemitemdef_) = new EPDDLProbStaticPred((yyvsp[0].staticpredlistdef_)); }
#line 2461 "Parser.C"
    break;

  case 88: /* ProblemItemDef: InitDef  */
#line 592 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbInit((yyvsp[0].initdef_)); }
#line 2467 "Parser.C"
    break;

  case 89: /* ProblemItemDef: InitialModelDef  */
#line 593 "epddl.y"
                    { (yyval.problemitemdef_) = new EPDDLProbInitModel((yyvsp[0].initialmodeldef_)); }
#line 2473 "Parser.C"
    break;

  case 90: /* ProblemItemDef: GoalDef  */
#line 594 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbGoal((yyvsp[0].goaldef_)); }
#line 2479 "Parser.C"
    break;

  case 91: /* ListProblemItemDef: %empty  */
#line 596 "epddl.y"
                                 { (yyval.listproblemitemdef_) = new ListProblemItemDef(); }
#line 2485 "Parser.C"
    break;

  case 92: /* ListProblemItemDef: ListProblemItemDef ProblemItemDef  */
#line 597 "epddl.y"
                                      { (yyvsp[-1].listproblemitemdef_)->push_back((yyvsp[0].problemitemdef_)); (yyval.listproblemitemdef_) = (yyvsp[-1].listproblemitemdef_); }
#line 2491 "Parser.C"
    break;

  case 93: /* ProblemDomainNameDef: _LPAREN _SYMB_20 DomainName _RPAREN  */
#line 599 "epddl.y"
                                                           { (yyval.problemdomainnamedef_) = new EPDDLProbDomainName((yyvsp[-1].domainname_)); }
#line 2497 "Parser.C"
    break;

  case 94: /* AgentNamesDef: _LPAREN _SYMB_21 TypedAgentList _RPAREN  */
#line 601 "epddl.y"
                                                        { (yyval.agentnamesdef_) = new EPDDLAgentNames((yyvsp[-1].typedagentlist_)); }
#line 2503 "Parser.C"
    break;

  case 95: /* AgentGroupsListDef: _LPAREN _SYMB_22 ListAgentGroupDef _RPAREN  */
#line 603 "epddl.y"
                                                                { (yyval.agentgroupslistdef_) = new EPDDLAgentGroupsList((yyvsp[-1].listagentgroupdef_)); }
#line 2509 "Parser.C"
    break;

  case 96: /* AgentGroupDef: _LPAREN _LBRACE AgentName ListAgentName _RBRACE _KW_as AgentGroupName _RPAREN  */
#line 605 "epddl.y"
                                                                                              { std::reverse((yyvsp[-4].listagentname_)->begin(),(yyvsp[-4].listagentname_)->end()) ;(yyval.agentgroupdef_) = new EPDDLAgentGroupDef((yyvsp[-5]._agentname), (yyvsp[-4].listagentname_), (yyvsp[-1].agentgroupname_)); }
#line 2515 "Parser.C"
    break;

  case 97: /* ListAgentGroupDef: %empty  */
#line 607 "epddl.y"
                                { (yyval.listagentgroupdef_) = new ListAgentGroupDef(); }
#line 2521 "Parser.C"
    break;

  case 98: /* ListAgentGroupDef: ListAgentGroupDef AgentGroupDef  */
#line 608 "epddl.y"
                                    { (yyvsp[-1].listagentgroupdef_)->push_back((yyvsp[0].agentgroupdef_)); (yyval.listagentgroupdef_) = (yyvsp[-1].listagentgroupdef_); }
#line 2527 "Parser.C"
    break;

  case 99: /* ObjectNamesDef: _LPAREN _SYMB_25 TypedIdentList _RPAREN  */
#line 610 "epddl.y"
                                                         { (yyval.objectnamesdef_) = new EPDDLObjectNames((yyvsp[-1].typedidentlist_)); }
#line 2533 "Parser.C"
    break;

  case 100: /* StaticPredListDef: _LPAREN _SYMB_26 ListStaticPredDef _RPAREN  */
#line 612 "epddl.y"
                                                               { std::reverse((yyvsp[-1].liststaticpreddef_)->begin(),(yyvsp[-1].liststaticpreddef_)->end()) ;(yyval.staticpredlistdef_) = new EPDDLStaticPredList((yyvsp[-1].liststaticpreddef_)); }
#line 2539 "Parser.C"
    break;

  case 101: /* StaticPredDef: _LPAREN PredicateName ListGenericName _RPAREN  */
#line 614 "epddl.y"
                                                              { (yyval.staticpreddef_) = new EPDDLStaticPredDef((yyvsp[-2].predicatename_), (yyvsp[-1].listgenericname_)); }
#line 2545 "Parser.C"
    break;

  case 102: /* ListStaticPredDef: StaticPredDef  */
#line 616 "epddl.y"
                                  { (yyval.liststaticpreddef_) = new ListStaticPredDef(); (yyval.liststaticpreddef_)->push_back((yyvsp[0].staticpreddef_)); }
#line 2551 "Parser.C"
    break;

  case 103: /* ListStaticPredDef: StaticPredDef ListStaticPredDef  */
#line 617 "epddl.y"
                                    { (yyvsp[0].liststaticpreddef_)->push_back((yyvsp[-1].staticpreddef_)); (yyval.liststaticpreddef_) = (yyvsp[0].liststaticpreddef_); }
#line 2557 "Parser.C"
    break;

  case 104: /* InitDef: _LPAREN _SYMB_27 InitialStateDescr _RPAREN  */
#line 619 "epddl.y"
                                                     { (yyval.initdef_) = new EPDDLInitialState((yyvsp[-1].initialstatedescr_)); }
#line 2563 "Parser.C"
    break;

  case 105: /* InitialStateDescr: ListFTheoryFormula  */
#line 621 "epddl.y"
                                       { std::reverse((yyvsp[0].listftheoryformula_)->begin(),(yyvsp[0].listftheoryformula_)->end()) ;(yyval.initialstatedescr_) = new FinitaryTheoryDescr((yyvsp[0].listftheoryformula_)); }
#line 2569 "Parser.C"
    break;

  case 106: /* InitialStateDescr: _LPAREN _SYMB_28 ModelName _RPAREN  */
#line 622 "epddl.y"
                                       { (yyval.initialstatedescr_) = new InitialModelDescr((yyvsp[-1].modelname_)); }
#line 2575 "Parser.C"
    break;

  case 107: /* FTheoryFormula: PredicateFormula  */
#line 624 "epddl.y"
                                  { (yyval.ftheoryformula_) = new FTheoryPredForm((yyvsp[0].predicateformula_)); }
#line 2581 "Parser.C"
    break;

  case 108: /* FTheoryFormula: _LBRACK AllAgents _RBRACK PredicateFormula  */
#line 625 "epddl.y"
                                               { (yyval.ftheoryformula_) = new FTheoryCKPredForm((yyvsp[-2].allagents_), (yyvsp[0].predicateformula_)); }
#line 2587 "Parser.C"
    break;

  case 109: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KPredicateFormula  */
#line 626 "epddl.y"
                                                { (yyval.ftheoryformula_) = new FTheoryCKKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kpredicateformula_)); }
#line 2593 "Parser.C"
    break;

  case 110: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KWPredicateFormula  */
#line 627 "epddl.y"
                                                 { (yyval.ftheoryformula_) = new FTheoryCKOrKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kwpredicateformula_)); }
#line 2599 "Parser.C"
    break;

  case 111: /* FTheoryFormula: _LBRACK AllAgents _RBRACK NotKWPredicateFormula  */
#line 628 "epddl.y"
                                                    { (yyval.ftheoryformula_) = new FTheoryCKAndKPredForm((yyvsp[-2].allagents_), (yyvsp[0].notkwpredicateformula_)); }
#line 2605 "Parser.C"
    break;

  case 112: /* FTheoryFormula: _LPAREN FTheoryFormula _RPAREN  */
#line 629 "epddl.y"
                                   { (yyval.ftheoryformula_) = (yyvsp[-1].ftheoryformula_); }
#line 2611 "Parser.C"
    break;

  case 113: /* ListFTheoryFormula: FTheoryFormula  */
#line 631 "epddl.y"
                                    { (yyval.listftheoryformula_) = new ListFTheoryFormula(); (yyval.listftheoryformula_)->push_back((yyvsp[0].ftheoryformula_)); }
#line 2617 "Parser.C"
    break;

  case 114: /* ListFTheoryFormula: FTheoryFormula ListFTheoryFormula  */
#line 632 "epddl.y"
                                      { (yyvsp[0].listftheoryformula_)->push_back((yyvsp[-1].ftheoryformula_)); (yyval.listftheoryformula_) = (yyvsp[0].listftheoryformula_); }
#line 2623 "Parser.C"
    break;

  case 115: /* KPredicateFormula: _LBRACK AgentName _RBRACK PredicateFormula  */
#line 634 "epddl.y"
                                                               { (yyval.kpredicateformula_) = new KPredFormula((yyvsp[-2]._agentname), (yyvsp[0].predicateformula_)); }
#line 2629 "Parser.C"
    break;

  case 116: /* KPredicateFormula: _LPAREN KPredicateFormula _RPAREN  */
#line 635 "epddl.y"
                                      { (yyval.kpredicateformula_) = (yyvsp[-1].kpredicateformula_); }
#line 2635 "Parser.C"
    break;

  case 117: /* KWPredicateFormula: KnowsWhether PredicateFormula  */
#line 637 "epddl.y"
                                                   { (yyval.kwpredicateformula_) = new KWPredFormula((yyvsp[-1].knowswhether_), (yyvsp[0].predicateformula_)); }
#line 2641 "Parser.C"
    break;

  case 118: /* KWPredicateFormula: _LPAREN KWPredicateFormula _RPAREN  */
#line 638 "epddl.y"
                                       { (yyval.kwpredicateformula_) = (yyvsp[-1].kwpredicateformula_); }
#line 2647 "Parser.C"
    break;

  case 119: /* NotKWPredicateFormula: _LPAREN _KW_not KnowsWhether PredicateFormula _RPAREN  */
#line 640 "epddl.y"
                                                                              { (yyval.notkwpredicateformula_) = new NotKWPredFormula((yyvsp[-2].knowswhether_), (yyvsp[-1].predicateformula_)); }
#line 2653 "Parser.C"
    break;

  case 120: /* NotKWPredicateFormula: _LPAREN NotKWPredicateFormula _RPAREN  */
#line 641 "epddl.y"
                                          { (yyval.notkwpredicateformula_) = (yyvsp[-1].notkwpredicateformula_); }
#line 2659 "Parser.C"
    break;

  case 121: /* InitialModelDef: _LPAREN _SYMB_31 ModelName ModelWorldsDef ModelRelDef ModelValDef ModelDesDef _RPAREN  */
#line 643 "epddl.y"
                                                                                                        { (yyval.initialmodeldef_) = new EPDDLInitialModel((yyvsp[-5].modelname_), (yyvsp[-4].modelworldsdef_), (yyvsp[-3].modelreldef_), (yyvsp[-2].modelvaldef_), (yyvsp[-1].modeldesdef_)); }
#line 2665 "Parser.C"
    break;

  case 122: /* ModelWorldsDef: _SYMB_32 _LPAREN ListWorldName _RPAREN  */
#line 645 "epddl.y"
                                                        { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modelworldsdef_) = new ModelWorlds((yyvsp[-1].listworldname_)); }
#line 2671 "Parser.C"
    break;

  case 123: /* ModelRelDef: _SYMB_16 ModelRelations  */
#line 647 "epddl.y"
                                      { (yyval.modelreldef_) = new ModelRel((yyvsp[0].modelrelations_)); }
#line 2677 "Parser.C"
    break;

  case 124: /* ModelValDef: _SYMB_33 ModelValuation  */
#line 649 "epddl.y"
                                      { (yyval.modelvaldef_) = new ModelVal((yyvsp[0].modelvaluation_)); }
#line 2683 "Parser.C"
    break;

  case 125: /* ModelDesDef: _SYMB_17 _LPAREN ListWorldName _RPAREN  */
#line 651 "epddl.y"
                                                     { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modeldesdef_) = new ModelDes((yyvsp[-1].listworldname_)); }
#line 2689 "Parser.C"
    break;

  case 126: /* ModelRelations: ListWorldRelation  */
#line 653 "epddl.y"
                                   { std::reverse((yyvsp[0].listworldrelation_)->begin(),(yyvsp[0].listworldrelation_)->end()) ;(yyval.modelrelations_) = new WorldsModelRel((yyvsp[0].listworldrelation_)); }
#line 2695 "Parser.C"
    break;

  case 127: /* ModelRelations: TrivialDef  */
#line 654 "epddl.y"
               { (yyval.modelrelations_) = new TrivialModelRel((yyvsp[0].trivialdef_)); }
#line 2701 "Parser.C"
    break;

  case 128: /* ModelValuation: ListWorldValuation  */
#line 656 "epddl.y"
                                    { std::reverse((yyvsp[0].listworldvaluation_)->begin(),(yyvsp[0].listworldvaluation_)->end()) ;(yyval.modelvaluation_) = new WorldsModelVal((yyvsp[0].listworldvaluation_)); }
#line 2707 "Parser.C"
    break;

  case 129: /* ModelValuation: TrivialDef  */
#line 657 "epddl.y"
               { (yyval.modelvaluation_) = new TrivialModelVal((yyvsp[0].trivialdef_)); }
#line 2713 "Parser.C"
    break;

  case 130: /* WorldRelation: _LPAREN AgentGroup ListWorldNamePair _RPAREN  */
#line 659 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listworldnamepair_)->begin(),(yyvsp[-1].listworldnamepair_)->end()) ;(yyval.worldrelation_) = new WorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listworldnamepair_)); }
#line 2719 "Parser.C"
    break;

  case 131: /* WorldRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 660 "epddl.y"
                                          { (yyval.worldrelation_) = new TrivialWorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2725 "Parser.C"
    break;

  case 132: /* ListWorldRelation: WorldRelation  */
#line 662 "epddl.y"
                                  { (yyval.listworldrelation_) = new ListWorldRelation(); (yyval.listworldrelation_)->push_back((yyvsp[0].worldrelation_)); }
#line 2731 "Parser.C"
    break;

  case 133: /* ListWorldRelation: WorldRelation ListWorldRelation  */
#line 663 "epddl.y"
                                    { (yyvsp[0].listworldrelation_)->push_back((yyvsp[-1].worldrelation_)); (yyval.listworldrelation_) = (yyvsp[0].listworldrelation_); }
#line 2737 "Parser.C"
    break;

  case 134: /* WorldNamePair: _LPAREN WorldName WorldName _RPAREN  */
#line 665 "epddl.y"
                                                    { (yyval.worldnamepair_) = new WorldPair((yyvsp[-2].worldname_), (yyvsp[-1].worldname_)); }
#line 2743 "Parser.C"
    break;

  case 135: /* ListWorldNamePair: WorldNamePair  */
#line 667 "epddl.y"
                                  { (yyval.listworldnamepair_) = new ListWorldNamePair(); (yyval.listworldnamepair_)->push_back((yyvsp[0].worldnamepair_)); }
#line 2749 "Parser.C"
    break;

  case 136: /* ListWorldNamePair: WorldNamePair ListWorldNamePair  */
#line 668 "epddl.y"
                                    { (yyvsp[0].listworldnamepair_)->push_back((yyvsp[-1].worldnamepair_)); (yyval.listworldnamepair_) = (yyvsp[0].listworldnamepair_); }
#line 2755 "Parser.C"
    break;

  case 137: /* WorldValuation: _LPAREN WorldName _LBRACK ListLiteral _RBRACK _RPAREN  */
#line 670 "epddl.y"
                                                                       { (yyval.worldvaluation_) = new WorldVal((yyvsp[-4].worldname_), (yyvsp[-2].listliteral_)); }
#line 2761 "Parser.C"
    break;

  case 138: /* ListWorldValuation: WorldValuation  */
#line 672 "epddl.y"
                                    { (yyval.listworldvaluation_) = new ListWorldValuation(); (yyval.listworldvaluation_)->push_back((yyvsp[0].worldvaluation_)); }
#line 2767 "Parser.C"
    break;

  case 139: /* ListWorldValuation: WorldValuation ListWorldValuation  */
#line 673 "epddl.y"
                                      { (yyvsp[0].listworldvaluation_)->push_back((yyvsp[-1].worldvaluation_)); (yyval.listworldvaluation_) = (yyvsp[0].listworldvaluation_); }
#line 2773 "Parser.C"
    break;

  case 140: /* GoalDef: _LPAREN _SYMB_34 Formula _RPAREN  */
#line 675 "epddl.y"
                                           { (yyval.goaldef_) = new EPDDLGoals((yyvsp[-1].formula_)); }
#line 2779 "Parser.C"
    break;

  case 141: /* Formula: _LPAREN _KW_imply Formula Formula _RPAREN  */
#line 677 "epddl.y"
                                                    { (yyval.formula_) = new ImplyFormula((yyvsp[-2].formula_), (yyvsp[-1].formula_)); }
#line 2785 "Parser.C"
    break;

  case 142: /* Formula: _LPAREN _KW_or Formula ListFormula _RPAREN  */
#line 678 "epddl.y"
                                               { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new OrFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2791 "Parser.C"
    break;

  case 143: /* Formula: _LPAREN _KW_and Formula ListFormula _RPAREN  */
#line 679 "epddl.y"
                                                { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new AndFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2797 "Parser.C"
    break;

  case 144: /* Formula: _LPAREN _KW_not Formula _RPAREN  */
#line 680 "epddl.y"
                                    { (yyval.formula_) = new NotFormula((yyvsp[-1].formula_)); }
#line 2803 "Parser.C"
    break;

  case 145: /* Formula: _LPAREN _KW_exists _LPAREN TypedVariableList _RPAREN Formula _RPAREN  */
#line 681 "epddl.y"
                                                                         { (yyval.formula_) = new ExistsFormula((yyvsp[-3].typedvariablelist_), (yyvsp[-1].formula_)); }
#line 2809 "Parser.C"
    break;

  case 146: /* Formula: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN Formula _RPAREN  */
#line 682 "epddl.y"
                                                                         { (yyval.formula_) = new ForAllFormula((yyvsp[-3].typedvariablelist_), (yyvsp[-1].formula_)); }
#line 2815 "Parser.C"
    break;

  case 147: /* Formula: Modality Formula  */
#line 683 "epddl.y"
                     { (yyval.formula_) = new ModalFormula((yyvsp[-1].modality_), (yyvsp[0].formula_)); }
#line 2821 "Parser.C"
    break;

  case 148: /* Formula: _LPAREN Variable _RPAREN  */
#line 684 "epddl.y"
                             { (yyval.formula_) = new VarFormula((yyvsp[-1]._variable)); }
#line 2827 "Parser.C"
    break;

  case 149: /* Formula: AtomicFormula  */
#line 685 "epddl.y"
                  { (yyval.formula_) = new AtmFormula((yyvsp[0].atomicformula_)); }
#line 2833 "Parser.C"
    break;

  case 150: /* Formula: AtomicEqFormula  */
#line 686 "epddl.y"
                    { (yyval.formula_) = new AtmEqFormula((yyvsp[0].atomiceqformula_)); }
#line 2839 "Parser.C"
    break;

  case 151: /* Formula: _KW_true  */
#line 687 "epddl.y"
             { (yyval.formula_) = new TrueFormula(); }
#line 2845 "Parser.C"
    break;

  case 152: /* Formula: _KW_false  */
#line 688 "epddl.y"
              { (yyval.formula_) = new FalseFormula(); }
#line 2851 "Parser.C"
    break;

  case 153: /* Formula: _LPAREN Formula _RPAREN  */
#line 689 "epddl.y"
                            { (yyval.formula_) = (yyvsp[-1].formula_); }
#line 2857 "Parser.C"
    break;

  case 154: /* ListFormula: Formula  */
#line 691 "epddl.y"
                      { (yyval.listformula_) = new ListFormula(); (yyval.listformula_)->push_back((yyvsp[0].formula_)); }
#line 2863 "Parser.C"
    break;

  case 155: /* ListFormula: Formula ListFormula  */
#line 692 "epddl.y"
                        { (yyvsp[0].listformula_)->push_back((yyvsp[-1].formula_)); (yyval.listformula_) = (yyvsp[0].listformula_); }
#line 2869 "Parser.C"
    break;

  case 156: /* AtomicFormula: _LPAREN PredicateName ListMetaTerm _RPAREN  */
#line 694 "epddl.y"
                                                           { (yyval.atomicformula_) = new Predicate((yyvsp[-2].predicatename_), (yyvsp[-1].listmetaterm_)); }
#line 2875 "Parser.C"
    break;

  case 157: /* AtomicEqFormula: _LPAREN _EQ Term Term _RPAREN  */
#line 696 "epddl.y"
                                                { (yyval.atomiceqformula_) = new EqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 2881 "Parser.C"
    break;

  case 158: /* FormulaOrEmpty: Formula  */
#line 698 "epddl.y"
                         { (yyval.formulaorempty_) = new NonTrivialFormula((yyvsp[0].formula_)); }
#line 2887 "Parser.C"
    break;

  case 159: /* FormulaOrEmpty: TrivialDef  */
#line 699 "epddl.y"
               { (yyval.formulaorempty_) = new TrivialFormula((yyvsp[0].trivialdef_)); }
#line 2893 "Parser.C"
    break;

  case 160: /* MetaTerm: Term  */
#line 701 "epddl.y"
                { (yyval.metaterm_) = new EPDDLMetaTerm((yyvsp[0].term_)); }
#line 2899 "Parser.C"
    break;

  case 161: /* MetaTerm: AnonVarAgent  */
#line 702 "epddl.y"
                 { (yyval.metaterm_) = new EPDDLMetaTermAnonVar((yyvsp[0].anonvaragent_)); }
#line 2905 "Parser.C"
    break;

  case 162: /* ListMetaTerm: %empty  */
#line 704 "epddl.y"
                           { (yyval.listmetaterm_) = new ListMetaTerm(); }
#line 2911 "Parser.C"
    break;

  case 163: /* ListMetaTerm: ListMetaTerm MetaTerm  */
#line 705 "epddl.y"
                          { (yyvsp[-1].listmetaterm_)->push_back((yyvsp[0].metaterm_)); (yyval.listmetaterm_) = (yyvsp[-1].listmetaterm_); }
#line 2917 "Parser.C"
    break;

  case 164: /* Term: GroundTerm  */
#line 707 "epddl.y"
                  { (yyval.term_) = new EPDDLGroundTerm((yyvsp[0].groundterm_)); }
#line 2923 "Parser.C"
    break;

  case 165: /* Term: Variable  */
#line 708 "epddl.y"
             { (yyval.term_) = new EPDDLTermVar((yyvsp[0]._variable)); }
#line 2929 "Parser.C"
    break;

  case 166: /* ListTerm: %empty  */
#line 710 "epddl.y"
                       { (yyval.listterm_) = new ListTerm(); }
#line 2935 "Parser.C"
    break;

  case 167: /* ListTerm: ListTerm Term  */
#line 711 "epddl.y"
                  { (yyvsp[-1].listterm_)->push_back((yyvsp[0].term_)); (yyval.listterm_) = (yyvsp[-1].listterm_); }
#line 2941 "Parser.C"
    break;

  case 168: /* GroundTerm: Name  */
#line 713 "epddl.y"
                  { (yyval.groundterm_) = new EPDDLGroundTermName((yyvsp[0]._name)); }
#line 2947 "Parser.C"
    break;

  case 169: /* GroundTerm: AgentName  */
#line 714 "epddl.y"
              { (yyval.groundterm_) = new EPDDLGroundTermAgName((yyvsp[0]._agentname)); }
#line 2953 "Parser.C"
    break;

  case 170: /* ListGroundTerm: %empty  */
#line 716 "epddl.y"
                             { (yyval.listgroundterm_) = new ListGroundTerm(); }
#line 2959 "Parser.C"
    break;

  case 171: /* ListGroundTerm: ListGroundTerm GroundTerm  */
#line 717 "epddl.y"
                              { (yyvsp[-1].listgroundterm_)->push_back((yyvsp[0].groundterm_)); (yyval.listgroundterm_) = (yyvsp[-1].listgroundterm_); }
#line 2965 "Parser.C"
    break;

  case 172: /* Modality: SingleModality  */
#line 719 "epddl.y"
                          { (yyval.modality_) = new EPDDLLabeledMod((yyvsp[0].singlemodality_)); }
#line 2971 "Parser.C"
    break;

  case 173: /* Modality: GroupModality  */
#line 720 "epddl.y"
                  { (yyval.modality_) = new EPDDLLabeledGroupMod((yyvsp[0].groupmodality_)); }
#line 2977 "Parser.C"
    break;

  case 174: /* SingleModality: _LBRACK ModalityLabel ModalityAgent _RBRACK  */
#line 722 "epddl.y"
                                                             { (yyval.singlemodality_) = new LabBoxMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2983 "Parser.C"
    break;

  case 175: /* SingleModality: _LT ModalityLabel ModalityAgent _GT  */
#line 723 "epddl.y"
                                        { (yyval.singlemodality_) = new LabDiamondMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2989 "Parser.C"
    break;

  case 176: /* GroupModality: _LBRACK ModalityLabel ModalityAgentGroup _RBRACK  */
#line 725 "epddl.y"
                                                                 { (yyval.groupmodality_) = new LabBoxGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2995 "Parser.C"
    break;

  case 177: /* GroupModality: _LT ModalityLabel ModalityAgentGroup _GT  */
#line 726 "epddl.y"
                                             { (yyval.groupmodality_) = new LabDiamondGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 3001 "Parser.C"
    break;

  case 178: /* ModalityLabel: ModalityName  */
#line 728 "epddl.y"
                             { (yyval.modalitylabel_) = new ModLabel((yyvsp[0]._modalityname)); }
#line 3007 "Parser.C"
    break;

  case 179: /* ModalityLabel: %empty  */
#line 729 "epddl.y"
                { (yyval.modalitylabel_) = new EmptyModLabel(); }
#line 3013 "Parser.C"
    break;

  case 180: /* KnowsWhether: _LBRACK ModalityName AgentName _RBRACK  */
#line 731 "epddl.y"
                                                      { (yyval.knowswhether_) = new KnowsWhetherMod((yyvsp[-2]._modalityname), (yyvsp[-1]._agentname)); }
#line 3019 "Parser.C"
    break;

  case 181: /* Literal: AtomicFormula  */
#line 733 "epddl.y"
                        { (yyval.literal_) = new PosLiteral((yyvsp[0].atomicformula_)); }
#line 3025 "Parser.C"
    break;

  case 182: /* Literal: _LPAREN _KW_not AtomicFormula _RPAREN  */
#line 734 "epddl.y"
                                          { (yyval.literal_) = new NegLiteral((yyvsp[-1].atomicformula_)); }
#line 3031 "Parser.C"
    break;

  case 183: /* ListLiteral: %empty  */
#line 736 "epddl.y"
                          { (yyval.listliteral_) = new ListLiteral(); }
#line 3037 "Parser.C"
    break;

  case 184: /* ListLiteral: ListLiteral Literal  */
#line 737 "epddl.y"
                        { (yyvsp[-1].listliteral_)->push_back((yyvsp[0].literal_)); (yyval.listliteral_) = (yyvsp[-1].listliteral_); }
#line 3043 "Parser.C"
    break;

  case 185: /* ConditionFormula: _LPAREN _KW_and Condition ListCondition _RPAREN  */
#line 739 "epddl.y"
                                                                   { std::reverse((yyvsp[-1].listcondition_)->begin(),(yyvsp[-1].listcondition_)->end()) ;(yyval.conditionformula_) = new AndCondFomula((yyvsp[-2].condition_), (yyvsp[-1].listcondition_)); }
#line 3049 "Parser.C"
    break;

  case 186: /* ConditionFormula: Condition  */
#line 740 "epddl.y"
              { (yyval.conditionformula_) = new CondFomula((yyvsp[0].condition_)); }
#line 3055 "Parser.C"
    break;

  case 187: /* Condition: AtomicCondition  */
#line 742 "epddl.y"
                            { (yyval.condition_) = new AtmCond((yyvsp[0].atomiccondition_)); }
#line 3061 "Parser.C"
    break;

  case 188: /* Condition: _LPAREN _KW_not AtomicCondition _RPAREN  */
#line 743 "epddl.y"
                                            { (yyval.condition_) = new NotAtmCond((yyvsp[-1].atomiccondition_)); }
#line 3067 "Parser.C"
    break;

  case 189: /* ListCondition: Condition  */
#line 745 "epddl.y"
                          { (yyval.listcondition_) = new ListCondition(); (yyval.listcondition_)->push_back((yyvsp[0].condition_)); }
#line 3073 "Parser.C"
    break;

  case 190: /* ListCondition: Condition ListCondition  */
#line 746 "epddl.y"
                            { (yyvsp[0].listcondition_)->push_back((yyvsp[-1].condition_)); (yyval.listcondition_) = (yyvsp[0].listcondition_); }
#line 3079 "Parser.C"
    break;

  case 191: /* AtomicCondition: _LPAREN PredicateName ListTerm _RPAREN  */
#line 748 "epddl.y"
                                                         { (yyval.atomiccondition_) = new AtmCondPredicate((yyvsp[-2].predicatename_), (yyvsp[-1].listterm_)); }
#line 3085 "Parser.C"
    break;

  case 192: /* AtomicCondition: _LPAREN _EQ Term Term _RPAREN  */
#line 749 "epddl.y"
                                  { (yyval.atomiccondition_) = new AtmCondEqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 3091 "Parser.C"
    break;

  case 193: /* PredicateFormula: _LPAREN _KW_imply PredicateFormula PredicateFormula _RPAREN  */
#line 751 "epddl.y"
                                                                               { (yyval.predicateformula_) = new ImplyPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].predicateformula_)); }
#line 3097 "Parser.C"
    break;

  case 194: /* PredicateFormula: _LPAREN _KW_or PredicateFormula ListPredicateFormula _RPAREN  */
#line 752 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new OrPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3103 "Parser.C"
    break;

  case 195: /* PredicateFormula: _LPAREN _KW_and PredicateFormula ListPredicateFormula _RPAREN  */
#line 753 "epddl.y"
                                                                  { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new AndPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3109 "Parser.C"
    break;

  case 196: /* PredicateFormula: _LPAREN _KW_not PredicateFormula _RPAREN  */
#line 754 "epddl.y"
                                             { (yyval.predicateformula_) = new NotPredFormula((yyvsp[-1].predicateformula_)); }
#line 3115 "Parser.C"
    break;

  case 197: /* PredicateFormula: _LPAREN PredicateName ListGroundTerm _RPAREN  */
#line 755 "epddl.y"
                                                 { (yyval.predicateformula_) = new AtmPredFormula((yyvsp[-2].predicatename_), (yyvsp[-1].listgroundterm_)); }
#line 3121 "Parser.C"
    break;

  case 198: /* ListPredicateFormula: PredicateFormula  */
#line 757 "epddl.y"
                                        { (yyval.listpredicateformula_) = new ListPredicateFormula(); (yyval.listpredicateformula_)->push_back((yyvsp[0].predicateformula_)); }
#line 3127 "Parser.C"
    break;

  case 199: /* ListPredicateFormula: PredicateFormula ListPredicateFormula  */
#line 758 "epddl.y"
                                          { (yyvsp[0].listpredicateformula_)->push_back((yyvsp[-1].predicateformula_)); (yyval.listpredicateformula_) = (yyvsp[0].listpredicateformula_); }
#line 3133 "Parser.C"
    break;

  case 200: /* GenericName: Name  */
#line 760 "epddl.y"
                   { (yyval.genericname_) = new EPDDLGenericNameObj((yyvsp[0]._name)); }
#line 3139 "Parser.C"
    break;

  case 201: /* GenericName: AgentName  */
#line 761 "epddl.y"
              { (yyval.genericname_) = new EPDDLGenericNameAg((yyvsp[0]._agentname)); }
#line 3145 "Parser.C"
    break;

  case 202: /* ListGenericName: %empty  */
#line 763 "epddl.y"
                              { (yyval.listgenericname_) = new ListGenericName(); }
#line 3151 "Parser.C"
    break;

  case 203: /* ListGenericName: ListGenericName GenericName  */
#line 764 "epddl.y"
                                { (yyvsp[-1].listgenericname_)->push_back((yyvsp[0].genericname_)); (yyval.listgenericname_) = (yyvsp[-1].listgenericname_); }
#line 3157 "Parser.C"
    break;

  case 204: /* TypedIdentList: ListName  */
#line 766 "epddl.y"
                          { std::reverse((yyvsp[0].listname_)->begin(),(yyvsp[0].listname_)->end()) ;(yyval.typedidentlist_) = new IdList((yyvsp[0].listname_)); }
#line 3163 "Parser.C"
    break;

  case 205: /* TypedIdentList: Name ListName _MINUS Type TypedIdentList  */
#line 767 "epddl.y"
                                             { std::reverse((yyvsp[-3].listname_)->begin(),(yyvsp[-3].listname_)->end()) ;(yyval.typedidentlist_) = new TypedIdList((yyvsp[-4]._name), (yyvsp[-3].listname_), (yyvsp[-1].type_), (yyvsp[0].typedidentlist_)); }
#line 3169 "Parser.C"
    break;

  case 206: /* TypedAgentList: ListAgentName  */
#line 769 "epddl.y"
                               { std::reverse((yyvsp[0].listagentname_)->begin(),(yyvsp[0].listagentname_)->end()) ;(yyval.typedagentlist_) = new AgList((yyvsp[0].listagentname_)); }
#line 3175 "Parser.C"
    break;

  case 207: /* TypedAgentList: AgentName ListAgentName _MINUS Type TypedAgentList  */
#line 770 "epddl.y"
                                                       { std::reverse((yyvsp[-3].listagentname_)->begin(),(yyvsp[-3].listagentname_)->end()) ;(yyval.typedagentlist_) = new TypedAgList((yyvsp[-4]._agentname), (yyvsp[-3].listagentname_), (yyvsp[-1].type_), (yyvsp[0].typedagentlist_)); }
#line 3181 "Parser.C"
    break;

  case 208: /* TypedVariableList: ListVariable  */
#line 772 "epddl.y"
                                 { std::reverse((yyvsp[0].listvariable_)->begin(),(yyvsp[0].listvariable_)->end()) ;(yyval.typedvariablelist_) = new VarList((yyvsp[0].listvariable_)); }
#line 3187 "Parser.C"
    break;

  case 209: /* TypedVariableList: Variable ListVariable _MINUS Type TypedVariableList  */
#line 773 "epddl.y"
                                                        { std::reverse((yyvsp[-3].listvariable_)->begin(),(yyvsp[-3].listvariable_)->end()) ;(yyval.typedvariablelist_) = new TypedVarList((yyvsp[-4]._variable), (yyvsp[-3].listvariable_), (yyvsp[-1].type_), (yyvsp[0].typedvariablelist_)); }
#line 3193 "Parser.C"
    break;

  case 210: /* PredicateName: Name  */
#line 775 "epddl.y"
                     { (yyval.predicatename_) = new EPDDLPredicate((yyvsp[0]._name)); }
#line 3199 "Parser.C"
    break;

  case 211: /* ModalityAgent: AgentName  */
#line 777 "epddl.y"
                          { (yyval.modalityagent_) = new EPDDLModAgent((yyvsp[0]._agentname)); }
#line 3205 "Parser.C"
    break;

  case 212: /* ModalityAgent: Variable  */
#line 778 "epddl.y"
             { (yyval.modalityagent_) = new EPDDLModVarAgent((yyvsp[0]._variable)); }
#line 3211 "Parser.C"
    break;

  case 213: /* ModalityAgent: AnonVarAgent  */
#line 779 "epddl.y"
                 { (yyval.modalityagent_) = new EPDDLModAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 3217 "Parser.C"
    break;

  case 214: /* ModalityAgent: AllAgents  */
#line 780 "epddl.y"
              { (yyval.modalityagent_) = new EPDDLModAllAgents((yyvsp[0].allagents_)); }
#line 3223 "Parser.C"
    break;

  case 215: /* ListModalityAgent: ModalityAgent  */
#line 782 "epddl.y"
                                  { (yyval.listmodalityagent_) = new ListModalityAgent(); (yyval.listmodalityagent_)->push_back((yyvsp[0].modalityagent_)); }
#line 3229 "Parser.C"
    break;

  case 216: /* ListModalityAgent: ModalityAgent ListModalityAgent  */
#line 783 "epddl.y"
                                    { (yyvsp[0].listmodalityagent_)->push_back((yyvsp[-1].modalityagent_)); (yyval.listmodalityagent_) = (yyvsp[0].listmodalityagent_); }
#line 3235 "Parser.C"
    break;

  case 217: /* ModalityAgentGroup: ModalityAgent ListModalityAgent  */
#line 785 "epddl.y"
                                                     { std::reverse((yyvsp[0].listmodalityagent_)->begin(),(yyvsp[0].listmodalityagent_)->end()) ;(yyval.modalityagentgroup_) = new EPDDLModAgList((yyvsp[-1].modalityagent_), (yyvsp[0].listmodalityagent_)); }
#line 3241 "Parser.C"
    break;

  case 218: /* AgentGroupName: AgentName  */
#line 787 "epddl.y"
                           { (yyval.agentgroupname_) = new EPDDLSingleAgentGroup((yyvsp[0]._agentname)); }
#line 3247 "Parser.C"
    break;

  case 219: /* AgentGroupName: AllAgents  */
#line 788 "epddl.y"
              { (yyval.agentgroupname_) = new EPDDLAllAgentsGroup((yyvsp[0].allagents_)); }
#line 3253 "Parser.C"
    break;

  case 220: /* ObservingAgentGroup: AgentName  */
#line 790 "epddl.y"
                                { (yyval.observingagentgroup_) = new EPDDLObsAgentGroup((yyvsp[0]._agentname)); }
#line 3259 "Parser.C"
    break;

  case 221: /* ListObservingAgentGroup: ObservingAgentGroup  */
#line 792 "epddl.y"
                                              { (yyval.listobservingagentgroup_) = new ListObservingAgentGroup(); (yyval.listobservingagentgroup_)->push_back((yyvsp[0].observingagentgroup_)); }
#line 3265 "Parser.C"
    break;

  case 222: /* ListObservingAgentGroup: ObservingAgentGroup ListObservingAgentGroup  */
#line 793 "epddl.y"
                                                { (yyvsp[0].listobservingagentgroup_)->push_back((yyvsp[-1].observingagentgroup_)); (yyval.listobservingagentgroup_) = (yyvsp[0].listobservingagentgroup_); }
#line 3271 "Parser.C"
    break;

  case 223: /* ObservingAgent: AgentName  */
#line 795 "epddl.y"
                           { (yyval.observingagent_) = new EPDDLObsAgent((yyvsp[0]._agentname)); }
#line 3277 "Parser.C"
    break;

  case 224: /* ObservingAgent: AllAgents  */
#line 796 "epddl.y"
              { (yyval.observingagent_) = new EPDDLObsAllAgents((yyvsp[0].allagents_)); }
#line 3283 "Parser.C"
    break;

  case 225: /* ObservingAgent: Variable  */
#line 797 "epddl.y"
             { (yyval.observingagent_) = new EPDDLObsVarAgent((yyvsp[0]._variable)); }
#line 3289 "Parser.C"
    break;

  case 226: /* ObservingAgent: AnonVarAgent  */
#line 798 "epddl.y"
                 { (yyval.observingagent_) = new EPDDLObsAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 3295 "Parser.C"
    break;

  case 227: /* AgentGroup: AgentGroupName  */
#line 800 "epddl.y"
                            { (yyval.agentgroup_) = new EPDDLAgentGroup((yyvsp[0].agentgroupname_)); }
#line 3301 "Parser.C"
    break;

  case 228: /* AgentGroup: _LBRACE AgentName ListAgentName _RBRACE  */
#line 801 "epddl.y"
                                            { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentgroup_) = new EPDDLAgentNameGroup((yyvsp[-2]._agentname), (yyvsp[-1].listagentname_)); }
#line 3307 "Parser.C"
    break;

  case 229: /* AllAgents: _KW_All  */
#line 803 "epddl.y"
                    { (yyval.allagents_) = new EPDDLAllAgents(); }
#line 3313 "Parser.C"
    break;

  case 230: /* AnonVarAgent: _SYMB_39  */
#line 805 "epddl.y"
                        { (yyval.anonvaragent_) = new EPDDLAnonVarAgent(); }
#line 3319 "Parser.C"
    break;

  case 231: /* Parameter: _LPAREN Variable _DCOLON ParameterValue _RPAREN  */
#line 807 "epddl.y"
                                                            { (yyval.parameter_) = new EPDDLParam((yyvsp[-3]._variable), (yyvsp[-1].parametervalue_)); }
#line 3325 "Parser.C"
    break;

  case 232: /* ListParameter: %empty  */
#line 809 "epddl.y"
                            { (yyval.listparameter_) = new ListParameter(); }
#line 3331 "Parser.C"
    break;

  case 233: /* ListParameter: ListParameter Parameter  */
#line 810 "epddl.y"
                            { (yyvsp[-1].listparameter_)->push_back((yyvsp[0].parameter_)); (yyval.listparameter_) = (yyvsp[-1].listparameter_); }
#line 3337 "Parser.C"
    break;

  case 234: /* ParameterValue: Term  */
#line 812 "epddl.y"
                      { (yyval.parametervalue_) = new EPDDLTermParam((yyvsp[0].term_)); }
#line 3343 "Parser.C"
    break;

  case 235: /* ParameterValue: Formula  */
#line 813 "epddl.y"
            { (yyval.parametervalue_) = new EPDDLFormulaParam((yyvsp[0].formula_)); }
#line 3349 "Parser.C"
    break;

  case 236: /* ParameterValue: ListPostParameterValue  */
#line 814 "epddl.y"
                           { std::reverse((yyvsp[0].listpostparametervalue_)->begin(),(yyvsp[0].listpostparametervalue_)->end()) ;(yyval.parametervalue_) = new EPDDLPostParam((yyvsp[0].listpostparametervalue_)); }
#line 3355 "Parser.C"
    break;

  case 237: /* PostParameterValue: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN ListLiteralPostcondition _RPAREN  */
#line 816 "epddl.y"
                                                                                                           { std::reverse((yyvsp[-1].listliteralpostcondition_)->begin(),(yyvsp[-1].listliteralpostcondition_)->end()) ;(yyval.postparametervalue_) = new PostParamForall((yyvsp[-3].typedvariablelist_), (yyvsp[-1].listliteralpostcondition_)); }
#line 3361 "Parser.C"
    break;

  case 238: /* PostParameterValue: LiteralPostcondition  */
#line 817 "epddl.y"
                         { (yyval.postparametervalue_) = new PostParamLiteral((yyvsp[0].literalpostcondition_)); }
#line 3367 "Parser.C"
    break;

  case 239: /* ListPostParameterValue: PostParameterValue  */
#line 819 "epddl.y"
                                            { (yyval.listpostparametervalue_) = new ListPostParameterValue(); (yyval.listpostparametervalue_)->push_back((yyvsp[0].postparametervalue_)); }
#line 3373 "Parser.C"
    break;

  case 240: /* ListPostParameterValue: PostParameterValue ListPostParameterValue  */
#line 820 "epddl.y"
                                              { (yyvsp[0].listpostparametervalue_)->push_back((yyvsp[-1].postparametervalue_)); (yyval.listpostparametervalue_) = (yyvsp[0].listpostparametervalue_); }
#line 3379 "Parser.C"
    break;

  case 241: /* Type: Name  */
#line 822 "epddl.y"
            { (yyval.type_) = new EPDDLTypeName((yyvsp[0]._name)); }
#line 3385 "Parser.C"
    break;

  case 242: /* Type: ReservedType  */
#line 823 "epddl.y"
                 { (yyval.type_) = new EPDDLResType((yyvsp[0].reservedtype_)); }
#line 3391 "Parser.C"
    break;

  case 243: /* ReservedType: _KW_agent  */
#line 825 "epddl.y"
                         { (yyval.reservedtype_) = new ResAgentType(); }
#line 3397 "Parser.C"
    break;

  case 244: /* ReservedType: _KW_predicate  */
#line 826 "epddl.y"
                  { (yyval.reservedtype_) = new PredicateType(); }
#line 3403 "Parser.C"
    break;

  case 245: /* ReservedType: _KW_literal  */
#line 827 "epddl.y"
                { (yyval.reservedtype_) = new LiteralType(); }
#line 3409 "Parser.C"
    break;

  case 246: /* ReservedType: _SYMB_41  */
#line 828 "epddl.y"
             { (yyval.reservedtype_) = new PredFormulaType(); }
#line 3415 "Parser.C"
    break;

  case 247: /* ReservedType: _KW_formula  */
#line 829 "epddl.y"
                { (yyval.reservedtype_) = new FormulaType(); }
#line 3421 "Parser.C"
    break;

  case 248: /* ReservedType: _KW_postcondition  */
#line 830 "epddl.y"
                      { (yyval.reservedtype_) = new PostconditionType(); }
#line 3427 "Parser.C"
    break;

  case 249: /* DomainName: Name  */
#line 832 "epddl.y"
                  { (yyval.domainname_) = new EPDDLDomainName((yyvsp[0]._name)); }
#line 3433 "Parser.C"
    break;

  case 250: /* LibraryName: Name  */
#line 834 "epddl.y"
                   { (yyval.libraryname_) = new EPDDLLibraryName((yyvsp[0]._name)); }
#line 3439 "Parser.C"
    break;

  case 251: /* ListLibraryName: LibraryName  */
#line 836 "epddl.y"
                              { (yyval.listlibraryname_) = new ListLibraryName(); (yyval.listlibraryname_)->push_back((yyvsp[0].libraryname_)); }
#line 3445 "Parser.C"
    break;

  case 252: /* ListLibraryName: LibraryName ListLibraryName  */
#line 837 "epddl.y"
                                { (yyvsp[0].listlibraryname_)->push_back((yyvsp[-1].libraryname_)); (yyval.listlibraryname_) = (yyvsp[0].listlibraryname_); }
#line 3451 "Parser.C"
    break;

  case 253: /* ProblemName: Name  */
#line 839 "epddl.y"
                   { (yyval.problemname_) = new EPDDLProblemName((yyvsp[0]._name)); }
#line 3457 "Parser.C"
    break;

  case 254: /* ActionName: Name  */
#line 841 "epddl.y"
                  { (yyval.actionname_) = new EPDDLActionName((yyvsp[0]._name)); }
#line 3463 "Parser.C"
    break;

  case 255: /* ActionTypeName: Name  */
#line 843 "epddl.y"
                      { (yyval.actiontypename_) = new EPDDLActTypeName((yyvsp[0]._name)); }
#line 3469 "Parser.C"
    break;

  case 256: /* EventName: Name  */
#line 845 "epddl.y"
                 { (yyval.eventname_) = new EPDDLEventName((yyvsp[0]._name)); }
#line 3475 "Parser.C"
    break;

  case 257: /* ListEventName: EventName  */
#line 847 "epddl.y"
                          { (yyval.listeventname_) = new ListEventName(); (yyval.listeventname_)->push_back((yyvsp[0].eventname_)); }
#line 3481 "Parser.C"
    break;

  case 258: /* ListEventName: EventName ListEventName  */
#line 848 "epddl.y"
                            { (yyvsp[0].listeventname_)->push_back((yyvsp[-1].eventname_)); (yyval.listeventname_) = (yyvsp[0].listeventname_); }
#line 3487 "Parser.C"
    break;

  case 259: /* ModelName: Name  */
#line 850 "epddl.y"
                 { (yyval.modelname_) = new EPDDLModelName((yyvsp[0]._name)); }
#line 3493 "Parser.C"
    break;

  case 260: /* WorldName: Name  */
#line 852 "epddl.y"
                 { (yyval.worldname_) = new EPDDLWorldName((yyvsp[0]._name)); }
#line 3499 "Parser.C"
    break;

  case 261: /* ListWorldName: WorldName  */
#line 854 "epddl.y"
                          { (yyval.listworldname_) = new ListWorldName(); (yyval.listworldname_)->push_back((yyvsp[0].worldname_)); }
#line 3505 "Parser.C"
    break;

  case 262: /* ListWorldName: WorldName ListWorldName  */
#line 855 "epddl.y"
                            { (yyvsp[0].listworldname_)->push_back((yyvsp[-1].worldname_)); (yyval.listworldname_) = (yyvsp[0].listworldname_); }
#line 3511 "Parser.C"
    break;

  case 263: /* RequireKey: _SYMB_42  */
#line 857 "epddl.y"
                      { (yyval.requirekey_) = new EPDDLReqDel(); }
#line 3517 "Parser.C"
    break;

  case 264: /* RequireKey: _SYMB_43  */
#line 858 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqTyping(); }
#line 3523 "Parser.C"
    break;

  case 265: /* RequireKey: _SYMB_44  */
#line 859 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqEquality(); }
#line 3529 "Parser.C"
    break;

  case 266: /* RequireKey: _SYMB_45  */
#line 860 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqParamList(); }
#line 3535 "Parser.C"
    break;

  case 267: /* RequireKey: _SYMB_46  */
#line 861 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqExiForm(); }
#line 3541 "Parser.C"
    break;

  case 268: /* RequireKey: _SYMB_47  */
#line 862 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqUniForm(); }
#line 3547 "Parser.C"
    break;

  case 269: /* RequireKey: _SYMB_48  */
#line 863 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqUniPost(); }
#line 3553 "Parser.C"
    break;

  case 270: /* RequireKey: _SYMB_49  */
#line 864 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPre(); }
#line 3559 "Parser.C"
    break;

  case 271: /* RequireKey: _SYMB_50  */
#line 865 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPost(); }
#line 3565 "Parser.C"
    break;

  case 272: /* RequireKey: _SYMB_6  */
#line 866 "epddl.y"
            { (yyval.requirekey_) = new EPDDLReqModalities(); }
#line 3571 "Parser.C"
    break;

  case 273: /* RequireKey: _SYMB_51  */
#line 867 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOnticChange(); }
#line 3577 "Parser.C"
    break;

  case 274: /* RequireKey: _SYMB_52  */
#line 868 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqCK(); }
#line 3583 "Parser.C"
    break;

  case 275: /* RequireKey: _SYMB_53  */
#line 869 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqDynCK(); }
#line 3589 "Parser.C"
    break;

  case 276: /* RequireKey: _SYMB_54  */
#line 870 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqMAStar(); }
#line 3595 "Parser.C"
    break;

  case 277: /* RequireKey: _SYMB_55  */
#line 871 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOntic(); }
#line 3601 "Parser.C"
    break;

  case 278: /* RequireKey: _SYMB_56  */
#line 872 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqSensing(); }
#line 3607 "Parser.C"
    break;

  case 279: /* RequireKey: _SYMB_57  */
#line 873 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqAnnouncement(); }
#line 3613 "Parser.C"
    break;

  case 280: /* RequireKey: _SYMB_58  */
#line 874 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqFTheory(); }
#line 3619 "Parser.C"
    break;

  case 281: /* RequireKey: _LPAREN _SYMB_59 _INTEGER_ _RPAREN  */
#line 875 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPreDepth((yyvsp[-1]._int)); }
#line 3625 "Parser.C"
    break;

  case 282: /* RequireKey: _LPAREN _SYMB_60 _INTEGER_ _RPAREN  */
#line 876 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPostDepth((yyvsp[-1]._int)); }
#line 3631 "Parser.C"
    break;

  case 283: /* RequireKey: _LPAREN _SYMB_61 _INTEGER_ _RPAREN  */
#line 877 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxDepth((yyvsp[-1]._int)); }
#line 3637 "Parser.C"
    break;

  case 284: /* ListRequireKey: RequireKey  */
#line 879 "epddl.y"
                            { (yyval.listrequirekey_) = new ListRequireKey(); (yyval.listrequirekey_)->push_back((yyvsp[0].requirekey_)); }
#line 3643 "Parser.C"
    break;

  case 285: /* ListRequireKey: RequireKey ListRequireKey  */
#line 880 "epddl.y"
                              { (yyvsp[0].listrequirekey_)->push_back((yyvsp[-1].requirekey_)); (yyval.listrequirekey_) = (yyvsp[0].listrequirekey_); }
#line 3649 "Parser.C"
    break;

  case 286: /* TrivialDef: _LPAREN _RPAREN  */
#line 882 "epddl.y"
                             { (yyval.trivialdef_) = new EPDDLTrivialDef(); }
#line 3655 "Parser.C"
    break;

  case 287: /* ListName: %empty  */
#line 884 "epddl.y"
                       { (yyval.listname_) = new ListName(); }
#line 3661 "Parser.C"
    break;

  case 288: /* ListName: Name ListName  */
#line 885 "epddl.y"
                  { (yyvsp[0].listname_)->push_back((yyvsp[-1]._name)); (yyval.listname_) = (yyvsp[0].listname_); }
#line 3667 "Parser.C"
    break;

  case 289: /* ListAgentName: %empty  */
#line 887 "epddl.y"
                            { (yyval.listagentname_) = new ListAgentName(); }
#line 3673 "Parser.C"
    break;

  case 290: /* ListAgentName: AgentName ListAgentName  */
#line 888 "epddl.y"
                            { (yyvsp[0].listagentname_)->push_back((yyvsp[-1]._agentname)); (yyval.listagentname_) = (yyvsp[0].listagentname_); }
#line 3679 "Parser.C"
    break;

  case 291: /* ListModalityName: %empty  */
#line 890 "epddl.y"
                               { (yyval.listmodalityname_) = new ListModalityName(); }
#line 3685 "Parser.C"
    break;

  case 292: /* ListModalityName: ModalityName ListModalityName  */
#line 891 "epddl.y"
                                  { (yyvsp[0].listmodalityname_)->push_back((yyvsp[-1]._modalityname)); (yyval.listmodalityname_) = (yyvsp[0].listmodalityname_); }
#line 3691 "Parser.C"
    break;

  case 293: /* ListVariable: %empty  */
#line 893 "epddl.y"
                           { (yyval.listvariable_) = new ListVariable(); }
#line 3697 "Parser.C"
    break;

  case 294: /* ListVariable: Variable ListVariable  */
#line 894 "epddl.y"
                          { (yyvsp[0].listvariable_)->push_back((yyvsp[-1]._variable)); (yyval.listvariable_) = (yyvsp[0].listvariable_); }
#line 3703 "Parser.C"
    break;

  case 295: /* Name: T_Name  */
#line 896 "epddl.y"
              { (yyval._name) = new Name((yyvsp[0]._string), (yyloc).first_line); }
#line 3709 "Parser.C"
    break;

  case 296: /* AgentName: T_AgentName  */
#line 898 "epddl.y"
                        { (yyval._agentname) = new AgentName((yyvsp[0]._string), (yyloc).first_line); }
#line 3715 "Parser.C"
    break;

  case 297: /* ModalityName: T_ModalityName  */
#line 900 "epddl.y"
                              { (yyval._modalityname) = new ModalityName((yyvsp[0]._string), (yyloc).first_line); }
#line 3721 "Parser.C"
    break;

  case 298: /* Variable: T_Variable  */
#line 902 "epddl.y"
                      { (yyval._variable) = new Variable((yyvsp[0]._string), (yyloc).first_line); }
#line 3727 "Parser.C"
    break;


#line 3731 "Parser.C"

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

#line 905 "epddl.y"



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



