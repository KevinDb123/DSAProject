#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

static int max_int(int a, int b)
{
    return a > b ? a : b;
}

AVLNode *avl_create_node(int data)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));

    if (node == NULL)
    {
        return NULL;
    }

    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int avl_height(const AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

void avl_update_height(AVLNode *node)
{
    if (node == NULL)
    {
        return;
    }

    node->height = max_int(avl_height(node->left), avl_height(node->right)) + 1;
}

int avl_balance_factor(const AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return avl_height(node->left) - avl_height(node->right);
}

static AVLNode *rotate_right(AVLNode *root)
{
    /*
     * TODO:
     * Complete the right rotation.
     */

    return root;
}

static AVLNode *rotate_left(AVLNode *root)
{
    /*
     * TODO:
     * Complete the left rotation.
     */

    return root;
}

AVLNode *avl_insert(AVLNode *root, int data)
{
    /*
     * TODO:
     * Complete AVL insertion and rebalancing.
     */

    return root;
}

void avl_print_sideways(const AVLNode *root, int depth)
{
    int i;

    if (root == NULL)
    {
        return;
    }

    avl_print_sideways(root->right, depth + 1);

    for (i = 0; i < depth; ++i)
    {
        printf("    ");
    }
    printf("%d\n", root->data);

    avl_print_sideways(root->left, depth + 1);
}

void avl_preorder(const AVLNode *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->data);
    avl_preorder(root->left);
    avl_preorder(root->right);
}

void avl_inorder(const AVLNode *root)
{
    if (root == NULL)
    {
        return;
    }

    avl_inorder(root->left);
    printf("%d ", root->data);
    avl_inorder(root->right);
}

void avl_postorder(const AVLNode *root)
{
    if (root == NULL)
    {
        return;
    }

    avl_postorder(root->left);
    avl_postorder(root->right);
    printf("%d ", root->data);
}

void avl_destroy(AVLNode *root)
{
    if (root == NULL)
    {
        return;
    }

    avl_destroy(root->left);
    avl_destroy(root->right);
    free(root);
}
