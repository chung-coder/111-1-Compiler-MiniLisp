#ifndef AST_HPP
#define AST_HPP
#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
using namespace std;

enum ASTtype{
    ast_stmts, ast_stmt, ast_print_stmt, ast_exp, ast_exps,
    ast_num_op, ast_plus, ast_minus, ast_multiply, ast_divide, ast_mod, ast_greater, ast_smaller, ast_equal,
    ast_logical_op, ast_and, ast_or, ast_not,
    ast_define_stmt, ast_def_variable, ast_get_variable,
    ast_fun_exp, ast_fun_ids, ast_fun_body, ast_fun_call, ast_params, ast_param, ast_fun_name,
    ast_if_exp, ast_test_exp, ast_if_act_exp, ast_then_exp, ast_else_exp,
    ast_ids,
    //new node token type
    AST_NUMBER, AST_BOOL, AST_ID,
    AST_PLUS, AST_MINUS, AST_MULTIPLY, AST_DIVIDE, AST_MOD, AST_GREATER, AST_SMALLER, AST_EQL, AST_AND, AST_OR, AST_NOT,
    AST_PRINT_NUM, AST_PRINT_BOOL, AST_IF, AST_DEFINE, AST_FUN,
};

struct inData
{
    int ival;
    bool bval;
    string sval;
};

class ASTnode{
    public:
        ASTnode *left;
        ASTnode *right;
        ASTtype token_type;
        inData *indata;
        ASTnode(ASTtype, inData *);
        ASTnode();
};

struct type
{
    ASTnode *node;
    inData *indata;
};

class Data{
    public:
        int ival;
        bool bval;
        string sval;
        type nval;
        vector<int> vec_ival;
        vector<bool> vec_bval;
        vector<string> vec_sval;
        vector<type> vec_nval;
        Data();
        Data(int);
        Data(bool);
        Data(string);
        Data(type);
        operator int();
        operator bool();
        operator string();
        operator type();
        operator vector<int>();
        operator vector<bool>();
        operator vector<string>();
        operator vector<type>();
};

void printAST(ASTnode *);
ASTnode *insertNode(ASTtype, ASTnode *, ASTnode *);
Data numOperation(ASTnode *, ASTtype);
Data traverseAST(ASTnode *);

#define YYSTYPE type

#endif