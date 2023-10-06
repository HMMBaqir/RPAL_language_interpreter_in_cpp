
#include "../include/scanner.h"

extern std::ifstream inputfilestream;
extern Token nextToken;




char peek() {
    return inputfilestream.peek();
}
void advance() {
    inputfilestream.get();
    return;
}

bool eof() {
    return peek() == EOF;
}

bool match(char c) {
    if (eof()) return false;
    else if (peek() == c) {
        advance();
        return true;
    }
    else return false;
}


//define function for getting next token that changes global variables for file and line number
void scanNextToken() {
    nextToken.lexeme = "";
    nextToken.value = 0;
    nextToken.type = NONE;

    if (eof()) {
        nextToken.type = END_OF_FILE ;
        return;
    }

    char nextChar = peek();
    
    // find type of token

    if (iswspace(nextChar)) {
        //consume wspaces
        advance();
        scanNextToken();
    }

    else if (isalpha(nextChar)) {
        nextToken.type = ID;
        nextToken.lexeme = "";
        while (!eof() && (isalpha(peek()) | isdigit(peek()))) {
            nextToken.lexeme+= peek();
            advance();
        }
        //check if lexeme is a keyword
        if (keywordMap.find(nextToken.lexeme) != keywordMap.end()) {
            nextToken.type = keywordMap[nextToken.lexeme];
        }
    }

    else if (isdigit(nextChar)) {
        nextToken.type = INT;
        nextToken.lexeme = "";
        while (!eof() && isdigit(peek())) {
            nextToken.lexeme += peek();
            advance();
        }
        //covert string value to integer
        nextToken.value = stoi(nextToken.lexeme);

    } 

    else if (singleCharOperatorMap.find(nextChar) != singleCharOperatorMap.end()) {
        nextToken.type = singleCharOperatorMap[nextChar];
        nextToken.lexeme = nextChar;
        advance();
    }

    else if (firstDoubleOperatorCharMap.find(nextChar) != firstDoubleOperatorCharMap.end()) {
        nextToken.type = firstDoubleOperatorCharMap[nextChar];
        nextToken.lexeme = nextChar;
        advance();
        nextToken.lexeme += peek();
        if (doubleCharOperatorMap.find(nextToken.lexeme) != doubleCharOperatorMap.end()) {
            nextToken.type = doubleCharOperatorMap[nextToken.lexeme];
            advance();
        }
        if (nextToken.type == COMMENT) {
            while (!eof() && peek() != '\n') {
                advance();
            }
            scanNextToken();
        }
    }

    else {
            nextToken.type = ERROR;
            readToken(NONE);
            
    }

    
}

void readToken(TokenType type) {
    if (nextToken.type == type ) {
        std::cout << "Read " << nextToken.lexeme << " " << nextToken.type << std::endl;
        scanNextToken();
    }
    else {
        std::cout << "Error: Expected " << type << " but got " << nextToken.type << std::endl;
        exit(1);
    }
}


void printTokenStream() {
    while (!eof()) {
        scanNextToken();
        std::cout << nextToken.lexeme << " " << nextToken.type << std::endl;
    }
}



