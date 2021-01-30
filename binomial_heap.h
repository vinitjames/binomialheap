#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinomialNode {
  void *value_ptr;
  unsigned int key_value;
  unsigned int degree;
  struct BinomialNode *child;
  struct BinomialNode *parent;
  struct BinomialNode *sibling;
} BinomialNode;

typedef struct BinomialHeap {
  BinomialNode *head;
} BinomialHeap;

BinomialHeap *create_bin_heap();

BinomialNode *create_bin_node(void *value, unsigned int key);

void bin_heap_enqueue(BinomialHeap *bh1, void *value, unsigned int key);

BinomialNode *bin_heap_dequeue(BinomialHeap *heap);

void delete_heap(BinomialHeap *heap);

#endif /* BINOMIAL_HEAP_H */
