#include <menu.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
int get_max_elem(char *arr[], int count);
int get_choice(char *choices[], int choices_count, char *title);

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

int get_choice(char *choices[], int choices_count, char *title)
{	ITEM **my_items;
	MENU *my_menu;
        WINDOW *my_menu_win;
	int c;	
        int n_choices, i, width;
        int row, col;
	int ch = 1;	
	int ti;

	getmaxyx(stdscr,row,col);
	mvwprintw(stdscr, 4, 10, "row = %d | col = %d", row, col);
        cbreak();
        noecho();
//	init_pair(2, COLOR_YELLOW, COLOR_MAGENTA);
//	init_pair(1, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

        n_choices = choices_count;
	width = get_max_elem(choices, n_choices);			// вычисляем размеры самой большой строки в массиве
	
	for (ti = 0; ti < n_choices; ++ti)
	{
		mvwprintw(stdscr, ti + 6, 10, "%d -> %d", ti, strlen(choices[ti]));
	}

	mvwprintw(stdscr, 5, 10, "width = %d ", width);

        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));		// выделяем память
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], NULL);		// инициализируем пункты меню

	my_menu = new_menu((ITEM **)my_items);				// создаем меню

        my_menu_win = newwin(n_choices + 6, width + 7, row - 40, (col - width)/2);	// создаем окно для меню
        keypad(my_menu_win, TRUE);
    	
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, n_choices, width + 3, 4, 1));
        set_menu_mark(my_menu, " > ");					// Set menu mark to the string " > "

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, width + 4, title, COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, width + 5);
	mvwaddch(my_menu_win, 2, width + 6, ACS_RTEE);
	mvprintw(LINES - 2, 3, "press ENTER for choice action");
	refresh();
        
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);

	while((c = wgetch(my_menu_win)) != 10)
	{       switch(c)
	        {	case KEY_DOWN:
				if (ch < choices_count)
				{
					menu_driver(my_menu, REQ_DOWN_ITEM);
					mvprintw(3, 10, "                            ");
					++ch;
				}
				break;
			case KEY_UP:
				if (ch > 1)
				{
					menu_driver(my_menu, REQ_UP_ITEM);
					mvprintw(3, 10, "                            ");
					--ch;
				}
				break;
			case KEY_LEFT:
				mvwprintw(stdscr, 3, 10, "select = %d", ch);
				refresh();
				break;
		}
                wrefresh(my_menu_win);
	}	

	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	return ch;
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

void create_ca(char *ca_name)
{
	
}

char *get_ca_name()
{
        WINDOW *my_win;
        my_win = newwin(6, 17, 40, 12);			// создаем окно для меню
        keypad(my_win, TRUE);
	char *name;		// = malloc(10);
	strcpy(name, "asdasdasdsadasd Ooo YEAH!!!");	
	return name;
}

int main ()
{
	char *ca_name;
	char *choices[] = {	"Create root CA",
        	                "Create inwdsfsfsdfsdftermediate CA",
        	                "123456789012345678901234567890",
        	                "123456789012345678901234567890",
        	               // "123456789012345678901234567890",
        	                "Create intermediate CA",
        	                "Crdsfsdfsdfsdfsdfsdfsdfsdfsdfsdfeate intermediate CA",
                	        "Create certificate",
                        	"Exit"	};

	initscr();							// Initialize curses
	start_color();
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	wattron(stdscr, COLOR_PAIR(2));
	mvprintw(2, 10, "Graphic OpenSSL");
	int ch = get_choice(choices, ARRAY_SIZE(choices), "Select action");
	switch(ch)
	{
		case 1:
			//printf("\n%s\n", "Create CA start...");
			ca_name = get_ca_name();
			break;
		case 2:
			ca_name = "ok";
			break;
		default:
			ca_name = "ok!";
			break;

	}
	endwin();
	printf("Selected: %d (%s)\n", ch, choices[ch - 1]);
	printf("CA name: %s\n", ca_name);
	//free(ca_name);
	return 0;
}
