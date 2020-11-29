#ifndef DEBERCCARD_H
#define DEBERCCARD_H
#include "card.h"


class DebercCard : public Card
{
public:
    DebercCard();
    DebercCard(unsigned int card_value);
    unsigned int getRankDeberc(unsigned int trumpSuit);
    static unsigned int getMaxCardDeberc(unsigned int firstCardCode,\
                                         unsigned int secondCardCode,\
                                         unsigned short trumpSuit);
    unsigned int getScore(unsigned short trumpSuit);

protected:
                                      //2, 3, 4, 5, 6, 7, 8, 9, 10, B,  Д,  К,  Т
    unsigned int numberRank[13]      = {0, 1, 2, 3, 4, 5, 6, 11, 9, 12, 7,  8, 10};
    unsigned int debercRank[13]      = {0, 1, 2, 3, 4, 5, 6, 7, 11,  8, 9, 10, 12};

                                      //2, 3, 4, 5, 6, 7, 8, 9, 10, B,  Д,  К,  Т
    unsigned int cardPoints[13]      = {0, 0, 0, 0, 0, 0, 0, 0, 10, 2,  3,  4,  11};
    unsigned int cardPointsTrump[13] = {0, 0, 0, 0, 0, 0, 0, 14,10, 20, 3,  4,  11};
};

#endif // DEBERCCARD_H
