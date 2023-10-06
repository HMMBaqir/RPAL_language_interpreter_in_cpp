#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ios>

#include "lexicon.h"
#include "token.h"

char peek();
void advance();
bool eof();
bool match(char c);
void scanNextToken();
void printTokenStream();
void readToken(TokenType type);


#endif // SCANNER_H
