#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

char **image_data;
char **text_data;
int row, col;

void size_from_file( const std::string & strToSplit );

void data_init( int r, int c ) {
	
	image_data = (char **) calloc( r, sizeof(*image_data) );
	text_data = (char **) calloc( r, sizeof(*text_data) );
	for ( int ri = 0; ri < r; ri++ ) {
		image_data[ri] = (char*) calloc( c, sizeof(char) );
		text_data[ri] = (char*) calloc( c, sizeof( char) );
	}

	for ( int ri = 0; ri < r; ri++ ) {
		for ( int ci = 0; ci < c; ci++ ) {
			image_data[ri][ci] = '1';
			text_data[ri][ci] = ' ';
		}
	}
	
	row = r;
	col = c;
	
}

void data_free( void ) {
	free( image_data );
	free( text_data );
}

char data_colour_at( int r, int c ) {
	return image_data[r][c];
}

char data_text_at(  int r, int c ) {
	return text_data[r][c];
}

void data_set_colour( int r, int c, char colour ) {
	image_data[r][c] = colour;
}

void data_set_text( int r, int c, char text ) {
	text_data[r][c] = text;
}

int data_get_row( void ) {
	return row;
}

int data_get_col( void ) {
	return col;
}

void data_write_file( const std::string& fn ) {

	std::ofstream outfile;
	outfile.open(fn);
	
	outfile << std::to_string(row) << "," << std::to_string(col) << std::endl;

	for ( int ri = 0; ri < row; ri++ ) {
		for ( int ci = 0; ci < col; ci++ ) {
			outfile << image_data[ri][ci];
		}
		outfile << std::endl;
	}

	for ( int ri = 0; ri < row; ri++ ) {
		for ( int ci = 0; ci < col; ci++ ) {
			outfile << text_data[ri][ci];
		}
		outfile << std::endl;
	}

	outfile.close();

}

void data_read_file( const std::string& fn ) {

	std::ifstream infile;
	
	infile.open( fn );
	
	if ( infile.is_open() ) {
		
		std::string line;
		std::getline( infile, line );

		size_from_file( line );

		for ( int ri = 0; ri < row; ri++ ) {
			getline( infile, line );
			for ( int ci = 0; ci < col; ci++ ) {
				image_data[ri][ci] = line[ci];
			}
		}

		for ( int ri = 0; ri < row; ri++ ) {
			getline( infile, line );
			for ( int ci = 0; ci < col; ci++ ) {
				text_data[ri][ci] = line[ci];
			}
		}

	}

}

void size_from_file( const std::string & strToSplit )
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> vals;
    while (std::getline(ss, item, ','))
    {
       vals.push_back(item);
    }
	data_init( stoi(vals[0]) , stoi(vals[1]) );
}