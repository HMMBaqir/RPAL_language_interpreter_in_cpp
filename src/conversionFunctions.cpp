#include "../include/conversionFunctions.h"


//declare functions
//get nth sibling recursively
std::unique_ptr<Node> getNthSibling(std::unique_ptr<Node>& currentNode, int n) {
    if (n == 0 || currentNode == nullptr) {
        return nullptr;
    }
    else {
        return getNthSibling(currentNode->nextSibling, n - 1);
    }
}



