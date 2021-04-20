#include "semantic.h"

int semanticCheck(node root)
{
    // printf("HAHA, Let's begin the semantic check\n");
    // printNode(root);
    symbolTable = createSymbolTable();
    structSymbolTable = createStructTable();
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
    semLog("HAHA, Let's check the Program\n");
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
    if (type->kind == ERROR)
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
            Symbol VarDecTuple = createTupleWithType(IDNode->val, newTupleType);
            insertTuple(VarDecTuple);
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
        //if decType is structure define type,we need to process it
        Type newFuncType = StructVarCopy(decType);
        FuncList varDecParam = createParamWithType(IDNode->val, newFuncType);
        //we also need to insert the parameter into our symbol table,BUT NOT NOW
        return varDecParam;
    }
    else if (strcmp(root->child->name, "VarDec") == 0)
    {
        FuncList varDecParam = FuncVarDec(root->child, decType);
        if (varDecParam != NULL)
        {
            Type lastArrayType = varDecParam->type;
            int arraySize = atoi(getKChild(root, 2)->val);
            //printf("last size:%d\n", arraySize);
            Type newArrayType = createArrayType(lastArrayType, arraySize);
            varDecParam->type = newArrayType;
        }
        return varDecParam;
    }
    else
    {
        semLog("some wrong with VarDec syntax");
        return NULL;
    }
}

FieldList StructVarDec(node root, Type decType)
{
    semLog("start parsing StructVarDec");
    if (strcmp(root->child->name, "ID") == 0)
    {
        node IDNode = root->child;
        //judge whether the val of this struct member exist in our symbol table
        if (0 && findSymbol(IDNode->val) != NULL)
        {
            semLog(root->child->val);
            errorOutput(3, root->child->lineno, IDNode->val);
            //return NULL;
        }
        //and use findMember to judge whether it exists in structSymbolTable
        if (findMember(IDNode->val))
        {
            semLog(root->child->val);
            errorOutput(15, root->child->lineno, IDNode->val);
        }
        Type newFieldType = StructVarCopy(decType);
        //if decType is structure define,we need to process it
        FieldList varDecField = createFieldWithType(IDNode->val, newFieldType);
        semLog("create field, and we don't need to insert");
        return varDecField;
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

//TO MENTION:return value changed into errorType(not NULL)
Type Tag(node root)
{
    node IDNode = root->child;
    //printf("IDNode->name:%s\n", IDNode->name);
    Symbol findTuple = findSymbol(IDNode->val);
    if (findTuple == NULL || findTuple->type->kind != STRUCTURE)
    {
        errorOutput(17, IDNode->lineno, IDNode->val);
        return createErrorType(17);
    }
    else
        return findTuple->type;
}

//REVISED 2021/4/20 20:35 add operations of structSymbolTable
Type OptTag(node root)
{
    semLog("start parsing OptTag(or \'LC\' if it is epsilon)");
    //printf("root:%s",root->name);
    node defListNode = root;
    if (strcmp(root->name, "OptTag") == 0)
        defListNode = root->sibling->sibling;
    else if (strcmp(root->name, "LC") == 0)
        defListNode = root->sibling;
    //link the members and return member head
    structSymbolTable = createStructTable();
    FieldList structMemberHead = StructDefList(defListNode);
    freeStructTable();
    //note:we need to initialize structSymbolTable and free it during each turn
    //and then create struct type with fieldlist,as is shown below
    Type newStructType = createStructType(structMemberHead, 0);
    if (root->child != NULL) //the struct type has name
    {
        semLog("struct type has name");
        Symbol findTuple = findSymbol(root->child->val);
        if (findTuple != NULL) //struct type name conflict
        {
            errorOutput(16, root->lineno, root->child->val);
            return createErrorType(16);
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

//TO MENTION return errorType changed(-1)
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
        return createErrorType(-1);
    }
}

//TO MENTION(recursive errorType)
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
    if (decListType->kind == ERROR) //it means specifier error happens
        return;
    DecList(getKChild(root, 1), decListType);
}

int existInFieldList(char *name, FieldList fieldHead)
{
    FieldList current = fieldHead;
    while (current != NULL)
    {
        if (strcmp(name, current->name) == 0)
            return 1;
        current = current->tail;
    }
    return 0;
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
        FieldList fieldTail = fieldHead;
        while (fieldTail->tail != NULL)
            fieldTail = fieldTail->tail;
        fieldTail->tail = fieldNext;
    }
    return fieldHead;
}

//NEED TO PROCESS/
FieldList StructDef(node root)
{
    semLog("start parsing Def of StructSpecifier");
    Type decListType = Specifier(getKChild(root, 0));
    if (decListType->kind == ERROR)
        return NULL;
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
    Symbol newDec = VarDec(root->child, decType);
    semLog("VarDec parsing over");
    if (getKChild(root, 1) != NULL)
    {
        Type expType = Exp(getKChild(root, 2));
        if (expType->kind == ERROR || newDec == NULL)
            return; //it means error happens in the Exp besides the ASSIGNOP or in the varDec
        semLog("before equal");
        if (isTypeEqual(newDec->type, expType) == 0)
            errorOutput(5, getKChild(root, 1)->lineno, "");
        // semLog("after equal");
        //segmentation fault?
    }
}

FieldList StructDecList(node root, Type decType)
{
    semLog("starting parsing DecList of StructSpecifier");
    FieldList decFieldHead = StructDec(root->child, decType);
    if (decFieldHead == NULL)
        return NULL; //it means that error happens in decFieldHead
    //represent that Dec has more than one child node,say, Dec with COMMA
    if (getKChild(root, 1) != NULL)
    {
        FieldList laterField = StructDecList(getKChild(root, 2), decType);
        // if (existInFieldList(decFieldHead->name, laterField))
        // {
        //     //it means duplicated name in struct field(duplicated name in one DecList)
        //     errorOutput(15, getKChild(root, 1)->lineno, "");
        //     return NULL;
        // }
        decFieldHead->tail = laterField;
    }
    return decFieldHead;
}

FieldList StructDec(node root, Type decType)
{
    semLog("starting parsing Dec of StructSpecifier");
    if (getKChild(root, 1) != NULL)
    {
        //it means invalid assignment in struct field
        errorOutput(15, getKChild(root, 1)->lineno, "");
    }
    FieldList newDecField = StructVarDec(root->child, decType);
    return newDecField;
}

void FunDec(node root, Type funcSpecifierType)
{
    semLog("start parsing FunDec");
    Symbol findTuple = findSymbol(root->child->val); //first child node is 'ID'
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
    Type funcInstanceType = StructVarCopy(funcSpecifierType);
    Type newFuncType = createFuncType(funcInstanceType, paramList);
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

//NEED TO PROCESS/REVISED 2021/4/19 11:30 paramType corrected
FuncList ParamDec(node root)
{
    Type paramType = Specifier(getKChild(root, 0));
    if (paramType->kind == ERROR) //it means parameter error happends,but should we create an error FuncList
        return NULL;
    FuncList newParam = FuncVarDec(getKChild(root, 1), paramType);
    if (newParam != NULL)
    {
        Type paramType = newParam->type;
        Symbol newParamTuple = createTupleWithType(newParam->name, paramType);
        insertTuple(newParamTuple);
    }
    return newParam;
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
        if (Exp(firstUnitOfStmt)->kind == ERROR)
            return;
    }
    else if (strcmp(firstUnitOfStmt->name, "CompSt") == 0)
    {
        CompSt(firstUnitOfStmt, funcType);
    }
    else if (strcmp(firstUnitOfStmt->name, "RETURN") == 0)
    {
        semLog("judge whether the return value matches\n");
        Type returnValueType = Exp(firstUnitOfStmt->sibling);
        if (returnValueType->kind == ERROR)
            return;
        //printf("returnValue:%d,funcType:%d\n",returnValueType->kind,funcType->kind);
        if (isTypeEqual(funcType, returnValueType) == 0)
        {
            //printf("---funcType:%d,returnValueType:%d---",funcType->kind,returnValueType->kind);
            errorOutput(8, firstUnitOfStmt->lineno, "");
        }
        else
        {
            semLog("return value matches!\n");
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
        semLog("some wrong happened in sytax");
    }
}

// add Exp, 2021-4-17-18:47

Type Exp(node root)
{
    semLog("start parsing Exp");
    int cnt = getChildNum(root);
    node n0 = getKChild(root, 0);
    node n1 = getKChild(root, 1);
    node n2 = getKChild(root, 2);
    node n3 = getKChild(root, 3);
    if (cnt == 1)
    {
        // Exp --> ID
        if (strcmp(n0->name, "ID") == 0)
        {
            //printf("%s\n", n0->val);
            Symbol findTuple = findSymbol(n0->val);
            if (findTuple == NULL)
            {
                errorOutput(1, n0->lineno, n0->val);
                return createErrorType(1);
            }
            else
            {
                // left-hand
                if (findTuple->type->kind != FUNCTION)
                    root->flag = 1;
                if (findTuple->type->kind == STRUCTURE)
                    errorOutput(1, n0->lineno, n0->val);
                return findTuple->type;
            }
        }
        // Exp --> INT
        else if (strcmp(n0->name, "INT") == 0)
        {
            semLog("return type int");
            return createBasicType(1);
        }
        // Exp --> FLOAT
        else if (strcmp(n0->name, "FLOAT") == 0)
        {
            semLog("return type int");
            return createBasicType(2);
        }
    }
    else if (cnt == 2)
    {
        Type t = Exp(n1);
        // Exp --> MINUS Exp
        if (strcmp(n0->name, "MINUS") == 0)
        {
            if (t->kind != BASIC)
            {
                errorOutput(7, n1->lineno, "");
                return createErrorType(7);
            }
            return t;
        }
        // Exp --> NOT Exp
        else if (strcmp(n0->name, "NOT") == 0)
        {
            if (t->kind == BASIC && t->u.basic == 1)
                return t;
            else
            {
                errorOutput(7, n1->lineno, "");
                return createErrorType(7);
            }
        }
    }
    else if (cnt == 3)
    {
        // Exp --> LP Exp RP
        if (strcmp(n0->name, "LP") == 0)
        {
            return Exp(n1);
        }
        // Exp --> ID LP RP
        else if (strcmp(n0->name, "ID") == 0)
        {
            return ExpFunc(root);
        }
        // Exp --> Exp ASSIGNOP Exp
        else if (strcmp(n1->name, "ASSIGNOP") == 0)
        {
            Type t0 = Exp(n0);
            Type t2 = Exp(n2);
            if (isTypeEqual(t0, t2))
            {
                // TODO 1: handle the left hand, maybe modify (FINISHED)
                if (n0->flag)
                {
                    root->flag = 1;
                    return t0;
                }
                else
                {
                    errorOutput(6, root->lineno, "");
                    return createErrorType(6);
                }
            }
            else
            {
                errorOutput(5, n0->lineno, "");
                return createErrorType(5);
            }
        }
        // Exp --> Exp AND Exp | Exp --> Exp OR Exp
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
                return createErrorType(7);
            }
        }
        // Exp --> Exp DOT Exp
        else if (strcmp(n1->name, "DOT") == 0)
        {
            return ExpStruct(root);
        }
        // Exp --> Exp RELOP Exp
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
                return createErrorType(7);
            }
        }
        // Exp --> Exp ADD | SUB | STAR | DIV Exp
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
                return createErrorType(7);
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
    return createErrorType(0);
}
// TODO 2: finish the following function(FINISHED)

// ID LP RP | ID LP Args RP
Type ExpFunc(node root)
{
    node n0 = getKChild(root, 0);
    node n2 = getKChild(root, 2);
    char func[32];
    strcpy(func, n0->val);
    Symbol findTuple = findSymbol(n0->val);
    if (findTuple == NULL)
    {
        errorOutput(2, n0->lineno, n0->val);
        return createErrorType(2);
    }
    else
    {
        // NOT A FUNCTION
        if (findTuple->type->kind != FUNCTION)
        {
            errorOutput(11, n0->lineno, n0->val);
            return findTuple->type;
        }
        // FUNCTION with no Args
        if (getChildNum(root) == 3)
            return findTuple->type->u.function->type;
        else
        {
            if (Args(n2, findTuple->type->u.function->tail))
            {
                return findTuple->type->u.function->type;
            }
            else
            {
                errorOutput(9, n0->lineno, n0->val);
                return findTuple->type->u.function->type;
            }
        }
    }
}
// Exp --> Exp DOT Exp
Type ExpStruct(node root)
{
    node n0 = getKChild(root, 0);
    node n2 = getKChild(root, 2);
    Type t0 = Exp(n0);
    Type t2 = Exp(n2);
    if (t0->kind == STRUCTVAR)
    {
        FieldList p = t0->u.structure;
        while (p)
        {
            if (strcmp(p->name, n2->val) == 0)
                break;
            p = p->tail;
        }
        if (p)
        {
            root->flag = 1;
            return p->type;
        }
        else
        {
            errorOutput(14, root->lineno, n2->val);
            return createErrorType(14);
        }
    }
    else if (t0->kind == STRUCTURE)
    {
        errorOutput(1, n0->lineno, n0->val);
        return createErrorType(1);
    }
    else
    {
        errorOutput(13, n0->lineno, "");
        return createErrorType(13);
    }
}

// Exp LB Exp RB
Type ExpArray(node root)
{
    node n0 = getKChild(root, 0);
    node n2 = getKChild(root, 2);
    Type t0 = Exp(n0);
    Type t2 = Exp(n2);
    if (t0->kind != ARRAY)
    {
        errorOutput(10, n0->lineno, n0->val);
        return createErrorType(10);
    }
    if (t2->kind != BASIC || t2->u.basic != 1)
    {
        errorOutput(12, n0->lineno, n0->val);
        // printf("%d \n",  t0->u.array.elem->u.basic);
        root->flag = 1;
        return t0->u.array.elem;
    }
    root->flag = 1;
    return t0->u.array.elem;
}

int Args(node root, FuncList params)
{
    while (getChildNum(root) > 1)
    {
        if (params == NULL || !isTypeEqual(Exp(root->child), params->type))
            return 0;
        root = getKChild(root, 2);
        params = params->tail;
    }
    if (params == NULL || !isTypeEqual(Exp(root->child), params->type) || params->tail)
        return 0;
    return 1;
}