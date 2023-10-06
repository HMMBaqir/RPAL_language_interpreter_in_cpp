#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "treeNode.h"
#include "tree.h"

#include <stack>
#include <functional>
#include <unordered_map>
#include <memory>



extern Token nextToken;
extern std::unordered_map<TokenType, std::function<void()>> buildTreeMap;
extern std::stack<std::unique_ptr<Node>> stackOfTrees;

enum procedureType {
    EXP,            //expression
    EXP_WHERE,      //expression with where
    TUP_EXP,        // tuple expression handles tuples
    
    TUP_AUG,        // tuple expression with aug
    TUP_COND,       // tuple expression with cond
    
    BOOL_EXP,       // boolean expression handles bool or
    BOOL_TERM,      //handles bool and
    BOOL_FACTOR,    //handles bool not
    BOOL_PRIMARY,   //handles bool comparators
    
    ARITH_EXP,      //arithmetic expression handles + and -
    ARITH_TERM,     //arithmetic term handles * and /
    ARITH_FACTOR,   //arithmetic factor handles unary + and -
    ARITH_POWER,    //arithmetic power handles ^
    ARITH_PRIMARY,  //arithmetic primary handles @
    
    RATOR_AND_RAND, //handles and operators and operands for function application
    RAND,           //handles operands for function application
    
    //definition types
    DEF,           //handles definitions with within
    DEF_AND,       //handles simultaneous definitions

    //function definitions
    DEF_REC,       //handles recursive definitions of functions
    DEF_FORM,      //handles function definitions

    //L value identifiers
    VAR_BIND,      //handles variables / identifiers in parenthesis or empty line
    VAR_LIST,      //handles lists of variables / identifiers or operands

};



void E();
void Ew();
void T();
void Ta();
void Tc();
void B();
void Bt();
void Bs();
void Bp();
void A();
void At();
void Af();
void Ap();
void R();
void Rn();
void D();
void Da();
void Dr();
void Db();
void Vb();
void Vl();

#endif // PARSER_H