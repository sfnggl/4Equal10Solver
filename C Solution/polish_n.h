#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <stdbool.h>
#include <errno.h>
#include <inttypes.h>

#define STACK_SIZE 4
#define STACK_MEMSET 0
#define STR_TO_IN_LEN 10
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

// input : a PN expression
// output : its evaluation

typedef struct pnToken {
	int value;
	int (*operator)(int a, int b);
} pnToken;

typedef struct pnNode {
	pnToken node;
	struct pnNode *left;
	struct pnNode *right;
} pnNode;

extern int evalStr(char *str);
extern pnNode* buildPNTree(pnToken *buffer);
extern int evalPNTree(pnNode *tree);
extern void printPNTree(pnNode *tree, char *prefix);
extern _Bool spawnBracket(pnNode *node1, pnNode *node2);
void printINFromPN(pnNode *tree, char buffer[STR_TO_IN_LEN]);
extern void printResult(int result);
