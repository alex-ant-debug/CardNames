#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card
{
public:
    Card();
    Card(unsigned int card_value);

    void print(void);
    void shortPrint(void);
    unsigned int getSuit(void);
    unsigned int getRank(void);
    static unsigned int getMaxCard(unsigned int firstCardCode, unsigned int secondCardCode, unsigned short trumpSuit);
    std::string getShortView(void);
    std::string getRankValue(void);

    static std::string ranks[13];
    static std::string imageSuits[4];


protected:

    static const unsigned int maxValue = 51;
    unsigned int suit_value;
    unsigned int rank_value;
    static std::string suits[4];

};

#endif // CARD_H
