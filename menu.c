#include <menu.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
                        "Create root CA",
                        "Create intermediate CA",
                        "Create certificate",
                        "Exit",
                  };
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int get_max_elem(char *arr[], int count)
{
        int i;
        int max_len = 0;
        for (i = 0; i < count; ++i)
        {
                if (strlen(arr[i]) > max_len)
                        max_len = strlen(arr[i]);
        }
        return max_len;
}


int main()
{	ITEM **my_items;
	MENU *my_menu;
        WINDOW *my_menu_win;
	int c;	
        int n_choices, i, width;
        int row, col;
	
	/* Initialize curses */
	initscr();
	getmaxyx(stdscr,row,col);
	start_color();
        cbreak();
        noecho();
	init_pair(1, COLOR_RED, COLOR_BLACK);

        n_choices = ARRAY_SIZE(choices);				// вычисляем количество пунктов меню
	width = get_max_elem(choices, n_choices);			// вычисляем размеры главного экрана
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));		// выделяем память
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], NULL);		// инициализируем пункты меню

	my_menu = new_menu((ITEM **)my_items);				// создаем меню

        my_menu_win = newwin(n_choices + 6, width + 9, row/3, (col - width)/2);	// создаем окно для меню
        keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, width + 3, 4, 2));

	/* Set menu mark to the string " * " */
        set_menu_mark(my_menu, " > ");

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, width + 8, "Select action", COLOR_PAIR(1));
//	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
//	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
	mvprintw(LINES - 2, 0, "F1 to exit");
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
		}
                wrefresh(my_menu_win);
	}	

	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return 0;
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
