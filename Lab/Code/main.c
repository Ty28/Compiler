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
<<<<<<< HEAD
    else
        ;
=======
    else 
        // printf("%d  %d", lexicalError, syntaxError);
>>>>>>> 427ac21126c89593778f72e945cc169fb58ca75f
    return 0;
}
