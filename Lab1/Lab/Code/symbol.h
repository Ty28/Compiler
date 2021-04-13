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
        STRUCT,
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
    int valid; //valid = 1 represents that this tuple is valid
    Type type;
    Symbol link;
};

Symbol symbolTable;

unsigned int hashProject(char *name);
Symbol createSymbolTable();
Symbol findSymbol(char *name);
void insertSymbolTable(char *name);

#endif