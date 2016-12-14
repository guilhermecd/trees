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
#define public
#define private static	
#define RED 0
#define BLACK 1


typedef struct node {
  itemtype data;
  int color; /* if red=0 then the node is black */
  struct node * left;
  struct node * right;
  struct node * parent;
} Node;

/**
 * Insert elements in binary tree.
 *
 * @param node ** tree, the root of the tree, is a node type pointer.
 * @param itemtype val, value to insert.
 *
 * @returns by parameter the tree with the new element.
 */
public void insert(Node ** tree, itemtype value){

	if ((*tree) == NULL){
		*tree = (createNode(value));
		return;
	}
	if (value < (*tree)->data){
		insert(&(*tree)->left, value);
	}
	else if (value > (*tree)->data){
		insert(&(*tree)->right, value);
	}
	else{
		return;
	}

	(*tree)->height = 1 + max(height(&(*tree)->left), height(&(*tree)->right));

	balance = getBalance(&(*tree));
 
	if (balance > 1 && value < (*tree)->left->data){
		rightRotate(&(*tree));
		return;
	}
	else if (balance < -1 && value > (*tree)->right->data){
		leftRotate(&(*tree));
		return;
	}
	else if (balance > 1 && value > (*tree)->left->data){
		leftRotate(&(*tree)->left);
		rightRotate(&(*tree));
		return;
	}
	else if (balance < -1 && value < (*tree)->right->data){
		rightRotate(&(*tree)->right);
		leftRotate(&(*tree));
		return;
	}
}

/**
 * Print avl tree in inorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 *
 */
public void print_in_order(Node * tree) {
	if(tree != NULL){
		print_in_order(tree->left);		
		printf("%d ", tree->data);
		print_in_order(tree->right);
	}
}

int main(){

	return 0;
}