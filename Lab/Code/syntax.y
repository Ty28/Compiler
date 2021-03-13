%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "treeNode.h"
    extern node ROOT;
    int syntaxError = 0;
%}

/* declared types */
%union {
    node type_node
}

/* declared Tokens */
%token <type_node> INT
%token <type_node> FLOAT
%token <type_node> ID
%token <type_node> SEMI
%token <type_node> COMMA
%token <type_node> ASSIGNOP
%token <type_node> RELOP
%token <type_node> PLUS
%token <type_node> MINUS
%token <type_node> STAR
%token <type_node> DIV
%token <type_node> AND
%token <type_node> OR
%token <type_node> DOT
%token <type_node> NOT
%token <type_node> TYPE
%token <type_node> LP
%token <type_node> RP
%token <type_node> LB
%token <type_node> RB
%token <type_node> LC
%token <type_node> RC
%token <type_node> STRUCT
%token <type_node> RETURN
%token <type_node> IF
%token <type_node> ELSE
%token <type_node> WHILE
/* declared High-level definitions */
%token <type_node> Program
%token <type_node> ExtDefList
%token <type_node> ExtDef
%token <type_node> ExtDecList
/* declared Specifiers */
%token <type_node> Specifier
%token <type_node> StructSpecifier
%token <type_node> OptTag
%token <type_node> Tag
/* declared Declarators */
%token <type_node> VarDec
%token <type_node> FunDec
%token <type_node> VarList
%token <type_node> ParamDec
/* declared Statements */
%token <type_node> CompSt
%token <type_node> StmtList
%token <type_node> Stmt
/* declared Local Definitions */
%token <type_node> DefList
%token <type_node> Def
%token <type_node> DecList
%token <type_node> Dec
/* declared Expressions */
%token <type_node> Exp
%token <type_node> Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : 
ExtDefList {
    $$ = createNode("Program", "", @$.first_line, 0);
    insertNode($$, $1);
    ROOT = $$;
};
ExtDefList : 
ExtDef ExtDefList {
    $$ = createNode("ExtDefList", "", @$.first_line, 0);
    insertNode($$, $1);
    insertNode($$, $2);
}
|  {
    $$ = NULL;
};
ExtDef : 
Specifier ExtDecList SEMI {
    $$ = createNode("ExtDef", "", @$.first_line, 0);
    insertNode($$, $1);
    insertNode($$, $2);
    insertNode($$, $3);
}
| Specifier SEMI {
    $$ = createNode("ExtDef", "", @$.first_line, 0);
    insertNode($$, $1);
    insertNode($$, $2);
}
| Specifier FunDec CompSt {
    $$ = createNode("ExtDef", "", @$.first_line, 0);
    insertNode($$, $1);
    insertNode($$, $2);
    insertNode($$, $3);
}
| error SEMI {
    syntaxError += 1;
}
| Specifier error SEMI {
    syntaxError += 1;
}
| error Specifier SEMI {
    syntaxError += 1;
}
%%
int yyerror(char* msg) {
    syntaxError += 1;
    printf("Error type B at Line %d: %s\n", yylineno, msg);
}