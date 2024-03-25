#include <stdio.h>
#include <stdlib.h>

static char charvalues[16] = {
  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 43, 45, 42, 47, 63, 33
};

void
bin (unsigned n)
{
  unsigned i;
  for (i = 1 << 31; i > 0; i = i / 2)
	(n & i) ? printf ("1 ") : printf ("0 ");
}

unsigned int
cons_bytes_mod_16 (unsigned int string, int offset)
{
  // unsigned int masks[4] = { 0x0fffffff, 0xff0fffff, 0xffff0fff, 0xffffff0f };
  unsigned int mask = 0xf0000000;
  unsigned int str_off = string;
  if (offset == 1)
	{
	  str_off = str_off >> 4;
	}
  for (int i = 0; i < 4; i++)
	{
	  str_off = str_off & (~mask);
	  mask = mask >> 8;
	}
  return str_off;
}

void
read_bytes_to_char(unsigned int* buf, char* off_buf, int offset_flag)
{
  unsigned int mask = 0x0f000000;
  for (int i = 0; i < 4; i++)
  {
    int ind = (*buf & mask) >> 8 * (3 - i);
    if (offset_flag && i == 0) { mask >>= 8; continue; }
    off_buf[i * 2 - offset_flag] = charvalues[ind];
    mask >>= 8;
  }
}

int
main ()
{
  // unsigned int string = 0x01234567;
  unsigned int string = 0xa9b5c12;
  unsigned int odd_chars = cons_bytes_mod_16 (string, 0);
  unsigned int even_chars = cons_bytes_mod_16 (string, 1);
  char* res = calloc(1, sizeof(char)*8);
  read_bytes_to_char (&odd_chars, res, 0);
  read_bytes_to_char (&even_chars, res, 1);
  fprintf(stdout, "%s\n", res);
  // printf ("0x%x = %s\n", string, (unsigned char *) &string);
  // printf ("0x%x = %s\n", odd_chars, (unsigned char *) &odd_chars);
  // printf ("0x%x = %s\n", even_chars, (unsigned char *) &even_chars);
  return 0;
}
