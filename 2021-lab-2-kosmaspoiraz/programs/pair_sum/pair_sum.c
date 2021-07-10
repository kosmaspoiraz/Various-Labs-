#include <stdlib.h>

#include "pair_sum.h"

Pair pair_sum(int target, Vector numbers)
{
	Pair pair_found = NULL;

	for (VectorNode node0 = vector_first(numbers); node0 != VECTOR_EOF; node0 = vector_next(numbers, node0))
	{
		for (VectorNode node1 = vector_next(numbers, node0); node1 != VECTOR_EOF; node1 = vector_next(numbers, node1))
		{
			if (*(int *)vector_node_value(numbers, node0) + *(int *)vector_node_value(numbers, node1) == target)
			{
				pair_found->first = *(int *)vector_node_value(numbers, node0);
				pair_found->second = *(int *)vector_node_value(numbers, node1);
			}
		}
	}

	if (pair_found != NULL)
	{
		return pair_found;
	}
	else
	{
		return NULL;
	}
}