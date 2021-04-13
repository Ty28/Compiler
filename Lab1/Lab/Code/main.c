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
    if(lexicalError == 0 && syntaxError == 0)
        preOrder(ROOT, 0);
    else 
<<<<<<< HEAD:Lab1/Lab/Code/main.c
        printf("\n");
=======
        printf("%d  %d", lexicalError, syntaxError);
>>>>>>> 940517cf349ca7537fb2841f6d316531f54eb4e8:Lab/Code/main.c
    return 0;
}
