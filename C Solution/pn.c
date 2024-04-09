#include "polish_n.h"

static int cursor;
static int length;
static char buffed_char;
char in_str[STR_TO_IN_LEN] = {'\0'};

int unckd_add(int a, int b){ return a+b; }
int unckd_sub(int a, int b){ return a-b; }
int unckd_mult(int a, int b){ return a*b; }
int unckd_safediv(int a, int b){
	if(b == 0.0){ return INT_MIN; }
	else{ return (int)round(a / b); }
}

int
evalStr(char *str)
{
	length = strlen(str);
	pnToken *buffer = calloc(length, sizeof(pnToken));
	int i = 0;
	char num[1];
	while(i < strlen(str))
	{
		int	char_base10 = (int)strtol(strncpy(num, str+i, 1), NULL, 10);
		buffer[i].value =  char_base10 || ((int)str[i] == 48) ? char_base10 : -1 * (int)str[i];
		switch((int)str[i])
		{
			case 42:
				buffer[i].operator = &unckd_mult;
				break;
			case 43:
				buffer[i].operator = &unckd_add;
				break;
			case 45:
				buffer[i].operator = &unckd_sub;
				break;
			case 47:
				buffer[i].operator = &unckd_safediv;
				break;
			default: buffer[i].operator = NULL;
		}
		i++;
	}

	// fprintf(stdout, "Legend:\n%c\t%p\n%c\t%p\n%c\t%p\n%c\t%p\n\n\n",
	// 		42, &unckd_mult, 43, &unckd_add, 45, &unckd_sub, 47, &unckd_safediv);

  memset(in_str, '\0', STR_TO_IN_LEN);
	pnNode* tree = buildPNTree(buffer);
	printINFromPN(tree, in_str);

	int result = evalPNTree(tree);

	free(buffer);
	free(tree);

  cursor = 0;

	return result;

}

pnNode* 
buildPNTree(pnToken *buffer)
{
	if(cursor >= length) { return NULL; }

	// printf("\n%d\n", cursor);

	pnNode *node = calloc(1, sizeof(pnNode));
	node->node.value = buffer[cursor].value;
	node->node.operator = buffer[cursor].operator;

	if(node->node.operator == NULL){ return node; }

	cursor++;
	node->left = buildPNTree(buffer);
	cursor++;
	node->right = buildPNTree(buffer);

	return node;
}

int 
evalPNTree(pnNode *tree)
{
	if(tree->node.value >= 0) {return tree->node.value;}
	else return tree->node.operator(evalPNTree(tree->left), evalPNTree(tree->right));
}

void
printINFromPN(pnNode *tree, char buffer[STR_TO_IN_LEN])
{
	if(tree == NULL){return;}

	buffed_char = (char) (tree->node.value + 48);

	if(tree->node.value >= 0) { strcat(buffer, &buffed_char); return; }

	_Bool bracket = spawnBracket(tree, tree->left);

	if(bracket) { buffed_char = (char)40; strcat(buffer, &buffed_char); }

	printINFromPN(tree->left, buffer);

	if(bracket) { buffed_char = (char)41; strcat(buffer, &buffed_char); }

	buffed_char = (char) (tree->node.value * -1);
	strcat(buffer, &buffed_char);

	bracket = spawnBracket(tree, tree->right);
	if(bracket) { buffed_char = (char)40; strcat(buffer, &buffed_char); }

	printINFromPN(tree->right, buffer);

	if(bracket) { buffed_char = (char)41; strcat(buffer, &buffed_char); }

}

_Bool
spawnBracket(pnNode *node1, pnNode *node2)
{
	if(node1 == NULL){exit(1);}
	if(node2 == NULL){return false;}

	if(node1->node.value < 0 && node2->node.value < 0)
	{
		int order = node1->node.value - node2->node.value;
		if(node1->node.value == -42 || (order > 0)) { return true; }
		if(node1->node.value == -47 || (order <= 0)) { return true; }
	}

	return false;
}

void
printResult(int result)
{
	if(result == 10){
		fprintf(stdout, GREEN"\nFound the solution:\n\n\t%s = %d\n\n"RESET, in_str, result);
	} else {
		fprintf(stdout, RED"\n%s = %d\n\nis not a solution\n\n"RESET, in_str, result);
	}
  memset(in_str, '\0', STR_TO_IN_LEN);
}
