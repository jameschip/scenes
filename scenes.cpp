#include "data.hpp"

#include <ncurses.h>
#include <stdlib.h>

void init_colours( void );
void key_for_mode( bool mode, int ch );
void backspace( void );

int main ( int argc, char ** argv ) {

	int ch, row, col, c_row, c_col = 0;
	bool draw = true;

	initscr();
	init_colours();
	noecho();
	cbreak();
	//set_mode( draw );
	getmaxyx( stdscr, row, col );
	keypad( stdscr, TRUE );
	dinit( row, col );

	while ( (ch = getch()) ) {

		getyx( stdscr, c_row, c_col );

		switch (ch) {
			case KEY_UP:
				if ( c_row > 0 ) move( c_row - 1, c_col );
				break;

			case KEY_DOWN:
				if ( c_row < row ) move( c_row + 1, c_col );
				break;

			case KEY_LEFT:
				if ( c_col > 0 ) move( c_row, c_col - 1 );
				break;

			case KEY_RIGHT:
				if ( c_col < col ) move( c_row, c_col + 1 );
				break;

			case '\t':
				draw = !draw;
				//set_mode( draw );
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

	bkgd( COLOR_PAIR( 1 ) );
	clear();
	refresh();

}

void key_for_mode( bool mode, int ch ) {
	int r, c;
	getyx( stdscr, r, c );
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
				attron( COLOR_PAIR( ch - 48 ) );
				addch( dtextat(r, c) );
				dsetcolour( r, c, ch - 48 );
				attroff( COLOR_PAIR( ch - 48 ) );
				break;

		}
	} else {
		if (( ch > 31 ) && (ch < 127 ) ) {

			attron( COLOR_PAIR( dcolourat( r, c ) ) ); // Add characters
			addch( ch );
			dsettext( r, c, ch );
			attroff( COLOR_PAIR( dcolourat( r, c ) ) );
		
		} else if ( (ch == KEY_BACKSPACE) || ( ch == 127 ) ) {
		
			backspace();
		
		}
	}
}

void backspace( void ) {
	int r, c;
	getyx( stdscr,r, c );
	if ( c == 0 ) return;
	move( r, c - 1 );
	addch( ' ' );
	move( r, c - 1 );

}