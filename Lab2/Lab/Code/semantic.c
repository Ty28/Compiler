#include "semantic.h"

int semanticCheck(node root)
{
    // printf("HAHA, Let's begin the semantic check\n");
    // printNode(root);
    symbolTable = createSymbolTable();
    Program(root);
}

void semLog(char *msg)
{
#ifdef semanticdebug
    printf("%s\n", msg);
#endif
}

void errorOutput(int errorType, int line)
{
    printf("Error Type %d at line %d:  \n", errorType, line);
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
    //semLog("HAHA, Let's check the ExtDefList");
    ExtDef(getKChild(root, 0));
    ExtDefList(getKChild(root, 1));
}

void ExtDef(node root)
{
    //semLog("HAHA, Let's check the ExtDef");
    // need to complete
    Type type = Specifier(getKChild(root, 0));
    if (strcmp(getKChild(root, 1)->name, "ExtDecList") == 0)
    {
        ExtDecList(getKChild(root, 1), type);
    }
    else if (strcmp(getKChild(root, 1)->name, "SEMI") == 0)
    {
        ;
    }
    else if (strcmp(getKChild(root, 1)->name, "FunDec") == 0)
    {
        //FunDec(getKChild(root, 1), type);
        //Compst(getKChild(root, 2), type);
    }
}

void ExtDecList(node root,Type extDecType)
{
    semLog("start parsing ExtDecList");
    VarDec(root->child, extDecType);
    //represent that ExtDecList has more than one child node,say, VarDec with COMMA
    if (getKChild(root, 1) != NULL)
        ExtDecList(getKChild(root, 2), extDecType);
}

void VarDec(node root,Type decType)
{
    semLog("start parsing VarDec");
    if(strcmp(root->child->name,"ID")==0)
    {
        node IDNode=root->child;
        if(findSymbol(IDNode->val)!=NULL)
        {
            semLog(root->child->val);
            errorOutput(3,IDNode->lineno);
        }
        else
        {
            Symbol VarDecTuple=createTupleWithType(IDNode->val,decType);
            semLog("insertTuple(VarDecTuple)");
            insertTuple(VarDecTuple);
            semLog("insert success!");
        }
    }
}

Type Tag(node root)
{
    semLog("start parsing Tag");
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
    semLog("start parsing StructSpecifier");
    node tagNode = getKChild(root, 1);
    if (strcmp(tagNode->name, "Tag") == 0)
    {
        semLog("start parsing Tag");
        return Tag(tagNode->child);
    }
    else if (strcmp(tagNode->name, "OptTag") == 0)
    {
        return NULL;
    }
    else
    {
        semLog("something wrong with syntax in StructSpecifier\n");
        return NULL;
    }
}

Type Specifier(node root)
{
    semLog("start parsing specifier");
    node typeNode = getKChild(root, 0);
    semLog(typeNode->name);
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
    else if (strcmp(typeNode->name, "StructSpecifier") == 0)
        return StructSpecifier(getKChild(root, 0));
    else
    {
        printf("well,something wrong with lexical parsing\n");
        return NULL;
    }
}

void DefList(node root)
{
    if (!root || !root->child)
        return;
    Def(getKChild(root, 0));
    DefList(getKChild(root, 1));
}

void Def(node root)
{
    Specifier(getKChild(root, 0));
}

void DecList(node root, Type decType)
{
    Dec(root->child, decType);
    //represent that Dec has more than one child node,say, Dec with COMMA
    if (getKChild(root, 1) != NULL)
        DecList(getKChild(root, 2), decType);
}

void Dec(node root, Type decType)
{

}