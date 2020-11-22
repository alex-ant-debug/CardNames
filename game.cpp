#include "game.h"
#include "card.h"
#include "carddeck.h"
#include <iostream>
#include <ctime>
#include <map>


void Game::checkCountOfPlayers(unsigned int num)
{
    unsigned int possibleNumberOfPlayers = (maxDeckSize - minRank*4)/numberOfCards;
    std::string str;
    if(possibleNumberOfPlayers < num)
    {
        str = std::to_string(possibleNumberOfPlayers);
        throw "Too many players in game. Available count is " + str;
    }

    if(num < 2)
    {
        str = "Count players can not be less than two.";
        throw str;
    }
}

Game::Game(unsigned int num)
{
    checkCountOfPlayers(num);

    desk = cardDeck(minRank);

    for(unsigned int i = 0; i < num; i++)
    {
        players.push_back(Player());
    }
}

unsigned int Game::pullOut(void)
{
    return desk.pullOut();
}

void Game::initialDistributionOfCards(void)
{
    for(unsigned int j = 0; j < players.size(); j++)
    {
        for(unsigned int i = 0; i < numberOfCards ; i++)
        {
            unsigned int card = pullOut();
            if(card == 100)
            {
                break;
            }
            players[j].addCard(card);
        }
    }
}

void Game::additionalDistributionOfCards(void)
{
    for(unsigned int j = 0; j < players.size(); j++)
    {
        for(unsigned int i = 0; i < 2 ; i++)
        {
            unsigned int card = pullOut();
            if(card != 100)
            {
                players[j].addCard(card);
            }
            else
            {
                players[j].addCard(this->trumpCard);
                break;
            }
        }
    }
}

void Game::setTrumpCard(void)
{
    this->trumpCard = pullOut();
    Card trump(this->trumpCard);
    this->trumpSuit = trump.getSuit();

    for(unsigned int i = 0; i < players.size(); i++)
    {
        players[i].setTrumpSuit(this->trumpSuit);
    }
}


void Game::findMaxTerz(void)
{
    unsigned int numberPlayers = players.size();
    unsigned int listTerc[numberPlayers][2];
    for(unsigned int j = 0; j < numberPlayers; j++)
    {
        players.at(j).combinationSearch(listTerc[j]);
    }

    unsigned int maxNumberCards = 0;

    for(unsigned int j = 0; j < numberPlayers; j++)
    {
        if(maxNumberCards < listTerc[j][0])
        {
            maxNumberCards = listTerc[j][0];
        }
    }

    if(maxNumberCards == 0)
    {
        return;
    }

    std::map <unsigned int, unsigned int> tercPlayers;
    for(unsigned int j = 0; j < numberPlayers; j++)
    {
        if(maxNumberCards == listTerc[j][0])
        {
            //listTerc[j][1] = cards, j = player number
            tercPlayers.insert(std::pair<unsigned int, unsigned int>(listTerc[j][1], j));
        }
    }



    auto it = tercPlayers.begin();
    if(tercPlayers.size() > 1)//if max terc more then 1
    {
        unsigned int winnerCard = it->first;

        for (++it; it != tercPlayers.end(); ++it)
        {
          winnerCard = Card::getMaxCard(it->first, winnerCard, this->trumpSuit);//search the greatest card
        }

        it = tercPlayers.find(winnerCard);//search player's index on the map of players terc
    }

    if(it != tercPlayers.end())
    {
        players[it->second].setScore(buildCombinationScoreRow(maxNumberCards, it->first));
    }
}

void Game::findBella(void)
{
    unsigned int numberPlayers = players.size();
    for(unsigned int j = 0; j < numberPlayers; j++)
    {
        players.at(j).findBella();
    }
}

void Game::testSetCards(unsigned int cards[4][8], unsigned short trumpCard)
{
    this->trumpCard = trumpCard;
    this->trumpSuit = Card(trumpCard).getSuit();

    for(unsigned int j = 0; j < players.size(); j++)
    {
        for(unsigned int i = 0; i < 8; i++)
        {
            players[j].addCard(cards[j][i]);
        }
    }

    for(unsigned int i = 0; i < players.size(); i++)
    {
        players[i].setTrumpSuit(this->trumpSuit);//send each player a suit of trump
    }
}

std::map <std::string, unsigned int> Game::buildCombinationScoreRow(unsigned int numberCard, unsigned int card)//scoring
{
    std::map <std::string, unsigned int> score;
    std::string strNumberCard = std::to_string(numberCard);
    std::string str = (kindCombinations.count(numberCard) > 0)? kindCombinations[numberCard]: "combination"+strNumberCard;
    unsigned int points = (numberPoints.count(numberCard) > 0)? numberPoints[numberCard]: 0;
    score.insert(std::pair<std::string, unsigned int>(str, points));

    return score;
}

void Game::printScores(void)
{
    for(unsigned int j = 0; j < players.size(); j++, std::cout<<std::endl)
    {
        std::cout<<"Player "<<j+1<<std::endl;
        std::cout<<"--------"<<std::endl;
        players[j].printScore();
    }
}

std::map <unsigned int, unsigned int>  Game::numberPoints = {{3,    20},
                                                            {4,    50},
                                                            {2,    30}};

void Game::printTrumpCard(void)
{
    std::cout<<"Trunp card = ";
    Card(this->trumpCard).print();
    std::cout<<std::endl;
}

void Game::printCards(void)
{
    for(unsigned int j = 0; j < players.size(); j++, std::cout<<std::endl)
    {
        players[j].printCards();
    }
}

void Game::setPlayersStrategy(std::vector <std::string> playersStrategies)
{
    for(unsigned int j = 0; j < players.size(); j++)
    {
        players[j].setSrategy(playersStrategies.at(j));
    }
}

void Game::printPlayersStratagy(void)
{
    for(unsigned int j = 0; j < players.size(); j++, std::cout<<"\t")
    {
        players[j].printStrategy();
    }
}

unsigned int Game::getTrumpCard(void)
{
    return this->trumpCard;
}

void Game::play(void)
{
    lastWinnerIndex = 0;
    std::vector <unsigned int> singleCycleWinners;

    for(unsigned int j = 0; j < numberOfCards; j++)
    {
        battlefield.resize(players.size());

        for(unsigned int i = lastWinnerIndex, count = 0; count < players.size(); count++)
        {
            unsigned int suitFirstCard;
            if(i == lastWinnerIndex)
            {
                unsigned int firstCard = players[i].putStepCard(true);
                battlefield[i] = (firstCard);
                suitFirstCard = Card(firstCard).getSuit();
            }
            else
            {
                battlefield[i] = (players[i].putStepCard(false, suitFirstCard));
            }
            Card(battlefield[i]).print();
            std::cout<<" = "<<i+1<<"\t";

            i = (i != (players.size()-1))? ++i: 0;
        }

        searchForWinner();
        players[lastWinnerIndex].setCardBribe(battlefield);
        battlefield.clear();
        std::cout<<"Winer = "<<lastWinnerIndex+1<<std::endl;

        singleCycleWinners.push_back(lastWinnerIndex);
    }
}

void Game::searchForWinner(void)
{
    unsigned int winnerCard = battlefield.at(0);//first step
    unsigned int winnerIndex = 0;

    for(unsigned int i = 1; i < battlefield.size(); i++)
    {

        if((Card(battlefield.at(i)).getSuit() == Card(battlefield.at(lastWinnerIndex)).getSuit())//compare with the suit of first step
                ||(Card(battlefield.at(i)).getSuit() == this->trumpSuit))//compare with the suit of the trump
        {
            winnerCard = Card::getMaxCard(battlefield.at(i), winnerCard, this->trumpSuit);//search the greatest card
            if(battlefield.at(i) == winnerCard)
            {
                winnerIndex =  i;//store the number of the player who won
            }
        }
    }

    lastWinnerIndex = winnerIndex; //number of the player
}

void Game::printBribe(void)
{
    for(unsigned int i = 0; i < players.size(); i++)
    {
        std::cout<<"Player "<<(i+1)<<" =\t";
        players[i].printBribe();
    }
}

void Game::doScoring(void)
{
    for(unsigned int i = 0; i < players.size(); i++)
    {
        players[i].doScoring();
    }
}
