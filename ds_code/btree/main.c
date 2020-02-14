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
void tree_show(const struct node_st *root, int level);
void tree_balance(struct node_st **root);

static struct node_st *debug_root;

int main(void)
{
	struct node_st *root = NULL; // root存储的是大树根节点地址	
	int ids[] = {1,2,3,4,5,6,7,8,9,10};
	struct stu_st s;

	for (int i = 0; i < sizeof(ids) / sizeof(*ids); i++) {
		s.id = ids[i];
		snprintf(s.name, NAMESIZE, "stu%d", ids[i]);
		tree_insert_other(&root, &s);	
	}

	debug_root = root;
	
	tree_show(root, 0);
	tree_balance(&root);	
	tree_show(root, 0);
#if 0
	tree_delete(&root, 5);
	tree_show(root, 0);
	tree_delete(&root, 9);
	tree_show(root, 0);

	traval_mid(root);
#endif

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

static struct node_st *left_node(const struct node_st *root)
{
	if (root->left == NULL)
		return (struct node_st *)root;
	return left_node(root->left);
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

// 画树
void tree_show(const struct node_st *root, int level)
{
	if (root == NULL)
		return ;
	tree_show(root->right, level+1);
	// 右子树画完了
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("%d %s\n", root->data.id, root->data.name);
	tree_show(root->left, level+1);
}

static int sum_nodes(const struct node_st *root)
{
	if (root == NULL)
		return 0;
	return sum_nodes(root->left)+sum_nodes(root->right)+1;
}

static void turn_left(struct node_st **root)
{
	struct node_st *r, *cur;

	r = (*root)->right;
	cur = *root;

	*root = r;
	cur->right = NULL;
	left_node(r)->left = cur;
	
	getchar();
	debug_root = *root;
	tree_show(debug_root, 0);
}

static void turn_right(struct node_st **root)
{
	struct node_st *l, *cur;

	cur = *root;
	l = cur->left;

	*root = l;
	cur->left = NULL;
	right_node(l)->right = cur;

	getchar();
	debug_root = *root;
	tree_show(debug_root, 0);
}

// 平衡二叉树
void tree_balance(struct node_st **root)
{
	int n;

	if (*root == NULL)
		return ;

	while (1) {
		n = sum_nodes((*root)->left) - sum_nodes((*root)->right);
		if (n > 1) {
			turn_right(root);
		} else if (n < -1) {
			turn_left(root);
		} else
			break;
	} 
	tree_balance(&(*root)->left);
	tree_balance(&(*root)->right);
}






