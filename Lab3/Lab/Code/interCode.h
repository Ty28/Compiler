#ifndef _INTERCODE_H
#define _INTERCODE_H
#include "treeNode.h"
typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct Label_Node_* Label_Node;
InterCode head;
InterCode tail;
int labelNum;
struct Operand_ {
    enum {
        VARIABLE,
        CONSTANT,
        ADDRESS
    } kind;
    union  
    {
        int var_no;
        char value[CHARMAXSIZE];
        Operand op;
    } u;  
};

struct InterCode_ {
    enum {
        MYFUNCTION,
        MYPARAM,
        MYRETURN,
        MYLABEL,
        MYGOTO,
        MYREAD,
        MYWRITE,
        MYARG,
        MYASSIGN,
        MYDEC,
        MYCALL,
        MYADD,
        MYSUB,
        MYMUL,
        MYDIV,
        MYIFGOTO,
        MYADDRESS
    } kind;
    union {
        struct{ Operand op; } op_single;

        struct{ Operand left, right; } op_assign;

		struct{ Operand result, op1, op2; } op_binary;

		struct{ Operand x; Operand y; Operand label; char relop[CHARMAXSIZE]; } op_triple;

		struct{ Operand op; int size; } op_dec;
    } u;
    InterCode prev;
	InterCode next;
};

struct Label_Node_{
	char name[32];
	Label_Node next;
};

void insertCode(InterCode code);
InterCode createCode();

void translateProgram(node root);
void translateExtDefList(node root);
void translateExtDef(node root);
void translateExtDefList(node root);
void translateFunDec(node root);
void translateCompst(node root);
void translateVarList(node root);
void translateParamDec(node root);
void translateVarDec_A(node root);
void translateVarDec_B(node root);
#endif