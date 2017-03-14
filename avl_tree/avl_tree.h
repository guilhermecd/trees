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

/**
 * TREE STRUCTURES, TYPES. 
 *
 */
#define itemtype int

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
 * method constructor
 *
 * @returns a new BinaryTree type and all functions
 */
AvlTree avltree();
