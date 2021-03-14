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
void preOrder(node root_, int depth) {
    if(!root_)
        return;
    // print tabs
    for(int i = 0; i < depth; i++)
		printf("  ");
    // print content, need to classify the type;
    printf("%s: %s\n", root_->name, root_->val);
    preOrder(root_->child, depth + 1);
    preOrder(root_->sibling, depth);
}