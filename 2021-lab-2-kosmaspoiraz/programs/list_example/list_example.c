#include <stdlib.h>
#include <stdio.h>

#include "ADTList.h"

// Δεσμεύει μνήμη για έναν ακέραιο, αντιγράφει το value εκεί και επιστρέφει pointer
int *create_int(int value)
{
	int *pointer = malloc(sizeof(int)); // δέσμευση μνήμης
	*pointer = value;					// αντιγραφή του value στον νέο ακέραιο
	return pointer;
}

int main()
{
	List list = list_create(free);

	// προσθήκη των αριθμών από το 0 έως 9 στη λίστα
	for (int i = 0; i < 10; i++)
		list_insert_next(list, list_last(list), create_int(i));

	// εκτύπωση των περιεχομένων της λίστας
	ListNode node = list_first(list);
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", *(int *)list_node_value(list, node));
		node = list_next(list, node);
	}

	list_destroy(list);
}