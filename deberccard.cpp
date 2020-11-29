#include "deberccard.h"

DebercCard::DebercCard(){}

DebercCard::DebercCard(unsigned int card_value):Card(card_value)
{

}

unsigned int DebercCard::getRankDeberc(unsigned int trumpSuit)
{
    return (this->suit_value == trumpSuit)? numberRank[this->rank_value]: debercRank[this->rank_value];
}

unsigned int DebercCard::getMaxCardDeberc(unsigned int firstCardCode, \
                                           unsigned int secondCardCode, \
                                           unsigned short trumpSuit)
{
    DebercCard firstCard(firstCardCode);
    DebercCard secondCard(secondCardCode);

    int maxCode = firstCardCode;

    //compare suit
    if(firstCard.getSuit() != secondCard.getSuit())
    {
        if((firstCard.getSuit() != trumpSuit)
                &&(secondCard.getSuit() == trumpSuit)) //the second card is a trump card, and the first is not a trump card
        {
            maxCode = secondCardCode;                  // the second card is older - need rewrite

        } else if((firstCard.getSuit() != trumpSuit)
                  &&(secondCard.getSuit() != trumpSuit))             //there is no trump card among cards
        {
            if(firstCard.getRankDeberc(trumpSuit) < secondCard.getRankDeberc(trumpSuit))           //compare ranks
            {
                maxCode = secondCardCode;                            //overwrite older
            }
        }
    }
    else
    {   //if suits are equal, compare ranks
        if(firstCard.getRankDeberc(trumpSuit) < secondCard.getRankDeberc(trumpSuit))               //compare ranks
        {
            maxCode = secondCardCode;                                //overwrite older
        }
    }

    return maxCode;
}

unsigned int DebercCard::getScore(unsigned short trumpSuit)
{
    return (this->suit_value == trumpSuit)? cardPointsTrump[this->rank_value]: cardPoints[this->rank_value];
}
