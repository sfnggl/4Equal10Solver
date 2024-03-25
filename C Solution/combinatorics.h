#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SPACE_SIZE 64 * 256

extern char* rand_start_state(char* ops, char* consts);
unsigned int cons_bytes_mod_16 (unsigned int string, int offset);
extern void permute(char* a, int i, int n);
extern void read_bytes_to_char(unsigned int* buf, char* off_buf, int offset_flag);
extern char** solution_space(char* args);
