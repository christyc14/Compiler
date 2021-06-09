%option noyywrap
%option yylineno

%{

  #include "parser.tab.hpp"
  #include <string>
  #include <sstream>
  #include <iostream>

extern "C" int fileno(FILE *stream);
extern FILE *yyin;

void yyerror (char const *s);
void printToken();
int createtoken(int T);

%}
jesus          [_a-zA-Z]
christ          [0-9]
O               [0-7]
H               [a-fA-F0-9]
E			          [Ee][+-]?{christ}+
FS			        (f|F|l|L)
IS			        (u|U|l|L)*

%%

{christ}+{IS}?		   { yylval.intNumber=strtol(yytext, NULL, 0); printToken(); return T_INTNUMBER; }
{christ}+{E}{FS}?		{ yylval.intNumber=strtol(yytext, NULL, 0); printToken(); return T_INTNUMBER; }

{christ}*"."{christ}+({E})?{FS}?	{ yylval.decNumber=strtod(yytext, 0); printToken(); return T_DECNUMBER; }
{christ}+"."{christ}*({E})?{FS}?	{ yylval.decNumber=strtod(yytext, 0); printToken(); return T_DECNUMBER; }


"if"            { return createtoken(T_IF); }
"else"          { return createtoken(T_ELSE); }
"while"         { return createtoken(T_WHILE); }
"enum"          { return createtoken(T_ENUM); }
"struct"        { return createtoken(T_STRUCT); }
"switch"        { return createtoken(T_SWITCH); }
"do"            { return createtoken(T_DO); }
"for"           { return createtoken(T_FOR); }
"goto"          {return createtoken(T_GOTO);}
"char"          { return createtoken(T_CHAR); }
"int"           { return createtoken(T_INT);  }
"void"          { return createtoken(T_VOID); }
"short"         { return createtoken(T_SHORT); }
"long"          { return createtoken(T_LONG); }
"float"         { return createtoken(T_FLOAT); }
"double"        { return createtoken(T_DOUBLE); }
"auto"          { return createtoken(T_AUTO); }
"signed"        { return createtoken(T_SIGNED); }
"unsigned"      { return createtoken(T_UNSIGNED); }
"static"        { return createtoken(T_STATIC); }
"register"      { return createtoken(T_REGISTER); }

"typedef"       { return createtoken(T_TYPEDEF); }
"extern"        { return createtoken(T_EXTERN); }

"default"       { return createtoken(T_DEFAULT); }
"return"        { return createtoken(T_RETURN); }
"continue"      { return createtoken(T_CONTINUE); }
"break"         { return createtoken(T_BREAK); }
"case"          { return createtoken(T_CASE); }
"sizeof"        { return createtoken(T_SIZEOF); }

"..."           { return createtoken(T_ELLIPSIS); }
"&&"            { return createtoken(T_AND_OP); }
"||"            { return createtoken(T_OR_OP); }
"=="            { return createtoken(T_EQ_OP); }
"*="            { return createtoken(T_MUL_EQ); }
"/="            { return createtoken(T_DIV_EQ); }
"%="            { return createtoken(T_MOD_EQ); }
"+="            { return createtoken(T_ADD_EQ); }
"-="            { return createtoken(T_SUB_EQ); }
"<<="           { return createtoken(T_LEFT_EQ); }
">>="           { return createtoken(T_RIGHT_EQ); }
"&="            { return createtoken(T_AND_EQ); }
"^="            { return createtoken(T_XOR_EQ); }
"|="            { return createtoken(T_OR_EQ); }
"<="            { return createtoken(T_LEEQ_OP); }
">="            { return createtoken(T_GREQ_OP); }
"!="            { return createtoken(T_NE_OP); }
"&"             {return createtoken(T_AMPER);}
"++"            { return createtoken(T_INC_OP); }
"--"            { return createtoken(T_DEC_OP); }
"<<"            { return createtoken(T_LEFT_OP); }
">>"            { return createtoken(T_RIGHT_OP); }
"->"            {return createtoken(T_PTR_OP);}
"*"             { return createtoken(T_STAR); }
"+"             { return createtoken(T_PLUS); }
"/"             { return createtoken(T_FSLASH); }
"-"             { return createtoken(T_MINUS); }
"="             { return createtoken(T_ASSIGN); }
"|"             { return createtoken(T_BAR); }
"^"             { return createtoken(T_HAT); }
"<"             { return createtoken(T_LESSTHAN); }
">"             { return createtoken(T_GREATERTHAN); }
"?"             { return createtoken(T_QUESTIONM); }
"~"             { return createtoken(T_TILDE); }
"%"             { return createtoken(T_MOD); }
"!"             {return createtoken(T_EXCL);}
"{"             { return createtoken(T_LCB); }
"}"             { return createtoken(T_RCB); }
"("             { return createtoken(T_LB); }
")"             { return createtoken(T_RB); }
"["             { return createtoken(T_LSQB); }
"]"             { return createtoken(T_RSQB); }

":"             { return createtoken(T_COLON);}
"."             { return createtoken(T_DOT);}
";"             { return createtoken(T_SEMICOLON); }
","             { return createtoken(T_COMMA); }
[0-9]+            { yylval.intNumber=strtol(yytext, NULL, 0); printToken(); return T_INTNUMBER; }
{jesus}({jesus}|{christ})*       {  return createtoken(T_ID); } //wtf are these even christy
jesus?\"(\\.|[^\\"])*\"	          { yylval.string=new std::string(yytext); printToken(); return T_STRING_LITERAL; }

(\/\/).*                {;}
(\/\*)[^*]*|[*]*(\*\/)  {;}
[ ] {;}
[\t\v\r\n\f]+ {;}

.               { fprintf(stderr, "Invalid token\n"); yyerror(yytext); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error on line: %i\n", yylineno);
  printToken();
  exit(1);
}

int createtoken(int T){
  yylval.string = new std::string(yytext);
  printToken();
  return T;
}
void printToken(){

  std::cerr << "here is the yytext: " << yytext << std::endl;
}
