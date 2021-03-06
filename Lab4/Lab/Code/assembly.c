#include "assembly.h"

VarMemAddress createMemAddressNode(char *name, int _offset)
{
    VarMemAddress newNode = (VarMemAddress)malloc(sizeof(struct VarMemAddress_));
    strcpy(newNode->name, name);
    newNode->fpOffset = _offset;
    newNode->link = NULL;
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
            {
                return current; //NOTE: this function return the node, not offset
            }
            current = current->link;
        }
        codeLog("end Loop");
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
    paramCount = 0;
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
        fprintf(fp, "  beq %s, %s ", reg1, reg2);
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
    //fprintf(stdout, "op value:%s\n", op->u.value);
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
    //fprintf(stdout, "last correct left:%s\n", op->u.value);
    switch (op->kind)
    {
    case VARIABLE:
    case TEMPVAR:
        codeLog("start doing VARIABLE\n");
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
    //it means, the first element of the array is stored in current sp
    fprintf(fp, "  addi $sp, $sp, -%d\n", arraySize); //subtract stack size of the array
    stack_sp = stack_sp - arraySize;
    newMemAddress(variable->u.value, stack_sp - stack_fp);
}

void assembleBINARY(FILE *fp, InterCode current)
{
    Operand op1 = current->u.op_binary.op1;
    Operand op2 = current->u.op_binary.op2;
    Operand result = current->u.op_binary.result;
    assert(result->kind == STAR__ || result->kind == TEMPVAR || result->kind == VARIABLE || result->kind == NOTHING);
    int op1Reg = easyGetRightReg(fp, op1);
    int op2Reg = easyGetRightReg(fp, op2);
    int resultReg = easyGetLeftReg(fp, result);
    if (result->kind == STAR__)
    {
        if (current->kind == MYADD)
        {
            if (isConst(op1) && isConst(op2))
                gen(fp, LI_, op1Reg, op1->u.var_no + op2->u.var_no, -1);
            else if (isConst(op1))
                gen(fp, ADDI_, op1Reg, op2Reg, op1->u.var_no);
            else if (isConst(op2))
                gen(fp, ADDI_, op1Reg, op1Reg, op2->u.var_no);
            else
                gen(fp, ADD_, op1Reg, op1Reg, op2Reg);
        }
        else if (current->kind == MYSUB)
        {
            if (isConst(op1) && isConst(op2))
                gen(fp, LI_, op1Reg, op1->u.var_no - op2->u.var_no, -1);
            else if (isConst(op1))
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, SUB_, op1Reg, op1Reg, op2Reg);
            }
            else if (isConst(op2))
                gen(fp, ADDI_, op1Reg, op1Reg, -op2->u.var_no);
            else
                gen(fp, SUB_, op1Reg, op1Reg, op2Reg);
        }
        else if (current->kind == MYMUL)
        {
            if (isConst(op1)&& isConst(op2))
                gen(fp, LI_, op1Reg, op1->u.var_no * op2->u.var_no, -1);
            else if (isConst(op1))
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, MUL_, op1Reg, op1Reg, op2Reg);
            }
            else if (isConst(op2))
            {
                gen(fp, LI_, op2Reg, op2->u.var_no, -1);
                gen(fp, MUL_, op1Reg, op1Reg, op2Reg);
            }
            else
                gen(fp, MUL_, op1Reg, op1Reg, op2Reg);
        }
        else if (current->kind == MYDIV)
        {
            if (isConst(op1))
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
            }
            if (isConst(op2))
            {
                gen(fp, LI_, op2Reg, op2->u.var_no, -1);
            }
            gen(fp, DIV_, op1Reg, op1Reg, op2Reg);
        }
        gen(fp, SW_, op1Reg, 0, resultReg);
    }
    else if (result->kind == TEMPVAR || result->kind == VARIABLE)
    {
        if (current->kind == MYADD)
        {
            if (isConst(op1)&&isConst(op2))
                gen(fp, LI_, resultReg, op1->u.var_no + op2->u.var_no, -1);
            else if (isConst(op1))
                gen(fp, ADDI_, resultReg, op2Reg, op1->u.var_no);
            else if (isConst(op2))
                gen(fp, ADDI_, resultReg, op1Reg, op2->u.var_no);
            else
                gen(fp, ADD_, resultReg, op1Reg, op2Reg);
        }
        else if (current->kind == MYSUB)
        {
            if (isConst(op1)&&isConst(op2))
                gen(fp, LI_, resultReg, op1->u.var_no - op2->u.var_no, -1);
            else if (isConst(op1))
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, SUB_, resultReg, op1Reg, op2Reg);
            }
            else if (isConst(op2))
                gen(fp, ADDI_, resultReg, op1Reg, -op2->u.var_no);
            else
                gen(fp, SUB_, resultReg, op1Reg, op2Reg);
        }
        else if (current->kind == MYMUL)
        {
            if (isConst(op1) && isConst(op2))
                gen(fp, LI_, resultReg, op1->u.var_no * op2->u.var_no, -1);
            else if (isConst(op1))
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
                gen(fp, MUL_, resultReg, op1Reg, op2Reg);
            }
            else if (isConst(op2))
            {
                gen(fp, LI_, op2Reg, op2->u.var_no, -1);
                gen(fp, MUL_, resultReg, op1Reg, op2Reg);
            }
            else
                gen(fp, MUL_, resultReg, op1Reg, op2Reg);
        }
        else if (current->kind == MYDIV)
        {
            if (isConst(op1))
            {
                gen(fp, LI_, op1Reg, op1->u.var_no, -1);
            }
            if (isConst(op2))
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
    Operand arg = current->u.op_single.op;
    int argReg = easyGetRightReg(fp, arg);
    if (arg->kind == CONSTANT || arg->kind == COSNTVAR)
        gen(fp, LI_, argReg, arg->u.var_no, -1);
    gen(fp, ADDI_, 29, 29, -4); //addi sp, sp, -4
    stack_sp = stack_sp - 4;
    gen(fp, SW_, argReg, stack_sp - stack_fp, 30);
}

void assembleFunction(FILE *fp, InterCode current)
{
    refreshStackPointer();
    fprintf(fp, "\n%s:\n", current->u.op_single.op->u.value);
    gen(fp, ADDI_, 29, 29, -4); //push fp
    stack_sp = stack_sp - 4;
    gen(fp, SW_, 30, 0, 29);
    gen(fp, MOVE_, 30, 29, -1); //move fp, sp
    stack_fp = stack_fp - 4;
    gen(fp, ADDI_, 29, 29, -4);
    stack_sp = stack_sp - 4;
    gen(fp, SW_, 31, 0, 29); //save $ra
}

void assemblePARAM(FILE *fp, InterCode current)
{
    Operand param = current->u.op_single.op;
    assert(findMemAddress(param->u.value) == NULL);
    paramCount++;
    newMemAddress(param->u.value, paramCount * 4);
}

void assembleCALL(FILE *fp, InterCode current)
{
    //left := CALL function
    Operand left = current->u.op_assign.left;
    Operand function = current->u.op_assign.right;
    fprintf(fp, "  jal %s\n", function->u.value);
    //restore our stack
    gen(fp, ADDI_, 29, 30, 4); //addi sp, fp, 4
    gen(fp, LW_, 30, 0, 30);   //lw fp, 0(fp)
    int leftReg = easyGetLeftReg(fp, left);
    gen(fp, MOVE_, leftReg, 2, -1);
    if (left->kind == STAR__)
        gen(fp, SW_, 2, 0, leftReg);
    else
    {
        assert(findMemAddress(left->u.value) != NULL);
        gen(fp, SW_, leftReg, findMemAddress(left->u.value)->fpOffset, 30);
    }
}

void assembleWRITE(FILE *fp, InterCode current)
{
    Operand write = current->u.op_single.op;
    if (write->kind == CONSTANT || write->kind == COSNTVAR)
        gen(fp, LI_, 4, write->u.var_no, -1);
    else
    {
        int writeReg = easyGetRightReg(fp, write);
        gen(fp, MOVE_, 4, writeReg, -1);
    }
    fprintf(fp, "  jal write\n");
}

void assembleREAD(FILE *fp, InterCode current)
{
    Operand read = current->u.op_single.op;
    assert(read->kind != CONSTANT && read->kind != COSNTVAR);
    fprintf(fp, "  jal read\n");
    int readReg = easyGetLeftReg(fp, read);
    gen(fp, MOVE_, readReg, 2, -1);
    gen(fp, SW_, readReg, findMemAddress(read->u.value)->fpOffset, 30);
}

void assembleRETURN(FILE *fp, InterCode current)
{
    Operand returnVar = current->u.op_single.op;
    if (returnVar->kind == CONSTANT || returnVar->kind == COSNTVAR)
        gen(fp, LI_, 2, returnVar->u.var_no, -1);
    else
    {
        int returnReg = easyGetRightReg(fp, returnVar);
        gen(fp, MOVE_, 2, returnReg, -1);
    }
    gen(fp, LW_, 31, -4, 30); //restore ra
    fprintf(fp, "  jr $ra\n");
}

void assembleSingleCode(FILE *fp, InterCode current)
{
    printAnnotation(fp, current);
    //fprintf(stdout, "fault type:%d\n", current->kind);
    if (current->kind != MYPARAM && paramCount > 0)
        paramCount = 0;
    switch (current->kind)
    {
    case MYFUNCTION:
        assembleFunction(fp, current);
        break;
    case MYPARAM:
        assemblePARAM(fp, current);
        break;
    case MYRETURN:
        assembleRETURN(fp, current);
        codeLine++;
        break;
    case MYLABEL:
        fprintf(fp, "%s:\n", current->u.op_single.op->u.value);
        gen(fp, ADDI_, 29, 30, stack_sp - stack_fp);
        break;
    case MYGOTO:
        fprintf(fp, "  j %s\n", current->u.op_single.op->u.value);
        break;
    case MYREAD:
        assembleREAD(fp, current);
        break;
    case MYWRITE:
        assembleWRITE(fp, current);
        break;
    case MYARG:
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
    case MYCALL:
        assembleCALL(fp, current);
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
    codeLine = 1;
    fp = fopen(outputFileName, "w+");
    if (fp == NULL)
        return;
    loadDataCode(fp);
    fprintf(fp, ".globl main\n");
    loadTextCode(fp);
    InterCode current = head;
    while (current != NULL)
    {
        //fprintf(stdout, "codeLine:%d\n", codeLine); //ANNOT
        assembleSingleCode(fp, current);
        freeReg();
        current = current->next;
        codeLine++;
    }
}