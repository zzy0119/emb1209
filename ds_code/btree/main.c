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
int tree_insert_other(struct node_st **root, const struct stu_st *stu);
int tree_delete(struct node_st **root, int id);
int main(void)
{
	struct node_st *root = NULL; // root存储的是大树根节点地址	
	int ids[] = {5,7,4,1,9,2,3,8,6};
	struct stu_st s;

	for (int i = 0; i < sizeof(ids) / sizeof(*ids); i++) {
		s.id = ids[i];
		snprintf(s.name, NAMESIZE, "stu%d", ids[i]);
		tree_insert_other(&root, &s);	
	}
	
	tree_delete(&root, 5);
	tree_delete(&root, 9);

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

int tree_insert_other(struct node_st **root, const struct stu_st *stu)
{
	struct node_st *new;
	struct node_st **p;

	new = malloc(sizeof(*new));
	if (NULL == new) {
		return -1;	
	}
	new->data = *stu;
	new->left = new->right = NULL;

	p = root;
	while (*p != NULL) {
		if ((*p)->data.id >= stu->id) {
			p = &(*p)->left;
		} else {
			p = &(*p)->right;
		}
	}
	*p = new;

	return 0;
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

// 返回root为根这个树的最大的结点地址
static struct node_st *right_node(const struct node_st *root)
{
	if (root->right == NULL)
		return (struct node_st *)root;
	return right_node(root->right);
}

static int _delete(struct node_st **root)
{
	struct node_st *del, *r, *l;
	del = *root;
	l = del->left;
	r = del->right;	

	// 左子树为根
	if (l == NULL) {
		(*root) = r;
	} else {
		*root = l;
		// 找到l最右边结点地址
		right_node(l)->right = r;
	}

	free(del);
	return 0;
}

// 删除指定结点
int tree_delete(struct node_st **root, int id)
{
	struct node_st **p = NULL;

	p = root;
	while (*p != NULL) {
		if ((*p)->data.id > id) {
			p = &(*p)->left;	
		} else if ((*p)->data.id < id) {
			p = &(*p)->right;
		} else {
			_delete(p);
			return 0;
		}
	}
	return -1;
}






