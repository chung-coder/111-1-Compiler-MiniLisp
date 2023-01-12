# 111-1-Compiler-MiniLisp
## How To Execute
```
cd final
make
./final < 01_1.lsp
python test_tool.py
```

## Defined Classes Functions
### classes:
**ASTnode**: node in abstract systax tree
**Data**: data that passing while traversing AST

### functions:

**printAST**: display AST structure
**insertNode**: construct the AST
**traverseAST**: traverse AST and perfom corresponding behaviors

## Grammar
```
program         : stmts
stmts           : stmt stmts
                | ε
stmt            : exp
                | def_stmt
                | print_stmt
print_stmt      : '(' PRINT_NUM exp ')'
                | '(' PRINT_BOOL exp ')'
exps            : exp exps
                | ε
exp             : BOOL_VAL
                | NUMBER
                | get_variable
                | num_op
                | logical_op
                | fun_exp
                | fun_call
                | if_exp
num_op          : plus
                | minus
                | multiply
                | divide
                | modulus
                | greater
                | smaller
                | equal
        plus            : '(' PLUS exp exps ')'
        minus           : '(' MINUS exp exp ')'
        multiply        : '(' MUL exp exps ')'
        divide          : '(' DIV exp exp ')'
        modulus         : '(' MOD exp exp ')'
        greater         : '(' GREATER exp exp ')'
        smaller         : '(' SMALLER exp exp ')'
        equal           : '(' EQL exp exps ')'
logical_op      : and_op
                | or_op
                | not_op
        and_op          : '(' AND exp exps ')'
        or_op           : '(' OR exp exps ')'
        not_op          : '(' NOT exp ')'
def_stmt        : '(' DEFINE def_variable exp ')'
def_variable    : ID
get_variable    : ID
fun_exp         : '(' FUN fun_ids fun_body ')'
        fun_ids         : '(' ids ')'
        fun_body        : exp
fun_call        : '(' fun_exp params ')'
                | '(' fun_name params ')'
        params          : ε
                        | param params
        param           : exp
        fun_name        : ID
if_exp          : '(' IF test_exp if_act_exp ')'
        test_exp        : exp
        if_act_exp      : then_exp else_exp
        then_exp        : exp
        else_exp        : exp
ids             : 
                | ID ids
```

## Basic Features
> complete

| Features             | Description                                   |
|:-------------------- | --------------------------------------------- |
| Syntax Validation    | Text                                          |
| Print                | Implement print-num statement                 |
| Numerical Operations | Implement all numerical operations            |
| Logical Expression   | Implement all logical operations              |
| if Expression        | Implement if expression                       |
| Variable Definition  | Able to define a variable                     |
| Function             | Able to declare and call a anonymous function |
| Named Function       | Able to declare and call a named function     |

## Bonus Features
> incomplete

| Features             | Description                             |
| -------------------- |:--------------------------------------- |
| Recursion            | Support recursive function call         |
| Type Checking        | Print error messages for type errors    |
| Nested Function      | Nested function (static scope)          |
| First-class Function | Able to pass functions, support closure |


