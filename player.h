#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "card.h"


class Player
{
public:
    Player();

    void printCardsNumbers(void);
    void addCard(unsigned int numberOfCard);
    void combinationSearch(unsigned int *tertsAnsver);
    void setTrumpSuit(unsigned int suit);
    void setScore(std::map <std::string, unsigned int> score);
    void printScore(void);
    void findBella(void);
    void printCards(void);
    //player move

protected:
    std::vector <unsigned int> cards;
    unsigned int trumpSuit;
    std::map <std::string, unsigned int> score;
};

#endif // PLAYER_H
