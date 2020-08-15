#include "player.h"
#include "game.h"


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
