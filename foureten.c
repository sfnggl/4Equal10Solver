#include "foureten.h"
  
#ifndef RAND_MAX
#include <limits.h>
#define RAND_MAX INT_MAX
#endif

static inline void automata_cell(syntax* s, char* msg, const size_t i){
  Token *next_token = NULL;
  if (i >= LENGTH){
    next_token = PARENS(s->gamma)->kind==POPEN?PARENS(END):PARENS(s->gamma);
    strcat(msg, next_token->what);
    return;
  } else if (((double)rand() / RAND_MAX) > s->weights[i]){
    next_token = PARENS(s->gamma);
    s->gamma++;
    strcat(msg, next_token->what);
  }
  next_token = OPERATOR_FROM_KIND(s->operators[i].kind);
  strcat(msg, next_token->kind==ANY?ANY_TOKEN()->what:next_token->what);
}

Token* get_token_by_kind(Dictionary* dict, Operator_Kind kind){
  for (Token* t = dict->tokens; t != NULL; t+=strlen(t->what)+1){
    if (t->kind == kind)
      return t;
  }
  return NULL;
}

Token* get_token_by_string(Dictionary* dict, Print str){
  for (Token* t = dict->tokens; t != NULL; t+=strlen(t->what)+1){
    if (!strcmp(t->what, str))
      return t;
  }
  return NULL;
}

int generate_from_any_syntax(char* msg){
  return generate_from_syntax(&any_syntax, msg);
}

int generate_from_syntax(syntax* s, char* msg){
  srand(time(NULL));
  if (NULL == s){
    fprintf(stderr,"No valid syntax structure was found\n");
    return -1;
  }
  for (size_t i = 0; i < LENGTH+1; i++){
    automata_cell(s, msg, i);
    if (NULL == msg) {
      fprintf(stderr,"Error generating the expression\n");
      return -1;
    }
  }
  return 0;
}

int generate_to_syntax(syntax* s, char* msg){
  if (NULL == msg){
    fprintf(stderr,"No valid expression was found\n");
    return -1;
  }
  if (NULL == s){
    s = calloc(1, sizeof(s));
    if (NULL == s){
      fprintf(stderr,"Error allocating space\n");
      return -1;
    }
  }
  return 0;
}

void change_order(syntax* s){}

void change_parity(syntax* s){}

int concatenate(uint* argv, syntax* s, char* msg){
  
  return 0;
}

int parse(char* msg){
  return 0;
}
