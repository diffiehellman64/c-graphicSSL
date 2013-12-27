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
{
	int choices_count = ARRAY_SIZE(choices);
	int len = get_max_elem(choices, choices_count);
	printf ("%d\n", len);
}
