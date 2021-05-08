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

    static std::map <unsigned int, std::string>  kindCombinations;
    static std::map <unsigned int, unsigned int> numberPoints;

    std::vector <Player> players;
    void setPlayersStrategy(std::vector <std::string> playersStrategies);
    void printPlayersStrategy(void);
    void printBribe(void);
    std::vector <unsigned int> battlefield;
    unsigned int lastWinnerIndex;
    void doScoring(void);
    void runOne(void);
    void runMultiple(void);
    void reset(void);
    int getFinalPlayer(void);


protected:

    cardDeck desk;
    static const unsigned int minRank = 5;
    static const unsigned int numberOfCards = 8;
    unsigned int trumpCard;
    unsigned short trumpSuit;
    static const unsigned int  maxDeckSize = 52;
    std::vector <unsigned int> playersScore;
    static const unsigned int  finalScoreValue = 200;

};

#endif // GAME_H
