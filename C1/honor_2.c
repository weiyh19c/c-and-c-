#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXDRAW 7
#define MAXCARDS 52
#define REPEAT 1000000

typedef enum cardtype
{
    clubs = 1,
    diamonds,
    hearts,
    spades
} cardtype;

typedef struct card
{
    short pips;
    cardtype suit;
} card;

void print_card(card c)
{
    printf("%d of ", c.pips);
    switch(c.suit) 
    {
        case clubs:
            printf("clubs\n");
            break;
        case diamonds:
            printf("diamonds\n");
            break;
        case hearts:
            printf("hearts\n");
            break;
        case spades:
            printf("spades\n");
            break;
        }
}

card deck[MAXCARDS]; 
card shuffled[MAXCARDS];
card draw[MAXDRAW];

void origin_cards(void) {
    int i;
    for (i = 0; i < MAXCARDS; i++) {
        deck[i].pips = i / 4 + 1;
        deck[i].suit = (cardtype)(i % 4 + 1);
    }
}

void shuffles(void) {
    int index[MAXCARDS];
    int i, j, r;
    srand(time(NULL));
    for (i = 0; i < MAXCARDS; i++) 
    {
        while(1) {
            r = rand() % MAXCARDS;
            for (j = 0; j < i; j++) {
                if (index[j] == r)
                    break;
            }
            if (j == i)
	    {
                index[i] = r;
		break;
	    }
        }
    }
    for (i = 0; i < MAXCARDS; i++)
    {
        shuffled[i].pips = deck[index[i]].pips;
        shuffled[i].suit = deck[index[i]].suit;
    }
}

void draw_seven_cards(void)
{
    int i, j, r, index[MAXDRAW];
    for (i = 0; i < MAXDRAW; i++)
    {
        while(1) {
            r = rand() % MAXCARDS;
            for (j = 0; j < i; j++) 
	    {
                if (index[j] == r)
                break;
            }
            if (j == i)
	    {
                index[i] = r;
		break;
	    }
        }
    }
    for (i = 0; i < MAXDRAW; i++)
    {
        draw[i].pips = shuffled[index[i]].pips;
        draw[i].suit = shuffled[index[i]].suit;
    }
}



int isNoPair()
{
    int i = MAXDRAW - 1, j, pair = 0;
    while (i > 0)
    {
        for (j = 0; j < i; j++)
        {
            if (draw[i].pips == draw[j].pips)
            {
                pair += 1;
            }
        }
        i--;
    }
    return (pair == 0);
}

int isOnePair()
{
    int i = MAXDRAW - 1, j, pair = 0;
    while (i > 0)
    {
        for (j = 0; j < i; j++)
        {
            if (draw[i].pips == draw[j].pips)
            {
                pair += 1;
            }
        }
        i--;
    }
    return (pair == 1);
}

int isTwoPairs()
{
    int i = MAXDRAW - 1, j, pair = 0, pip1, pip2;
    while (i > 0)
    {
        for (j = 0; j < i; j++)
        {
            if (draw[i].pips == draw[j].pips)
            {
                pair += 1;
                if (pair == 1)
                {
                    pip1 = draw[i].pips;
                }
                else if(pair == 2)
                {
                    pip2 = draw[i].pips;
                }
		// printf("pair found:\n");
		// print_card(draw[i]);
		// print_card(draw[j]);
            }
        }
        i--;
    }
    return ((pair == 2) && (pip1 != pip2));
}

int isThreeOneKind()
{
    int i, j, result = 0, count;
    for (i = 0; i < MAXDRAW; i++)
    {
        count = 0;
        for (j = 0; j < MAXDRAW; j++)
        {
            if (i != j)
            {
                if (draw[i].pips == draw[j].pips)
                {
                    count += 1;
		    // printf("\nfound same pips\n");
		    // print_card(draw[i]);
		    // print_card(draw[j]);
                }
            }
        }
        if (count == 2)
        {
            result += 1;
	    // printf("\nthree found\n");
        }
	if (result == 3)
	{
	    break;
	}
    }
    return (result == 3);
}

int main(void)
{
    int i, noPair = 0, onePair = 0, twoPair = 0, threeOneKind = 0;
    ;
    origin_cards();
    shuffles();
    srand(time(NULL));
    for (i = 0; i < REPEAT; i++)
    {
        // printf("\ndraw no %d\n", i+1);
        draw_seven_cards();
        noPair += isNoPair();
        onePair += isOnePair();
        twoPair += isTwoPairs();
        threeOneKind += isThreeOneKind();
    }
    printf("\n%.4lf no-pair among %d draws\n", (noPair * 1.0) / REPEAT, REPEAT);
    printf("\n%.4lf one-pair among %d draws\n", (onePair * 1.0) / REPEAT, REPEAT);
    printf("\n%.4lf two-pair among %d draws\n", (twoPair * 1.0) / REPEAT, REPEAT);
    printf("\n%.4lf three-of-a-kind among %d draws\n", (threeOneKind * 1.0) / REPEAT, REPEAT);
    return 0;
}