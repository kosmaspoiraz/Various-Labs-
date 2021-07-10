///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω ταξινομημένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTList.h" // Η υλοποίηση του PriorityQueue χρησιμοποιεί List

// Ενα PriorityQueue είναι pointer σε αυτό το struct
struct priority_queue
{
	List list;				   // η λίστα στην οποία αποθηκεύουμε τα στοιχεία
	CompareFunc compare;	   // Η διάταξη
	DestroyFunc destroy_value; // Συνάρτηση που καταστρέφει ένα στοιχείο του list.
};

//gia na perasw thn compare sthn qsort
typedef int (*qsort_cmp)(const void *, const void *);

static void listify(PriorityQueue pqueue, Vector values)
{
	int size = vector_size(values);
	Pointer array[size];
	int index = 0;

	//μεταφορά στοιχείων του input vector σε array
	for (VectorNode node = vector_first(values); node != VECTOR_EOF; node = vector_next(values, node))
	{
		array[index] = vector_node_value(values, node);
		index++;
	}

	//ταξινόμηση array με qsort
	//f8hnoysa seira
	qsort(array, size, sizeof(void *), (qsort_cmp)pqueue->compare);

	//εισαγωγή ταξινομημένων στοιχείων του array στην λίστα της pqueue
	for (int i = 0; i < size; i++)
	{
		pqueue_insert(pqueue, array[i]);
	}
}

// Συναρτήσεις του ADTPriorityQueue //////////////////////////////////////////////////
PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values)
{
	assert(compare != NULL); // LCOV_EXCL_LINE

	PriorityQueue pqueue = malloc(sizeof(*pqueue));
	pqueue->compare = compare;
	pqueue->destroy_value = destroy_value;

	// Δημιουργία του vector που αποθηκεύει τα στοιχεία.
	// ΠΡΟΣΟΧΗ: ΔΕΝ περνάμε την destroy_value στο list!
	// Αν την περάσουμε θα καλείται όταν κάνουμε swap 2 στοιχεία, το οποίο δεν το επιθυμούμε.
	pqueue->list = list_create(NULL);

	// Αν values != NULL, αρχικοποιούμε το σωρό.
	if (values != NULL)
		listify(pqueue, values);

	return pqueue;
}

int pqueue_size(PriorityQueue pqueue)
{
	//pqueue size = pqueue->list size
	return list_size(pqueue->list);
}

Pointer pqueue_max(PriorityQueue pqueue)
{
	//μαξ θα ειναι first
	return list_node_value(pqueue->list, list_first(pqueue->list));
}

void pqueue_insert(PriorityQueue pqueue, Pointer value)
{
	//an h lista einai kenh || h to value einai megalytero toy prwtoy stoixeioy
	if (list_size(pqueue->list) == 0 || pqueue->compare(value, list_node_value(pqueue->list, list_first(pqueue->list))) > 0)
	{
		//balto prwto
		list_insert_next(pqueue->list, LIST_BOF, value);
	}
	else
	{
		//alliws oso to value einai mikrotero toy node, go next_node
		ListNode node = list_first(pqueue->list);
		ListNode pnode = list_first(pqueue->list);
		while (pqueue->compare(value, list_node_value(pqueue->list, node)) < 0)
		{
			if (list_next(pqueue->list, node) != NULL)
			{
				pnode = node;
				node = list_next(pqueue->list, node);
			}
			else
			{
				pnode = node;
				break;
			}
		}
		list_insert_next(pqueue->list, pnode, value);
	}
}

void pqueue_remove_max(PriorityQueue pqueue)
{
	//max = first, so remove_next_BOF
	list_remove_next(pqueue->list, LIST_BOF);
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value)
{
	// Απλά καλούμε την αντίστοιχη συνάρτηση της λίστας
	return list_set_destroy_value(pqueue->list, destroy_value);
}

void pqueue_destroy(PriorityQueue pqueue)
{
	// Αντί να κάνουμε εμείς destroy τα στοιχεία, είναι απλούστερο να
	// προσθέσουμε τη destroy_value στο vector ώστε να κληθεί κατά το vector_destroy.
	list_set_destroy_value(pqueue->list, pqueue->destroy_value);
	list_destroy(pqueue->list);

	free(pqueue);
}
