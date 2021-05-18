#include "extern.h"

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
        initInterCode(ROOT);
        // for (int i = 0; i < FORMALPARAMETERSIZE; i++)
        // {
        //     if (FPTable[i] != NULL)
        //     {
        //         FPTableNode current = FPTable[i];
        //         while (current != NULL)
        //         {
        //             printf("%s", current->name);
        //             current = current->link;
        //         }
        //         printf("\n");
        //     }
        // }
        if (argc < 3)
            printCode("out.ir");
        else
            printCode(argv[2]);
    }
    return 0;
}