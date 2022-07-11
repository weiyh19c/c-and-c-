#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 100
#define NCOLS 5

typedef struct node {
    int value;
    struct node *next;
} Node;

typedef Node *List;

int main(void)
{
    int i, j, k, temp, index;
    List head = NULL, prev, current;
    srand(time(0));
    for (i = 0; i < NUM; i++)  // generate 100 random integers
    {
        current = malloc(sizeof(Node));
        if (head == NULL)
            head = current;
        else
            prev->next = current;
        current->next = NULL;
        current->value = rand() % 100 + 1;
        prev = current;
    }

    index = 1;
    current = head;
    printf("\nHere are %d random numbers:\n", NUM);
    while (current != NULL) // print random numbers, in row of 5
    {
        if (index % NCOLS == 0)
            printf("%d\n", current->value);
        else
            printf("%d\t", current->value);
        current = current->next;
        index++;
    }


    current = head;
    while (current->next != NULL) // sort integers with bubble sort
    {
        prev = current->next;
        while (prev != NULL)
        {
            if (current->value > prev->value)
            {
                temp = prev->value;
                prev->value = current->value;
                current->value = temp;
            }
            prev = prev->next;
        }
        current = current->next;
    }

    printf("\n\nHere's %d sorted numbers:\n", NUM);

    index = 1;
    current = head;
    while (current != NULL)  // print random numbers, in row of 5
    {
        if (index % NCOLS  == 0)
            printf("%d\n", current->value);
        else
            printf("%d\t", current->value);
        current = current->next;
        index++;
    }

    current = head;  // set off space for generated integers
    while (current != NULL)
    {
        head = current->next;
        free(current);
        current = head;
    }
    return 0;
}
