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
    if(lexicalError == 0 && syntaxError == 0){
        //preOrder(ROOT, 0);
        semanticCheck(ROOT);
        initInterCode(ROOT);
    }
    return 0;
}