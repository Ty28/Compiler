%{
	#include <stdio.h>
%}

/* declared tokens */
%union{
    int type_int;
    float type_float;
}
%token <type_int> INT 
%token <type_float> FLOAT
%token PLUS MINUS STAR DIV

%type <type_float> Exp Factor Term

%%
Calc: /* empty */
    |Exp {printf("= %f\n",$1);}
;
Exp:Factor
    |Exp PLUS Factor{$$=$1+$3;}
    |Exp MINUS Factor{$$=$1-$3;}
;
Factor:Term
    |Factor STAR Term{$$=$1*$3;}
    |Factor DIV Term{$$=$1/$3;}
;
Term:INT{$$=$1;}
    |FLOAT{$$=$1;}
;

%%
#include "lex.yy.c"
int main(){
	yyparse();
}
yyerror(char* msg){
	fprintf(stderr,"error:%s/n",msg);
}
	
