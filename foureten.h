#ifndef F_EQ_10_H
#define F_EQ_10_H

#define MAX_BOUND 30720 // 20 * 6 * 4^4
#define LENGTH 3

#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef EOF
#undef EOF
#endif

typedef enum operator_kind { NONE = 0, PLUS, MINUS, TIMES, FRAC, ANY, POPEN, PCLOSE, EOF, OP_N } Operator_Kind;
typedef char* Print;
typedef enum parity { OFF = 0, ON, END } PARITY;
typedef struct {
  Operator_Kind kind;
  Print what;
} Token;
typedef struct {
  size_t size;
  Token* tokens;
} Dictionary;
typedef struct {
  PARITY gamma;
  Token operators[3];
  float weights[4];
} syntax;

int generate_from_any_syntax(char* msg);
int generate_from_syntax(syntax* s, char* msg);
int generate_to_syntax(syntax* s, char* msg);
void change_order(syntax* s);
void change_parity(syntax* s);
int concatenate(uint* argv, syntax* s, char* msg);
int parse(char* msg);
Token* get_token_by_kind(Dictionary* dict, Operator_Kind kind);
Token* get_token_by_string(Dictionary* dict, Print str);

static syntax any_syntax = {
  .gamma=OFF,
  .operators={
    { .kind = ANY, .what="?" },
    { .kind = ANY, .what="?" },
    { .kind = ANY, .what="?" }
  },
  .weights={0.5f,0.5f,0.5f,0.0f}
};

static Token tokens[] = {
  {PLUS, "+"},
  {MINUS, "-"},
  {TIMES, "*"},
  {FRAC, "/"},
  {ANY, "?"}
};

static Token parens[] = {
  { .kind = POPEN, .what="(" },
  { .kind = PCLOSE, .what=")" },
  { .kind = EOF, .what="" },
};

static Dictionary dictionary = {
  .size = 5,
  .tokens = tokens
};

// TODO 0: Implement syntax rule
// and the expression generator
// TODO 1: work on calc.y to accept a array of chars and
// build a minimal API (WIP)
// TODO 2: lookup MD4 and implement as a fast quick hash
// to implement the search space
// TODO 3: write agent with BSP (all costs are unitary, so
// dijkstra is not too useful)
// TODO 4: put all the parts together, implement statistics
// analysis (say runtime)
// TODO 5: actually use it to solve the damn game

#define ANY_TOKEN() ((&dictionary)->tokens+(rand()%(dictionary.size - 1)))
#define PARENS(g) (&(parens[g]))
#define OPERATOR_FROM_KIND(op) (get_token_by_kind(&dictionary, op))
#define OPERATOR_FROM_STRING(str) (get_token_by_string(&dictionary, str))

#endif
