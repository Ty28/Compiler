#include "extern.h"

void printOpSingle(Operand op)
{
    switch (op->kind)
    {
    case (VARIABLE):
    case (LABEL):
    case (TEMPVAR):
        printf("%s", op->u.value);
        break;
    case (CONSTANT):
    case (COSNTVAR):
        printf("#%d", op->u.var_no);
        break;
    default:
        printf("we can't process this type");
        break;
    }
}


void printCode()
{
    InterCode current = head;
    while (current != NULL)
    {
        switch (current->kind)
        {
        case (MYFUNCTION):
            printf("FUNCTION ");
            printOpSingle(current->u.op_single.op);
            printf(" :");
            break;
        case (MYPARAM):
            printf("PARAM ");
            printOpSingle(current->u.op_single.op);
            break;
        case (MYRETURN):
            printf("RETURN ");
            printOpSingle(current->u.op_single.op);
            printf("\n");
            break;
        case (MYLABEL):
            printf("LABEL ");
            printOpSingle(current->u.op_single.op);
            printf(" :");
            break;
        case (MYGOTO):
            printf("GOTO ");
            printOpSingle(current->u.op_single.op);
            break;
        //TODO:need to complete MYREAD and MYWRITE
        case (MYREAD):
            break;
        case (MYWRITE):
            break;
        //TODO:need to complete MYARG
        case (MYARG):
            break;
        case (MYASSIGN):
            printOpSingle(current->u.op_assign.left);
            printf(" := ");
            printOpSingle(current->u.op_assign.right);
            break;
        case (MYDEC):
            printf("DEC ");
            printOpSingle(current->u.op_dec.op);
            printf(" %d", current->u.op_dec.size);
            break;
        //TODO:need to complete MYCALL
        case (MYCALL):
            break;
        case (MYADD):
        case (MYSUB):
        case (MYMUL):
        case (MYDIV):
            printOpSingle(current->u.op_binary.result);
            printf(" := ");
            printOpSingle(current->u.op_binary.op1);
            printf(" %c ", current->u.op_binary._operator);
            printOpSingle(current->u.op_binary.op2);
            break;
        default:
            printf("others");
        }
        printf("\n");
        current = current->next;
    }
}