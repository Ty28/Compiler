#ifndef _TREENODE_H
#define _TREENODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#define YYDEBUG 1
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

node ROOT;
extern int yylineno;
#endif