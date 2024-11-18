/* Infix notation calculator. */

%{
  #include "calc.h"
%}

/* Bison declarations. */
%define api.value.type {double}
%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG   /* negation--unary minus */
%right '^'        /* exponentiation */

%% /* The grammar follows. */
input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'  { printf ("\t%.10g\n", $1); }
;

exp:
  NUM
| exp '+' exp        { $$ = $1 + $3;      }
| exp '-' exp        { $$ = $1 - $3;      }
| exp '*' exp        { $$ = $1 * $3;      }
| exp '/' exp        { $$ = $1 / $3;      }
| '-' exp  %prec NEG { $$ = -$2;          }
| exp '^' exp        { $$ = pow ($1, $3); }
| '(' exp ')'        { $$ = $2;           }
;

%%

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int idx = 0;
char *msg;

void yystrdup(const char * argv){
  msg = strndup(argv, strlen(argv));
}

int yylex(){
  char c = msg[idx];
  /* Skip white space. */
  while (c == ' ' || c == '\t'){
    idx++;
    c = msg[idx];   
  }

  /* Process numbers. */
  if (isdigit (msg[idx])){
    if ((yylval = (double)atof(msg+idx)) == -1){
      abort ();
      return NUM;
    }
  }
  
  /* Return end-of-input. */
  else if (msg[idx] == EOF)
    return YYEOF;
  /* Return a single char. */
  else
    return msg[idx];

  idx++;
}

double yycallparse(void){
  yylex();
  yyparse();
  return yylval;
}

/* Called by yyparse on error. */
void yyerror(char const *s){
  fprintf (stderr, "%s\n", s);
}
