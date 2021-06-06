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

void refreshStackPointer()
{
    stack_sp = 10000;
    stack_fp = 10000;
}

void initAssembly()
{
    refreshStackPointer();
    for (int i = 0; i < 32; i++)
        used[i] = 0;
    for (int i = 0; i < MEMADDRESSSIZE; i++)
        memAddressTable[i] = NULL;
    argCount = 0;
}

void printAnnotation(FILE *fp, InterCode current)
{
    if (current->kind != MYFUNCTION && current->kind != MYLABEL)
    {
        fprintf(fp, "                               #");
        printSingleCode(fp, current);
    }
}

char *regName(int registerID, char str[])
{
    switch (registerID)
    {
    case 0:
        return "$zero";
    case 1:
        return "$at";
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
        return "$gp";
    case 29:
        return "$sp";
    case 30:
        return "$fp";
    case 31:
        return "$ra";
    default:
        return "NULL";
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
    codeLog("no idle register!");
    assert(1 == 0); //in our primitive function, it is impossible that all registers are busy
    return -1;
}

void freeReg()
{
    for (int i = 0; i < 32; i++)
        used[i] = 0;
}

int easyGetRightReg(FILE *fp, Operand op)
{
    // ---Method 1--- :all variable and tempVar stored in memory, load it before using it
    // and store it to memory after using it

    // VarMemAddress addressNode = findMemAddress(name);
    int idleID = getIdleReg();
    if (op->kind == CONSTANT || op->kind == COSNTVAR)
    {
        used[idleID] = 1;
        return idleID;
    }
    assert(findMemAddress(op->u.value) != NULL);
    int fpOffset = findMemAddress(op->u.value)->fpOffset;
    switch (op->kind)
    {
    case VARIABLE:
    case TEMPVAR:
        gen(fp, LW_, idleID, fpOffset, 30);
        break;
    case ADDRESS:
        gen(fp, ADDI_, idleID, 30, fpOffset);
        break;
    case STAR__:
        gen(fp, LW_, idleID, fpOffset, 30);
        gen(fp, LW_, idleID, 0, idleID);
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
        gen(fp, LW_, idleID, findMemAddress(op->u.value)->fpOffset, 30);
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

void gen(FILE *fp, int codeType, int _arg1, int _arg2, int _arg3)
{
    //this function generate machine code through codeType and three args
    char reg1[10], reg2[10], reg3[10];
    strcpy(reg1, regName(_arg1, reg1));
    strcpy(reg2, regName(_arg2, reg2));
    strcpy(reg3, regName(_arg3, reg3));
    switch (codeType)
    {
    case LI_:
        fprintf(fp, "  li %s, %d\n", reg1, _arg2);
        break;
    case MOVE_:
        fprintf(fp, "  move %s, %s\n", reg1, reg2);
        break;
    case ADDI_:
        fprintf(fp, "  addi %s, %s, %d\n", reg1, reg2, _arg3);
        break;
    case ADD_:
        fprintf(fp, "  add %s, %s, %s\n", reg1, reg2, reg3);
        break;
    case SUB_:
        fprintf(fp, "  sub %s, %s, %s\n", reg1, reg2, reg3);
        break;
    case MUL_:
        fprintf(fp, "  mul %s, %s, %s\n", reg1, reg2, reg3);
        break;
    case DIV_:
        fprintf(fp, "  div %s, %s\n", reg2, reg3);
        fprintf(fp, "  mflo %s\n", reg1);
        break;
    case LW_:
        fprintf(fp, "  lw %s, %d(%s)\n", reg1, _arg2, reg3);
        break;
    case SW_:
        fprintf(fp, "  sw %s, %d(%s)\n", reg1, _arg2, reg3);
        break;
    case BEQ_:
        fprintf(fp, "  beg %s, %s ", reg1, reg2);
        break;
    case BNE_:
        fprintf(fp, "  bne %s, %s ", reg1, reg2);
        break;
    case BGT_:
        fprintf(fp, "  bgt %s, %s ", reg1, reg2);
        break;
    case BLT_:
        fprintf(fp, "  blt %s, %s ", reg1, reg2);
        break;
    case BGE_:
        fprintf(fp, "  bge %s, %s ", reg1, reg2);
        break;
    case BLE_:
        fprintf(fp, "  ble %s, %s ", reg1, reg2);
        break;
    }
}

void assembleASSIGN(FILE *fp, InterCode current)
{
    Operand left = current->u.op_assign.left;
    Operand right = current->u.op_assign.right;
    int leftReg = easyGetLeftReg(fp, left);
    int rightReg = easyGetRightReg(fp, right);
    // printf("leftReg:%d,rightReg:%d\n", leftReg, rightReg);
    assert(left->kind == STAR__ || left->kind == TEMPVAR || left->kind == VARIABLE);
    if (left->kind == STAR__)
    {
        if (right->kind == CONSTANT || right->kind == COSNTVAR)
            gen(fp, LI_, rightReg, right->u.var_no, -1);
        gen(fp, SW_, rightReg, 0, leftReg);
    }
    else
    {
        if (right->kind == CONSTANT || right->kind == COSNTVAR)
            gen(fp, LI_, leftReg, right->u.var_no, -1);
        else
            gen(fp, MOVE_, leftReg, rightReg, -1);
        gen(fp, SW_, leftReg, findMemAddress(left->u.value)->fpOffset, 30);
    }
}

void assembleDEC(FILE *fp, InterCode current)
{
    Operand variable = current->u.op_dec.op;
    int arraySize = current->u.op_dec.size;
    assert(!findMemAddress(variable->u.value));
    newMemAddress(variable->u.value, stack_sp - stack_fp);
    //it means, the first element of the array is stored in current sp
    fprintf(fp, "  addi $sp, $sp, -%d\n", arraySize); //subtract stack size of the array
    stack_sp = stack_sp - arraySize;
}

void assembleBINARY(FILE *fp, InterCode current)
{
    Operand op1 = current->u.op_binary.op1;
    Operand op2 = current->u.op_binary.op2;
    Operand result = current->u.op_binary.result;
    int op1Reg = easyGetRightReg(fp, op1);
    int op2Reg = easyGetRightReg(fp, op2);
    int resultReg = easyGetLeftReg(fp, result);
    assert(result->kind == STAR__ || result->kind == TEMPVAR || result->kind == VARIABLE);
    if (result->kind == STAR__)
    {
        if (current->kind == MYADD)
        {
            if (op1->kind == CONSTANT && op2->kind == COSNTVAR)
                gen(fp, LI_, op1Reg, op1->u.var_no + op2->u.var_no, -1);
            else if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
                gen(fp, ADDI_, op1Reg, op2Reg, op1->u.var_no);
            else if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
                gen(fp, ADDI_, op1Reg, op1Reg, op2->u.var_no);
            else
                gen(fp, ADD_, op1Reg, op1Reg, op2Reg);
        }
        else if (current->kind == MYSUB)
        {
            if (op1->kind == CONSTANT && op2->kind == COSNTVAR)
                gen(fp, LI_, op1Reg, op1->u.var_no - op2->u.var_no, -1);
            else if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, SUB_, op1Reg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
                gen(fp, ADDI_, op1Reg, op1Reg, -op2->u.var_no);
            else
                gen(fp, SUB_, op1Reg, op1Reg, op2Reg);
        }
        else if (current->kind == MYMUL)
        {
            if ((op1->kind == CONSTANT || op1->kind == COSNTVAR) && (op2->kind == CONSTANT || op2->kind == COSNTVAR))
                gen(fp, LI_, op1Reg, op1->u.var_no * op2->u.var_no, -1);
            else if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, MUL_, op1Reg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
            {
                gen(fp, LI_, op2Reg, op2->u.var_no, -1);
                gen(fp, MUL_, op1Reg, op1Reg, op2Reg);
            }
            else
                gen(fp, MUL_, op1Reg, op1Reg, op2Reg);
        }
        else if (current->kind == MYDIV)
        {
            if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
            }
            if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
            {
                gen(fp, LI_, op2Reg, op2->u.var_no, -1);
            }
            gen(fp, DIV_, op1Reg, op1Reg, op2Reg);
        }
        gen(fp, SW_, op1Reg, 0, resultReg);
    }
    else
    {
        if (current->kind == MYADD)
        {
            if (op1->kind == CONSTANT && op2->kind == COSNTVAR)
                gen(fp, LI_, resultReg, op1->u.var_no + op2->u.var_no, -1);
            else if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
                gen(fp, ADDI_, resultReg, op2Reg, op1->u.var_no);
            else if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
                gen(fp, ADDI_, resultReg, op1Reg, op2->u.var_no);
            else
                gen(fp, ADD_, resultReg, op1Reg, op2Reg);
        }
        else if (current->kind == MYSUB)
        {
            if (op1->kind == CONSTANT && op2->kind == COSNTVAR)
                gen(fp, LI_, resultReg, op1->u.var_no - op2->u.var_no, -1);
            else if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, SUB_, resultReg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
                gen(fp, ADDI_, resultReg, op1Reg, -op2->u.var_no);
            else
                gen(fp, SUB_, resultReg, op1Reg, op2Reg);
        }
        else if (current->kind == MYMUL)
        {
            codeLog("this is myMul");
            if ((op1->kind == CONSTANT || op1->kind == COSNTVAR) && (op2->kind == CONSTANT || op2->kind == COSNTVAR))
                gen(fp, LI_, resultReg, op1->u.var_no * op2->u.var_no, -1);
            else if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, MUL_, resultReg, op1Reg, op2Reg);
            }
            else if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
            {
                gen(fp, LI_, op2Reg, op2->u.var_no, -1);
                gen(fp, MUL_, resultReg, op1Reg, op2Reg);
            }
            else
                gen(fp, MUL_, resultReg, op1Reg, op2Reg);
        }
        else if (current->kind == MYDIV)
        {
            if (op1->kind == CONSTANT || op1->kind == COSNTVAR)
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
            }
            if (op2->kind == CONSTANT || op2->kind == COSNTVAR)
            {
                gen(fp, LI_, op2Reg, op2->u.var_no, -1);
            }
            gen(fp, DIV_, resultReg, op1Reg, op2Reg);
        }
        assert(findMemAddress(result->u.value) != NULL);
        gen(fp, SW_, resultReg, findMemAddress(result->u.value)->fpOffset, 30);
    }
}

void assembleIFGOTO(FILE *fp, InterCode current)
{
    //in this function,we first load two operands(x and y)to two registers
    //then generate different codes according to the relop
    char relop[CHARMAXSIZE];
    Operand x = current->u.op_triple.x;
    Operand y = current->u.op_triple.y;
    Operand label = current->u.op_triple.label;
    strcpy(relop, current->u.op_triple.relop);
    int xReg = easyGetRightReg(fp, x);
    int yReg = easyGetRightReg(fp, y);
    //easyGetRightReg has already loaded the VARIABLE/TEMPVAR/STAR/ADDRESS operand to regs
    //but if x or y is constant, we need to load it to registers manually
    if (x->kind == CONSTANT || x->kind == COSNTVAR)
        gen(fp, LI_, xReg, x->u.var_no, -1);
    if (y->kind == CONSTANT || y->kind == COSNTVAR)
        gen(fp, LI_, yReg, y->u.var_no, -1);
    if (strcmp(relop, "==") == 0)
        gen(fp, BEQ_, xReg, yReg, -1);
    else if (strcmp(relop, "!=") == 0)
        gen(fp, BNE_, xReg, yReg, -1);
    else if (strcmp(relop, ">") == 0)
        gen(fp, BGT_, xReg, yReg, -1);
    else if (strcmp(relop, "<") == 0)
        gen(fp, BLT_, xReg, yReg, -1);
    else if (strcmp(relop, ">=") == 0)
        gen(fp, BGE_, xReg, yReg, -1);
    else if (strcmp(relop, "<=") == 0)
        gen(fp, BLE_, xReg, yReg, -1);
    fprintf(fp, "%s\n", label->u.value);
}

void assembleARG(FILE *fp, InterCode current)
{
    if (argCount <= 4)
    {

    }
    else
    {
        
    }
}

void assembleSingleCode(FILE *fp, InterCode current)
{
    printAnnotation(fp, current);
    switch (current->kind)
    {
    case MYFUNCTION:
        refreshStackPointer();
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
        assembleARG(fp, current);
        break;
    case MYASSIGN:
        assembleASSIGN(fp, current);
        break;
    case MYADD:
    case MYSUB:
    case MYMUL:
    case MYDIV:
        assembleBINARY(fp, current);
        break;
    case MYDEC:
        assembleDEC(fp, current);
        break;
    case MYCALL: //TODO
        break;
    case MYIFGOTO:
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
        freeReg();
        current = current->next;
    }
}