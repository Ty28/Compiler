#include "extern.h"
char* int2String(int num,char *str)
{
	int i = 0;
	if(num<0)
	{
		num = -num;
		str[i++] = '-';
	} 
	do
	{
		str[i++] = num%10+48;
		num /= 10;
	}while(num);
	str[i] = '\0';
	int j = 0;
	if(str[0]=='-')
	{
		j = 1;
		++i;
	}
	for(;j<i/2;j++)
	{
		str[j] = str[j] + str[i-1-j];
		str[i-1-j] = str[j] - str[i-1-j];
		str[j] = str[j] - str[i-1-j];
	} 
	return str;
}

int calculateSize(Type type) {
    if(type->kind == BASIC) 
        return 4;
    else if(type->kind == ARRAY) 
        return type->u.array.size * calculateSize(type->u.array.elem);
    else if(type->kind == STRUCTVAR) {
        int size = 0;
        FieldList p = type->u.structure;
        while(p) {
            size += calculateSize(p->type);
            p = p->tail;
        }
        return size;
    }
}

void insertCode(InterCode code) {
    if(head == NULL) {
        head = code;
        tail = code;
        head->next = head->prev = NULL;
    }
    else {
        tail->next = code;
        code->prev = tail;
        code->next = NULL;
        tail = tail->next;
    }
}

InterCode createCode() {
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
    code->next = code->prev = NULL;
}

Operand createOpTmp() {
    tNum ++;
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = TEMPVAR;
    strcpy(res->u.value, "tt");
    char str[CHARMAXSIZE];
    int2String(tNum, str);
    strcat(res->u.value, str);
    return res;
}

Operand createOpLabel() {
    labelNum ++;
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = LABEL;
    strcpy(res->u.value, "label");
    char str[CHARMAXSIZE];
    int2String(labelNum, str);
    strcat(res->u.value, str);
    return res;
}
Operand copyOpLabel(int num) {
    Operand res = (Operand)malloc(sizeof(struct Operand_));
    res->kind = LABEL;
    strcpy(res->u.value, "label");
    char str[CHARMAXSIZE];
    int2String(num, str);
    strcat(res->u.value, str);
    return res;
}
void initInterCode(node root) {
    head = tail = NULL;
    tNum = labelNum = 0;
    translateProgram(root);
}

void translateProgram(node root) {
    translateExtDefList(root->child);
}

void translateExtDefList(node root) {
    if(root == NULL)
        return ;
    translateExtDef(root->child);
    translateExtDefList(root->child->sibling);
}

void translateExtDef(node root) {
    node n1 = getKChild(root, 1);
    node n2 = getKChild(root, 2);
    if(strcmp(n1->name, "FunDec") == 0) {
        translateFunDec(n1);
        translateCompst(n2);
    }
}

void translateFunDec(node root) {
    Operand op_tmp = (Operand)malloc(sizeof(struct Operand_));
    op_tmp->kind = VARIABLE;
    strcpy(op_tmp->u.value, root->child->val);
    InterCode code = createCode();
    code->kind = FUNCTION;
    code->u.op_single.op = op_tmp;
    insertCode(code);
    if(getChildNum(root) == 4)
        translateVarList(getKChild(root, 2));
}

void translateVarList(node root) {
    translateParamDec(root->child);
    if(getChildNum(root) > 1)
        translateVarList(getKChild(root, 2));
}

void translateParamDec(node root) {
    translateVarDec_A(getKChild(root, 1));
    return ;
}
// FunDec: VarDec
void translateVarDec_A(node root) {
    node n0 = getKChild(root, 0);
    if(strcmp(n0->name, "ID") == 0) {
        Symbol findTuple = findSymbol(n0->val);
        Operand op_tmp = (Operand)malloc(sizeof(struct Operand_));
        op_tmp->kind = VARIABLE;
        strcpy(op_tmp->u.value, n0->val);
        InterCode code = createCode();
        code->kind = MYPARAM;
        code->u.op_single.op = op_tmp;
        insertCode(code);
        if(findTuple->type->kind == ARRAY) {
            //TODO1: mutil-dimensional array(should pass, because params only have 1d-array)
            //TODO2: params of 1d-array 
        }
        else if(findTuple->type->kind == STRUCTURE || findTuple->type->kind == STRUCTVAR) {
            printf("Cannot translate: Code contains variables or paraneters of structure type\n");
        }
    }
}
//Local Variable: VarDec
void translateVarDec_B(node root) {
    node n0 = getKChild(root, 0);
    if(strcmp(n0->name, "ID") == 0) {
        Symbol findTuple = findSymbol(n0->val);
        if(findTuple->type->kind == STRUCTURE || findTuple->type->kind == STRUCTVAR) {
            printf("Cannot translate: Code contains variables or paraneters of structure type\n");
        }
        else if(findTuple->type->kind == ARRAY) {
            if(findTuple->type->kind == ARRAY) {
                //TODO3: mutil-dimensional array 
            }
            else {
                int size = calculateSize(findTuple->type);
                Operand op_tmp = (Operand)malloc(sizeof(struct Operand_));
                op_tmp->kind = VARIABLE;
                strcpy(op_tmp->u.value, n0->val);
                InterCode code = createCode();
                code->kind = MYDEC;
                code->u.op_dec.op = op_tmp;
                code->u.op_dec.size = size;
                insertCode(code);
            }
        }
    }
    else 
        translateVarDec_B(n0);
}

void translateCompst(node root) {
    translateDefList_A(getKChild(root, 1));
    translateStmtList(getKChild(root, 2));
}
// DefList in Function
void translateDefList_A(node root) {
    if(root != NULL) {
        translateDef_A(getKChild(root, 0));
        translateDefList_A(getKChild(root, 1));
    }
}

void translateDef_A(node root) {
    translateDecList_A(getKChild(root, 1));
}

void translateDecList_A(node root) {
    if(getChildNum(root) == 1) 
        translateDec_A(getKChild(root, 0));
    else {
        translateDec_A(getKChild(root, 0));
        translateDecList_A(getKChild(root, 2));
    }
}

void translateDec_A(node root) {
    if(getChildNum(root) == 1)
        translateVarDec_B(getKChild(root, 0));
    else {
        Operand op_left = (Operand)malloc(sizeof(struct Operand_));
        op_left->kind = VARIABLE;
        strcpy(op_left->u.value, root->child->child->val);
        Operand op_right = createOpTmp();
        translateExp(getKChild(root, 2), op_right);
        InterCode code = createCode();
        code->kind = MYASSIGN;
        code->u.op_assign.left = op_left;
        code->u.op_assign.right = op_right;
        insertCode(code);
        if(op_right->kind == CONSTANT || op_right->kind == COSNTVAR) {
            // TODO
        }
    }
    
}



void translateStmtList(node root) {
    if(root != NULL) {
        translateStmt(getKChild(root, 0));
        translateStmtList(getKChild(root, 1));
    }
}

void translateStmt(node root) {
    node n0 = getKChild(root, 0);
    if(strcmp(n0->name, "Exp") == 0){
        Operand op = (Operand)malloc(sizeof(struct Operand_));
        op->kind = NOTHING;
        translateExp(n0, op);
    }
    else if(strcmp(n0->name, "Compst") == 0)
        translateCompst(n0);
    else if(strcmp(n0->name, "RETURN") == 0) {
        Operand op = createOpTmp();
        node n1 = getKChild(root, 1);
        translateExp(n1, op);
        InterCode code = createCode();
        code->kind = MYRETURN;
        code->u.op_single.op = op;
        insertCode(code);
    }
    else if(strcmp(n0->name, "IF") == 0) {
        // IF LP EXP RP STMT
        if(getChildNum(root) == 5) {
            Operand op_label1 = createOpLabel();
            int label1 = labelNum;
            Operand op_label2 = createOpLabel();
            int label2 = labelNum;
            
            node n2 = getKChild(root, 2);
            translateCond(n2, label1, label2);

            InterCode code1 = createCode();
            code1->kind = MYLABEL;
            code1->u.op_single.op = op_label1;
            insertCode(code1);

            //increase cnt2
            node n4 = getKChild(root, 4);
            translateStmt(n4);
            //decrease cnt2

            InterCode code2 = createCode();
            code2->kind = MYLABEL;
            code2->u.op_single.op = op_label2;
            insertCode(code2);
        }
        // IF LP EXP RP STMT ELSE STMT
        else {
            Operand op_label1 = createOpLabel();
            int label1 = labelNum;
            Operand op_label2 = createOpLabel();
            int label2 = labelNum;
            Operand op_label3 = createOpLabel();
            int label3 = labelNum;
            
            node n2 = getKChild(root, 2);
            translateCond(n2, label1, label2);

            InterCode code1 = createCode();
            code1->kind = MYLABEL;
            code1->u.op_single.op = op_label1;
            insertCode(code1);

            //increase cnt2
            node n4 = getKChild(root, 4);
            translateStmt(n4);
            //decrease cnt2

            InterCode code2 = createCode();
            code2->kind = MYGOTO;
            Operand op_tmp3 = copyOpLabel(label3);
            code2->u.op_single.op = op_tmp3;
            insertCode(code2);

            InterCode code3 = createCode();
            code3->kind = MYLABEL;
            code3->u.op_single.op = op_label2;
            insertCode(code3);

            //increase cnt2
            node n6 = getKChild(root, 6);
            translateStmt(n6);
            //decrease cnt2

            InterCode code4 = createCode();
            code4->kind = MYLABEL;
            code4->u.op_single.op = op_label3;
            insertCode(code4);
        }
    }
    // WHILE LP EXP RP STMT (unfinished)
    else {
        Operand op_label1 = createOpLabel();
        int label1 = labelNum;
        Operand op_label2 = createOpLabel();
        int label2 = labelNum;
        Operand op_label3 = createOpLabel();
        int label3 = labelNum;

        InterCode code1 = createCode();
        code1->kind = MYLABEL;
        code1->u.op_single.op = op_label1;
        insertCode(code1);

        //increase cnt1
        node n2 = getKChild(root, 2);
        translateCond(n2, label2, label3);
        //decrease cnt2

        InterCode code2 = createCode();
        code2->kind = MYLABEL;
        Operand op_tmp3 = copyOpLabel(label3);
        code2->u.op_single.op = op_tmp3;
        insertCode(code2);

    }
}

void translateExp(node root, Operand op) {
    
}

void translateCond(node root, int label_true, int label_false) {
    
}