/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_EPDDL_BISON_H_INCLUDED
# define YY_EPDDL_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int epddl_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    _ERROR_ = 258,                 /* _ERROR_  */
    _LPAREN = 259,                 /* _LPAREN  */
    _RPAREN = 260,                 /* _RPAREN  */
    _MINUS = 261,                  /* _MINUS  */
    _SYMB_7 = 262,                 /* _SYMB_7  */
    _SYMB_9 = 263,                 /* _SYMB_9  */
    _SYMB_2 = 264,                 /* _SYMB_2  */
    _SYMB_20 = 265,                /* _SYMB_20  */
    _SYMB_19 = 266,                /* _SYMB_19  */
    _SYMB_51 = 267,                /* _SYMB_51  */
    _SYMB_40 = 268,                /* _SYMB_40  */
    _SYMB_15 = 269,                /* _SYMB_15  */
    _SYMB_45 = 270,                /* _SYMB_45  */
    _SYMB_18 = 271,                /* _SYMB_18  */
    _SYMB_52 = 272,                /* _SYMB_52  */
    _SYMB_42 = 273,                /* _SYMB_42  */
    _SYMB_16 = 274,                /* _SYMB_16  */
    _SYMB_13 = 275,                /* _SYMB_13  */
    _SYMB_46 = 276,                /* _SYMB_46  */
    _SYMB_12 = 277,                /* _SYMB_12  */
    _SYMB_29 = 278,                /* _SYMB_29  */
    _SYMB_24 = 279,                /* _SYMB_24  */
    _SYMB_53 = 280,                /* _SYMB_53  */
    _SYMB_56 = 281,                /* _SYMB_56  */
    _SYMB_57 = 282,                /* _SYMB_57  */
    _SYMB_54 = 283,                /* _SYMB_54  */
    _SYMB_55 = 284,                /* _SYMB_55  */
    _SYMB_60 = 285,                /* _SYMB_60  */
    _SYMB_59 = 286,                /* _SYMB_59  */
    _SYMB_58 = 287,                /* _SYMB_58  */
    _SYMB_49 = 288,                /* _SYMB_49  */
    _SYMB_48 = 289,                /* _SYMB_48  */
    _SYMB_26 = 290,                /* _SYMB_26  */
    _SYMB_25 = 291,                /* _SYMB_25  */
    _SYMB_44 = 292,                /* _SYMB_44  */
    _SYMB_23 = 293,                /* _SYMB_23  */
    _SYMB_11 = 294,                /* _SYMB_11  */
    _SYMB_6 = 295,                 /* _SYMB_6  */
    _SYMB_50 = 296,                /* _SYMB_50  */
    _SYMB_43 = 297,                /* _SYMB_43  */
    _SYMB_8 = 298,                 /* _SYMB_8  */
    _SYMB_17 = 299,                /* _SYMB_17  */
    _SYMB_10 = 300,                /* _SYMB_10  */
    _SYMB_5 = 301,                 /* _SYMB_5  */
    _SYMB_14 = 302,                /* _SYMB_14  */
    _SYMB_3 = 303,                 /* _SYMB_3  */
    _SYMB_4 = 304,                 /* _SYMB_4  */
    _SYMB_41 = 305,                /* _SYMB_41  */
    _SYMB_47 = 306,                /* _SYMB_47  */
    _SYMB_28 = 307,                /* _SYMB_28  */
    _SYMB_27 = 308,                /* _SYMB_27  */
    _LT = 309,                     /* _LT  */
    _EQ = 310,                     /* _EQ  */
    _GT = 311,                     /* _GT  */
    _SYMB_37 = 312,                /* _SYMB_37  */
    _KW_All = 313,                 /* _KW_All  */
    _LBRACK = 314,                 /* _LBRACK  */
    _RBRACK = 315,                 /* _RBRACK  */
    _KW_agent = 316,               /* _KW_agent  */
    _KW_and = 317,                 /* _KW_and  */
    _KW_announcement = 318,        /* _KW_announcement  */
    _KW_as = 319,                  /* _KW_as  */
    _KW_define = 320,              /* _KW_define  */
    _KW_domain = 321,              /* _KW_domain  */
    _SYMB_34 = 322,                /* _SYMB_34  */
    _KW_false = 323,               /* _KW_false  */
    _KW_formula = 324,             /* _KW_formula  */
    _SYMB_39 = 325,                /* _SYMB_39  */
    _KW_imply = 326,               /* _KW_imply  */
    _SYMB_33 = 327,                /* _SYMB_33  */
    _KW_library = 328,             /* _KW_library  */
    _KW_literal = 329,             /* _KW_literal  */
    _KW_not = 330,                 /* _KW_not  */
    _KW_ontic = 331,               /* _KW_ontic  */
    _KW_or = 332,                  /* _KW_or  */
    _KW_otherwise = 333,           /* _KW_otherwise  */
    _KW_predicate = 334,           /* _KW_predicate  */
    _SYMB_38 = 335,                /* _SYMB_38  */
    _KW_problem = 336,             /* _KW_problem  */
    _SYMB_35 = 337,                /* _SYMB_35  */
    _KW_sensing = 338,             /* _KW_sensing  */
    _KW_true = 339,                /* _KW_true  */
    _KW_when = 340,                /* _KW_when  */
    T_AgentName = 341,             /* T_AgentName  */
    T_ModalityName = 342,          /* T_ModalityName  */
    T_Name = 343,                  /* T_Name  */
    T_Variable = 344,              /* T_Variable  */
    _INTEGER_ = 345                /* _INTEGER_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "epddl.y"

  int    _int;
  char   _char;
  double _double;
  char*  _string;
  Name* _name;
  AgentName* _agentname;
  ModalityName* _modalityname;
  Variable* _variable;
  MainDef* maindef_;
  DomainDef* domaindef_;
  DomainItemDef* domainitemdef_;
  ListDomainItemDef* listdomainitemdef_;
  DomainLibrariesNameDef* domainlibrariesnamedef_;
  RequireDef* requiredef_;
  TypesDef* typesdef_;
  PredicateListDef* predicatelistdef_;
  PredicateDef* predicatedef_;
  ListPredicateDef* listpredicatedef_;
  ObservabilityGroupsDef* observabilitygroupsdef_;
  ActionDef* actiondef_;
  ActionParameterDef* actionparameterdef_;
  ActionTypeSignatureDef* actiontypesignaturedef_;
  ActionPreDef* actionpredef_;
  Precondition* precondition_;
  ActionObsDef* actionobsdef_;
  ObsConditionDef* obsconditiondef_;
  ListObsConditionDef* listobsconditiondef_;
  LibraryDef* librarydef_;
  LibraryItemDef* libraryitemdef_;
  ListLibraryItemDef* listlibraryitemdef_;
  ActionTypeDef* actiontypedef_;
  ActionTypeParameterDef* actiontypeparameterdef_;
  ActionTypeFrameDef* actiontypeframedef_;
  ActionTypeEventsDef* actiontypeeventsdef_;
  ActionTypeRelDef* actiontypereldef_;
  ActionTypeDesDef* actiontypedesdef_;
  EventSignature* eventsignature_;
  ListEventSignature* listeventsignature_;
  ActionRelations* actionrelations_;
  EventRelation* eventrelation_;
  ListEventRelation* listeventrelation_;
  EventNamePair* eventnamepair_;
  ListEventNamePair* listeventnamepair_;
  EventDef* eventdef_;
  EventParameterDef* eventparameterdef_;
  EventPreDef* eventpredef_;
  EventPostDef* eventpostdef_;
  EventPostconditions* eventpostconditions_;
  LiteralPostcondition* literalpostcondition_;
  ListLiteralPostcondition* listliteralpostcondition_;
  Postcondition* postcondition_;
  ProblemDef* problemdef_;
  ProblemItemDef* problemitemdef_;
  ListProblemItemDef* listproblemitemdef_;
  ProblemDomainNameDef* problemdomainnamedef_;
  AgentNamesDef* agentnamesdef_;
  AgentGroupsListDef* agentgroupslistdef_;
  AgentGroupDef* agentgroupdef_;
  ListAgentGroupDef* listagentgroupdef_;
  ObjectNamesDef* objectnamesdef_;
  InitDef* initdef_;
  InitialStateDescr* initialstatedescr_;
  FTheoryFormula* ftheoryformula_;
  ListFTheoryFormula* listftheoryformula_;
  KPredicateFormula* kpredicateformula_;
  KWPredicateFormula* kwpredicateformula_;
  NotKWPredicateFormula* notkwpredicateformula_;
  InitialModelDef* initialmodeldef_;
  ModelWorldsDef* modelworldsdef_;
  ModelRelDef* modelreldef_;
  ModelValDef* modelvaldef_;
  ModelDesDef* modeldesdef_;
  ModelRelations* modelrelations_;
  ModelValuation* modelvaluation_;
  WorldRelation* worldrelation_;
  ListWorldRelation* listworldrelation_;
  WorldNamePair* worldnamepair_;
  ListWorldNamePair* listworldnamepair_;
  WorldValuation* worldvaluation_;
  ListWorldValuation* listworldvaluation_;
  GoalDef* goaldef_;
  Formula* formula_;
  ListFormula* listformula_;
  AtomicFormula* atomicformula_;
  AtomicEqFormula* atomiceqformula_;
  MetaTerm* metaterm_;
  ListMetaTerm* listmetaterm_;
  Term* term_;
  Modality* modality_;
  SingleModality* singlemodality_;
  GroupModality* groupmodality_;
  ModalityLabel* modalitylabel_;
  KnowsWhether* knowswhether_;
  Literal* literal_;
  ListLiteral* listliteral_;
  PredicateFormula* predicateformula_;
  ListPredicateFormula* listpredicateformula_;
  BasicTypedIdentList* basictypedidentlist_;
  BasicTypedVariableList* basictypedvariablelist_;
  TypedVariableList* typedvariablelist_;
  PredicateName* predicatename_;
  ModalityAgent* modalityagent_;
  ListModalityAgent* listmodalityagent_;
  ModalityAgentGroup* modalityagentgroup_;
  AgentGroupName* agentgroupname_;
  ObservingAgentGroup* observingagentgroup_;
  ListObservingAgentGroup* listobservingagentgroup_;
  ObservingAgent* observingagent_;
  AgentList* agentlist_;
  AllAgents* allagents_;
  AnonVarAgent* anonvaragent_;
  Parameter* parameter_;
  ListParameter* listparameter_;
  BasicParameter* basicparameter_;
  Type* type_;
  BasicType* basictype_;
  CompoundType* compoundtype_;
  ReservedBasicType* reservedbasictype_;
  ReservedFormulaType* reservedformulatype_;
  LibraryName* libraryname_;
  ListLibraryName* listlibraryname_;
  ActionTypeName* actiontypename_;
  ReservedActionTypeName* reservedactiontypename_;
  EventName* eventname_;
  ListEventName* listeventname_;
  ReservedEventName* reservedeventname_;
  ActionName* actionname_;
  ModelName* modelname_;
  WorldName* worldname_;
  ListWorldName* listworldname_;
  RequireKey* requirekey_;
  ListRequireKey* listrequirekey_;
  TrivialDef* trivialdef_;
  ListName* listname_;
  ListAgentName* listagentname_;
  ListVariable* listvariable_;

#line 293 "Bison.H"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int epddl_parse (yyscan_t scanner, YYSTYPE *result);


#endif /* !YY_EPDDL_BISON_H_INCLUDED  */
