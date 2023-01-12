%{
#include "ast.hh"

extern "C"
{
        void yyerror(const char *s);
        extern int yylex(void);
}

ASTnode *root;
%}
%type<node> program stmts stmt print_stmt exps exp
%type<node> num_op plus minus multiply divide modulus greater smaller equal
%type<node> logical_op and_op or_op not_op
%type<node> def_stmt def_variable get_variable
%type<node> fun_exp fun_ids fun_body fun_call params param fun_name
%type<node> if_exp test_exp if_act_exp then_exp else_exp
%type<node> ids

%token<indata> NUMBER
%token<indata> BOOL_VAL
%token<indata> ID
%token PRINT_NUM PRINT_BOOL
%left PLUS MINUS MUL DIV MOD GREATER SMALLER EQL AND OR NOT IF DEFINE FUN '(' ')'

%%
program         : stmts         {root = $$; }
                ;
stmts           : stmt stmts    {$$ = insertNode(ast_stmts, $1, $2);}
                |               {$$ = NULL;}
                ;
stmt            : exp           {$$ = insertNode(ast_stmt, $1, NULL );}
                | def_stmt      {$$ = insertNode(ast_stmt, $1, NULL );}
                | print_stmt    {$$ = insertNode(ast_stmt, $1, NULL );}
                ;
print_stmt      : '(' PRINT_NUM exp ')'         {$$ = insertNode(ast_print_stmt, new ASTnode(AST_PRINT_NUM, NULL), $3 );}
                | '(' PRINT_BOOL exp ')'        {$$ = insertNode(ast_print_stmt, new ASTnode(AST_PRINT_BOOL, NULL), $3 );}
                ;
exps            : exp exps      {$$ = insertNode(ast_exps, $1, $2 );}
                |               {$$ = NULL;}
                ;
exp             : BOOL_VAL      {$$ = insertNode(ast_exp, new ASTnode(AST_BOOL, $1), NULL);}
                | NUMBER        {$$ = insertNode(ast_exp, new ASTnode(AST_NUMBER, $1), NULL);}
                | get_variable  {$$ = insertNode(ast_exp, $1, NULL);}
                | num_op        {$$ = insertNode(ast_exp, $1, NULL);}
                | logical_op    {$$ = insertNode(ast_exp, $1, NULL);}
                | fun_exp       {$$ = insertNode(ast_exp, $1, NULL);}
                | fun_call      {$$ = insertNode(ast_exp, $1, NULL);}
                | if_exp        {$$ = insertNode(ast_exp, $1, NULL);}
                ;
num_op          : plus          {$$ = insertNode(ast_num_op, $1, NULL);}
                | minus         {$$ = insertNode(ast_num_op, $1, NULL);}
                | multiply      {$$ = insertNode(ast_num_op, $1, NULL);}
                | divide        {$$ = insertNode(ast_num_op, $1, NULL);}
                | modulus       {$$ = insertNode(ast_num_op, $1, NULL);}
                | greater       {$$ = insertNode(ast_num_op, $1, NULL);}
                | smaller       {$$ = insertNode(ast_num_op, $1, NULL);}
                | equal         {$$ = insertNode(ast_num_op, $1, NULL);}
                ;
        plus            : '(' PLUS exp exps ')'     {$$ = insertNode(ast_plus, $3, $4);}
                        ;
        minus           : '(' MINUS exp exp ')'     {$$ = insertNode(ast_minus, $3, $4);}
                        ;
        multiply        : '(' MUL exp exps ')'      {$$ = insertNode(ast_multiply, $3, $4);}
                        ;
        divide          : '(' DIV exp exp ')'       {$$ = insertNode(ast_divide, $3, $4);}
                        ;
        modulus         : '(' MOD exp exp ')'       {$$ = insertNode(ast_mod, $3, $4);}
                        ;
        greater         : '(' GREATER exp exp ')'   {$$ = insertNode(ast_greater, $3, $4);}
                        ;
        smaller         : '(' SMALLER exp exp ')'   {$$ = insertNode(ast_smaller, $3, $4);}
                        ;
        equal           : '(' EQL exp exps ')'      {$$ = insertNode(ast_equal, $3, $4);}
                        ;
logical_op      : and_op        {$$ = insertNode(ast_logical_op, $1, NULL);}
                | or_op         {$$ = insertNode(ast_logical_op, $1, NULL);}
                | not_op        {$$ = insertNode(ast_logical_op, $1, NULL);}
                ;
        and_op          : '(' AND exp exps ')'      {$$ = insertNode(ast_and, $3, $4);}
                        ;
        or_op           : '(' OR exp exps ')'       {$$ = insertNode(ast_or, $3, $4);}
                        ;
        not_op          : '(' NOT exp ')'           {$$ = insertNode(ast_not, $3, NULL);}
                        ;
def_stmt        : '(' DEFINE def_variable exp ')'   {$$ = insertNode(ast_define_stmt, $3, $4);}
                ;
def_variable    : ID                                {$$ = insertNode(ast_def_variable, new ASTnode(AST_ID, $1), NULL);}
                ;
get_variable    : ID                                {$$ = insertNode(ast_get_variable, new ASTnode(AST_ID, $1), NULL);}
                ;
fun_exp         : '(' FUN fun_ids fun_body ')'      {$$ = insertNode(ast_fun_exp, $3, $4);}
                ;
        fun_ids         : '(' ids ')'               {$$ = insertNode(ast_fun_ids, $2, NULL);}
                        ;
        fun_body        : exp                       {$$ = insertNode(ast_fun_body, $1, NULL);}
                        ;
fun_call        : '(' fun_exp params ')'            {$$ = insertNode(ast_fun_call, $2, $3);}
                | '(' fun_name params ')'           {$$ = insertNode(ast_fun_call, $2, $3);}
        params          :               {$$ = NULL;}
                        | param params  {$$ = insertNode(ast_params, $1, $2);}
                        ;
        param           : exp           {$$ = insertNode(ast_param, $1, NULL);}
                        ;
        fun_name        : ID            {$$ = insertNode(ast_fun_name, new ASTnode(AST_ID, $1), NULL);}
                        ;
if_exp          : '(' IF test_exp if_act_exp ')'    {$$ = insertNode(ast_if_exp, $3, $4);}
                ;
        test_exp        : exp                   {$$ = insertNode(ast_test_exp, $1, NULL);}
                        ;
        if_act_exp      : then_exp else_exp     {$$ = insertNode(ast_if_act_exp, $1, $2);}
                        ;
        then_exp        : exp                   {$$ = insertNode(ast_then_exp, $1, NULL);}
                        ;
        else_exp        : exp                   {$$ = insertNode(ast_else_exp, $1, NULL);}
                        ;
ids             :               {$$ = NULL;}
                | ID ids        {$$ = insertNode(ast_ids, new ASTnode(AST_ID, $1), $2);}
                ;
%%

void yyerror (const char *s)
{
        cerr << s << endl;
}

int main() {
        yyparse();
        traverseAST(root);
        return(0);
}
