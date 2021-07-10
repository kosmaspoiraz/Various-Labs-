///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT List μέσω συνδεδεμένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTList.h"

// Ενα List είναι pointer σε αυτό το struct
struct list
{
	ListNode dummy;			   // χρησιμοποιούμε dummy κόμβο, ώστε ακόμα και η κενή λίστα να έχει έναν κόμβο.
	ListNode last;			   // δείκτης στον τελευταίο κόμβο, ή στον dummy (αν η λίστα είναι κενή)
	int size;				   // μέγεθος, ώστε η list_size να είναι Ο(1)
	DestroyFunc destroy_value; // Συνάρτηση που καταστρέφει ένα στοιχείο της λίστας.
};

struct list_node
{
	ListNode next; // Δείκτης στον επόμενο
	Pointer value; // Η τιμή που αποθηκεύουμε στον κόμβο
};

List list_create(DestroyFunc destroy_value)
{
	// Πρώτα δημιουργούμε το stuct
	List list = malloc(sizeof(*list));
	list->size = 0;
	list->destroy_value = destroy_value;

	// Χρησιμοποιούμε dummy κόμβο, ώστε ακόμα και μια άδεια λίστα να έχει ένα κόμβο
	// (απλοποιεί τους αλγορίθμους). Οπότε πρέπει να τον δημιουργήσουμε.
	//
	list->dummy = malloc(sizeof(*list->dummy));
	list->dummy->next = NULL; // άδεια λίστα, ο dummy δεν έχει επόμενο

	// Σε μια κενή λίστα, τελευταίος κόμβος είναι επίσης ο dummy
	list->last = list->dummy;

	return list;
}

int list_size(List list)
{
	return list->size;
}

ListNode list_first(List list)
{
	// Ο πρώτος κόμβος είναι ο επόμενος του dummy.
	//
	return list->dummy->next;
}

ListNode list_last(List list)
{
	// Προσοχή, αν η λίστα είναι κενή το last δείχνει στον dummy, εμείς όμως θέλουμε να επιστρέψουμε NULL, όχι τον dummy!
	//
	if (list->last == list->dummy)
		return LIST_EOF; // κενή λίστα
	else
		return list->last;
}

ListNode list_next(List list, ListNode node)
{
	assert(node != NULL); // LCOV_EXCL_LINE (αγνοούμε το branch από τα coverage reports, είναι δύσκολο να τεστάρουμε το false γιατί θα κρασάρει το test)
	return node->next;
}

Pointer list_node_value(List list, ListNode node)
{
	assert(node != NULL); // LCOV_EXCL_LINE
	return node->value;
}

void list_insert_next(List list, ListNode node, Pointer value)
{
	// Αν το node είναι NULL απλά εισάγουμε μετά τον dummy κόμβο!
	// Αυτή ακριβώς είναι η αξία του dummy, δε χρειαζόμαστε ξεχωριστή υλοποίηση.
	if (node == NULL)
		node = list->dummy;

	// Δημιουργία του νέου κόμβου
	ListNode new = malloc(sizeof(*new));
	new->value = value;

	// Σύνδεση του new ανάμεσα στο node και το node->next
	new->next = node->next;
	node->next = new;

	// Ενημέρωση των size & last
	list->size++;
	if (list->last == node)
		list->last = new;
}

void list_remove_next(List list, ListNode node)
{
	// Αν το node είναι NULL απλά διαγράφουμε μετά τον dummy κόμβο!
	// Αυτή ακριβώς είναι η αξία του dummy, δε χρειαζόμαστε ξεχωριστή υλοποίηση.
	if (node == NULL)
		node = list->dummy;

	// Ο κόμβος προς διαγραφή είναι ο επόμενος του node, ο οποίος πρέπει να υπάρχει
	ListNode removed = node->next;
	assert(removed != NULL); // LCOV_EXCL_LINE

	if (list->destroy_value != NULL)
		list->destroy_value(removed->value);

	// Σύνδεση του node με τον επόμενο του removed
	node->next = removed->next; // πριν το free!

	free(removed);

	// Ενημέρωση των size & last
	list->size--;
	if (list->last == removed)
		list->last = node;
}

ListNode list_find_node(List list, Pointer value, CompareFunc compare)
{
	// διάσχιση όλης της λίστας, καλούμε την compare μέχρι να επιστρέψει 0
	//
	for (ListNode node = list->dummy->next; node != NULL; node = node->next)
		if (compare(value, node->value) == 0)
			return node; // βρέθηκε

	return NULL; // δεν υπάρχει
}

Pointer list_find(List list, Pointer value, CompareFunc compare)
{
	ListNode node = list_find_node(list, value, compare);
	return node == NULL ? NULL : node->value;
}

DestroyFunc list_set_destroy_value(List list, DestroyFunc destroy_value)
{
	DestroyFunc old = list->destroy_value;
	list->destroy_value = destroy_value;
	return old;
}

void list_destroy(List list)
{
	// Διασχίζουμε όλη τη λίστα και κάνουμε free όλους τους κόμβους,
	// συμπεριλαμβανομένου και του dummy!
	//
	ListNode node = list->dummy;
	while (node != NULL)
	{								// while αντί για for, γιατί θέλουμε να διαβάσουμε
		ListNode next = node->next; // το node->next _πριν_ κάνουμε free!

		// Καλούμε τη destroy_value, αν υπάρχει (προσοχή, όχι στον dummy!)
		if (node != list->dummy && list->destroy_value != NULL)
			list->destroy_value(node->value);

		free(node);
		node = next;
	}

	// Τέλος free το ίδιο το struct
	free(list);
}

//// Επιπλέον συναρτήσεις προς υλοποίηση στο Εργαστήριο 3

// Επιστρέφει την τιμή στη θέση pos της λίστας list (μη ορισμένο αποτέλεσμα αν pos < 0 ή pos >= size)
Pointer list_get_at(List list, int pos)
{
	if (pos < 0 || pos >= list_size(list))
	{
		// printf("Not declared result! Returned NULL! \n");
		return NULL;
	}

	int i = 0;
	ListNode node = list_first(list);
	while (i < list_size(list))
	{
		if (i == pos)
		{
			return node->value;
		}
		else
		{
			node = node->next;
			i++;
		}
	}
	return NULL;
}

// Διαγράφει τον κόμβο node της λίστας list.
void list_remove(List list, ListNode node)
{
	//Κρατάω τον επόμενο του node(to remove)
	ListNode next_node = node->next;

	ListNode previous_node = malloc(sizeof(ListNode));

	//Ψάχνοντας τον προηγούμενου(ή αλλιώς nemo) του node
	for (ListNode nemo = list_first(list); nemo != LIST_EOF; nemo = list_next(list, nemo))
	{
		if (nemo->next == node)
		{
			previous_node = nemo;
			break;
		}
		else
		{
			previous_node = list->dummy;
		}
	}

	//Διαγραφή node
	if (list->destroy_value != NULL)
	{
		list->destroy_value(node->value);
	}

	//Σύνδεση previous με next
	previous_node->next = next_node;

	free(node);

	// Ενημέρωση των size & last
	if (list->last == node)
		list->last = next_node;
	list->size--;
}

// Προσθέτει όλα τα στοιχεία της λίστας to_append στο τέλος της λίστας list. Η λίστα to_append καταστρέφεται
// και δεν μπορεί πλέον να χρησιμοποιηθεί (αλλά τα στοιχεία της δεν καταστρέφονται αφού ανήκουν πλέον στη
// list). Αν list == to_append η συμπεριφορά είναι μη ορισμένη.
void list_append(List list, List to_append)
{
	if (list == to_append || to_append == NULL)
	{
		// printf("Not Defined! \n");
		return;
	}

	for (ListNode node = list_first(to_append); node != LIST_EOF; node = list_next(to_append, node))
	{
		list_insert_next(list, list_last(list), list_node_value(to_append, node));
	}

	list_destroy(to_append);
}