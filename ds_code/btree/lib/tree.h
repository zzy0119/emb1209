#ifndef __TREE_H
#define __TREE_H

struct node_st {
	struct node_st *left;
	struct node_st *right;
	char data[0];
};

typedef struct {
	struct node_st *root;	
	int size;
}tree_t;

typedef int (*cmp_t)(const void *data, const void *key);
typedef void (*pri_t)(const void *data);

tree_t *tree_init(int size);

int tree_insert(tree_t *t, const void *data, cmp_t cmp);

int tree_delete(tree_t *t, const void *key, cmp_t cmp);

void tree_mid_traval(const tree_t *t, pri_t pri);

void tree_destroy(tree_t *t);

#endif

