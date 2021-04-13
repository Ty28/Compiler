#ifndef _SYMBOL_H
#define _SYMBOL_H

#include "treeNode.h"
#define HASHSIZE 0x3fff
typedef struct SymbolTuple *Symbol;
typedef struct Type_ *Type;

struct Type_
{
    enum
    {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNCTION
    } kind;
    union
    {
        int basic;
        /*
            type    meaning
            1       int
            2       float
        */
        struct
        {
            Type elem;
            int size;
        } array;
        Symbol structure;
        Symbol function;
    } u;
};

struct SymbolTuple
{
    char name[32];
    Type type;
    Symbol hashLink;
    Symbol structLink;
};

Symbol *symbolTable;

unsigned int hashProject(char *name);
Symbol* createSymbolTable();
Symbol findSymbol(char *name);
Type createBasicType(int _basic);
Type createArrayType(Type _elem,int _size);
Type createStructType(Symbol _structure);
Type createType(int _kind,int _basic,Type _elem,int _size,Symbol _structure);
Symbol createBlankTuple(char *name);
Symbol createBasicTuple(char *name,int _basic);
Symbol createArrayTuple(char *name,Type _elem,int _size);
Symbol createStructTuple(char *name,Symbol structNext);
void insertTuple(Symbol tuple);

#endif