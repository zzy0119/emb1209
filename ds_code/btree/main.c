#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE	32

struct stu_st {
	int id;
	char name[NAMESIZE];
};

struct node_st {
	struct stu_st data;
	struct node_st *left;
	struct node_st *right;
};

int tree_insert(struct node_st **root, const struct stu_st *stu);
void traval_mid(const struct node_st *root);
int main(void)
{
	struct node_st *root = NULL; // root存储的是大树根节点地址	
	int ids[] = {5,7,4,1,9,2,3,8,6};
	struct stu_st s;

	for (int i = 0; i < sizeof(ids) / sizeof(*ids); i++) {
		s.id = ids[i];
		snprintf(s.name, NAMESIZE, "stu%d", ids[i]);
		tree_insert(&root, &s);	
	}
	
	traval_mid(root);

	return 0;
}

// 插入一个新的结点
int tree_insert(struct node_st **root, const struct stu_st *stu)
{
	struct node_st *new;

	if (*root == NULL) {
		new = malloc(sizeof(*new));
		if (NULL == new) {
			return -1;	
		}
		new->data = *stu;
		new->left = new->right = NULL;
		*root = new;
		return 0;
	} else {
		if ((*root)->data.id >= stu->id) {
			return tree_insert(&(*root)->left, stu);
		} else {
			return tree_insert(&(*root)->right, stu);
		}
	}
}

// 中序遍历
void traval_mid(const struct node_st *root)
{
	if (root == NULL)
		return ;
	traval_mid(root->left);
	printf("%d %s\n", root->data.id, root->data.name);
	traval_mid(root->right);
}








