#include "extern.h"

int main(int argc, char** argv) {
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    char fileName[CHARMAXSIZE];
    if(lexicalError == 0 && syntaxError == 0){
        //preOrder(ROOT, 0);
        semanticCheck(ROOT);
        initInterCode(ROOT);
        if(argc < 3)
            strcpy(fileName, "out.ir");
        else 
            strcpy(fileName, argv[2]);
        optimize_deleteGOTO();
        optimize_deleteNONEVAR();
        optimize_mergeLABEL();
        if(structNum > 0)
            printf("Cannot translate: Code contains variables or paraneters of structure type\n");
        printCode(fileName);
    }
    return 0;
}
