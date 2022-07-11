#include <stdio.h>
#include <stdlib.h>

double average(int size, int array[])  // calculate average of array
{
    double avr = 0.0;
    int i;
    for (i = 0; i < size; i++)
        avr += *(array + i);
    return (avr / size);
}

int maximum(int size, int array[])  // get maximum of array
{
    int max = array[0], i;
    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

void print_array(int size, int array[])  // print array by row of 10 
{
    int i;
    printf("\nThere are %d integers:\n", size);
    for (i = 0; i < size; i++)
    {
        printf("%d\t", array[i]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n");
}

int main()
{
    FILE *in, *out;
    int count = 0, i;
    double *pavr;
    int *pmax;

    in = fopen("integers.txt", "r+");  // read input file
    out = fopen("answer-hw3.txt", "w+");  // open output file

    if (fscanf(in, "%d", &count) != 1)
    {
        fprintf(stderr, "Error by integers");
        exit(EXIT_FAILURE);
    }

    int data[count];
    for (i = 0; i < count; i++)
        fscanf(in, "%d", &data[i]);  // put integers into array

    rewind(in);
    int c;
    while ((c = getc(in)) != EOF)
        putc(c, out);
    fclose(in);

    double avr = average(count, data);
    int max = maximum(count, data);
    pavr = &avr;
    pmax = &max;

    putc('\n', out);

    print_array(count, data);  // print results
    fprintf(stdout, "\nAverage of the array = %.2lf\n", average(count, data));
    fprintf(out, "%.2lf\n", average(count, data));
    fprintf(stdout, "Maximum of the array = %d\n\n", maximum(count, data));
    fprintf(out, "%d\n", maximum(count, data));

    printf("\nHere's what's in the out file:\n");
    rewind(out);
    while ((c = getc(out)) != EOF)
        putc(c, stdout);
    fclose(out);
    return 0;
}