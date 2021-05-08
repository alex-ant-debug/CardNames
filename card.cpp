#include "card.h"

const std::string Card::ranks [] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
const std::string Card::imageSuits[] = {"\x05", "\x06", "\x04", "\x03"};
const std::string Card::suits[] = {"Clubs", "Spades", "Diamonds", "Hearts"};

Card::Card(){}

Card::Card(unsigned int card_value)
{
    if(card_value > maxValue)
    {
     std::string str = std::to_string(maxValue);
     throw  "Card value greater than maximum value. Maximum value is " + str;
    }
    this->suit_value = card_value / 13;
    this->rank_value = card_value % 13;
}

void Card::print(void)
{
    shortPrint();
}

std::string Card::getRankValue(void)
{
    return (this->rank_value < 9)? ranks[this->rank_value]: std::string(1, ranks[this->rank_value][0]);
}


void Card::shortPrint(void)
{
    std::cout<<imageSuits[this->suit_value]<<getRankValue()<<"  ";
}

std::string Card::getShortView(void)
{
    return imageSuits[this->suit_value]+getRankValue();
}

unsigned int  Card::getSuit(void)
{
    return this->suit_value;
}

unsigned int  Card::getRank(void)
{
    return this->rank_value;
}

// compare two card and return max of them
unsigned int Card::getMaxCard(unsigned int firstCardCode, unsigned int secondCardCode, unsigned short trumpSuit)
{
    Card firstCard(firstCardCode);
    Card secondCard(secondCardCode);

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
            if(firstCard.getRank() < secondCard.getRank())           //compare ranks
            {
                maxCode = secondCardCode;                            //overwrite older
            }
        }
    }
    else
    {   //if suits are equal, compare ranks
        if(firstCard.getRank() < secondCard.getRank())               //compare ranks
        {
            maxCode = secondCardCode;                                //overwrite older
        }
    }

    return maxCode;
}
