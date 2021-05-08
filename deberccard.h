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

    static unsigned int numberRank[13];
    static unsigned int debercRank[13];
    static unsigned int cardPoints[13];
    static unsigned int cardPointsTrump[13];

protected:

};

#endif // DEBERCCARD_H
