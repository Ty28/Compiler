#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#include "symbol.h"

int semanticCheck(node root);
void Program(node root);
void ExtDefList(node root);
void ExtDef(node root);

Type Specifier(node root);
Type StructSpecifier(node root);

#endif