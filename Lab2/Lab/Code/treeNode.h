#ifndef _TREENODE_H
#define _TREENODE_H

#define YYDEBUG 1
#define MAXSIZE 100000010
#define OVERFLOW 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct treeNode *node;

struct treeNode {
    char name[32];
    char val[32];
    int lineno;
    int type;
    node child;
    node sibling;
};

node createNode(char name_[], char val_[], int lineno_, int type_);
void insertNode(node root_, int args, ...);
void printNode(node root_);
void preOrder(node root_, int depth);
void preOrder_nonrecursion(node root_);

node ROOT;
extern int yylineno;

typedef struct myStack *st;

struct myStack
{
    node data[MAXSIZE];
    long top;
};

void initStack(st S);
int push(st S, node t);
node pop(st S);
int isEmpty(st S);

#endif