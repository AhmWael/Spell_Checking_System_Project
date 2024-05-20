#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node
{
    char *data;
    struct Node *left, *right;
} Node;

Node *newNode(char *data);
Node *insertNode(Node *node, char *data);
Node *findMin(Node *root);
Node *findMax(Node *root);
Node *search(Node *root, char *key);
Node *getpredecessor(Node *root, Node *current);
Node *getsuccessor(Node *root, Node *current);
Node *load();
int findHeight(Node *root);

Node *newNode(char *data)
{
    Node *n = malloc(sizeof(Node));
    n->data = malloc(strlen(data) + 1);
    strcpy(n->data, data);
    n->left = n->right = NULL;
    return n;
}

Node *insertNode(Node *node, char *data)
{
    if (!node)
        return newNode(data);

    if (strcasecmp(data, node->data) < 0)
        node->left = insertNode(node->left, data);
    else if (strcasecmp(data, node->data) > 0)
        node->right = insertNode(node->right, data);
    return node;
}

Node *load()
{
    printf("\nLoading dictionary...\n");
    FILE *fp;
    fp = fopen("Dictionary.txt", "r");
    if (fp == NULL)
    {
        printf("Error: Dictionary.txt file not found\nQuitting the program.\n");
        fclose(fp);
        exit(2);
    }
    char record[50];
    rewind(fp);
    int num_word = 0;
    Node *root = NULL;
    while (fgets(record, sizeof(record), fp))
    {
        if (record[0] == '\n')
            continue; // skip empty line
        num_word++;
        record[strlen(record) - 1] = '\0'; // remove \n
        // printf("Record: \"%s\"", record);
        root = insertNode(root, record);
    }
    printf("..................................\n");
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    printf("Size = %d\n", num_word);
    printf("..................................\n");
    printf("Height = %d\n", findHeight(root));
    printf("..................................\n");
    rewind(fp);
    fclose(fp);
    return root;
}

Node *findMin(Node *root)
{
    if (root == NULL)
        return root;
    if (root->left == NULL)
        return root;
    else
        return findMin(root->left);
}

Node *findMax(Node *root)
{
    if (root == NULL)
        return root;
    if (root->right == NULL)
        return root;
    else
        return findMax(root->right);
}

int findHeight(Node *root)
{
    if(root == NULL)
        return -1;
    return 1 + fmax(findHeight(root->left), findHeight(root->right));
}

Node *search(Node *root, char *key)
{
    if (root == NULL)
        return NULL;
    else if (!strcasecmp(key, root->data))
        return root;
    else if (strcasecmp(key, root->data) < 0)
        if (root->left)
            return search(root->left, key);
        else
            return root;
    else if (root->right)
        return search(root->right, key);
    else
        return root;
}

Node *getpredecessor(Node *root, Node *current)
{
    if (current == NULL)
        return NULL;
    if (current->left != NULL)
        return findMax(current->left);
    else
    {
        Node *predecessor = NULL;
        Node *ancestor = root;
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
        return predecessor;
    }
}

Node *getsuccessor(Node *root, Node *current)
{
    if (current == NULL)
        return NULL;
    if (current->right != NULL)
        return findMin(current->right);
    else
    {
        Node *successor = NULL;
        Node *ancestor = root;
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
    Node *root = load();
    char *sentence = malloc(80);
    printf("\nEnter a sentence: ");
    fgets(sentence, 80, stdin);
    sentence[strlen(sentence) - 1] = '\0';
    char *token = strtok(sentence, " ");
    while (token)
    {
        Node *temp = search(root, token);
        if (!strcasecmp(token, temp->data))
            printf("%s - CORRECT\n", token);
        else
        {
            Node *successor = getsuccessor(root, temp);
            Node *predecessor = getpredecessor(root, temp);
            printf("%s - Incorrect, Suggestions: %s %s %s\n", token, temp->data, successor ? successor->data : "", predecessor ? predecessor->data : "");
        }
        token = strtok(NULL, " ");
    }
}