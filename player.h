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
    void findBella(void);
    void printCards(void);
    void setSrategy(std::string str);
    static std::string availableStrategy[3];
    static std::string defaultStrategy;
    void printStrategy(void);
    void cardDeletion(unsigned int card);
    unsigned int getRandomCard(std::vector <unsigned int> availableCards);
    unsigned int getMaxCard(std::vector <unsigned int> availableCards);
    unsigned int getMinCard(std::vector <unsigned int> availableCards);
    unsigned int putStepCard(bool isFirstStep = false, unsigned int stepSuit = 0);
    std::vector <unsigned int> getValidCardsForStep(unsigned int previousCard);
    void setCardBribe(std::vector <unsigned int> card);
    void printBribe(void);
    void doScoring(void);
    unsigned int getTotalScore(void);
    void clearBribes(void);
    void clearScore(void);


protected:
    std::vector <unsigned int> cards;
    std::vector < std::vector <unsigned int>> bribes;
    unsigned int trumpSuit;
    std::map <std::string, unsigned int> score;
    std::string strategy;
    unsigned int numberPoints;
};

#endif // PLAYER_H
