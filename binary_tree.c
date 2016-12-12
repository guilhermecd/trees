/*
	The C programming language includes a very limited standard library in
	comparison to other modern programming languages.  This is a collection of
	common Computer Science algorithms which may be used in C projects.

	Copyright (C) 2016, Guilherme Castro Diniz.
	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License as
	published by the Free Software Foundation (FSF); in version 2 of the
	license.
	This program is distributed in the hope that it can be useful,
	but WITHOUT ANY IMPLIED WARRANTY OF ADEQUATION TO ANY
	MARKET OR APPLICATION IN PARTICULAR. See the
	GNU General Public License for more details.
	<http://www.gnu.org/licenses/>
*/

#include <stdio.h>
#include <stdlib.h>

#define itemtype int

typedef struct bin_tree {
	itemtype data;
	struct bin_tree * right;
	struct bin_tree * left;
}node;

/**
 * Insert elements in binary tree.
 *
 * @param node ** tree, the root of the tree, is a node type pointer.
 * @param itemtype val, value to insert.
 *
 * @returns by parameter the tree with the new element.
 */
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

/**
 * Search elements in binary tree.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 * @param itemtype val, value to searched.
 *
 * @returns node type pointer, node referring to found element.
 */
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

/**
 * Delete and free memory of binary tree.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 *
 */
void delete_tree(node * tree){
	if(tree != NULL){
		delete_tree(tree->left);
		delete_tree(tree->right);
		free(tree);
	}
}

/**
 * Print binary tree in preorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 *
 */
void print_pre_order(node * tree) {
	if(tree != NULL){
		printf("%d\n", tree->data);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}

/**
 * Print binary tree in inorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 *
 */
void print_in_order(node * tree) {
	if(tree != NULL){
		print_in_order(tree->left);		
		printf("%d\n", tree->data);
		print_in_order(tree->right);
	}
}

/**
 * Print binary tree in posorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 *
 */
void print_pos_order(node * tree) {
	if(tree != NULL){
		print_pos_order(tree->left);	
		print_pos_order(tree->right);				
		printf("%d\n", tree->data);					
	}
}

/**
 * Main program
 *
 */
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