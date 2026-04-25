#ifndef AVL_H
#define AVL_H

#define MAX_INPUT_COUNT 256

typedef struct AVLNode
{
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode *avl_create_node(int data);
int avl_height(const AVLNode *node);
int avl_balance_factor(const AVLNode *node);
void avl_update_height(AVLNode *node);
AVLNode *avl_insert(AVLNode *root, int data);
void avl_print_sideways(const AVLNode *root, int depth);
void avl_preorder(const AVLNode *root);
void avl_inorder(const AVLNode *root);
void avl_postorder(const AVLNode *root);
void avl_destroy(AVLNode *root);

#endif
