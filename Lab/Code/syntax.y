%{
    #include "extern.h"
    #include "treeNode.h"
    // int yydebug = 1;
    int syntaxError = 0;
    void missing(char* c)
    {
        printf("missing %s",c);
    }
    void fault(int _id)
    {
        printf("    fault id:%d\n",_id);
    }

    void my_yyerror(char* msg) {
        printf("Error type B at Line %d: syntax error: %s.\n", yylineno, msg);
    }
%}

/* declared types */
%union {
    node type_node;
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
%type <type_node> Program
%type <type_node> ExtDefList
%type <type_node> ExtDef
%type <type_node> ExtDecList
/* declared Specifiers */
%type <type_node> Specifier
%type <type_node> StructSpecifier
%type <type_node> OptTag
%type <type_node> Tag
/* declared Declarators */
%type <type_node> VarDec
%type <type_node> FunDec
%type <type_node> VarList
%type <type_node> ParamDec
/* declared Statements */
%type <type_node> CompSt
%type <type_node> StmtList
%type <type_node> Stmt
/* declared Local Definitions */
%type <type_node> DefList
%type <type_node> Def
%type <type_node> DecList
%type <type_node> Dec
/* declared Expressions */
%type <type_node> Exp
%type <type_node> Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left NEG
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : 
ExtDefList {
    $$ = createNode("Program", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
    ROOT = $$;
} |
error
{
    my_yyerror("StructSpecifier error");fault(162001);
};

ExtDefList : 
ExtDef ExtDefList {
    $$ = createNode("ExtDefList", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2);
} |
/*empty case*/  {
        @$.first_line = yylineno;
    $$ = NULL;
} |
error
{
    my_yyerror("StructSpecifier error");fault(162001);
};

ExtDef : 
Specifier ExtDecList SEMI {
    $$ = createNode("ExtDef", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} | 
Specifier SEMI {
    $$ = createNode("ExtDef", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2);
} | 
Specifier FunDec CompSt {
    $$ = createNode("ExtDef", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
error SEMI {
    syntaxError += 1;
    my_yyerror("error 0");
} |
Specifier error SEMI {
    syntaxError += 1;
    my_yyerror("initialized or invalid global variable");
} |
error Specifier SEMI {
    syntaxError += 1;
    my_yyerror("error 2");
};

ExtDecList :
VarDec {
    $$ = createNode("ExtDecList", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} | 
VarDec COMMA ExtDecList {
    $$ = createNode("ExtDecList", " ", @$.first_line, 0);
}
;

Specifier :
TYPE {
    $$ = createNode("Specifier", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} | 
StructSpecifier {
    $$ = createNode("Specifier", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
}|
error
{
    my_yyerror("Specifier error");fault(162000);
}
;

StructSpecifier :
STRUCT OptTag LC DefList RC {
    $$ = createNode("StructSpecifier", " ", @$.first_line, 0);
    insertNode($$, 5, $1, $2, $3, $4, $5);
} |
STRUCT Tag {
    $$ = createNode("StructSpecifier", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2);
} |
STRUCT OptTag LC DefList error{
    missing("RC");fault(1613);
} |
STRUCT OptTag error DefList RC{
    missing("LC");fault(1616);
}
;

OptTag :
ID {
    $$ = createNode("OptTag", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
 {
    $$ = NULL;
} |
error
{
    my_yyerror("OptTag error");fault(162001);
};

Tag :
ID {
    $$ = createNode("Tag", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
error{
    printf("OptTag error");fault(1618);
};

VarDec :
ID {
    $$ = createNode("VarDec", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
VarDec LB INT RB {
    $$ = createNode("VarDec", " ", @$.first_line, 0);
    insertNode($$, 4, $1, $2, $3, $4);
} |
ID error{
    my_yyerror("something after identifier gets wrong");fault(162103);
} |
VarDec LB error RB {
    syntaxError += 1;
    my_yyerror("invalid expression between \'[]\'");
};

FunDec :
ID LP VarList RP {
    $$ = createNode("FunDec", " ", @$.first_line, 0);
    insertNode($$, 4, $1, $2, $3, $4);
} |
ID LP RP {
    $$ = createNode("FunDec", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
ID LP VarList error{
    missing("RP");
    fault(1622);
} |
ID LP error RP{
    syntaxError += 1;
    my_yyerror("invalid varlist");
} |
error LP VarList RP {
    syntaxError += 1;
    my_yyerror("invalid function name");
} |
error LP RP {
    syntaxError += 1;
    my_yyerror("invalid function name");
};

VarList :
ParamDec COMMA VarList {
    $$ = createNode("VarList", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
ParamDec {
    $$ = createNode("VarList", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
ParamDec error VarList {
    missing("COMMA");
    fault(1628);
} |
error
{
    my_yyerror("VarList error");fault(162002);
};

ParamDec :
Specifier VarDec {
    $$ = createNode("ParamDec", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2);
}|
error
{
    my_yyerror("ParamDec error");fault(162003);
};

CompSt :
LC DefList StmtList RC {
    $$ = createNode("CompSt", " ", @$.first_line, 0);
    
    insertNode($$, 4, $1, $2, $3, $4);
} |
LC DefList StmtList error {
    my_yyerror("missing \"}\"");fault(161942);
} |
LC error RC{
    my_yyerror("contents between \"{ }\" gets wrong");fault(161944);
} |
DefList StmtList RC {
    my_yyerror("missing \"{\"");fault(161945);
} |
error
{
    my_yyerror("CompSt error");fault(1620031);
}
;

StmtList :
Stmt StmtList {
    $$ = createNode("StmtList", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2);
} |
 {
    $$ = NULL;
}
;

Stmt :
Exp SEMI {
    $$ = createNode("Stmt", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2); 
} |
CompSt {
    $$ = createNode("Stmt", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
RETURN Exp SEMI{
    $$ = createNode("Stmt", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3); 
} |
IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{
    $$ = createNode("Stmt", " ", @$.first_line, 0);
    insertNode($$, 5, $1, $2, $3, $4, $5);
} |
IF LP Exp RP Stmt ELSE Stmt {
    $$ = createNode("Stmt", " ", @$.first_line, 0);
    insertNode($$, 7, $1, $2, $3, $4, $5, $6, $7);
} |
WHILE LP Exp RP Stmt {
    $$ = createNode("Stmt", " ", @$.first_line, 0);
    insertNode($$, 5, $1, $2, $3, $4, $5);
} |
Exp error{
    my_yyerror("missing \";\"");fault(161850);
} |
RETURN Exp error{
    my_yyerror("missing \";\"");fault(161850);
} |
RETURN error{
    my_yyerror("missing returning value and \";\"");fault(161900);
} |
IF LP Exp error Stmt %prec LOWER_THAN_ELSE{
    my_yyerror("missing right parenthesis");fault(161911);
} |
IF LP error RP Stmt %prec LOWER_THAN_ELSE{
    my_yyerror("condition for \"if\" gets wrong");fault(161916);
} |
IF error Exp RP Stmt %prec LOWER_THAN_ELSE{
    my_yyerror("missing left parenthesis");fault(161917);
} |
WHILE LP Exp error Stmt {
    my_yyerror("missing right parenthesis");fault(161925);
} |
WHILE LP error RP Stmt {
    my_yyerror("condition for \"while\" gets wrong");fault(161929);
} |
WHILE error Exp RP Stmt {
    my_yyerror("missing left parenthesis");fault(161929);
} | //////////////////////////////////////////////////////
error SEMI {
    syntaxError += 1;
    my_yyerror("invalid statement or cannot define variable before \';\'");
} |
Exp error SEMI {
    syntaxError += 1;
    my_yyerror("invalid expression near \';\'");
} |
RETURN Exp error {
    syntaxError += 1;
    my_yyerror("invalid expression near \'return\'");
} |
RETURN error SEMI {
    syntaxError += 1;
    my_yyerror("invalid expression between \'return\' and \';\'");
};

DefList :
Def DefList {
    $$ = createNode("DefList", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2); 
} |
 {
    $$ = NULL;
}
;

Def : 
Specifier DecList SEMI {
    $$ = createNode("Def", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
Specifier error SEMI {
    syntaxError += 1;
    my_yyerror("invalid variable or expected expression before \';\'");
} |
Specifier DecList error {
    syntaxError += 1;
    my_yyerror("missing \';\' or invalid token");
};

DecList : 
Dec {
    $$ = createNode("DecList", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
Dec COMMA DecList {
    $$ = createNode("DecList", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
}
;

Dec :
VarDec {
    $$ = createNode("Dec", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
VarDec ASSIGNOP Exp {
    $$ = createNode("Dec", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
}
;

Exp :
Exp ASSIGNOP Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
Exp AND Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
Exp OR Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
Exp RELOP Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
Exp PLUS Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
Exp MINUS Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0); 
    insertNode($$, 3, $1, $2, $3);
} | 
Exp STAR Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
Exp DIV Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
LP Exp RP {
    $$ = createNode("Exp", " ", @$.first_line, 0); 
    insertNode($$, 3, $1, $2, $3);
} |
MINUS Exp %prec NEG{
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2); 
} |
NOT Exp {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 2, $1, $2); 
} |
ID LP Args RP {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 4, $1, $2, $3, $4);
} |
ID LP RP {
    $$ = createNode("Exp", " ", @$.first_line, 0); 
    insertNode($$, 3, $1, $2, $3);
} |
Exp LB Exp RB {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 4, $1, $2, $3, $4);
} |
Exp DOT ID {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
} |
ID {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
INT {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
FLOAT {
    $$ = createNode("Exp", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} |
Exp ASSIGNOP error {
    syntaxError += 1;
    my_yyerror("invalid token near \'=\'");
} |
Exp AND error {
    syntaxError += 1;
    my_yyerror("invalid token near \'&&\'");
} |
Exp OR error {
    syntaxError += 1;
    my_yyerror("invalid token near \'||\'");
} |
Exp RELOP error {
    syntaxError += 1;
    my_yyerror("invalid token near \'RELOP\'");
} |
Exp PLUS error {
    syntaxError += 1;
    my_yyerror("invalid token near \'+\'");
} |
Exp MINUS error {
    syntaxError += 1;
    my_yyerror("invalid token near \'-\'");
} |
Exp STAR error {
    syntaxError += 1;
    my_yyerror("invalid token near \'*\'");
} | 
Exp DIV error {
    syntaxError += 1;
    my_yyerror("invalid token near \'/\'");
} |
LP error RP {
    syntaxError += 1;
    my_yyerror("invalid token between \'()\'");
} |
MINUS error {
    syntaxError += 1;
    my_yyerror("invalid token after \'-\'");
} |
NOT error {
    syntaxError += 1;
    my_yyerror("invalid token after \'!\'");
} |
ID LP error RP {
    syntaxError += 1;
    my_yyerror("invalid tokens between \'()\'");
} |
Exp LB error RB {
    syntaxError += 1;
    my_yyerror("invalid expression between \'[]\'");
};

Args :
Exp COMMA Args {
    $$ = createNode("Args", " ", @$.first_line, 0);
    insertNode($$, 3, $1, $2, $3);
}
| Exp {
    $$ = createNode("Args", " ", @$.first_line, 0);
    insertNode($$, 1, $1);
} 
;

%%
#include "lex.yy.c"
void yyerror(char* msg) {
    // syntaxError += 1;
    // printf("Error type B at Line %d: %s.\n", yylineno, msg);
}