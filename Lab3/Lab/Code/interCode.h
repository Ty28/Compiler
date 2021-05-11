#ifndef _INTERCODE_H
#define _INTERCODE_H
#include "extern.h"
typedef struct Operand_* Operand;
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
        ASSIGN,
        ADD,
        SUB,
        MUL,
        DIV,
        LABEL,
        GOTO,
        IFGOTO,
        READ,
        WRITE,
        CALL,
        ARG,
        FUNCTION,
        PARAM,
        RETURN,
        DEC,
        ADDRESS
    } kind;
};
#endif