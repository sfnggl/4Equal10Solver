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

#define STACK_SIZE 16
#define STACK_MEMSET 0
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

enum mode { CONSTANT = 0, OPERATOR = 1 };
extern _Bool override;

typedef struct exprToken{
	char id;
	 int value;
	 int (*operator)( int a,  int b);
	enum mode mode;
	_Bool hold;
} exprToken;

typedef struct exprTokenBuffer{
	exprToken* tokens;
	 int length;
} exprTokenBuffer;

typedef struct exprNode {
	exprToken node;
	struct exprNode *left;
	struct exprNode *right;
} exprNode;

typedef struct exprTree {
	exprNode *root;
} exprTree;

typedef struct exprTokenStack {
	ushort t_Count;
	u_char t_Buffer[STACK_SIZE];
} exprTokenStack ;

 int unckd_add( int a,  int b);
 int unckd_sub( int a,  int b);
 int unckd_mult( int a,  int b);
 int unckd_safediv( int a,  int b);

exprTokenStack* tokenStackCreate(void);
void tokenStackPush(exprTokenStack* stack, u_char new_value);
u_char tokenStackPop(exprTokenStack* stack);

extern exprTokenBuffer* parseTree(const char *str);
extern int buildTree(exprTokenBuffer *buf);
extern void insertRoot(exprTree *tree, exprToken *op_node, exprToken *const_node);
extern void insertNewRoot(exprTree* tree, exprToken* op_node);
extern void insertNode(exprTree* tree, exprToken* op_node, exprToken* const_node, _Bool hold);
extern void insertLastNode(exprTree* tree, exprToken* const_node);
extern _Bool checkTree(exprNode *root);
extern int evalTree(exprNode* root);
extern void visitTree(exprNode* root);
extern void freeTree(exprNode *root);
extern int evalStr(const char* str);
