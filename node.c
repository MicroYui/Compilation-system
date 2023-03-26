#include "node.h"

Node* createNode(char* name, char* yytext)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->nodeName = (char*)malloc(sizeof(*name));
    strcpy(node->nodeName, name);
    // printf("nodeName: %s, yytext: %s\n", name, yytext);
    node->yytext = (char*)malloc(sizeof(*yytext));
    strcpy(node->yytext,yytext);
    node->lineNumber = yylineno;
    // printf("nodeName: %s, lineNumber: %d\n", name, yylineno);
    node->childNumber = 0;
    node->firstChild = NULL;
    node->nextBrother = NULL;
}

void addNode(Node* parent, int childNumber, ...)
{
    va_list ap;
    va_start(ap, childNumber);
    parent->childNumber = childNumber;
    Node* firstChild = NULL;
    Node* lastNode = NULL;
    // printf("parent: %s\n", parent->nodeName);
    // printf("childNumber: %d\n", childNumber);
    for (int i = 0; i < childNumber; i++)
    {
        Node* curNode = va_arg(ap, Node*);
        if (firstChild == NULL)
        {
            if (curNode != NULL)
            {
                firstChild = curNode;
                lastNode = firstChild;
            }
        }
        else
        {
            if (curNode != NULL) 
            {
                lastNode->nextBrother = curNode;
                lastNode = curNode;
            }
        }
    }
    parent->firstChild = firstChild;
    parent->lineNumber = parent->firstChild->lineNumber;
    va_end(ap);
}

void printTree(Node *root, int number)
{
    if (root == NULL) return;
    for (int i = 0; i < number; i++) printf(" ");
    //printf("childNumber: %d\n", root->childNumber);
    if (root->childNumber != 0)
    {
        printf("%s (%d)\n", root->nodeName, root->lineNumber);
        Node* firstChild = NULL;
        Node* curNode = NULL;
        for (int i = 0; i < root->childNumber; i++) 
        {
            if (firstChild == NULL) 
            {
                firstChild = root->firstChild;
                printTree(firstChild, number+2);
                curNode = firstChild;
            }
            else
            {
                curNode = curNode->nextBrother;
                printTree(curNode, number+2);
            }
        }
    }
    else
    {
        if (strcmp("ID", root->nodeName) == 0) printf("%s: %s\n", root->nodeName, root->yytext);
        else if (strcmp("TYPE", root->nodeName) == 0) printf("%s: %s\n", root->nodeName, root->yytext);
        else if (strcmp("INT", root->nodeName) == 0) printf("%s: %d\n", root->nodeName, atoi(root->yytext));
        else if (strcmp("FLOAT", root->nodeName) == 0) printf("%s: %f\n", root->nodeName, atof(root->yytext));
        else printf("%s\n", root->nodeName);
    }
}
