#include "extern.h"

void printOpSingle(FILE *fp, Operand op)
{
    switch (op->kind)
    {
    case (VARIABLE):
    case (LABEL):
    case (TEMPVAR):
    case (FUNCTION__):
        fprintf(fp, "%s", op->u.value);
        break;
    case (CONSTANT):
    case (COSNTVAR):
        fprintf(fp, "#%d", op->u.var_no);
        break;
    case (ADDRESS):
        fprintf(fp, "&%d", op->u.var_no);
        break;
    case (STAR_):
        fprintf(fp, "*%d", op->u.var_no);
        break;
    case (NOTHING):
        fprintf(fp, "nothing");
        break;
    default:
        fprintf(fp, "we can't process this type:%d", op->kind);
        break;
    }
}

void printCode()
{
    FILE *fp;
    fp = fopen("out.ir", "w+");
    InterCode current = head;
    while (current != NULL)
    {
        switch (current->kind)
        {
        case (MYFUNCTION):
            fprintf(fp, "FUNCTION ");
            printOpSingle(fp,current->u.op_single.op);
            fprintf(fp, " :");
            break;
        case (MYPARAM):
            fprintf(fp, "PARAM ");
            printOpSingle(fp,current->u.op_single.op);
            break;
        case (MYRETURN):
            fprintf(fp, "RETURN ");
            printOpSingle(fp,current->u.op_single.op);
            fprintf(fp, "\n");
            break;
        case (MYLABEL):
            fprintf(fp, "LABEL ");
            printOpSingle(fp,current->u.op_single.op);
            fprintf(fp, " :");
            break;
        case (MYGOTO):
            fprintf(fp, "GOTO ");
            printOpSingle(fp,current->u.op_single.op);
            break;
        //TODO:need to complete MYREAD and MYWRITE
        case (MYREAD):
            fprintf(fp, "READ ");
            printOpSingle(fp,current->u.op_single.op);
            break;
        case (MYWRITE):
            fprintf(fp, "WRITE ");
            printOpSingle(fp,current->u.op_single.op);
            break;
        //TODO:need to complete MYARG
        case (MYARG):
            fprintf(fp, "ARG ");
            printOpSingle(fp,current->u.op_single.op);
            break;
        case (MYASSIGN):
            printOpSingle(fp,current->u.op_assign.left);
            fprintf(fp, " := ");
            printOpSingle(fp,current->u.op_assign.right);
            break;
        case (MYDEC):
            fprintf(fp, "DEC ");
            printOpSingle(fp,current->u.op_dec.op);
            fprintf(fp, " %d", current->u.op_dec.size);
            break;
        //TODO:need to complete MYCALL
        case (MYCALL):
            printOpSingle(fp,current->u.op_assign.left);
            fprintf(fp, " := CALL ");
            printOpSingle(fp,current->u.op_assign.right);
            break;
        case (MYADD):
            printOpSingle(fp,current->u.op_binary.result);
            fprintf(fp, " := ");
            printOpSingle(fp,current->u.op_binary.op1);
            fprintf(fp, " + ");
            printOpSingle(fp,current->u.op_binary.op2);
            break;
        case (MYSUB):
            printOpSingle(fp,current->u.op_binary.result);
            fprintf(fp, " := ");
            printOpSingle(fp,current->u.op_binary.op1);
            fprintf(fp, " - ");
            printOpSingle(fp,current->u.op_binary.op2);
            break;
        case (MYMUL):
            printOpSingle(fp,current->u.op_binary.result);
            fprintf(fp, " := ");
            printOpSingle(fp,current->u.op_binary.op1);
            fprintf(fp, " * ");
            printOpSingle(fp,current->u.op_binary.op2);
            break;
        case (MYDIV):
            printOpSingle(fp,current->u.op_binary.result);
            fprintf(fp, " := ");
            printOpSingle(fp,current->u.op_binary.op1);
            fprintf(fp, " / ");
            printOpSingle(fp,current->u.op_binary.op2);
            break;
            break;
        case (MYIFGOTO):
            fprintf(fp, "IF ");
            printOpSingle(fp,current->u.op_triple.x);
            fprintf(fp, " %s ", current->u.op_triple.relop);
            printOpSingle(fp,current->u.op_triple.y);
            fprintf(fp, " GOTO ");
            printOpSingle(fp,current->u.op_triple.label);
            break;
        //TODO:need to complete MYADDRESS ?
        case (MYADDRESS):
            break;
        default:
            fprintf(fp, "others");
            break;
        }
        fprintf(fp, "\n");
        current = current->next;
    }
}
