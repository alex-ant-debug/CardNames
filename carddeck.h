#ifndef CARDDECK_H
#define CARDDECK_H

#include <vector>
#include <iostream>
#include <ctime>

class cardDeck
{
public:
    cardDeck();
    cardDeck(unsigned int minRank);
    unsigned int pullOut(void);
    void print(void);

protected:
    std::vector <unsigned int> cards;
    unsigned int minRank;

};

#endif // CARDDECK_H
