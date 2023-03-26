#include "node.h"

int error = 0;
Node* root = NULL;
int yyrestart();
int yyparse();
extern int yydebug;

void yyerror(char* msg)
{
    if (strcmp(msg, "syntax error") == 0) 
    {
        printf("Error type B at Line %d: %s\n", yylineno,msg);
    }
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    // yydebug = 1;
    yyparse();
    if (error == 0) printTree(root, 0);
    // printf("error: %d\n", error);
    return 0;
}