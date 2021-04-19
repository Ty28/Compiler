#include "extern.h"

void printStructure(FieldList field)
{
    while (field != NULL)
    {
        printf("%d : %s", field->type->kind, field->name);
        if (field->type->kind == ARRAY)
        {
            Type myType = field->type;
            while (1)
            {
                if (myType->kind == ARRAY)
                {
                    printf(" %d ", myType->u.array.size);
                    myType = myType->u.array.elem;
                }
                else if (myType->kind == BASIC)
                {
                    printf(" BASIC:%d", myType->u.basic);
                    break;
                }
                else if (myType->kind == STRUCTVAR)
                {
                    printf(" STRUCTVAR");
                    printf("\n\n-------------\n");
                    printStructure(myType->u.structure);
                    printf("\n-------------\n\n");
                    break;
                }
                else if (myType->kind == STRUCTURE)
                {
                    printf(" STRUCTURE");
                    break;
                }
            }
        }
        printf("\n*\n");
        field = field->tail;
    }
}

int main(int argc, char **argv)
{
    if (argc <= 1)
        return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    if (lexicalError == 0 && syntaxError == 0)
    {
        //preOrder(ROOT, 0);
        semanticCheck(ROOT);
        // Symbol p = findSymbol("k3");
        // //printf("%s",p);
        // FieldList field = p->type->u.structure;
        // printStructure(field);
    }
    return 0;
}
