#ifndef LEXICON_H
#define LEXICON_H

#include "token.h"
#include <map>
#include <string>

extern std::map<std::string, TokenType> keywordMap;
extern std::map<char, TokenType> singleCharOperatorMap;
extern std::map<char, TokenType> firstDoubleOperatorCharMap;
extern std::map<std::string, TokenType> doubleCharOperatorMap;

extern std::map<TokenType, std::string> tokenToStringMap;
#endif // LEXICON_H