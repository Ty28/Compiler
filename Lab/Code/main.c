#include <stdio.h>
#include "treeNode.h"

extern FILE* yyin;
extern int yylex(void);
extern int yyparse(void);
extern void yyrestart(FILE*);
extern void yyerror(char*);
extern int yylineno;
extern int lexicalError;
extern int syntaxError;
extern node ROOT;

int main(int argc, char** argv) {
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yylineno = 1;
    yyrestart(f);
    yyparse();
    preOrder(ROOT);
    return 0;
}
