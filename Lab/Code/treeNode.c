#include "treeNode.h"

node createNode(char name_[], char val_[], int lineno_, int type_)
{
    // malloc root
    node root_ = (node)malloc(sizeof(struct treeNode));
    // copy content
    strcpy(root_->name, name_);
    strcpy(root_->val, val_);
    root_->lineno = lineno_;
    root_->type = type_;
    root_->tabs = 0;
    // return root;
    return root_;
}
void insertNode(node root_, node child_)
{
    if (!root_ || !child_)
        return;
    if (!root_->child)
    {
        root_->child = child_;
        return;
    }
    node p = root_->child;
    while (p->sibling)
        p = p->sibling;
    p->sibling = child_;
    return;
}

void printNode(node root_)
{
    // print tabs
    for (int i = 0; i < root_->tabs; i++)
        printf(" ");
    if (root_->type == 0)
        printf("%s (%d)\n", root_->name, root_->lineno);
    else
    {
        //all nodes need to print their names
        printf("%s", root_->name); 
        switch (root_->type)
        {
        case (1): 
            printf(": %d\n", atoi(root_->val));
            break;
            //case 1 for INT
        case (2): 
            printf(": %f\n", atof(root_->val));
            break;
            //case 2 for FLOAT
        case (3): 
        case (16):  
            printf(": %s\n", root_->val);
            break;
            //case 3 for ID
            //case 16 for TYPE
        default:
            printf("\n");
            break;
        }
    }
}

void preOrder(node root_)
{
    if (!root_)
        return;
    // print tabs
    // print content, need to classify the type;
    // printf("%s: %s (%d)\n", root_->name, root_->val, root_->lineno); 
    printNode(root_);
    if (root_->child)
        root_->child->tabs = root_->tabs + 1;
    if (root_->sibling)
        root_->sibling->tabs = root_->tabs;
    preOrder(root_->child);
    preOrder(root_->sibling);
}