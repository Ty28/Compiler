#ifndef _SYMBOL_H
#define _SYMBOL_H

#include "treeNode.h"
#define HASHSIZE 0x3fff
typedef struct SymbolTuple *Symbol;
typedef struct Type_ *Type;
typedef struct FieldList_* FieldList;
typedef struct FuncList_* FuncList;

struct Type_
{
    enum
    {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNCTION,
        STRUCTVAR
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
        FieldList structure;
        FuncList function;
    } u;
};

struct SymbolTuple
{
    char name[32];
    Type type;
    Symbol hashLink;
};

struct FieldList_ {
    char name[32];
    Type type;
    FieldList tail;
};

struct FuncList_ {
    char name[32];
    Type type;
    FuncList tail;
};

Symbol *symbolTable;

unsigned int hashProject(char *name);
Symbol *createSymbolTable();

Type createBasicType(int _basic);
Type createArrayType(Type _elem, int _size);
Type createStructType(FieldList _structure,int isVariable);
Type createFuncType(FuncList _parameter);
Type createType(int _kind, int _basic, Type _elem, int _size, FieldList _structure, 
                FuncList _function,int isVariable);
Symbol createBlankTuple(char *name);
Symbol createBasicTuple(char *name, int _basic);
Symbol createArrayTuple(char *name, Type _elem, int _size);
Symbol createStructTuple(char *name, FieldList _structure,int isVariable);
Symbol createFuncTuple(char *name, FuncList _parameter);
//new Func
Symbol createTupleWithType(char* name,Type _type);
FieldList createBlankField(char* name);
FieldList createFieldWithType(char* name,Type _type);
///////////////////////////////////////
Symbol findSymbol(char *name);
void insertTuple(Symbol tuple);

#endif