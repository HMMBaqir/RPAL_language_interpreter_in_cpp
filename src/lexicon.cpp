
#include "../include/lexicon.h"


std::map<std::string, TokenType> keywordMap = {
    {"let", TokenType::LET},
    {"in", TokenType::IN},

    {"where", TokenType::WHERE},
    {"within", TokenType::WITHIN},
    {"and", TokenType::AND},

    {"fn", TokenType::FN},
    {"rec", TokenType::REC},


    {"or", TokenType::OR},
    {"not", TokenType::NOT},

    {"gr", TokenType::GR},
    {"ge", TokenType::GE},
    {"ls", TokenType::LS},
    {"le", TokenType::LE},

    {"eq", TokenType::EQ},
    {"ne", TokenType::NE},

    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},

    {"aug", TokenType::AUG},
    {"nil", TokenType::NIL},

    {"dummy", TokenType::DUMMY},
};

std::map<char, TokenType> singleCharOperatorMap = {
    {'(', TokenType::LPAREN},
    {')', TokenType::RPAREN},
    {'[', TokenType::LBRACK},
    {']', TokenType::RBRACK},
    {'{', TokenType::LBRACE},
    {'}', TokenType::RBRACE},
    {':', TokenType::COLON},
    {';', TokenType::SEMICOLON},
    {',', TokenType::COMMA},
    {'_', TokenType::UNDERSCORE},
    {'|', TokenType::BAR},
    {'.', TokenType::DOT},
    {'$', TokenType::DOLLAR},
    {'+', TokenType::PLUS},


    {'@', TokenType::AT},

    {'&', TokenType::BOOLAND},

};



std::map<char, TokenType> firstDoubleOperatorCharMap = {
    //first chars 
    {'*', TokenType::TIMES},
    {'-', TokenType::MINUS},
    {'/', TokenType::DIVIDE},
    {'<', TokenType::LS},
    {'>', TokenType::GR},
    {'=', TokenType::ASSIGN},
    {'!', TokenType::NOT},
   
};

std::map<std::string, TokenType> doubleCharOperatorMap = {
    //second chars
    {"**", TokenType::POW},
    {"->", TokenType::COND},
    {"<=", TokenType::LE},
    {">=", TokenType::GE},
    {"==", TokenType::EQ},
    {"!=", TokenType::NE},
    {"//", TokenType::COMMENT},
};

std::map<TokenType, std::string> tokenToStringMap = {
    {TokenType::COMMA, "COMMA"},
    {TokenType::LPAREN, "LPAREN"},
    {TokenType::RPAREN, "RPAREN"},
    {TokenType::LBRACE, "LBRACE"},
    {TokenType::RBRACE, "RBRACE"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::ASSIGN, "ASSIGN"},
    {TokenType::EQ, "EQ"},
    {TokenType::NE, "NE"},
    {TokenType::LE, "LE"},
    {TokenType::GE, "GE"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::TIMES, "TIMES"},
    {TokenType::DIVIDE, "DIVIDE"},
    {TokenType::AND, "AND"},
    {TokenType::OR, "OR"},
    {TokenType::NOT, "NOT"},
    {TokenType::GR, "GR"},
    {TokenType::NE, "NE"},
    {TokenType::LS, "LS"},
    {TokenType::LE, "LE"},
    {TokenType::AT, "AT"},
    {TokenType::POW, "POW"},
    {TokenType::BOOLAND, "BOOLAND"},
    {TokenType::COND, "COND"},

    {TokenType::NEG, "NEG"},
    {TokenType::LET, "LET"},
    {TokenType::IN, "IN"},
    {TokenType::FN, "FN"},
    {TokenType::WHERE, "WHERE"},
    {TokenType::AUG, "AUG"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::NIL, "NIL"},
    {TokenType::DUMMY, "DUMMY"},
    {TokenType::WITHIN, "WITHIN"},
    {TokenType::REC, "REC"},
};


