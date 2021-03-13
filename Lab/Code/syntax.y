%{
    #include <stdio.h>
    #include <stdlib.h>
%}

/* declared types */
%union {
    TreeNode type_TreeNode;
}

/* declared tokens*/
%token <type_TreeNode> INT;
%token <type_TreeNode> FLOAT;
%
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