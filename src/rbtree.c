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

void rb_transplant(rbtree *t, node_t *u, node_t *v){
  if(u->parent == t->nil){
    t->root = v;
  }
  else if (u == u->parent->left)
  { 
    u->parent->left = v; // 부모 입장에서 자식을 설정
  }
  else
    u->parent->right = v; // 부모 입장에서 자식을 설정
  v->parent = u->parent; // 자식 입장에서 부모를 설정
}

void delete_node(rbtree *t, node_t* rnode){
  if(rnode == t->nil){
    return;
  }
  delete_node(t, rnode->left);
  delete_node(t, rnode->right);
  free(rnode);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  delete_node(t, t->root);
  free(t->nil);
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
  newNode->color = RBTREE_RED;
  
  rb_insert_fixup(t, newNode);

  return t->root;
}



node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *p = t->root;
  while(p != t->nil){
    if(p->key==key){
      return p;
    }
    else if(p->key < key)
      p = p -> right;
    else
      p = p-> left;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *p = t->root;
  while (p->left != t->nil)
  {
    p = p->left;
  }
  
  return p;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement   
  node_t *p = t->root;
  while (p->right != t->nil)
  {
    p = p->right;
  }
  
  return p;
}
node_t *tree_minimum(rbtree *t, node_t *x){
  while(x->left != t->nil){
    x = x->left;
  }
  return x;
}


void rb_erase_fixup(rbtree *t, node_t *x){
  while(x!=t->root && x->color == RBTREE_BLACK){
    if(x==x->parent->left){
      node_t *w = x->parent->right;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if(w->left->color == RBTREE_BLACK && w->right->color==RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->right->color == RBTREE_BLACK)
        {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;

        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t,x->parent);
        x = t->root;
      }
    }
    else {
      node_t *w = x->parent->left;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if(w->right->color == RBTREE_BLACK && w->left->color==RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->left->color == RBTREE_BLACK)
        {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;

        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t,x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t *y = z;
  color_t y_original_color = y->color;
  node_t *x;
  if(z->left == t->nil){
    x = z->right;
    rb_transplant(t,z,z->right);
  }
  else if (z->right==t->nil)
  {
    x = z->left;
    rb_transplant(t, z, z->left);
  }
  else 
  {
    y = tree_minimum(t, z->right);
    y_original_color = y->color;
    x = y->right;
    if(y->parent == z){
      x->parent = y;
    }
    else {
      rb_transplant(t,y,y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rb_transplant(t,z,y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if(y_original_color == RBTREE_BLACK){
    rb_erase_fixup(t, x);
  }
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  inorder(t, t->root, arr, n, 0);
  return 0;
}

int inorder(const rbtree *t, node_t *root, key_t *arr, const size_t n, size_t i){
  if(root == t->nil || i >= n)
    return i;
i = inorder(t, root->left, arr, n, i);

arr[i] = root->key;
i++;

i= inorder(t, root->right, arr, n, i);

return i;
    
}