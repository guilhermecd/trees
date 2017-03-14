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

#include "binary_tree.h"
   
/**
 * Main program 
 * Example of how to use the functions of the avl tree
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
