#ifndef _INTERCODE_H
#define _INTERCODE_H
#include "symbol.h"
#define FORMALPARAMETERSIZE 0x3fff
//#define InterCodeDebug
typedef struct Operand_ *Operand;
typedef struct InterCode_ *InterCode;
typedef struct argNode_ *argNode;
typedef struct FPTableNode_ *FPTableNode;
typedef struct LabelNode_ *LabelNode;
InterCode head;
InterCode tail;
int labelNum;
int tNum;
int varNum;
int structNum;
struct Operand_
{
    enum
    {
        VARIABLE,
        CONSTANT,
        ADDRESS,
        STAR__,
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
    } u;
};

struct InterCode_
{
    enum
    {
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
        MYIFGOTO
    } kind;
    union
    {
        struct
        {
            Operand op;
        } op_single;

        struct
        {
            Operand left, right;
        } op_assign;

        struct
        {
            Operand result, op1, op2;
            char _operator;
        } op_binary; //REVISE: add _operator to represent +-*/

        struct
        {
            Operand x;
            Operand y;
            Operand label;
            char relop[CHARMAXSIZE];
        } op_triple;

        struct
        {
            Operand op;
            int size;
        } op_dec;
    } u;
    InterCode prev;
    InterCode next;
};

struct argNode_
{
    Operand op;
    argNode next;
};

struct FPTableNode_ //to construct a formal parameter table
{
    char name[CHARMAXSIZE];
    FPTableNode link;
};

struct LabelNode_ {
    char name[CHARMAXSIZE];
    LabelNode link;
};

FPTableNode *FPTable;
FPTableNode *createFPTable();
FPTableNode createFPMember(char *name);
int findFPMember(char *name,int _insert);

void initInterCode(node root);
void insertCode(InterCode code);
void deleteCode(InterCode code);
void newInterCode(int kind, ...);
InterCode createCode();
Operand createOpTmp();
Operand createOpLabel();
Operand copyOpLabel(int num);
Operand createOperand(int kind, ...);
char *int2String(int num, char *str);

// translate InterCode
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

// optimize InterCode
void optimize_mergeLABEL();
void optimize_deleteGOTO();
void optimize_deleteNONEVAR();
LabelNode deleteContinuedLabel(InterCode* q);
LabelNode createLabelNode(char* labelName);
LabelNode createLabelList(InterCode code);
void reverseCodeRELOP(InterCode* q);
// void optimize_deleteCONST();
// InterCode nextInterCode(InterCode code);
// void insteadUnderlineVar() ;
#endif