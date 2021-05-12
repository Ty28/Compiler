#include "extern.h"
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
    if(strcmp(n0->name, "ID")) {
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
    if(strcmp(n0->name, "ID")) {
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
    
}