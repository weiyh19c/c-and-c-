#include <stdio.h>
#define MAX 1010

double average(int[], int);

double average(int weight[], int num)
{
    int sum = 0;
    for (int i = 0; i < num; i++)
        sum += weight[i];
    return (sum * 1.0 / num);
}


int main()
{
    static int weight[MAX];
    int count = 0;
    FILE *fp;
    fp = fopen("elephant_seal_data.txt", "r");
    while(fscanf(fp, "%4d", &weight[count]) != EOF)
        count++;
    fclose(fp);
    double avg = average(weight, count);
    printf("Average weight of %d elephant seals is %.2lf", count, avg);
    return 0;
}