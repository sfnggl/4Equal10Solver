#include <stdio.h>
#include "calc.h"
#include "foureten.h"

int main(void){
  const char * test = "1+2+3+4";
  yystrdup(test);
  yycallparse();
  return 0;
}
