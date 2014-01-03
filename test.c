#include <menu.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
                        "Create root CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Test test test Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create intermediate CA",
                        "Create certificate",
                        "Exit",
                        "Test test test test Create intermediate CA",
                  };

int get_max_elem(char *arr[])
{
	int i;
	int max_len = 0;
	while (arr[i])
	{
		if (strlen(arr[i]) > max_len)
			max_len = strlen(arr[i]);
		++i;
	}
	return max_len;
}

int get_quantity_elem(char *arr[])
{
	int i = 0;
	while (arr[i])
	{
		printf ("%s\n", arr[i]);
		++i;
	}
	return i;
}

int main()
{
//	int choices_count = ARRAY_SIZE(choices);
//	int len = get_max_elem(choices, choices_count);
//	printf ("%d\n", len);
	int max_elem = get_max_elem(choices);
//	get_quantity_elem(choices);
	printf ("%d\n", max_elem);	
}
