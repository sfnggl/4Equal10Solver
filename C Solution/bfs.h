#define SET_SIZE 20000 // > 4! * 764

typedef struct State
{
  unsigned int bytes;
  char string[8];
  int value;
} State;

typedef struct Queue
{
  State buffer[SET_SIZE];
  int Rear;
  int Front;
} Queue;

void fisher_yates(int* arr, int len);
State rand_start(int* args);
void neighbors(State* current_state);
void enqueue(const void* seed, State* state);
State dequeue();
_Bool isEmpty();
_Bool isFull();
int bfs_loop(unsigned int* args);
