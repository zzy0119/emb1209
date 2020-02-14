#include <stdio.h>

#include "tree.h"

static int cmp_nodes(const void *data, const void *ist)
{
	const int *d = data;
	const int *i = ist;

	return *d - *i;
}

static void pri_node(const void *data)
{
	const int *d = data;
	printf("%d\n", *d);
}

int main(void)
{
	int nodes[] = {5,7,4,8,9,2,6,8,2,3};
	tree_t *tree;

	tree = tree_init(sizeof(int));
	// if error

	for (int i = 0; i < sizeof(nodes) / sizeof(*nodes); i++) {
		tree_insert(tree, nodes+i, cmp_nodes);	
	}
	tree_mid_traval(tree, pri_node);

	return 0;
}

