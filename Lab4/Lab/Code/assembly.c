#include "assembly.h"

VarMemAddress createMemAddressNode(char *name, int _offset)
{
    VarMemAddress newNode = (VarMemAddress)malloc(sizeof(struct VarMemAddress_));
    strcpy(newNode->name, name);
    newNode->fpOffset = _offset;
    return newNode;
}

VarMemAddress findMemAddress(char *name)
{
    //codeLog("start find Address");
    unsigned int hashID = hashProject(name, MEMADDRESSSIZE);
    VarMemAddress current = memAddressTable[hashID];
    if (current == NULL)
    {
        return NULL; //if this variable doesn't exist, return NULL
    }
    else
    {
        while (current != NULL)
        {
            if (strcmp(current->name, name) == 0) //loop until we find that name
                return current;                   //NOTE: this function return the node, not offset
            current = current->link;
        }
        return NULL;
    }
}

void newMemAddress(char *name, int _offset)
{
    // codeLog("start insert Address");
    unsigned int hashID = hashProject(name, MEMADDRESSSIZE);
    VarMemAddress current = memAddressTable[hashID];
    if (current == NULL)
    {
        memAddressTable[hashID] = createMemAddressNode(name, _offset);
    }
    else
    {
        while (current->link != NULL)
        {
            // if (strcmp(current->name, name) == 0)
            // {
            //     current->fpOffset = _offset;
            //     return;
            // }
            current = current->link;
        }
        current->link = createMemAddressNode(name, _offset);
    }
}

void initAssembly()
{
    stack_sp = 10000;
    stack_fp = 10000;
    for (int i = 0; i < 32; i++)
        used[i] = 0;
    for (int i = 0; i < MEMADDRESSSIZE; i++)
        memAddressTable[i] = NULL;
}

char *regName(int registerID)
{
    char *str;
    str=(char*)malloc(10);
    switch (registerID)
    {
    case 0:
        strcpy(str, "$zero");
        return str;
    case 1:
        strcpy(str, "$at");
        return str;
    case 2 ... 3:
        strcpy(str, "$v0");
        str[2] += registerID - 2;
        return str;
    case 4 ... 7:
        strcpy(str, "$a0");
        str[2] += registerID - 4;
        return str;
    case 8 ... 15:
        strcpy(str, "$t0");
        str[2] += registerID - 8;
        return str;
    case 16 ... 23:
        strcpy(str, "$s0");
        str[2] += registerID - 16;
        return str;
    case 24 ... 25:
        strcpy(str, "$t0");
        str[2] += registerID - 16;
        return str;
    case 26 ... 27:
        strcpy(str, "$k0");
        str[2] += registerID - 26;
        return str;
    case 28:
        strcpy(str, "$gp");
        return str;
    case 29:
        strcpy(str, "$sp");
        return str;
    case 30:
        strcpy(str, "$fp");
        return str;
    case 31:
        strcpy(str, "$ra");
        return str;
    }
}

void loadDataCode(FILE *fp)
{
    //this function load .data to our output assembly file

    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
}

void loadTextCode(FILE *fp)
{
    //this function load .text, read, and write to our output assembly file

    fprintf(fp, ".text\n");
    //print read
    fprintf(fp, "read:\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _prompt\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 5\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  jr $ra\n");
    fprintf(fp, "  \n");
    //print write
    fprintf(fp, "write:\n");
    fprintf(fp, "  li $v0, 1\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _ret\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  move $v0, $0\n");
    fprintf(fp, "  jr $ra\n");
}

int getIdleReg()
{
    //just select a idle register from $t0 - $t7
    for (int i = 8; i < 15; i++)
        if (used[i] == 0)
            return i;
}

int easyGetRightReg(FILE *fp, Operand op)
{
    // ---Method 1--- :all variable and tempVar stored in memory, load it before using it
    // and store it to memory after using it

    // VarMemAddress addressNode = findMemAddress(name);
    int idleID = getIdleReg();
    if (op->kind == CONSTANT || op->kind == COSNTVAR)
    {
        return idleID;
    }
    assert(findMemAddress(op->u.value) != NULL);
    int fpOffset = findMemAddress(op->u.value)->fpOffset;
    switch (op->kind)
    {
    case VARIABLE:
    case TEMPVAR:
        fprintf(fp, "  lw %s, %d($fp)\n", regName(idleID), fpOffset);
        break;
    case ADDRESS:
        fprintf(fp, "  addi %s, $fp, %d\n", regName(idleID), fpOffset);
        break;
    case STAR__:
        fprintf(fp, "  lw %s, %d($fp)\n", regName(idleID), fpOffset);
        fprintf(fp, "  lw %s, 0(%s)\n", regName(idleID), regName(idleID));
        break;
    default:
        codeLog("something wrong happens when dealing with getRightReg");
        codeLog("error case:");
        codeLog(op->u.value);
        codeLog("upper line is value of this op\n");
        break;
    }
    used[idleID] = 1;
    return idleID;
}

int easyGetLeftReg(FILE *fp, Operand op)
{
    assert(op->kind != ADDRESS);
    int idleID = getIdleReg();
    switch (op->kind)
    {
    case VARIABLE:
    case TEMPVAR:
        if (!findMemAddress(op->u.value)) //this branch means this variable hasn't been stored in memory
        {
            fprintf(fp, "  addi $sp, $sp, -4\n");
            stack_sp = stack_sp - 4;
            newMemAddress(op->u.value, stack_sp - stack_fp);
        }
        break;
    case STAR__:
        assert(findMemAddress(op->u.value) != NULL);
        fprintf(fp, "  lw %s, %d($fp)\n", regName(idleID), findMemAddress(op->u.value)->fpOffset);
        break;
    default:
        codeLog("something wrong happens when dealing with getleftReg");
        codeLog("error case:");
        codeLog(op->u.value);
        codeLog("upper line is value of this op\n");
        break;
    }
    used[idleID] = 1;
    return idleID;
}

void assembleASSIGN(FILE *fp, InterCode current)
{
    if (current->kind == MYASSIGN)
    {
        Operand left = current->u.op_assign.left;
        Operand right = current->u.op_assign.right;
        int leftReg = easyGetLeftReg(fp, left);
        int rightReg = easyGetRightReg(fp, right);
        // printf("leftReg:%d,rightReg:%d", leftReg, rightReg);
        assert(left->kind == STAR__ || left->kind == TEMPVAR || left->kind == VARIABLE);
        if (left->kind == STAR__)
        {
            if (right->kind == CONSTANT || right->kind == COSNTVAR)
            {
                //since we don't allocate register for constant in function easyGetRightReg
                //we just use leftReg + 1 when the left operand is STAR__ type
                fprintf(fp, "  li %s, %d\n", regName(rightReg), right->u.var_no);
                used[rightReg] = 1;
            }
            fprintf(fp, "  sw %s, 0(%s)\n", regName(rightReg), regName(leftReg));
        }
        else
        {
            if (right->kind == CONSTANT || right->kind == COSNTVAR)
            {
                fprintf(fp, "  li %s, %d\n", regName(leftReg), right->u.var_no);
            }
            else
            {
                fprintf(fp, "  move %s, %s\n", regName(leftReg), regName(rightReg));
            }
            fprintf(fp, "  sw %s, %d($fp)\n", regName(leftReg), findMemAddress(left->u.value)->fpOffset);
        }
    }
}

void assembleIFGOTO(FILE *fp, InterCode current)
{
}

void assembleSingleCode(FILE *fp, InterCode current)
{
    switch (current->kind)
    {
    case MYFUNCTION:
        fprintf(fp, "\n%s:\n", current->u.op_single.op->u.value);
        break;
    case MYPARAM: //TODO
        break;
    case MYRETURN: //TODO
        break;
    case MYLABEL:
        fprintf(fp, "%s:\n", current->u.op_single.op->u.value);
        break;
    case MYGOTO:
        fprintf(fp, "  j %s\n", current->u.op_single.op->u.value);
        break;
    case MYREAD: //TODO
        break;
    case MYWRITE: //TODO
        break;
    case MYARG: //TODO
        break;
    case MYASSIGN:
    case MYADD:
    case MYSUB:
    case MYMUL:
    case MYDIV:
        assembleASSIGN(fp, current);
        break;
    case MYDEC: //TODO
        break;
    case MYCALL: //TODO
        break;
    case MYIFGOTO: //TODO
        assembleIFGOTO(fp, current);
        break;
    default:
        break;
    }
}

void assembleCodes(char *outputFileName) //main assembly procedure
{
    FILE *fp;
    fp = fopen(outputFileName, "w+");
    if (fp == NULL)
        return;
    loadDataCode(fp);
    fprintf(fp, ".globl main\n");
    loadTextCode(fp);
    InterCode current = head;
    while (current != NULL)
    {
        assembleSingleCode(fp, current);
        current = current->next;
    }
}