#ifndef _SYMBLE_H
#define _SYMBLE_H

#include <treeNode.h>

typedef struct SymbleTuple *Symble;
typedef struct Type_ *Type;

struct Type_
{
    enum
    {
        BASIC,
        ARRAY,
        STRUCT
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
        Symble structure;
    } u;
};

struct SymbleTuple
{
    char name[32];
    Type type;
};

Symble createSymbleTable(int n);

#endif