#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ios>

#include "./include/lexicon.h"
#include "./include/token.h"

#include "./include/scanner.h"

#include "./include/treeNode.h"
#include "./include/tree.h"
#include "./include/parser.h"


#include <memory>
#include <stack>






using namespace std;


ifstream inputfilestream;
extern Token nextToken;
extern stack<unique_ptr<Node>> stackOfTrees;
//declare global variable for current node of tree
//initialize to top of stack
unique_ptr<Node> currentNode;



int main (int argc, char *argv[]) {
    

    // Check if the user has provided a file name
    if (argc < 2) {
        cout << "Please provide a file name." << endl;
        return 0;
    }

    
    // Open the file
    inputfilestream.open(argv[1]);
    
    if (!inputfilestream.is_open()) {
        cout << "Unable to open file." << endl;
        return 0;
        
    }

    scanNextToken(); // read the first token into nextToken
    E();
    //initialize current node to top of stack



    
    currentNode = move(stackOfTrees.top());
    printTree(currentNode, 0);
    //printTokenStream();

    inputfilestream.close();


    return 0;
}
