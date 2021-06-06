#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H
#include "interCodePrint.h"
#include "assert.h"
#define MEMADDRESSSIZE 0x3fff
#define LI_ 0
#define MOVE_ 1
#define ADDI_ 2
#define ADD_ 3
#define SUB_ 4
#define MUL_ 5
#define DIV_ 6
#define LW_ 7
#define SW_ 8
#define BEQ_ 9
#define BNE_ 10
#define BGT_ 11
#define BLT_ 12
#define BGE_ 13
#define BLE_ 14

int stack_sp;
int stack_fp;
int paramCount;
int used[32]; //to represent whether a register is being used;
char *regName(int registerID, char str[]);
void freeReg();
void printAnnotation(FILE *fp, InterCode current);
typedef struct VarMemAddress_ *VarMemAddress;
struct VarMemAddress_
{
    char name[CHARMAXSIZE];
    int fpOffset;
    VarMemAddress link;
};

int findRegAddress(char *name);
VarMemAddress memAddressTable[0x3fff]; //hash table to store the memory address of the variables
VarMemAddress createMemAddressNode(char *name, int _offset);
VarMemAddress findMemAddress(char *name);
void newMemAddress(char *name, int _offset);

void refreshStackPointer();
void initAssembly();
void loadDataCode(FILE *fp);
void loadTextCode(FILE *fp);
int getIdleReg();
int easyGetRightReg(FILE *fp, Operand op);
int easyGetLeftReg(FILE *fp, Operand op);
void gen(FILE *fp, int codeType, int _arg1, int _arg2, int _arg3);
void assembleFunction(FILE *fp, InterCode current);
void assembleASSIGN(FILE *fp, InterCode current);
void assemBleAdd(FILE *fp, InterCode current);
void assembleDEC(FILE *fp, InterCode current);
void assembleBINARY(FILE *fp, InterCode current);
void assembleIFGOTO(FILE *fp, InterCode current);
void assembleARG(FILE *fp, InterCode current);
void assemblePARAM(FILE *fp, InterCode current);
void assembleCALL(FILE *fp, InterCode current);
void assembleSingleCode(FILE *fp, InterCode current);
void assembleCodes(char *outputFileName);

#endif