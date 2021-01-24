#include "binomial_heap.h"

int main(int argc, char *argv[])

{
#define KEYWORD_LENGTH 100
#define MAX_FILE_PATH_LENGTH 25

  printf("********************Binomial Heap Priority Queue "
         "Test*********************\n");

  BinomialHeap *heap = create_bin_heap();
  printf("Constructing Binomial Heap Priority Queue\n");

  bin_heap_enqueue(heap, NULL, 5);
  printf("Enqueued Value: %i\n", 5);

  bin_heap_enqueue(heap, NULL, 200);
  printf("Enqueued Value: %i\n", 200);

  bin_heap_enqueue(heap, NULL, 5010);
  printf("Enqueued Value: %i\n", 5010);

  bin_heap_enqueue(heap, NULL, 4000);
  printf("Enqueued Value: %i\n", 4000);

  bin_heap_enqueue(heap, NULL, 58);
  printf("Enqueued Value: %i\n", 58);

  bin_heap_enqueue(heap, NULL, 69);
  printf("Enqueued Value: %i\n", 69);

  bin_heap_enqueue(heap, NULL, 5);
  printf("Enqueued Value: %i\n", 5);

  printf("Finished Construction\n\n");
  printf("Start Dequeing Binomial Heap\n");

  printf("Dequed Value: %i\n", bin_heap_dequeue(heap)->key_value);
  printf("Dequed Value: %i\n", bin_heap_dequeue(heap)->key_value);
  printf("Dequed Value: %i\n", bin_heap_dequeue(heap)->key_value);
  printf("Dequed Value: %i\n", bin_heap_dequeue(heap)->key_value);
  printf("Dequed Value: %i\n", bin_heap_dequeue(heap)->key_value);
  printf("Dequed Value: %i\n", bin_heap_dequeue(heap)->key_value);
  printf("Dequed Value: %i\n", bin_heap_dequeue(heap)->key_value);

  printf("Test Finished\n");

  return 0;
}
