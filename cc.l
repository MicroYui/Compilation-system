%{
#include "cc.tab.h"

extern int error;

void create_node(char* name, char* yytext)
{
    yylval.node = createNode(name, yytext);
}

%}

%option yylineno

INT	    [1-9]+[0-9]*|0
FLOAT	[0-9]+\.[0-9]+|[0-9]+[eE]-?[0-9]+
ID 	    [a-zA-Z_]+[a-zA-Z_0-9]*
RELOP   >|<|>=|<=|==|!=
TYPE    int|float

%%

"//"        {
                char c = input(); 
                while(c!='\n') c=input();
            }
"/*"        {
                char pre = input(), next = input();
	            while (next) 
                {
		            if(pre == '*' && next == '/') break;
                    pre = next;
                    next = input();
	            }
                if (!next) 
                { 
                    printf("Error type B at Line %d: LACK OF */.\n", yylineno);
                    error++;
	            }
            }
[ \t\n\r]+  {}
";"			{create_node("SEMI", yytext); return SEMI;}
","         {create_node("COMMA", yytext); return COMMA;}
"="			{create_node("ASSIGNOP", yytext); return ASSIGNOP;}
{RELOP}     {create_node("RELOP", yytext); return RELOP;}
"+"         {create_node("PLUS", yytext); return PLUS;}
"-"         {create_node("MINUS", yytext); return MINUS;}
"*"         {create_node("STAR", yytext); return STAR;}
"/"         {create_node("DIV", yytext); return DIV;}
"&&"        {create_node("AND", yytext); return AND;}
"||"        {create_node("OR", yytext); return OR;}
"."         {create_node("DOT", yytext); return DOT;}
"!"         {create_node("NOT", yytext); return NOT;}
{TYPE}      {create_node("TYPE", yytext); return TYPE;}
"("         {create_node("LP", yytext); return LP;}
")"         {create_node("RP", yytext); return RP;}
"["         {create_node("LB", yytext); return LB;}
"]"         {create_node("RB", yytext); return RB;}
"{"         {create_node("LC", yytext); return LC;}
"}"         {create_node("RC", yytext); return RC;}
struct      {create_node("STRUCT", yytext); return STRUCT;}
return      {create_node("RETURN", yytext); return RETURN;}
if          {create_node("IF", yytext); return IF;}
else        {create_node("ELSE", yytext); return ELSE;}
while       {create_node("WHILE", yytext); return WHILE;}
{INT}		{create_node("INT", yytext); return INT;}
{FLOAT}		{create_node("FLOAT", yytext); return FLOAT;}
{ID}		{create_node("ID", yytext); return ID;}
.           {
                printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext);
                error++;
            }

%%
