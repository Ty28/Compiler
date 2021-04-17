#include "semantic.h"

int semanticCheck(node root)
{
    // printf("HAHA, Let's begin the semantic check\n");
    // printNode(root);
    symbolTable = createSymbolTable();
    Program(root);
}

void semLog(char *msg)
{
#ifdef semanticdebug
    printf("%s\n", msg);
#endif
}

void errorOutput(int errorType, int line, char* msg)
{   
    switch (errorType)
    {
    case 1:
        printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", line, msg);
        break;
    case 2:
        printf("Error type 2 at Line %d: Undefined function \"%s\".\n", line, msg);
        break;
    case 3:
        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", line, msg);
        break;
    case 4:
        printf("Error type 4 at Line %d: Redefined function \"%s\".\n", line, msg);
        break;
    case 5:
        printf("Error type 5 at Line %d: Type mismatched for assignment.\n", line);
        break;
    case 6:
        printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", line);
        break;
    case 7:
        printf("Error type 7 at Line %d: Type mismatched for operands.\n", line);
        break;    
    case 8:
        printf("Error type 8 at Line %d: Type mismatched for return.\n", line);
        break;  
    case 9:
        // TODO: complete func name and params
        printf("Error type 9 at Line %d: Function \"func(int)\" is not applicable for arguments \"(int, int)\".\n", line);
        break;
    case 10:
        printf("Error type 10 at Line %d: \"%s\" is not an array.\n", line, msg);
        break;
    case 11: 
        printf("Error type 11 at Line %d: \"%s\" is not a function.\n", line, msg);
        break;
    case 12:
        printf("Error type 12 at Line %d: \"%s\" is not an integer.\n", line, msg);
        break;
    case 13: 
        printf("Error type 13 at Line %d: Illegal use of \".\".\n", line);
        break;
    case 14:
        printf("Error type 14 at Line %d: Non-existent field \"%s\".\n", line, msg);
        break;
    case 15: 
        printf("Error type 15 at Line %d: Non-existent field \"%s\".\n", line, msg);
        break;
    case 16:
        printf("Error type 16 at Line %d: Duplicated name \"%s\".\n", line, msg);
        break;
    case 17:
        printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", line, msg);
        break;
    default:
        // check whether errorType is valid, do not use like this: errorOutput(123, 1);
        printf("Error type UNKNOWN at Line %d\n", line);
        break;
    }
}

void Program(node root)
{
    printf("HAHA, Let's check the Program\n");
    ExtDefList(getKChild(root, 0));
}

void ExtDefList(node root)
{
    if (!root)
        return;
    //semLog("HAHA, Let's check the ExtDefList");
    ExtDef(getKChild(root, 0));
    ExtDefList(getKChild(root, 1));
}

void ExtDef(node root)
{
    //semLog("HAHA, Let's check the ExtDef");
    // need to complete
    Type type = Specifier(getKChild(root, 0));
    if (strcmp(getKChild(root, 1)->name, "ExtDecList") == 0)
    {
        ExtDecList(getKChild(root, 1), type);
    }
    else if (strcmp(getKChild(root, 1)->name, "SEMI") == 0)
    {
        ;
    }
    else if (strcmp(getKChild(root, 1)->name, "FunDec") == 0)
    {
        //FunDec(getKChild(root, 1), type);
        //Compst(getKChild(root, 2), type);
    }
}

void ExtDecList(node root, Type extDecType)
{
    semLog("start parsing ExtDecList");
    VarDec(root->child, extDecType);
    //represent that ExtDecList has more than one child node,say, VarDec with COMMA
    if (getKChild(root, 1) != NULL)
        ExtDecList(getKChild(root, 2), extDecType);
}

Symbol VarDec(node root, Type decType)
{
    semLog("start parsing VarDec");
    if (strcmp(root->child->name, "ID") == 0)
    {
        node IDNode = root->child;
        if (findSymbol(IDNode->val) != NULL)
        {
            semLog(root->child->val);
            errorOutput(3, root->child->lineno, IDNode->val);
            return NULL;
        }
        else
        {
            Symbol VarDecTuple = createTupleWithType(IDNode->val, decType);
            semLog("insertTuple(VarDecTuple)");
            insertTuple(VarDecTuple);
            semLog("insert success!");
            return VarDecTuple;
        }
    }
    else if (strcmp(root->child->name, "VarDec") == 0)
    {
        Symbol varDecTuple = VarDec(root->child, decType);
        if (varDecTuple != NULL)
        {
            Type lastArrayType = varDecTuple->type;
            int arraySize = atoi(getKChild(root, 2)->val);
            //printf("last size:%d\n",arraySize);
            Type newArrayType = createArrayType(lastArrayType, arraySize);
            varDecTuple->type = newArrayType;
        }
        return varDecTuple;
    }
    else
    {
        semLog("some wrong with VarDec syntax");
    }
}

FieldList StructVarDec(node root, Type decType)
{
    semLog("start parsing VarDec");
    if (strcmp(root->child->name, "ID") == 0)
    {
        node IDNode = root->child;
        //judge whether the val of this struct member exist in our symbol table
        //and TODO:I think we also need to judge whether it exists in the fieldLists
        if (findSymbol(IDNode->val) != NULL)
        {
            semLog(root->child->val);
            errorOutput(3, root->child->lineno, IDNode->val);
            return NULL;
        }
        else
        {
            if(decType->kind==STRUCTURE)
                decType->kind = STRUCTVAR; //we need to change the struct type into struct variable
            FieldList varDecField = createFieldWithType(IDNode->val, decType);
            semLog("create field,and we don't need to insert");
            return varDecField;
        }
    }
    else if (strcmp(root->child->name, "VarDec") == 0)
    {
        FieldList varDecField = StructVarDec(root->child, decType);
        if (varDecField != NULL)
        {
            Type lastArrayType = varDecField->type;
            int arraySize = atoi(getKChild(root, 2)->val);
            //printf("last size:%d\n",arraySize);
            Type newArrayType = createArrayType(lastArrayType, arraySize);
            varDecField->type = newArrayType;
        }
        return varDecField;
    }
    else
    {
        semLog("some wrong with VarDec syntax");
    }
}

Type Tag(node root)
{
    node IDNode = root->child;
    //printf("IDNode->name:%s\n", IDNode->name);
    Symbol findTuple = findSymbol(IDNode->val);
    if (findTuple == NULL)
    {
        errorOutput(1, IDNode->lineno, IDNode->val);
        return NULL;
    }
    else
        return findTuple->type;
}

Type OptTag(node root)
{
    //get DefList
    node defListNode = root->sibling->sibling;
    //link the members and return member head
    FieldList structMemberHead = StructDefList(defListNode);
    //now create struct type with fieldlist
    Type newStructType = createStructType(structMemberHead, 0);
    if (root->child != NULL) //the struct type has name
    {
        semLog("struct type has name");
        //printf("his name is %s\n", root->child->val);
        Symbol findTuple = findSymbol(root->child->val);
        if (findTuple != NULL) //struct type name conflict
        {
            errorOutput(16, root->lineno, root->child->val);
            return NULL;
        }
        Symbol newStructTuple = createTupleWithType(root->child->val, newStructType);
        insertTuple(newStructTuple);
    }
    else //the struct type doesn't have name
    {
        semLog("struct type doesn't have name");
        //do not need to insert into hashTable , just return type is OKAY
    }
    return newStructType;
}

Type StructSpecifier(node root)
{
    semLog("start parsing StructSpecifier\n");
    node tagNode = getKChild(root, 1);
    // node current = getKChild(root, 0);
    // while (current != NULL)
    // {
    //     printf("%s ",current->name);
    //     current=current->sibling;
    // }
    // printf("\n");
    if (strcmp(tagNode->name, "Tag") == 0)
    {
        semLog("start parsing Tag\n");
        return Tag(tagNode);
    }
    else
    {
        semLog("start parsing OptTag\n");
        return OptTag(tagNode);
    }
}

Type Specifier(node root)
{
    semLog("start parsing specifier\n");
    node typeNode = getKChild(root, 0);
    semLog(typeNode->name);
    if (strcmp(typeNode->name, "TYPE") == 0) //if specifier induces TYPE
    {
        if (strcmp(typeNode->val, "int") == 0)
        {
            semLog("create type int");
            return createBasicType(1);
        }
        else if (strcmp(typeNode->val, "float") == 0)
        {
            semLog("create type float");
            return createBasicType(2);
        }
    }
    else if (strcmp(typeNode->name, "StructSpecifier") == 0)
        return StructSpecifier(getKChild(root, 0));
    else
    {
        printf("well,something wrong with lexical parsing\n");
        return NULL;
    }
}

void Def(node root)
{
    Type decListType = Specifier(getKChild(root, 0));
    DecList(getKChild(root, 1), decListType);
}

void DefList(node root)
{
    if (!root || !root->child)
        return;
    Def(getKChild(root, 0));
    DefList(getKChild(root, 1));
}

FieldList StructDefList(node root)
{
    semLog("starting parsing DefList of StructSpecifier");
    //printf("StructDefList root:%s\n", root->name);
    if (root == NULL || root->child == NULL)
        return NULL;
    FieldList fieldHead = StructDef(root->child);
    if (fieldHead == NULL)
        return NULL; //this means that semantic error happens in fieldHead;
    if (getKChild(root, 1) != NULL)
    {
        FieldList fieldNext = StructDefList(getKChild(root, 1));
        fieldHead->tail = fieldNext;
    }
    return fieldHead;
}

FieldList StructDef(node root)
{
    semLog("starting parsing Def of StructSpecifier");
    Type decListType = Specifier(getKChild(root, 0));
    return StructDecList(getKChild(root, 1), decListType);
}

void DecList(node root, Type decType)
{
    Dec(root->child, decType);
    //represent that Dec has more than one child node,say, Dec with COMMA
    if (getKChild(root, 1) != NULL)
        DecList(getKChild(root, 2), decType);
}

void Dec(node root, Type decType)
{
    VarDec(root, decType);
}

FieldList StructDecList(node root, Type decType)
{
    semLog("starting parsing DecList of StructSpecifier");
    FieldList decFieldHead = StructDec(root->child, decType);
    if (decFieldHead == NULL)
        return NULL; //it means that error happens in decFieldHead
    //represent that Dec has more than one child node,say, Dec with COMMA
    if (getKChild(root, 1) != NULL)
        decFieldHead->tail = StructDecList(getKChild(root, 2), decType);
    return decFieldHead;
}

FieldList StructDec(node root, Type decType)
{
    semLog("starting parsing Dec of StructSpecifier");
    return StructVarDec(root->child, decType);
    //TODO:we also need to finish EXPRESSION
}

// add Exp, 2021-4-17-18:47

Type Exp(node root) {
    int cnt = getChildNum(root);
    node n0 = getKChild(root, 0);
    node n1 = getKChild(root, 1);
    node n2 = getKChild(root, 2);
    node n3 = getKChild(root, 3);
    if(cnt == 1) {
        if(strcmp(n0->name, "ID") == 0) {
            printf("%s\n", n0->val);
            Symbol findTuple = findSymbol(n0->val);
            if (findTuple == NULL) {
                errorOutput(1, n0->lineno, n0->val);
                return NULL;
            }
            else {
                return findTuple->type;
            }
        }
        else if(strcmp(n0->name, "INT") == 0) {
            semLog("return type int");
            return createBasicType(1);
        }
        else if(strcmp(n0->name, "FLOAT") == 0) {
            semLog("return type int");
            return createBasicType(2);
        }
    }
    else if(cnt == 2) {
        Type t = Exp(n1);
        if(strcmp(n0->name, "MINUS") == 0) {
            if(t->kind != BASIC) {
                errorOutput(7, n1->lineno, "");
                return NULL;
            }
            return t;
        }
        else if(strcmp(n0->name, "NOT") == 0) {
            if(t->kind == BASIC && t->u.basic == 1)
                return t;
            else {
                errorOutput(7, n1->lineno, "");
                return NULL;
            }   
        }
    }
    else if(cnt == 3) {
        if(strcmp(n0->name, "LP") == 0) { 
            return Exp(n1);
        }
        else if(strcmp(n0->name, "ID") == 0) { 
            return ExpFunc(root);
        }
        else if(strcmp(n1->name, "ASSIGNOP") == 0) {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if(isTypeEqual(t0, t2)) {
                // TODO 1: handle the left hand, maybe modify Type
                return t0;
            }
            else {
                errorOutput(5, n0->lineno, "");
                return NULL;
            }
        }
        else if(strcmp(n1->name, "AND") == 0 || strcmp(n1->name, "OR") == 0) {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if(t0->kind == BASIC && t0->u.basic == 1 && isTypeEqual(t0, t2)) {
                return t0;
            }
            else {
                errorOutput(7, n0->lineno, "");
                return NULL;
            }
        }
        else if(strcmp(n1->name, "DOT") == 0) {
            // struct
            return ExpStruct(root);
        }
        else if(strcmp(n1->name, "RELOP") == 0){
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if(t0->kind == BASIC && isTypeEqual(t0, t2)) {
                return createBasicType(1);
            }
            else {
                errorOutput(7, n0->lineno, "");
                return NULL;
            }
        }
        else {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if(t0->kind == BASIC && isTypeEqual(t0, t2)) {
                return t0;
            }
            else {
                errorOutput(7, n0->lineno, "");
                return NULL;
            }
        }
    }
    else if(cnt == 4) {
        if(strcmp(n0->name, "ID") == 0) {
            return ExpFunc(root);
        }
        else 
            return ExpArray(root);
    }
    semLog("There's something wrong about Exp!");
    return NULL;
}
// TODO 2: finish the following function

Type ExpFunc(node root) {
    return NULL;
}
Type ExpStruct(node root) {
    return NULL;
}
Type ExpArray(node root) {
    return NULL;
}