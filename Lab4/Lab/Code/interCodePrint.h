#ifndef __INTERCODEPRINT_H
#define __INTERCODEPRINT_H
#include "interCode.h"
void printSingleCode(FILE *fp, InterCode current);
void printOpSingle(FILE *fp, Operand op);
void printCode(char *outputFileName);
#endif