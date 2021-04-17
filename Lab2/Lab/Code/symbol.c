#include "extern.h"

unsigned int hashProject(char *name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~HASHSIZE)
            val = (val ^ (i >> 12)) & HASHSIZE;
    }
    return val;
}

Symbol *createSymbolTable() //the elements of our Hashtable are pointers
{
    Symbol *tableHead = (Symbol *)malloc(HASHSIZE * sizeof(Symbol *));
    for (int i = 0; i < HASHSIZE; i++) //initialize
    {
        tableHead[i] = NULL;
    }
    return tableHead;
}

Type createBasicType(int _basic)
{
    Type tupleType = (Type)malloc(sizeof(struct Type_));
    tupleType->kind = BASIC;
    tupleType->u.basic = _basic;
    return tupleType;
}

Type createArrayType(Type _elem, int _size)
{
    Type tupleType = (Type)malloc(sizeof(struct Type_));
    tupleType->kind = ARRAY;
    tupleType->u.array.elem = _elem;
    tupleType->u.array.size = _size;
    return tupleType;
}

Type createStructType(FieldList _structure, int isVariable)
{
    Type tupleType = (Type)malloc(sizeof(struct Type_));
    if (isVariable)
        tupleType->kind = STRUCTVAR;
    else
        tupleType->kind = STRUCTURE;
    tupleType->u.structure = _structure;
    return tupleType;
}

Type createFuncType(FuncList _parameter)
{
    Type tupleType = (Type)malloc(sizeof(struct Type_));
    tupleType->kind = FUNCTION;
    tupleType->u.function = _parameter;
    return tupleType;
}

Type createType(int _kind, int _basic, Type _elem, int _size,
                FieldList _structure, FuncList _function, int isVariable)
{
    switch (_kind)
    {
    case (0):
        return createBasicType(_basic);
    case (1):
        return createArrayType(_elem, _size);
    case (2):
        return createStructType(_structure, isVariable);
    case (3):
        return createFuncType(_function);
    }
}

Symbol createBlankTuple(char *name)
{
    Symbol newTuple = (Symbol)malloc(sizeof(struct SymbolTuple));
    strcpy(newTuple->name, name);
    newTuple->hashLink = NULL;
    return newTuple;
}

FieldList createBlankField(char *name)
{
    FieldList newField = (FieldList)malloc(sizeof(struct FieldList_));
    strcpy(newField->name, name);
    newField->tail = NULL;
    return newField;
}

FieldList createFieldWithType(char *name, Type _type)
{
    FieldList newField = createBlankField(name);
    newField->type = _type;
    return newField;
}

Symbol createBasicTuple(char *name, int _basic)
{
    Type tupleType = createBasicType(_basic);
    Symbol newTuple = createBlankTuple(name);
    newTuple->type = tupleType;
    return newTuple;
}

Symbol createArrayTuple(char *name, Type _elem, int _size)
{
    Type tupleType = createArrayType(_elem, _size);
    Symbol newTuple = createBlankTuple(name);
    newTuple->type = tupleType;
    return newTuple;
}

Symbol createStructTuple(char *name, FieldList _structure, int isVariable)
{
    Type tupleType = createStructType(_structure, isVariable);
    Symbol newTuple = createBlankTuple(name);
    newTuple->type = tupleType;
    return newTuple;
}

Symbol createFuncTuple(char *name, FuncList _parameter)
{
    Type tupleType = createFuncType(_parameter);
    Symbol newTuple = createBlankTuple(name);
    newTuple->type = tupleType;
    return newTuple;
}

Symbol createTupleWithType(char *name, Type _type)
{
    Symbol newTuple = createBlankTuple(name);
    newTuple->type = _type;
    return newTuple;
}

Symbol findSymbol(char *name)
{
    unsigned int hashID = hashProject(name);
    if (symbolTable[hashID] != NULL)
    {
        Symbol current = symbolTable[hashID];
        while (current != NULL)
        {
            if (strcmp(current->name, name) == 0) //loop until we find that name
            {
                return current;
            }
            current = current->hashLink;
        }
    }
    return NULL; //if that name does not exist in our table, return NULL
}

void insertTuple(Symbol tuple)
{
    Symbol find = findSymbol(tuple->name);
    if (find != NULL)
        return;
    unsigned int hashID = hashProject(tuple->name);
    if (symbolTable[hashID] == NULL)
    {
        symbolTable[hashID] = tuple; //make the NULL pointer pointed to the tuple
        return;
    }
    Symbol current = symbolTable[hashID]->hashLink;
    while (current->hashLink != NULL)
        current = current->hashLink;
    current->hashLink = tuple;
}

int isTypeEqual(Type t1, Type t2) {
    if(t1->kind != t2->kind)
        return 0;
    if(t1->kind == BASIC)
        if(t1->u.basic == t2->u.basic)
            return 1;
    else if(t1->kind == ARRAY)
        if(isTypeEqual(t1->u.array.elem, t2->u.array.elem) == 1)
            return 1;
    else if(t1->kind == STRUCTURE || t1->kind == STRUCTVAR) 
        if(isStructEqual(t1->u.structure, t2->u.structure) == 1)
            return 1;
    else if(t1->kind == FUNCTION) 
        if(isFuncEqual(t1->u.function, t2->u.function) == 1)
            return 1;
    return 0;
}

int isStructEqual(FieldList f1, FieldList f2) {
    if(f1 == NULL && f2 == NULL)
        return 1;
    else if(f1 == NULL || f2 == NULL)
        return 0;
    if(isTypeEqual(f1->type, f2->type) == 1 && isStructEqual(f1->tail, f2->tail) == 1)
        return 1;
    else
        return 0;
}

int isFuncEqual(FuncList f1, FuncList f2) {
    if(f1 == NULL && f2 == NULL)
        return 1;
    else if(f1 == NULL || f2 == NULL)
        return 0;
    if(strcmp(f1->name, f2->name) == 0 && isTypeEqual(f1->type, f2->type) == 1)
        return isFuncEqual(f1->tail, f2->tail);
    else 
        return 0;
}