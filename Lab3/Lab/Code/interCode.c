#include "extern.h"
void codeLog(char *msg)
{
#ifdef InterCodeDebug
    printf("%s\n", msg);
#endif
}

char *int2String(int num, char *str)
{
    int i = 0;
    if (num < 0)
    {
        num = -num;
        str[i++] = '-';
    }
    do
    {
        str[i++] = num % 10 + 48;
        num /= 10;
    } while (num);
    str[i] = '\0';
    int j = 0;
    if (str[0] == '-')
    {
        j = 1;
        ++i;
    }
    for (; j < i / 2; j++)
    {
        str[j] = str[j] + str[i - 1 - j];
        str[i - 1 - j] = str[j] - str[i - 1 - j];
        str[j] = str[j] - str[i - 1 - j];
    }
    return str;
}

int calculateSize(Type type)
{
    if (type->kind == BASIC)
        return 4;
    else if (type->kind == ARRAY)
        return type->u.array.size * calculateSize(type->u.array.elem);
    else if (type->kind == STRUCTVAR)
    {
        int size = 0;
        FieldList p = type->u.structure;
        while (p)
        {
            size += calculateSize(p->type);
            p = p->tail;
        }
        return size;
    }
}

void insertCode(InterCode code)
{
    if (head == NULL)
    {
        head = code;
        tail = code;
        head->next = head->prev = NULL;
    }
    else
    {
        tail->next = code;
        code->prev = tail;
        code->next = NULL;
        tail = tail->next;
    }
}
void deleteCode(InterCode code)
{
    if (code == head && code == tail)
    {
        head = NULL;
        tail = NULL;
    }
    else if (code == head)
    {
        head = code->next;
        head->prev = NULL;
    }
    else if (code == tail)
    {
        tail = code->prev;
        tail->next = NULL;
    }
    else
    {
        code->prev->next = code->next;
        code->next->prev = code->prev;
    }
    free(code);
}

InterCode createCode()
{
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->next = code->prev = NULL;
    return code;
}

Operand createOpTmp()
{
    tNum++;
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = TEMPVAR;
    strcpy(res->u.value, "tt");
    char str[CHARMAXSIZE];
    int2String(tNum, str);
    strcat(res->u.value, str);
    return res;
}

Operand createOpLabel()
{
    labelNum++;
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = LABEL;
    strcpy(res->u.value, "label");
    char str[CHARMAXSIZE];
    int2String(labelNum, str);
    strcat(res->u.value, str);
    return res;
}

Operand copyOpLabel(int num)
{
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = LABEL;
    strcpy(res->u.value, "label");
    char str[CHARMAXSIZE];
    int2String(num, str);
    strcat(res->u.value, str);
    return res;
}

void newInterCode(int kind, ...)
{
    va_list args;
    va_start(args, kind);
    InterCode code = createCode();
    code->kind = kind;
    switch (kind)
    {
    case MYFUNCTION:
    case MYPARAM:
    case MYRETURN:
    case MYLABEL:
    case MYGOTO:
    case MYREAD:
    case MYWRITE:
    case MYARG:
    {
        code->u.op_single.op = va_arg(args, Operand);
        break;
    }
    case MYASSIGN:
    case MYCALL:
    {
        code->u.op_assign.left = va_arg(args, Operand);
        code->u.op_assign.right = va_arg(args, Operand);
        break;
    }
    case MYDEC:
    {
        code->u.op_dec.op = va_arg(args, Operand);
        code->u.op_dec.size = va_arg(args, int);
        break;
    }
    case MYADD:
    {
        code->u.op_binary.result = va_arg(args, Operand);
        code->u.op_binary.op1 = va_arg(args, Operand);
        code->u.op_binary.op2 = va_arg(args, Operand);
        code->u.op_binary._operator = '+';
        break;
    }
    case MYSUB:
    {
        code->u.op_binary.result = va_arg(args, Operand);
        code->u.op_binary.op1 = va_arg(args, Operand);
        code->u.op_binary.op2 = va_arg(args, Operand);
        code->u.op_binary._operator = '-';
        break;
    }
    case MYMUL:
    {
        code->u.op_binary.result = va_arg(args, Operand);
        code->u.op_binary.op1 = va_arg(args, Operand);
        code->u.op_binary.op2 = va_arg(args, Operand);
        code->u.op_binary._operator = '*';
        break;
    }
    case MYDIV:
    {
        code->u.op_binary.result = va_arg(args, Operand);
        code->u.op_binary.op1 = va_arg(args, Operand);
        code->u.op_binary.op2 = va_arg(args, Operand);
        code->u.op_binary._operator = '/';
        break;
    }
    case MYIFGOTO:
    {
        code->u.op_triple.x = va_arg(args, Operand);
        strcpy(code->u.op_triple.relop, va_arg(args, char *));
        code->u.op_triple.y = va_arg(args, Operand);
        code->u.op_triple.label = va_arg(args, Operand);
        break;
    }
    default:
        printf("to be continued\n");
        break;
    }
    insertCode(code);
    va_end(args);
}

Operand createOperand(int kind, ...)
{
    va_list args;
    va_start(args, kind);
    Operand op_ = (Operand)malloc(sizeof(struct Operand_));
    op_->kind = kind;
    switch (kind)
    {
    case VARIABLE:
    case STAR__:
    case FUNCTION__:
    case TEMPVAR:
    {
        strcpy(op_->u.value, va_arg(args, char *));
        break;
    }
    case CONSTANT:
    {
        op_->u.var_no = va_arg(args, int);
        break;
    }
    default:
        printf("to be continued\n");
        break;
    }
    va_end(args);
    return op_;
}

FPTableNode *createFPTable()
{
    FPTableNode *table = (FPTableNode *)malloc(FORMALPARAMETERSIZE * sizeof(FPTableNode));
    for (int i = 0; i < FORMALPARAMETERSIZE; i++)
        table[i] = NULL;
    return table;
}

FPTableNode createFPMember(char *name)
{
    FPTableNode newMember = (FPTableNode)malloc(sizeof(struct FPTableNode_));
    strcpy(newMember->name, name);
    newMember->link = NULL;
    return newMember;
}

int findFPMember(char *name, int _insert)
{
    codeLog("start find FPMember");
    unsigned int hashID = hashProject(name, FORMALPARAMETERSIZE);
    FPTableNode current = FPTable[hashID];
    if (current == NULL)
    {
        if (_insert)
            FPTable[hashID] = createFPMember(name);
        return 0;
    }
    else
    {
        while (current->link != NULL)
        {
            if (strcmp(current->name, name) == 0) //loop until we find that name
                return 1;
            current = current->link;
        }
        if (strcmp(current->name, name) == 0) //if the last tuple matches
            return 1;
        else
        {
            if (_insert)
                current->link = createFPMember(name);
            return 0; //if that name does not exist in our table, insert it and return False
        }
    }
}

void initInterCode(node root)
{
    head = tail = NULL;
    tNum = labelNum = structNum = varNum =0;
    FPTable = createFPTable();
    translateProgram(root);
}

void translateProgram(node root)
{
    translateExtDefList(root->child);
}

void translateExtDefList(node root)
{
    if (root == NULL)
        return;
    translateExtDef(root->child);
    translateExtDefList(root->child->sibling);
}

void translateExtDef(node root)
{
    node n1 = getKChild(root, 1);
    node n2 = getKChild(root, 2);
    if (strcmp(n1->name, "FunDec") == 0)
    {
        translateFunDec(n1);
        translateCompst(n2);
    }
}

void translateFunDec(node root)
{
    // Operand op_tmp = (Operand)malloc(sizeof(struct Operand_));
    // op_tmp->kind = VARIABLE;
    // strcpy(op_tmp->u.value, root->child->val);
    Operand op_tmp = createOperand(VARIABLE, root->child->val);
    newInterCode(MYFUNCTION, op_tmp);
    if (getChildNum(root) == 4)
        translateVarList(getKChild(root, 2));
}

void translateVarList(node root)
{
    translateParamDec(root->child);
    if (getChildNum(root) > 1)
        translateVarList(getKChild(root, 2));
}

void translateParamDec(node root)
{
    translateVarDec_A(getKChild(root, 1));
    return;
}
// FunDec: VarDec
void translateVarDec_A(node root)
{
    node n0 = getKChild(root, 0);
    if (strcmp(n0->name, "ID") == 0)
    {
        Symbol findTuple = findSymbol(n0->val);
        Operand op_tmp = createOperand(VARIABLE, n0->val);
        findFPMember(n0->val, 1);
        newInterCode(MYPARAM, op_tmp);
        if (findTuple->type->kind == ARRAY)
        {
            //TODO: params of 1d-array
        }
        else if (findTuple->type->kind == STRUCTURE || findTuple->type->kind == STRUCTVAR)
        {
            structNum++;
            // printf("Cannot translate: Code contains variables or paraneters of structure type\n");
        }
    }
    else
        translateVarDec_A(n0);
}
//Local Variable: VarDec
void translateVarDec_B(node root)
{
    node n0 = getKChild(root, 0);
    if (strcmp(n0->name, "ID") == 0)
    {
        Symbol findTuple = findSymbol(n0->val);
        if (findTuple->type->kind == STRUCTURE || findTuple->type->kind == STRUCTVAR)
        {
            structNum++;
            // printf("Cannot translate: Code contains variables or paraneters of structure type\n");
        }
        else if (findTuple->type->kind == ARRAY)
        {
            //REVISE:delete multi-dimensional array process
            int size = calculateSize(findTuple->type);
            Operand op_tmp = createOperand(VARIABLE, n0->val);
            newInterCode(MYDEC, op_tmp, size);
        }
    }
    else
        translateVarDec_B(n0);
}

void translateCompst(node root)
{
    node n1 = getKChild(root, 1);
    if (strcmp(n1->name, "DefList") == 0)
    {
        translateDefList_A(n1);
        n1 = n1->sibling;
    }
    if (strcmp(n1->name, "StmtList") == 0)
        translateStmtList(n1);
}
// DefList in Function
void translateDefList_A(node root)
{
    if (root != NULL)
    {
        translateDef_A(getKChild(root, 0));
        translateDefList_A(getKChild(root, 1));
    }
}

void translateDef_A(node root)
{
    translateDecList_A(getKChild(root, 1));
}

void translateDecList_A(node root)
{
    if (getChildNum(root) == 1)
        translateDec_A(getKChild(root, 0));
    else
    {
        translateDec_A(getKChild(root, 0));
        translateDecList_A(getKChild(root, 2));
    }
}

void translateDec_A(node root)
{
    if (getChildNum(root) == 1)
        translateVarDec_B(getKChild(root, 0));
    else
    {
        Operand op_left = createOperand(VARIABLE, root->child->child->val);
        Operand op_right = createOpTmp();
        translateExp(getKChild(root, 2), op_right);
        newInterCode(MYASSIGN, op_left, op_right);
        if (op_right->kind == CONSTANT || op_right->kind == COSNTVAR)
        {
            // TODO
        }
    }
}

void translateStmtList(node root)
{
    if (root != NULL)
    {
        translateStmt(getKChild(root, 0));
        translateStmtList(getKChild(root, 1));
    }
}

void translateStmt(node root)
{
    node n0 = getKChild(root, 0);
    if (strcmp(n0->name, "Exp") == 0)
    {
        Operand op = (Operand)malloc(sizeof(struct Operand_));
        op->kind = NOTHING;
        translateExp(n0, op);
    }
    else if (strcmp(n0->name, "CompSt") == 0)
        translateCompst(n0);
    else if (strcmp(n0->name, "RETURN") == 0)
    {
        Operand op = createOpTmp();
        node n1 = getKChild(root, 1);
        translateExp(n1, op);
        newInterCode(MYRETURN, op);
    }
    else if (strcmp(n0->name, "IF") == 0)
    {
        // IF LP EXP RP STMT
        if (getChildNum(root) == 5)
        {
            Operand op_label1 = createOpLabel();
            int label1 = labelNum;
            Operand op_label2 = createOpLabel();
            int label2 = labelNum;

            node n2 = getKChild(root, 2);
            translateCond(n2, label1, label2);

            newInterCode(MYLABEL, op_label1);

            //increase cnt2
            node n4 = getKChild(root, 4);
            translateStmt(n4);
            //decrease cnt2

            newInterCode(MYLABEL, op_label2);
        }
        // IF LP EXP RP STMT ELSE STMT
        else
        {
            Operand op_label1 = createOpLabel();
            int label1 = labelNum;
            Operand op_label2 = createOpLabel();
            int label2 = labelNum;
            Operand op_label3 = createOpLabel();
            int label3 = labelNum;

            node n2 = getKChild(root, 2);
            translateCond(n2, label1, label2);

            newInterCode(MYLABEL, op_label1);

            //increase cnt2
            node n4 = getKChild(root, 4);
            translateStmt(n4);
            //decrease cnt2

            Operand op_tmp3 = copyOpLabel(label3);
            newInterCode(MYGOTO, op_tmp3);

            newInterCode(MYLABEL, op_label2);

            //increase cnt2
            node n6 = getKChild(root, 6);
            translateStmt(n6);
            //decrease cnt2

            newInterCode(MYLABEL, op_label3);
        }
    }
    // WHILE LP EXP RP STMT (unfinished)
    else
    {
        Operand op_label1 = createOpLabel();
        int label1 = labelNum;
        Operand op_label2 = createOpLabel();
        int label2 = labelNum;
        Operand op_label3 = createOpLabel();
        int label3 = labelNum;

        newInterCode(MYLABEL, op_label1);

        //set cnt = 1
        node n2 = getKChild(root, 2);
        translateCond(n2, label2, label3);
        //set cnt = 0

        newInterCode(MYLABEL, op_label2);

        // cnt1 ++;
        node n4 = getKChild(root, 4);
        translateStmt(n4);
        // cnt1 --;

        Operand op_tmp1 = copyOpLabel(label1);
        newInterCode(MYGOTO, op_tmp1);

        newInterCode(MYLABEL, op_label3);
    }
}

void translateExp(node root, Operand op)
{
    node n0 = getKChild(root, 0);
    node n1 = getKChild(root, 1);
    node n2 = getKChild(root, 2);
    int childNum = getChildNum(root);
    if (childNum == 1)
    {
        if (strcmp(n0->name, "ID") == 0)
        {
            Symbol findTuple = findSymbol(n0->val);
            if (findTuple->type->kind == ARRAY)
                op->kind = ADDRESS;
            else
                op->kind = VARIABLE;
            strcpy(op->u.value, n0->val);
        }
        else if (strcmp(n0->name, "INT") == 0)
        {
            op->kind = CONSTANT;
            op->u.var_no = atoi(n0->val);
        }
    }
    else if (childNum == 2)
    {
        if (strcmp(n0->name, "MINUS") == 0)
        {
            Operand op_tmp = createOpTmp();
            translateExp(n1, op_tmp);
            if (op_tmp->kind == CONSTANT || op_tmp->kind == COSNTVAR)
            {
                op->kind = COSNTVAR;
                op->u.var_no = op_tmp->u.var_no * (-1);
            }
            else
            {
                Operand op_const = createOperand(CONSTANT, 0);
                newInterCode(MYSUB, op, op_const, op_tmp);
            }
        }
        else if (strcmp(n0->name, "NOT") == 0)
        {
            translateExpCommon(root, op);
        }
    }
    else if (childNum == 3)
    {
        if (strcmp(n0->name, "LP") == 0)
            translateExp(n1, op);
        else if (strcmp(n1->name, "ASSIGNOP") == 0)
        {
            // ALL kinds of ASSIGNOP
            Operand op_tmp = createOpTmp();
            translateExp(n0, op_tmp);
            if (op_tmp->kind == COSNTVAR)
            {
                op_tmp->kind = VARIABLE;
                strcpy(op_tmp->u.value, n0->child->val);
            }
            Operand t1 = createOpTmp();
            translateExp(n2, t1);
            Type type1 = Exp(n0);
            Type type2 = Exp(n2);
            if (type1->kind != ARRAY)
            {
                newInterCode(MYASSIGN, op_tmp, t1);
                // place := varialbe.name
                if (op->kind != NOTHING)
                {
                    op->kind = op_tmp->kind;
                    strcpy(op->u.value, op_tmp->u.value);
                }
            }
            else
            {
                // i = &addr1
                Operand addr1 = (Operand)malloc(sizeof(struct Operand_));
                if (op_tmp->kind == ADDRESS)
                    addr1->kind = ADDRESS;
                else
                    addr1->kind = VARIABLE;
                strcpy(addr1->u.value, op_tmp->u.value);
                Operand i = createOpTmp();

                newInterCode(MYASSIGN, i, addr1);

                // j = &addr2
                Operand addr2 = (Operand)malloc(sizeof(struct Operand_));
                if (t1->kind == ADDRESS)
                    addr2->kind = ADDRESS;
                else
                    addr2->kind = VARIABLE;
                strcpy(addr2->u.value, t1->u.value);
                Operand j = createOpTmp();
                newInterCode(MYASSIGN, j, addr2);

                // k = &array2 + sizeof(array2)
                Operand k = createOpTmp();
                Operand constsize = createOperand(CONSTANT, calculateSize(type2));
                newInterCode(MYADD, k, j, constsize);

                //label1
                Operand op_label1 = createOpLabel();
                int label1 = labelNum;
                newInterCode(MYLABEL, op_label1);

                // ifgoto label2
                Operand op_label2 = createOpLabel();
                int label2 = labelNum;
                newInterCode(MYIFGOTO, j, ">=", k, op_label2);

                // *i = *j
                Operand tmp1 = createOperand(STAR__, i->u.value);
                Operand tmp2 = createOperand(STAR__, j->u.value);
                newInterCode(MYASSIGN, tmp1, tmp2);

                // i = i + 4
                Operand constsize4 = createOperand(CONSTANT, 4);
                newInterCode(MYADD, i, i, constsize4);

                // j = j + 4
                newInterCode(MYADD, j, j, constsize4);

                // GOTO LABEL1
                Operand op_tmp1 = copyOpLabel(label1);
                newInterCode(MYGOTO, op_tmp1);

                // LABEL2
                newInterCode(MYLABEL, copyOpLabel(label2));

                op->kind = op_tmp->kind;
                strcpy(op->u.value, op_tmp->u.value);
            }
        }
        else if (strcmp(n1->name, "AND") == 0 || strcmp(n1->name, "OR") == 0 || strcmp(n1->name, "RELOP") == 0)
        {
            translateExpCommon(root, op);
        }
        else if (strcmp(n1->name, "DOT") == 0)
        {
            structNum++;
            // printf("cannot translate struct\n");
        }
        else if (strcmp(n0->name, "ID") == 0)
        {
            translateExpFunc(root, op);
        }
        else
        {
            translateExpMath(root, op);
        }
    }
    else if (childNum == 4)
    {
        if (strcmp(n0->name, "Exp") == 0)
        {
            translateExpArray(root, op);
        }
        else
        {
            translateExpFunc(root, op);
        }
    }
}

void translateExpCommon(node root, Operand place)
{
    Operand op_label1 = createOpLabel();
    int label1 = labelNum;
    Operand op_label2 = createOpLabel();
    int label2 = labelNum;
    Operand const0 = createOperand(CONSTANT, 0);
    Operand const1 = createOperand(CONSTANT, 1);

    newInterCode(MYASSIGN, place, const0);

    translateCond(root, label1, label2);

    newInterCode(MYLABEL, op_label1);

    newInterCode(MYASSIGN, place, const1);

    newInterCode(MYLABEL, op_label2);
}

void translateExpFunc(node root, Operand place)
{
    char name[CHARMAXSIZE];
    strcpy(name, root->child->val);
    Symbol findTuple = findSymbol(name);
    int childNum = getChildNum(root);
    if (place->kind == NOTHING)
    {
        free(place);
        place = createOpTmp();
    }
    if (childNum == 3)
    {
        if (strcmp(name, "read") == 0)
        {
            newInterCode(MYREAD, place);
        }
        else
        {
            Operand funcName = createOperand(FUNCTION__, name);
            newInterCode(MYCALL, place, funcName);
        }
    }
    else
    {
        argNode argList = NULL;
        argList = translateArgs(getKChild(root, 2));
        if (strcmp(name, "write") == 0)
        {
            newInterCode(MYWRITE, argList->op);
        }
        else
        {
            argNode p = argList;
            while (p)
            {
                newInterCode(MYARG, p->op);
                p = p->next;
            }
            Operand funcName = createOperand(FUNCTION__, name);
            newInterCode(MYCALL, place, funcName);
        }
    }
}

argNode translateArgs(node root)
{
    // argNode argListHead = NULL;
    // while (getChildNum(root) > 1)
    // {
    //     Operand t1 = createOpTmp();
    //     node n0 = getKChild(root, 0);
    //     translateExp(n0, t1);
    //     if (t1->kind == ADDRESS && findFPMember(t1->u.value, 0))
    //         t1->kind = VARIABLE;
    //     argNode node1 = (argNode)malloc(sizeof(struct argNode_));
    //     node1->op = t1;
    //     node1->next = argListHead;
    //     argListHead = node1;
    //     root = getKChild(root, 2);
    // }
    argNode argListHead = NULL;
    if (getChildNum(root) > 1)
        argListHead = translateArgs(getKChild(root, 2)); //argListHead represents the head of the args after current Exp
    Operand t1 = createOpTmp();
    node n0 = getKChild(root, 0);
    translateExp(n0, t1);
    if (t1->kind == ADDRESS && findFPMember(t1->u.value, 0))
        t1->kind = VARIABLE;
    argNode node1 = (argNode)malloc(sizeof(struct argNode_));
    node1->op = t1;
    if (argListHead == NULL)
        argListHead = node1;
    else
    {
        argNode argListTail = argListHead;
        while (argListTail->next != NULL)
            argListTail = argListTail->next;
        argListTail->next = node1;
    }
    return argListHead;
}

void translateExpMath(node root, Operand place)
{
    node n0 = getKChild(root, 0);
    node n1 = getKChild(root, 1);
    node n2 = getKChild(root, 2);
    Operand t1 = createOpTmp();
    translateExp(n0, t1);
    Operand t2 = createOpTmp();
    translateExp(n2, t2);
    if ((t1->kind == CONSTANT || t1->kind == COSNTVAR) && (t2->kind == CONSTANT || t2->kind == COSNTVAR))
    {
        if (strcmp(n1->name, "PLUS") == 0)
            place->u.var_no = t1->u.var_no + t2->u.var_no, place->kind = COSNTVAR;
        else if (strcmp(n1->name, "MINUS") == 0)
            place->u.var_no = t1->u.var_no - t2->u.var_no, place->kind = COSNTVAR;
        else if (strcmp(n1->name, "STAR") == 0)
            place->u.var_no = t1->u.var_no * t2->u.var_no, place->kind = COSNTVAR;
        else if (strcmp(n1->name, "DIV") == 0)
        {
            if (t2->u.var_no != 0)
                place->u.var_no = t1->u.var_no / t2->u.var_no, place->kind = COSNTVAR;
            else
                newInterCode(MYDIV, place, t1, t2);
        }
    }
    else
    {
        if (strcmp(n1->name, "PLUS") == 0)
            newInterCode(MYADD, place, t1, t2);
        else if (strcmp(n1->name, "MINUS") == 0)
            newInterCode(MYSUB, place, t1, t2);
        else if (strcmp(n1->name, "STAR") == 0)
            newInterCode(MYMUL, place, t1, t2);
        else if (strcmp(n1->name, "DIV") == 0)
            newInterCode(MYDIV, place, t1, t2);
    }
}

void translateExpArray(node root, Operand place)
{
    Operand t1 = createOpTmp();
    node n0 = getKChild(root, 0);
    node n2 = getKChild(root, 2);
    translateExp(n2, t1);
    Operand t2 = createOpTmp();
    translateExp(n0, t2);
    Operand t3 = createOpTmp();
    t3->kind = place->kind;
    strcpy(t3->u.value, place->u.value);
    //t1:represents [Exp]
    //t2:represents Exp[]
    //t3:represents place
    if (t2->kind != STAR__ && !findFPMember(t2->u.value, 0))
        t2->kind = ADDRESS;
    else
        t2->kind = VARIABLE;
    Operand t4 = createOpTmp();
    Type type = Exp(n0);
    Operand constsize = createOperand(CONSTANT, calculateSize(type->u.array.elem));

    newInterCode(MYMUL, t4, constsize, t1);
    newInterCode(MYADD, t3, t2, t4);
    place->kind = STAR__;
}

void translateCond(node root, int label_true, int label_false)
{
    node n1 = getKChild(root, 1);
    node n0 = getKChild(root, 0);
    node n2 = getKChild(root, 2);
    if (n1 && strcmp(n1->name, "RELOP") == 0)
    {
        Operand t1 = createOpTmp();
        Operand t2 = createOpTmp();

        translateExp(n0, t1);
        translateExp(n2, t2);

        newInterCode(MYIFGOTO, t1, n1->val, t2, copyOpLabel(label_true));

        newInterCode(MYGOTO, copyOpLabel(label_false));
    }
    else if (n0 && strcmp(n0->name, "NOT") == 0)
        translateCond(n1, label_false, label_true);
    else if (n1 && strcmp(n1->name, "AND") == 0)
    {
        Operand op_label1 = createOpLabel();
        int label1 = labelNum;

        translateCond(n0, label1, label_false);

        newInterCode(MYLABEL, op_label1);
        translateCond(n2, label_true, label_false);
    }
    else if (n1 && strcmp(n1->name, "OR") == 0)
    {
        Operand op_label1 = createOpLabel();
        int label1 = labelNum;

        translateCond(n0, label_true, label1);

        newInterCode(MYLABEL, op_label1);

        translateCond(n2, label_true, label_false);
    }
    else
    {
        Operand t1 = createOpTmp();
        translateExp(root, t1);
        Operand t2 = createOperand(CONSTANT, 0);

        newInterCode(MYIFGOTO, t1, "!=", t2, copyOpLabel(label_true));

        newInterCode(MYGOTO, copyOpLabel(label_false));
    }
}

LabelNode createLabelNode(char *labelName)
{
    LabelNode lnode = (LabelNode)malloc(sizeof(struct LabelNode_));
    strcpy(lnode->name, labelName);
    lnode->link = NULL;
    return lnode;
}

LabelNode deleteContinuedLabel(InterCode *q)
{
    LabelNode labelHead, labelTail;
    labelHead = labelTail = NULL;
    InterCode p = *q;
    LabelNode label_ = createLabelNode(p->u.op_single.op->u.value);
    labelHead = labelTail = label_;
    labelTail->link = NULL;
    p = p->next;
    while (p && p->kind == MYLABEL)
    {
        LabelNode label_ = createLabelNode(p->u.op_single.op->u.value);
        labelTail->link = label_;
        labelTail = label_;
        InterCode toDelete = p;
        p = p->next;
        deleteCode(toDelete);
    }
    *q = p;
    return labelHead;
}

LabelNode createLabelList(InterCode code)
{
    LabelNode labelHead, labelTail;
    labelHead = labelTail = NULL;
    InterCode p = code;
    while (p)
    {
        if (p->kind == MYGOTO || p->kind == MYIFGOTO)
        {
            LabelNode tmpNode = createLabelNode(p->kind == MYGOTO ? p->u.op_single.op->u.value : p->u.op_triple.label->u.value);
            if (labelHead == NULL)
            {
                labelHead = labelTail = tmpNode;
                labelTail->link = NULL;
            }
            else
            {
                labelTail->link = tmpNode;
                labelTail = tmpNode;
            }
        }
        p = p->next;
    }
    return labelHead;
}

void optimize_mergeLABEL()
{
    InterCode p = head;
    while (p)
    {
        if (p->kind != MYLABEL)
            p = p->next;
        else
        {
            LabelNode labelHead = deleteContinuedLabel(&p);
            // delete continued label and store into a list called labelHead
            if (labelHead->link)
            {
                InterCode tmp = head;
                while (tmp)
                {
                    if (tmp->kind == MYGOTO || tmp->kind == MYIFGOTO)
                    {
                        char name[CHARMAXSIZE];
                        strcpy(name, (tmp->kind == MYGOTO) ? tmp->u.op_single.op->u.value : tmp->u.op_triple.label->u.value);
                        LabelNode q = labelHead;
                        while (q)
                        {
                            if (strcmp(q->name, name) == 0)
                            {
                                strcpy((tmp->kind == MYGOTO) ? tmp->u.op_single.op->u.value : tmp->u.op_triple.label->u.value, labelHead->name);
                                break;
                            }
                            q = q->link;
                        }
                    }
                    tmp = tmp->next;
                }
            }
        }
    }
}

void optimize_deleteGOTO()
{
    InterCode p = head;
    while (p)
    {
        if (p->kind == MYGOTO)
        {
            InterCode q = p->next;
            if (q && q->kind == MYLABEL && strcmp(p->u.op_single.op->u.value, q->u.op_single.op->u.value) == 0)
                deleteCode(p);
        }
        else if (p->kind == MYIFGOTO)
        {
            // reverse p->u.op_triple.relop
            InterCode q = p->next;
            if (q && q->next && q->kind == MYGOTO && strcmp(p->u.op_triple.label->u.value, q->next->u.op_single.op->u.value) == 0)
            {
                strcpy(p->u.op_triple.label->u.value, q->u.op_single.op->u.value);
                deleteCode(q);
                reverseCodeRELOP(&p);
            }
        }
        p = p->next;
    }
    // delete unnecessary label
    LabelNode labelHead = createLabelList(head);
    p = head;
    while (p)
    {
        if (p->kind != MYLABEL)
            p = p->next;
        else
        {
            LabelNode q = labelHead;
            while (q)
            {
                if (strcmp(q->name, p->u.op_single.op->u.value) == 0)
                    break;
                q = q->link;
            }
            InterCode toDelete = p;
            p = p->next;
            if (q == NULL)
                deleteCode(toDelete);
        }
    }
}

void reverseCodeRELOP(InterCode *q)
{
    InterCode p = *q;
    if (strcmp(p->u.op_triple.relop, "==") == 0)
        strcpy(p->u.op_triple.relop, "!=");
    else if (strcmp(p->u.op_triple.relop, "!=") == 0)
        strcpy(p->u.op_triple.relop, "==");
    else if (strcmp(p->u.op_triple.relop, ">") == 0)
        strcpy(p->u.op_triple.relop, "<=");
    else if (strcmp(p->u.op_triple.relop, ">=") == 0)
        strcpy(p->u.op_triple.relop, "<");
    else if (strcmp(p->u.op_triple.relop, "<") == 0)
        strcpy(p->u.op_triple.relop, ">=");
    else if (strcmp(p->u.op_triple.relop, "<=") == 0)
        strcpy(p->u.op_triple.relop, ">");
}

void optimize_deleteNONEVAR()
{
    InterCode p = head;
    while (p)
    {
        if (p->kind == MYASSIGN && p->u.op_assign.left->kind == NOTHING)
            deleteCode(p);
        p = p->next;
    }
}

void optimize_deleteCONST() {
    InterCode p = head;
    while(p) 
    {
        if(p->kind == MYASSIGN && (p->u.op_assign.right->kind == CONSTANT || p->u.op_assign.right->kind == COSNTVAR) && (p->u.op_assign.left->kind == VARIABLE || p->u.op_assign.right->kind == TEMPVAR)) {

            int insteadConst = p->u.op_assign.right->u.var_no;
            char insteadName[CHARMAXSIZE];
            strcpy(insteadName, p->u.op_assign.left->u.value);
            InterCode q = p->next;
            InterCode final = nextInterCode(p);
            while(q != final) 
            {
                if(q->kind == MYREAD) {
                    if(strcmp(q->u.op_single.op->u.value, insteadName) == 0)
                    {
                        break;
                    }
                }
                if(q->kind == MYRETURN || q->kind == MYWRITE) 
                {
                    if(strcmp(q->u.op_single.op->u.value, insteadName) == 0)
                    {
                        q->u.op_single.op->kind = COSNTVAR;
                        q->u.op_single.op->u.var_no = insteadConst;
                    }
                }
                else if(q->kind == MYASSIGN) {
                    if(strcmp(q->u.op_assign.right->u.value, insteadName) == 0) {
                        q->u.op_assign.right->kind = COSNTVAR;
                        q->u.op_assign.right->u.var_no = insteadConst;
                    }
                    if(strcmp(q->u.op_assign.left->u.value, insteadName) == 0)
                        break;
                }
                else if(q->kind == MYADD || q->kind == MYSUB || q->kind == MYMUL || q->kind == MYDIV) {
                    if(strcmp(q->u.op_binary.op1->u.value, insteadName) == 0) {
                        q->u.op_binary.op1->kind = COSNTVAR;
                        q->u.op_binary.op1->u.var_no = insteadConst;
                    }
                    if(strcmp(q->u.op_binary.op2->u.value, insteadName) == 0) {
                        q->u.op_binary.op2->kind = COSNTVAR;
                        q->u.op_binary.op2->u.var_no = insteadConst;
                    }
                    if(strcmp(q->u.op_binary.result->u.value, insteadName) == 0) {
                        break;
                    }
                }
                q = q->next;
            }
            if(q == final)
                p = p->next;
            else
            {
                InterCode toDelete = p;
                p = p->next;
                deleteCode(toDelete);
            }
            
        }
        else 
            p = p->next;
    }
}

InterCode nextInterCode(InterCode code) {
    if(code == NULL || code->next)
        return NULL;
    InterCode cur = code->next, pre = code;
    while(cur) {
        if(cur->kind == MYLABEL || cur->kind == MYFUNCTION ||pre->kind == MYGOTO || pre->kind == MYIFGOTO)
            return cur;
        pre = cur;
        cur = cur->next;
    }
    return NULL;
}

void insteadUnderlineVar() {
    InterCode p = head;
    while(p) 
    {
        if(p->kind == MYPARAM || p->kind == MYREAD)  
        {
            if(!isalpha(p->u.op_single.op->u.value[0])) {
                char target[CHARMAXSIZE];
                strcpy(target, p->u.op_single.op->u.value);
                varNum++;
                char instead[CHARMAXSIZE];
                strcpy(instead, "vv");
                char str[CHARMAXSIZE];
                int2String(varNum, str);
                strcat(instead, str);
                strcpy(p->u.op_single.op->u.value, instead);
                InterCode q = p->next;
                while(q) {
                    switch(q->kind) 
                    {
                        case MYFUNCTION :
                        case MYPARAM:
                        case MYRETURN:
                        case MYLABEL:
                        case MYGOTO:
                        case MYREAD:
                        case MYWRITE:
                        case MYARG:
                            if(strcmp(q->u.op_single.op->u.value, target) == 0)
                                strcpy(q->u.op_single.op->u.value, instead);
                            break;
                        case MYASSIGN:
                        case MYCALL:
                            if(strcmp(q->u.op_assign.left->u.value, target) == 0)
                                strcpy(q->u.op_assign.left->u.value, instead);
                            if(strcmp(q->u.op_assign.right->u.value, target) == 0)
                                strcpy(q->u.op_assign.right->u.value, instead);
                            break;
                        case MYDEC:
                            if(strcmp(q->u.op_dec.op->u.value, target) == 0)
                                strcpy(q->u.op_dec.op->u.value, instead);
                            break;
                        case MYADD:
                        case MYSUB:
                        case MYMUL:
                        case MYDIV:
                            if(strcmp(q->u.op_binary.op1->u.value, target) == 0)
                                strcpy(q->u.op_binary.op1->u.value, instead);
                            if(strcmp(q->u.op_binary.op2->u.value, target) == 0)
                                strcpy(q->u.op_binary.op2->u.value, instead);
                            if(strcmp(q->u.op_binary.result->u.value, target) == 0)
                                strcpy(q->u.op_binary.result->u.value, instead);
                            break;
                        case MYIFGOTO:
                            if(strcmp(q->u.op_triple.x->u.value, target) == 0)
                                strcpy(q->u.op_triple.x->u.value, instead);
                            if(strcmp(q->u.op_triple.y->u.value, target) == 0)
                                strcpy(q->u.op_triple.y->u.value, instead);
                            if(strcmp(q->u.op_triple.label->u.value, target) == 0)
                                strcpy(q->u.op_triple.label->u.value, instead);
                            break;
                        default:
                            break;
                    }
                    q = q->next;
                }
            }
        }
        p = p->next;
    }
}
