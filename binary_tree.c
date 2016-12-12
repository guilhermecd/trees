#include <stdio.h>
#include <stdlib.h>

#define itemtype int

typedef struct bin_tree {
	itemtype data;
	struct bin_tree * right;
	struct bin_tree * left;
}node;

void insert(node ** tree, itemtype val){
	node *aux = NULL;
	if((*tree) == NULL){
		aux = (node*) calloc(1, sizeof(node));
		aux->left = NULL;
		aux->right = NULL;
		aux->data = val;
		*tree = aux;
		return;
	}
	if(val < (*tree)->data){
		insert(&(*tree)->left, val);
	}
	else if(val > (*tree)->data){
		insert(&(*tree)->right, val);
	}
}

node* search(node * tree, itemtype val){
	if (tree == NULL){
		return  NULL;
	}
	else if(val < tree->data){
		search(tree->left, val);
	}
	else if(val > tree->data){
		search(tree->right, val);
	}
	else if(val == tree->data){
		return tree;
	}
}

void delete_tree(node * tree){
	if(tree != NULL){
		delete_tree(tree->left);
		delete_tree(tree->right);
		free(tree);
	}
}
void print_pre_order(node * tree) {
	if(tree != NULL){
		printf("%d\n", tree->data);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}

void print_in_order(node * tree) {
	if(tree != NULL){
		print_in_order(tree->left);		
		printf("%d\n", tree->data);
		print_in_order(tree->right);
	}
}

void print_pos_order(node * tree) {
	if(tree != NULL){
		print_pos_order(tree->left);	
		print_pos_order(tree->right);				
		printf("%d\n", tree->data);					
	}
}

int main(){
	node *root;
	node * temp;
	root = NULL;
	insert(&root, 9);
	insert(&root, 4);
	insert(&root, 15);
	insert(&root, 6);
	insert(&root, 12);
	printf("Pre Order\n");
	print_pre_order(root); 
	printf("In Order\n");
	print_in_order(root);
	printf("Pos Order\n");
	print_pos_order(root);  

	temp = search(root, 15);
	printf("%d\n", temp->data);

	delete_tree(root);

	return 0;
}