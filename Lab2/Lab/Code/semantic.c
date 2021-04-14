#include "semantic.h"

int semanticCheck(node root) {
    printf("HAHA, Let's begin the semantic check\n");
    // printNode(root);
    symbolTable = createSymbolTable();
    Program(root);
}

void Program(node root){
    printf("HAHA, Let's check the Program\n");
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
    printf("HAHA, Let's check the ExtDef\n");
    // need to complete
    Type type = Specifier(getKChild(root, 0));
    
    if(strcmp(getKChild(root, 1)->name,"ExtDecList")==0){
        ExtDecList(getKChild(root, 1)->name, type);
    }
    else if(strcmp(getKChild(root, 1)->name,"SEMI")==0){
        ;
    }
    else if(strcmp(getKChild(root, 1)->name,"FunDec")==0){
        FunDec(getKChild(root, 1), type);
        Compst(getKChild(root, 2), type);
    }
}