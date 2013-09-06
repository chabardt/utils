#include "../utils.h"

int main () {
	binary *b1, *b2;
	puts ("Copy location : -2, 15, 31.") ;
	puts ("Copy 3 bits") ;
	b1 = binary_new ("", 32) ; // 32 0-bits.	
	b2 = binary_new ("101", 3) ; 

	binary_cpy (b1, b2, -2) ;
	binary_cpy (b1, b2, 15) ;
	binary_cpy (b1, b2, 31) ;

	// final number should be 10010101011010010110101010010101

	binary_display (b1) ;
	binary_display (b2) ;
	binary_delete (b1) ;
	binary_delete (b2) ;

	puts ("Copy 16 bits") ;
	b1 = binary_new ("", 32) ; // 32 0-bits.	
	b2 = binary_new ("1000000000000001", 16) ; 

	binary_cpy (b1, b2, -2) ;
	binary_cpy (b1, b2, 15) ;
	binary_cpy (b1, b2, 31) ;

	// final number should be 10010101011010010110101010010101

	binary_display (b1) ;
	binary_display (b2) ;
	binary_delete (b1) ;
	binary_delete (b2) ;

	puts ("copy 24 bits") ;
	b1 = binary_new ("", 32) ; // 32 0-bits.	
	b2 = binary_new ("100000000000000000000001", 24) ; 

	binary_cpy (b1, b2, -2) ;
	binary_cpy (b1, b2, 15) ;
	binary_cpy (b1, b2, 31) ;

	// final number should be 10010101011010010110101010010101

	binary_display (b1) ;
	binary_display (b2) ;
	binary_delete (b1) ;
	binary_delete (b2) ;

	return 0 ; 
}
