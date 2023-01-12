%{
#include "ast.hh"
#include "miniLisp.tab.h"
using namespace std;

extern "C"
{
    int yywrap(void);
    int yylex(void);
}
%}

separator       [\t|\n|\r| ]
letter          [a-z]
digit           [0-9]
number          0|[1-9]{digit}*|-[1-9]{digit}*
id              {letter}({letter}|{digit}|\-)*
bool-val-t      #t
bool-val-f      #f
%%
{separator}     {}
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"mod"           { return MOD; }
">"             { return GREATER; }
"<"             { return SMALLER; }
"="             { return EQL; }
"and"           { return AND; }
"or"            { return OR; }
"not"           { return NOT; }
"print-num"     { return PRINT_NUM; }
"print-bool"    { return PRINT_BOOL; }
"if"            { return IF; }
"define"        { return DEFINE; }
"fun"|"lambda"  { return FUN; }

{number}        { yylval.indata = new inData{atoi(yytext), true, "\0"}; return NUMBER; }
{id}            { yylval.indata = new inData{0, true, strdup(yytext)}; return ID; }
{bool-val-t}    { yylval.indata = new inData{0, 1, "\0"}; return BOOL_VAL;}
{bool-val-f}    { yylval.indata = new inData{0, 0, "\0"}; return BOOL_VAL;}
.               { return yytext[0];}

%%
int yywrap(void)
{
    return 1;
}
