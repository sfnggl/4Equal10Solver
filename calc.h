#include <math.h>
#include <stdio.h>

int yylex();
void yyerror(char const *);
void yystrdup(const char * argv);
double yycallparse(void);
