#ifndef _EXTERN_H
#define _EXTERN_H

#include "treeNode.h"

extern int yylex(void);
extern int yyparse(void);
extern void yyrestart(FILE*);
extern void yyerror(char*);
extern void my_yyerror(char*);
extern int yylineno;
extern node ROOT;
extern int lexicalError;
extern int syntaxError;
extern int preErrorLine;
#endif