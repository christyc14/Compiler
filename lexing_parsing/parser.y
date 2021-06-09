%code requires{
  #include "ast.hpp"
  #include <fstream>
  #include <string>
  #include <iostream>

  extern Node *g_root; // a way of getting the AST out
  extern FILE* yyin;

  //this is to fix problems when generating C++
  // we are declaring the functions provided by Flex, so that bison can call them
  int yylex(void);
  void yyerror(const char *);
}

//represents the value associated with any kind of ast node

%union{
  Node* node;
  double decNumber;
  int intNumber;
  std::string *string;
}

%token T_ID T_LB T_RB T_RSQB T_LSQB T_LCB T_RCB T_STRING_LITERAL
%token T_DOT T_PTR_OP T_SEMICOLON T_COLON T_COMMA T_INC_OP T_DEC_OP
%token T_STAR T_PLUS T_MINUS T_FSLASH T_MOD
%token T_LEFT_OP T_RIGHT_OP T_LESSTHAN T_GREATERTHAN T_LEEQ_OP T_GREQ_OP T_EQ_OP T_NE_OP
%token T_HAT T_BAR T_AND_OP T_OR_OP T_QUESTIONM
%token T_EQ T_MUL_EQ T_DIV_EQ T_MOD_EQ T_ADD_EQ T_SUB_EQ T_LEFT_EQ T_RIGHT_EQ T_AND_EQ T_XOR_EQ T_OR_EQ
%token T_TYPEDEF T_EXTERN T_STATIC T_AUTO T_REGISTER T_VOID T_CHAR T_SHORT T_INT T_LONG T_FLOAT T_DOUBLE T_SIGNED T_UNSIGNED T_TYPE_NAME
%token T_STRUCT T_ENUM T_ELLIPSIS T_DEFAULT T_SWITCH T_CONTINUE T_DO T_WHILE T_FOR T_RETURN
%token T_DECNUMBER T_INTNUMBER T_BREAK T_CASE T_ELSE T_IF T_SIZEOF T_ASSIGN T_EOF
%token T_GOTO T_AMPER T_EXCL T_TILDE

%type<node> Primary_Expression Postfix_Expression Argument_Expression_List Cast_Expression
%type<node> Multiplicative_Expression Additive_Expression Shift_Expression Relational_Expression Equality_Expression
%type<node> And_Expression Exclusive_Or_Expression Inclusive_Or_Expression Logical_And_Expression Logical_Or_Expression
%type<node> Conditional_Expression Assignment_Expression Expression Constant_Expression Declaration Init_Declarator_List
%type<node>  Init_Declarator  Struct_Declaration_List Struct_Declaration Declaration_List
%type<node> Struct_Declarator_List Struct_Declarator  Enumerator_List
%type<node> Enumerator Declarator Direct_Declarator Pointer Parameter_type_list Parameter_List Parameter_Declaration
%type<node> Identifier_List Abstract_Declarator Direct_Abstract_Declarator Initializer Initializer_List Statement
%type<node> Labeled_Statement Compound_Statement Statement_List Expression_Statement Selection_Statement
%type<node> Iteration_Statement Jump_Statement Translation_Unit External_Declaration Function_Definition
%type<node> Unary_Expression

%type<string> Assignment_Operator Unary_Operator Type_Specifier Storage_Class_Specifier
%type<string> Declaration_Specifiers Type_Name Specifier_Qualifier_List
%type<string> Struct_Specifier Enum_Specifier
%type<string> T_INC_OP T_DEC_OP T_PLUS T_STAR T_MINUS T_TILDE T_EXCL
%type<string> T_STRING_LITERAL T_ID T_VOID T_CHAR T_SHORT T_INT T_LONG T_DOUBLE T_FLOAT T_SIGNED T_UNSIGNED T_TYPE_NAME
%type<string> T_FSLASH T_MOD T_LEFT_OP T_RIGHT_OP T_LESSTHAN T_GREATERTHAN T_LEEQ_OP T_GREQ_OP T_EQ_OP
%type<string> T_NE_OP T_HAT T_BAR T_AND_OP T_OR_OP T_ASSIGN T_MUL_EQ T_DIV_EQ T_MOD_EQ T_ADD_EQ T_SUB_EQ
%type<string> T_LEFT_EQ T_RIGHT_EQ T_AND_EQ T_XOR_EQ T_OR_EQ T_EXTERN T_FOR T_GOTO T_AMPER T_PTR_OP
%type<decNumber> T_DECNUMBER
%type<intNumber> T_INTNUMBER


%start Translation_Unit

%%

Primary_Expression          : T_ID {std::cerr << "T_ID primary expression" << std::endl; $$ = new Variable($1);}
                            | T_INTNUMBER { $$ = new Integer($1); }
                            | T_DECNUMBER {$$ = new Floating($1);}
                            | T_STRING_LITERAL {$$ = new String($1);}
                            | T_LB Expression T_RB {$$ = $2;}
                            ;

Postfix_Expression          : Primary_Expression { $$ = $1; }
                            | Postfix_Expression T_LSQB Expression T_RSQB
                            | Postfix_Expression T_LB T_RB {$$ = new CallFunction($1, NULL);}
                            | Postfix_Expression T_LB Argument_Expression_List T_RB {$$ = new CallFunction($1,$3);}
                            | Postfix_Expression T_DOT T_ID
                            | Postfix_Expression T_PTR_OP T_ID
                            | Postfix_Expression T_INC_OP {$$ = new PostFix_Exp($1,$2);}
                            | Postfix_Expression T_DEC_OP {$$ = new PostFix_Exp($1,$2);}
                            ;

Argument_Expression_List    : Assignment_Expression {$$ = new StatementList(); $$->insert($1); $$->settype("ARG_EXP");}
  	                        | Argument_Expression_List T_COMMA Assignment_Expression {$$->insert($3); $$ = $1;}
  	                        ;

Unary_Expression            : Postfix_Expression { $$ = $1; }
                        	  | T_INC_OP Unary_Expression {$$ = new UnaryOp($1, $2);}
                            | T_DEC_OP Unary_Expression {$$ = new UnaryOp($1, $2);}
                        	  | Unary_Operator Cast_Expression {$$ = new UnaryOp($1, $2);}
                        	  | T_SIZEOF Unary_Expression {$$ = new SizeOf();}
                        	  | T_SIZEOF T_LB Type_Name T_RB  {$$ = new SizeOf();}
                        	  ;

Unary_Operator              : T_AND_OP {$$ = $1;}
                            | T_STAR {$$ = $1;}
                            | T_PLUS {$$ = $1;}
                            | T_MINUS {$$ = $1;}
                            | T_TILDE {$$ = $1;}
                            | T_EXCL {$$ = $1;}
                            ;

Cast_Expression             : Unary_Expression { $$ = $1; }
                          	| T_LB Type_Name T_RB Cast_Expression {;}
                          	;

Multiplicative_Expression   : Cast_Expression { $$ = $1; }
                          	| Multiplicative_Expression T_STAR Cast_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	| Multiplicative_Expression T_FSLASH Cast_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	| Multiplicative_Expression T_MOD Cast_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Additive_Expression	        : Multiplicative_Expression { $$ = $1; }
                          	| Additive_Expression T_PLUS Multiplicative_Expression {std::cerr << "Additive_Expression T_PLUS Multiplicative_Expression" << '\n';$$ = new BitwiseOp($1, $2, $3);}
                          	| Additive_Expression T_MINUS Multiplicative_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Shift_Expression            : Additive_Expression { $$ = $1; }
                          	| Shift_Expression T_LEFT_OP Additive_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	| Shift_Expression T_RIGHT_OP Additive_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Relational_Expression       : Shift_Expression { $$ = $1; }
                          	| Relational_Expression T_LESSTHAN Shift_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	| Relational_Expression T_GREATERTHAN Shift_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	| Relational_Expression T_LEEQ_OP Shift_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	| Relational_Expression T_GREQ_OP Shift_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Equality_Expression         : Relational_Expression { $$ = $1; }
                          	| Equality_Expression T_EQ_OP Relational_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	| Equality_Expression T_NE_OP Relational_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

And_Expression              : Equality_Expression { $$ = $1; }
                          	| And_Expression T_AND_OP Equality_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Exclusive_Or_Expression     : And_Expression { $$ = $1; }
                          	| Exclusive_Or_Expression T_HAT And_Expression {$$ = new BitwiseOp($1, $2, $3);} //''^''
                          	;

Inclusive_Or_Expression     : Exclusive_Or_Expression { $$ = $1; }
                          	| Inclusive_Or_Expression T_OR_OP Exclusive_Or_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Logical_And_Expression      : Inclusive_Or_Expression { $$ = $1; }
                          	| Logical_And_Expression T_AMPER Inclusive_Or_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Logical_Or_Expression       : Logical_And_Expression { $$ = $1; }
                          	| Logical_Or_Expression T_BAR Logical_And_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Conditional_Expression      : Logical_Or_Expression { $$ = $1; }
                            | Logical_Or_Expression T_QUESTIONM Expression T_COLON Conditional_Expression {$$ = new Conditional($1, $3, $5);}
                            ;

Assignment_Expression       : Conditional_Expression { $$ = $1; }
                          	| Unary_Expression Assignment_Operator Assignment_Expression {$$ = new BitwiseOp($1, $2, $3);}
                          	;

Assignment_Operator         : T_ASSIGN {$$ = $1;}
                          	| T_MUL_EQ {$$ = $1;}
                          	| T_DIV_EQ {$$ = $1;}
                          	| T_MOD_EQ {$$ = $1;}
                          	| T_ADD_EQ {$$ = $1;}
                          	| T_SUB_EQ {$$ = $1;}
                          	| T_LEFT_EQ {$$ = $1;}
                          	| T_RIGHT_EQ {$$ = $1;}
                          	| T_AND_EQ {$$ = $1;}
                          	| T_XOR_EQ {$$ = $1;}
                          	| T_OR_EQ {$$ = $1;}
                          	;

Expression                  : Assignment_Expression { $$ = $1; }
                          	| Expression T_COMMA Assignment_Expression
                          	;

Constant_Expression         : Conditional_Expression {$$ = $1;}
	                          ;

Declaration                 : Declaration_Specifiers T_SEMICOLON {$$ = new Declare($1, NULL);}
                          	| Declaration_Specifiers Init_Declarator_List T_SEMICOLON {$$ = new Declare($1,$2);}
                          	;

Declaration_Specifiers      : Storage_Class_Specifier { $$ = $1; }
                          	| Storage_Class_Specifier Declaration_Specifiers {$$ = new std::string(*$1 + " " + *$2);}
                          	| Type_Specifier { $$ = $1; }
                          	| Type_Specifier Declaration_Specifiers {$$ = new std::string(*$1 + " " + *$2);}
                          	;

Init_Declarator_List        : Init_Declarator {$$ = new StatementList(); $$->insert($1); $$->settype("INIT");}
                          	| Init_Declarator_List T_COMMA Init_Declarator {$1->insert($3); $$ = $1;}
                          	;

Init_Declarator             : Declarator {std::cerr << "Init declarator" << std::endl; $$ = new InitDeclare($1, NULL);}
                          	| Declarator T_ASSIGN Initializer {std::cerr << "Declarator T_EQ Initializer " << std::endl; $$ = new InitDeclare($1, $3);}
                          	;

Storage_Class_Specifier     : T_TYPEDEF
                          	| T_EXTERN {$$ = $1;}
                          	| T_STATIC
                          	| T_AUTO
                          	| T_REGISTER
                          	;

Type_Specifier              : T_VOID                         { $$ = $1; }
                          	| T_CHAR                         { $$ = $1; }
                          	| T_SHORT                        { $$ = $1; }
                          	| T_INT                          { $$ = $1; }
                          	| T_LONG                         { $$ = $1; }
                          	| T_FLOAT                        { $$ = $1; }
                          	| T_DOUBLE                       { $$ = $1; }
                          	| T_SIGNED                       { $$ = $1; }
                          	| T_UNSIGNED                     { $$ = $1; }
                          	| Struct_Specifier
                          	| Enum_Specifier
                          	| T_TYPE_NAME                    { $$ = $1; }
                          	;

Struct_Specifier            : T_STRUCT T_ID T_LCB Struct_Declaration_List T_RCB
                          	| T_STRUCT T_LCB Struct_Declaration_List T_RCB
                          	| T_STRUCT T_ID
                          	;

Struct_Declaration_List     : Struct_Declaration
                          	| Struct_Declaration_List Struct_Declaration
                          	;

Struct_Declaration          : Specifier_Qualifier_List Struct_Declarator_List T_SEMICOLON
        	                  ;

Specifier_Qualifier_List    : Type_Specifier Specifier_Qualifier_List {$$ = new std::string(*$1 + " " + *$2);}
                          	| Type_Specifier {$$ = $1;}
                          	;

Struct_Declarator_List      : Struct_Declarator
                          	| Struct_Declarator_List T_COMMA Struct_Declarator
                          	;

Struct_Declarator           : Declarator
                          	| T_COLON Constant_Expression
                          	| Declarator T_COLON Constant_Expression
                          	;

Enum_Specifier              : T_ENUM T_LCB Enumerator_List T_RCB
                          	| T_ENUM T_ID T_LCB Enumerator_List T_RCB
                          	| T_ENUM T_ID
            	              ;

Enumerator_List             : Enumerator
                          	| Enumerator_List T_COMMA Enumerator
                          	;

Enumerator                  : T_ID
                          	| T_ID T_ASSIGN Constant_Expression
                          	;

/*
Type_Qualifier              : T_CONST
                          	| T_VOLATILE
                          	;  no volatile or const :)
*/

Declarator                  : Pointer Direct_Declarator
                          	| Direct_Declarator  { std::cerr << "direct declarator entered" << std::endl; $$ = $1; std::cerr << "u wot" << std::endl; }
                          	;

Direct_Declarator           : T_ID { std::cerr << "t_id, direct declarator" << std::endl; $$ = new Variable($1); }
                          	| T_LB Declarator T_RB {$$ = $2;}
                          	| Direct_Declarator T_LSQB Constant_Expression T_RSQB
                          	| Direct_Declarator T_LSQB T_RSQB
                          	| Direct_Declarator T_LB Parameter_type_list T_RB {std::cerr << "Direct_Declarator T_LB Parameter_type_list T_RB" << std::endl; $$ = new DirectDeclarator($1, $3);}
                          	| Direct_Declarator T_LB Identifier_List T_RB {std::cerr << "Direct_Declarator T_LB Identifier_List T_RB" << std::endl; $$ = new DirectDeclarator($1,$3);}
                          	| Direct_Declarator T_LB T_RB {std::cerr<< " Direct_Declarator T_LB T_RB " << std::endl; $$ = new DirectDeclarator($1); }
                          	;

Pointer                     : T_STAR
                          	| T_STAR Pointer
                          	;

Parameter_type_list         : Parameter_List {$$ = $1;}
                          //	| Parameter_List T_COMMA T_ELLIPSIS // do we need this????
                          	;

Parameter_List              : Parameter_Declaration {$$ = new StatementList(); $$->insert($1); $$->settype("PAR");}
                          	| Parameter_List T_COMMA Parameter_Declaration {$1->insert($3); $$ = $1;}
                          	;

Parameter_Declaration       : Declaration_Specifiers Declarator {std::cerr << "Parameter Declaration" << std::endl; $$ = new Paramdeclare($1,$2);}
                          	| Declaration_Specifiers Abstract_Declarator
                          	| Declaration_Specifiers
                          	;

Identifier_List             : T_ID {$$ = new IdList(); $$->insert($1);}
                          	| Identifier_List T_COMMA T_ID {$1->insert($3); $$ = $1;}
                          	;

Type_Name                   : Specifier_Qualifier_List {$$ = $1;}
                          	| Specifier_Qualifier_List Abstract_Declarator {$$ = $1;}
                          	;

Abstract_Declarator         : Pointer
                          	| Direct_Abstract_Declarator
                          	| Pointer Direct_Abstract_Declarator
                          	;

Direct_Abstract_Declarator  : T_LB Abstract_Declarator T_RB
                          	| T_LSQB T_RSQB
                          	| T_LSQB Constant_Expression T_RSQB
                          	| Direct_Abstract_Declarator T_LSQB T_RSQB
                          	| Direct_Abstract_Declarator T_LSQB Constant_Expression T_RSQB
                          	| T_LB T_RB
                          	| T_LB Parameter_type_list T_RB
                          	| Direct_Abstract_Declarator T_LB T_RB
                          	| Direct_Abstract_Declarator T_LB Parameter_type_list T_RB
                          	;

Initializer                 : Assignment_Expression {$$ = $1;}
                          	| T_LCB Initializer_List T_LCB {$$ = $2;}
                          	| T_LCB Initializer_List T_COMMA T_LCB {$$ = $2;}
                          	;

Initializer_List            : Initializer { std::cerr << "idk what this does k" << std::endl; $$ = new StatementList(); $$->insert($1); $$->settype("INITLIST");}
                          	| Initializer_List T_COMMA Initializer {$1->insert($3); $$ = $1;}
                          	;

Statement                   : Labeled_Statement { $$ = $1; }
                          	| Compound_Statement { $$ = $1; }
                          	| Expression_Statement { $$ = $1; }
                          	| Selection_Statement { $$ = $1; }
                          	| Iteration_Statement { $$ = $1; }
                          	| Jump_Statement { $$ = $1; }
                          	;

Labeled_Statement           : T_ID T_COLON Statement
                          	| T_CASE Constant_Expression T_COLON Statement
                          	| T_DEFAULT T_COLON Statement
                          	;

Compound_Statement          : T_LCB T_RCB {$$ = new Encapsulate(NULL);}
                          	| T_LCB Statement_List T_RCB { $$ = new Encapsulate($2); }
                          	| T_LCB Declaration_List T_RCB {$$ = new Encapsulate($2);}
                          	| T_LCB Declaration_List Statement_List T_RCB {$$ = new Encapsulate($2,$3);}
                          	;

Declaration_List            : Declaration {$$ = new StatementList(); $$->insert($1); $$->settype("DEC"); }
                          	| Declaration_List Declaration {$1->insert($2); $$ = $1;}
                          	;

Statement_List              : Statement { $$ = new StatementList(); $$->insert($1);$$->settype("somethingelse"); }
                          	| Statement_List Statement { $1->insert($2); $$ = $1; }
                          	;

Expression_Statement        : T_SEMICOLON {$$ = NULL;}
                          	| Expression T_SEMICOLON {$$ = $1;}
                          	;

Selection_Statement         : T_IF T_LB Expression T_RB Statement {$$ = new Ifelse($3, $5, NULL);}
                          	| T_IF T_LB Expression T_RB Statement T_ELSE Statement {$$ = new Ifelse($3, $5, $7);}
                          	| T_SWITCH T_LB Expression T_RB Statement
                          	;

Iteration_Statement         : T_WHILE T_LB Expression T_RB Statement {$$ = new While_Loop($3, $5);}
                          	| T_DO Statement T_WHILE T_LB Expression T_RB T_SEMICOLON {$$ = new Do_While_Loop($2, $5);}
                          	| T_FOR T_LB Expression_Statement Expression_Statement T_RB Statement
                          	| T_FOR T_LB Expression_Statement Expression_Statement Expression T_RB Statement { $$ = new Forloop($3, $4, $5, $7); }
                          	;

Jump_Statement              : T_CONTINUE T_SEMICOLON
                          	| T_BREAK T_SEMICOLON
                          	| T_RETURN T_SEMICOLON {$$ = new Return(NULL);}
                          	| T_RETURN Expression T_SEMICOLON { std::cerr << "return statement" << '\n';$$ = new Return($2); }
                          	;

Translation_Unit            : External_Declaration {std::cerr << "translation_unit" << std::endl; g_root->insert($1);std::cerr << "hi my name is jeff " << std::endl; }
	                          | Translation_Unit External_Declaration { std::cerr << "translation unit, external dec" << std::endl; g_root->insert($2); }
  ;

External_Declaration        : Function_Definition { std::cerr << "external declaration" << std::endl; $$ = $1; }
                            | Declaration { $$ = $1; }
                            ;

Function_Definition         : Declaration_Specifiers Declarator Compound_Statement { std::cerr << "entered function rule" << std::endl; $$ = new Function($1 ,$2 ,$3); std::cerr << "done function creation" << std::endl; }
                          	| Declarator Declaration_List Compound_Statement {}
                          	| Declarator Compound_Statement {}
                          	;
%%

Node* g_root;
//const Node *g_root; // Definition of variable (to match declaration earlier)

Node* parseAST(std::string name)
{
  g_root = new TranslationUnit();
  yyin = fopen(name.c_str(), "r");

  std::cerr << "name is : " << name << std::endl;

  if (!yyin){
    std::cerr << "poop" << std::endl;
  }
  else if(yyin){
    std::cerr << "opened file" << '\n';
    yyparse();
    std::cerr << "yyparse done" << std::endl;
  }
   fclose(yyin);
   std::cerr << "parsed" << std::endl;
 return g_root; /*

 g_root = 0;
   yyparse();
   return g_root; */
}
