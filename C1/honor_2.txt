#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXDRAW 7
#define MAXCARDS 52
#define REPEAT 1000000

typedef enum cardtype  // four suits for poker
{
    clubs = 1,
    diamonds,
    hearts,
    spades
} cardtype;

typedef struct card  //  define a card with pips and suits
{
    short pips;
    cardtype suit;
} card;

void print_card(card c)
{
    printf("%d of ", c.pips);
    switch (c.suit)
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

/* 
    define three decks of cards:
        one in order,
        one been shuffled,
        one for 7 cards in hand
*/

card deck[MAXCARDS];
card shuffled[MAXCARDS];
card draw[MAXDRAW];

void origin_cards(void)  //  get a deck of cards in order
{
    int i;
    for (i = 0; i < MAXCARDS; i++)
    {
        deck[i].pips = i / 4 + 1;
        deck[i].suit = (cardtype)(i % 4 + 1);
    }
}

void shuffles(void)  //  shuffle cards randomly
{
    int index[MAXCARDS];
    int i, j, r;
    srand(time(NULL));
    for (i = 0; i < MAXCARDS; i++)
    {
        while (1)
        {
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
    for (i = 0; i < MAXCARDS; i++)
    {
        shuffled[i].pips = deck[index[i]].pips;
        shuffled[i].suit = deck[index[i]].suit;
    }
}

void draw_seven_cards(void)  // randomly draw 7 seven cards from shuffled deck
{
    int i, j, r, index[MAXDRAW];
    for (i = 0; i < MAXDRAW; i++)
    {
        while (1)
        {
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

int pair()  //  return number of pairs in hand
{
    int i, j, count = 0;
    for (i = 0; i < MAXDRAW; i++)
    {
        for (j = i + 1; j < MAXDRAW; j++)
        {
            if (draw[i].pips == draw[j].pips)
            {
                count += 1;
            }
        }
    }
    return count;
}

int three()  //  return number of three of a kind in hand
{
    int i, j, count = 0, found;
    for (i = 0; i < MAXDRAW; i++)
    {
        found = 0;
        for (j = 0; j < MAXDRAW; j++)
        {
            if (draw[i].pips == draw[j].pips)
            {
                found += 1;
            }
        }
        if (found == 3)
        {
            count += 1;
        }
    }
    return (count / 3);
}

int four()  //  return number of four of a kind in hand
{
    int i, j, count = 0, found;
    for (i = 0; i < MAXDRAW; i++)
    {
        found = 0;
        for(j = 0; j < MAXDRAW; j++)
        {
            if (draw[i].pips == draw[j].pips)
            {
                found += 1;
            }
        }
        if (found == 4)
        {
            count += 1;
        }
    }
    return (count / 4);
}

int isNoPair()  //  whether a hand has no pair
{
    return (pair() == 0);
}

int isOnePair()  //  whether a hand has one pair only
{
    return (pair() == 1);
}

int isTwoPair()  //  whether a hand has two pair only
{
    return ((pair() == 2) && (three() == 0));
}

int isThreeOneKind()  //  whether a hand has three of a kind only
{
    return ((pair() == 3) && (three() == 1));
}

int isFourOneKind()  //  whether a hand has four of a hand only
{
    return ((pair() == 6) && (four() == 1));
}

int isFullHouse()  //  whether a hand has full house only
{
    return ((pair() == 4) && (three() == 1));
}

int main(void)
{
    int i, noPair = 0, onePair = 0, twoPair = 0, threeOneKind = 0, fourOneKind = 0, fullHouse = 0;
    ;
    origin_cards();
    shuffles();
    srand(time(NULL));
    for (i = 0; i < REPEAT; i++)
    {
        draw_seven_cards();
        noPair += isNoPair();
        onePair += isOnePair();
        twoPair += isTwoPair();
        threeOneKind += isThreeOneKind();
        fourOneKind += isFourOneKind();
        fullHouse += isFullHouse();
    }
    
    // print probabilities below
    
    printf("\nAfter %d draws:\n", REPEAT);
    printf("\nHand   \t\t  \tProbabilities\n");
    printf("\nNo pair \t  \t%.6lf\n", (noPair * 1.0) / REPEAT);
    printf("\nOne pair \t  \t%.6lf\n", (onePair * 1.0) / REPEAT);
    printf("\nTwo pair \t  \t%.6lf\n", (twoPair * 1.0) / REPEAT);
    printf("\nThree of a kind \t%.6lf\n", (threeOneKind * 1.0) / REPEAT);
    printf("\nFour of a kind \t  \t%.6lf\n", (fourOneKind * 1.0) / REPEAT);
    printf("\nFull house \t  \t%.6lf\n", (fullHouse * 1.0) / REPEAT);
    return 0;
    return 0;
}