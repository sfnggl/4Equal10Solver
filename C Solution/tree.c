#include "solver.h"

_Bool override = false;

 int unckd_add( int a,  int b){
	return a+b;
}

 int unckd_sub( int a,  int b){
	return a-b;
}

 int unckd_mult( int a,  int b){
	return a*b;
}

 int unckd_safediv( int a,  int b){
	if (b != 0) {
		return round(a / b);
	} else {
		return INT_MAX;
	}
}

exprTokenBuffer* parseTree(const char *str){
	override = false;
	exprToken* tokenized = calloc(strlen(str), sizeof(exprToken));
	int tokenId = 0;
	int i = 0;
	/* printf("%s\n", str); */
	/* for (i = 0; i < strlen(str); i++) */ 
	while (i < strlen(str) && strcmp(str+i, "\0")) {
		if((char)str[i] == 40) { override = true; }
		if((char)str[i] == 41) { override = false; }
		/* fprintf(stdout, "%c : %d | ", *(str+i), (char)str[i]); */
		tokenized[i].id = str[i];
		if((tokenId = (char)str[i]) >= 42 && tokenId < 48) {
			// operator 
			tokenized[i].value = INT_MAX - tokenId;
			tokenized[i].mode = OPERATOR;
			switch (tokenId) {
				case 42:
					tokenized[i].operator = &unckd_mult;
					tokenized[i].hold = true || override;
					break;
				case 43:
					tokenized[i].operator = &unckd_add;
					tokenized[i].hold = false || override;
					break;
				case 45:
					tokenized[i].operator = &unckd_sub;
					tokenized[i].hold = false || override;
					break;
				case 47:
					tokenized[i].operator = &unckd_safediv;
					tokenized[i].hold = true || override;
				default:
					tokenized[i].operator = NULL;
					tokenized[i].hold = false || override;
			}
		} else if (tokenId >= 48 && tokenId < 58) {
			// constant
			tokenized[i].value = tokenId;
			tokenized[i].mode = CONSTANT;
			tokenized[i].operator = NULL;
			tokenized[i].hold = false || override;
		}
		i++;
	}
	if (override) { // unclosed parathesis, wrong expression
		free(tokenized);
		return NULL;
	} else {
		exprTokenBuffer* buffer = calloc(1, sizeof(exprTokenBuffer));
		buffer->tokens = tokenized;
		buffer->length = i;
		return buffer;
	}
}

void insertRoot(exprTree *tree, exprToken *op_node, exprToken *const_node){
	if((tree = calloc(1, sizeof(exprTree))) != NULL){
		tree->root->node = *op_node;
		tree->root->left = calloc(1, sizeof(exprNode));
		tree->root->left->node = *const_node;
		tree->root->right = NULL;
	}
	else{
		exit(errno);
	}
}

void insertNewRoot(exprTree *tree, exprToken *op_node){
	exprTree *new_tree = NULL;
	if((new_tree = calloc(1, sizeof(exprTree))) != NULL){
		new_tree->root->node = *op_node;
		new_tree->root->left = tree->root;
		new_tree->root->right = NULL;
		tree = new_tree;
	}
}

void insertNode(exprTree* tree, exprToken *op_node, exprToken *const_node, bool hold){
	if(hold){
		for (exprNode* node = tree->root; node != NULL; node = node->left){
			if(node->right == NULL){
				node->right = calloc(1, sizeof(exprNode));
				node->right->node = *const_node;
				insertNewRoot(tree, op_node);
			}
		}
	} else {
		for (exprNode* node = tree->root; node != NULL; node = node->left){
			if(node->right == NULL){
				node->right = node->left;
				node->left = calloc(1, sizeof(exprNode));
				node->left->node = *op_node;
				node->left->left = calloc(1, sizeof(exprNode));
				node->left->left->node = *const_node;
			}
		}
	}
}

void insertLastNode(exprTree *tree, exprToken *const_node){
	for(exprNode* node = tree->root; node != NULL; node = node->left){
		if(node->right == NULL){
			node->right = calloc(1, sizeof(exprNode));
			node->right->node = *const_node;
		}
	}
}

 int evalTree(exprNode* root){
	exprNode current_node = *root;
	if (current_node.node.mode == CONSTANT) { return atoi(&(current_node.node.id)); }
	else {
		return current_node.node.operator(evalTree(current_node.left), evalTree(current_node.right));
	}
}

int buildTree(exprTokenBuffer* buf){

	 int offset = 0;
	 int result = 0;

	/* fprintf(stdout, "%d\n", buf->length); */
	exprNode* tree = calloc(buf->length + 1, sizeof(exprNode));
	exprNode* origin = tree;
	/* exprToken* token = NULL; */
	exprToken* tmp = NULL;
	_Bool flip = true;

	for( int i = 0; i < buf->length; i++){
		
		if(offset > i){exit(-1);}

		exprToken* token = &(buf->tokens[i]);

		/* fprintf(stdout, "\ */
		/* 		---- \ */
		/* 		%c\n \ */
		/* 		%d\n \ */
		/* 		%s\n \ */
		/* 		%b\n \ */
		/* 		Func = (%p)\n \ */
		/* 		at : %ld\n \ */
		/* 		---- \n", */ 
		/* 		token->id, */ 
		/* 		token->value, */ 
		/* 		token->mode == CONSTANT ? "CONSTANT" : "OPERATOR", */ 
		/* 		token->hold, */
		/* 		token->operator == NULL ? NULL : token->operator, */
		/* 		(long)&(buf->tokens[i]) */
		/* ); */

		if (token->mode == CONSTANT) {
		/*! TODO: Insert last constant
		*  \todo Insert last constant
		*/
			exit(0);
			tmp = token;
		} else {
			if(offset == 0){
				/*first iteration*/
				tree->node = *token;
				tree->left = tree+offset+1;
				tree->right = tree+offset+2;
				tree->left->node = *tmp;
				/* offset += 2; */
			}
			if (!flip && token->hold) {
				/*release tmp, move tree ptr*/
				tree[offset].right->node = *tmp;
				/* to be done ONLY ONCE */
				offset += 3;
				tree[offset].node = *token;
				tree[offset].left = tree;
				/* is this an infinite loop? */
				/* first line should be a stopgap */
				tree[offset].right = tree+offset+1;
				tree = tree+offset;
				offset = 0;
				/*TRIGGERS FIRST INTERACTION ROUTINE*/
			} else {
				/*put (op, A) pair along ptrs*/
				offset += 2;
				tree[offset].node = *token;
				tree[offset].left = tree+offset+1;
				tree[offset].right = tree+offset+2;
				tree[offset].left->node = *tmp;
			}
			flip = token->hold;
		}
	}

	/* visitTree(tree); */
	for(int i = 0; i < buf->length; i++){
		fprintf(stdout, 
		"\n\
		| %c | At: %d\n\
		| Left: %d\n\
		| Right: %d\n\
		\n", origin[i].node.id, (short)(&origin[i]), (short)origin[i].left, (short)origin[i].right);
	}
	fprintf(stdout, "Root t: %d\n", (short)tree);
	exit(-1);

	if (checkTree(tree)) {
		result = evalTree(tree);
		free(origin);
		fprintf(stdout, "%d\n", result);
		/* fflush(stdout); */
		if (result == 10) {
			return 0;
		} 
	}
	return 1;
}

_Bool checkTree(exprNode* root){
	if (root->node.mode == OPERATOR &&
			root->left != NULL && root->right != NULL) {
		return true;	
	} else if (root->node.mode == CONSTANT &&
			root->left == NULL && root->right == NULL) {
		return true;
	} else {
		return checkTree(root->left) && checkTree(root->right);
	}
}

int evalStr(const char *str){
	/* exprTokenBuffer *buf = parseTree(str); */
	if (buildTree(parseTree(str)) == 0) {
		fprintf(stdout, "%s%s%s", GREEN, "Found the solution:\n\tstr\n", RESET);
		return 0;
	} 
	return 1;
}

void visitTree(exprNode* root){
	if (root != NULL){
		fprintf(stdout, "\
				-----\n \
				%s\n \
				%c\n \
				-----\n \
				", 
				root->node.operator == NULL ? 
				"CONSTANT" : "OPERATOR", 
				root->node.value);
	} else {
		visitTree(root->left);
		visitTree(root->right);
	}
}

void freeTree(exprNode* root){
	if (root == NULL) {
		return;
	} else {
		freeTree(root->left);
		freeTree(root->right);
	}
	free(root);
}

