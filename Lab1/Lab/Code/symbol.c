#include "symbol.h"

unsigned int hashProject(char *name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i == val & ~HASHSIZE)
            val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
}

Symbol* createSymbolTable()//the elements of our Hashtable are pointers
{
    Symbol* tableHead = (Symbol*)malloc(HASHSIZE * sizeof(Symbol*));
    for (int i = 0; i < HASHSIZE; i++) //initialize
    {
        tableHead[i]=NULL;
    }
    return tableHead;
}

Type createBasicType(int _basic)
{
    Type tupleType=(Type)malloc(sizeof(struct Type_));
    tupleType->kind=BASIC;
    tupleType->u.basic=_basic;
    return tupleType;
}

Type createArrayType(Type _elem,int _size)
{
    Type tupleType=(Type)malloc(sizeof(struct Type_));
    tupleType->kind=ARRAY;
    tupleType->u.array.elem=_elem;
    tupleType->u.array.size=_size;
    return tupleType;
}

Type createStructType(Symbol _structure)
{
    Type tupleType=(Type)malloc(sizeof(struct Type_));
    tupleType->kind=STRUCTURE;
    tupleType->u.structure=_structure;
    return tupleType;
}

Type createType(int _kind,int _basic,Type _elem,int _size,Symbol _structure)
{
    switch(_kind)
    {
    case(1):
        return createBasicType(_basic);
    case(2):
        return createArrayType(_elem,_size);
    case(3):
        return createStructType(_structure);   
    }
}

Symbol createBlankTuple(char *name)
{
    Symbol newTuple = (Symbol)malloc(sizeof(struct SymbolTuple));
    strcpy(newTuple->name, name);
    newTuple->hashLink = NULL;
    newTuple->structLink = NULL;
    return newTuple;

}

Symbol createBasicTuple(char *name,int _basic)
{
    Type tupleType=(Type)malloc(sizeof(struct Type_));
    tupleType->kind=BASIC;
    tupleType->u.basic=_basic;
    Symbol newTuple=createBlankTuple(name);
    newTuple->type=tupleType;
    return newTuple;
}

Symbol createArrayTuple(char *name,Type _elem,int _size)
{
    Type tupleType=(Type)malloc(sizeof(struct Type_));
    tupleType->kind=ARRAY;
    tupleType->u.array.elem=_elem;
    tupleType->u.array.size=_size;
    Symbol newTuple=createBlankTuple(name);
    newTuple->type=tupleType;
    return newTuple;
}

Symbol createStructTuple(char *name,Symbol structNext)
{
    Type tupleType=(Type)malloc(sizeof(struct Type_));
    tupleType->kind=STRUCTURE;
    tupleType->u.structure=structNext;
    Symbol newTuple=createBlankTuple(name);
    newTuple->type=tupleType;
    return newTuple;
}

Symbol findSymbol(char *name)
{
    unsigned int hashID = hashProject(name);
    if (symbolTable[hashID]!=NULL)
    {
        Symbol current = symbolTable[hashID];
        while (current != NULL)
        {
            if (strcmp(current->name, name) == 0)//loop until we find that name
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
    Symbol current = symbolTable[hashID];
    if (current==NULL)
    {
        current=tuple;//make the NULL pointer pointed to tuple
        return;
    }    
    while (current->hashLink != NULL)
        current = current->hashLink;
    current->hashLink=tuple;
}