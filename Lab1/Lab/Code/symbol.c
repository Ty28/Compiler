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

Symbol createSymbolTable()
{
    Symbol tableHead = (Symbol)malloc(HASHSIZE * sizeof(struct SymbolTuple));
    for (int i = 0; i < HASHSIZE; i++)//initialize
    {
        tableHead[i].valid=0;
        tableHead[i].link=NULL;
    }
    return tableHead;
}

Symbol findSymbol(char *name)
{
    unsigned int hashID = hashProject(name);
    if (symbolTable[hashID].valid)
    {
        Symbol current = &symbolTable[hashID];
        while (current != NULL)
        {
            if (strcmp(current->name, name) == 0)
            {
                return current;
            }
            current = current->link;
        }
    }
    return NULL; //if that name does not exist in our table, return NULL
}

void insertSymbolTable(char *name)
{
    unsigned int hashID = hashProject(name);
    if (symbolTable[hashID].valid)
    {
        
    }
    else
    {
        symbolTable[hashID].valid = 1;
    }
}