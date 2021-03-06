#ifndef _EXTERN_H
#define _EXTERN_H

#include "treeNode.h"
#include "symbol.h"
#include "semantic.h"
#include "interCode.h"
#include "interCodePrint.h"
#include "assembly.h"
#include <ctype.h>

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

extern Symbol* symbolTable;
extern StructSymbol* structSymbolTable;
extern Symbol* createSymbolTable();
extern Symbol findSymbol(char *name);
extern void insertSymbolTable(char *name);

extern InterCode head;
extern InterCode tail;
extern int labelNum;
extern int tNum;
extern int structNum;
extern int varNum;
#endif