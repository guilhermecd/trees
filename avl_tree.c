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

typedef struct node{
    itemtype data;
    struct node *left;
    struct node *right;
    int height;
}Node;

/**
 * createNode allocates a new node with the given value and NULL left and right pointers
 *
 * @param itemtype value, value to insert.
 *
 * @returns a new node, a pointer of type node
 */
Node* createNode(itemtype value){
    Node* aux;
    aux = (Node*) calloc(1, sizeof(Node));
    aux->data = value;
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
int height(Node * tree){
    if (tree == NULL){
        return 0;
    }
    return tree->height;
}

/**
 * get the highest value between two integers 
 *
 * @param int a, first value
 * @param int b, second value
 *
 * @returns a integer type, is the highest value between two integers
 */ 
int max(int a, int b){
    return (a > b)? a : b;
}

/**
 * get balance factor of node .
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 * @returns a integer type, is the balance factor of a node 
 */
int getBalance(Node * tree){
    if (tree == NULL){
        return 0;
    }
    return height(tree->left) - height(tree->right);
}

/**
 * Right Rotate 
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 * @returns a pointer of Node. Returns the old tree but with right rotation
 */
Node * rightRotate( Node * tree){
    Node * tree_balance = tree->left;
    Node * aux = tree_balance->right;

    tree_balance->right = tree;
    tree->left = aux;
 
    tree->height = max(height(tree->left), height(tree->right))+1;
    tree_balance->height = max(height(tree_balance->left), height(tree_balance->right))+1;
 
    return tree_balance;
}

/**
 * Left Rotate 
 *
 * @param Node * tree, the root of the tree, is a Node type pointer.
 *
 * @returns a pointer of Node. Returns the old tree but with left rotation
 */
Node * leftRotate(Node * tree){
    Node * tree_balance = tree->right;
    Node * aux = tree_balance->left;
 
    tree_balance->left = tree;
    tree->right = aux;
 
    tree->height = max(height(tree->left), height(tree->right))+1;
    tree_balance->height = max(height(tree_balance->left), height(tree_balance->right))+1;
    return tree_balance;
}
 
/**
 * Insert elements in binary tree.
 *
 * @param node ** tree, the root of the tree, is a node type pointer.
 * @param itemtype val, value to insert.
 *
 * @returns by parameter the tree with the new element.
 */
Node* insert(Node* tree, itemtype value){
    if (tree == NULL){
        return(createNode(value));
    }
    if (value < tree->data){
        tree->left  = insert(tree->left, value);
    }
    else if (value > tree->data){
        tree->right = insert(tree->right, value);
    }
    else{
        return tree;
    }

    tree->height = 1 + max(height(tree->left), height(tree->right));

    int balance = getBalance(tree);
 
    if (balance > 1 && value < tree->left->data){
        return rightRotate(tree);
    }
    if (balance < -1 && value > tree->right->data){
        return leftRotate(tree);
    }
    if (balance > 1 && value > tree->left->data){
        tree->left =  leftRotate(tree->left);
        return rightRotate(tree);
    }
    if (balance < -1 && value < tree->right->data){
        tree->right = rightRotate(tree->right);
        return leftRotate(tree);
    }

    return tree;
}

/**
 * Search elements in avl tree.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 * @param itemtype val, value to searched.
 *
 * @returns node type pointer, node referring to found element.
 */
Node* search(Node * tree, itemtype value){
	if (tree == NULL){
		return  NULL;
	}
	else if(value < tree->data){
		search(tree->left, value);
	}
	else if(value > tree->data){
		search(tree->right, value);
	}
	else if(value == tree->data){
		return tree;
	}
}

/**
 * Delete and free memory of avl tree.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 *
 */
void delete_tree(Node * tree){
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
void print_pre_order(Node * tree) {
	if(tree != NULL){
		printf("%d ", tree->data);
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
void print_in_order(Node * tree) {
	if(tree != NULL){
		print_in_order(tree->left);		
		printf("%d ", tree->data);
		print_in_order(tree->right);
	}
}

/**
 * Print avl tree in posorder form.
 *
 * @param node * tree, the root of the tree, is a node type pointer.
 *
 */
void print_pos_order(Node * tree) {
	if(tree != NULL){
		print_pos_order(tree->left);	
		print_pos_order(tree->right);				
		printf("%d ", tree->data);					
	}
}

/**
 * Main program
 *
 */
int main(){
	Node * root = NULL;
 	Node * temp;
 	int h;

	root = insert(root, 11);
	root = insert(root, 12);
	root = insert(root, 14);
	root = insert(root, 15);
	root = insert(root, 16);
	root = insert(root, 13);

	printf("Pre Order\n");
	print_pre_order(root);
	printf("\n\n");
	printf("In Order\n");
	print_in_order(root);
	printf("\n\n");
	printf("Pos Order\n");	
	print_pos_order(root);
	printf("\n\n");

 	temp = search(root, 10);
	printf("Found element %d\n", temp->data);

	h = height(root);
	printf("height: %d\n", h);

 	delete_tree(root);
	return 0;
}