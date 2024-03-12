#include "solver.h"

exprTree *root = NULL; /* initialized to NULL */


int main(int argc, char *argv[]){
	/* consume expression 
	 * create trees from buffer when stopped
	 * continue until eating the whole expression*/

	const char* dummy = "1*2*3+4";
	/* const char* dummy = "1+(2+3)+4"; */
	/* const char* dummy = "1*2+(3+4)"; */
	/* const char* dummy = "1*(2/3+2)"; */

	fprintf(stdout, "%s = ", dummy);
	fprintf(stdout, "\n");

	if(evalStr(dummy) == 0){
		return 0;
	} else {
		return 1;
	}

}
