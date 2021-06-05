#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H
#include "interCode.h"
#include "assert.h"
#define MEMADDRESSSIZE 0x3fff

int stack_sp;
int stack_fp;
int used[32]; //to represent whether a register is being used;
char *regName(int registerID);
typedef struct VarMemAddress_ *VarMemAddress;
struct VarMemAddress_
{
    char name[CHARMAXSIZE];
    int fpOffset;
    VarMemAddress link;
};

VarMemAddress memAddressTable[0x3fff]; //hash table to store the memory address of the variables

VarMemAddress createMemAddressNode(char *name, int _offset);
VarMemAddress findMemAddress(char *name);
void newMemAddress(char *name, int _offset);

void initAssembly();
void loadDataCode(FILE *fp);
void loadTextCode(FILE *fp);
int getIdleReg();
int easyGetRightReg(FILE *fp, Operand op);
int easyGetLeftReg(FILE *fp, Operand op);
void assembleASSIGN(FILE *fp, InterCode current);
void assembleIFGOTO(FILE *fp, InterCode current);
void assembleSingleCode(FILE *fp, InterCode current);
void assembleCodes(char *outputFileName);

#endif