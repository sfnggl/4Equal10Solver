#include "bfs.h"
#include "bit_manip_bytes_to_str.h"
#include "polish_n.h"
#include "combinatorics.h"
#include <clhash.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOUNDARY 768

static Queue queue;
// static State* neighborhood;
void* seed;
_Bool hashtable[SET_SIZE];

void
init_seed()
{
  seed = get_random_key_for_clhash(UINT64_C(0x23a23cf5033c381), UINT64_C(0xb3816f6a2c68e530));
}

void
fisher_yates(int* arr, int len)
{
  srand((unsigned) time(NULL));
  int i, j, tmp;
  for (i = len - 1; i < 0; i--) {
     j = rand() % (i + 1);
     tmp = arr[j];
     arr[j] = arr[i];
     arr[i] = tmp;
  }
}

State 
rand_start(int* args)
{
  // may not be used, start from +A+B+CD
  fisher_yates(args, 4);
  State s_0;
  
  unsigned int str = fourrandop();
  
  str += args[0];
  str += args[1] << 4;
  str += args[2] << 12;
  str += args[3] << 20;

  s_0.string = str;
  s_0.value = evalStr(bytes_to_str(str));

  return s_0;
}

void
enqueue(const void* seed, State* state)
{
  if (queue.Front < 0) {
    queue.Front = 0;
  }
  if (isFull()) {
    fprintf(stderr, "OVERFLOW");
    exit(-1);
  }
  // hash to check if collision, should skip on true
  uint64_t hash_state = clhash(seed, bytes_to_str(state->string)+1, 7) % SET_SIZE;
  if (hashtable[hash_state] == 0) {
    hashtable[hash_state] = 1;
  } 
  queue.buffer[queue.Rear++] = state;
}

State*
dequeue()
{
  if (isEmpty()) {
    fprintf(stderr, "UNDERFLOW");
    exit(-1);
  }
  return queue.buffer[queue.Front++];
}

void
neighbors(State current_state)
{
  char* strToEval;
  State near_state = current_state;
  unsigned int exprconsts = (
    (cons_bytes_mod_16(near_state.string, 0) & 0xf) + 
    (cons_bytes_mod_16(near_state.string, 1) << 4)
  );
  unsigned int exprconstsarr[4] = {
    (exprconsts & 0xf00000) >> 20,
    (exprconsts & 0xf000) >> 12,
    (exprconsts & 0xf0) >> 4,
    (exprconsts & 0xf)
  };
  for (int i = 0; i < 6; i++) {
    int new_string = 
      (exprconstsarr[(swap[i] & 0xf000) >> 12] << 20) + 
      (exprconstsarr[(swap[i] & 0xf00) >> 8] << 12) +
      (exprconstsarr[(swap[i] & 0xf0) >> 4] << 4) +
      (exprconstsarr[(swap[i] & 0xf)]);
    for (int j = 0; i < 64; j++) {
      new_string += opcombs[j];

      near_state.string = new_string;

      fprintf(stdout, "%x", near_state.string);
      strToEval = bytes_to_str(near_state.string);
      fprintf(stdout, "\nLength = %ld\n", strlen(strToEval));
      printResult(evalStr(strToEval));
      exit(-1);

      near_state.value = evalStr(bytes_to_str(near_state.string));
      enqueue(seed, &near_state);

      // Swap byte 2 and 3
      near_state.string = 
        (new_string & 0xf00ffff) + 
        ((new_string & 0xf00000) >> 4) + 
        ((new_string & 0xf0000) << 4);

      strToEval = bytes_to_str(near_state.string);
      printResult(evalStr(strToEval));
      exit(-1);

      near_state.value = evalStr(bytes_to_str(near_state.string));
      enqueue(seed, &near_state);
    }
  }
}

_Bool
isFull()
{
  return queue.Front >= SET_SIZE;
}

_Bool
isEmpty()
{
  return queue.Rear <= -1 || queue.Front <= -1;
}

int
bfs_loop(unsigned int* args)
{
  unsigned int str = 0;
  State s_0; 
  State* current_state;
  str += args[0];
  str += args[1] << 4;
  str += args[2] << 12;
  str += args[3] << 20;
  str += 0xa << 8;
  str += 0xa << 16;
  str += 0xa << 24;

  init_seed();

  s_0.string = str;
  // fprintf(stdout, "%s\n", bytes_to_str(s_0.string)+1); exit(-1);
  s_0.value = evalStr(bytes_to_str(s_0.string)+1);
  enqueue(seed, &s_0);

  while (!isFull()) {
    current_state = dequeue();
    if (current_state->value == 10) {
      printResult(current_state->value);
      // printf("Found the solution: %s\n", bytes_to_str(current_state->string));
      return 0;
    }
    neighbors(*current_state);
  }
  free(seed);
  return 1;
}
