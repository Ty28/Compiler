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
    }
    // printf("-----------------------global_table_below----------------------\n");
	// for(int i=0;i<HASHSIZE;i++){
	// 	if(symbolTable[i]!=NULL){
	// 		printf("i:%d ",i);
	// 		Symbol temp = symbolTable[i];
	// 		while(temp != NULL){
    //                 printf("%s,  %d ", temp->name, temp->type->kind);
	// 				temp=temp->hashLink;
	// 		}
	// 		printf("\n");
	// 	};
	// };
	// printf("-----------------------global_table_above----------------------\n");
    // errorOutput(1, 1, "asda");
    return 0;
}
