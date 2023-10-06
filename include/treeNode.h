#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <string>
#include <memory>


//define node type
enum nodeType {
    //definition/ scopes
    LET_NODE,WHERE_NODE,WITHIN_NODE,REC_NODE,AND_NODE,

    GAMMA_NODE, LAMBDA_NODE,

    ASSIGN_NODE, COMMA_NODE, FCN_FORM_NODE,

    COND_NODE,

    BOOLAND_NODE, OR_NODE, NOT_NODE,
    GR_NODE,GE_NODE, LS_NODE,LE_NODE , EQ_NODE,NE_NODE,

    NEG_NODE,
    PLUS_NODE, MINUS_NODE, TIMES_NODE, DIVIDE_NODE, POW_NODE,

    AT_NODE,

    ID_NODE, STRING_NODE, INT_NODE, 
    TRUE_NODE, FALSE_NODE, NIL_NODE, DUMMY_NODE,

    EMPTYPAREN_NODE,

    TAU_NODE, AUG_NODE,
    
};


class Node {
public:
    nodeType type;
    std::unique_ptr<Node> firstChild;
    std::unique_ptr<Node> nextSibling;

    std::string strValue;
    long intValue;

    Node(nodeType type)
        : type(type), firstChild(nullptr), nextSibling(nullptr), strValue(""), intValue(0) {}
};
class LiteralNode : public Node {
public:

    std::string strValue;
    long intValue;

    LiteralNode(nodeType type, std::string strValue = "", long intValue = 0)
        : Node(type), strValue(strValue), intValue(intValue) {}

};

class InnerNode : public Node {
public:
    InnerNode(nodeType type)
        : Node(type) {}

};
#endif