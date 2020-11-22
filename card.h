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
    unsigned int getScore(unsigned short trumpSuit);
    std::string getRankValue(void);

    std::string ranks[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    std::string imageSuits[4] = {"\x05", "\x06", "\x04", "\x03"};

    //2, 3, 4, 5, 6, 7, 8, 9, 10, B,  Д,  К,  Т
    unsigned int cardPoints[13]      = {0, 0, 0, 0, 0, 0, 0, 0, 10, 2,  3,  4,  11};
    unsigned int cardPointsTrump[13] = {0, 0, 0, 0, 0, 0, 0, 14,10, 20, 3,  4,  11};


protected:

    unsigned int maxValue = 51;
    unsigned int suit_value;
    unsigned int rank_value;
    std::string suits[4] = {"Clubs", "Spades", "Diamonds", "Hearts"};

};

#endif // CARD_H
