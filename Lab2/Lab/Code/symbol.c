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