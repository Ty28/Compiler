#include "semantic.h"

int semanticCheck(node root) {
    printf("HAHA, Let's begin the semantic check\n");
    // printNode(root);
    symbolTable = createSymbolTable();
    Program(root);
}

void Program(node root){
    printf("HAHA, Let's check the Program\n");
    node ExtDefList_ = getKChild(root, 0);
    printNode(ExtDefList_);
    ExtDefList(getKChild(root, 0));
}
void ExtDefList(node root) {
    if(!root)
        return;
    printf("HAHA, Let's check the ExtDefList\n");
    ExtDef(getKChild(root, 0));
    ExtDefList(getKChild(root, 1));
}
void ExtDef(node root) {
    if(!root)
        return;
    printf("HAHA, Let's check the ExtDef\n");
}