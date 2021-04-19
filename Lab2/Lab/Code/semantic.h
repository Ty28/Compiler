#ifndef _SEMANTIC_H
#define _SEMANTIC_H
//#define semanticdebug
#include "symbol.h"

int semanticCheck(node root);
void errorOutput(int errorType, int line, char *msg);
void Program(node root);
void ExtDefList(node root);
void ExtDef(node root);
void ExtDecList(node root, Type extDecType);
void DefList(node root);
void Def(node root);
void DecList(node root, Type decType);
void Dec(node root, Type decType);
void FunDec(node root, Type funcSpecifierType);
void CompSt(node root, Type funcType);
void StmtList(node root, Type funcType);
void Stmt(node root, Type funcType);
int existInFieldList(char* name,FieldList fieldHead);
Type StructVarCopy(Type structureDecType);
FuncList VarList(node root);
FuncList ParamDec(node root);
FieldList StructDecList(node root, Type decType);
FieldList StructDec(node root, Type decType);
FieldList StructDefList(node root);
FieldList StructDef(node root);
Symbol VarDec(node root, Type decType);
FuncList FuncVarDec(node root, Type decType);
FieldList StructVarDec(node root, Type decType);
Type Tag(node root);
Type OptTag(node root);
Type Specifier(node root);
Type StructSpecifier(node root);

Type Exp(node root);

Type ExpFunc(node root);
Type ExpStruct(node root);
Type ExpArray(node root);
int Args(node root, FuncList params);

#endif