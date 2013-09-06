#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../utils.h"

typedef struct test{
	int i;
} test;

test* test_new (int i) {
	test* result = NULL;
	result = malloc (sizeof (*result)); 
	assert (result != NULL) ;
	result->i = i;
	return result;
} 

void test_delete (test* t) {
	if (t != NULL)
		free (t); 
}

int test_cmp (const void* d1, const void* d2) {
	return ((test*)d1)->i - ((test*)d2)->i;
}

void test_display (const void* d) {
	printf ("%d\n", ((test*)d)->i) ;
}


int main () {
	// test on successive insertion
	puts ("\n\ttest n1") ;

	pqueue *q = NULL;
	test* t = NULL;
	int i, j;

	srand (time(NULL));

	q = pqueue_new (10, test_cmp);

	for (i=0; i<10; ++i) {
		t = test_new(rand()%20+1) ;
		pqueue_insert (q, t) ;
	}
	for (i=0; i<10; ++i) {	
		t = (test*)pqueue_pop(q);
		printf ("%d\n", ((test*)t)->i) ;
		test_delete (t);
	}
	pqueue_delete(q) ;


	// test on allocation from a already defined array.
	puts ("\n\ttest n2.");

	q = NULL;
	test **tab = NULL;
	tab = (test**) malloc (20*sizeof(test*));
	for (i=0; i<20; ++i) {
		if (rand()%2) {
			tab[i] = NULL ;
			puts ("NULL") ;
		} else {
			tab[i] = test_new(rand()%20+1) ;
			printf ("%d\n", tab[i]->i) ;
		}
	}
	puts ("") ;
	q = pqueue_new_with_data (test_cmp, (void**) tab, 20) ;
	pqueue_display (q, test_display) ;
	pqueue_delete (q) ;
	free (tab);

	// test compare big data.
	puts ("\n\ttest n3.");

	for (i=1000; i<10000000; i*=10) {
		printf ("\n with %d elements. ", i);

		printf ("\n Insertion ");
		q = pqueue_new (i, test_cmp);

		for (j=0; j<i; ++j) {
			t = test_new(rand()%i+1) ;
			pqueue_insert (q, t) ;
		}
		pqueue_delete(q) ;
	
		printf ("\n Allocation ");
		tab = (test**) malloc (i*sizeof(test*));
		for (j=0; j<i; ++j) {
			if (rand()%2) {
				tab[j] = NULL ;
			} else {
				tab[j] = test_new(rand()%i+1) ;
			}
		}

		q = pqueue_new_with_data (test_cmp, (void**) tab, i) ;
		pqueue_delete (q) ;
		free (tab);

		puts ("");
	}
}



