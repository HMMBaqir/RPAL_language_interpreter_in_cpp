#include "../include/tree.h"

std::stack<std::unique_ptr<Node>> stackOfTrees = std::stack<std::unique_ptr<Node>>();

std::unique_ptr<Node> newNode = std::unique_ptr<Node>(new Node(NONE));

void buildTree(TokenType parentNodeType, const int noOfChildren)
{
    std::unique_ptr<Node> parentTreeNode(new Node(parentNodeType));

    parentTreeNode->type = parentNodeType;

    if (parentNodeType == ID || parentNodeType == INT || parentNodeType == STRING)
    {
        parentTreeNode->strValue = nextToken.lexeme;
        parentTreeNode->intValue = nextToken.value;
    }
    else
    {
        parentTreeNode->strValue = "";
        parentTreeNode->intValue = 0;
    }
    // we know parents and children no info about sibling of parent hence it is nullptr

    parentTreeNode->nextSibling = nullptr;
    parentTreeNode->firstChild = nullptr;

    if (noOfChildren == 0)
    {
        stackOfTrees.push(std::move(parentTreeNode));
        return;
    }

    if (noOfChildren > 0 && stackOfTrees.empty())
    {
        exit(EXIT_FAILURE);
    }

    std::unique_ptr<Node> childTreeNode = std::move(stackOfTrees.top());
    stackOfTrees.pop();

    for (int i = 1; i < noOfChildren && !stackOfTrees.empty(); i++)
    {
        stackOfTrees.top()->nextSibling = std::move(childTreeNode);
        childTreeNode = std::move(stackOfTrees.top());
        stackOfTrees.pop();
    }

    parentTreeNode->firstChild = std::move(childTreeNode);
    stackOfTrees.push(std::move(parentTreeNode));
}

void printTree(std::unique_ptr<Node> &tree, int level)
{

    if (tree == nullptr)
    {
        return;
    }
    for (int i = 0; i < level; i++)
    {
        std::cout << " . ";
    }
    std::cout << tokenToString(tree->type) << " ";
    if (tree->type == ID || tree->type == INT || tree->type == STRING)
    {
        std::cout << tree->strValue << std::endl;
    }
    else
    {
        std::cout << std::endl;
    }
    printTree(tree->firstChild, level + 1);
    printTree(tree->nextSibling, level);
}
// declare global variable for current node
// initialize to top of stack

// define STD_LAMBDA
// define make lambda which makes global newnode a lambda

void MakeNewNode(TokenType type)
{
    // reset the new node
    newNode.reset(new Node(type));
}

void swapPointers(std::unique_ptr<Node> &Node1, std::unique_ptr<Node> &Node2)
{
    std::unique_ptr<Node> temp = std::move(Node1);
    Node1 = std::move(Node2);
    Node2 = std::move(temp);
}

void STD_LAMBDA(std::unique_ptr<Node> &Node)
{
    // make a new node for the left child
    /*  *OP ->  E   =>  *LAMBDA ->E
                            v
                            OP
    */
    if (Node->nextSibling == nullptr)
    {
        return;
    }

    Node->type = LAMBDA; // make the current node a lambda

    MakeNewNode(ID);
    newNode->strValue = Node->strValue;
    newNode->intValue = Node->intValue;

    // so above we have essentially made a lambda and swapped it with operand
    Node->firstChild = std::move(newNode);

    STD_LAMBDA(Node->nextSibling);
}
void standardizeTree()
{
    // i think you can make this function STD_GAMMA that takes a node and standardizes it

    if (currentNode == nullptr)
    {
        return;
    }
    std::unique_ptr<Node> newNode = std::unique_ptr<Node>(new Node(NONE));

    std::unique_ptr<Node> childNode = std::move(currentNode->firstChild);

    switch (currentNode->type)
    {
    case ID:
    case INT:
    case STRING:
        // Do not standardize leaf nodes
        break;

    case FCN_FORM:
        // Convert function form to standardized form
        /*fcn_form                                assign
            v                           =>           v
            f_name -> op -> op -> E                   f_name -> lambda -> lambda -> E
                                                                v         v
                                                                op        op
        */
        // convert current node to assign
        currentNode->type = ASSIGN;

        // make current the op node
        currentNode = std::move(childNode->nextSibling);

        STD_LAMBDA();
        // make the first child of the new node the child node
        newNode->firstChild = std::move(childNode->nextSibling);
        // so we have to change the child nodes sibling to newnode
        childNode->nextSibling = std::move(newNode);
        break;

    case COMMA:
        // if cur node has no sibling then just make current node the first child of parent node
        if (childNode->nextSibling == nullptr)
        {
            // restore the parent node and return
            currentNode = std::move(childNode);
            break;
        }
        // make new lambda node
        newNode.reset(new Node(LAMBDA));
        // make the first child of the new node the current node
        newNode->firstChild = std::move(childNode);

        childNode = std::move(newNode);

        break;

    case AT:
        // infix @
        // convert to gamma
        currentNode->type = GAMMA;
        // make a new node for the left child
        newNode.reset(new Node(GAMMA));
        // get the first child of new node using getNthSibling
        newNode->firstChild = std::move(getNthSibling(childNode, 1));
        // get the second child of new node is current node
        newNode->firstChild->nextSibling = std::move(childNode);
        // get the sibling of new node is 2nd sibling of current node
        newNode->nextSibling = std::move(getNthSibling(childNode, 2));
        // current node has no kids or siblings

        childNode->firstChild = nullptr;
        childNode->nextSibling = nullptr;

        // make current node the new node

        childNode = std::move(newNode);

        // sibling of the current node is the 2nd sibling of current nodes first child

    case LET:

        // Convert let expression to standardized form

        break;

    case TAU:
        break;

    case COND:
        break;

    default:
        break;
    }

    currentNode->firstChild = std::move(childNode);
}