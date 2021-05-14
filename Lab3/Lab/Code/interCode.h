#ifndef _INTERCODE_H
#define _INTERCODE_H
typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct argNode_* argNode;
InterCode head;
InterCode tail;
int labelNum;
int tNum;
struct Operand_ {
    enum {
        VARIABLE,
        CONSTANT,
        ADDRESS,
        COSNTVAR,
        TEMPVAR,
        NOTHING,
        LABEL,
        FUNCTION__
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

		struct{ Operand result, op1, op2; char _operator;} op_binary;//REVISE: add _operator to represent +-*/

		struct{ Operand x; Operand y; Operand label; char relop[CHARMAXSIZE]; } op_triple;

		struct{ Operand op; int size; } op_dec;
    } u;
    InterCode prev;
	InterCode next;
};

struct argNode_{
	Operand op;
	argNode next;
};

void initInterCode(node root);
void insertCode(InterCode code);
InterCode createCode();
Operand createOpTmp();
Operand createOpLabel();
Operand copyOpLabel(int num);
char* int2String(int num,char *str);
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
void translateDefList_A(node root);
void translateStmtList(node root);
void translateStmt(node root);
void translateDef_A(node root);
void translateDecList_A(node root);
void translateDec_A(node root);
void translateExp(node root, Operand op);
void translateExpCommon(node root, Operand place);
void translateExpFunc(node root, Operand place);
void translateExpMath(node root, Operand place);
void translateExpArray(node root, Operand place);
void translateCond(node root, int label_true, int label_false);
argNode translateArgs(node root);
#endif