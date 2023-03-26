#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"

extern int yylineno;

enum NodeType {Vn, VtNVal, VtVal};

typedef struct Node
{
    char* nodeName;
    char* yytext;
    struct Node* firstChild;
    struct Node* nextBrother;
    int lineNumber;
    int childNumber;
}Node;

Node* createNode(char* name, char* yytext);

void addNode(Node* parent, int childNumber, ...);

void printTree(Node* root, int number);
