
#include "../include/parser.h"

extern Token nextToken;

// Define the global function map


using namespace std;
// create a map of functions that simply give the name of function to call based on the token type if multiple functions give an array of functions

/*
unordered_map<TokenType, function<void()>> binaryFunctionMap = {
    {PLUS, At},
    {MINUS, At},
    {TIMES, Af},
    {DIVIDE, Af},
    {GR, Bt},
    {GREATER, Bt},
    {GE, Bt},
    {LS, Bt},
    {LE, Bt},
    {EQ, Bt},
    {NE, Bt}
};

// Define the binaryOp() function that uses the global function map
void binaryOp(TokenType opType) {
    readToken(opType);
    binaryFunctionMap.at(opType)();
    buildTree(opType, 2);
}
*/
//declare all functions




// v1 procedure for reading identifiers

void Vl() {
    buildTree(ID_NODE, 0);
    readToken(ID);

    int numIdentifiers = 1;
    while (nextToken.type == COMMA) {
        readToken(COMMA);
        numIdentifiers += 1;
        buildTree(ID_NODE, 0);
        readToken(ID);
    }

    if (numIdentifiers > 1) {
        buildTree(COMMA_NODE, numIdentifiers);
    }
}
// variable ?
void Vb() {
    switch (nextToken.type) {
        case LPAREN:
            readToken(LPAREN);
            switch (nextToken.type) {
                case ID:
                    Vl();
                    break;
                case RPAREN:
                    buildTree(EMPTYPAREN_NODE, 0);
                    break;

            }
            readToken(RPAREN);
            break;
        case ID:
            buildTree(ID_NODE, 0);
            readToken(ID);
            break;
    }
}
//declaration of function?
void Db() {
    switch (nextToken.type) {
        case LPAREN:
            readToken(LPAREN);
            D();
            readToken(RPAREN);
            break;
        case ID:
            buildTree(ID_NODE, 0);
            readToken(ID);
            switch (nextToken.type) {
                case COMMA:
                    readToken(COMMA);
                    Vl();
                    readToken(ASSIGN);
                    E();
                    buildTree(ASSIGN_NODE, 2);
                    break;
                case ASSIGN:
                    readToken(ASSIGN);
                    E();
                    buildTree(ASSIGN_NODE, 2);
                    break;
                default:
                    int n = 1;
                    while (nextToken.type == ID || nextToken.type == LPAREN) {
                        Vb();
                        n++;
                    }
                    readToken(ASSIGN);
                    E();
                    buildTree(FCN_FORM_NODE, n + 1);
                    break;
            }
            break;
    }
}
// declaration of functions (wrapper to see if function is recursive or not)

void Dr() {
    if (nextToken.type == REC) {
        readToken(REC);
        Db();
        buildTree(REC_NODE, 1);

    } else {

        Db();

    }
}

 // Declaration of and for and keyword (multiple declarations)
void Da() {
    
    Dr();
    int n = 1;

    while (nextToken.type == AND) {
        readToken(AND);
        Dr();
        n++;
    }
    if (n > 1) {
        buildTree(AND_NODE, n);
    }

}
// declaration of functions checks for within keyword
void D() {
    Da();
    if (nextToken.type == WITHIN) {
        readToken(WITHIN);
        Dr();
        buildTree(WITHIN_NODE, 2);
    }
}
//rn means opearand of function application
void Rn() {
    switch (nextToken.type) {
        case ID:
        case STRING:
        case INT:
        case TRUE:
        case FALSE:
        case NIL:
        case DUMMY:
            buildTree(nextToken.type);
            readToken(nextToken.type);
            break;
        case LPAREN:
            readToken(LPAREN);
            E();
            readToken(RPAREN);
            break;
        default:
            // Handle unexpected token type
            break;
    }
}

// function application 
void R() {
    Rn();
    while (true) {
        switch (nextToken.type) {
            // if any of the following is satisfied then Rn will execute
            case ID:
            case INT:
            case STRING:
            case TRUE:
            case FALSE:
            case NIL:
            case DUMMY:
            case LPAREN:
                Rn();
                buildTree(GAMMA_NODE, 2);
                break;

            default:
                return;
        }
    }
}

// operators below
// function application wrapper checks for @ operator
void Ap() {
    R();
    while (nextToken.type == AT) {
        readToken(AT);
        buildTree(AT_NODE, 2);
        R();
    }
}
// checks for exponent operator
void Af() {
    Ap();
    if (nextToken.type == POW) {
        readToken(POW);
        Af();
        buildTree(POW_NODE, 2);
    }
}
// checks for multiplication and division operators
void At() {
    Af();
    while (nextToken.type == TIMES || nextToken.type == DIVIDE) {
        if (nextToken.type == TIMES) {
            readToken(TIMES);
            Af();
            buildTree(TIMES_NODE, 2);
        } else if (nextToken.type == DIVIDE) {
            readToken(DIVIDE);
            Af();
            buildTree(DIVIDE_NODE, 2);
        }
    }
}

// handle addition and subtraction operators
/*A -> A ’+’ At => ’+’
-> A ’-’ At => ’-’
-> ’+’ At
-> ’-’At =>’neg’*/

void A() {
    // the first value can be + or - so we check if - then neg if + ignore it

    if (nextToken.type == PLUS) {
        readToken(PLUS);
        At();
    } else if (nextToken.type == MINUS) {
        readToken(MINUS);
        At();
        buildTree(NEG_NODE, 1);
    } else {
        At();
    }

    while (nextToken.type == PLUS || nextToken.type == MINUS) {
        
        if (nextToken.type == PLUS) {
            readToken(PLUS);
            At();
            buildTree(PLUS_NODE, 2);
        } else if (nextToken.type == MINUS) {
            readToken(MINUS);
            At();
            buildTree(MINUS_NODE, 2);
        }
    }
}

//procedures to handle comparison operators
void Bp() {
    A();
    TokenType memoTokenType = nextToken.type;
    switch (nextToken.type) {
        case GR:
        
        case GE:
         
        case LS:
      
        case LE:
      
        case EQ:

        case NE:
            readToken(nextToken.type);
            A();
            buildTree(memoTokenType, 2);            
            break;

        default:
            break;
    }
}

void Bs() {
    if (nextToken.type == NOT) {
        readToken(NOT);
        Bp();
        buildTree(NOT_NODE, 1);
    } else {
        Bp();
    }
}
// handles & operator n is number of booleans connected by & operator
void Bt() {
    Bs();
    int n = 1;
    while (nextToken.type == BOOLAND) {
        readToken(BOOLAND);
        Bs();
        n++;
    }
    if (n > 1) {
        buildTree(BOOLAND_NODE, n);
    }
}

void B() {
    Bt();
    int n = 1;
    while (nextToken.type == OR) {
        readToken(OR);
        Bt();
        n++;
    }
    if (n > 1) {
        buildTree(OR_NODE, n);
    }
    
}

void Tc() {
    B();
    if (nextToken.type == COND) {
        readToken(COND);
        Tc();
        readToken(BAR);
        Tc();
        buildTree(COND_NODE, 3);
    }
}

void Ta() {
    Tc();
    while (nextToken.type == AUG) {
        readToken(AUG);
        Tc();
        buildTree(AUG_NODE, 2);
    }
}

void T() {
    Ta();
    int n = 1;
    while (nextToken.type == COMMA) {
        n++;
        readToken(COMMA);
        Ta();
    }
    if (n > 1) {
        buildTree(TAU_NODE, n);
    }
}

void Ew() {
    T();
    if (nextToken.type == WHERE) {
        readToken(WHERE);
        Dr();
        buildTree(WHERE_NODE, 2);
    }
}

void E() {
    int N = 0;
    switch (nextToken.type) {
        case LET:
            readToken(LET);
            D();
            readToken(IN);
            E();
            buildTree(LET_NODE, 2);
            break;
            
        case FN:
            readToken(FN);
            do {
                Vb();
                N++;
            } while (nextToken.type == ID || nextToken.type == LPAREN);
            readToken(DOT);
            E();
            buildTree(LAMBDA_NODE, N + 1);
            break;
        default:
            Ew();
            break;
    }
}


