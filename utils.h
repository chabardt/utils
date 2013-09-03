#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>

typedef struct pqueue {
	size_t size ;
	size_t capacity ;
	int (*p_cmp) (const void* d1, const void* d2) ;
	void ** data ;
} pqueue ;


// allocates memory
pqueue* pqueue_new (size_t capacity, int (*p_cmp) (const void* d1, const void* d2)) ;
// Initialize in O ( n ) instead of successiv insertions in O ( n log (n) ). data can have null value inside.
pqueue* pqueue_new_with_data (	int (*p_cmp) (const void* d1, const void* d2),
					void **data,
					size_t size) ;

// deallocates memory
void pqueue_delete (pqueue* q) ;

// add an element to the queue with an associated priority.
void pqueue_insert (pqueue* q, const void* d) ;

// remove the element from the queue that has the highest priority and return it.
void* pqueue_pop (pqueue* q) ;

// return the highest-priority ellement but does not modify the queue.
void* pqueue_peek (pqueue* q) ;

int pqueue_is_empty (pqueue* q) ;

void pqueue_display (pqueue* q, void (*display) (const void* d)) ;

#endif



