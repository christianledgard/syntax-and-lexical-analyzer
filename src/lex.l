%{
#include <stdio.h>
%}

%%
[ \t]+
if                                          printf("<IF> ");
else                                        printf("<ELSE> ");
[0123456789]+		                        printf("<NUMBER, %s> ", yytext);
[0123456789]+[\.|E|0123456789|E\-]*		        printf("<NUMBER, %s> ", yytext);
[a-zA-Z|\_]+[a-zA-Z|0123456789|\_]*		    printf("<ID, %s> ", yytext);
[\=]			                            printf("<ASSIGN_OP> ");
[\*]			                            printf("<MUL_OP> ");
[\/]                                        printf("<DIV_OP> ");
[\+]                                        printf("<ADD_OP> ");
[\-]                                        printf("<SUBS_OP> ");
[\<]                                        printf("<RELOP_LT> ");
\<\=                                        printf("<RELOP_LE> ");
={2}                                        printf("<RELOP_EQ> ");
[\>]                                        printf("<RELOP_GT> ");
\>\=                                        printf("<RELOP_GE> ");
\(                                          printf("<PAR_BEGIN> ");
\)                                          printf("<PAR_END> ");
.                                           printf("ERROR: Caracter %s no soportado ", yytext);
%%
