#include "stdio.h"
#include "stdlib.h"

struct node {
  int key_value;
  struct node *left;
  struct node *right;
};

void
destroy_tree(struct node *leaf) {
  if(leaf != 0) {
    destroy_tree(leaf->left);
    destroy_tree(leaf->right);

    /* no memory leaks on us */
    free(leaf);
  }
}

struct node*
df_search(int key, struct node *leaf) {
  if(leaf == 0) {
    return 0;
  }

  if(key == leaf->key_value) {
    return leaf;
  } else if(key > leaf->key_value) {
    return df_search(key, leaf->right);
  } else {
    return df_search(key, leaf->left);
  }
}

void
insert(int key, struct node **leaf) {
  if(*leaf == 0) {
    *leaf = (struct node*) malloc(sizeof(struct node));
    (*leaf)->key_value = key;
    (*leaf)->left = 0;
    (*leaf)->right = 0;
  } else if(key > (*leaf)->key_value) {
    insert(key, &(*leaf)->right);
  } else {
    insert(key, &(*leaf)->left);
  }
}

int
main() {
  printf("hi\n");

  struct node *root = 0;
  insert(2, &root);
  insert(12, &root);
  insert(10, &root);
  insert(3, &root);
  insert(5, &root);

  if(df_search(12, root) == 0) {
    printf("oops\n");
  } else {
    printf("yay!\n");
  }
}
