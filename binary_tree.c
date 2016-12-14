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
#include <stdbool.h>

#define itemtype int
#define public
#define private static

typedef struct node {
	itemtype value;
	struct node * right;
	struct node * left;
}Node;

typedef struct binarytree {
	void (*insert)(Node ** tree, itemtype value); 
	Node* (*search)(Node * tree, itemtype value);
	bool (*remove) (Node ** tree, itemtype value);
	int (*height) (Node * tree);
	void (*delete) (Node * tree);	
	void (*preOrder)(Node * tree);
	void (*posOrder)(Node * tree);
	void (*inOrder)(Node * tree);
	Node * root;
}BinaryTree;

/**
 * createNode allocates a new node with the given value and NULL left and right pointers
 *
 * @param itemtype value, value to insert.
 *
 * @returns a new Node, a pointer of type Node
 */
private Node * createNode(itemtype value){
	Node * aux;
	aux = (Node*) calloc(1, sizeof(Node));
	aux->left = NULL;
	aux->right = NULL;
	aux->value = value;
	return aux;
}

/**
 * Insert elements in binary tree.
 *
 * @param Node ** tree, the root of the tree, is a Node type pointer.
 * @param itemtype value, value to insert.
 *
 * @returns by parameter the tree with the new element.
 */
public void insert(Node ** tree, itemtype value){
	Node *aux = NULL;
	if((*tree) == NULL){
		*tree = createNode(value);
		return;
	}
	if(value < (*tree)->value){
		insert(&(*tree)->left, value);
	}
	else if(value > (*tree)->value){
		insert(&(*tree)->right, value);
	}
	else{
		return;
	}
}


/**
 * Search elements in binary tree.
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 * @param itemtype value, value to searched.
 *
 * @returns Node type pointer, Node referring to found element.
 */
public Node* search(Node * tree, itemtype value){
	if (tree == NULL){
		return  NULL;
	}
	else if(value < tree->value){
		search(tree->left, value);
	}
	else if(value > tree->value){
		search(tree->right, value);
	}
	else if(value == tree->value){
		return tree;
	}
	else{
		return NULL;
	}
}

/**
 * find the element with a minimum value on the left side.
 *
 * @param Node ** tree, the root of the tree, is a Node type pointer.
 *
 * @returns by the node referring the minimum element.
 */
private Node * findMinValue(Node * tree){
	if(tree->left == NULL)
		return tree;
	else{
		findMinValue(tree->left);
	}
}


/**
 * remove elements in binary tree.
 *
 * @param Node ** tree, the root of the tree, is a Node type pointer.
 * @param itemtype value, value to insert.
 *
 * @returns by parameter the tree with the new element.
 */
public bool removeNode(Node ** tree, itemtype value){
	Node * temp;
	if(*tree == NULL){
		return false;
	}
	else if(value < (*tree)->value){
		removeNode(&(*tree)->left, value);
	}
	else if(value > (*tree)->value){
		removeNode(&(*tree)->right, value);
	}
	else{
		if((*tree)->right && (*tree)->left){
			temp = findMinValue((*tree)->right);
			(*tree)->value = temp->value; 
			removeNode(&(*tree)->right, temp->value);
		}
		else{
			temp = *tree;
			if((*tree)->left == NULL){
				*tree = (*tree)->right;
			}
			else if((*tree)->right == NULL){
				*tree = (*tree)->left;
			}
			free(temp);
			return true;			
		}
	}
}

/**
 * height of binary tree.
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 * @returns a int type, is the height of tree
 */
public int height(Node * tree){
	if (tree == NULL)
		return 0;
	int left = height(tree->left);
	int right = height(tree->right);
	return (left > right) ? left + 1 : right + 1;
}

/**
 * Delete and free memory of binary tree.
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 */
public void delete_tree(Node * tree){
	if(tree != NULL){
		delete_tree(tree->left);
		delete_tree(tree->right);
		free(tree);
	}
}

/**
 * Print binary tree in preorder form.
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 */
public void print_pre_order(Node * tree) {
	if(tree != NULL){
		printf("%d ", tree->value);					
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
}

/**
 * Print binary tree in inorder form.
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 */
public void print_in_order(Node * tree) {
	if(tree != NULL){
		print_in_order(tree->left);		
		printf("%d ", tree->value);					
		print_in_order(tree->right);
	}
}


/**
 * Print binary tree in posorder form.
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 */
public void print_pos_order(Node * tree) {
	if(tree != NULL){
		print_pos_order(tree->left);	
		print_pos_order(tree->right);				
		printf("%d ", tree->value);					
	}
}

/**
 * method constructor
 *
 * @returns a new BinaryTree type
 */
public BinaryTree binarytree(){
	BinaryTree new_bt;
	new_bt.insert = &insert;
	new_bt.remove = &removeNode;
	new_bt.search = &search;	
	new_bt.height = &height;
	new_bt.delete = &delete_tree;
	new_bt.preOrder = &print_pre_order;
	new_bt.posOrder = &print_pos_order;
	new_bt.inOrder = &print_in_order;	
	new_bt.root = NULL;
	return new_bt;
}

/**
 * Main program
 *
 */
int main(){
	Node * temp;

	BinaryTree tree = binarytree();
	int h = 0;

	tree.insert(&tree.root, 9);
	tree.insert(&tree.root, 4);
	tree.insert(&tree.root, 15);
	tree.insert(&tree.root, 6);
	tree.insert(&tree.root, 12);
	tree.insert(&tree.root, 3);
	tree.insert(&tree.root, 2);

	printf("Pre Order\n");
	tree.preOrder(tree.root); 
	printf("\n\n");	
	printf("In Order\n");
	tree.inOrder(tree.root); 
	printf("\n\n");	
	printf("Pos Order\n");
	tree.posOrder(tree.root); 
	printf("\n\n");	 

	temp = tree.search(tree.root, 12); 
	printf("Found element %d\n", temp->value);

	h = tree.height(tree.root); 
	printf("height: %d\n", h);

	tree.remove(&tree.root, 4);

	tree.inOrder(tree.root); 
	printf("\n\n");		
	tree.delete(tree.root);

	return 0;
}
