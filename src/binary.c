#include "../utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

binary* binary_new (char *str, unsigned int l) {
	int i = 0 ;

	binary *b;
	b = malloc (sizeof(*b)) ;
	assert (b != NULL) ;

	b->l = l ;
	assert (l >= strlen(str)) ;

	unsigned int bytes = ceil ( ((float)l) / 8.);
	b->bytes = (unsigned char*) malloc ( bytes * sizeof (unsigned char) ) ;
	assert (b->bytes != NULL) ;
	for (i=0; i<bytes; ++i) {
		b->bytes[i] = 0 ;
	}

	for (i=0; i < strlen (str); ++i) {
		assert (str[i] == '0' || str[i] == '1') ;
		if (str[i] == '1'){
			b->bytes [i/8] |= (128 >> i%8) ;
		}
	}

	return b;
}

void binary_delete (binary *b) {
	if (b != NULL) {
		free (b->bytes) ;
		free (b) ;
	}
}

int binary_cpy (	binary *des,
			binary *src,
			int offset)
{
	assert (offset + src->l > 0) ;

	int i = 0 ;
	int cur_byte ;
	unsigned int bytes_des = (unsigned int)ceil ( (float) des->l / 8.) ;
	unsigned int bytes_src = (unsigned int)ceil ( (float) src->l / 8.) ;
	unsigned char shift = (offset+8*(int)bytes_des)%8 ; 

	while (i < bytes_src) {
		cur_byte =  (unsigned int)floor ( ( (float) offset) / 8.) + i ;
		if (	cur_byte < bytes_des &&
			cur_byte >= 0 ) {
			des->bytes [cur_byte] |= src->bytes[i] >> shift ; 
		}
		if (	cur_byte + 1 < bytes_des &&
			cur_byte + 1 >= 0) {
			des->bytes [cur_byte + 1] |= src->bytes [i] << (8 - shift) ;
		}
		++i ;
	}
	return des->l - (offset + src->l) ; 
}

char binary_read_next_bit (	binary *b,
				size_t offset)
{
	assert (offset < b->l) ;
	int byte_to_read = offset / 8 ; 
	unsigned char r = (b->bytes [byte_to_read] << offset%8 ) & 128 ;
	return (r == 128) + '0';
}

void binary_display (binary *b) {
	int i = 0 ;
	for (i = 0; i < b->l; ++i) {
		fprintf (stderr, "%c", binary_read_next_bit (b, i)) ;
	}
	fprintf (stderr, "\n") ;
}
