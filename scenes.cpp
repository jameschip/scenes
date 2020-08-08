#include "data.hpp"

#include <ncurses.h>
#include <stdlib.h>
#include <string>

void init_colours( void );
void key_for_mode( bool mode, int ch );
void backspace( void );
void image_from_data( int row,int col );
WINDOW *create_newwin(int height, int width, int starty, int startx);

std::string fn;
WINDOW *draw_win;

int main ( int argc, char ** argv ) {

	int ch, row, col, c_row, c_col = 0;
	bool draw = true;
	initscr();
	noecho();
	cbreak();

	if ( argc == 2 ) {
		fn = argv[1];
		data_read_file( fn );
		row = data_get_row();
		col = data_get_col();
	}

	if ( row == -1 || col == -1) {
		getmaxyx( stdscr, row, col );
		data_init( row, col );
	}

	draw_win = create_newwin( row, col, 0, 0 );
	init_colours();
	image_from_data( row,col );
	keypad( stdscr, TRUE );
	keypad( draw_win, TRUE );


	while ( (ch = wgetch( draw_win )) ) {

		getyx( draw_win, c_row, c_col );

		switch (ch) {
			case KEY_UP:
				if ( c_row > 0 ) wmove( draw_win, c_row - 1, c_col );
				break;

			case KEY_DOWN:
				if ( c_row < row ) wmove( draw_win, c_row + 1, c_col );
				break;

			case KEY_LEFT:
				if ( c_col > 0 ) wmove( draw_win, c_row, c_col - 1 );
				break;

			case KEY_RIGHT:
				if ( c_col < col ) wmove( draw_win, c_row, c_col + 1 );
				break;

			case '\t':
				draw = !draw;
				break;

			default:
				key_for_mode( draw, ch );
				break;

		}

	}

	exit_loop:

	return 0;

}

void init_colours( void ) {

	if ( has_colors() == FALSE ) {
		endwin();
		printf("Terminal does not have colours!\n");
		exit( 1 );
	}

	start_color();

	init_color( 7, 1000, 1000, 1000 );
	init_color( 6, 875, 875, 875 );
	init_color( 5, 750, 750, 750 );
	init_color( 4, 625, 625, 625 );
	init_color( 3, 500, 500, 500 );
	init_color( 2, 375, 375, 375 );
	init_color( 1, 250, 250, 250 );
	init_color( 0, 125, 125, 125 );

	init_pair( 1, 1, 7 );
	init_pair( 2, 1, 6 );
	init_pair( 3, 1, 5 );
	init_pair( 4, 1, 4 );
	init_pair( 5, 6, 3 );
	init_pair( 6, 6, 2 );
	init_pair( 7, 6, 1 );
	init_pair( 8, 6, 0 );

	wbkgd( stdscr, COLOR_PAIR( 1 ) );
	wbkgd( draw_win, COLOR_PAIR( 1 ) );
	wclear( draw_win );
	clear();
	wrefresh( draw_win );
	refresh();
}

void key_for_mode( bool mode, int ch ) {
	int r, c;
	getyx( draw_win, r, c );
	if ( mode == TRUE ) {
		switch ( ch ) {

			case '1':	// Colours
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				wattron( draw_win, COLOR_PAIR( ch - 48 ) );
				waddch( draw_win, data_text_at(r, c) );
				data_set_colour( r, c, ch );
				wattroff( draw_win,  COLOR_PAIR( ch - 48 ) );
				break;

			case 's':
				data_write_file( fn );
				break;
		}
	} else {
		if (( ch > 31 ) && (ch < 127 ) ) {

			wattron( draw_win, COLOR_PAIR( data_colour_at( r, c ) - 48 ) ); // Add characters
			waddch( draw_win, ch );
			data_set_text( r, c, ch );
			wattroff( draw_win, COLOR_PAIR( data_colour_at( r, c ) - 48 ) );
		
		} else if ( (ch == KEY_BACKSPACE) || ( ch == 127 ) ) {
		
			backspace();
		
		}
	}
}

void backspace( void ) {
	int r, c;
	getyx( draw_win,r, c );
	if ( c == 0 ) return;
	wmove( draw_win,  r, c - 1 );
	waddch( draw_win,  ' ' );
	data_set_text( r, c - 1, ' ' );
	wmove( draw_win, r, c - 1 );

}

void image_from_data( int row,int col ) {
	
	for (int ri = 0; ri < row; ri++ ) {
		for ( int ci = 0; ci < col; ci++ ){
			move( ri, ci );
			wattron( draw_win, COLOR_PAIR( data_colour_at( ri, ci ) - 48 ) ); // Add characters
			waddch(  draw_win, data_text_at( ri, ci ) );
			wattroff( draw_win, COLOR_PAIR( data_colour_at( ri, ci ) - 48 ) );
		}
	}
	wmove( draw_win, 0, 0 );
	wrefresh( draw_win );
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	return local_win;
}
