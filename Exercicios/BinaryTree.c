#include<stdio.h>
#include<stdlib.h>
#define COUNT 5

struct node
{
	int value;
	struct node *left_child, *right_child;
};

struct node *new_node(int value)
{
	struct node *tmp = (struct node *)malloc(sizeof(struct node));
	tmp->value = value;
	tmp->left_child = tmp->right_child = NULL;
	return tmp;
}

void print(struct node *root_node, int level) // displaying the nodes!
{
	if (root_node != NULL)
	{
		print(root_node->left_child, level + 1);
		printf("%d ::: %d \n", level, root_node->value);
		print(root_node->right_child, level + 1);
	}
}

void printHierarchy(struct node *root_node, int space)
{
	int i;
	
	if(root_node == NULL) return;
	
	space += COUNT;
	
	printHierarchy(root_node->right_child, space);
	
	printf("\n");
	for(i=COUNT; i < space; i++)
	{
		printf(" ");
	}
	printf("%d\n", root_node->value);

	printHierarchy(root_node->left_child, space);

}

struct node* insert_node(struct node* node, int value) // inserting nodes!
{

	if (node == NULL) return new_node(value);
	if (value < node->value)
	{
		node->left_child = insert_node(node->left_child, value);
	}
	else if (value > node->value)
	{
		node->right_child = insert_node(node->right_child, value);
	}
	return node;
}

int main()
{

printf("::: Binary Tree\n\n");

struct node *root_node = NULL;
root_node = insert_node(root_node, 10);
insert_node(root_node, 10);
insert_node(root_node, 05);
insert_node(root_node, 07);
insert_node(root_node, 04);
insert_node(root_node, 28);
insert_node(root_node, 30);
insert_node(root_node, 25);
insert_node(root_node, 36);
insert_node(root_node, 56);
insert_node(root_node, 78);
insert_node(root_node, 11);
insert_node(root_node, 15);

print(root_node, 0);

printHierarchy(root_node, 0);

return 0;
}
