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
    void setSrategy(std::string str);
    static std::string availableStrategy[3];
    static std::string defaultStrategy;
    void printStrategy(void);
    unsigned int getRandomCard(void);
    unsigned int getMaxCard(void);
    unsigned int getMinCard(void);
    unsigned int getFirstStepCard(void);

protected:
    std::vector <unsigned int> cards;
    unsigned int trumpSuit;
    std::map <std::string, unsigned int> score;
    std::string strategy;

};

#endif // PLAYER_H
