#include "game.h"
#include "card.h"
#include <iostream>
#include <ctime>
#include <map>



Game::Game(unsigned int num)
{
    for(unsigned int i = 0; i < num; i++)
    {
        players.push_back(Player());
    }
    for(unsigned int i = 0; i < 52; i++)                                  //заполняем колоду картами
    {
        cardDeck.push_back(i);
    }
}

unsigned int Game::pullOut(void)
{
    unsigned int card;

    std::srand(time(0));                                 // автоматическая рандомизация
    unsigned int randNum = 0 + rand() % cardDeck.size();
    card = cardDeck.at(randNum);
    cardDeck.erase(cardDeck.begin()+randNum);

    return card;
}

void Game::initialDistributionOfCards(void)//начальной раздачи карт
{
    for(unsigned int j = 0; j < players.size(); j++)
    {
        for(unsigned int i = 0; i < numberOfCards ; i++)// players[0].cards
        {
            players[j].addCard(pullOut());
        }
    }
}

void Game::printPlayersCard(void)
{
    for(unsigned int j = 0; j < players.size(); j++, std::cout<<std::endl)
    {
        players.at(j).printCards();
    }
}

void Game::setTrumpCard(void)
{
    this->trumpCard = pullOut();            //запаминаем вытянутую карту козырь
    Card trump(this->trumpCard);
    this->trumpSuit = trump.getSuit();      //масть козыря

    for(unsigned int i = 0; i < players.size(); i++)
    {
        players[i].setTrumpSuit(this->trumpSuit);//каждому игроку отправляем масть козыря
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
        if(maxNumberCards < listTerc[j][0]) //сравниваем по количеству карт
        {
            maxNumberCards = listTerc[j][0];
        }
    }

    if(maxNumberCards == 0)
    {
        std::cout<<"Not max card";
        return;
    }

    std::map <unsigned int, unsigned int> tercPlayers;
    for(unsigned int j = 0; j < numberPlayers; j++)
    {
        if(maxNumberCards == listTerc[j][0])
        {
            //listTerc[j][1] = карта, j = номер игрока
            tercPlayers.insert(std::pair<unsigned int, unsigned int>(listTerc[j][1], j));
        }
    }



    auto it = tercPlayers.begin();
    if(tercPlayers.size() > 1)//если максимальных терцев больше 1
    {
        unsigned int winnerCard = it->first;

        for (++it; it != tercPlayers.end(); ++it)
        {
          winnerCard = Card::getMaxCard(it->first, winnerCard, this->trumpSuit);//ищим наибольшую карту
        }

        it = tercPlayers.find(winnerCard);//ищим игрока по карте
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
        for(unsigned int i = 0; i < numberOfCards; i++)
        {
            players[j].addCard(cards[j][i]);
        }
    }

    for(unsigned int i = 0; i < players.size(); i++)
    {
        players[i].setTrumpSuit(this->trumpSuit);//каждому игроку отправляем масть козыря
    }
}

std::map <std::string, unsigned int> Game::buildCombinationScoreRow(unsigned int numberCard, unsigned int card)//подсчет очков
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
