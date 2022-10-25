#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

  new_node->color = RBTREE_BLACK;
  p->nil = new_node;
  p->root = p->nil;

 
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

void left_rotate(rbtree *t, node_t* x) {
  node_t* y = x->right;
  x->right = y->left;
  if(y->left != t->nil){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->nil){
    t->root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else 
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t* x) {
  node_t* y = x->left;
  x->left = y->right;
  if(y->right != t->nil){
    y->right->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->nil){
    t->root = y;
  }
  else if (x == x->parent->right)
  {
    x->parent->right = y;
  }
  else 
    x->parent->left = y;
  y->right = x;
  x->parent = y;
}

void rb_insert_fixup(rbtree *t, node_t* z){
  while(z->parent->color == 0){
    if(z->parent == z->parent->parent->left){
      node_t* y = z->parent->parent->right;
      if(y->color == 0){
        z->parent->color = 1;
        y->color = 1;
        z->parent->parent->color = 0;
        z = z->parent->parent;
      }
      else{ 
        if (z == z->parent->right)
        {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = 1;
        z->parent->parent->color = 0;
        right_rotate(t, z->parent->parent);
      }
    }
    else{
      node_t* y = z->parent->parent->left;
      if(y->color == 0){
        z->parent->color = 1;
        y->color = 1;
        z->parent->parent->color = 0;
        z = z->parent->parent;
      }
      else{ 
        if (z == z->parent->left)
        {
          z = z->parent;
          right_rotate(t, z);
        }
        z->parent->color = 1;
        z->parent->parent->color = 0;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = 1;
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t* y = t->nil;
  node_t* x = t->root;
  node_t* newNode = (node_t*)malloc(sizeof(node_t));
  newNode->key = key;
  
  while(x != t->nil){
    y = x;
    if (newNode->key < x->key){
      x = x->left;
    }
    else
      x = x->right;
  }
  
  newNode->parent = y;
  if (y == t->nil)
    t->root = newNode;
  else if (newNode->key < y->key)
  {
    y->left = newNode;
  }
  else
    y->right = newNode;

  newNode->left = newNode->right = t->nil;
  newNode->color = 0;
  
  rb_insert_fixup(t, newNode);

  return t->root;
}




node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
