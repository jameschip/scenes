#include <stdlib.h>

char **image_data;
char **text_data;
int row, col;

void dinit( int r, int c ) {
	
	image_data = (char **) calloc( r, sizeof(*image_data) );
	text_data = (char **) calloc( r, sizeof(*text_data) );
	for ( int ri = 0; ri < r; ri++ ) {
		image_data[ri] = (char*) calloc( c, sizeof(char) );
		text_data[ri] = (char*) calloc( c, sizeof( char) );
	}

	for ( int ri = 0; ri < r; ri++ ) {
		for ( int ci = 0; ci < c; ci++ ) {
			image_data[ri][ci] = 1;
			text_data[ri][ci] = ' ';
		}
	}
	
	row = r;
	col = c;
	
}

void dfree( void ) {
	free( image_data );
	free( text_data );
}

char dcolourat( int r, int c ) {
	return image_data[r][c];
}

char dtextat(  int r, int c ) {
	return text_data[r][c];
}

void dsetcolour( int r, int c, char colour ) {
	image_data[r][c] = colour;
}

void dsettext( int r, int c, char text ) {
	text_data[r][c] = text;
}
