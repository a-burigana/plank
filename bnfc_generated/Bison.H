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
    _DCOLON = 262,                 /* _DCOLON  */
    _SYMB_8 = 263,                 /* _SYMB_8  */
    _SYMB_11 = 264,                /* _SYMB_11  */
    _SYMB_2 = 265,                 /* _SYMB_2  */
    _SYMB_22 = 266,                /* _SYMB_22  */
    _SYMB_21 = 267,                /* _SYMB_21  */
    _SYMB_52 = 268,                /* _SYMB_52  */
    _SYMB_42 = 269,                /* _SYMB_42  */
    _SYMB_17 = 270,                /* _SYMB_17  */
    _SYMB_20 = 271,                /* _SYMB_20  */
    _SYMB_53 = 272,                /* _SYMB_53  */
    _SYMB_44 = 273,                /* _SYMB_44  */
    _SYMB_18 = 274,                /* _SYMB_18  */
    _SYMB_15 = 275,                /* _SYMB_15  */
    _SYMB_46 = 276,                /* _SYMB_46  */
    _SYMB_14 = 277,                /* _SYMB_14  */
    _SYMB_34 = 278,                /* _SYMB_34  */
    _SYMB_27 = 279,                /* _SYMB_27  */
    _SYMB_54 = 280,                /* _SYMB_54  */
    _SYMB_57 = 281,                /* _SYMB_57  */
    _SYMB_58 = 282,                /* _SYMB_58  */
    _SYMB_55 = 283,                /* _SYMB_55  */
    _SYMB_56 = 284,                /* _SYMB_56  */
    _SYMB_61 = 285,                /* _SYMB_61  */
    _SYMB_60 = 286,                /* _SYMB_60  */
    _SYMB_59 = 287,                /* _SYMB_59  */
    _SYMB_50 = 288,                /* _SYMB_50  */
    _SYMB_49 = 289,                /* _SYMB_49  */
    _SYMB_6 = 290,                 /* _SYMB_6  */
    _SYMB_31 = 291,                /* _SYMB_31  */
    _SYMB_28 = 292,                /* _SYMB_28  */
    _SYMB_25 = 293,                /* _SYMB_25  */
    _SYMB_13 = 294,                /* _SYMB_13  */
    _SYMB_7 = 295,                 /* _SYMB_7  */
    _SYMB_51 = 296,                /* _SYMB_51  */
    _SYMB_45 = 297,                /* _SYMB_45  */
    _SYMB_9 = 298,                 /* _SYMB_9  */
    _SYMB_19 = 299,                /* _SYMB_19  */
    _SYMB_12 = 300,                /* _SYMB_12  */
    _SYMB_5 = 301,                 /* _SYMB_5  */
    _SYMB_16 = 302,                /* _SYMB_16  */
    _SYMB_3 = 303,                 /* _SYMB_3  */
    _SYMB_26 = 304,                /* _SYMB_26  */
    _SYMB_4 = 305,                 /* _SYMB_4  */
    _SYMB_43 = 306,                /* _SYMB_43  */
    _SYMB_47 = 307,                /* _SYMB_47  */
    _SYMB_48 = 308,                /* _SYMB_48  */
    _SYMB_33 = 309,                /* _SYMB_33  */
    _SYMB_10 = 310,                /* _SYMB_10  */
    _SYMB_32 = 311,                /* _SYMB_32  */
    _LT = 312,                     /* _LT  */
    _EQ = 313,                     /* _EQ  */
    _GT = 314,                     /* _GT  */
    _SYMB_39 = 315,                /* _SYMB_39  */
    _KW_All = 316,                 /* _KW_All  */
    _LBRACK = 317,                 /* _LBRACK  */
    _RBRACK = 318,                 /* _RBRACK  */
    _KW_agent = 319,               /* _KW_agent  */
    _KW_and = 320,                 /* _KW_and  */
    _KW_as = 321,                  /* _KW_as  */
    _KW_define = 322,              /* _KW_define  */
    _KW_domain = 323,              /* _KW_domain  */
    _KW_exists = 324,              /* _KW_exists  */
    _KW_false = 325,               /* _KW_false  */
    _KW_forall = 326,              /* _KW_forall  */
    _KW_formula = 327,             /* _KW_formula  */
    _KW_if = 328,                  /* _KW_if  */
    _KW_iff = 329,                 /* _KW_iff  */
    _KW_imply = 330,               /* _KW_imply  */
    _KW_library = 331,             /* _KW_library  */
    _KW_literal = 332,             /* _KW_literal  */
    _KW_not = 333,                 /* _KW_not  */
    _KW_or = 334,                  /* _KW_or  */
    _KW_otherwise = 335,           /* _KW_otherwise  */
    _KW_postcondition = 336,       /* _KW_postcondition  */
    _KW_predicate = 337,           /* _KW_predicate  */
    _SYMB_41 = 338,                /* _SYMB_41  */
    _KW_problem = 339,             /* _KW_problem  */
    _KW_set = 340,                 /* _KW_set  */
    _KW_true = 341,                /* _KW_true  */
    _LBRACE = 342,                 /* _LBRACE  */
    _RBRACE = 343,                 /* _RBRACE  */
    T_AgentName = 344,             /* T_AgentName  */
    T_ModalityName = 345,          /* T_ModalityName  */
    T_Name = 346,                  /* T_Name  */
    T_Variable = 347,              /* T_Variable  */
    _INTEGER_ = 348                /* _INTEGER_  */
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
  ObservabilityGroupsDef* observabilitygroupsdef_;
  ActionDef* actiondef_;
  ActionParameterDef* actionparameterdef_;
  ActionConditionsDef* actionconditionsdef_;
  ActionTypeSignatureDef* actiontypesignaturedef_;
  ActionPreDef* actionpredef_;
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
  Postcondition* postcondition_;
  ListPostcondition* listpostcondition_;
  LiteralPostcondition* literalpostcondition_;
  ListLiteralPostcondition* listliteralpostcondition_;
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
  FormulaOrEmpty* formulaorempty_;
  MetaTerm* metaterm_;
  ListMetaTerm* listmetaterm_;
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
  AnonVarAgent* anonvaragent_;
  Parameter* parameter_;
  ListParameter* listparameter_;
  ParameterValue* parametervalue_;
  PostParameterValue* postparametervalue_;
  ListPostParameterValue* listpostparametervalue_;
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
  ModelName* modelname_;
  WorldName* worldname_;
  ListWorldName* listworldname_;
  RequireKey* requirekey_;
  ListRequireKey* listrequirekey_;
  TrivialDef* trivialdef_;
  ListName* listname_;
  ListAgentName* listagentname_;
  ListModalityName* listmodalityname_;
  ListVariable* listvariable_;

#line 311 "Bison.H"

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
