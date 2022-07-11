#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXRANGE 50
#define NUM 200
#define NCOLS 10

typedef struct node
{
    struct node *prev;
    int value;
    struct node *next;
} Node, *list;

list random_list(int n)  // generate random numbers by double linked list
{
    int i;
    list head = NULL, current, back;
    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        current = (list)malloc(sizeof(Node));
	current->next = (list)malloc(sizeof(Node));     
        if (head == NULL)
        {
            head = current;
	    current->prev = (list)malloc(sizeof(Node));
            current->prev = NULL;
        }
        else
        {
            current->prev = back;
            back->next = current;
        }    
	current->next = NULL;
        current->value = rand() % MAXRANGE;
        back = current;
    }
    return head;
}

void print_list(list head) //  print integers in row of 10
{
    int index = 1;
    list current = head;
    while (current != NULL)
    {
        if (index % NCOLS == 0)
            printf("%d\n", current->value);
        else
            printf("%d\t", current->value);
        current = current->next;
        index++;
    }
}

list sort_by_bubble(list head)
{
    int temp;
    list current = head, fore;
    while (current->next != NULL) // sort integers with bubble sort
    {
        fore = current->next;
        while (fore != NULL)
        {
            if (current->value > fore->value)
            {
                temp = fore->value;
                fore->value = current->value;
                current->value = temp;
            }
            fore = fore->next;
        }
        current = current->next;
	if (current == NULL)
	    break;
    }
    return head;
}

list remove_repeat(list head)  //  remove repeat in sorted list
{
    int i = 1;
    list current = head, fore;
    while (current->next != NULL)
    {
	fore = current->next;
        while (fore != NULL)
        {
            if (current->value == fore->value)
            {
		current->next = fore->next;
                if (fore->next != NULL)
                    fore->next->prev = current;
                fore = fore->next;
            }
	    else
		break;
	}
        current = current->next;
	if (current == NULL)
	    break;
	i++;
    }
    return head;
}

list search_remove(list head)  // removing repeat by element searching
{
    list current = head, fore;
    while (current->next != NULL)
    {
        fore = current->next;
        while (fore != NULL)
        {
            if (current->value == fore->value)
            {
                fore->prev->next = fore->next;
                if (fore->next != NULL)
                    fore->next->prev = fore->prev;
            }
            fore = fore->next;
        }
        current = current->next;
	if (current == NULL)
	    break;
    }

    return head;
}

int main(void)
{
    list rand_list = random_list(NUM), sorted, norepeat, search, current;
    printf("\n%d Random integers:\n\n", NUM);
    print_list(rand_list);
    /* Option 1
        Sort the list by its data field. 
        Remove adjacent elements of the sorted list with the same value.
    */
    sorted = sort_by_bubble(rand_list);
    printf("\nAfter sorted:\n");
    print_list(sorted);

    norepeat = remove_repeat(sorted);
    printf("\nAfter removing:\n");
    print_list(norepeat);

    current = rand_list; // set off space for generated integers
    while (current != NULL)
    {
        rand_list = current->next;
        free(current);
        current = rand_list;

    /*
    Option 2
        Take the first element—search the remainder of the list for elements with the same data and remove them. 
        Then take the second element and do the same
    */
    rand_list = random_list(NUM);
    printf("\n%d Random integers:\n\n", NUM);
    print_list(rand_list);
    
    search = search_remove(rand_list);
    printf("\nOption 2:\n\n");
    print_list(search);

    current = rand_list; // set off space for generated integers
    while (current != NULL)
    {
        rand_list = current->next;
        free(current);
        current = rand_list;
    }
    return 0;
}