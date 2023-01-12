#include "ast.hh"
using namespace std;

ASTnode::ASTnode() {}
ASTnode::ASTnode(ASTtype token, inData *in) {
     this->token_type = token;
     this->indata = in; 
}
Data::Data() {}
Data::Data(int data) {this->ival = data;}
Data::Data(bool data) {this->bval = data;}
Data::Data(string data) {this->sval = data;}
Data::Data(type data) {this->nval = data;}
Data::operator int() { return this->ival; }
Data::operator bool() { return this->bval; }
Data::operator string() { return this->sval; }
Data::operator type() { return this->nval; }
Data::operator vector<int>() { return this->vec_ival; }
Data::operator vector<bool>() { return this->vec_bval; }
Data::operator vector<string>() { return this->vec_sval; }
Data::operator vector<type>() { return this->vec_nval; }

// function
map<string, type> table;
map<string, type> fun_table;
void printAST(ASTnode *tree)
{
    if(tree == NULL) {
        cout << "NULL tree";
        return ;
    }
    if (tree->left || tree->right) cout << "(";
    if (tree->indata)
        printf(" [%d, %d, %s] ", tree->indata->ival, tree->indata->bval, tree->indata->sval.c_str());
    if (tree->left) printAST(tree->left);
    if (tree->right) printAST(tree->right);
    if (tree->left || tree->right) cout << ")";
}

ASTnode *insertNode(ASTtype token, ASTnode *left, ASTnode *right)
{
    ASTnode *node = new ASTnode();
    node->left = left;
    node->right = right;
    node->token_type = token;
    node->indata = NULL;
    return node;
}

Data numOperation(Data data, ASTtype op){
    Data result = Data();
    vector<int> vec_ival = data;
    vector<bool> vec_bval = data;
    int tmp;
    switch (op)
    {
        case ast_plus:
            result.ival = 0;
            for(auto i : vec_ival){
                result.ival += i;
            } 
            break;
        case ast_multiply:
            result.ival = 1;
            for(auto i : vec_ival){
                result.ival *= i;
            } 
            break;
        case ast_equal:
            tmp = vec_ival[0];
            result.bval = 1; //true
            for(auto i : vec_ival){
                if(i != tmp)
                    result.bval = 0; //false
            } 
            break;
        case ast_and:
            result.bval = 1;
            for(auto i : vec_bval){
                result.bval &= i;
            } 
            break;
        case ast_or:
            result.bval = 0;
            for(auto i : vec_bval){
                result.bval |= i;
            } 
            break;
    }
    return result;
};

Data traverseAST(ASTnode *pointer)
{
    if(pointer == NULL) return Data(0);

    Data left = traverseAST(pointer->left);
    Data right = traverseAST(pointer->right);
    
    switch(pointer->token_type){
        case ast_stmts:
            return left;
        case ast_stmt:
            return left;
        case ast_exp:
            return left;
        case ast_exps:
            // left:  exp int/bool
            // right: exps vector<int/bool>
            right.vec_ival.push_back(left.ival);
            right.vec_bval.push_back(left.bval);
            return right;
        case ast_print_stmt:
        {
            if(left == AST_PRINT_NUM)
                cout << right.ival << endl;
            else if(left == AST_PRINT_BOOL)
            {
                if((bool)right) cout << "#t" << endl;
                else cout << "#f" << endl;
            }
            return Data(1);
        }
        case AST_PRINT_NUM:
            return Data(AST_PRINT_NUM);
        case AST_PRINT_BOOL:
            return Data(AST_PRINT_BOOL);
        case ast_num_op:
            return left;
            case ast_minus:
                return Data(left - right);
            case ast_divide:
                if(right == 0) return Data(0);
                return Data(left / right);
            case ast_mod:
                return Data(left % right);
            case ast_greater:
                return Data(left > right);
            case ast_smaller:
                return Data(left < right);
        case ast_logical_op:
            return left;
            case ast_not:
                return Data(!left);
            // for multiple operation
            case ast_plus:
            case ast_multiply:
            case ast_equal:
            case ast_and:
            case ast_or:
                right.vec_ival.push_back(left.ival);
                right.vec_bval.push_back(left.bval);
                right = numOperation(right, pointer->token_type);
                return right;
            case ast_define_stmt:
                // cout << "define string is: " << (string)left << endl;
                table[(string)left].node = pointer->right;
                // cout << "define var is: " << table[(string)left].node << endl;
                return Data(1);
            case ast_def_variable:
                return left;
            case ast_get_variable:
                if( fun_table.find((string)left) != fun_table.end()) // variable in function table
                    return traverseAST(fun_table[(string)left].node);
                return traverseAST(table[(string)left].node);
            case ast_fun_exp: // right is fun_call
                return right;
            case ast_fun_ids: // function input left: vector<string>
                return left;
            case ast_fun_body:
                return left;
            case ast_fun_call:{
                // left: ast_fun_name(string) or ast_fun_exp(int/bool)
                // r: vector<type>
                if(pointer->left->token_type == ast_fun_name){
                    if(fun_table.find((string)left) == table.end()){
                        cout << "Variable not define!\n";         // error
                        return Data(0);
                    }
                    pointer->left = table[(string)left].node->left;
                }
                vector<string> vec_variables = traverseAST(pointer->left->left);
                vector<type> vec_exp = right;
                for (int i = 0; i < vec_exp.size(); i++)
                {
                    // cout << "vec_variables i is: " <<  vec_variables[i] << endl;
                    fun_table[vec_variables[i]] = vec_exp[i];
                }
                left = traverseAST(pointer->left->right);
                fun_table.clear();
                return left;
            }
            case ast_params:
                right.vec_nval.push_back(left.nval); //left: type right: vector<type>
                return right;
            case ast_param:
                return Data(type{pointer->left->left, NULL}); //left:exp
            case ast_fun_name:
                return left;
            case ast_if_exp:{
            // left: bool   right: Data
                if((bool)left){
                    right = traverseAST(pointer->right->left);
                } 
                else{
                    right = traverseAST(pointer->right->right);
                }
                return right;
            }
            case ast_test_exp:
                return left;
            case ast_if_act_exp:
                return Data(0);
            case ast_then_exp:
                return left;
            case ast_else_exp:
                return left;
            case ast_ids: 
            //left: string  right: vector<string>
                right.vec_sval.push_back(left.sval);
                return right;
            case AST_NUMBER:
                return Data(pointer->indata->ival);
            case AST_BOOL:
                return Data(pointer->indata->bval);
            case AST_ID:
                return Data(pointer->indata->sval);
            case AST_IF:
            case AST_DEFINE:
            case AST_FUN:
                return Data(1);
            default:
                return Data(1);
    }
}  


