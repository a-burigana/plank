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

#ifndef YY_PLANK_BISON_H_INCLUDED
# define YY_PLANK_BISON_H_INCLUDED
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
    _COLON = 262,                  /* _COLON  */
    _SYMB_7 = 263,                 /* _SYMB_7  */
    _SYMB_10 = 264,                /* _SYMB_10  */
    _SYMB_2 = 265,                 /* _SYMB_2  */
    _SYMB_23 = 266,                /* _SYMB_23  */
    _SYMB_22 = 267,                /* _SYMB_22  */
    _SYMB_50 = 268,                /* _SYMB_50  */
    _SYMB_41 = 269,                /* _SYMB_41  */
    _SYMB_17 = 270,                /* _SYMB_17  */
    _SYMB_21 = 271,                /* _SYMB_21  */
    _SYMB_51 = 272,                /* _SYMB_51  */
    _SYMB_43 = 273,                /* _SYMB_43  */
    _SYMB_18 = 274,                /* _SYMB_18  */
    _SYMB_15 = 275,                /* _SYMB_15  */
    _SYMB_44 = 276,                /* _SYMB_44  */
    _SYMB_52 = 277,                /* _SYMB_52  */
    _SYMB_35 = 278,                /* _SYMB_35  */
    _SYMB_28 = 279,                /* _SYMB_28  */
    _SYMB_55 = 280,                /* _SYMB_55  */
    _SYMB_54 = 281,                /* _SYMB_54  */
    _SYMB_53 = 282,                /* _SYMB_53  */
    _SYMB_48 = 283,                /* _SYMB_48  */
    _SYMB_47 = 284,                /* _SYMB_47  */
    _SYMB_6 = 285,                 /* _SYMB_6  */
    _SYMB_26 = 286,                /* _SYMB_26  */
    _SYMB_12 = 287,                /* _SYMB_12  */
    _SYMB_14 = 288,                /* _SYMB_14  */
    _SYMB_49 = 289,                /* _SYMB_49  */
    _SYMB_8 = 290,                 /* _SYMB_8  */
    _SYMB_19 = 291,                /* _SYMB_19  */
    _SYMB_11 = 292,                /* _SYMB_11  */
    _SYMB_5 = 293,                 /* _SYMB_5  */
    _SYMB_16 = 294,                /* _SYMB_16  */
    _SYMB_3 = 295,                 /* _SYMB_3  */
    _SYMB_32 = 296,                /* _SYMB_32  */
    _SYMB_29 = 297,                /* _SYMB_29  */
    _SYMB_27 = 298,                /* _SYMB_27  */
    _SYMB_4 = 299,                 /* _SYMB_4  */
    _SYMB_42 = 300,                /* _SYMB_42  */
    _SYMB_45 = 301,                /* _SYMB_45  */
    _SYMB_46 = 302,                /* _SYMB_46  */
    _SYMB_34 = 303,                /* _SYMB_34  */
    _SYMB_9 = 304,                 /* _SYMB_9  */
    _SYMB_33 = 305,                /* _SYMB_33  */
    _LT = 306,                     /* _LT  */
    _LARROW = 307,                 /* _LARROW  */
    _EQ = 308,                     /* _EQ  */
    _GT = 309,                     /* _GT  */
    _KW_All = 310,                 /* _KW_All  */
    _LBRACK = 311,                 /* _LBRACK  */
    _RBRACK = 312,                 /* _RBRACK  */
    _KW_agent = 313,               /* _KW_agent  */
    _KW_and = 314,                 /* _KW_and  */
    _KW_as = 315,                  /* _KW_as  */
    _KW_define = 316,              /* _KW_define  */
    _KW_domain = 317,              /* _KW_domain  */
    _KW_exists = 318,              /* _KW_exists  */
    _KW_false = 319,               /* _KW_false  */
    _KW_forall = 320,              /* _KW_forall  */
    _KW_formula = 321,             /* _KW_formula  */
    _KW_if = 322,                  /* _KW_if  */
    _KW_iff = 323,                 /* _KW_iff  */
    _KW_imply = 324,               /* _KW_imply  */
    _KW_library = 325,             /* _KW_library  */
    _KW_literal = 326,             /* _KW_literal  */
    _KW_not = 327,                 /* _KW_not  */
    _KW_or = 328,                  /* _KW_or  */
    _KW_otherwise = 329,           /* _KW_otherwise  */
    _KW_postcondition = 330,       /* _KW_postcondition  */
    _KW_predicate = 331,           /* _KW_predicate  */
    _SYMB_40 = 332,                /* _SYMB_40  */
    _KW_problem = 333,             /* _KW_problem  */
    _KW_true = 334,                /* _KW_true  */
    _KW_when = 335,                /* _KW_when  */
    _LBRACE = 336,                 /* _LBRACE  */
    _RBRACE = 337,                 /* _RBRACE  */
    T_AgentName = 338,             /* T_AgentName  */
    T_ModalityName = 339,          /* T_ModalityName  */
    T_Name = 340,                  /* T_Name  */
    T_Variable = 341,              /* T_Variable  */
    _INTEGER_ = 342                /* _INTEGER_  */
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
  ModalitiesDef* modalitiesdef_;
  ActionDef* actiondef_;
  ParametersDef* parametersdef_;
  ActionConditionDef* actionconditiondef_;
  ActionTypeSignatureDef* actiontypesignaturedef_;
  ActionPreDef* actionpredef_;
  ActionObsDef* actionobsdef_;
  ObsConditionDef* obsconditiondef_;
  ListObsConditionDef* listobsconditiondef_;
  ObsCondition* obscondition_;
  ListObsCondition* listobscondition_;
  LibraryDef* librarydef_;
  LibraryItemDef* libraryitemdef_;
  ListLibraryItemDef* listlibraryitemdef_;
  ObservabilityGroupsDef* observabilitygroupsdef_;
  ActionTypeDef* actiontypedef_;
  ActionTypeGroupsDef* actiontypegroupsdef_;
  ActionTypeEventsDef* actiontypeeventsdef_;
  EventSignature* eventsignature_;
  ListEventSignature* listeventsignature_;
  ActionTypeRelDef* actiontypereldef_;
  ActionRelations* actionrelations_;
  EventRelation* eventrelation_;
  ListEventRelation* listeventrelation_;
  EventNamePair* eventnamepair_;
  ListEventNamePair* listeventnamepair_;
  ActionTypeDesignDef* actiontypedesigndef_;
  EventDef* eventdef_;
  EventPreDef* eventpredef_;
  EventPostDef* eventpostdef_;
  PostconditionBlock* postconditionblock_;
  Postcondition* postcondition_;
  ListPostcondition* listpostcondition_;
  SimplePostcondition* simplepostcondition_;
  ListSimplePostcondition* listsimplepostcondition_;
  ProblemDef* problemdef_;
  ProblemItemDef* problemitemdef_;
  ListProblemItemDef* listproblemitemdef_;
  ProblemDomainNameDef* problemdomainnamedef_;
  AgentNamesDef* agentnamesdef_;
  AgentGroupsListDef* agentgroupslistdef_;
  AgentGroupDef* agentgroupdef_;
  ListAgentGroupDef* listagentgroupdef_;
  ObjectNamesDef* objectnamesdef_;
  StaticPredListDef* staticpredlistdef_;
  StaticPredDef* staticpreddef_;
  ListStaticPredDef* liststaticpreddef_;
  InitDef* initdef_;
  InitialStateDescr* initialstatedescr_;
  FTheoryFormula* ftheoryformula_;
  ListFTheoryFormula* listftheoryformula_;
  SimpleFTheoryFormula* simpleftheoryformula_;
  StateDef* statedef_;
  StateWorldsDef* stateworldsdef_;
  StateRelDef* statereldef_;
  StateRelations* staterelations_;
  WorldRelation* worldrelation_;
  ListWorldRelation* listworldrelation_;
  WorldNamePair* worldnamepair_;
  ListWorldNamePair* listworldnamepair_;
  StateValDef* statevaldef_;
  StateValuation* statevaluation_;
  WorldValuation* worldvaluation_;
  ListWorldValuation* listworldvaluation_;
  StateDesignDef* statedesigndef_;
  GoalDef* goaldef_;
  Formula* formula_;
  ListFormula* listformula_;
  AtomicFormula* atomicformula_;
  Predicate* predicate_;
  AtomicEqFormula* atomiceqformula_;
  FormulaOrEmpty* formulaorempty_;
  Term* term_;
  ListTerm* listterm_;
  GroundTerm* groundterm_;
  ListGroundTerm* listgroundterm_;
  Modality* modality_;
  SingleModality* singlemodality_;
  GroupModality* groupmodality_;
  ModalityLabel* modalitylabel_;
  KnowsWhether* knowswhether_;
  Literal* literal_;
  ListLiteral* listliteral_;
  ConditionFormula* conditionformula_;
  Condition* condition_;
  ListCondition* listcondition_;
  AtomicCondition* atomiccondition_;
  PredicateFormula* predicateformula_;
  ListPredicateFormula* listpredicateformula_;
  GenericName* genericname_;
  ListGenericName* listgenericname_;
  TypedIdentList* typedidentlist_;
  TypedAgentList* typedagentlist_;
  TypedVariableList* typedvariablelist_;
  PredicateName* predicatename_;
  ModalityAgent* modalityagent_;
  ListModalityAgent* listmodalityagent_;
  ModalityAgentGroup* modalityagentgroup_;
  AgentGroupName* agentgroupname_;
  ObservingAgentGroup* observingagentgroup_;
  ListObservingAgentGroup* listobservingagentgroup_;
  ObservingAgent* observingagent_;
  AgentGroup* agentgroup_;
  AllAgents* allagents_;
  Parameter* parameter_;
  ListParameter* listparameter_;
  Expression* expression_;
  Type* type_;
  ReservedType* reservedtype_;
  DomainName* domainname_;
  LibraryName* libraryname_;
  ListLibraryName* listlibraryname_;
  ProblemName* problemname_;
  ActionName* actionname_;
  ActionTypeName* actiontypename_;
  EventName* eventname_;
  ListEventName* listeventname_;
  StateName* statename_;
  WorldName* worldname_;
  ListWorldName* listworldname_;
  RequirementKey* requirementkey_;
  ListRequirementKey* listrequirementkey_;
  TrivialDef* trivialdef_;
  ListName* listname_;
  ListAgentName* listagentname_;
  ListModalityName* listmodalityname_;
  ListVariable* listvariable_;

#line 299 "Bison.H"

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


#endif /* !YY_PLANK_BISON_H_INCLUDED  */
