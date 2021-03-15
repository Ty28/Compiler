%{
// #define debug
#include "syntax.tab.h"
#include "treeNode.h"
int lexicalError = 0;
int yycolumn = 1;
void debug_log(char *mytext) {
    #ifdef debug    
        // printf("DEBUG LOG: token %s value %s at Line %d\n", mytext, yytext, yylineno);
        printf("%s ",yytext);
    #endif
}
#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

%option yylineno
ws [ \t\r\n]+
digit [0-9]
digits [0-9]+
INT 0|[1-9]{digit}*
FLOAT {digits}\.{digits}
ID [a-zA-Z_][0-9a-zA-Z_]*
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS \+
MINUS -
STAR \*
DIV \/
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE "int"|"float"
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
LINECOMMENT \/\/
BLOCKCOMMENT \/\*
OTHER .
%%
{LINECOMMENT} { 
    char c = input();
    while(c!='\n')
    {
        c = input();
        if(c == '\0')
            break;
    }
        
}
{BLOCKCOMMENT} {
    char pre = input(), cur = input();
    while(pre != '*' || cur != '/') {
        pre = cur;
        cur = input();
        if(cur == '\0') {
            lexicalError += 1;
            printf("Error type A at Line %d: Missing */.\n",yylineno);
            break;
        }
    }
}
{INT} {
    debug_log("INT");
    yylval.type_node = createNode("INT", yytext, yylineno, 1);
    return INT;
}
{FLOAT} {
    debug_log("FLOAT");
    yylval.type_node = createNode("FLOAT", yytext, yylineno, 2);
    return FLOAT;
}
{TYPE} {
    debug_log("TYPE");
    yylval.type_node = createNode("TYPE", yytext, yylineno, 16);
    return TYPE;
}
{STRUCT} {
    debug_log("STRUCT");
    yylval.type_node = createNode("STRUCT", yytext, yylineno, 23);
    return STRUCT;
}
{RETURN} {
    debug_log("RETURN");
    yylval.type_node = createNode("RETURN", yytext, yylineno, 24);
    return RETURN;
}
{IF} {
    debug_log("IF");
    yylval.type_node = createNode("IF", yytext, yylineno, 25);
    return IF;
}
{ELSE} {
    debug_log("ELSE");
    yylval.type_node = createNode("ELSE", yytext, yylineno, 26);
    return ELSE;
}
{WHILE} {
    debug_log("WHILE");
    yylval.type_node = createNode("WHILE", yytext, yylineno, 27);
    return WHILE;
}
{ID} {
    debug_log("ID");
    yylval.type_node = createNode("ID", yytext, yylineno, 3);
    return ID;
}
{SEMI} {
    debug_log("SEMI");
    yylval.type_node = createNode("SEMI", yytext, yylineno, 4);
    return SEMI;
}
{COMMA} {
    debug_log("COMMA");
    yylval.type_node = createNode("COMMA", yytext, yylineno, 5);
    return COMMA;
}
{ASSIGNOP} {
    debug_log("ASSIGNOP");
    yylval.type_node = createNode("ASSIGNOP", yytext, yylineno, 6);
    return ASSIGNOP;
}
{RELOP} {
    debug_log("RELOP");
    yylval.type_node = createNode("RELOP", yytext, yylineno, 7);
    return RELOP;
}
{PLUS} {
    debug_log("PLUS");
    yylval.type_node = createNode("PLUS", yytext, yylineno, 8);
    return PLUS;
}
{MINUS} {
    debug_log("MINUS");
    yylval.type_node = createNode("MINUS", yytext, yylineno, 9);
    return MINUS;
}
{STAR} {
    debug_log("STAR");
    yylval.type_node = createNode("STAR", yytext, yylineno, 10);
    return STAR;
}
{DIV} {
    debug_log("DIV");
    yylval.type_node = createNode("DIV", yytext, yylineno, 11);
    return DIV;
}
{AND} {
    debug_log("AND");
    yylval.type_node = createNode("AND", yytext, yylineno, 12);
    return AND;
}
{OR} {
    debug_log("OR");
    yylval.type_node = createNode("OR", yytext, yylineno, 13);
    return OR;
}
{DOT} {
    debug_log("DOT");
    yylval.type_node = createNode("DOT", yytext, yylineno, 14);
    return DOT;
}
{NOT} {
    debug_log("NOT");
    yylval.type_node = createNode("NOT", yytext, yylineno, 15);
    return NOT;
}
{LP} {
    debug_log("LP");
    yylval.type_node = createNode("LP", yytext, yylineno, 17);
    return LP;
}
{RP} {
    debug_log("RP");
    yylval.type_node = createNode("RP", yytext, yylineno, 18);
    return RP;
}
{LB} {
    debug_log("LB");
    yylval.type_node = createNode("LB", yytext, yylineno, 19);
    return LB;
}
{RB} {
    debug_log("RB");
    yylval.type_node = createNode("RB", yytext, yylineno, 20);
    return RB;
}
{LC} {
    debug_log("LC");
    yylval.type_node = createNode("LC", yytext, yylineno, 21);
    return LC;
}
{RC} {
    debug_log("RC");
    yylval.type_node = createNode("RC", yytext, yylineno, 22);
    return RC;
}
\n {
    yycolumn = 1;
}
{ws} {
    
}
{OTHER} {
    lexicalError += 1;
    printf("Error type A at Line %d: Mysterious character \'%s'.\n",yylineno,yytext);
}
%%
// int main(int argc, char** argv) {
//     if(argc > 1) {
//         if(!(yyin = fopen(argv[1], "r"))) {
//             perror(argv[1]);
//             return 1;
//         }
//     }
//     while(yylex() != 0);
//     printf("Lexical Error : %d", lexicalError);
//     return 0;
// }