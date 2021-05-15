#ifndef __INTERCODEPRINT_H
#define __INTERCODEPRINT_H
#include "interCode.h"
void printOpSingle(FILE *fp, Operand op);
void printOpAssign(Operand left, Operand right);
void printOpBinary(Operand result, Operand left, Operand right);
void printOpTriple(Operand x, Operand y, Operand laebl, char *relop);
void printCode();
#endif