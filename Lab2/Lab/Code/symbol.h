#ifndef _SYMBOL_H
#define _SYMBOL_H

#include "treeNode.h"
#define SYMBOLTABLESIZE 0x3fff
#define STRUCTTABLESIZE 0x3fff
//#define semanticdebug
void semLog(char *msg);
typedef struct SymbolTuple *Symbol;
typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;
typedef struct FuncList_ *FuncList;
typedef struct StructSymbolTuple *StructSymbol;
struct Type_
{
    enum
    {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNCTION,
        STRUCTVAR,
        ERROR
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
        int errorCode;
    } u;
};

struct SymbolTuple
{
    char name[CHARMAXSIZE];
    Type type;
    Symbol hashLink;
};

struct FieldList_
{
    char name[CHARMAXSIZE];
    Type type;
    FieldList tail;
};

struct FuncList_
{
    char name[CHARMAXSIZE];
    Type type;
    FuncList tail;
};

struct StructSymbolTuple
{
    char name[CHARMAXSIZE];
    StructSymbol link;
};

Symbol *symbolTable;
StructSymbol *structSymbolTable;

unsigned int hashProject(char *name, unsigned int hashsize);
Symbol *createSymbolTable();

Type createBasicType(int _basic);
Type createArrayType(Type _elem, int _size);
Type createStructType(FieldList _structure, int isVariable);

//2021/4/18 16:13 createFuncType has been revised
Type createFuncType(Type returnValueType, FuncList _parameter);
//

Type createType(int _kind, int _basic, Type _elem, int _size, FieldList _structure,
                FuncList _function, int isVariable);
Symbol createBlankTuple(char *name);
Symbol createBasicTuple(char *name, int _basic);
Symbol createArrayTuple(char *name, Type _elem, int _size);
Symbol createStructTuple(char *name, FieldList _structure, int isVariable);
//Symbol createFuncTuple(char *name, FuncList _parameter);
//new Func
Symbol createTupleWithType(char *name, Type _type);
FieldList createBlankField(char *name);
FieldList createFieldWithType(char *name, Type _type);
FuncList createBlankParam(char *name);
FuncList createParamWithType(char *name, Type _type);
///////////////////////////////////////
Symbol findSymbol(char *name);
void insertTuple(Symbol tuple);

//add func:create symbol table for struct members 2021/4/20
StructSymbol *createStructTable();
void freeStructMember(StructSymbol _current); //recursive free one hashline
void freeStructTable(); //free the whole struct symbol table
StructSymbol createMember(char* name);
int findMember(char *name);

// add func: check Type a & Type b
int isTypeEqual(Type t1, Type t2);
int isStructEqual(FieldList f1, FieldList f2);
int isFuncEqual(FuncList f1, FuncList f2);
Type createErrorType(int _errorCode);

#endif
