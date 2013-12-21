#include <menu.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD   4

char *choices[] = {
                        "Create root CA",
                        "Create intermediate CA",
                        "Create certificate",
                        "Exit",
                        (char *)NULL,
                  };
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int get_max_elem(char *arr)
{       int count_elem;
	int length_str;
        int i;
        count_elem = ARRAY_SIZE(arr);
        for (i = 1; i < count_elem; ++i)
        {
	//	length_str = strlen(arr[i]);	
                printf("%s\n", *arr[i]);
        }
        return count_elem;
}

int main()
{	get_max_elem(*choices);
	return 0;
}
