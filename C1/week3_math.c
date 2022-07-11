#include <stdio.h>
#include <math.h>
#define PI 3.1415926
int main(void)
{
    double degree;
    printf("Please enter a degree between 0 and 90: \n");
    scanf("%lf", &degree);
    printf("Degree  =  %lf\n", degree);
    printf("Sine    =  %lf\n", sin(degree * PI / 180));
    printf("Cosine  =  %lf\n", cos(degree * PI / 180));
    return 0;
}