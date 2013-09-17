#include "../utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

binary* binary_new (unsigned char* data, unsigned int l, unsigned int c) {
	binary *b ;
	assert (l <= c) ;
	b = malloc (sizeof (*b) ) ;
	assert (b != NULL) ;

	b->l = l ;
	b->c = c ;

	unsigned int bytes = ((b->c-1)/8)+1 ; 
	b->bytes = (unsigned char*) calloc ( bytes, sizeof (unsigned char) ) ;
	assert (b->bytes != NULL) ;

	memcpy (b->bytes, data, l) ;
	return b ;
}

binary* binary_new_with_str (char *str, unsigned int l, unsigned int c) {
	int i = 0 ;

	binary *b;
	assert (l <= c) ;
	assert (l >= strlen(str)) ;
	b = malloc (sizeof(*b)) ;
	assert (b != NULL) ;

	b->l = l ;
	b->c = c ;

	unsigned int bytes = ((b->c-1)/8) +1 ;
	b->bytes = (unsigned char*) calloc ( bytes, sizeof (unsigned char) ) ;
	assert (b->bytes != NULL) ;

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
	
	int i = 0 ;

	assert (offset + src->l > 0) ;
	assert (src->l <= des->c) ;

	unsigned int bytes_src = ((src->l-1)/8) +1 ;
	unsigned int bytes_des = ((des->c-1)/8) +1 ;

	binary* tmp = binary_new_with_str ("", src->l, des->c) ;

	for (i=0; i<bytes_src; ++i) {
		tmp->bytes[i] = src->bytes[i] ;
	}

	if (offset > 0) { 
		binary_rshift (tmp, offset) ;
	} else {
		binary_lshift (tmp, -offset) ;
	}

	for (i=0; i<bytes_des; ++i) {
		des->bytes[i] |= tmp->bytes[i] ;
	}

	des->l = tmp->l ;

	binary_delete (tmp) ;

	return des->c - (offset + src->l) ; 
}

int binary_cpy_data (	binary *des,
			unsigned char *src,
			unsigned int src_l,
			int offset)
{
	int i = 0 ;

	assert (offset + src_l > 0) ;

	unsigned int bytes_des = ((des->c-1)/8) +1 ;

	binary* tmp = binary_new_with_str ("", src_l, des->c) ;

	for (i=0; i<src_l; ++i) {
		tmp->bytes[i] = src[i] ;
	}

	if (offset > 0) { 
		binary_rshift (tmp, offset) ;
	} else {
		binary_lshift (tmp, -offset) ;
	}

	for (i=0; i<bytes_des; ++i) {
		des->bytes[i] |= tmp->bytes[i] ;
	}

	des->l = tmp->l ;

	binary_delete (tmp) ;

	return des->c - (offset + src_l) ; 
}

void binary_lshift (	binary *b,
			unsigned int l) 
{
	binary *tmp = binary_new_with_str ("", 0, b->c) ;
	int i = 0 ;

	if (l < b->l) { 
		for (i=l; i<b->l; ++i) {

			if ( i%8-((int)l)%8 >= 0 ) {
				tmp->bytes[(i-l)/8] |= ((128 >> (i%8)) & b->bytes[i/8]) << (l%8);
			} else {
				tmp->bytes[(i-l)/8] |= ((128 >> (i%8)) & b->bytes[i/8]) >> (8-(l%8));	
			}
		}

	}

	b->l = (b->l - l < 0) ? 0 : b->l - l ;
	for (i=0; i<(b->c-1)/8+1; ++i) {
		b->bytes[i] = tmp->bytes[i] ;
	}

	binary_delete (tmp) ; 
}

void binary_rshift (	binary *b,
			unsigned int l) 
{
	binary *tmp = binary_new_with_str ("", 0, b->c) ;
	int i = 0, up_limit = (b->l + l < b->c) ? b->l : b->c ;	
	for (i=0; i< up_limit; ++i) {
		if (l%8+i%8 < 8) {
			tmp->bytes [(i+l)/8] |= ((128 >> (i%8)) & b->bytes[i/8]) >> (l%8) ;
		} else {
			tmp->bytes [(i+l)/8] |= ((128 >> (i%8)) & b->bytes[i/8]) << (8-(l%8)) ;
		}
	}

	b->l = (b->l + l > b->c) ? b->c : b->l + l ;
	for (i=0; i<(b->c-1)/8+1; ++i) {
		b->bytes[i] = tmp->bytes[i] ;
	}

	binary_delete (tmp) ;
}

int binary_cmp (	binary *b1,
			binary *b2,
			size_t num) 
{
	assert (b1->l >= num && b2->l >= num) ;

	int result = 0, i = 0 ;
	unsigned char mask = 255 << (8-(num%8));
	if (mask == 0 && num != 0) mask = 255 ;

	for (i=0; i<(num-1)/8; ++i) {
		result += !(b1->bytes[i] == b2->bytes[i]) ;
	}

	result += !((b1->bytes[(num-1)/8] & mask) == (b2->bytes[(num-1)/8] & mask)) ;

	return result ;
}

void binary_clear (binary* b) {
	int i = 0;

	assert (b != NULL) ;

	for (i=0; i < ((((int)b->c)-1)/8)+1; ++i) {
		b->bytes[i] = 0;
	}
	b->l = 0;
}

char binary_read_bit (	binary *b,
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
		fprintf (stderr, "%c", binary_read_bit (b, i)) ;
	}
}
