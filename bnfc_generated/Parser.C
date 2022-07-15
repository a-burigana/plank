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
  YYSYMBOL__SYMB_8 = 7,                    /* _SYMB_8  */
  YYSYMBOL__SYMB_11 = 8,                   /* _SYMB_11  */
  YYSYMBOL__SYMB_2 = 9,                    /* _SYMB_2  */
  YYSYMBOL__SYMB_22 = 10,                  /* _SYMB_22  */
  YYSYMBOL__SYMB_21 = 11,                  /* _SYMB_21  */
  YYSYMBOL__SYMB_53 = 12,                  /* _SYMB_53  */
  YYSYMBOL__SYMB_42 = 13,                  /* _SYMB_42  */
  YYSYMBOL__SYMB_17 = 14,                  /* _SYMB_17  */
  YYSYMBOL__SYMB_47 = 15,                  /* _SYMB_47  */
  YYSYMBOL__SYMB_20 = 16,                  /* _SYMB_20  */
  YYSYMBOL__SYMB_54 = 17,                  /* _SYMB_54  */
  YYSYMBOL__SYMB_44 = 18,                  /* _SYMB_44  */
  YYSYMBOL__SYMB_18 = 19,                  /* _SYMB_18  */
  YYSYMBOL__SYMB_15 = 20,                  /* _SYMB_15  */
  YYSYMBOL__SYMB_48 = 21,                  /* _SYMB_48  */
  YYSYMBOL__SYMB_26 = 22,                  /* _SYMB_26  */
  YYSYMBOL__SYMB_14 = 23,                  /* _SYMB_14  */
  YYSYMBOL__SYMB_34 = 24,                  /* _SYMB_34  */
  YYSYMBOL__SYMB_27 = 25,                  /* _SYMB_27  */
  YYSYMBOL__SYMB_55 = 26,                  /* _SYMB_55  */
  YYSYMBOL__SYMB_58 = 27,                  /* _SYMB_58  */
  YYSYMBOL__SYMB_59 = 28,                  /* _SYMB_59  */
  YYSYMBOL__SYMB_56 = 29,                  /* _SYMB_56  */
  YYSYMBOL__SYMB_57 = 30,                  /* _SYMB_57  */
  YYSYMBOL__SYMB_62 = 31,                  /* _SYMB_62  */
  YYSYMBOL__SYMB_61 = 32,                  /* _SYMB_61  */
  YYSYMBOL__SYMB_60 = 33,                  /* _SYMB_60  */
  YYSYMBOL__SYMB_51 = 34,                  /* _SYMB_51  */
  YYSYMBOL__SYMB_50 = 35,                  /* _SYMB_50  */
  YYSYMBOL__SYMB_6 = 36,                   /* _SYMB_6  */
  YYSYMBOL__SYMB_31 = 37,                  /* _SYMB_31  */
  YYSYMBOL__SYMB_28 = 38,                  /* _SYMB_28  */
  YYSYMBOL__SYMB_46 = 39,                  /* _SYMB_46  */
  YYSYMBOL__SYMB_25 = 40,                  /* _SYMB_25  */
  YYSYMBOL__SYMB_13 = 41,                  /* _SYMB_13  */
  YYSYMBOL__SYMB_7 = 42,                   /* _SYMB_7  */
  YYSYMBOL__SYMB_52 = 43,                  /* _SYMB_52  */
  YYSYMBOL__SYMB_45 = 44,                  /* _SYMB_45  */
  YYSYMBOL__SYMB_9 = 45,                   /* _SYMB_9  */
  YYSYMBOL__SYMB_19 = 46,                  /* _SYMB_19  */
  YYSYMBOL__SYMB_12 = 47,                  /* _SYMB_12  */
  YYSYMBOL__SYMB_5 = 48,                   /* _SYMB_5  */
  YYSYMBOL__SYMB_16 = 49,                  /* _SYMB_16  */
  YYSYMBOL__SYMB_3 = 50,                   /* _SYMB_3  */
  YYSYMBOL__SYMB_4 = 51,                   /* _SYMB_4  */
  YYSYMBOL__SYMB_43 = 52,                  /* _SYMB_43  */
  YYSYMBOL__SYMB_49 = 53,                  /* _SYMB_49  */
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
  YYSYMBOL__KW_announcement = 66,          /* _KW_announcement  */
  YYSYMBOL__KW_as = 67,                    /* _KW_as  */
  YYSYMBOL__KW_define = 68,                /* _KW_define  */
  YYSYMBOL__KW_domain = 69,                /* _KW_domain  */
  YYSYMBOL__KW_false = 70,                 /* _KW_false  */
  YYSYMBOL__KW_forall = 71,                /* _KW_forall  */
  YYSYMBOL__KW_formula = 72,               /* _KW_formula  */
  YYSYMBOL__SYMB_41 = 73,                  /* _SYMB_41  */
  YYSYMBOL__KW_if = 74,                    /* _KW_if  */
  YYSYMBOL__KW_iff = 75,                   /* _KW_iff  */
  YYSYMBOL__KW_imply = 76,                 /* _KW_imply  */
  YYSYMBOL__KW_library = 77,               /* _KW_library  */
  YYSYMBOL__KW_literal = 78,               /* _KW_literal  */
  YYSYMBOL__KW_not = 79,                   /* _KW_not  */
  YYSYMBOL__KW_ontic = 80,                 /* _KW_ontic  */
  YYSYMBOL__KW_or = 81,                    /* _KW_or  */
  YYSYMBOL__KW_otherwise = 82,             /* _KW_otherwise  */
  YYSYMBOL__KW_postcondition = 83,         /* _KW_postcondition  */
  YYSYMBOL__KW_predicate = 84,             /* _KW_predicate  */
  YYSYMBOL__SYMB_40 = 85,                  /* _SYMB_40  */
  YYSYMBOL__KW_problem = 86,               /* _KW_problem  */
  YYSYMBOL__KW_sensing = 87,               /* _KW_sensing  */
  YYSYMBOL__KW_set = 88,                   /* _KW_set  */
  YYSYMBOL__KW_true = 89,                  /* _KW_true  */
  YYSYMBOL__LBRACE = 90,                   /* _LBRACE  */
  YYSYMBOL__RBRACE = 91,                   /* _RBRACE  */
  YYSYMBOL_T_AgentName = 92,               /* T_AgentName  */
  YYSYMBOL_T_ModalityName = 93,            /* T_ModalityName  */
  YYSYMBOL_T_Name = 94,                    /* T_Name  */
  YYSYMBOL_T_ParameterName = 95,           /* T_ParameterName  */
  YYSYMBOL_T_Variable = 96,                /* T_Variable  */
  YYSYMBOL__INTEGER_ = 97,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_MainDef = 99,                   /* MainDef  */
  YYSYMBOL_DomainDef = 100,                /* DomainDef  */
  YYSYMBOL_DomainItemDef = 101,            /* DomainItemDef  */
  YYSYMBOL_ListDomainItemDef = 102,        /* ListDomainItemDef  */
  YYSYMBOL_DomainLibrariesNameDef = 103,   /* DomainLibrariesNameDef  */
  YYSYMBOL_RequireDef = 104,               /* RequireDef  */
  YYSYMBOL_TypesDef = 105,                 /* TypesDef  */
  YYSYMBOL_PredicateListDef = 106,         /* PredicateListDef  */
  YYSYMBOL_PredicateDef = 107,             /* PredicateDef  */
  YYSYMBOL_ListPredicateDef = 108,         /* ListPredicateDef  */
  YYSYMBOL_ModalitiesDef = 109,            /* ModalitiesDef  */
  YYSYMBOL_ObservabilityGroupsDef = 110,   /* ObservabilityGroupsDef  */
  YYSYMBOL_ActionDef = 111,                /* ActionDef  */
  YYSYMBOL_ActionParameterDef = 112,       /* ActionParameterDef  */
  YYSYMBOL_ActionConditionsDef = 113,      /* ActionConditionsDef  */
  YYSYMBOL_ActionTypeSignatureDef = 114,   /* ActionTypeSignatureDef  */
  YYSYMBOL_ActionPreDef = 115,             /* ActionPreDef  */
  YYSYMBOL_Precondition = 116,             /* Precondition  */
  YYSYMBOL_ActionObsDef = 117,             /* ActionObsDef  */
  YYSYMBOL_ObsConditionDef = 118,          /* ObsConditionDef  */
  YYSYMBOL_ListObsConditionDef = 119,      /* ListObsConditionDef  */
  YYSYMBOL_LibraryDef = 120,               /* LibraryDef  */
  YYSYMBOL_LibraryItemDef = 121,           /* LibraryItemDef  */
  YYSYMBOL_ListLibraryItemDef = 122,       /* ListLibraryItemDef  */
  YYSYMBOL_ActionTypeDef = 123,            /* ActionTypeDef  */
  YYSYMBOL_ActionTypeParameterDef = 124,   /* ActionTypeParameterDef  */
  YYSYMBOL_ActionTypeFrameDef = 125,       /* ActionTypeFrameDef  */
  YYSYMBOL_ActionTypeEventsDef = 126,      /* ActionTypeEventsDef  */
  YYSYMBOL_ActionTypeRelDef = 127,         /* ActionTypeRelDef  */
  YYSYMBOL_ActionTypeDesDef = 128,         /* ActionTypeDesDef  */
  YYSYMBOL_EventSignature = 129,           /* EventSignature  */
  YYSYMBOL_ListEventSignature = 130,       /* ListEventSignature  */
  YYSYMBOL_ActionRelations = 131,          /* ActionRelations  */
  YYSYMBOL_EventRelation = 132,            /* EventRelation  */
  YYSYMBOL_ListEventRelation = 133,        /* ListEventRelation  */
  YYSYMBOL_EventNamePair = 134,            /* EventNamePair  */
  YYSYMBOL_ListEventNamePair = 135,        /* ListEventNamePair  */
  YYSYMBOL_EventDef = 136,                 /* EventDef  */
  YYSYMBOL_EventParameterDef = 137,        /* EventParameterDef  */
  YYSYMBOL_EventPreDef = 138,              /* EventPreDef  */
  YYSYMBOL_EventPostDef = 139,             /* EventPostDef  */
  YYSYMBOL_EventPostconditions = 140,      /* EventPostconditions  */
  YYSYMBOL_Postcondition = 141,            /* Postcondition  */
  YYSYMBOL_ListPostcondition = 142,        /* ListPostcondition  */
  YYSYMBOL_LiteralPostcondition = 143,     /* LiteralPostcondition  */
  YYSYMBOL_ListLiteralPostcondition = 144, /* ListLiteralPostcondition  */
  YYSYMBOL_FormulaOrEmpty = 145,           /* FormulaOrEmpty  */
  YYSYMBOL_ProblemDef = 146,               /* ProblemDef  */
  YYSYMBOL_ProblemItemDef = 147,           /* ProblemItemDef  */
  YYSYMBOL_ListProblemItemDef = 148,       /* ListProblemItemDef  */
  YYSYMBOL_ProblemDomainNameDef = 149,     /* ProblemDomainNameDef  */
  YYSYMBOL_AgentNamesDef = 150,            /* AgentNamesDef  */
  YYSYMBOL_AgentGroupsListDef = 151,       /* AgentGroupsListDef  */
  YYSYMBOL_AgentGroupDef = 152,            /* AgentGroupDef  */
  YYSYMBOL_ListAgentGroupDef = 153,        /* ListAgentGroupDef  */
  YYSYMBOL_ObjectNamesDef = 154,           /* ObjectNamesDef  */
  YYSYMBOL_FactListDef = 155,              /* FactListDef  */
  YYSYMBOL_FactDef = 156,                  /* FactDef  */
  YYSYMBOL_ListFactDef = 157,              /* ListFactDef  */
  YYSYMBOL_InitDef = 158,                  /* InitDef  */
  YYSYMBOL_InitialStateDescr = 159,        /* InitialStateDescr  */
  YYSYMBOL_FTheoryFormula = 160,           /* FTheoryFormula  */
  YYSYMBOL_ListFTheoryFormula = 161,       /* ListFTheoryFormula  */
  YYSYMBOL_KPredicateFormula = 162,        /* KPredicateFormula  */
  YYSYMBOL_KWPredicateFormula = 163,       /* KWPredicateFormula  */
  YYSYMBOL_NotKWPredicateFormula = 164,    /* NotKWPredicateFormula  */
  YYSYMBOL_InitialModelDef = 165,          /* InitialModelDef  */
  YYSYMBOL_ModelWorldsDef = 166,           /* ModelWorldsDef  */
  YYSYMBOL_ModelRelDef = 167,              /* ModelRelDef  */
  YYSYMBOL_ModelValDef = 168,              /* ModelValDef  */
  YYSYMBOL_ModelDesDef = 169,              /* ModelDesDef  */
  YYSYMBOL_ModelRelations = 170,           /* ModelRelations  */
  YYSYMBOL_ModelValuation = 171,           /* ModelValuation  */
  YYSYMBOL_WorldRelation = 172,            /* WorldRelation  */
  YYSYMBOL_ListWorldRelation = 173,        /* ListWorldRelation  */
  YYSYMBOL_WorldNamePair = 174,            /* WorldNamePair  */
  YYSYMBOL_ListWorldNamePair = 175,        /* ListWorldNamePair  */
  YYSYMBOL_WorldValuation = 176,           /* WorldValuation  */
  YYSYMBOL_ListWorldValuation = 177,       /* ListWorldValuation  */
  YYSYMBOL_GoalDef = 178,                  /* GoalDef  */
  YYSYMBOL_Formula = 179,                  /* Formula  */
  YYSYMBOL_ListFormula = 180,              /* ListFormula  */
  YYSYMBOL_AtomicFormula = 181,            /* AtomicFormula  */
  YYSYMBOL_AtomicEqFormula = 182,          /* AtomicEqFormula  */
  YYSYMBOL_MetaTerm = 183,                 /* MetaTerm  */
  YYSYMBOL_ListMetaTerm = 184,             /* ListMetaTerm  */
  YYSYMBOL_Term = 185,                     /* Term  */
  YYSYMBOL_ListTerm = 186,                 /* ListTerm  */
  YYSYMBOL_GroundTerm = 187,               /* GroundTerm  */
  YYSYMBOL_ListGroundTerm = 188,           /* ListGroundTerm  */
  YYSYMBOL_Modality = 189,                 /* Modality  */
  YYSYMBOL_SingleModality = 190,           /* SingleModality  */
  YYSYMBOL_GroupModality = 191,            /* GroupModality  */
  YYSYMBOL_ModalityLabel = 192,            /* ModalityLabel  */
  YYSYMBOL_KnowsWhether = 193,             /* KnowsWhether  */
  YYSYMBOL_Literal = 194,                  /* Literal  */
  YYSYMBOL_ListLiteral = 195,              /* ListLiteral  */
  YYSYMBOL_ConditionFormula = 196,         /* ConditionFormula  */
  YYSYMBOL_Condition = 197,                /* Condition  */
  YYSYMBOL_ListCondition = 198,            /* ListCondition  */
  YYSYMBOL_AtomicCondition = 199,          /* AtomicCondition  */
  YYSYMBOL_PredicateFormula = 200,         /* PredicateFormula  */
  YYSYMBOL_ListPredicateFormula = 201,     /* ListPredicateFormula  */
  YYSYMBOL_Entity = 202,                   /* Entity  */
  YYSYMBOL_ListEntity = 203,               /* ListEntity  */
  YYSYMBOL_TypedIdentList = 204,           /* TypedIdentList  */
  YYSYMBOL_TypedVariableList = 205,        /* TypedVariableList  */
  YYSYMBOL_PredicateName = 206,            /* PredicateName  */
  YYSYMBOL_ModalityAgent = 207,            /* ModalityAgent  */
  YYSYMBOL_ListModalityAgent = 208,        /* ListModalityAgent  */
  YYSYMBOL_ModalityAgentGroup = 209,       /* ModalityAgentGroup  */
  YYSYMBOL_AgentGroupName = 210,           /* AgentGroupName  */
  YYSYMBOL_ObservingAgentGroup = 211,      /* ObservingAgentGroup  */
  YYSYMBOL_ListObservingAgentGroup = 212,  /* ListObservingAgentGroup  */
  YYSYMBOL_ObservingAgent = 213,           /* ObservingAgent  */
  YYSYMBOL_AgentGroup = 214,               /* AgentGroup  */
  YYSYMBOL_AllAgents = 215,                /* AllAgents  */
  YYSYMBOL_AnonVarAgent = 216,             /* AnonVarAgent  */
  YYSYMBOL_Parameter = 217,                /* Parameter  */
  YYSYMBOL_ListParameter = 218,            /* ListParameter  */
  YYSYMBOL_ParameterValue = 219,           /* ParameterValue  */
  YYSYMBOL_PostParameterValue = 220,       /* PostParameterValue  */
  YYSYMBOL_ListPostParameterValue = 221,   /* ListPostParameterValue  */
  YYSYMBOL_Type = 222,                     /* Type  */
  YYSYMBOL_ReservedType = 223,             /* ReservedType  */
  YYSYMBOL_LibraryName = 224,              /* LibraryName  */
  YYSYMBOL_ListLibraryName = 225,          /* ListLibraryName  */
  YYSYMBOL_ActionTypeName = 226,           /* ActionTypeName  */
  YYSYMBOL_ReservedActionTypeName = 227,   /* ReservedActionTypeName  */
  YYSYMBOL_EventName = 228,                /* EventName  */
  YYSYMBOL_ListEventName = 229,            /* ListEventName  */
  YYSYMBOL_ReservedEventName = 230,        /* ReservedEventName  */
  YYSYMBOL_ActionName = 231,               /* ActionName  */
  YYSYMBOL_ModelName = 232,                /* ModelName  */
  YYSYMBOL_WorldName = 233,                /* WorldName  */
  YYSYMBOL_ListWorldName = 234,            /* ListWorldName  */
  YYSYMBOL_RequireKey = 235,               /* RequireKey  */
  YYSYMBOL_ListRequireKey = 236,           /* ListRequireKey  */
  YYSYMBOL_TrivialDef = 237,               /* TrivialDef  */
  YYSYMBOL_ListName = 238,                 /* ListName  */
  YYSYMBOL_ListAgentName = 239,            /* ListAgentName  */
  YYSYMBOL_ListModalityName = 240,         /* ListModalityName  */
  YYSYMBOL_ListVariable = 241,             /* ListVariable  */
  YYSYMBOL_Name = 242,                     /* Name  */
  YYSYMBOL_AgentName = 243,                /* AgentName  */
  YYSYMBOL_ModalityName = 244,             /* ModalityName  */
  YYSYMBOL_Variable = 245,                 /* Variable  */
  YYSYMBOL_ParameterName = 246             /* ParameterName  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 205 "epddl.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, epddl_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 397 "Parser.C"


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
#define YYLAST   645

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  149
/* YYNRULES -- Number of rules.  */
#define YYNRULES  302
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  564

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   352


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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   466,   466,   467,   468,   470,   472,   473,   474,   475,
     476,   477,   478,   480,   481,   483,   485,   487,   489,   491,
     493,   494,   496,   498,   500,   502,   504,   505,   507,   509,
     511,   512,   514,   515,   517,   518,   519,   521,   522,   524,
     526,   527,   528,   529,   530,   532,   533,   535,   537,   539,
     540,   542,   544,   546,   548,   550,   551,   553,   554,   556,
     557,   559,   560,   562,   564,   565,   567,   569,   571,   573,
     574,   576,   577,   579,   580,   581,   583,   584,   586,   588,
     589,   591,   592,   594,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   607,   608,   610,   612,   614,   616,
     618,   619,   621,   623,   625,   627,   628,   630,   632,   633,
     635,   636,   637,   638,   639,   640,   642,   643,   645,   646,
     648,   649,   651,   652,   654,   656,   658,   660,   662,   664,
     665,   667,   668,   670,   671,   673,   674,   676,   678,   679,
     681,   683,   684,   686,   688,   689,   690,   691,   692,   693,
     694,   695,   696,   697,   698,   700,   701,   703,   705,   707,
     708,   710,   711,   713,   714,   716,   717,   719,   720,   722,
     723,   725,   726,   728,   729,   731,   732,   734,   735,   737,
     739,   740,   742,   743,   745,   746,   748,   749,   751,   752,
     754,   755,   757,   758,   759,   760,   761,   763,   764,   766,
     767,   769,   770,   772,   773,   775,   776,   778,   780,   781,
     782,   783,   785,   786,   788,   790,   791,   793,   795,   796,
     798,   799,   800,   801,   803,   804,   806,   808,   810,   812,
     813,   815,   816,   817,   818,   820,   821,   823,   824,   826,
     827,   829,   830,   831,   832,   833,   834,   836,   838,   839,
     841,   842,   844,   845,   846,   848,   849,   851,   852,   854,
     856,   858,   860,   862,   863,   865,   866,   867,   868,   869,
     870,   871,   872,   873,   874,   875,   876,   877,   878,   879,
     880,   881,   882,   883,   884,   885,   886,   888,   889,   891,
     893,   894,   896,   897,   899,   900,   902,   903,   905,   907,
     909,   911,   913
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
  "_RPAREN", "_MINUS", "_SYMB_8", "_SYMB_11", "_SYMB_2", "_SYMB_22",
  "_SYMB_21", "_SYMB_53", "_SYMB_42", "_SYMB_17", "_SYMB_47", "_SYMB_20",
  "_SYMB_54", "_SYMB_44", "_SYMB_18", "_SYMB_15", "_SYMB_48", "_SYMB_26",
  "_SYMB_14", "_SYMB_34", "_SYMB_27", "_SYMB_55", "_SYMB_58", "_SYMB_59",
  "_SYMB_56", "_SYMB_57", "_SYMB_62", "_SYMB_61", "_SYMB_60", "_SYMB_51",
  "_SYMB_50", "_SYMB_6", "_SYMB_31", "_SYMB_28", "_SYMB_46", "_SYMB_25",
  "_SYMB_13", "_SYMB_7", "_SYMB_52", "_SYMB_45", "_SYMB_9", "_SYMB_19",
  "_SYMB_12", "_SYMB_5", "_SYMB_16", "_SYMB_3", "_SYMB_4", "_SYMB_43",
  "_SYMB_49", "_SYMB_33", "_SYMB_10", "_SYMB_32", "_LT", "_EQ", "_GT",
  "_SYMB_39", "_KW_All", "_LBRACK", "_RBRACK", "_KW_agent", "_KW_and",
  "_KW_announcement", "_KW_as", "_KW_define", "_KW_domain", "_KW_false",
  "_KW_forall", "_KW_formula", "_SYMB_41", "_KW_if", "_KW_iff",
  "_KW_imply", "_KW_library", "_KW_literal", "_KW_not", "_KW_ontic",
  "_KW_or", "_KW_otherwise", "_KW_postcondition", "_KW_predicate",
  "_SYMB_40", "_KW_problem", "_KW_sensing", "_KW_set", "_KW_true",
  "_LBRACE", "_RBRACE", "T_AgentName", "T_ModalityName", "T_Name",
  "T_ParameterName", "T_Variable", "_INTEGER_", "$accept", "MainDef",
  "DomainDef", "DomainItemDef", "ListDomainItemDef",
  "DomainLibrariesNameDef", "RequireDef", "TypesDef", "PredicateListDef",
  "PredicateDef", "ListPredicateDef", "ModalitiesDef",
  "ObservabilityGroupsDef", "ActionDef", "ActionParameterDef",
  "ActionConditionsDef", "ActionTypeSignatureDef", "ActionPreDef",
  "Precondition", "ActionObsDef", "ObsConditionDef", "ListObsConditionDef",
  "LibraryDef", "LibraryItemDef", "ListLibraryItemDef", "ActionTypeDef",
  "ActionTypeParameterDef", "ActionTypeFrameDef", "ActionTypeEventsDef",
  "ActionTypeRelDef", "ActionTypeDesDef", "EventSignature",
  "ListEventSignature", "ActionRelations", "EventRelation",
  "ListEventRelation", "EventNamePair", "ListEventNamePair", "EventDef",
  "EventParameterDef", "EventPreDef", "EventPostDef",
  "EventPostconditions", "Postcondition", "ListPostcondition",
  "LiteralPostcondition", "ListLiteralPostcondition", "FormulaOrEmpty",
  "ProblemDef", "ProblemItemDef", "ListProblemItemDef",
  "ProblemDomainNameDef", "AgentNamesDef", "AgentGroupsListDef",
  "AgentGroupDef", "ListAgentGroupDef", "ObjectNamesDef", "FactListDef",
  "FactDef", "ListFactDef", "InitDef", "InitialStateDescr",
  "FTheoryFormula", "ListFTheoryFormula", "KPredicateFormula",
  "KWPredicateFormula", "NotKWPredicateFormula", "InitialModelDef",
  "ModelWorldsDef", "ModelRelDef", "ModelValDef", "ModelDesDef",
  "ModelRelations", "ModelValuation", "WorldRelation", "ListWorldRelation",
  "WorldNamePair", "ListWorldNamePair", "WorldValuation",
  "ListWorldValuation", "GoalDef", "Formula", "ListFormula",
  "AtomicFormula", "AtomicEqFormula", "MetaTerm", "ListMetaTerm", "Term",
  "ListTerm", "GroundTerm", "ListGroundTerm", "Modality", "SingleModality",
  "GroupModality", "ModalityLabel", "KnowsWhether", "Literal",
  "ListLiteral", "ConditionFormula", "Condition", "ListCondition",
  "AtomicCondition", "PredicateFormula", "ListPredicateFormula", "Entity",
  "ListEntity", "TypedIdentList", "TypedVariableList", "PredicateName",
  "ModalityAgent", "ListModalityAgent", "ModalityAgentGroup",
  "AgentGroupName", "ObservingAgentGroup", "ListObservingAgentGroup",
  "ObservingAgent", "AgentGroup", "AllAgents", "AnonVarAgent", "Parameter",
  "ListParameter", "ParameterValue", "PostParameterValue",
  "ListPostParameterValue", "Type", "ReservedType", "LibraryName",
  "ListLibraryName", "ActionTypeName", "ReservedActionTypeName",
  "EventName", "ListEventName", "ReservedEventName", "ActionName",
  "ModelName", "WorldName", "ListWorldName", "RequireKey",
  "ListRequireKey", "TrivialDef", "ListName", "ListAgentName",
  "ListModalityName", "ListVariable", "Name", "AgentName", "ModalityName",
  "Variable", "ParameterName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-374)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,    -7,    67,  -374,  -374,  -374,    75,  -374,   112,   -13,
     -13,   -13,  -374,   143,   149,   155,  -374,  -374,  -374,   253,
     282,   292,   204,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,   259,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
     408,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,   -13,   -13,    81,    70,   164,   507,   -13,
     329,    -8,  -374,    70,   -13,   176,   133,    65,   -13,   -13,
     147,  -374,   -13,   195,  -374,  -374,   203,    81,  -374,    70,
     221,  -374,   -13,   164,   225,   315,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,   507,   240,   243,  -374,   -13,
    -374,  -374,  -374,   192,  -374,  -374,  -374,   223,  -374,  -374,
     302,   267,    70,   297,   -13,   176,   307,   451,    81,    81,
    -374,  -374,   309,  -374,  -374,   133,  -374,  -374,   131,   255,
     322,    66,  -374,  -374,   208,  -374,   326,   276,   280,  -374,
    -374,  -374,  -374,  -374,  -374,   257,  -374,  -374,  -374,   265,
     277,   285,  -374,  -374,  -374,   358,   -13,   368,   361,   388,
     349,   310,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
     198,   133,   133,   133,   133,  -374,   396,  -374,   397,   289,
    -374,   289,  -374,  -374,   162,   -13,   401,   401,   401,   401,
     403,  -374,  -374,   347,  -374,  -374,   409,   366,  -374,   257,
     413,   417,   421,  -374,   257,   422,   423,   426,   405,  -374,
     257,   431,   420,   257,   174,   391,    70,    23,   198,  -374,
    -374,  -374,  -374,   133,   133,   436,   133,  -374,    18,  -374,
    -374,   269,   387,  -374,  -374,  -374,  -374,   124,   384,   444,
     450,   401,   401,   445,   401,  -374,    42,    69,   -13,   448,
     399,   452,   226,  -374,  -374,  -374,   455,   418,  -374,   454,
     257,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
     -13,  -374,  -374,   459,    70,   464,   407,   465,   416,  -374,
    -374,  -374,   467,   470,   381,  -374,  -374,  -374,  -374,   471,
     133,   474,   477,  -374,   479,  -374,  -374,  -374,  -374,  -374,
     289,  -374,  -374,  -374,  -374,  -374,   401,   480,   488,  -374,
     489,  -374,  -374,   275,   232,  -374,  -374,  -374,   401,  -374,
     -13,   491,  -374,    63,  -374,   494,  -374,  -374,   496,   487,
    -374,   198,   498,   500,  -374,   329,   174,   473,   405,  -374,
    -374,  -374,   512,    -8,   464,  -374,   514,   509,  -374,  -374,
      30,  -374,   534,  -374,  -374,  -374,  -374,   472,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,    27,    94,
     543,   544,   547,   490,    70,  -374,  -374,  -374,    70,  -374,
     550,  -374,  -374,   -15,  -374,    22,  -374,   551,  -374,  -374,
     552,   553,   198,   224,   498,   -10,   556,    48,  -374,  -374,
     558,   559,   257,  -374,  -374,  -374,    63,  -374,   561,  -374,
    -374,   562,   563,   565,   566,   567,   -34,  -374,     5,   495,
      81,   401,  -374,  -374,  -374,   401,   504,    70,    22,   569,
     570,   571,   501,   -13,  -374,   -13,  -374,   572,   498,   573,
    -374,  -374,  -374,   354,   281,   558,  -374,  -374,  -374,   363,
     575,   -15,  -374,    -8,  -374,   257,    73,  -374,   499,  -374,
     576,   577,  -374,  -374,   492,   -13,   -13,  -374,  -374,  -374,
    -374,   579,  -374,  -374,  -374,   476,  -374,  -374,   289,    70,
    -374,  -374,  -374,  -374,  -374,  -374,    31,   581,   582,   583,
      -8,   584,   585,   587,   174,  -374,  -374,  -374,   588,    28,
    -374,  -374,   219,    70,    37,    -8,    -8,  -374,  -374,  -374,
    -374,  -374,   590,   -13,   591,   592,  -374,  -374,  -374,   593,
    -374,   318,  -374,  -374,  -374,   594,   596,  -374,  -374,   597,
    -374,   133,   598,   513,   590,   599,  -374,  -374,  -374,   601,
    -374,   182,  -374,  -374,   602,  -374,  -374,  -374,   257,  -374,
     603,   590,   604,  -374
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,     0,     2,     3,     4,     0,     1,     0,     0,
       0,     0,   298,     0,     0,     0,    13,    45,    94,     0,
       0,     0,     0,     5,    14,     6,     7,     8,     9,    10,
      11,    12,     0,    39,    40,    41,    42,    46,    43,    44,
       0,    83,    85,    86,    95,    84,    87,    88,    89,    90,
      91,    92,    93,     0,     0,   294,     0,     0,     0,   290,
       0,     0,   100,     0,     0,     0,     0,     0,     0,   290,
       0,   260,   248,     0,   247,   300,     0,   294,   299,   218,
       0,   217,     0,    20,     0,     0,   277,   265,   270,   278,
     267,   271,   279,   282,   283,   280,   281,   274,   273,   275,
     269,   276,   268,   266,   272,   287,     0,     0,   203,   290,
     254,   252,   253,     0,   250,   251,   259,     0,   255,   256,
       0,     0,   292,     0,     0,   105,     0,     0,   178,   178,
     153,   152,     0,   150,   151,     0,   171,   172,     0,     0,
       0,   116,   108,   110,     0,   261,     0,     0,    27,   249,
      15,    22,   295,   219,    23,   296,   207,    21,    18,     0,
       0,     0,   288,    16,    17,   291,   290,     0,    50,     0,
       0,     0,    98,   101,    97,   293,    96,   201,   106,   103,
       0,     0,     0,     0,     0,   301,     0,   161,     0,     0,
     177,     0,   143,   148,     0,     0,     0,     0,     0,     0,
       0,   169,   226,     0,   107,   117,     0,     0,   102,   296,
       0,     0,     0,   205,   296,     0,     0,     0,     0,   291,
     296,     0,     0,   296,     0,    70,     0,     0,     0,   163,
     167,   168,   164,     0,     0,     0,     0,   154,     0,   149,
     227,     0,     0,   211,   210,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,   115,     0,     0,     0,     0,
       0,     0,     0,    26,   185,   186,     0,     0,    19,   297,
     296,   286,   285,   284,   241,   245,   243,   246,   242,   244,
     290,   240,   239,     0,     0,     0,     0,     0,     0,    68,
      30,    31,     0,     0,     0,   104,   202,   199,   200,     0,
     155,     0,     0,   147,     0,   157,   162,   159,   160,   174,
     212,   214,   176,   173,   175,   109,   197,     0,     0,   195,
       0,   196,   170,     0,     0,   112,   113,   114,     0,   111,
     263,     0,   262,     0,   126,   135,   129,   130,     0,     0,
      25,     0,     0,     0,   165,     0,     0,    33,     0,   297,
     204,    48,     0,     0,    55,    51,     0,     0,    67,   289,
       0,    69,    76,    71,    74,    72,    66,     0,   158,   156,
     146,   144,   145,   213,   198,   194,   192,   193,     0,     0,
       0,     0,     0,     0,     0,   120,   264,   125,     0,   224,
       0,   216,   215,     0,   136,     0,   127,   141,   131,   132,
       0,     0,     0,     0,     0,     0,     0,     0,   229,    29,
       0,     0,   296,    49,   229,    56,     0,    52,    61,    57,
      58,     0,     0,     0,     0,     0,     0,    77,     0,     0,
       0,     0,   119,   121,   123,     0,     0,     0,     0,   138,
       0,     0,     0,     0,   142,     0,   124,     0,   188,     0,
     187,   190,   166,     0,     0,    37,    32,    24,   206,     0,
       0,     0,    62,     0,    47,   296,     0,   180,     0,    75,
       0,     0,   118,   179,     0,     0,     0,   139,   133,   134,
     182,     0,   191,   189,   184,     0,    28,   230,     0,     0,
     221,   223,   220,   222,    38,    54,     0,    64,     0,     0,
     257,     0,     0,     0,     0,    99,   122,   225,     0,     0,
     128,   302,     0,     0,     0,     0,     0,    65,    59,    60,
     258,    53,     0,     0,     0,     0,    81,    82,   137,     0,
     183,     0,   236,   232,   231,     0,   237,   234,   233,     0,
      34,     0,     0,     0,    79,     0,   181,    78,   140,     0,
     228,     0,   238,    36,     0,    63,    80,    73,   296,    35,
       0,     0,     0,   235
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -374,  -374,  -374,  -374,  -374,  -374,   350,  -374,  -374,  -374,
     497,   370,   586,  -374,  -374,  -374,  -374,  -374,   246,  -374,
    -374,   140,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,
    -374,  -374,   256,  -374,  -374,   168,  -374,   114,  -374,  -374,
    -374,  -374,  -374,  -374,   250,  -270,  -311,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,  -374,   493,
    -374,  -374,   -35,   475,   356,   357,   360,  -374,  -374,  -374,
    -374,  -374,  -374,  -374,  -374,   284,  -374,   181,  -374,   218,
    -374,   -61,  -215,  -360,  -374,  -374,  -374,  -208,  -374,   365,
    -374,  -374,  -374,  -374,   502,  -322,   113,  -374,  -374,  -191,
     175,   283,  -158,  -229,  -374,  -374,   -45,  -206,   -48,  -133,
     314,   434,   199,  -325,   -69,   141,  -373,  -128,  -226,  -374,
     214,  -374,  -374,    96,   286,  -374,  -374,   564,   288,  -374,
     -54,   130,  -374,  -374,   440,  -293,  -315,  -374,   532,  -243,
     -83,  -118,   568,  -105,    -9,   -50,  -120,  -109,  -374
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,    24,    19,    25,    26,    27,    28,    83,
      84,    29,    30,    31,   148,   211,   267,   347,   289,   411,
     455,   456,     4,    37,    20,    38,   168,   222,   286,   357,
     422,   354,   355,   417,   418,   419,   497,   498,    39,   170,
     225,   293,   361,   362,   363,   544,   545,   525,     5,    44,
      21,    45,    46,    47,   173,   120,    48,    49,   125,   126,
      50,   140,   141,   142,   380,   381,   382,    51,   207,   260,
     339,   401,   334,   396,   335,   336,   439,   440,   397,   398,
      52,   186,   301,   133,   134,   306,   238,   228,   407,   229,
     256,   135,   136,   137,   189,   328,   468,   509,   263,   448,
     449,   265,   143,   317,   296,   227,   107,   212,   187,   310,
     311,   242,   389,    79,    80,   489,   390,   243,   244,   487,
     453,   535,   536,   537,   280,   281,    72,    73,   113,   114,
     500,   501,   118,    70,   144,   330,   331,   105,   106,   291,
     108,   121,    76,   213,   156,   231,    77,   214,   512
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    14,    15,   261,   175,   132,    81,   117,   190,   190,
     153,   203,   308,   122,   283,   386,   337,   287,   188,   264,
     299,   304,   364,   305,   146,   320,   165,   359,   295,    81,
     307,   378,   466,     1,   155,   359,   359,   423,   251,   252,
     253,   254,   540,   460,    71,    74,   202,   321,   341,   365,
     109,   115,   119,   451,   424,   123,   241,   431,   247,   145,
     109,     6,   185,    74,   467,   116,   202,     7,   359,   138,
     194,   232,   122,   323,   193,   388,   177,    78,   240,     8,
     246,    12,   246,   219,    12,   369,    12,   374,   460,   324,
     201,   529,   364,   316,   318,   399,   316,    78,   250,   329,
     166,   423,   442,   200,   116,   270,   429,   431,   294,   269,
      78,   541,    12,   420,   185,    78,    12,    12,   424,   232,
     233,   234,   235,   236,   202,    12,   185,   139,   139,   232,
     481,   324,   246,   402,    78,   194,    12,   127,   246,   245,
      78,   245,    12,   524,   185,   475,   201,   441,    16,   467,
     442,   404,   503,   388,    17,    78,   430,   166,   316,   200,
      18,   270,    78,   290,   514,   349,   194,    12,    82,   195,
     385,   230,   300,   302,    75,   300,   122,   298,   288,   188,
     124,     9,   508,   475,   240,   202,   145,   313,   539,    10,
     128,   245,   147,   139,   447,   129,   196,   245,    11,   452,
     150,   246,   201,   130,   384,   391,   458,   197,   151,   282,
     198,    53,   199,    54,   344,   352,    78,   499,   297,   230,
     185,   253,   131,   531,   139,    12,   154,   196,   491,   230,
     158,   128,   232,   556,    81,   350,   129,   167,   197,   300,
      55,   198,   532,   199,   130,   163,    56,   230,   164,   332,
     562,   425,    57,   549,    58,    59,    12,    22,    23,   502,
     245,   527,   491,   131,   206,   391,   532,    60,   169,   538,
     424,   109,   174,   471,   383,   201,   128,   472,    61,   378,
     209,   129,   341,   392,   341,   290,    32,    33,   391,   130,
      78,   342,    12,   232,   185,    55,    40,    41,   232,   414,
     391,    56,   176,   343,   534,   343,   171,   172,   131,    58,
     384,    78,   179,    12,   192,   185,   202,   425,    12,   474,
      12,   332,   127,   359,    78,    75,   490,   204,   309,   240,
     202,   208,   230,   391,   436,   210,   115,   324,   437,   282,
     196,   240,   202,   392,   119,   493,   159,   160,   161,   240,
     202,   197,   560,   185,   379,   344,   199,   344,   485,   486,
     490,    78,   215,   488,   218,   185,   392,   485,   495,    12,
      34,    42,   220,    78,   216,   128,   180,   185,   392,   493,
     129,    78,   217,   181,   221,   185,   332,   122,   130,   549,
      35,    43,   223,   230,   182,   110,   224,   183,   230,   184,
     226,   237,   239,   232,   492,   250,   424,   131,   255,   111,
     257,   392,    12,   258,   185,   259,   112,   262,    62,    63,
     127,   359,   188,    12,    64,   266,   268,   271,   272,   332,
      65,   273,    66,    67,   332,   284,   332,   292,   492,    81,
     285,   303,   515,   526,    55,    68,   312,   314,    69,   315,
     319,   533,   333,   338,   119,   127,   356,   340,    58,   345,
     348,   542,   515,    81,   351,   346,   332,   332,   353,   274,
     358,   360,   367,   128,   180,   366,   368,   275,   129,   370,
     554,   181,   371,   276,   372,   375,   130,   119,   277,   278,
     279,   119,   182,   376,   377,   183,   387,   184,   393,    12,
     395,   400,   403,   230,   405,   131,   119,   119,   128,   180,
      12,    85,   185,   129,   410,   196,   181,   413,   416,    86,
      87,   130,    88,   421,    89,    90,   197,   182,    91,   198,
     183,   199,   184,    92,    93,    94,    95,    96,   426,   428,
     131,    97,    98,    99,    12,    12,   100,   185,   432,   433,
     101,   102,   434,   435,   438,   443,   445,   430,   446,   103,
     104,   450,   454,   480,   457,   461,   463,   473,   464,   465,
     466,   511,   469,   476,   504,   478,   479,   482,   484,   496,
     157,   505,   506,   507,   510,   516,   462,   518,   519,   521,
     522,   523,   409,   528,   543,   494,   546,   547,   548,   550,
     551,   424,   553,   555,   557,   558,    36,   559,   561,   563,
     415,   517,   427,   325,   326,   444,   205,   327,   178,   394,
     477,   322,   530,   483,   373,   248,   406,   470,   459,   513,
     520,   191,   552,   408,   412,   249,   149,   162,     0,     0,
       0,     0,     0,     0,     0,   152
};

static const yytype_int16 yycheck[] =
{
       9,    10,    11,   209,   122,    66,    56,    61,   128,   129,
      79,   139,   238,    63,   220,   330,   259,   223,   127,   210,
     228,   236,   292,     5,    69,   254,   109,     5,     5,    79,
     238,     4,     4,     4,    82,     5,     5,    71,   196,   197,
     198,   199,     5,   416,    53,    54,    61,     5,    58,   292,
      59,    60,    61,     5,    88,    64,   189,   379,   191,    68,
      69,    68,    96,    72,   424,    73,    61,     0,     5,     4,
       4,   180,   122,     4,   135,    90,   124,    92,    60,     4,
     189,    94,   191,   166,    94,   300,    94,   316,   461,    62,
     138,    63,   362,   251,   252,   338,   254,    92,     4,   257,
     109,    71,   395,   138,    73,   214,    79,   429,   226,   214,
      92,    74,    94,   356,    96,    92,    94,    94,    88,   228,
     181,   182,   183,   184,    61,    94,    96,    62,    62,   238,
     445,    62,   241,   341,    92,     4,    94,     4,   247,   189,
      92,   191,    94,   503,    96,   438,   194,   390,     5,   509,
     443,   342,    79,    90,     5,    92,    62,   166,   316,   194,
       5,   270,    92,   224,   489,   270,     4,    94,     4,    38,
     328,   180,   233,   234,    93,   236,   226,   227,     4,   288,
       4,    69,   475,   476,    60,    61,   195,    63,   513,    77,
      57,   241,    45,    62,   402,    62,    65,   247,    86,   407,
       5,   310,   250,    70,   324,   333,   412,    76,     5,   218,
      79,     7,    81,     9,   262,   284,    92,   460,   227,   228,
      96,   379,    89,     4,    62,    94,     5,    65,   454,   238,
       5,    57,   341,   544,   284,   280,    62,    45,    76,   300,
      36,    79,   512,    81,    70,     5,    42,   256,     5,   258,
     561,   360,    48,    71,    50,    51,    94,     4,     5,   465,
     310,   504,   488,    89,    56,   393,   536,     8,    45,   512,
      88,   280,     5,   431,   324,   323,    57,   435,    19,     4,
       4,    62,    58,   333,    58,   346,     4,     5,   416,    70,
      92,    65,    94,   402,    96,    36,     4,     5,   407,   353,
     428,    42,     5,    79,   512,    79,     4,     5,    89,    50,
     430,    92,     5,    94,     5,    96,    61,   426,    94,   437,
      94,   330,     4,     5,    92,    93,   454,     5,    59,    60,
      61,     5,   341,   461,   384,    55,   345,    62,   388,   348,
      65,    60,    61,   393,   353,   454,    31,    32,    33,    60,
      61,    76,   558,    96,    79,   403,    81,   405,     4,     5,
     488,    92,    97,    82,     6,    96,   416,     4,     5,    94,
      20,    21,     4,    92,    97,    57,    58,    96,   428,   488,
      62,    92,    97,    65,    23,    96,   395,   437,    70,    71,
      20,    21,     4,   402,    76,    66,    47,    79,   407,    81,
      90,     5,     5,   512,   454,     4,    88,    89,     5,    80,
      63,   461,    94,     4,    96,    49,    87,     4,    10,    11,
       4,     5,   531,    94,    16,     8,     5,     5,     5,   438,
      22,     5,    24,    25,   443,     4,   445,    46,   488,   489,
      20,     5,   496,   504,    36,    37,    59,    63,    40,     5,
       5,   512,     4,    54,   463,     4,    49,     5,    50,     4,
       6,   515,   516,   513,     5,    47,   475,   476,     4,    64,
       5,     4,    91,    57,    58,     5,     5,    72,    62,     5,
     541,    65,     5,    78,     5,     5,    70,   496,    83,    84,
      85,   500,    76,     5,     5,    79,     5,    81,     4,    94,
       4,    14,     4,   512,     4,    89,   515,   516,    57,    58,
      94,     4,    96,    62,    41,    65,    65,     5,     4,    12,
      13,    70,    15,    14,    17,    18,    76,    76,    21,    79,
      79,    81,    81,    26,    27,    28,    29,    30,     4,    67,
      89,    34,    35,    36,    94,    94,    39,    96,     5,     5,
      43,    44,     5,    63,     4,     4,     4,    62,     5,    52,
      53,     5,     4,    62,     5,     4,     4,    63,     5,     4,
       4,    95,     5,     4,    75,     5,     5,     5,     5,     4,
      83,     5,     5,    91,     5,     4,   418,     5,     5,     5,
       5,     4,   346,     5,     4,   455,     5,     5,     5,     5,
       4,    88,     5,     5,     5,     4,    20,     5,     5,     5,
     354,   497,   362,   257,   257,   397,   141,   257,   125,   335,
     439,   256,   509,   448,   310,   191,   343,   428,   414,   488,
     500,   129,   536,   345,   348,   195,    72,   105,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    99,   100,   120,   146,    68,     0,     4,    69,
      77,    86,    94,   242,   242,   242,     5,     5,     5,   102,
     122,   148,     4,     5,   101,   103,   104,   105,   106,   109,
     110,   111,     4,     5,   104,   109,   110,   121,   123,   136,
       4,     5,   104,   109,   147,   149,   150,   151,   154,   155,
     158,   165,   178,     7,     9,    36,    42,    48,    50,    51,
       8,    19,    10,    11,    16,    22,    24,    25,    37,    40,
     231,   242,   224,   225,   242,    93,   240,   244,    92,   211,
     212,   243,     4,   107,   108,     4,    12,    13,    15,    17,
      18,    21,    26,    27,    28,    29,    30,    34,    35,    36,
      39,    43,    44,    52,    53,   235,   236,   204,   238,   242,
      66,    80,    87,   226,   227,   242,    73,   228,   230,   242,
     153,   239,   243,   242,     4,   156,   157,     4,    57,    62,
      70,    89,   179,   181,   182,   189,   190,   191,     4,    62,
     159,   160,   161,   200,   232,   242,   204,    45,   112,   225,
       5,     5,   240,   212,     5,   206,   242,   108,     5,    31,
      32,    33,   236,     5,     5,   238,   242,    45,   124,    45,
     137,     4,     5,   152,     5,   239,     5,   206,   157,     5,
      58,    65,    76,    79,    81,    96,   179,   206,   245,   192,
     244,   192,     5,   179,     4,    38,    65,    76,    79,    81,
     160,   206,    61,   215,     5,   161,    56,   166,     5,     4,
      55,   113,   205,   241,   245,    97,    97,    97,     6,   238,
       4,    23,   125,     4,    47,   138,    90,   203,   185,   187,
     242,   243,   245,   179,   179,   179,   179,     5,   184,     5,
      60,   207,   209,   215,   216,   243,   245,   207,   209,   232,
       4,   200,   200,   200,   200,     5,   188,    63,     4,    49,
     167,   205,     4,   196,   197,   199,     8,   114,     5,   241,
     245,     5,     5,     5,    64,    72,    78,    83,    84,    85,
     222,   223,   242,   205,     4,    20,   126,   205,     4,   116,
     179,   237,    46,   139,   239,     5,   202,   242,   243,   185,
     179,   180,   179,     5,   180,     5,   183,   185,   216,    59,
     207,   208,    59,    63,    63,     5,   200,   201,   200,     5,
     201,     5,   187,     4,    62,   162,   163,   164,   193,   200,
     233,   234,   242,     4,   170,   172,   173,   237,    54,   168,
       5,    58,    65,    79,   206,     4,    47,   115,     6,   241,
     204,     5,   212,     4,   129,   130,    49,   127,     5,     5,
       4,   140,   141,   142,   143,   237,     5,    91,     5,   180,
       5,     5,     5,   208,   201,     5,     5,     5,     4,    79,
     162,   163,   164,   243,   244,   200,   234,     5,    90,   210,
     214,   215,   243,     4,   173,     4,   171,   176,   177,   237,
      14,   169,   185,     4,   197,     4,   199,   186,   226,   116,
      41,   117,   222,     5,   228,   130,     4,   131,   132,   133,
     237,    14,   128,    71,    88,   245,     4,   142,    67,    79,
      62,   193,     5,     5,     5,    63,   243,   243,     4,   174,
     175,   237,   233,     4,   177,     4,     5,   185,   197,   198,
       5,     5,   185,   218,     4,   118,   119,     5,   205,   218,
     214,     4,   133,     4,     5,     4,     4,   181,   194,     5,
     210,   200,   200,    63,   239,   233,     4,   175,     5,     5,
      62,   234,     5,   198,     5,     4,     5,   217,    82,   213,
     215,   216,   243,   245,   119,     5,     4,   134,   135,   237,
     228,   229,   205,    79,    75,     5,     5,    91,   233,   195,
       5,    95,   246,   213,   211,   228,     4,   135,     5,     5,
     229,     5,     5,     4,   181,   145,   179,   237,     5,    63,
     194,     4,   143,   179,   185,   219,   220,   221,   237,   211,
       5,    74,   228,     4,   143,   144,     5,     5,     5,    71,
       5,     4,   221,     5,   179,     5,   144,     5,     4,     5,
     205,     5,   144,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,    99,    99,   100,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   103,   104,   105,   106,   107,
     108,   108,   109,   110,   111,   112,   113,   113,   114,   115,
     116,   116,   117,   117,   118,   118,   118,   119,   119,   120,
     121,   121,   121,   121,   121,   122,   122,   123,   124,   125,
     125,   126,   127,   128,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   134,   135,   135,   136,   137,   138,   139,
     139,   140,   140,   141,   141,   141,   142,   142,   143,   144,
     144,   145,   145,   146,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   148,   148,   149,   150,   151,   152,
     153,   153,   154,   155,   156,   157,   157,   158,   159,   159,
     160,   160,   160,   160,   160,   160,   161,   161,   162,   162,
     163,   163,   164,   164,   165,   166,   167,   168,   169,   170,
     170,   171,   171,   172,   172,   173,   173,   174,   175,   175,
     176,   177,   177,   178,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   180,   180,   181,   182,   183,
     183,   184,   184,   185,   185,   186,   186,   187,   187,   188,
     188,   189,   189,   190,   190,   191,   191,   192,   192,   193,
     194,   194,   195,   195,   196,   196,   197,   197,   198,   198,
     199,   199,   200,   200,   200,   200,   200,   201,   201,   202,
     202,   203,   203,   204,   204,   205,   205,   206,   207,   207,
     207,   207,   208,   208,   209,   210,   210,   211,   212,   212,
     213,   213,   213,   213,   214,   214,   215,   216,   217,   218,
     218,   219,   219,   219,   219,   220,   220,   221,   221,   222,
     222,   223,   223,   223,   223,   223,   223,   224,   225,   225,
     226,   226,   227,   227,   227,   228,   228,   229,   229,   230,
     231,   232,   233,   234,   234,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   236,   236,   237,
     238,   238,   239,   239,   240,   240,   241,   241,   242,   243,
     244,   245,   246
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     8,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     4,     4,     4,     4,     4,
       1,     2,     4,     4,     9,     4,     2,     0,     5,     2,
       1,     1,     2,     0,     4,     6,     5,     1,     2,     8,
       1,     1,     1,     1,     1,     0,     2,     9,     4,     4,
       0,     2,     2,     4,     4,     1,     2,     1,     1,     4,
       4,     1,     2,     4,     1,     2,     7,     4,     2,     2,
       0,     1,     1,     7,     1,     3,     1,     2,     6,     1,
       2,     1,     1,     8,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     4,     4,     4,     7,
       0,     2,     4,     4,     4,     1,     2,     4,     1,     4,
       1,     4,     4,     4,     4,     3,     1,     2,     4,     3,
       2,     3,     5,     3,     8,     4,     2,     2,     4,     1,
       1,     1,     1,     4,     4,     1,     2,     4,     1,     2,
       6,     1,     2,     4,     5,     5,     5,     4,     2,     3,
       1,     1,     1,     1,     3,     1,     2,     4,     5,     1,
       1,     0,     2,     1,     1,     0,     2,     1,     1,     0,
       2,     1,     1,     4,     4,     4,     4,     1,     0,     4,
       1,     4,     0,     2,     5,     1,     1,     4,     1,     2,
       4,     5,     5,     5,     5,     4,     4,     1,     2,     1,
       1,     0,     2,     1,     5,     1,     5,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     4,     1,     1,     4,     0,
       2,     1,     1,     1,     1,     7,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     4,     1,     2,     2,
       0,     2,     1,     2,     0,     2,     0,     2,     1,     1,
       1,     1,     1
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
#line 466 "epddl.y"
                    { (yyval.maindef_) = new Domain((yyvsp[0].domaindef_)); result->maindef_ = (yyval.maindef_); }
#line 1947 "Parser.C"
    break;

  case 3: /* MainDef: LibraryDef  */
#line 467 "epddl.y"
               { (yyval.maindef_) = new ActionTypeLibrary((yyvsp[0].librarydef_)); result->maindef_ = (yyval.maindef_); }
#line 1953 "Parser.C"
    break;

  case 4: /* MainDef: ProblemDef  */
#line 468 "epddl.y"
               { (yyval.maindef_) = new Problem((yyvsp[0].problemdef_)); result->maindef_ = (yyval.maindef_); }
#line 1959 "Parser.C"
    break;

  case 5: /* DomainDef: _LPAREN _KW_define _LPAREN _KW_domain Name _RPAREN ListDomainItemDef _RPAREN  */
#line 470 "epddl.y"
                                                                                         { (yyval.domaindef_) = new EPDDLDomain((yyvsp[-3]._name), (yyvsp[-1].listdomainitemdef_)); }
#line 1965 "Parser.C"
    break;

  case 6: /* DomainItemDef: DomainLibrariesNameDef  */
#line 472 "epddl.y"
                                       { (yyval.domainitemdef_) = new EPDDLDomLibrary((yyvsp[0].domainlibrariesnamedef_)); }
#line 1971 "Parser.C"
    break;

  case 7: /* DomainItemDef: RequireDef  */
#line 473 "epddl.y"
               { (yyval.domainitemdef_) = new EPDDLDomRequire((yyvsp[0].requiredef_)); }
#line 1977 "Parser.C"
    break;

  case 8: /* DomainItemDef: TypesDef  */
#line 474 "epddl.y"
             { (yyval.domainitemdef_) = new EPDDLDomTypes((yyvsp[0].typesdef_)); }
#line 1983 "Parser.C"
    break;

  case 9: /* DomainItemDef: PredicateListDef  */
#line 475 "epddl.y"
                     { (yyval.domainitemdef_) = new EPDDLDomPredicates((yyvsp[0].predicatelistdef_)); }
#line 1989 "Parser.C"
    break;

  case 10: /* DomainItemDef: ModalitiesDef  */
#line 476 "epddl.y"
                  { (yyval.domainitemdef_) = new EPDDLDomModalities((yyvsp[0].modalitiesdef_)); }
#line 1995 "Parser.C"
    break;

  case 11: /* DomainItemDef: ObservabilityGroupsDef  */
#line 477 "epddl.y"
                           { (yyval.domainitemdef_) = new EPDDLDomObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 2001 "Parser.C"
    break;

  case 12: /* DomainItemDef: ActionDef  */
#line 478 "epddl.y"
              { (yyval.domainitemdef_) = new EPDDLDomAction((yyvsp[0].actiondef_)); }
#line 2007 "Parser.C"
    break;

  case 13: /* ListDomainItemDef: %empty  */
#line 480 "epddl.y"
                                { (yyval.listdomainitemdef_) = new ListDomainItemDef(); }
#line 2013 "Parser.C"
    break;

  case 14: /* ListDomainItemDef: ListDomainItemDef DomainItemDef  */
#line 481 "epddl.y"
                                    { (yyvsp[-1].listdomainitemdef_)->push_back((yyvsp[0].domainitemdef_)); (yyval.listdomainitemdef_) = (yyvsp[-1].listdomainitemdef_); }
#line 2019 "Parser.C"
    break;

  case 15: /* DomainLibrariesNameDef: _LPAREN _SYMB_2 ListLibraryName _RPAREN  */
#line 483 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listlibraryname_)->begin(),(yyvsp[-1].listlibraryname_)->end()) ;(yyval.domainlibrariesnamedef_) = new EPDDLDomLibraryNames((yyvsp[-1].listlibraryname_)); }
#line 2025 "Parser.C"
    break;

  case 16: /* RequireDef: _LPAREN _SYMB_3 ListRequireKey _RPAREN  */
#line 485 "epddl.y"
                                                    { std::reverse((yyvsp[-1].listrequirekey_)->begin(),(yyvsp[-1].listrequirekey_)->end()) ;(yyval.requiredef_) = new EPDDLRequire((yyvsp[-1].listrequirekey_)); }
#line 2031 "Parser.C"
    break;

  case 17: /* TypesDef: _LPAREN _SYMB_4 TypedIdentList _RPAREN  */
#line 487 "epddl.y"
                                                  { (yyval.typesdef_) = new EPDDLTypes((yyvsp[-1].typedidentlist_)); }
#line 2037 "Parser.C"
    break;

  case 18: /* PredicateListDef: _LPAREN _SYMB_5 ListPredicateDef _RPAREN  */
#line 489 "epddl.y"
                                                            { std::reverse((yyvsp[-1].listpredicatedef_)->begin(),(yyvsp[-1].listpredicatedef_)->end()) ;(yyval.predicatelistdef_) = new EPDDLPredicateList((yyvsp[-1].listpredicatedef_)); }
#line 2043 "Parser.C"
    break;

  case 19: /* PredicateDef: _LPAREN PredicateName TypedVariableList _RPAREN  */
#line 491 "epddl.y"
                                                               { (yyval.predicatedef_) = new EPDDLPredicateDef((yyvsp[-2].predicatename_), (yyvsp[-1].typedvariablelist_)); }
#line 2049 "Parser.C"
    break;

  case 20: /* ListPredicateDef: PredicateDef  */
#line 493 "epddl.y"
                                { (yyval.listpredicatedef_) = new ListPredicateDef(); (yyval.listpredicatedef_)->push_back((yyvsp[0].predicatedef_)); }
#line 2055 "Parser.C"
    break;

  case 21: /* ListPredicateDef: PredicateDef ListPredicateDef  */
#line 494 "epddl.y"
                                  { (yyvsp[0].listpredicatedef_)->push_back((yyvsp[-1].predicatedef_)); (yyval.listpredicatedef_) = (yyvsp[0].listpredicatedef_); }
#line 2061 "Parser.C"
    break;

  case 22: /* ModalitiesDef: _LPAREN _SYMB_6 ListModalityName _RPAREN  */
#line 496 "epddl.y"
                                                         { std::reverse((yyvsp[-1].listmodalityname_)->begin(),(yyvsp[-1].listmodalityname_)->end()) ;(yyval.modalitiesdef_) = new EPDDLModalities((yyvsp[-1].listmodalityname_)); }
#line 2067 "Parser.C"
    break;

  case 23: /* ObservabilityGroupsDef: _LPAREN _SYMB_7 ListObservingAgentGroup _RPAREN  */
#line 498 "epddl.y"
                                                                         { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.observabilitygroupsdef_) = new EPDDLObsGroupsNames((yyvsp[-1].listobservingagentgroup_)); }
#line 2073 "Parser.C"
    break;

  case 24: /* ActionDef: _LPAREN _SYMB_8 ActionName ActionParameterDef ActionConditionsDef ActionTypeSignatureDef ActionPreDef ActionObsDef _RPAREN  */
#line 500 "epddl.y"
                                                                                                                                       { (yyval.actiondef_) = new EPDDLAction((yyvsp[-6].actionname_), (yyvsp[-5].actionparameterdef_), (yyvsp[-4].actionconditionsdef_), (yyvsp[-3].actiontypesignaturedef_), (yyvsp[-2].actionpredef_), (yyvsp[-1].actionobsdef_)); }
#line 2079 "Parser.C"
    break;

  case 25: /* ActionParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 502 "epddl.y"
                                                               { (yyval.actionparameterdef_) = new ActionParam((yyvsp[-1].typedvariablelist_)); }
#line 2085 "Parser.C"
    break;

  case 26: /* ActionConditionsDef: _SYMB_10 ConditionFormula  */
#line 504 "epddl.y"
                                                { (yyval.actionconditionsdef_) = new ActionCond((yyvsp[0].conditionformula_)); }
#line 2091 "Parser.C"
    break;

  case 27: /* ActionConditionsDef: %empty  */
#line 505 "epddl.y"
                { (yyval.actionconditionsdef_) = new EmptyActionCond(); }
#line 2097 "Parser.C"
    break;

  case 28: /* ActionTypeSignatureDef: _SYMB_11 _LPAREN ActionTypeName ListParameter _RPAREN  */
#line 507 "epddl.y"
                                                                               { (yyval.actiontypesignaturedef_) = new ActionSignature((yyvsp[-2].actiontypename_), (yyvsp[-1].listparameter_)); }
#line 2103 "Parser.C"
    break;

  case 29: /* ActionPreDef: _SYMB_12 Precondition  */
#line 509 "epddl.y"
                                     { (yyval.actionpredef_) = new ActionPre((yyvsp[0].precondition_)); }
#line 2109 "Parser.C"
    break;

  case 30: /* Precondition: Formula  */
#line 511 "epddl.y"
                       { (yyval.precondition_) = new FormulaPrecondition((yyvsp[0].formula_)); }
#line 2115 "Parser.C"
    break;

  case 31: /* Precondition: TrivialDef  */
#line 512 "epddl.y"
               { (yyval.precondition_) = new TrivialPrecondition((yyvsp[0].trivialdef_)); }
#line 2121 "Parser.C"
    break;

  case 32: /* ActionObsDef: _SYMB_13 ListObsConditionDef  */
#line 514 "epddl.y"
                                            { std::reverse((yyvsp[0].listobsconditiondef_)->begin(),(yyvsp[0].listobsconditiondef_)->end()) ;(yyval.actionobsdef_) = new ActionObs((yyvsp[0].listobsconditiondef_)); }
#line 2127 "Parser.C"
    break;

  case 33: /* ActionObsDef: %empty  */
#line 515 "epddl.y"
                { (yyval.actionobsdef_) = new EmptyActionObs(); }
#line 2133 "Parser.C"
    break;

  case 34: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _RPAREN  */
#line 517 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new EmptyObsCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2139 "Parser.C"
    break;

  case 35: /* ObsConditionDef: _LPAREN ObservingAgent ObservingAgentGroup _KW_if Formula _RPAREN  */
#line 518 "epddl.y"
                                                                      { (yyval.obsconditiondef_) = new ObsCond((yyvsp[-4].observingagent_), (yyvsp[-3].observingagentgroup_), (yyvsp[-1].formula_)); }
#line 2145 "Parser.C"
    break;

  case 36: /* ObsConditionDef: _LPAREN _KW_otherwise ObservingAgent ObservingAgentGroup _RPAREN  */
#line 519 "epddl.y"
                                                                     { (yyval.obsconditiondef_) = new ObsOtherwiseCond((yyvsp[-2].observingagent_), (yyvsp[-1].observingagentgroup_)); }
#line 2151 "Parser.C"
    break;

  case 37: /* ListObsConditionDef: ObsConditionDef  */
#line 521 "epddl.y"
                                      { (yyval.listobsconditiondef_) = new ListObsConditionDef(); (yyval.listobsconditiondef_)->push_back((yyvsp[0].obsconditiondef_)); }
#line 2157 "Parser.C"
    break;

  case 38: /* ListObsConditionDef: ObsConditionDef ListObsConditionDef  */
#line 522 "epddl.y"
                                        { (yyvsp[0].listobsconditiondef_)->push_back((yyvsp[-1].obsconditiondef_)); (yyval.listobsconditiondef_) = (yyvsp[0].listobsconditiondef_); }
#line 2163 "Parser.C"
    break;

  case 39: /* LibraryDef: _LPAREN _KW_define _LPAREN _KW_library Name _RPAREN ListLibraryItemDef _RPAREN  */
#line 524 "epddl.y"
                                                                                            { (yyval.librarydef_) = new EPDDLLibrary((yyvsp[-3]._name), (yyvsp[-1].listlibraryitemdef_)); }
#line 2169 "Parser.C"
    break;

  case 40: /* LibraryItemDef: RequireDef  */
#line 526 "epddl.y"
                            { (yyval.libraryitemdef_) = new EPDDLLibRequire((yyvsp[0].requiredef_)); }
#line 2175 "Parser.C"
    break;

  case 41: /* LibraryItemDef: ModalitiesDef  */
#line 527 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibModalities((yyvsp[0].modalitiesdef_)); }
#line 2181 "Parser.C"
    break;

  case 42: /* LibraryItemDef: ObservabilityGroupsDef  */
#line 528 "epddl.y"
                           { (yyval.libraryitemdef_) = new EPDDLLibObsGroups((yyvsp[0].observabilitygroupsdef_)); }
#line 2187 "Parser.C"
    break;

  case 43: /* LibraryItemDef: ActionTypeDef  */
#line 529 "epddl.y"
                  { (yyval.libraryitemdef_) = new EPDDLLibActionType((yyvsp[0].actiontypedef_)); }
#line 2193 "Parser.C"
    break;

  case 44: /* LibraryItemDef: EventDef  */
#line 530 "epddl.y"
             { (yyval.libraryitemdef_) = new EPDDLLibEvent((yyvsp[0].eventdef_)); }
#line 2199 "Parser.C"
    break;

  case 45: /* ListLibraryItemDef: %empty  */
#line 532 "epddl.y"
                                 { (yyval.listlibraryitemdef_) = new ListLibraryItemDef(); }
#line 2205 "Parser.C"
    break;

  case 46: /* ListLibraryItemDef: ListLibraryItemDef LibraryItemDef  */
#line 533 "epddl.y"
                                      { (yyvsp[-1].listlibraryitemdef_)->push_back((yyvsp[0].libraryitemdef_)); (yyval.listlibraryitemdef_) = (yyvsp[-1].listlibraryitemdef_); }
#line 2211 "Parser.C"
    break;

  case 47: /* ActionTypeDef: _LPAREN _SYMB_11 ActionTypeName ActionTypeParameterDef ActionTypeFrameDef ActionTypeEventsDef ActionTypeRelDef ActionTypeDesDef _RPAREN  */
#line 535 "epddl.y"
                                                                                                                                                        { (yyval.actiontypedef_) = new EPDDLActType((yyvsp[-6].actiontypename_), (yyvsp[-5].actiontypeparameterdef_), (yyvsp[-4].actiontypeframedef_), (yyvsp[-3].actiontypeeventsdef_), (yyvsp[-2].actiontypereldef_), (yyvsp[-1].actiontypedesdef_)); }
#line 2217 "Parser.C"
    break;

  case 48: /* ActionTypeParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 537 "epddl.y"
                                                                   { (yyval.actiontypeparameterdef_) = new ActTypeParam((yyvsp[-1].typedvariablelist_)); }
#line 2223 "Parser.C"
    break;

  case 49: /* ActionTypeFrameDef: _SYMB_14 _LPAREN ListObservingAgentGroup _RPAREN  */
#line 539 "epddl.y"
                                                                      { std::reverse((yyvsp[-1].listobservingagentgroup_)->begin(),(yyvsp[-1].listobservingagentgroup_)->end()) ;(yyval.actiontypeframedef_) = new ActTypeFrame((yyvsp[-1].listobservingagentgroup_)); }
#line 2229 "Parser.C"
    break;

  case 50: /* ActionTypeFrameDef: %empty  */
#line 540 "epddl.y"
                { (yyval.actiontypeframedef_) = new EmptyActTypeFrame(); }
#line 2235 "Parser.C"
    break;

  case 51: /* ActionTypeEventsDef: _SYMB_15 ListEventSignature  */
#line 542 "epddl.y"
                                                  { std::reverse((yyvsp[0].listeventsignature_)->begin(),(yyvsp[0].listeventsignature_)->end()) ;(yyval.actiontypeeventsdef_) = new ActTypeEvents((yyvsp[0].listeventsignature_)); }
#line 2241 "Parser.C"
    break;

  case 52: /* ActionTypeRelDef: _SYMB_16 ActionRelations  */
#line 544 "epddl.y"
                                            { (yyval.actiontypereldef_) = new ActTypeRel((yyvsp[0].actionrelations_)); }
#line 2247 "Parser.C"
    break;

  case 53: /* ActionTypeDesDef: _SYMB_17 _LPAREN ListEventName _RPAREN  */
#line 546 "epddl.y"
                                                          { std::reverse((yyvsp[-1].listeventname_)->begin(),(yyvsp[-1].listeventname_)->end()) ;(yyval.actiontypedesdef_) = new ActTypeDes((yyvsp[-1].listeventname_)); }
#line 2253 "Parser.C"
    break;

  case 54: /* EventSignature: _LPAREN EventName ListParameter _RPAREN  */
#line 548 "epddl.y"
                                                         { (yyval.eventsignature_) = new EventSign((yyvsp[-2].eventname_), (yyvsp[-1].listparameter_)); }
#line 2259 "Parser.C"
    break;

  case 55: /* ListEventSignature: EventSignature  */
#line 550 "epddl.y"
                                    { (yyval.listeventsignature_) = new ListEventSignature(); (yyval.listeventsignature_)->push_back((yyvsp[0].eventsignature_)); }
#line 2265 "Parser.C"
    break;

  case 56: /* ListEventSignature: EventSignature ListEventSignature  */
#line 551 "epddl.y"
                                      { (yyvsp[0].listeventsignature_)->push_back((yyvsp[-1].eventsignature_)); (yyval.listeventsignature_) = (yyvsp[0].listeventsignature_); }
#line 2271 "Parser.C"
    break;

  case 57: /* ActionRelations: ListEventRelation  */
#line 553 "epddl.y"
                                    { std::reverse((yyvsp[0].listeventrelation_)->begin(),(yyvsp[0].listeventrelation_)->end()) ;(yyval.actionrelations_) = new EventsActionRel((yyvsp[0].listeventrelation_)); }
#line 2277 "Parser.C"
    break;

  case 58: /* ActionRelations: TrivialDef  */
#line 554 "epddl.y"
               { (yyval.actionrelations_) = new TrivialActionRel((yyvsp[0].trivialdef_)); }
#line 2283 "Parser.C"
    break;

  case 59: /* EventRelation: _LPAREN AgentGroup ListEventNamePair _RPAREN  */
#line 556 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listeventnamepair_)->begin(),(yyvsp[-1].listeventnamepair_)->end()) ;(yyval.eventrelation_) = new EventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listeventnamepair_)); }
#line 2289 "Parser.C"
    break;

  case 60: /* EventRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 557 "epddl.y"
                                          { (yyval.eventrelation_) = new TrivialEventRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2295 "Parser.C"
    break;

  case 61: /* ListEventRelation: EventRelation  */
#line 559 "epddl.y"
                                  { (yyval.listeventrelation_) = new ListEventRelation(); (yyval.listeventrelation_)->push_back((yyvsp[0].eventrelation_)); }
#line 2301 "Parser.C"
    break;

  case 62: /* ListEventRelation: EventRelation ListEventRelation  */
#line 560 "epddl.y"
                                    { (yyvsp[0].listeventrelation_)->push_back((yyvsp[-1].eventrelation_)); (yyval.listeventrelation_) = (yyvsp[0].listeventrelation_); }
#line 2307 "Parser.C"
    break;

  case 63: /* EventNamePair: _LPAREN EventName EventName _RPAREN  */
#line 562 "epddl.y"
                                                    { (yyval.eventnamepair_) = new EventPair((yyvsp[-2].eventname_), (yyvsp[-1].eventname_)); }
#line 2313 "Parser.C"
    break;

  case 64: /* ListEventNamePair: EventNamePair  */
#line 564 "epddl.y"
                                  { (yyval.listeventnamepair_) = new ListEventNamePair(); (yyval.listeventnamepair_)->push_back((yyvsp[0].eventnamepair_)); }
#line 2319 "Parser.C"
    break;

  case 65: /* ListEventNamePair: EventNamePair ListEventNamePair  */
#line 565 "epddl.y"
                                    { (yyvsp[0].listeventnamepair_)->push_back((yyvsp[-1].eventnamepair_)); (yyval.listeventnamepair_) = (yyvsp[0].listeventnamepair_); }
#line 2325 "Parser.C"
    break;

  case 66: /* EventDef: _LPAREN _SYMB_18 EventName EventParameterDef EventPreDef EventPostDef _RPAREN  */
#line 567 "epddl.y"
                                                                                         { (yyval.eventdef_) = new EPDDLEvent((yyvsp[-4].eventname_), (yyvsp[-3].eventparameterdef_), (yyvsp[-2].eventpredef_), (yyvsp[-1].eventpostdef_)); }
#line 2331 "Parser.C"
    break;

  case 67: /* EventParameterDef: _SYMB_9 _LPAREN TypedVariableList _RPAREN  */
#line 569 "epddl.y"
                                                              { (yyval.eventparameterdef_) = new EventParam((yyvsp[-1].typedvariablelist_)); }
#line 2337 "Parser.C"
    break;

  case 68: /* EventPreDef: _SYMB_12 Precondition  */
#line 571 "epddl.y"
                                    { (yyval.eventpredef_) = new EventPre((yyvsp[0].precondition_)); }
#line 2343 "Parser.C"
    break;

  case 69: /* EventPostDef: _SYMB_19 EventPostconditions  */
#line 573 "epddl.y"
                                            { (yyval.eventpostdef_) = new EventPost((yyvsp[0].eventpostconditions_)); }
#line 2349 "Parser.C"
    break;

  case 70: /* EventPostDef: %empty  */
#line 574 "epddl.y"
                { (yyval.eventpostdef_) = new EmptyEventPost(); }
#line 2355 "Parser.C"
    break;

  case 71: /* EventPostconditions: ListPostcondition  */
#line 576 "epddl.y"
                                        { std::reverse((yyvsp[0].listpostcondition_)->begin(),(yyvsp[0].listpostcondition_)->end()) ;(yyval.eventpostconditions_) = new Postconditions((yyvsp[0].listpostcondition_)); }
#line 2361 "Parser.C"
    break;

  case 72: /* EventPostconditions: TrivialDef  */
#line 577 "epddl.y"
               { (yyval.eventpostconditions_) = new TrivialPostconditions((yyvsp[0].trivialdef_)); }
#line 2367 "Parser.C"
    break;

  case 73: /* Postcondition: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN ListLiteralPostcondition _RPAREN  */
#line 579 "epddl.y"
                                                                                                      { std::reverse((yyvsp[-1].listliteralpostcondition_)->begin(),(yyvsp[-1].listliteralpostcondition_)->end()) ;(yyval.postcondition_) = new ForallPostcondition((yyvsp[-3].typedvariablelist_), (yyvsp[-1].listliteralpostcondition_)); }
#line 2373 "Parser.C"
    break;

  case 74: /* Postcondition: LiteralPostcondition  */
#line 580 "epddl.y"
                         { (yyval.postcondition_) = new SinglePostcondition((yyvsp[0].literalpostcondition_)); }
#line 2379 "Parser.C"
    break;

  case 75: /* Postcondition: _LPAREN Variable _RPAREN  */
#line 581 "epddl.y"
                             { (yyval.postcondition_) = new VarPostcondition((yyvsp[-1]._variable)); }
#line 2385 "Parser.C"
    break;

  case 76: /* ListPostcondition: Postcondition  */
#line 583 "epddl.y"
                                  { (yyval.listpostcondition_) = new ListPostcondition(); (yyval.listpostcondition_)->push_back((yyvsp[0].postcondition_)); }
#line 2391 "Parser.C"
    break;

  case 77: /* ListPostcondition: Postcondition ListPostcondition  */
#line 584 "epddl.y"
                                    { (yyvsp[0].listpostcondition_)->push_back((yyvsp[-1].postcondition_)); (yyval.listpostcondition_) = (yyvsp[0].listpostcondition_); }
#line 2397 "Parser.C"
    break;

  case 78: /* LiteralPostcondition: _LPAREN _KW_set Literal _KW_iff FormulaOrEmpty _RPAREN  */
#line 586 "epddl.y"
                                                                              { (yyval.literalpostcondition_) = new LiteralPost((yyvsp[-3].literal_), (yyvsp[-1].formulaorempty_)); }
#line 2403 "Parser.C"
    break;

  case 79: /* ListLiteralPostcondition: LiteralPostcondition  */
#line 588 "epddl.y"
                                                { (yyval.listliteralpostcondition_) = new ListLiteralPostcondition(); (yyval.listliteralpostcondition_)->push_back((yyvsp[0].literalpostcondition_)); }
#line 2409 "Parser.C"
    break;

  case 80: /* ListLiteralPostcondition: LiteralPostcondition ListLiteralPostcondition  */
#line 589 "epddl.y"
                                                  { (yyvsp[0].listliteralpostcondition_)->push_back((yyvsp[-1].literalpostcondition_)); (yyval.listliteralpostcondition_) = (yyvsp[0].listliteralpostcondition_); }
#line 2415 "Parser.C"
    break;

  case 81: /* FormulaOrEmpty: Formula  */
#line 591 "epddl.y"
                         { (yyval.formulaorempty_) = new NonTrivialFormula((yyvsp[0].formula_)); }
#line 2421 "Parser.C"
    break;

  case 82: /* FormulaOrEmpty: TrivialDef  */
#line 592 "epddl.y"
               { (yyval.formulaorempty_) = new TrivialFormula((yyvsp[0].trivialdef_)); }
#line 2427 "Parser.C"
    break;

  case 83: /* ProblemDef: _LPAREN _KW_define _LPAREN _KW_problem Name _RPAREN ListProblemItemDef _RPAREN  */
#line 594 "epddl.y"
                                                                                            { (yyval.problemdef_) = new EPDDLProblem((yyvsp[-3]._name), (yyvsp[-1].listproblemitemdef_)); }
#line 2433 "Parser.C"
    break;

  case 84: /* ProblemItemDef: ProblemDomainNameDef  */
#line 596 "epddl.y"
                                      { (yyval.problemitemdef_) = new EPDDLProbDomain((yyvsp[0].problemdomainnamedef_)); }
#line 2439 "Parser.C"
    break;

  case 85: /* ProblemItemDef: RequireDef  */
#line 597 "epddl.y"
               { (yyval.problemitemdef_) = new EPDDLProbRequire((yyvsp[0].requiredef_)); }
#line 2445 "Parser.C"
    break;

  case 86: /* ProblemItemDef: ModalitiesDef  */
#line 598 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbModalities((yyvsp[0].modalitiesdef_)); }
#line 2451 "Parser.C"
    break;

  case 87: /* ProblemItemDef: AgentNamesDef  */
#line 599 "epddl.y"
                  { (yyval.problemitemdef_) = new EPDDLProbAgents((yyvsp[0].agentnamesdef_)); }
#line 2457 "Parser.C"
    break;

  case 88: /* ProblemItemDef: AgentGroupsListDef  */
#line 600 "epddl.y"
                       { (yyval.problemitemdef_) = new EPDDLProbAgentGroups((yyvsp[0].agentgroupslistdef_)); }
#line 2463 "Parser.C"
    break;

  case 89: /* ProblemItemDef: ObjectNamesDef  */
#line 601 "epddl.y"
                   { (yyval.problemitemdef_) = new EPDDLProbObjects((yyvsp[0].objectnamesdef_)); }
#line 2469 "Parser.C"
    break;

  case 90: /* ProblemItemDef: FactListDef  */
#line 602 "epddl.y"
                { (yyval.problemitemdef_) = new EPDDLProbFacts((yyvsp[0].factlistdef_)); }
#line 2475 "Parser.C"
    break;

  case 91: /* ProblemItemDef: InitDef  */
#line 603 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbInit((yyvsp[0].initdef_)); }
#line 2481 "Parser.C"
    break;

  case 92: /* ProblemItemDef: InitialModelDef  */
#line 604 "epddl.y"
                    { (yyval.problemitemdef_) = new EPDDLProbInitModel((yyvsp[0].initialmodeldef_)); }
#line 2487 "Parser.C"
    break;

  case 93: /* ProblemItemDef: GoalDef  */
#line 605 "epddl.y"
            { (yyval.problemitemdef_) = new EPDDLProbGoal((yyvsp[0].goaldef_)); }
#line 2493 "Parser.C"
    break;

  case 94: /* ListProblemItemDef: %empty  */
#line 607 "epddl.y"
                                 { (yyval.listproblemitemdef_) = new ListProblemItemDef(); }
#line 2499 "Parser.C"
    break;

  case 95: /* ListProblemItemDef: ListProblemItemDef ProblemItemDef  */
#line 608 "epddl.y"
                                      { (yyvsp[-1].listproblemitemdef_)->push_back((yyvsp[0].problemitemdef_)); (yyval.listproblemitemdef_) = (yyvsp[-1].listproblemitemdef_); }
#line 2505 "Parser.C"
    break;

  case 96: /* ProblemDomainNameDef: _LPAREN _SYMB_20 Name _RPAREN  */
#line 610 "epddl.y"
                                                     { (yyval.problemdomainnamedef_) = new EPDDLDomainName((yyvsp[-1]._name)); }
#line 2511 "Parser.C"
    break;

  case 97: /* AgentNamesDef: _LPAREN _SYMB_21 ListAgentName _RPAREN  */
#line 612 "epddl.y"
                                                       { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentnamesdef_) = new EPDDLAgentNames((yyvsp[-1].listagentname_)); }
#line 2517 "Parser.C"
    break;

  case 98: /* AgentGroupsListDef: _LPAREN _SYMB_22 ListAgentGroupDef _RPAREN  */
#line 614 "epddl.y"
                                                                { (yyval.agentgroupslistdef_) = new EPDDLAgentGroupsList((yyvsp[-1].listagentgroupdef_)); }
#line 2523 "Parser.C"
    break;

  case 99: /* AgentGroupDef: _LPAREN _LBRACE ListAgentName _RBRACE _KW_as AgentGroupName _RPAREN  */
#line 616 "epddl.y"
                                                                                    { std::reverse((yyvsp[-4].listagentname_)->begin(),(yyvsp[-4].listagentname_)->end()) ;(yyval.agentgroupdef_) = new EPDDLAgentGroupDef((yyvsp[-4].listagentname_), (yyvsp[-1].agentgroupname_)); }
#line 2529 "Parser.C"
    break;

  case 100: /* ListAgentGroupDef: %empty  */
#line 618 "epddl.y"
                                { (yyval.listagentgroupdef_) = new ListAgentGroupDef(); }
#line 2535 "Parser.C"
    break;

  case 101: /* ListAgentGroupDef: ListAgentGroupDef AgentGroupDef  */
#line 619 "epddl.y"
                                    { (yyvsp[-1].listagentgroupdef_)->push_back((yyvsp[0].agentgroupdef_)); (yyval.listagentgroupdef_) = (yyvsp[-1].listagentgroupdef_); }
#line 2541 "Parser.C"
    break;

  case 102: /* ObjectNamesDef: _LPAREN _SYMB_25 TypedIdentList _RPAREN  */
#line 621 "epddl.y"
                                                         { (yyval.objectnamesdef_) = new EPDDLObjectNames((yyvsp[-1].typedidentlist_)); }
#line 2547 "Parser.C"
    break;

  case 103: /* FactListDef: _LPAREN _SYMB_26 ListFactDef _RPAREN  */
#line 623 "epddl.y"
                                                   { std::reverse((yyvsp[-1].listfactdef_)->begin(),(yyvsp[-1].listfactdef_)->end()) ;(yyval.factlistdef_) = new EPDDLFactList((yyvsp[-1].listfactdef_)); }
#line 2553 "Parser.C"
    break;

  case 104: /* FactDef: _LPAREN PredicateName ListEntity _RPAREN  */
#line 625 "epddl.y"
                                                   { (yyval.factdef_) = new EPDDLFactDef((yyvsp[-2].predicatename_), (yyvsp[-1].listentity_)); }
#line 2559 "Parser.C"
    break;

  case 105: /* ListFactDef: FactDef  */
#line 627 "epddl.y"
                      { (yyval.listfactdef_) = new ListFactDef(); (yyval.listfactdef_)->push_back((yyvsp[0].factdef_)); }
#line 2565 "Parser.C"
    break;

  case 106: /* ListFactDef: FactDef ListFactDef  */
#line 628 "epddl.y"
                        { (yyvsp[0].listfactdef_)->push_back((yyvsp[-1].factdef_)); (yyval.listfactdef_) = (yyvsp[0].listfactdef_); }
#line 2571 "Parser.C"
    break;

  case 107: /* InitDef: _LPAREN _SYMB_27 InitialStateDescr _RPAREN  */
#line 630 "epddl.y"
                                                     { (yyval.initdef_) = new EPDDLInitialState((yyvsp[-1].initialstatedescr_)); }
#line 2577 "Parser.C"
    break;

  case 108: /* InitialStateDescr: ListFTheoryFormula  */
#line 632 "epddl.y"
                                       { std::reverse((yyvsp[0].listftheoryformula_)->begin(),(yyvsp[0].listftheoryformula_)->end()) ;(yyval.initialstatedescr_) = new FinitaryTheoryDescr((yyvsp[0].listftheoryformula_)); }
#line 2583 "Parser.C"
    break;

  case 109: /* InitialStateDescr: _LPAREN _SYMB_28 ModelName _RPAREN  */
#line 633 "epddl.y"
                                       { (yyval.initialstatedescr_) = new InitialModelDescr((yyvsp[-1].modelname_)); }
#line 2589 "Parser.C"
    break;

  case 110: /* FTheoryFormula: PredicateFormula  */
#line 635 "epddl.y"
                                  { (yyval.ftheoryformula_) = new FTheoryPredForm((yyvsp[0].predicateformula_)); }
#line 2595 "Parser.C"
    break;

  case 111: /* FTheoryFormula: _LBRACK AllAgents _RBRACK PredicateFormula  */
#line 636 "epddl.y"
                                               { (yyval.ftheoryformula_) = new FTheoryCKPredForm((yyvsp[-2].allagents_), (yyvsp[0].predicateformula_)); }
#line 2601 "Parser.C"
    break;

  case 112: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KPredicateFormula  */
#line 637 "epddl.y"
                                                { (yyval.ftheoryformula_) = new FTheoryCKKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kpredicateformula_)); }
#line 2607 "Parser.C"
    break;

  case 113: /* FTheoryFormula: _LBRACK AllAgents _RBRACK KWPredicateFormula  */
#line 638 "epddl.y"
                                                 { (yyval.ftheoryformula_) = new FTheoryCKOrKPredForm((yyvsp[-2].allagents_), (yyvsp[0].kwpredicateformula_)); }
#line 2613 "Parser.C"
    break;

  case 114: /* FTheoryFormula: _LBRACK AllAgents _RBRACK NotKWPredicateFormula  */
#line 639 "epddl.y"
                                                    { (yyval.ftheoryformula_) = new FTheoryCKAndKPredForm((yyvsp[-2].allagents_), (yyvsp[0].notkwpredicateformula_)); }
#line 2619 "Parser.C"
    break;

  case 115: /* FTheoryFormula: _LPAREN FTheoryFormula _RPAREN  */
#line 640 "epddl.y"
                                   { (yyval.ftheoryformula_) = (yyvsp[-1].ftheoryformula_); }
#line 2625 "Parser.C"
    break;

  case 116: /* ListFTheoryFormula: FTheoryFormula  */
#line 642 "epddl.y"
                                    { (yyval.listftheoryformula_) = new ListFTheoryFormula(); (yyval.listftheoryformula_)->push_back((yyvsp[0].ftheoryformula_)); }
#line 2631 "Parser.C"
    break;

  case 117: /* ListFTheoryFormula: FTheoryFormula ListFTheoryFormula  */
#line 643 "epddl.y"
                                      { (yyvsp[0].listftheoryformula_)->push_back((yyvsp[-1].ftheoryformula_)); (yyval.listftheoryformula_) = (yyvsp[0].listftheoryformula_); }
#line 2637 "Parser.C"
    break;

  case 118: /* KPredicateFormula: _LBRACK AgentName _RBRACK PredicateFormula  */
#line 645 "epddl.y"
                                                               { (yyval.kpredicateformula_) = new KPredFormula((yyvsp[-2]._agentname), (yyvsp[0].predicateformula_)); }
#line 2643 "Parser.C"
    break;

  case 119: /* KPredicateFormula: _LPAREN KPredicateFormula _RPAREN  */
#line 646 "epddl.y"
                                      { (yyval.kpredicateformula_) = (yyvsp[-1].kpredicateformula_); }
#line 2649 "Parser.C"
    break;

  case 120: /* KWPredicateFormula: KnowsWhether PredicateFormula  */
#line 648 "epddl.y"
                                                   { (yyval.kwpredicateformula_) = new KWPredFormula((yyvsp[-1].knowswhether_), (yyvsp[0].predicateformula_)); }
#line 2655 "Parser.C"
    break;

  case 121: /* KWPredicateFormula: _LPAREN KWPredicateFormula _RPAREN  */
#line 649 "epddl.y"
                                       { (yyval.kwpredicateformula_) = (yyvsp[-1].kwpredicateformula_); }
#line 2661 "Parser.C"
    break;

  case 122: /* NotKWPredicateFormula: _LPAREN _KW_not KnowsWhether PredicateFormula _RPAREN  */
#line 651 "epddl.y"
                                                                              { (yyval.notkwpredicateformula_) = new NotKWPredFormula((yyvsp[-2].knowswhether_), (yyvsp[-1].predicateformula_)); }
#line 2667 "Parser.C"
    break;

  case 123: /* NotKWPredicateFormula: _LPAREN NotKWPredicateFormula _RPAREN  */
#line 652 "epddl.y"
                                          { (yyval.notkwpredicateformula_) = (yyvsp[-1].notkwpredicateformula_); }
#line 2673 "Parser.C"
    break;

  case 124: /* InitialModelDef: _LPAREN _SYMB_31 ModelName ModelWorldsDef ModelRelDef ModelValDef ModelDesDef _RPAREN  */
#line 654 "epddl.y"
                                                                                                        { (yyval.initialmodeldef_) = new EPDDLInitialModel((yyvsp[-5].modelname_), (yyvsp[-4].modelworldsdef_), (yyvsp[-3].modelreldef_), (yyvsp[-2].modelvaldef_), (yyvsp[-1].modeldesdef_)); }
#line 2679 "Parser.C"
    break;

  case 125: /* ModelWorldsDef: _SYMB_32 _LPAREN ListWorldName _RPAREN  */
#line 656 "epddl.y"
                                                        { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modelworldsdef_) = new ModelWorlds((yyvsp[-1].listworldname_)); }
#line 2685 "Parser.C"
    break;

  case 126: /* ModelRelDef: _SYMB_16 ModelRelations  */
#line 658 "epddl.y"
                                      { (yyval.modelreldef_) = new ModelRel((yyvsp[0].modelrelations_)); }
#line 2691 "Parser.C"
    break;

  case 127: /* ModelValDef: _SYMB_33 ModelValuation  */
#line 660 "epddl.y"
                                      { (yyval.modelvaldef_) = new ModelVal((yyvsp[0].modelvaluation_)); }
#line 2697 "Parser.C"
    break;

  case 128: /* ModelDesDef: _SYMB_17 _LPAREN ListWorldName _RPAREN  */
#line 662 "epddl.y"
                                                     { std::reverse((yyvsp[-1].listworldname_)->begin(),(yyvsp[-1].listworldname_)->end()) ;(yyval.modeldesdef_) = new ModelDes((yyvsp[-1].listworldname_)); }
#line 2703 "Parser.C"
    break;

  case 129: /* ModelRelations: ListWorldRelation  */
#line 664 "epddl.y"
                                   { std::reverse((yyvsp[0].listworldrelation_)->begin(),(yyvsp[0].listworldrelation_)->end()) ;(yyval.modelrelations_) = new WorldsModelRel((yyvsp[0].listworldrelation_)); }
#line 2709 "Parser.C"
    break;

  case 130: /* ModelRelations: TrivialDef  */
#line 665 "epddl.y"
               { (yyval.modelrelations_) = new TrivialModelRel((yyvsp[0].trivialdef_)); }
#line 2715 "Parser.C"
    break;

  case 131: /* ModelValuation: ListWorldValuation  */
#line 667 "epddl.y"
                                    { std::reverse((yyvsp[0].listworldvaluation_)->begin(),(yyvsp[0].listworldvaluation_)->end()) ;(yyval.modelvaluation_) = new WorldsModelVal((yyvsp[0].listworldvaluation_)); }
#line 2721 "Parser.C"
    break;

  case 132: /* ModelValuation: TrivialDef  */
#line 668 "epddl.y"
               { (yyval.modelvaluation_) = new TrivialModelVal((yyvsp[0].trivialdef_)); }
#line 2727 "Parser.C"
    break;

  case 133: /* WorldRelation: _LPAREN AgentGroup ListWorldNamePair _RPAREN  */
#line 670 "epddl.y"
                                                             { std::reverse((yyvsp[-1].listworldnamepair_)->begin(),(yyvsp[-1].listworldnamepair_)->end()) ;(yyval.worldrelation_) = new WorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].listworldnamepair_)); }
#line 2733 "Parser.C"
    break;

  case 134: /* WorldRelation: _LPAREN AgentGroup TrivialDef _RPAREN  */
#line 671 "epddl.y"
                                          { (yyval.worldrelation_) = new TrivialWorldRel((yyvsp[-2].agentgroup_), (yyvsp[-1].trivialdef_)); }
#line 2739 "Parser.C"
    break;

  case 135: /* ListWorldRelation: WorldRelation  */
#line 673 "epddl.y"
                                  { (yyval.listworldrelation_) = new ListWorldRelation(); (yyval.listworldrelation_)->push_back((yyvsp[0].worldrelation_)); }
#line 2745 "Parser.C"
    break;

  case 136: /* ListWorldRelation: WorldRelation ListWorldRelation  */
#line 674 "epddl.y"
                                    { (yyvsp[0].listworldrelation_)->push_back((yyvsp[-1].worldrelation_)); (yyval.listworldrelation_) = (yyvsp[0].listworldrelation_); }
#line 2751 "Parser.C"
    break;

  case 137: /* WorldNamePair: _LPAREN WorldName WorldName _RPAREN  */
#line 676 "epddl.y"
                                                    { (yyval.worldnamepair_) = new WorldPair((yyvsp[-2].worldname_), (yyvsp[-1].worldname_)); }
#line 2757 "Parser.C"
    break;

  case 138: /* ListWorldNamePair: WorldNamePair  */
#line 678 "epddl.y"
                                  { (yyval.listworldnamepair_) = new ListWorldNamePair(); (yyval.listworldnamepair_)->push_back((yyvsp[0].worldnamepair_)); }
#line 2763 "Parser.C"
    break;

  case 139: /* ListWorldNamePair: WorldNamePair ListWorldNamePair  */
#line 679 "epddl.y"
                                    { (yyvsp[0].listworldnamepair_)->push_back((yyvsp[-1].worldnamepair_)); (yyval.listworldnamepair_) = (yyvsp[0].listworldnamepair_); }
#line 2769 "Parser.C"
    break;

  case 140: /* WorldValuation: _LPAREN WorldName _LBRACK ListLiteral _RBRACK _RPAREN  */
#line 681 "epddl.y"
                                                                       { (yyval.worldvaluation_) = new WorldVal((yyvsp[-4].worldname_), (yyvsp[-2].listliteral_)); }
#line 2775 "Parser.C"
    break;

  case 141: /* ListWorldValuation: WorldValuation  */
#line 683 "epddl.y"
                                    { (yyval.listworldvaluation_) = new ListWorldValuation(); (yyval.listworldvaluation_)->push_back((yyvsp[0].worldvaluation_)); }
#line 2781 "Parser.C"
    break;

  case 142: /* ListWorldValuation: WorldValuation ListWorldValuation  */
#line 684 "epddl.y"
                                      { (yyvsp[0].listworldvaluation_)->push_back((yyvsp[-1].worldvaluation_)); (yyval.listworldvaluation_) = (yyvsp[0].listworldvaluation_); }
#line 2787 "Parser.C"
    break;

  case 143: /* GoalDef: _LPAREN _SYMB_34 Formula _RPAREN  */
#line 686 "epddl.y"
                                           { (yyval.goaldef_) = new EPDDLGoals((yyvsp[-1].formula_)); }
#line 2793 "Parser.C"
    break;

  case 144: /* Formula: _LPAREN _KW_imply Formula Formula _RPAREN  */
#line 688 "epddl.y"
                                                    { (yyval.formula_) = new ImplyFormula((yyvsp[-2].formula_), (yyvsp[-1].formula_)); }
#line 2799 "Parser.C"
    break;

  case 145: /* Formula: _LPAREN _KW_or Formula ListFormula _RPAREN  */
#line 689 "epddl.y"
                                               { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new OrFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2805 "Parser.C"
    break;

  case 146: /* Formula: _LPAREN _KW_and Formula ListFormula _RPAREN  */
#line 690 "epddl.y"
                                                { std::reverse((yyvsp[-1].listformula_)->begin(),(yyvsp[-1].listformula_)->end()) ;(yyval.formula_) = new AndFormula((yyvsp[-2].formula_), (yyvsp[-1].listformula_)); }
#line 2811 "Parser.C"
    break;

  case 147: /* Formula: _LPAREN _KW_not Formula _RPAREN  */
#line 691 "epddl.y"
                                    { (yyval.formula_) = new NotFormula((yyvsp[-1].formula_)); }
#line 2817 "Parser.C"
    break;

  case 148: /* Formula: Modality Formula  */
#line 692 "epddl.y"
                     { (yyval.formula_) = new ModalFormula((yyvsp[-1].modality_), (yyvsp[0].formula_)); }
#line 2823 "Parser.C"
    break;

  case 149: /* Formula: _LPAREN Variable _RPAREN  */
#line 693 "epddl.y"
                             { (yyval.formula_) = new VarFormula((yyvsp[-1]._variable)); }
#line 2829 "Parser.C"
    break;

  case 150: /* Formula: AtomicFormula  */
#line 694 "epddl.y"
                  { (yyval.formula_) = new AtmFormula((yyvsp[0].atomicformula_)); }
#line 2835 "Parser.C"
    break;

  case 151: /* Formula: AtomicEqFormula  */
#line 695 "epddl.y"
                    { (yyval.formula_) = new AtmEqFormula((yyvsp[0].atomiceqformula_)); }
#line 2841 "Parser.C"
    break;

  case 152: /* Formula: _KW_true  */
#line 696 "epddl.y"
             { (yyval.formula_) = new TrueFormula(); }
#line 2847 "Parser.C"
    break;

  case 153: /* Formula: _KW_false  */
#line 697 "epddl.y"
              { (yyval.formula_) = new FalseFormula(); }
#line 2853 "Parser.C"
    break;

  case 154: /* Formula: _LPAREN Formula _RPAREN  */
#line 698 "epddl.y"
                            { (yyval.formula_) = (yyvsp[-1].formula_); }
#line 2859 "Parser.C"
    break;

  case 155: /* ListFormula: Formula  */
#line 700 "epddl.y"
                      { (yyval.listformula_) = new ListFormula(); (yyval.listformula_)->push_back((yyvsp[0].formula_)); }
#line 2865 "Parser.C"
    break;

  case 156: /* ListFormula: Formula ListFormula  */
#line 701 "epddl.y"
                        { (yyvsp[0].listformula_)->push_back((yyvsp[-1].formula_)); (yyval.listformula_) = (yyvsp[0].listformula_); }
#line 2871 "Parser.C"
    break;

  case 157: /* AtomicFormula: _LPAREN PredicateName ListMetaTerm _RPAREN  */
#line 703 "epddl.y"
                                                           { (yyval.atomicformula_) = new Predicate((yyvsp[-2].predicatename_), (yyvsp[-1].listmetaterm_)); }
#line 2877 "Parser.C"
    break;

  case 158: /* AtomicEqFormula: _LPAREN _EQ Term Term _RPAREN  */
#line 705 "epddl.y"
                                                { (yyval.atomiceqformula_) = new EqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 2883 "Parser.C"
    break;

  case 159: /* MetaTerm: Term  */
#line 707 "epddl.y"
                { (yyval.metaterm_) = new EPDDLMetaTerm((yyvsp[0].term_)); }
#line 2889 "Parser.C"
    break;

  case 160: /* MetaTerm: AnonVarAgent  */
#line 708 "epddl.y"
                 { (yyval.metaterm_) = new EPDDLMetaTermAnonVar((yyvsp[0].anonvaragent_)); }
#line 2895 "Parser.C"
    break;

  case 161: /* ListMetaTerm: %empty  */
#line 710 "epddl.y"
                           { (yyval.listmetaterm_) = new ListMetaTerm(); }
#line 2901 "Parser.C"
    break;

  case 162: /* ListMetaTerm: ListMetaTerm MetaTerm  */
#line 711 "epddl.y"
                          { (yyvsp[-1].listmetaterm_)->push_back((yyvsp[0].metaterm_)); (yyval.listmetaterm_) = (yyvsp[-1].listmetaterm_); }
#line 2907 "Parser.C"
    break;

  case 163: /* Term: GroundTerm  */
#line 713 "epddl.y"
                  { (yyval.term_) = new EPDDLGroundTerm((yyvsp[0].groundterm_)); }
#line 2913 "Parser.C"
    break;

  case 164: /* Term: Variable  */
#line 714 "epddl.y"
             { (yyval.term_) = new EPDDLTermVar((yyvsp[0]._variable)); }
#line 2919 "Parser.C"
    break;

  case 165: /* ListTerm: %empty  */
#line 716 "epddl.y"
                       { (yyval.listterm_) = new ListTerm(); }
#line 2925 "Parser.C"
    break;

  case 166: /* ListTerm: ListTerm Term  */
#line 717 "epddl.y"
                  { (yyvsp[-1].listterm_)->push_back((yyvsp[0].term_)); (yyval.listterm_) = (yyvsp[-1].listterm_); }
#line 2931 "Parser.C"
    break;

  case 167: /* GroundTerm: Name  */
#line 719 "epddl.y"
                  { (yyval.groundterm_) = new EPDDLGroundTermName((yyvsp[0]._name)); }
#line 2937 "Parser.C"
    break;

  case 168: /* GroundTerm: AgentName  */
#line 720 "epddl.y"
              { (yyval.groundterm_) = new EPDDLGroundTermAgName((yyvsp[0]._agentname)); }
#line 2943 "Parser.C"
    break;

  case 169: /* ListGroundTerm: %empty  */
#line 722 "epddl.y"
                             { (yyval.listgroundterm_) = new ListGroundTerm(); }
#line 2949 "Parser.C"
    break;

  case 170: /* ListGroundTerm: ListGroundTerm GroundTerm  */
#line 723 "epddl.y"
                              { (yyvsp[-1].listgroundterm_)->push_back((yyvsp[0].groundterm_)); (yyval.listgroundterm_) = (yyvsp[-1].listgroundterm_); }
#line 2955 "Parser.C"
    break;

  case 171: /* Modality: SingleModality  */
#line 725 "epddl.y"
                          { (yyval.modality_) = new EPDDLLabeledMod((yyvsp[0].singlemodality_)); }
#line 2961 "Parser.C"
    break;

  case 172: /* Modality: GroupModality  */
#line 726 "epddl.y"
                  { (yyval.modality_) = new EPDDLLabeledGroupMod((yyvsp[0].groupmodality_)); }
#line 2967 "Parser.C"
    break;

  case 173: /* SingleModality: _LBRACK ModalityLabel ModalityAgent _RBRACK  */
#line 728 "epddl.y"
                                                             { (yyval.singlemodality_) = new LabBoxMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2973 "Parser.C"
    break;

  case 174: /* SingleModality: _LT ModalityLabel ModalityAgent _GT  */
#line 729 "epddl.y"
                                        { (yyval.singlemodality_) = new LabDiamondMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagent_)); }
#line 2979 "Parser.C"
    break;

  case 175: /* GroupModality: _LBRACK ModalityLabel ModalityAgentGroup _RBRACK  */
#line 731 "epddl.y"
                                                                 { (yyval.groupmodality_) = new LabBoxGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2985 "Parser.C"
    break;

  case 176: /* GroupModality: _LT ModalityLabel ModalityAgentGroup _GT  */
#line 732 "epddl.y"
                                             { (yyval.groupmodality_) = new LabDiamondGroupMod((yyvsp[-2].modalitylabel_), (yyvsp[-1].modalityagentgroup_)); }
#line 2991 "Parser.C"
    break;

  case 177: /* ModalityLabel: ModalityName  */
#line 734 "epddl.y"
                             { (yyval.modalitylabel_) = new ModLabel((yyvsp[0]._modalityname)); }
#line 2997 "Parser.C"
    break;

  case 178: /* ModalityLabel: %empty  */
#line 735 "epddl.y"
                { (yyval.modalitylabel_) = new EmptyModLabel(); }
#line 3003 "Parser.C"
    break;

  case 179: /* KnowsWhether: _LBRACK ModalityName AgentName _RBRACK  */
#line 737 "epddl.y"
                                                      { (yyval.knowswhether_) = new KnowsWhetherMod((yyvsp[-2]._modalityname), (yyvsp[-1]._agentname)); }
#line 3009 "Parser.C"
    break;

  case 180: /* Literal: AtomicFormula  */
#line 739 "epddl.y"
                        { (yyval.literal_) = new PosLiteral((yyvsp[0].atomicformula_)); }
#line 3015 "Parser.C"
    break;

  case 181: /* Literal: _LPAREN _KW_not AtomicFormula _RPAREN  */
#line 740 "epddl.y"
                                          { (yyval.literal_) = new NegLiteral((yyvsp[-1].atomicformula_)); }
#line 3021 "Parser.C"
    break;

  case 182: /* ListLiteral: %empty  */
#line 742 "epddl.y"
                          { (yyval.listliteral_) = new ListLiteral(); }
#line 3027 "Parser.C"
    break;

  case 183: /* ListLiteral: ListLiteral Literal  */
#line 743 "epddl.y"
                        { (yyvsp[-1].listliteral_)->push_back((yyvsp[0].literal_)); (yyval.listliteral_) = (yyvsp[-1].listliteral_); }
#line 3033 "Parser.C"
    break;

  case 184: /* ConditionFormula: _LPAREN _KW_and Condition ListCondition _RPAREN  */
#line 745 "epddl.y"
                                                                   { std::reverse((yyvsp[-1].listcondition_)->begin(),(yyvsp[-1].listcondition_)->end()) ;(yyval.conditionformula_) = new AndCondFomula((yyvsp[-2].condition_), (yyvsp[-1].listcondition_)); }
#line 3039 "Parser.C"
    break;

  case 185: /* ConditionFormula: Condition  */
#line 746 "epddl.y"
              { (yyval.conditionformula_) = new CondFomula((yyvsp[0].condition_)); }
#line 3045 "Parser.C"
    break;

  case 186: /* Condition: AtomicCondition  */
#line 748 "epddl.y"
                            { (yyval.condition_) = new AtmCond((yyvsp[0].atomiccondition_)); }
#line 3051 "Parser.C"
    break;

  case 187: /* Condition: _LPAREN _KW_not AtomicCondition _RPAREN  */
#line 749 "epddl.y"
                                            { (yyval.condition_) = new NotAtmCond((yyvsp[-1].atomiccondition_)); }
#line 3057 "Parser.C"
    break;

  case 188: /* ListCondition: Condition  */
#line 751 "epddl.y"
                          { (yyval.listcondition_) = new ListCondition(); (yyval.listcondition_)->push_back((yyvsp[0].condition_)); }
#line 3063 "Parser.C"
    break;

  case 189: /* ListCondition: Condition ListCondition  */
#line 752 "epddl.y"
                            { (yyvsp[0].listcondition_)->push_back((yyvsp[-1].condition_)); (yyval.listcondition_) = (yyvsp[0].listcondition_); }
#line 3069 "Parser.C"
    break;

  case 190: /* AtomicCondition: _LPAREN PredicateName ListTerm _RPAREN  */
#line 754 "epddl.y"
                                                         { (yyval.atomiccondition_) = new AtmCondPredicate((yyvsp[-2].predicatename_), (yyvsp[-1].listterm_)); }
#line 3075 "Parser.C"
    break;

  case 191: /* AtomicCondition: _LPAREN _EQ Term Term _RPAREN  */
#line 755 "epddl.y"
                                  { (yyval.atomiccondition_) = new AtmCondEqFormula((yyvsp[-2].term_), (yyvsp[-1].term_)); }
#line 3081 "Parser.C"
    break;

  case 192: /* PredicateFormula: _LPAREN _KW_imply PredicateFormula PredicateFormula _RPAREN  */
#line 757 "epddl.y"
                                                                               { (yyval.predicateformula_) = new ImplyPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].predicateformula_)); }
#line 3087 "Parser.C"
    break;

  case 193: /* PredicateFormula: _LPAREN _KW_or PredicateFormula ListPredicateFormula _RPAREN  */
#line 758 "epddl.y"
                                                                 { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new OrPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3093 "Parser.C"
    break;

  case 194: /* PredicateFormula: _LPAREN _KW_and PredicateFormula ListPredicateFormula _RPAREN  */
#line 759 "epddl.y"
                                                                  { std::reverse((yyvsp[-1].listpredicateformula_)->begin(),(yyvsp[-1].listpredicateformula_)->end()) ;(yyval.predicateformula_) = new AndPredFormula((yyvsp[-2].predicateformula_), (yyvsp[-1].listpredicateformula_)); }
#line 3099 "Parser.C"
    break;

  case 195: /* PredicateFormula: _LPAREN _KW_not PredicateFormula _RPAREN  */
#line 760 "epddl.y"
                                             { (yyval.predicateformula_) = new NotPredFormula((yyvsp[-1].predicateformula_)); }
#line 3105 "Parser.C"
    break;

  case 196: /* PredicateFormula: _LPAREN PredicateName ListGroundTerm _RPAREN  */
#line 761 "epddl.y"
                                                 { (yyval.predicateformula_) = new AtmPredFormula((yyvsp[-2].predicatename_), (yyvsp[-1].listgroundterm_)); }
#line 3111 "Parser.C"
    break;

  case 197: /* ListPredicateFormula: PredicateFormula  */
#line 763 "epddl.y"
                                        { (yyval.listpredicateformula_) = new ListPredicateFormula(); (yyval.listpredicateformula_)->push_back((yyvsp[0].predicateformula_)); }
#line 3117 "Parser.C"
    break;

  case 198: /* ListPredicateFormula: PredicateFormula ListPredicateFormula  */
#line 764 "epddl.y"
                                          { (yyvsp[0].listpredicateformula_)->push_back((yyvsp[-1].predicateformula_)); (yyval.listpredicateformula_) = (yyvsp[0].listpredicateformula_); }
#line 3123 "Parser.C"
    break;

  case 199: /* Entity: Name  */
#line 766 "epddl.y"
              { (yyval.entity_) = new EPDDLObjEntity((yyvsp[0]._name)); }
#line 3129 "Parser.C"
    break;

  case 200: /* Entity: AgentName  */
#line 767 "epddl.y"
              { (yyval.entity_) = new EPDDLAgEntity((yyvsp[0]._agentname)); }
#line 3135 "Parser.C"
    break;

  case 201: /* ListEntity: %empty  */
#line 769 "epddl.y"
                         { (yyval.listentity_) = new ListEntity(); }
#line 3141 "Parser.C"
    break;

  case 202: /* ListEntity: ListEntity Entity  */
#line 770 "epddl.y"
                      { (yyvsp[-1].listentity_)->push_back((yyvsp[0].entity_)); (yyval.listentity_) = (yyvsp[-1].listentity_); }
#line 3147 "Parser.C"
    break;

  case 203: /* TypedIdentList: ListName  */
#line 772 "epddl.y"
                          { std::reverse((yyvsp[0].listname_)->begin(),(yyvsp[0].listname_)->end()) ;(yyval.typedidentlist_) = new IdList((yyvsp[0].listname_)); }
#line 3153 "Parser.C"
    break;

  case 204: /* TypedIdentList: Name ListName _MINUS Type TypedIdentList  */
#line 773 "epddl.y"
                                             { std::reverse((yyvsp[-3].listname_)->begin(),(yyvsp[-3].listname_)->end()) ;(yyval.typedidentlist_) = new TypedIdList((yyvsp[-4]._name), (yyvsp[-3].listname_), (yyvsp[-1].type_), (yyvsp[0].typedidentlist_)); }
#line 3159 "Parser.C"
    break;

  case 205: /* TypedVariableList: ListVariable  */
#line 775 "epddl.y"
                                 { std::reverse((yyvsp[0].listvariable_)->begin(),(yyvsp[0].listvariable_)->end()) ;(yyval.typedvariablelist_) = new VarList((yyvsp[0].listvariable_)); }
#line 3165 "Parser.C"
    break;

  case 206: /* TypedVariableList: Variable ListVariable _MINUS Type TypedVariableList  */
#line 776 "epddl.y"
                                                        { std::reverse((yyvsp[-3].listvariable_)->begin(),(yyvsp[-3].listvariable_)->end()) ;(yyval.typedvariablelist_) = new TypedVarList((yyvsp[-4]._variable), (yyvsp[-3].listvariable_), (yyvsp[-1].type_), (yyvsp[0].typedvariablelist_)); }
#line 3171 "Parser.C"
    break;

  case 207: /* PredicateName: Name  */
#line 778 "epddl.y"
                     { (yyval.predicatename_) = new EPDDLPredicate((yyvsp[0]._name)); }
#line 3177 "Parser.C"
    break;

  case 208: /* ModalityAgent: AgentName  */
#line 780 "epddl.y"
                          { (yyval.modalityagent_) = new EPDDLModAgent((yyvsp[0]._agentname)); }
#line 3183 "Parser.C"
    break;

  case 209: /* ModalityAgent: Variable  */
#line 781 "epddl.y"
             { (yyval.modalityagent_) = new EPDDLModVarAgent((yyvsp[0]._variable)); }
#line 3189 "Parser.C"
    break;

  case 210: /* ModalityAgent: AnonVarAgent  */
#line 782 "epddl.y"
                 { (yyval.modalityagent_) = new EPDDLModAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 3195 "Parser.C"
    break;

  case 211: /* ModalityAgent: AllAgents  */
#line 783 "epddl.y"
              { (yyval.modalityagent_) = new EPDDLModAllAgents((yyvsp[0].allagents_)); }
#line 3201 "Parser.C"
    break;

  case 212: /* ListModalityAgent: ModalityAgent  */
#line 785 "epddl.y"
                                  { (yyval.listmodalityagent_) = new ListModalityAgent(); (yyval.listmodalityagent_)->push_back((yyvsp[0].modalityagent_)); }
#line 3207 "Parser.C"
    break;

  case 213: /* ListModalityAgent: ModalityAgent ListModalityAgent  */
#line 786 "epddl.y"
                                    { (yyvsp[0].listmodalityagent_)->push_back((yyvsp[-1].modalityagent_)); (yyval.listmodalityagent_) = (yyvsp[0].listmodalityagent_); }
#line 3213 "Parser.C"
    break;

  case 214: /* ModalityAgentGroup: ModalityAgent ListModalityAgent  */
#line 788 "epddl.y"
                                                     { std::reverse((yyvsp[0].listmodalityagent_)->begin(),(yyvsp[0].listmodalityagent_)->end()) ;(yyval.modalityagentgroup_) = new EPDDLModAgList((yyvsp[-1].modalityagent_), (yyvsp[0].listmodalityagent_)); }
#line 3219 "Parser.C"
    break;

  case 215: /* AgentGroupName: AgentName  */
#line 790 "epddl.y"
                           { (yyval.agentgroupname_) = new EPDDLSingleAgentGroup((yyvsp[0]._agentname)); }
#line 3225 "Parser.C"
    break;

  case 216: /* AgentGroupName: AllAgents  */
#line 791 "epddl.y"
              { (yyval.agentgroupname_) = new EPDDLAllAgentsGroup((yyvsp[0].allagents_)); }
#line 3231 "Parser.C"
    break;

  case 217: /* ObservingAgentGroup: AgentName  */
#line 793 "epddl.y"
                                { (yyval.observingagentgroup_) = new EPDDLObsAgentGroup((yyvsp[0]._agentname)); }
#line 3237 "Parser.C"
    break;

  case 218: /* ListObservingAgentGroup: ObservingAgentGroup  */
#line 795 "epddl.y"
                                              { (yyval.listobservingagentgroup_) = new ListObservingAgentGroup(); (yyval.listobservingagentgroup_)->push_back((yyvsp[0].observingagentgroup_)); }
#line 3243 "Parser.C"
    break;

  case 219: /* ListObservingAgentGroup: ObservingAgentGroup ListObservingAgentGroup  */
#line 796 "epddl.y"
                                                { (yyvsp[0].listobservingagentgroup_)->push_back((yyvsp[-1].observingagentgroup_)); (yyval.listobservingagentgroup_) = (yyvsp[0].listobservingagentgroup_); }
#line 3249 "Parser.C"
    break;

  case 220: /* ObservingAgent: AgentName  */
#line 798 "epddl.y"
                           { (yyval.observingagent_) = new EPDDLObsAgent((yyvsp[0]._agentname)); }
#line 3255 "Parser.C"
    break;

  case 221: /* ObservingAgent: AllAgents  */
#line 799 "epddl.y"
              { (yyval.observingagent_) = new EPDDLObsAllAgents((yyvsp[0].allagents_)); }
#line 3261 "Parser.C"
    break;

  case 222: /* ObservingAgent: Variable  */
#line 800 "epddl.y"
             { (yyval.observingagent_) = new EPDDLObsVarAgent((yyvsp[0]._variable)); }
#line 3267 "Parser.C"
    break;

  case 223: /* ObservingAgent: AnonVarAgent  */
#line 801 "epddl.y"
                 { (yyval.observingagent_) = new EPDDLObsAnonVarAgent((yyvsp[0].anonvaragent_)); }
#line 3273 "Parser.C"
    break;

  case 224: /* AgentGroup: AgentGroupName  */
#line 803 "epddl.y"
                            { (yyval.agentgroup_) = new EPDDLAgentGroup((yyvsp[0].agentgroupname_)); }
#line 3279 "Parser.C"
    break;

  case 225: /* AgentGroup: _LBRACE AgentName ListAgentName _RBRACE  */
#line 804 "epddl.y"
                                            { std::reverse((yyvsp[-1].listagentname_)->begin(),(yyvsp[-1].listagentname_)->end()) ;(yyval.agentgroup_) = new EPDDLAgentNameGroup((yyvsp[-2]._agentname), (yyvsp[-1].listagentname_)); }
#line 3285 "Parser.C"
    break;

  case 226: /* AllAgents: _KW_All  */
#line 806 "epddl.y"
                    { (yyval.allagents_) = new EPDDLAllAgents(); }
#line 3291 "Parser.C"
    break;

  case 227: /* AnonVarAgent: _SYMB_39  */
#line 808 "epddl.y"
                        { (yyval.anonvaragent_) = new EPDDLAnonVarAgent(); }
#line 3297 "Parser.C"
    break;

  case 228: /* Parameter: _LPAREN ParameterName ParameterValue _RPAREN  */
#line 810 "epddl.y"
                                                         { (yyval.parameter_) = new EPDDLParam((yyvsp[-2]._parametername), (yyvsp[-1].parametervalue_)); }
#line 3303 "Parser.C"
    break;

  case 229: /* ListParameter: %empty  */
#line 812 "epddl.y"
                            { (yyval.listparameter_) = new ListParameter(); }
#line 3309 "Parser.C"
    break;

  case 230: /* ListParameter: ListParameter Parameter  */
#line 813 "epddl.y"
                            { (yyvsp[-1].listparameter_)->push_back((yyvsp[0].parameter_)); (yyval.listparameter_) = (yyvsp[-1].listparameter_); }
#line 3315 "Parser.C"
    break;

  case 231: /* ParameterValue: Term  */
#line 815 "epddl.y"
                      { (yyval.parametervalue_) = new EPDDLTermParam((yyvsp[0].term_)); }
#line 3321 "Parser.C"
    break;

  case 232: /* ParameterValue: Formula  */
#line 816 "epddl.y"
            { (yyval.parametervalue_) = new EPDDLFormulaParam((yyvsp[0].formula_)); }
#line 3327 "Parser.C"
    break;

  case 233: /* ParameterValue: TrivialDef  */
#line 817 "epddl.y"
               { (yyval.parametervalue_) = new EPDDLTrivialParam((yyvsp[0].trivialdef_)); }
#line 3333 "Parser.C"
    break;

  case 234: /* ParameterValue: ListPostParameterValue  */
#line 818 "epddl.y"
                           { std::reverse((yyvsp[0].listpostparametervalue_)->begin(),(yyvsp[0].listpostparametervalue_)->end()) ;(yyval.parametervalue_) = new EPDDLPostParam((yyvsp[0].listpostparametervalue_)); }
#line 3339 "Parser.C"
    break;

  case 235: /* PostParameterValue: _LPAREN _KW_forall _LPAREN TypedVariableList _RPAREN ListLiteralPostcondition _RPAREN  */
#line 820 "epddl.y"
                                                                                                           { std::reverse((yyvsp[-1].listliteralpostcondition_)->begin(),(yyvsp[-1].listliteralpostcondition_)->end()) ;(yyval.postparametervalue_) = new PostParamForall((yyvsp[-3].typedvariablelist_), (yyvsp[-1].listliteralpostcondition_)); }
#line 3345 "Parser.C"
    break;

  case 236: /* PostParameterValue: LiteralPostcondition  */
#line 821 "epddl.y"
                         { (yyval.postparametervalue_) = new PostParamLiteral((yyvsp[0].literalpostcondition_)); }
#line 3351 "Parser.C"
    break;

  case 237: /* ListPostParameterValue: PostParameterValue  */
#line 823 "epddl.y"
                                            { (yyval.listpostparametervalue_) = new ListPostParameterValue(); (yyval.listpostparametervalue_)->push_back((yyvsp[0].postparametervalue_)); }
#line 3357 "Parser.C"
    break;

  case 238: /* ListPostParameterValue: PostParameterValue ListPostParameterValue  */
#line 824 "epddl.y"
                                              { (yyvsp[0].listpostparametervalue_)->push_back((yyvsp[-1].postparametervalue_)); (yyval.listpostparametervalue_) = (yyvsp[0].listpostparametervalue_); }
#line 3363 "Parser.C"
    break;

  case 239: /* Type: Name  */
#line 826 "epddl.y"
            { (yyval.type_) = new EPDDLTypeName((yyvsp[0]._name)); }
#line 3369 "Parser.C"
    break;

  case 240: /* Type: ReservedType  */
#line 827 "epddl.y"
                 { (yyval.type_) = new EPDDLResType((yyvsp[0].reservedtype_)); }
#line 3375 "Parser.C"
    break;

  case 241: /* ReservedType: _KW_agent  */
#line 829 "epddl.y"
                         { (yyval.reservedtype_) = new ResAgentType(); }
#line 3381 "Parser.C"
    break;

  case 242: /* ReservedType: _KW_predicate  */
#line 830 "epddl.y"
                  { (yyval.reservedtype_) = new PredicateType(); }
#line 3387 "Parser.C"
    break;

  case 243: /* ReservedType: _KW_literal  */
#line 831 "epddl.y"
                { (yyval.reservedtype_) = new LiteralType(); }
#line 3393 "Parser.C"
    break;

  case 244: /* ReservedType: _SYMB_40  */
#line 832 "epddl.y"
             { (yyval.reservedtype_) = new PredFormulaType(); }
#line 3399 "Parser.C"
    break;

  case 245: /* ReservedType: _KW_formula  */
#line 833 "epddl.y"
                { (yyval.reservedtype_) = new FormulaType(); }
#line 3405 "Parser.C"
    break;

  case 246: /* ReservedType: _KW_postcondition  */
#line 834 "epddl.y"
                      { (yyval.reservedtype_) = new PostconditionType(); }
#line 3411 "Parser.C"
    break;

  case 247: /* LibraryName: Name  */
#line 836 "epddl.y"
                   { (yyval.libraryname_) = new EPDDLLibraryName((yyvsp[0]._name)); }
#line 3417 "Parser.C"
    break;

  case 248: /* ListLibraryName: LibraryName  */
#line 838 "epddl.y"
                              { (yyval.listlibraryname_) = new ListLibraryName(); (yyval.listlibraryname_)->push_back((yyvsp[0].libraryname_)); }
#line 3423 "Parser.C"
    break;

  case 249: /* ListLibraryName: LibraryName ListLibraryName  */
#line 839 "epddl.y"
                                { (yyvsp[0].listlibraryname_)->push_back((yyvsp[-1].libraryname_)); (yyval.listlibraryname_) = (yyvsp[0].listlibraryname_); }
#line 3429 "Parser.C"
    break;

  case 250: /* ActionTypeName: ReservedActionTypeName  */
#line 841 "epddl.y"
                                        { (yyval.actiontypename_) = new EPDDLResActTypeName((yyvsp[0].reservedactiontypename_)); }
#line 3435 "Parser.C"
    break;

  case 251: /* ActionTypeName: Name  */
#line 842 "epddl.y"
         { (yyval.actiontypename_) = new EPDDLActTypeName((yyvsp[0]._name)); }
#line 3441 "Parser.C"
    break;

  case 252: /* ReservedActionTypeName: _KW_ontic  */
#line 844 "epddl.y"
                                   { (yyval.reservedactiontypename_) = new OntActTypeName(); }
#line 3447 "Parser.C"
    break;

  case 253: /* ReservedActionTypeName: _KW_sensing  */
#line 845 "epddl.y"
                { (yyval.reservedactiontypename_) = new SenActTypeName(); }
#line 3453 "Parser.C"
    break;

  case 254: /* ReservedActionTypeName: _KW_announcement  */
#line 846 "epddl.y"
                     { (yyval.reservedactiontypename_) = new AnnActTypeName(); }
#line 3459 "Parser.C"
    break;

  case 255: /* EventName: ReservedEventName  */
#line 848 "epddl.y"
                              { (yyval.eventname_) = new EPDDLResEventName((yyvsp[0].reservedeventname_)); }
#line 3465 "Parser.C"
    break;

  case 256: /* EventName: Name  */
#line 849 "epddl.y"
         { (yyval.eventname_) = new EPDDLEventName((yyvsp[0]._name)); }
#line 3471 "Parser.C"
    break;

  case 257: /* ListEventName: EventName  */
#line 851 "epddl.y"
                          { (yyval.listeventname_) = new ListEventName(); (yyval.listeventname_)->push_back((yyvsp[0].eventname_)); }
#line 3477 "Parser.C"
    break;

  case 258: /* ListEventName: EventName ListEventName  */
#line 852 "epddl.y"
                            { (yyvsp[0].listeventname_)->push_back((yyvsp[-1].eventname_)); (yyval.listeventname_) = (yyvsp[0].listeventname_); }
#line 3483 "Parser.C"
    break;

  case 259: /* ReservedEventName: _SYMB_41  */
#line 854 "epddl.y"
                             { (yyval.reservedeventname_) = new IdleEvent(); }
#line 3489 "Parser.C"
    break;

  case 260: /* ActionName: Name  */
#line 856 "epddl.y"
                  { (yyval.actionname_) = new EPDDLActionName((yyvsp[0]._name)); }
#line 3495 "Parser.C"
    break;

  case 261: /* ModelName: Name  */
#line 858 "epddl.y"
                 { (yyval.modelname_) = new EPDDLModelName((yyvsp[0]._name)); }
#line 3501 "Parser.C"
    break;

  case 262: /* WorldName: Name  */
#line 860 "epddl.y"
                 { (yyval.worldname_) = new EPDDLWorldName((yyvsp[0]._name)); }
#line 3507 "Parser.C"
    break;

  case 263: /* ListWorldName: WorldName  */
#line 862 "epddl.y"
                          { (yyval.listworldname_) = new ListWorldName(); (yyval.listworldname_)->push_back((yyvsp[0].worldname_)); }
#line 3513 "Parser.C"
    break;

  case 264: /* ListWorldName: WorldName ListWorldName  */
#line 863 "epddl.y"
                            { (yyvsp[0].listworldname_)->push_back((yyvsp[-1].worldname_)); (yyval.listworldname_) = (yyvsp[0].listworldname_); }
#line 3519 "Parser.C"
    break;

  case 265: /* RequireKey: _SYMB_42  */
#line 865 "epddl.y"
                      { (yyval.requirekey_) = new EPDDLReqDel(); }
#line 3525 "Parser.C"
    break;

  case 266: /* RequireKey: _SYMB_43  */
#line 866 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqTyping(); }
#line 3531 "Parser.C"
    break;

  case 267: /* RequireKey: _SYMB_44  */
#line 867 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqEquality(); }
#line 3537 "Parser.C"
    break;

  case 268: /* RequireKey: _SYMB_45  */
#line 868 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqParamList(); }
#line 3543 "Parser.C"
    break;

  case 269: /* RequireKey: _SYMB_46  */
#line 869 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqNegPre(); }
#line 3549 "Parser.C"
    break;

  case 270: /* RequireKey: _SYMB_47  */
#line 870 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqDisPre(); }
#line 3555 "Parser.C"
    break;

  case 271: /* RequireKey: _SYMB_48  */
#line 871 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqExiPre(); }
#line 3561 "Parser.C"
    break;

  case 272: /* RequireKey: _SYMB_49  */
#line 872 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqUniPre(); }
#line 3567 "Parser.C"
    break;

  case 273: /* RequireKey: _SYMB_50  */
#line 873 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPre(); }
#line 3573 "Parser.C"
    break;

  case 274: /* RequireKey: _SYMB_51  */
#line 874 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqModPost(); }
#line 3579 "Parser.C"
    break;

  case 275: /* RequireKey: _SYMB_6  */
#line 875 "epddl.y"
            { (yyval.requirekey_) = new EPDDLReqModalities(); }
#line 3585 "Parser.C"
    break;

  case 276: /* RequireKey: _SYMB_52  */
#line 876 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOnticChange(); }
#line 3591 "Parser.C"
    break;

  case 277: /* RequireKey: _SYMB_53  */
#line 877 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqCK(); }
#line 3597 "Parser.C"
    break;

  case 278: /* RequireKey: _SYMB_54  */
#line 878 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqDynCK(); }
#line 3603 "Parser.C"
    break;

  case 279: /* RequireKey: _SYMB_55  */
#line 879 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqMAStar(); }
#line 3609 "Parser.C"
    break;

  case 280: /* RequireKey: _SYMB_56  */
#line 880 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqOntic(); }
#line 3615 "Parser.C"
    break;

  case 281: /* RequireKey: _SYMB_57  */
#line 881 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqSensing(); }
#line 3621 "Parser.C"
    break;

  case 282: /* RequireKey: _SYMB_58  */
#line 882 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqAnnouncement(); }
#line 3627 "Parser.C"
    break;

  case 283: /* RequireKey: _SYMB_59  */
#line 883 "epddl.y"
             { (yyval.requirekey_) = new EPDDLReqFTheory(); }
#line 3633 "Parser.C"
    break;

  case 284: /* RequireKey: _LPAREN _SYMB_60 _INTEGER_ _RPAREN  */
#line 884 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPreDepth((yyvsp[-1]._int)); }
#line 3639 "Parser.C"
    break;

  case 285: /* RequireKey: _LPAREN _SYMB_61 _INTEGER_ _RPAREN  */
#line 885 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxPostDepth((yyvsp[-1]._int)); }
#line 3645 "Parser.C"
    break;

  case 286: /* RequireKey: _LPAREN _SYMB_62 _INTEGER_ _RPAREN  */
#line 886 "epddl.y"
                                       { (yyval.requirekey_) = new EPDDLReqMaxDepth((yyvsp[-1]._int)); }
#line 3651 "Parser.C"
    break;

  case 287: /* ListRequireKey: RequireKey  */
#line 888 "epddl.y"
                            { (yyval.listrequirekey_) = new ListRequireKey(); (yyval.listrequirekey_)->push_back((yyvsp[0].requirekey_)); }
#line 3657 "Parser.C"
    break;

  case 288: /* ListRequireKey: RequireKey ListRequireKey  */
#line 889 "epddl.y"
                              { (yyvsp[0].listrequirekey_)->push_back((yyvsp[-1].requirekey_)); (yyval.listrequirekey_) = (yyvsp[0].listrequirekey_); }
#line 3663 "Parser.C"
    break;

  case 289: /* TrivialDef: _LPAREN _RPAREN  */
#line 891 "epddl.y"
                             { (yyval.trivialdef_) = new EPDDLTrivialDef(); }
#line 3669 "Parser.C"
    break;

  case 290: /* ListName: %empty  */
#line 893 "epddl.y"
                       { (yyval.listname_) = new ListName(); }
#line 3675 "Parser.C"
    break;

  case 291: /* ListName: Name ListName  */
#line 894 "epddl.y"
                  { (yyvsp[0].listname_)->push_back((yyvsp[-1]._name)); (yyval.listname_) = (yyvsp[0].listname_); }
#line 3681 "Parser.C"
    break;

  case 292: /* ListAgentName: AgentName  */
#line 896 "epddl.y"
                          { (yyval.listagentname_) = new ListAgentName(); (yyval.listagentname_)->push_back((yyvsp[0]._agentname)); }
#line 3687 "Parser.C"
    break;

  case 293: /* ListAgentName: AgentName ListAgentName  */
#line 897 "epddl.y"
                            { (yyvsp[0].listagentname_)->push_back((yyvsp[-1]._agentname)); (yyval.listagentname_) = (yyvsp[0].listagentname_); }
#line 3693 "Parser.C"
    break;

  case 294: /* ListModalityName: %empty  */
#line 899 "epddl.y"
                               { (yyval.listmodalityname_) = new ListModalityName(); }
#line 3699 "Parser.C"
    break;

  case 295: /* ListModalityName: ModalityName ListModalityName  */
#line 900 "epddl.y"
                                  { (yyvsp[0].listmodalityname_)->push_back((yyvsp[-1]._modalityname)); (yyval.listmodalityname_) = (yyvsp[0].listmodalityname_); }
#line 3705 "Parser.C"
    break;

  case 296: /* ListVariable: %empty  */
#line 902 "epddl.y"
                           { (yyval.listvariable_) = new ListVariable(); }
#line 3711 "Parser.C"
    break;

  case 297: /* ListVariable: Variable ListVariable  */
#line 903 "epddl.y"
                          { (yyvsp[0].listvariable_)->push_back((yyvsp[-1]._variable)); (yyval.listvariable_) = (yyvsp[0].listvariable_); }
#line 3717 "Parser.C"
    break;

  case 298: /* Name: T_Name  */
#line 905 "epddl.y"
              { (yyval._name) = new Name((yyvsp[0]._string), (yyloc).first_line); }
#line 3723 "Parser.C"
    break;

  case 299: /* AgentName: T_AgentName  */
#line 907 "epddl.y"
                        { (yyval._agentname) = new AgentName((yyvsp[0]._string), (yyloc).first_line); }
#line 3729 "Parser.C"
    break;

  case 300: /* ModalityName: T_ModalityName  */
#line 909 "epddl.y"
                              { (yyval._modalityname) = new ModalityName((yyvsp[0]._string), (yyloc).first_line); }
#line 3735 "Parser.C"
    break;

  case 301: /* Variable: T_Variable  */
#line 911 "epddl.y"
                      { (yyval._variable) = new Variable((yyvsp[0]._string), (yyloc).first_line); }
#line 3741 "Parser.C"
    break;

  case 302: /* ParameterName: T_ParameterName  */
#line 913 "epddl.y"
                                { (yyval._parametername) = new ParameterName((yyvsp[0]._string), (yyloc).first_line); }
#line 3747 "Parser.C"
    break;


#line 3751 "Parser.C"

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

#line 916 "epddl.y"



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



