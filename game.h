#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"


class Game
{
public:
    Game(unsigned int num);

    unsigned int pullOut(void);
    void initialDistributionOfCards(void);
    void printPlayersCard(void);
    void setTrumpCard(void);
    void findMaxTerz(void);
    void testSetCards(unsigned int cards[4][8], unsigned short suit);
    std::map <std::string, unsigned int> buildCombinationScoreRow(unsigned int numberCard, unsigned int card);
    void printScores(void);
    void findBella(void);
    void printTrumpCard(void);
    void printCards(void);

    std::map <unsigned int, std::string>  kindCombinations = {{3,    "Tierce"},
                                                            {4,    "Deberts"},
                                                            {2,    "Bella"}};

    static std::map <unsigned int, unsigned int> numberPoints;

    std::vector <Player> players;

protected:

    std::vector <unsigned int> cardDeck;

    unsigned int numberOfCards = 8;
    unsigned int trumpCard;
    unsigned short trumpSuit;

};

#endif // GAME_H
