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
        printf("we can't process this type:NOTHING");
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
            printf("READ ");
            printOpSingle(current->u.op_single.op);
            break;
        case (MYWRITE):
            printf("WRITE ");
            printOpSingle(current->u.op_single.op);
            break;
        //TODO:need to complete MYARG
        case (MYARG):
            printf("ARG ");
            printOpSingle(current->u.op_single.op);
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
            printOpSingle(current->u.op_assign.left);
            printf(" := CALL ");
            printOpSingle(current->u.op_assign.right);
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
        case (MYIFGOTO):
            printf("IF ");
            printOpSingle(current->u.op_triple.x);
            printf(" %s ", current->u.op_triple.relop);
            printOpSingle(current->u.op_triple.y);
            printf(" GOTO ");
            printOpSingle(current->u.op_triple.label);
            break;
        //TODO:need to complete MYADDRESS ?
        case (MYADDRESS):
            break;
        default:
            printf("others");
            break;
        }
        printf("\n");
        current = current->next;
    }
}
