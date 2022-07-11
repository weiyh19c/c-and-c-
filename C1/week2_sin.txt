#include <stdio.h> 
#include <math.h>
#define PI 3.1415926
int main(void)
{
    double angle;
    printf("Please enter an angle between 0 and 90, inclusively: ");  // get an angle between 0 and 90
    scanf("%lf", &angle);
    printf("\nsin(%lf) = %lf\n", angle, sin(angle * PI / 180)); // print out the result
    return 0;
}