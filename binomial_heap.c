#include "binomial_heap.h"


static BinomialNode *merge_bin_heap(BinomialHeap *bh1, BinomialHeap *bh2);

static BinomialNode *merge_tree(BinomialNode *n1, BinomialNode *n2);

static BinomialNode *union_bin_heap(BinomialHeap *bh1, BinomialHeap *bh2);

static void bin_heap_remove(BinomialHeap *heap, BinomialNode *node, BinomialNode *prev);

static BinomialNode* reverse_list(BinomialNode* node);

BinomialHeap *create_bin_heap() {
  BinomialHeap *heap = (BinomialHeap *)malloc(sizeof(BinomialHeap));
  if (heap != NULL)
    heap->head = NULL;
  return heap;
}

BinomialNode *create_bin_node(void *value, unsigned int key) {
  BinomialNode *node = (BinomialNode *)malloc(sizeof(BinomialNode));
  if (node != NULL) {
    node->value_ptr = value;
    node->key_value = key;
    node->child = NULL;
    node->parent = NULL;
    node->sibling = NULL;
    node->degree = 0;
  }
  return node;
}

static BinomialNode *merge_bin_heap(BinomialHeap *bh1, BinomialHeap *bh2) {
  if ((bh1->head == NULL) && (bh2->head == NULL))
    return NULL;
  if (bh2->head == NULL)
    return bh1->head;
  if (bh1->head == NULL)
    return bh2->head;

  BinomialNode *new_head;
  if (bh1->head->degree <= bh2->head->degree) {
    new_head = bh1->head;
    bh1->head = bh1->head->sibling;
  } else {
    new_head = bh2->head;
    bh2->head = bh2->head->sibling;
  }

  BinomialNode *iter = new_head;
  while ((bh1->head != NULL) && (bh2->head != NULL)) {
    if (bh1->head->degree <= bh2->head->degree) {
      iter->sibling = bh1->head;
      iter = iter->sibling;
      bh1->head = bh1->head->sibling;
    } else {
      iter->sibling = bh2->head;
      iter = iter->sibling;
      bh2->head = bh2->head->sibling;
    }
  }
  while (bh1->head != NULL) {
    iter->sibling = bh1->head;
    iter = iter->sibling;
    bh1->head = bh1->head->sibling;
  }
  while (bh2->head != NULL) {
    iter->sibling = bh2->head;
    iter = iter->sibling;
    bh2->head = bh2->head->sibling;
  }
  return new_head;
}

static BinomialNode *merge_tree(BinomialNode *n1, BinomialNode *n2) {
  BinomialNode *temp;
  if (n1->key_value < n2->key_value) {
    temp = n1;
    n1 = n2;
    n2 = temp;
  }
  if (n1->sibling == n2)
    n1->sibling = n2->sibling;
  n2->sibling = n1->child;
  n2->parent = n1;
  n1->child = n2;
  n1->degree++;
  return n1;
}

static BinomialNode *union_bin_heap(BinomialHeap *bh1, BinomialHeap *bh2) {
  BinomialNode *new_head = merge_bin_heap(bh1, bh2);

  if (new_head == NULL)
    return NULL;

  BinomialNode *curr = new_head;
  BinomialNode *next = curr->sibling;
  BinomialNode *prev = NULL;
  while (next != NULL) {
    if ((curr->degree != next->degree) ||
        ((next->sibling != NULL) && (curr->degree == next->sibling->degree))) {
      prev = curr;
      curr = next;
      next = curr->sibling;
      continue;
    } else {
      curr = merge_tree(curr, next);
      if (prev == NULL)
        new_head = curr;
      else
        prev->sibling = curr;
      next = curr->sibling;
    }
  }
  return new_head;
}

void bin_heap_enqueue(BinomialHeap *bh1, void *value, unsigned int key) {
  if (bh1 == NULL)
    return;
  BinomialNode *node = create_bin_node(value, key);
  if (node == NULL)
    return;
  BinomialHeap *tempheap = create_bin_heap();
  tempheap->head = node;
  bh1->head = union_bin_heap(bh1, tempheap);
  free(tempheap);
}

static void bin_heap_remove(BinomialHeap *heap, BinomialNode *node,
                     BinomialNode *prev) {
  if (heap->head == node)
    heap->head = node->sibling;
  else
    prev->sibling = node->sibling;

  BinomialHeap *tempheap = create_bin_heap();

  tempheap->head = reverse_list(node->child);
  
  heap->head = union_bin_heap(heap, tempheap);
}

static BinomialNode* reverse_list(BinomialNode* node){
	BinomialNode* new_head = NULL;
	while (node != NULL) {
		BinomialNode *sibling = node->sibling;
		node->parent = NULL;
		node->sibling = new_head;
		new_head = node;
		node = sibling;
  }
	return new_head;	
}

BinomialNode *bin_heap_dequeue(BinomialHeap *heap) {
  if ((heap == NULL) || (heap->head == NULL))
    return NULL;
  BinomialNode *iter = heap->head->sibling;
  BinomialNode *iter_prev = heap->head;
  BinomialNode *max_node = heap->head;
  BinomialNode *prev_node = NULL;
  while (iter != NULL) {
    if (max_node->key_value < iter->key_value) {
      prev_node = iter_prev;
      max_node = iter;
    }
    iter_prev = iter;
    iter = iter->sibling;
  }

  bin_heap_remove(heap, max_node, prev_node);
  max_node->sibling = NULL;
  max_node->child = NULL;
  return max_node;
}


void delete_heap(BinomialHeap* heap){
	BinomialNode* node = bin_heap_dequeue(heap);
	while (node != NULL){
		free(node);
		node = bin_heap_dequeue(heap);
	}
	
}

