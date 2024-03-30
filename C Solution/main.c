#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char* argv[])
{
  if (argc != 5) {
    fprintf(stderr, "Needed more than %d argument/s", argc);
    return -1;
  }
  unsigned int args[4];
  for (int i = 1; i < argc; i++) {
    if (strlen(argv[i]) > 1) {
      return -1; 
    }
    args[i-1] = (unsigned int)strtol(argv[i], NULL, 10) % 10;
  }
  return bfs_loop((unsigned int*)&args);
}
