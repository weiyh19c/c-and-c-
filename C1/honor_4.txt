#include <stdio.h>
#include <stdlib.h>

typedef struct node  // define a node in tree
{
    int value;
    struct node *right;
    struct node *left;
} node, *ptree;

void inorder(ptree root)  // walk the tree in order
{
    if (root!= NULL)
    {
        inorder(root->left);
        printf("%d\t", root->value);
        inorder(root->right);
    }
}

ptree new_node(void) { return malloc(sizeof(node)); }  // allocate space for a node

ptree init_node(int n, ptree l, ptree r)  // initialize a node of tree
{
    ptree t = new_node();
    t->value = n;
    t->right = r;
    t->left = l;
    return t;
}

ptree create_tree(int d[], int i, int size)  //  create a tree from an array
{
    if (i >= size)
        return NULL;
    else
        return (init_node(d[i], 
        create_tree(d, 2 * i + 1, size),
        create_tree(d, 2 * i + 2, size)));
}

int main(void)
{
    FILE *in;
    int count = 0, i;

    in = fopen("input_integer.txt", "r+");  // open a file reading integers

    if (fscanf(in, "%d", &count) != 1)  // obtain number of integers
    {
        fprintf(stderr, "Error by integers");
        exit(EXIT_FAILURE);
    }

    int data[count];
    for (i = 0; i < count; i++)  // read integers to an array
    {
        fscanf(in, "%d", &data[i]);
    }

    ptree new_one = create_tree(data, 0, count);  // generate a new tree
    inorder(new_one);  //  print integers in order

    return 0;
}