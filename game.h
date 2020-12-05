#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "carddeck.h"


class Game
{
public:
    Game(unsigned int num);

    void checkCountOfPlayers(unsigned int num);
    unsigned int pullOut(void);
    void additionalDistributionOfCards(void);
    void initialDistributionOfCards(void);
    void setTrumpCard(void);
    unsigned int getTrumpCard(void);
    void printTrumpCard(void);
    void findMaxTerz(void);
    void testSetCards(unsigned int cards[4][8], unsigned short suit);
    std::map <std::string, unsigned int> buildCombinationScoreRow(unsigned int numberCard, unsigned int card);
    void printScores(void);
    void findBella(void);
    void printCards(void);
    void play(void);
    void searchForWinner(void);

    std::map <unsigned int, std::string>  kindCombinations = {{3,    "Tierce"},
                                                              {4,    "Deberts"},
                                                              {2,    "Bella"}};

    static std::map <unsigned int, unsigned int> numberPoints;

    std::vector <Player> players;
    void setPlayersStrategy(std::vector <std::string> playersStrategies);
    void printPlayersStrategy(void);
    void printBribe(void);
    std::vector <unsigned int> battlefield;
    unsigned int lastWinnerIndex;
    void doScoring(void);
    void runOne(void);


protected:

    cardDeck desk;
    unsigned int minRank = 5;
    unsigned int numberOfCards = 6;
    unsigned int trumpCard;
    unsigned short trumpSuit;
    unsigned int  maxDeckSize = 52;

};

#endif // GAME_H
