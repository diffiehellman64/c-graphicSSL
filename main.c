#include <stdio.h>
#include <string.h>
#include <ncurses.h>

char *choices[] = { 
			"Create root CA",		//1
			"Create intermediate CA",	//2
			"Create certificate",		//3
			"Exit",				//4
		  };
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
int menu_action();
int get_max_len(char *arr[], int arr_len);

int get_max_len(char *arr[], int arr_len)
{
	int max_len = 0;
	for (int i = 0; i < arr_len; ++i){
		if (strlen(arr[i]) > max_len)
		{
			max_len = strlen(arr[i]);
		}
			
	}
	return max_len;
}

int menu_action()
{
 	WINDOW *menu_win;
	int max_str = get_max_len(choices, n_choices);
	int row, col;
	int highlight = 1;
	int choice = 0;
	int c;
	getmaxyx(stdscr, row, col);
	int startx = (col - max_str) / 2 ;
	int starty = (row - n_choices) / 2 - 6;
	
	menu_win = newwin(n_choices + 4, max_str + 6, starty, startx);
	keypad(menu_win, TRUE);
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	
			break;
	}	
	return choice;
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 3;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}

void input_str(char msg[])
{
 char str[80];
 initscr();                             /* start the curses mode */
 mvprintw(2, 2, "%s", msg);
                                /* print the message at the center of the screen */
 getstr(str);
 mvprintw(LINES - 2, 0, "You Entered: %s", str);
}

/*void input_str()//(WINDOW *input_box)
{
	WINDOW *input_win;
	input_win = newwin(15, 15, 15, 15);
	char mesg[]="Enter a string: ";
	mvprintw(input_win, 3, 3, "%s", mesg);
	wrefresh(input_win);
}
*/
int main()
{
	initscr();
	clear();
	mvprintw(1, 15, "Graphic SSL");
//	input_str();
//	int action = menu_action();
//	mvprintw(50, 15, "You chose choice %d", action);
	input_str("sdf ");
//	mvprintw(50, 15, "You entered %s", str);
	getch();
	refresh();
	endwin();
	return 0;
}
