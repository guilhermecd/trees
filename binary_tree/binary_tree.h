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


public BinaryTree binarytree();