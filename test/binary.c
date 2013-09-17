#include "../utils.h"
#include <stdio.h>

int main () {
	binary *b1, *b2;
	puts ("Copy location : -2, 15, 31.") ;
	puts ("Copy 3 bits") ;
	b1 = binary_new_with_str ("", 0, 32) ; // 32 0-bits.	
	b2 = binary_new_with_str ("101", 3, 3) ; 

	binary_cpy (b1, b2, -2) ;
	binary_cpy (b1, b2, 15) ;
	binary_cpy (b1, b2, 31) ;

	binary_display (b1) ;
	puts ("") ;
	binary_display (b2) ;
	puts ("") ;
	binary_delete (b1) ;
	binary_delete (b2) ;

	puts ("Copy 16 bits") ;
	b1 = binary_new_with_str ("", 0, 32) ; // 32 0-bits.	
	b2 = binary_new_with_str ("1000000000000001", 16, 16) ; 

	binary_cpy (b1, b2, -2) ;
	binary_cpy (b1, b2, 15) ;
	binary_cpy (b1, b2, 31) ;

	binary_display (b1) ;
	puts ("") ;
	binary_display (b2) ;
	puts ("") ;
	binary_delete (b1) ;
	binary_delete (b2) ;

	puts ("copy 24 bits") ;
	b1 = binary_new_with_str ("", 0, 32) ; // 32 0-bits.	
	b2 = binary_new_with_str ("100000000000000000000001", 24, 24) ; 

	binary_cpy (b1, b2, -2) ;
	binary_cpy (b1, b2, 15) ;
	binary_cpy (b1, b2, 31) ;

	binary_display (b1) ;
	puts ("") ;
	binary_display (b2) ;
	puts ("") ;
	binary_delete (b1) ;
	binary_delete (b2) ;

	puts ("\nShifting test.") ;
	b1 = binary_new_with_str ("111111000001011011100101000000000", 33, 40) ;
	binary_display (b1) ;
	puts ("") ;
	puts ("left shift of 2.") ;
	binary_lshift (b1, 2) ;
	binary_display (b1) ;
	puts ("") ;
	puts ("left shift of 9.") ;
	binary_lshift (b1, 9) ;
	binary_display (b1) ;
	puts ("") ;
	puts ("right shift of 3.") ;
	binary_rshift (b1, 3) ;
	binary_display (b1) ;
	puts ("") ;
	puts ("right shift of 9.") ;
	binary_rshift (b1, 9) ;
	binary_display (b1) ;
	puts ("") ;

	binary_delete (b1) ;

	puts ("\ncmp test.") ;
	b1 = binary_new_with_str ("01010110", 8, 32) ;
	b2 = binary_new_with_str ("11000100", 8, 32) ; 

	binary_display (b1) ;
	puts ("") ;
	binary_display (b2) ;
	puts ("") ;

	fprintf (stderr, "cmp on 4 bits : %d\n", binary_cmp (b1, b2, 4) ) ;
	fprintf (stderr, "cmp on 9 bits : %d\n", binary_cmp (b1, b2, 8) ) ;

	binary_delete (b1) ;
	binary_delete (b2) ;

	return 0 ; 
}
