
#ifndef DATA_HPP
#define DATA_GPP

#include <string>

void data_init( int r, int c );
void data_free( void );

char data_colour_at( int r, int c );
char data_text_at( int r, int c );
void data_set_colour( int r, int c, char colour );
void data_set_text( int r, int c, char text );
int data_get_row( void );
int data_get_col( void );

void data_write_file( const std::string& fn );
void data_read_file( const std::string& fn );

#endif
