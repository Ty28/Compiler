#include "treeNode.h"

node createNode(char name_[], char val_[], int lineno_, int type_) {
    // malloc root
    node root_ = (node)malloc(sizeof(struct treeNode));
    // copy content
    strcpy(root_->name, name_);
    strcpy(root_->val, val_);
    root_->lineno = lineno_;
    root_->type = type_;
    root_->child = NULL;
    root_->sibling = NULL;
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

// new API: get the kth child of root_
node getKChild(node root_, int k) {
    node p = root_;
    p = p->child;
    if(k == 0)
        return p;
    
    while(k--)
        p = p->sibling;
    //printNode(p);
    return p;
}

void printNode(node root_)
{
    if(!root_)
        return;
    if (root_->type == 0)
        printf("%s (%d)\n", root_->name, root_->lineno);
    else
    {
        //all nodes need to print their names
        printf("%s", root_->name); 
        switch (root_->type)
        {
        case (1): 
            printf(": %s\n", root_->val);
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

void preOrder_nonrecursion(node root_) {
    if(!root_)
        return;
    st stk = (st)malloc(sizeof(struct myStack));
    initStack(stk);
    while(root_ || !isEmpty(stk)) {
        while(root_) {
            printf("%ld ", stk->top);
            printNode(root_);
            printf("%ld ", stk->top);
            push(stk, root_);
            root_ = root_->child;
        }
        if(!isEmpty(stk)) {
            root_ = pop(stk);
            root_ = root_->sibling;
        }
    }
}

void initStack(st S) {
    S = (st)malloc(sizeof(struct myStack));
    if(!S)
        exit(OVERFLOW);
    S->top = 0;
}

int push(st S, node t) {
    if(S->top == MAXSIZE - 1)
        return 0;
    S->top += 1;
    S->data[S->top] = t;
    return 1;
}

node pop(st S){
    if(S->top == 0)
        return NULL;
    node res = (node)malloc(sizeof(struct treeNode));
    res = S->data[S->top];
    S->top--;
    return res;
}

int isEmpty(st S) {
    return S->top == 0;
}