#include "player.h"
#include "game.h"
#include <ctime>
#include <algorithm>


Player::Player()
{

}

void Player::addCard(unsigned int numberOfCard)
{
    cards.push_back(numberOfCard);
}


void Player::printCardsNumbers(void)
{

    for(unsigned int i = 0; i < cards.size(); i++)
    {
        std::cout<<cards.at(i)<<" ";
    }
}

void Player::combinationSearch(unsigned int *tertsAnsver)
{
    if(cards.empty())
    {
        *(tertsAnsver) = 0;
        *(tertsAnsver+1) = 0;
        return;
    }

    unsigned int suit, suitNext, rung, rungNext, count = 1;
    unsigned int numberOfCards = cards.size();
    std::map<unsigned int, unsigned int> terts;
    std::sort(cards.begin(), cards.end());

    for(unsigned int i = 0; i < numberOfCards; i++)
    {
        Card card(cards[i]);
        Card nextCard((i<numberOfCards-1)? cards[i+1] : 0);

        suit = card.getSuit();
        suitNext = nextCard.getSuit();
        rung = card.getRank();
        rungNext = nextCard.getRank();

        if((suit == suitNext)&&(rung == (rungNext - 1)))//если масть одна и ранг больше на 1
        {
            count++;
        }
        else
        {
            if(count >= 3)
            {
                std::map<unsigned int, unsigned int>::iterator  it = terts.find(count);
                if(it != terts.end())
                {
                    terts[count] = Card::getMaxCard(cards.at(i), terts[count], this->trumpSuit);
                }
                else
                {
                    terts.insert(std::pair<unsigned int, unsigned int>(count, cards.at(i)));
                }

            }
            count = 1;
        }
    }

    if(terts.empty())
    {
        *(tertsAnsver) = 0;
        *(tertsAnsver+1) = 0;
        return;
    }
    auto it = terts.begin();
    std::advance(it, terts.size()-1);

    *(tertsAnsver) = it->first;
    *(tertsAnsver+1) = it->second;
}

void Player::setTrumpSuit(unsigned int suit)
{
    this->trumpSuit = suit;
}

void Player::setScore(std::map <std::string, unsigned int> score)
{
    auto it = score.begin();
    this->score.insert(std::pair<std::string, unsigned int>(it->first, it->second));
}

void Player::printScore(void)
{
    if(!this->score.empty())
    {
        for(auto it = this->score.begin(); it != this->score.end(); it++)
        {
            std::cout<<it->first<<"\t\t";
            std::cout<<it->second<<std::endl;
        }
    }
    else
    {
        std::cout<<"None\t\t";
        std::cout<<0<<std::endl;
    }
}

void Player::findBella(void)
{
    if(cards.empty())
    {
        return;
    }
    unsigned int numberCards = cards.size();

    unsigned int count = 0, suit, rung;

    for(unsigned int i = 0; i < numberCards; i++)
    {
        Card card(cards.at(i));
        suit = card.getSuit();
        rung = card.getRank();

        if(suit == trumpSuit && (rung == 10 || rung == 11))//нашли даму
        {
           count++;
        }
    }

    if(count == 2)//нашли короля
    {
        std::map <std::string, unsigned int> scoreBella;
        scoreBella["Bella"] = Game::numberPoints[2];
        setScore(scoreBella);
    }
}

void Player::printCards(void)
{
    unsigned int numberCards = cards.size();
    for(unsigned int i = 0; i < numberCards; i++)
    {
        Card(cards.at(i)).print();
    }
}

std::string Player::availableStrategy[3] = {"min", "max", "random"};
std::string Player::defaultStrategy = "min";

void Player::setSrategy(std::string strategy)
{
    for(unsigned int i = 0; i < sizeof(availableStrategy)/sizeof(std::string); i++)
    {
        if(Player::availableStrategy[i] == strategy)
        {
            this->strategy = strategy;
            break;
        }
    }
    if(this->strategy == "")
    {
        this->strategy = defaultStrategy;
    }
}

void Player::printStrategy(void)
{
    std::cout<<this->strategy;
}

unsigned int Player::getRandomCard(void)
{
    srand(time(0));
    auto cardIndex = 0 + rand() % (cards.size()-1);
    unsigned int cardNumber = cards.at(cardIndex);
    cards.erase(cards.begin() + cardIndex);
    return cardNumber;
}

unsigned int Player::getMaxCard(void)
{
    unsigned int numberCards = cards.size();
    unsigned int max = cards.at(0);

    for(unsigned int i = 1; i < numberCards; i++)
    {
        max = Card::getMaxCard(max, cards.at(i), this->trumpSuit);
    }
    std::vector<unsigned int>::iterator it = std::find(cards.begin(), cards.end(), max);
    std::vector<unsigned int>::difference_type index = std::distance(cards.begin(), it);
    cards.erase(cards.begin() + index);
    return max;
}

unsigned int Player::getMinCard(void)
{
    unsigned int numberCards = cards.size();
    unsigned int min = cards.at(0);

    for(unsigned int i = 1; i < numberCards; i++)
    {
        min = (Card::getMaxCard(min, cards.at(i), this->trumpSuit) == min)? cards.at(i):  min;
    }
    std::vector<unsigned int>::iterator it = std::find(cards.begin(), cards.end(), min);
    std::vector<unsigned int>::difference_type index = std::distance(cards.begin(), it);
    cards.erase(cards.begin() + index);
    return min;
}

unsigned int Player::putFirstStepCard(void)
{
    std::string strategyPlayer[3] = {"min", "max", "random"};
    unsigned int i;
    unsigned int card;

    for(i = 0; i < 3; i++)
    {
        if(strategyPlayer[i] == this->strategy)
        {
            break;
        }
    }

    switch (i)
    {
    case 0:  {card  = getMinCard();      } break;
    case 1:  {card  = getMaxCard();      } break;
    case 2:  {card  = getRandomCard();   } break;
    default: break;
    }
    return card;
}

unsigned int Player::nextStepCard(unsigned int previousCard)
{
    Card opponentPreviousCard(previousCard);
    unsigned int suitPreviousCard = opponentPreviousCard.getSuit();
    unsigned int numberCards = cards.size();
    unsigned int minCard;
    bool flagThereIsSuchSuit = false;       //флаг есть такая масть
    bool flagIsMinimumTrumpCard = false;    //флаг есть минимальный козырь

    for(unsigned int i = 0; i < numberCards; i++)
    {
        Card myCards(cards.at(i));
        if(myCards.getSuit() == suitPreviousCard)   //ищем масть как у предыдущей карты
        {
            //если есть такая масть ищем минимальную карту
            flagThereIsSuchSuit = true;
            if(i != 0)
            {
                minCard = (minCard > cards.at(i))? minCard: cards.at(i);//(Card::getMaxCard(minCard, cards.at(i), this->trumpSuit) == minCard)? cards.at(i):  minCard;
            }
            else
            {
                minCard = cards.at(0);
            }
        }
    }

    if(flagThereIsSuchSuit)//есть ли у нас карты с такой мастью
    {
        //если есть выдаем наименьшую карту
        return minCard;
    }
    else
    {
        //если нету ходим наименьшим козырем, если у нас есть козырь
        unsigned int minTrumpCard;
        for(unsigned int i = 0; i < numberCards; i++)
        {
            Card myTrumpCards(cards.at(i));
            if(myTrumpCards.getSuit() == trumpSuit)   //сравниваем масти моих карт с козырем
            {
                //если есть козырь ищем минимальную козырную карту
                flagIsMinimumTrumpCard = true;
                if(i > 0)
                {
                    minTrumpCard = (minTrumpCard > cards.at(i))? minTrumpCard: cards.at(i);//(Card::getMaxCard(minTrumpCard, cards.at(i), this->trumpSuit) == minTrumpCard)? cards.at(i):  minTrumpCard;
                }
                else
                {
                    minTrumpCard = cards.at(i);
                }
            }
        }

        if(flagIsMinimumTrumpCard)
        {
            //возвращаем минимальный козырь
            return minTrumpCard;
        }
        else
        {
            //если козыря нету возвращаем любую минимальную карту
            return getMinCard();
        }
    }
}


std::vector <unsigned int> Player::getValidCardsForStep(unsigned int previousCard)
{
    std::vector <unsigned int> arrayValidCards;
    unsigned int suitPreviousCard = Card(previousCard).getSuit();
    unsigned int numberCards = cards.size();

    for(unsigned int i = 0; i < numberCards; i++)//перебераем карты
    {
        if(Card(cards.at(i)).getSuit() == suitPreviousCard)   //есть карты с мастью хода?
        {
            //если есть такая масть записваем карту
            arrayValidCards.push_back(cards.at(i));
        }
    }

    if(!arrayValidCards.empty())
    {
        return arrayValidCards;//возвращаем все карты с мастью хода
    }
    else
    {
        if(suitPreviousCard == trumpSuit)//масть хода равна масти козыря?
        {
            //да равна, возвращаем все карты
            return cards;
        }
        else
        {
            //нет
            for(unsigned int i = 0; i < numberCards; i++)
            {
                if(Card(cards.at(i)).getSuit() == trumpSuit)   //сравниваем масти моих карт с козырем
                {
                    //если есть козырь записваем козырную карту
                    arrayValidCards.push_back(cards.at(i));
                }
            }
            return (!arrayValidCards.empty())?  arrayValidCards:  cards;
        }
    }
}
