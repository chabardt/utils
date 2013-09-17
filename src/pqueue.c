#include "../utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// binary heap handling.
#define PARENT(i) (i-1)/2

#define LEFT_CHILD(i) (2*i +1)

#define RIGHT_CHILD(i) (2*i +2)

void heapify (pqueue* q, size_t i) {
	assert (q != NULL) ;
	void* swap_tmp = NULL ;
	size_t left = LEFT_CHILD(i), right = RIGHT_CHILD(i), largest = i ;

	if (left < q->size && q->p_cmp (q->data[left], q->data[i]) > 0) {
		largest = left ;
	}
 
	if (right < q->size && q->p_cmp (q->data[right], q->data[largest]) > 0 ) {
		largest = right ;
	}
	
	if (largest != i) {
		swap_tmp = q->data[largest] ;
		q->data[largest] = q->data[i] ;
		q->data[i] = swap_tmp ;
		heapify (q, largest) ;
	}
}
// End binary heap handling.


pqueue* pqueue_new (size_t capacity, int (*p_cmp) (const void* d1, const void* d2) ) {
	assert (capacity > 0 && p_cmp != NULL) ; 
	pqueue* result ;
	result = malloc (sizeof (*result)) ;
	assert (result != NULL) ;

	result->p_cmp = p_cmp;
	result->data = malloc (capacity * sizeof (*(result->data))) ;
	assert (result->data != NULL) ;

	result->size = 0 ;
	result->capacity = capacity ;
	return result ;
}

pqueue* pqueue_new_with_data (	int (*p_cmp) (const void* d1, const void* d2),
				void **data,
				size_t size) {
	assert (size > 0 && p_cmp != NULL && data != NULL) ;
	pqueue* result ;
	result = malloc (sizeof (*result)) ;
	assert (result != NULL) ;
	result->data = malloc (size * sizeof (*(result->data))) ;
	assert (result->data != NULL) ;
	result->p_cmp = p_cmp ;

	int i = 0, j=0 ;
	result->capacity = size ;
	result->size = size ;

	// pushing all null data at the end and calculating actual size. That way we respect the shape propriety.
	while (i < size) {
		while (i < size && data[i] != NULL) {
			result->data[i] = data[i] ;
			i++ ;
		}
		if (i == size) {break ;}
		j = size-1 ;
		while (j > i && data[j] == NULL ) {j-- ;}
		if (j == i) {
			break ;
		}
		result->data[i] = data[j] ;
		data[j] = NULL ;
		i++ ;
	}

	result->size = i ;

	// the heap propriety
	for (i=result->size/2; i>=0; --i) {
		heapify (result, i) ;
	}
	return result ;
}

void pqueue_delete (pqueue* q) {
	if (q == NULL) return ;

	int i = 0 ;
	for (i=0; i<q->size; ++i) {
		free (q->data[i]) ;
	}
	free (q->data) ;
	free (q) ;
}

void pqueue_insert (pqueue* q, const void* d) {
	assert (q != NULL) ;

	size_t i ;
	void* swap_tmp=NULL ;
	if (q->size >= q->capacity) { return ; }

	q->data[q->size] = (void*) d ;
	i = q->size ;
	q->size++ ;
	while (i>0 && q->p_cmp (q->data[i], q->data[PARENT(i)]) > 0) {
		swap_tmp = q->data[i] ;
		q->data[i] = q->data[PARENT(i)] ;
		q->data[PARENT(i)] = swap_tmp ;
		i = PARENT(i) ;
	}
}

void* pqueue_pop (pqueue *q) {
	assert (q != NULL) ;
	if (q->size < 1) return NULL ; 
	void *result = q->data[0] ;
	q->data[0] = q->data[q->size -1] ;
	q->size-- ;
	heapify (q, 0) ;
	return result ;
}

void* pqueue_peek (pqueue *q) {
	assert (q != NULL) ;
	if (q->size < 1) return NULL ;
	return q->data[0] ;
}

int pqueue_size (pqueue* q) {
	return q->size ;
}

int pqueue_is_empty (pqueue* q) {
	return q->size < 1 ;
}

void pqueue_display (pqueue* q, void (*display) (const void* d)) {
	assert (q != NULL && display != NULL) ;
	int i = 0 ;
	for (i=0 ; i<q->size; ++i) {
		display (q->data[i]) ;
	}
}
