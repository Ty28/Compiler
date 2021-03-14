#include "treeNode.h"

node createNode(char name_[], char val_[], int lineno_, int type_) {
    // malloc root
    node root_ = (node)malloc(sizeof(struct treeNode));
    // copy content
    strcpy(root_->name, name_);
    strcpy(root_->val, val_);
    root_->lineno = lineno_;
    root_->type = type_;
    // return root;
    return root_;
}
void insertNode(node root_, int args, ...) {
    // reference on https://blog.csdn.net/ithomer/article/details/6189072
    va_list s;
    va_start(s, args);
    node c = va_arg(s, node);
    root_->child = c;
    for(int i = 1; i < args; i++) {
        c->sibling = va_arg(s, node);
        if(c->sibling)
            c = c->sibling;
    }
    return;
}
void printNode(node root_)
{
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
void preOrder(node root_, int depth) {
    if(!root_)
        return;
    // print tabs
    for(int i = 0; i < depth; i++)
		printf("  ");
    // print content, need to classify the type;
    printNode(root_);
    // if child, child.depth = parent.depth + 1, if sibling, sibling.depth = child.depth
    preOrder(root_->child, depth + 1);
    preOrder(root_->sibling, depth);
}