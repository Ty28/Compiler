%{
#define debug

int lexicalError = 0;
void debug_log(char *mytext) {
    #ifdef debug    
        printf("DEBUG LOG: token %s value %s at Line %d\n", mytext, yytext, yylineno);
    #endif
}
%}

%option yylineno
ws [ \t\r\n]+
digit [0-9]
digits [0-9]+
INT 0|[1-9]{digit}*
FLOAT {digits}\.{digits}
ID [a-zA-Z_][0-9a-zA-Z_]*
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS \+
MINUS -
STAR \*
DIV \/
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE "int"|"float"
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
LINECOMMENT \/\/
BLOCKCOMMENT \/\*
OTHER .
%%
{LINECOMMENT} { 
    char c = input();
    while(c!='\n')
        c = input();
}
{BLOCKCOMMENT} {
    char pre = input(), cur = input();
    while(pre != '*' || cur != '/') {
        pre = cur;
        cur = input();
        if(cur == '\0') {
            lexicalError += 1;
            printf("Error type A at Line %d: Missing */.\n",yylineno);
            break;
        }
    }
}
{INT} {
    debug_log("INT");
}
{FLOAT} {
    debug_log("FLOAT");
}
{TYPE} {
    debug_log("TYPE");
}
{STRUCT} {
    debug_log("STRUCT");
}
{RETURN} {
    debug_log("RETURN");
}
{IF} {
    debug_log("IF");
}
{ELSE} {
    debug_log("ELSE");
}
{WHILE} {
    debug_log("WHILE");
}
{ID} {
    debug_log("ID");
}
{SEMI} {
    debug_log("SEMI");
}
{COMMA} {
    debug_log("COMMA");
}
{ASSIGNOP} {
    debug_log("ASSIGNOP");
}
{RELOP} {
    debug_log("RELOP");
}
{PLUS} {
    debug_log("PLUS");
}
{MINUS} {
    debug_log("MINUS");
}
{STAR} {
    debug_log("STAR");
}
{DIV} {
    debug_log("DIV");
}
{AND} {
    debug_log("AND");
}
{OR} {
    debug_log("OR");
}
{DOT} {
    debug_log("DOT");
}
{NOT} {
    debug_log("NOT");
}
{LP} {
    debug_log("LP");
}
{RP} {
    debug_log("RP");
}
{LB} {
    debug_log("LB");
}
{RB} {
    debug_log("RB");
}
{LC} {
    debug_log("LC");
}
{RC} {
    debug_log("RC");
}
{ws} {
    
}
{OTHER} {
    lexicalError += 1;
    printf("Error type A at Line %d: Mysterious character \'%s'\n",yylineno,yytext);
}
%%
int main(int argc, char** argv) {
    if(argc > 1) {
        if(!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }
    while(yylex() != 0);
    printf("Lexical Error : %d", lexicalError);
    return 0;
}