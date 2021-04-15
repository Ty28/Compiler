#include "semantic.h"

int semanticCheck(node root)
{
    printf("HAHA, Let's begin the semantic check\n");
    // printNode(root);
    symbolTable = createSymbolTable();
    Program(root);
}

void semLog(char* msg)
{
#ifdef semanticdebug
    printf("%s\n",msg);
#endif
}

void errorOutput(int errorType, int line)
{
    printf("Error Type %d at line %d:", errorType, line);
}

void Program(node root)
{
    printf("HAHA, Let's check the Program\n");
    ExtDefList(getKChild(root, 0));
}

void ExtDefList(node root)
{
    if (!root)
        return;
    printf("HAHA, Let's check the ExtDefList\n");
    ExtDef(getKChild(root, 0));
    ExtDefList(getKChild(root, 1));
}

void ExtDef(node root)
{
    printf("HAHA, Let's check the ExtDef\n");
    // need to complete
    Type type = Specifier(getKChild(root, 0));
    if(strcmp(getKChild(root, 1)->name,"ExtDecList")==0){
        //ExtDecList(getKChild(root, 1)->name, type);
    }
    else if(strcmp(getKChild(root, 1)->name,"SEMI")==0){
        ;
    }
    else if(strcmp(getKChild(root, 1)->name,"FunDec")==0){
        //FunDec(getKChild(root, 1), type);
        //Compst(getKChild(root, 2), type);
    }
}

//////ADD after push

Type Tag(node root)
{
    Symbol findTuple = findSymbol(root->name);
    if (findTuple == NULL)
    {
        errorOutput(1, root->lineno);
        return NULL;
    }
    else
        return findTuple->type;
}

Type StructSpecifier(node root)
{
    node tagNode=getKChild(root,2);
    if(strcmp(tagNode->name,"Tag")==0)
        return Tag(tagNode->child);
    else if(strcmp(tagNode->name,"OptTag")==0)
    {
        return NULL;
    }
}

Type Specifier(node root)
{
    semLog("start parsing specifier");
    node typeNode=getKChild(root, 0);
    if (strcmp(typeNode->name, "TYPE") == 0) //if specifier induces TYPE
    {
        if (strcmp(typeNode->val, "int") == 0)
        {
            semLog("create type int");
            return createBasicType(1);
        }
        else if (strcmp(typeNode->val, "float") == 0)
        {
            semLog("create type float");
            return createBasicType(2);
        }
    }
    else if (strcmp(getKChild(root, 0)->name, "StructSpecifier"))
        return StructSpecifier(getKChild(root, 0));
    else
    {
        printf("well,something wrong with lexical parsing\n");
        return NULL;
    }
}