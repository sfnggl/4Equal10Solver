#include <stdio.h>
#include <stdlib.h>
#include "time.h"

extern char charvalues[16];
extern int swap[6];
extern int constcombs[24];
extern unsigned int opcombs[64];

char* bytes_to_str(unsigned int bytes);
void bin (unsigned n);
unsigned int cons_bytes_mod_16(unsigned int string, int offset);
void read_bytes_to_char(unsigned int* buf, char* off_buf, int offset_flag);
unsigned int fourrandop(void);
