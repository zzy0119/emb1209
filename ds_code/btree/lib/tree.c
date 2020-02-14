#include <stdlib.h>
#include <string.h>
#include "tree.h"

tree_t *tree_init(int size)
{
	tree_t *tree;	

	tree = malloc(sizeof(tree_t));
	if (NULL == tree)
		return NULL;
	tree->root = NULL;
	tree->size = size;

	return tree;
}

static int _insert(struct node_st **root, const struct node_st *node, cmp_t cmp)
{
	if (*root == NULL) {
		*root = (void *)node;	
		return 0;
	}
	if (cmp((*root)->data, node->data) >= 0) {
		return _insert(&(*root)->left, node, cmp);
	} else {
		return _insert(&(*root)->right, node, cmp);
	}
}

int tree_insert(tree_t *t, const void *data, cmp_t cmp)
{
	struct node_st *new;
	
	new = malloc(sizeof(*new) + t->size);
	if (NULL == new)
		return -1;
	memcpy(new->data, data, t->size);
	new->left = new->right = NULL;

	return _insert(&t->root, new, cmp);
}

// int tree_delete(tree_t *t, const void *key, cmp_t cmp);

static void _mid_traval(const struct node_st *root, pri_t pri)
{
	if (root == NULL)
		return ;
	_mid_traval(root->left, pri);
	pri(root->data);
	_mid_traval(root->right, pri);
}

void tree_mid_traval(const tree_t *t, pri_t pri)
{
	_mid_traval(t->root, pri);
}

// void tree_destroy(tree_t *t);

