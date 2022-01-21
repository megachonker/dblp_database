#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
                        "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
			"Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
			"Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
			"Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
                        "Exit",
                        (char *)NULL,
                  };

int main()
{	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i;
	
	/* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);

	/* Create items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], choices[i]);

	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Set menu option not to show the description */
	menu_opts_off(my_menu, O_SHOWDESC);

	/* Create the window to be associated with the menu */
        my_menu_win = newwin(10, 70, 4, 4);
        keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 68, 3, 1));
	set_menu_format(my_menu, 5, 3);
	set_menu_mark(my_menu, " * ");

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	
	attron(COLOR_PAIR(2));
	mvprintw(LINES - 3, 0, "Use PageUp and PageDown to scroll");
	mvprintw(LINES - 2, 0, "Use Arrow Keys to navigate (F1 to Exit)");
	attroff(COLOR_PAIR(2));
	refresh();

	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);
	
	while((c = wgetch(my_menu_win)) != KEY_F(1))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(my_menu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_RIGHT_ITEM);
				break;
			case KEY_NPAGE:
				menu_driver(my_menu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				menu_driver(my_menu, REQ_SCR_UPAGE);
				break;
		}
                wrefresh(my_menu_win);
	}	

	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
}

// #include <curses.h>
// #include <menu.h>
// #include <stdlib.h>
// #define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
// #define CTRLD 	4

// char *choices[] = {
//                         "Choice 1",
//                         "Choice 2",
//                         "Choice 3",
//                         "Choice 4",
//                         "Exit",
//                   };


// char *choicesB[] = {
//                         "OWO 1",
//                         "OWO 2",
//                         "OWO 3",
//                         "OWO 4",
//                         "Exit",
//                   };

// int main()
// {	ITEM **my_items;
// 	int c;
// 	MENU *my_menu;
// 	int n_choices, i;
// 	ITEM *cur_item;

// 	initscr();
// 	cbreak();
// 	noecho();
// 	keypad(stdscr, TRUE);

// 	n_choices = ARRAY_SIZE(choices);
// 	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

// 	for(i = 0; i < n_choices; ++i)
// 	        my_items[i] = new_item(choices[i], choicesB[i]);
// 	my_items[n_choices] = (ITEM *)NULL;

// 	my_menu = new_menu((ITEM **)my_items);
// 	mvprintw(LINES - 2, 0, "F1 to Exit");
// 	post_menu(my_menu);
// 	refresh();

// 	while((c = getch()) != KEY_F(1))
// 	{   switch(c)
// 	    {	case KEY_DOWN:
// 		        menu_driver(my_menu, REQ_DOWN_ITEM);
// 				break;
// 			case KEY_UP:
// 				menu_driver(my_menu, REQ_UP_ITEM);
// 				break;
// 			case KEY_LEFT:
// 				menu_driver(my_menu, REQ_TOGGLE_ITEM);
// 				menu_mark(my_menu);
// 				break;
// 		}
// 	}

// 	free_item(my_items[0]);
// 	free_item(my_items[1]);
// 	free_menu(my_menu);
// 	endwin();
// }

// #include <curses.h>

// /* triangle.c */
// #include <curses.h>
// #include <stdlib.h>
// #include <time.h>
// #include <ncurses.h>

// WINDOW *create_newwin(int height, int width, int starty, int startx);
// void destroy_win(WINDOW *local_win);

// int main(int argc, char *argv[])
// {	WINDOW *my_win;
// 	int startx, starty, width, height;
// 	int ch;

// 	initscr();			/* Start curses mode 		*/
// 	cbreak();			/* Line buffering disabled, Pass on
// 					 * everty thing to me 		*/
// 	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

// 	height = 4;
// 	width = 4;
// 	starty = (LINES - height) / 2;	/* Calculating for a center placement */
// 	startx = (COLS - width) / 2;	/* of the window		*/
// 	printw("Press F1 to exit");
// 	refresh();
// 	my_win = create_newwin(height, width, starty, startx);

// 	while((ch = getch()) != KEY_F(1))
// 	{	switch(ch)
// 		{	case KEY_LEFT:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, starty,--startx);
// 				break;
// 			case KEY_RIGHT:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, starty,++startx);
// 				break;
// 			case KEY_UP:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, --starty,startx);
// 				break;
// 			case KEY_DOWN:
// 				destroy_win(my_win);
// 				my_win = create_newwin(height, width, ++starty,startx);
// 				break;
// 		}
// 	}

// 	endwin();			/* End curses mode		  */
// 	return 0;
// }

// WINDOW *create_newwin(int height, int width, int starty, int startx)
// {	WINDOW *local_win;

// 	local_win = newwin(height, width, starty, startx);
// 	box(local_win, 0 , 0);		/* 0, 0 gives default characters
// 					 * for the vertical and horizontal
// 					 * lines			*/
// 	wrefresh(local_win);		/* Show that box 		*/

// 	return local_win;
// }

// void destroy_win(WINDOW *local_win)
// {
// 	/* box(local_win, ' ', ' '); : This won't produce the desired
// 	 * result of erasing the window. It will leave it's four corners
// 	 * and so an ugly remnant of window.
// 	 */
// 	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
// 	/* The parameters taken are
// 	 * 1. win: the window on which to operate
// 	 * 2. ls: character to be used for the left side of the window
// 	 * 3. rs: character to be used for the right side of the window
// 	 * 4. ts: character to be used for the top side of the window
// 	 * 5. bs: character to be used for the bottom side of the window
// 	 * 6. tl: character to be used for the top left corner of the window
// 	 * 7. tr: character to be used for the top right corner of the window
// 	 * 8. bl: character to be used for the bottom left corner of the window
// 	 * 9. br: character to be used for the bottom right corner of the window
// 	 */
// 	wrefresh(local_win);
// 	delwin(local_win);
// }