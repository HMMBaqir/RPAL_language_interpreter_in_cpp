#ifndef TREE_H
#define TREE_H


#include "token.h"
#include "treeNode.h"

#include "conversionFunctions.h"


#include <stack>
#include <memory>   
#include <string>

extern std::stack<std::unique_ptr<Node>> stackOfTrees;
extern std::unique_ptr<Node> currentNode;

void buildTree(TokenType type);
void buildTree(TokenType type, int numChildren);
void buildTree(nodeType type, int numChildren);
void printTree(std::unique_ptr<Node> &root, int depth);
#endif // TREE_H