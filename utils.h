#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>

// BINARY NUMBER MANIPULATION

typedef struct binary {
	unsigned int l ;
	unsigned char *bytes ;
} binary ;

// Store a binary coded with ascii chars in a bytes array. User-Friendly implementation.
binary* binary_new (char *str, unsigned int l) ;

void binary_delete (binary *b) ;

// return the remaining capacity of buf, if negativ then Buffer Overflow. offset can be negativ.
int binary_cpy (	binary *des, 
			binary *src,
			int offset) ;

// Send '0' or '1'. User_Friendly implementation.
char binary_read_next_bit (	binary *b,
				size_t offset) ;

// For debugging purpose.
void binary_display (binary *b) ;

// END OF BINARY NUMBER


// PRIORITY QUEUE (implemented with Binary Heap, stored in an array).
typedef struct pqueue {

	size_t size ;
	size_t capacity ;
	int (*p_cmp) (const void* d1, const void* d2) ;
	void ** data ;
} pqueue ;


// allocates memory
pqueue* pqueue_new (	size_t capacity,
			int (*p_cmp) (const void* d1, const void* d2)) ;
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

int pqueue_size (pqueue* q) ;

int pqueue_is_empty (pqueue* q) ;

void pqueue_display (	pqueue* q,
			void (*display) (const void* d)) ;
// END OF PRIORITY QUEUE.

#endif



