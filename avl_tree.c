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
typedef enum {false, true} bool;

typedef struct node{
	itemtype value;
	struct node * left;
	struct node * right;
	int height;
}Node;

typedef struct avltree {
	void (*insert)(Node ** tree, itemtype value);
	Node* (*search)(Node * tree, itemtype value);
	int (*height) (Node ** tree);
	void (*delete) (Node * tree);	
	void (*preOrder)(Node * tree);
	void (*posOrder)(Node * tree);
	void (*inOrder)(Node * tree);
	bool (*remove) (Node ** tree, itemtype value);
	Node * root;
}AvlTree;

/**
 * createNode allocates a new node with the given value and NULL left and right pointers
 *
 * @param itemtype value, value to insert.
 *
 * @returns a new node, a pointer of type node
 */
private Node* createNode(itemtype value){
	Node* aux;
	aux = (Node*) calloc(1, sizeof(Node));
	aux->value = value;
	aux->left = NULL;
	aux->right = NULL;
	aux->height = 1;
	return aux;
}

/**
 * get height of avl tree.
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 * @returns a integer type, is the height of tree 
 */
public int height(Node ** tree){
	if ((*tree) == NULL){
		return 0;
	}
	return (*tree)->height;
}

/**
 * get the highest value between two integers 
 *
 * @param int a, first value
 * @param int b, second value
 *
 * @returns a integer type, is the highest value between two integers
 */ 
private int max(int a, int b){
	return (a > b)? a : b;
}

/**
 * get balance factor of node .
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 * @returns a integer type, is the balance factor of a node 
 */
private int getBalance(Node ** tree){
	if ((*tree) == NULL){
		return 0;
	}
	return height(&(*tree)->left) - height(&(*tree)->right);
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
 * Right Rotate 
 *
 * @param Node ** tree, the root of the tree, is a Node type pointer.
 *
 * @returns by parameter a new tree with a right rotate.
 */
private void rightRotate( Node ** tree){
	Node * tree_balance = (*tree)->left;
	Node * aux = tree_balance->right;

	tree_balance->right = (*tree);
	(*tree)->left = aux;

	(*tree)->height = max(height(&(*tree)->left), height(&(*tree)->right))+1;
	tree_balance->height = max(height(&tree_balance->left), height(&tree_balance->right))+1;
	(*tree) = tree_balance;
}

/**
 * Left Rotate 
 *
 * @param Node ** tree, the root of the tree, is a Node type pointer.
 *
 * @returns by parameter a new tree with a left rotate.
 */
private void leftRotate(Node ** tree){
	Node * tree_balance = (*tree)->right;
	Node * aux = tree_balance->left;

	tree_balance->left = (*tree);
	(*tree)->right = aux;

	(*tree)->height = max(height(&(*tree)->left), height(&(*tree)->right))+1;
	tree_balance->height = max(height(&tree_balance->left), height(&tree_balance->right))+1;
	(*tree) = tree_balance;
}

/**
 * Insert elements in binary tree.
 *
 * @param node ** tree, the root of the tree, is a node type pointer.
 * @param itemtype val, value to insert.
 *
 * @returns by parameter the tree with the new element.
 */
public void insert(Node ** tree, itemtype value){
	int balance;
	if ((*tree) == NULL){
		*tree = (createNode(value));
		return;
	}
	if (value < (*tree)->value){
		insert(&(*tree)->left, value);
	}
	else if (value > (*tree)->value){
		insert(&(*tree)->right, value);
	}
	else{
		return;
	}

	(*tree)->height = 1 + max(height(&(*tree)->left), height(&(*tree)->right));

	balance = getBalance(&(*tree));

	if (balance > 1 && value < (*tree)->left->value){
		rightRotate(&(*tree));
		return;
	}
	else if (balance < -1 && value > (*tree)->right->value){
		leftRotate(&(*tree));
		return;
	}
	else if (balance > 1 && value > (*tree)->left->value){
		leftRotate(&(*tree)->left);
		rightRotate(&(*tree));
		return;
	}
	else if (balance < -1 && value < (*tree)->right->value){
		rightRotate(&(*tree)->right);
		leftRotate(&(*tree));
		return;
	}
}

/**
 * remove elements in Avl tree.
 *
 * @param Node ** tree, the root of the tree, is a Node type pointer.
 * @param itemtype value, value to insert.
 *
 * @returns true if element removed or false if element not remove.
 */
public bool removeNode(Node ** tree, itemtype value){
	Node * temp;	
	int balance;

	if ((*tree) == NULL){
		return false;
	}
	if ( value < (*tree)->value ){
		removeNode(&(*tree)->left, value);
	}
	else if( value > (*tree)->value ){
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
		}
	}

	if ((*tree) == NULL){
		return true;
	}

	(*tree)->height = 1 + max(height(&(*tree)->left),
			height(&(*tree)->right));

	balance = getBalance(&(*tree));

	if (balance > 1 && getBalance(&(*tree)->left) >= 0){
		rightRotate(&(*tree));
	}
	if (balance > 1 && getBalance(&(*tree)->left) < 0){
		leftRotate(&(*tree)->left);
		rightRotate(&(*tree));
	}
	if (balance < -1 && getBalance(&(*tree)->right) <= 0){
		leftRotate(&(*tree));
	}
	if (balance < -1 && getBalance(&(*tree)->right) > 0){
		rightRotate(&(*tree)->right);
		leftRotate(&(*tree));
	}
	return true;
}

/**
 * Search elements in avl tree.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 * @param itemtype val, value to searched.
 *
 * @returns node type pointer, node referring to found element.
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
}

/**
 * Delete and free memory of avl tree.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
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
 * Print avl tree in preorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
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
 * Print avl tree in inorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
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
 * Print avl tree in posorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
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
public AvlTree avltree(){
	AvlTree new_avl;
	new_avl.insert = &insert;
	new_avl.search = &search;	
	new_avl.remove = &removeNode;	
	new_avl.height = &height;
	new_avl.delete = &delete_tree;
	new_avl.preOrder = &print_pre_order;
	new_avl.posOrder = &print_pos_order;
	new_avl.inOrder = &print_in_order;	
	new_avl.root = NULL;
	return new_avl;
}

/**
 * Main program
 *
 */
int main(){
	Node * temp;

	AvlTree tree = avltree();
	int h = 0;

	tree.insert(&tree.root, 5);
	tree.insert(&tree.root, 10);
	tree.insert(&tree.root, 20);
	tree.insert(&tree.root, 30);
	tree.insert(&tree.root, 40);
	tree.insert(&tree.root, 50);

	printf("Pre Order\n");
	tree.preOrder(tree.root); 
	printf("\n\n");	
	printf("In Order\n");
	tree.inOrder(tree.root); 
	printf("\n\n");	
	printf("Pos Order\n");
	tree.posOrder(tree.root); 
	printf("\n\n");	 

	temp = tree.search(tree.root, 11); 
	if(temp != NULL) {
		printf("Found element %d\n", temp->value);
	}

	h = tree.height(&tree.root); 
	printf("height: %d\n", h);

	tree.remove(&tree.root, 10); 

	tree.delete(tree.root);

	return 0;
}
