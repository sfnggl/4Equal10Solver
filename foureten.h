#ifndef F_EQ_10_H
#define F_EQ_10_H

#define MAX_BOUND 30720 // 20 * 6 * 4^4

#include "sys/types.h"

// Check out BISON and write small numerical expression parser
typedef enum { OFF = 0, ON, EOF } par;
typedef struct {
  par gamma;
  char operators[3];
  float weights[3];
} syntax;
typedef struct {
  par gamma;
  const char operators[3] = {'?','?','?'};
  const float weights[3] = {.5f,.5f,.5f};
} any_syntax;

// TODO 1: work on calc.y to accept a array of chars and
// build a minimal API
// TODO 2: lookup MD4 and implement as a fast quick hash
// to implement the search space
// TODO 3: write agent with BSP (all costs are unitary, so
// dijkstra is not too useful)
// TODO 4: put all the parts together, implement statistics
// analysis (say runtime)
// TODO 5: actually use it to solve the damn game

int generate_from_any_syntax(syntax* s, char* msg);
int generate_from_syntax(syntax* s, char* msg);
void change_order(syntax* s);
void change_parity(syntax* s);
int concatenate(uint* argv, syntax* s, char* msg);
int parse(char* msg);

#endif
