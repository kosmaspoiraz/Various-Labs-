#include <stdio.h>
#include <stdlib.h>

#include "ADTPriorityQueue.h"
#include "ADTSet.h"

int compare_ints(Pointer a, Pointer b)
{
    return *(int *)a - *(int *)b;
}

// Δεσμεύει μνήμη για έναν ακέραιο, αντιγράφει το value εκεί και επιστρέφει pointer
int *create_int(int value)
{
    int *pointer = malloc(sizeof(int)); // δέσμευση μνήμης
    *pointer = value;                   // αντιγραφή του value στον νέο ακέραιο
    return pointer;
}

int main()
{
    PriorityQueue pqueue = pqueue_create(compare_ints, free, NULL);

    //lab-2-3-1
    for (int i = 0; i < 20; i++)
    {
        pqueue_insert(pqueue, create_int(rand()));
    }

    //lab-2-3-3
    for (int i = 0; i < 20; i++)
    {
        printf("%d\n", *(int *)pqueue_max(pqueue));
        pqueue_remove_max(pqueue);
    }

    //newlines
    printf("\n\n");

    //lab-2-3-3
    Set set = set_create(compare_ints, free);

    for (int i = 0; i < 20; i++)
    {
        set_insert(set, create_int(rand()));
    }

    //lab-2-3-4
    for (SetNode node = set_first(set); node != SET_EOF; node = set_next(set, node))
    {
        printf("%d\n", *(int *)set_node_value(set, node));
    }

    pqueue_destroy(pqueue);
    return 0;
}