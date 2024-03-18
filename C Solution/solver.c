#include "polish_n.h"

// exprTree *root = NULL; /* initialized to NULL */

int main(int argc, char *argv[]){

	/* TEST STRINGS */
	// const char *dummy = "*1+4+23";
	// const char *dummy = "+1+2+34";
	// const char *dummy = "/*54*12";
	// const char *dummy = "+*25*01";
	const char *dummy = "+*3+121";
	printResult(evalStr(dummy));

	return 0;
}
