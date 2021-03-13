#include "treeNode.h"

node createNode(char name_[], char val_[], int lineno_, int type_) {
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
void insertNode(node root_, node child_) {
    if(!root_ || !child_)
        return;
    if(!root_->child) {
        root_->child = child_;
        return;
    }
    node p = root_->child;
    while(p->sibling)
        p = p->sibling;
    p->sibling = child_;
    return;
}
void preOrder(node root_) {
    if(!root_)
        return;
    // print tabs
    for(int i = 0; i < root_->tabs; i++)
		printf(" ");
    // print content, need to classify the type;
    printf("%s: %s\n", root_->name, root_->val);
    if(root_->child)
        root_->child->tabs = root_->tabs + 1;
    if(root_->sibling)
        root_->sibling->tabs = root_->tabs;
    preOrder(root_->child);
    preOrder(root_->sibling);
}