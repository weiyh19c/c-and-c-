#include <stdio.h>
#define FEB 28
#define MAX 31
#define MIN 30

typedef enum month // define 12 months
{
    jan = 1,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
} month;

enum month new_month(enum month m, int next) // calculate the next month
{
    if (next == 0)
        return m;
    else 
        return (month)((m + next) % 12);
}; 

typedef struct date
{
    month m;
    int d;
} date;

struct date nextday(struct date today)  // calculate the next day
{
    struct date next_day;
    int turn_to_next_month = 0;  // next month if needed 

    switch (today.m)
    {
    case (jan):
    case (mar):
    case (may):
    case (jul):
    case (aug):
    case (oct):
    case (dec):
        next_day.d = (today.d + 1) % MAX;
        turn_to_next_month =  today.d / MAX;  // for months with 31 days
        break;
    case (apr):
    case (jun):
    case (sep):
    case (nov):
        next_day.d = (today.d + 1) % MIN;
        turn_to_next_month = today.d / MIN;  // for months with 30 days
        break;
    case (feb):
        next_day.d = (today.d + 1) % FEB;
        turn_to_next_month = today.d / FEB;  // for feb with 28 days
        break;
    }
    next_day.m = new_month(today.m, turn_to_next_month);
    return next_day;
};

void printdate(struct date one_date) {
    switch(one_date.m){
        case (jan): 
            printf(" January ");
            break;
        case (feb): 
            printf(" February ");
            break;
        case (mar): 
            printf(" March ");
            break;
        case (apr): 
            printf(" April ");
            break;
        case (may): 
            printf(" May ");
            break;
        case (jun): 
            printf(" June ");
            break;
        case (jul): 
            printf(" July ");
            break;
        case (aug): 
            printf(" August ");
            break;
        case (sep): 
            printf(" September ");
            break;
        case (oct): 
            printf(" October ");
            break;
        case (nov): 
            printf(" November ");
            break;
        case (dec): 
            printf(" December ");
            break;
    }
    printf("%d\n", one_date.d); 
}

int main() {
    struct date d1, d2, d3, d4;
    d1 = {feb, 28};
    d2 = {mar, 15};
    d3 = {oct, 31};
    d4 = {dec, 31};

    printf("If today is");
    printdate(d1);
    printf("   Tomorrow is");
    printdate(nextday(d1));

    printf("\nIf today is");
    printdate(d2);
    printf("   Tomorrow is");
    printdate(nextday(d2));

    printf("\nIf today is");
    printdate(d3);
    printf("   Tomorrow is");
    printdate(nextday(d3));

    printf("\n If today is");
    printdate(d4);
    printf("   Tomorrow is");
    printdate(nextday(d4));

    return 0;
}