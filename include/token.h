

#ifndef TOKEN_H
#define TOKEN_H


#include <string>


enum TokenType {
    NONE,COMMENT,ERROR,END_OF_FILE,
    // Keywords
    LET, IN, FN, WHERE, WITHIN, AND, REC,

    AUG, ASSIGN,
    // Punctuation
    LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE, COLON, SEMICOLON, COMMA, UNDERSCORE, BAR, DOT, DOLLAR,
    // condition boolean
    BOOLAND, COND,  OR, NOT,
    //bool ops
    GR, GE, LS, LE, EQ, NE, 
    // Operators
    NEG,
    POW, PLUS, MINUS, TIMES, DIVIDE, 
    AT,

    // Literals
    INT, STRING, ID, TRUE, FALSE, NIL, DUMMY,

};


//create a map of keywords to token types

//create a struct for tokens declaration
struct Token {
    TokenType type;
    std::string lexeme;
    long int value;
};
extern Token nextToken;

#endif


