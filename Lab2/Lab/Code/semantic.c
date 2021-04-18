#include "semantic.h"

int semanticCheck(node root)
{
    // printf("HAHA, Let's begin the semantic check\n");
    // printNode(root);
    symbolTable = createSymbolTable();
    Program(root);
}

void errorOutput(int errorType, int line, char *msg)
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

Type StructVarCopy(Type structureDecType)
{
    if (structureDecType->kind != STRUCTURE)
        return structureDecType;
    else
        return createStructType(structureDecType->u.structure, 1);
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
    semLog("HAHA, Let's check the ExtDef");
    // need to complete
    Type type = Specifier(getKChild(root, 0));
    if (type == NULL)
        return; //type=NULL means error happened;TODO:also we can choose not to return
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
        FunDec(getKChild(root, 1), type);
        CompSt(getKChild(root, 2), StructVarCopy(type));
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
    if (decType == NULL)
        return NULL;
    semLog("start parsing VarDec");
    semLog(root->child->name);
    if (strcmp(root->child->name, "ID") == 0)
    {
        node IDNode = root->child;
        semLog(IDNode->val);
        if (findSymbol(IDNode->val) != NULL)
        {
            semLog(root->child->val);
            errorOutput(3, root->child->lineno, IDNode->val);
            return NULL;
        }
        else
        {
            semLog("this newVarDec doesn't exist,so we need to insert it into hash table");
            //if decType is struct define type,we need to process it (well, the function name is a little confusing)
            Type newTupleType = StructVarCopy(decType);
            //semLog("copy over");
            Symbol VarDecTuple = createTupleWithType(IDNode->val, newTupleType);
            //semLog("create over");
            insertTuple(VarDecTuple);
            //semLog("insert over");
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

FuncList FuncVarDec(node root, Type decType)
{
    if (decType == NULL)
        return NULL;
    semLog("start parsing FuncVarDec");
    if (strcmp(root->child->name, "ID") == 0)
    {
        node IDNode = root->child;
        //judge whether the val of this formal parameter exist in our symbol table
        if (findSymbol(IDNode->val) != NULL)
        {
            semLog(root->child->val);
            errorOutput(3, root->child->lineno, IDNode->val);
            return NULL;
        }
        else
        {
            //if decType is structure define type,we need to process it
            Type newFuncType = StructVarCopy(decType);
            FuncList varDecParam = createParamWithType(IDNode->val, newFuncType);
            Symbol ParamTuple = createTupleWithType(IDNode->val, newFuncType);
            //we also need to insert the parameter into our symbol table
            insertTuple(ParamTuple);
            return varDecParam;
        }
    }
    else if (strcmp(root->child->name, "VarDec") == 0)
    {
        FuncList varDecParam = FuncVarDec(root->child, decType);
        if (varDecParam != NULL)
        {
            Type lastArrayType = varDecParam->type;
            int arraySize = atoi(getKChild(root, 2)->val);
            //printf("last size:%d\n",arraySize);
            Type newArrayType = createArrayType(lastArrayType, arraySize);
            varDecParam->type = newArrayType;
        }
        return varDecParam;
    }
    else
    {
        printf("some wrong with VarDec syntax");
    }
}

FieldList StructVarDec(node root, Type decType)
{
    if (decType == NULL)
        return NULL;
    semLog("start parsing StructVarDec");
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
            Type newFieldType = StructVarCopy(decType);
            //if decType is structure define,we need to process it
            FieldList varDecField = createFieldWithType(IDNode->val, newFieldType);
            semLog("create field, and we don't need to insert");
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
    if (findTuple == NULL || findTuple->type->kind != STRUCTURE)
    {
        errorOutput(17, IDNode->lineno, IDNode->val);
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

void DefList(node root)
{
    semLog("start parsing DefList");
    if (!root || !root->child)
        return;
    Def(getKChild(root, 0));
    DefList(getKChild(root, 1));
}

void Def(node root)
{
    semLog("start parsing Def");
    Type decListType = Specifier(getKChild(root, 0));
    if (decListType == NULL)
        return;
    DecList(getKChild(root, 1), decListType);
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
    semLog("start parsing DecList");
    Dec(root->child, decType);
    //represent that Dec has more than one child node,say, Dec with COMMA
    if (getKChild(root, 1) != NULL)
        DecList(getKChild(root, 2), decType);
}

void Dec(node root, Type decType)
{
    semLog("start parsing Dec");
    VarDec(root->child, decType);
    //TODO:
    semLog("VarDec parsing over");
    if (getKChild(root, 1) != NULL)
        Exp(getKChild(root, 2));
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
    ////TODO decList should be linked,stil some error to fix
}

FieldList StructDec(node root, Type decType)
{
    semLog("starting parsing Dec of StructSpecifier");
    return StructVarDec(root->child, decType);
    //TODO:we also need to finish EXPRESSION
}

void FunDec(node root, Type funcDecType)
{
    semLog("start parsing FunDec of StructSpecifier");
    Symbol findTuple = findSymbol(root->child->val);
    if (findTuple != NULL)
    {
        errorOutput(4, root->child->lineno, root->child->val); //func name redefined;
        return;
    }
    FuncList paramList = NULL;
    if (getKChild(root, 3) != NULL) //it means the function has parameters
    {
        node varListNode = getKChild(root, 2); //get VarList
        paramList = VarList(varListNode);
        if (paramList == NULL)
            return;
        //I mean if semantic error happens in the params,we just don't create this func
        //TODO:but we can also create it for later semantic judge?
    }
    Type newFuncType = createFuncType(paramList);
    Symbol newFuncTuple = createTupleWithType(root->child->val, newFuncType);
    insertTuple(newFuncTuple);
}

FuncList VarList(node root)
{
    FuncList paramListHead = ParamDec(root->child);
    if (paramListHead == NULL)
        return NULL; //it means that somthing wrong happens with the parameter
    if (getKChild(root, 1) != NULL)
    {
        node varListNode = getKChild(root, 2);
        paramListHead->tail = VarList(varListNode);
    }
    return paramListHead;
}

FuncList ParamDec(node root)
{
    Type paramType = Specifier(getKChild(root, 0));
    if (paramType == NULL)
        return NULL;
    return FuncVarDec(getKChild(root, 1), paramType);
}

void CompSt(node root, Type funcType)
{
    semLog("start parsing CompSt");
    node defListNode = getKChild(root, 1);
    if (strcmp(defListNode->name, "DefList") == 0)
    {
        DefList(defListNode);
        defListNode = defListNode->sibling;
    }
    semLog("defList parsing over");
    node stmtListNode = defListNode;
    //printf("stmtListNode->name:%s",stmtListNode->name);
    if (strcmp(stmtListNode->name, "StmtList") == 0)
    {
        StmtList(stmtListNode, funcType);
    }
}

void StmtList(node root, Type funcType)
{
    if (root == NULL || root->child == NULL)
        return;
    semLog("start parsing StmtList");
    Stmt(getKChild(root, 0), funcType);
    StmtList(getKChild(root, 1), funcType);
}

void Stmt(node root, Type funcType)
{
    semLog("start parsing stmt");
    node firstUnitOfStmt = getKChild(root, 0);
    if (strcmp(firstUnitOfStmt->name, "Exp") == 0)
    {
        Exp(firstUnitOfStmt);
    }
    else if (strcmp(firstUnitOfStmt->name, "CompSt") == 0)
    {
        CompSt(firstUnitOfStmt, funcType);
    }
    else if (strcmp(firstUnitOfStmt->name, "RETURN") == 0)
    {
        semLog("judge whether the return value matches");
        Type returnValueType = Exp(firstUnitOfStmt->sibling);
        if (isTypeEqual(funcType, returnValueType) == 0)
        {
            //printf("---funcType:%d,returnValueType:%d---",funcType->kind,returnValueType->kind);
            errorOutput(8, 10, "");
        }
        else
        {
            semLog("return value matches!");
        }
    }
    else if (strcmp(firstUnitOfStmt->name, "IF") == 0)
    {
        Exp(getKChild(root, 2));
        Stmt(getKChild(root, 4), funcType);
        if (getChildNum(root) == 7) //to process circumstances of ELSE
        {
            Stmt(getKChild(root, 6), funcType);
        }
    }
    else if (strcmp(firstUnitOfStmt->name, "WHILE") == 0)
    {
        Exp(getKChild(root, 2));
        Stmt(getKChild(root, 4), funcType);
    }
    else
    {
        printf("some wrong happened in sytax");
    }
}

Type Exp(node root)
{
    int cnt = getChildNum(root);
    node n0 = getKChild(root, 0);
    node n1 = getKChild(root, 1);
    node n2 = getKChild(root, 2);
    node n3 = getKChild(root, 3);
    if (cnt == 1)
    {
        if (strcmp(n0->name, "ID") == 0)
        {
            //printf("%s\n", n0->val);
            Symbol findTuple = findSymbol(n0->val);
            if (findTuple == NULL)
            {
                errorOutput(1, n0->lineno, n0->val);
                return NULL;
            }
            else
            {
                return findTuple->type;
            }
        }
        else if (strcmp(n0->name, "INT") == 0)
        {
            semLog("return type int");
            return createBasicType(1);
        }
        else if (strcmp(n0->name, "FLOAT") == 0)
        {
            semLog("return type int");
            return createBasicType(2);
        }
    }
    else if (cnt == 2)
    {
        Type t = Exp(n1);
        if (strcmp(n0->name, "MINUS") == 0)
        {
            if (t->kind != BASIC)
            {
                errorOutput(7, n1->lineno, "");
                return NULL;
            }
            return t;
        }
        else if (strcmp(n0->name, "NOT") == 0)
        {
            if (t->kind == BASIC && t->u.basic == 1)
                return t;
            else
            {
                errorOutput(7, n1->lineno, "");
                return NULL;
            }
        }
    }
    else if (cnt == 3)
    {
        if (strcmp(n0->name, "LP") == 0)
        {
            return Exp(n1);
        }
        else if (strcmp(n0->name, "ID") == 0)
        {
            return ExpFunc(root);
        }
        else if (strcmp(n1->name, "ASSIGNOP") == 0)
        {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if (isTypeEqual(t0, t2))
            {
                // TODO 1: handle the left hand, maybe modify Type
                return t0;
            }
            else
            {
                errorOutput(5, n0->lineno, "");
                return NULL;
            }
            return t0;
        }
        else if (strcmp(n1->name, "AND") == 0 || strcmp(n1->name, "OR") == 0)
        {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if (t0->kind == BASIC && t0->u.basic == 1 && isTypeEqual(t0, t2))
            {
                return t0;
            }
            else
            {
                errorOutput(7, n0->lineno, "");
                return NULL;
            }
        }
        else if (strcmp(n1->name, "DOT") == 0)
        {
            // struct
            return ExpStruct(root);
        }
        else if (strcmp(n1->name, "RELOP") == 0)
        {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if (t0->kind == BASIC && isTypeEqual(t0, t2))
            {
                return createBasicType(1);
            }
            else
            {
                errorOutput(7, n0->lineno, "");
                return NULL;
            }
        }
        else
        {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if (t0->kind == BASIC && isTypeEqual(t0, t2))
            {
                return t0;
            }
            else
            {
                errorOutput(7, n0->lineno, "");
                return NULL;
            }
        }
    }
    else if (cnt == 4)
    {
        if (strcmp(n0->name, "ID") == 0)
        {
            return ExpFunc(root);
        }
        else
            return ExpArray(root);
    }
    semLog("There's something wrong about Exp!");
    return NULL;
}

Type ExpFunc(node root)
{
    return NULL;
}
Type ExpStruct(node root)
{
    return NULL;
}
Type ExpArray(node root)
{
    return NULL;
}