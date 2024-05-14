#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>

typedef struct node
{
    char *data;
    struct node *left, *right;
} node;

node *findMin(node *root)
{
    if (root == NULL)
        return root;
    if (root->left == NULL)
        return root;
    else
        return findMin(root->left);
}

node *findMax(node *root)
{
    if (root == NULL)
        return root;
    if (root->right == NULL)
        return root;
    else
        return findMax(root->right);
}

node *search(node *root, char *x)
{
    if (root == NULL)
        return NULL;
    else if (!strcasecmp(x, root->data))
        return root;
    else if (strcasecmp(x, root->data) < 0)
        return search(root->left, x);
    else
        return search(root->right, x);
}

node *getpredecessor(node *root, char *data)
{
    node *current = search(root, data);
    if (current == NULL)
        return NULL;
    if (current->left != NULL)
        return findMax(current->left);
    else
    {
        node *predecessor = NULL;
        node *ancestor = root;
        while (ancestor != current)
        {
            if (strcasecmp(current->data, ancestor->data) > 0)
            {
                predecessor = ancestor;
                ancestor = ancestor->right;
            }
            else
                ancestor = ancestor->left;
        }
    }
}

node *getsuccessor(node *root, char *data)
{
    node *current = search(root, data);
    if (current == NULL)
        return NULL;
    if (current->right != NULL)
        return findMin(current->right);
    else
    {
        node *successor = NULL;
        node *ancestor = root;
        while (ancestor != current)
        {
            if (strcasecmp(current->data, ancestor->data) < 0)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return successor;
    }
}

void main()
{
    printf("hello world!");
}