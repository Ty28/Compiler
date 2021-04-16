#ifndef _SEMANTIC_H
#define _SEMANTIC_H
#define semanticdebug
#include "symbol.h"

int semanticCheck(node root);
void semLog(char* msg);
void errorOutput(int errorType,int line);
void Program(node root);
void ExtDefList(node root);
void ExtDef(node root);
void ExtDecList(node root,Type extDecType);
void VarDec(node root,Type decType);
void DefList(node root);
void Def(node root);
void DecList(node root,Type decType);
void Dec(node root,Type decType);

Type Tag(node root);
Type Specifier(node root);
Type StructSpecifier(node root);


#endif