#include "player.h"
#include "game.h"
#include "card.h"
#include "deberccard.h"
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

        if((suit == suitNext)&&(rung == (rungNext - 1)))//if suits are same and rank more by 1
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
    if(it->second > 0)
    {
        this->score.insert(std::pair<std::string, unsigned int>(it->first, it->second));
    }
}

unsigned int Player::getTotalScore(void)
{
    unsigned int totalScore = 0;
    for(auto it = this->score.begin(); it != this->score.end(); it++)
    {
        totalScore += it->second;
    }

    return totalScore;
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

        if(suit == trumpSuit && (rung == 10 || rung == 11))//found a lady
        {
           count++;
        }
    }

    if(count == 2)//found the king
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

void Player::cardDeletion(unsigned int card)
{
    std::vector<unsigned int>::iterator it = std::find(cards.begin(), cards.end(), card);
    std::vector<unsigned int>::difference_type index = std::distance(cards.begin(), it);
    cards.erase(cards.begin() + index);
}

unsigned int Player::getRandomCard(std::vector <unsigned int> availableCards)
{
    availableCards = (availableCards.empty())? cards: availableCards;
    unsigned int numberCards = availableCards.size();
    unsigned int randomCard;

    if(numberCards != 1)
    {
        srand(time(0));
        auto cardIndex = 0 + rand() % (numberCards-1);
        randomCard = availableCards.at(cardIndex);
    }
    else
    {
        randomCard = availableCards.at(0);
    }

    cardDeletion(randomCard);
    return randomCard;
}

unsigned int Player::getMaxCard(std::vector <unsigned int> availableCards)
{
    availableCards = (availableCards.empty())? cards: availableCards;
    unsigned int numberCards = availableCards.size();
    unsigned int max = availableCards.at(0);

    for(unsigned int i = 1; i < numberCards; i++)
    {
        max = Card::getMaxCard(max, availableCards.at(i), this->trumpSuit);
    }

    cardDeletion(max);
    return max;
}

unsigned int Player::getMinCard(std::vector <unsigned int> availableCards)
{
    availableCards = (availableCards.empty())? cards: availableCards;
    unsigned int numberCards = availableCards.size();
    unsigned int min = availableCards.at(0);

    for(unsigned int i = 1; i < numberCards; i++)
    {
        min = (Card::getMaxCard(min, availableCards.at(i), this->trumpSuit) == min)? availableCards.at(i):  min;
    }

    cardDeletion(min);
    return min;
}


// тестировать первый шаг
unsigned int Player::putStepCard(bool isFirstStep, unsigned int stepSuit)
{
    unsigned int i;
    unsigned int card;
    std::vector <unsigned int> validCards;
    std::string str = {"Player do not have any card"};

    if(cards.empty())
    {
        throw str;
    }

    if(cards.size() == 1)
    {
        card = cards.at(0);
        cards.clear();
        return card;
    }

    if(!isFirstStep)
    {
        validCards = getValidCardsForStep(stepSuit);
    }


    if(validCards.size() == 1)
    {
        card = validCards.at(0);
        cardDeletion(card);
        return card;
    }

    for(i = 0; i < 3; i++)
    {
        if(availableStrategy[i] == this->strategy)
        {
            break;
        }
    }

    switch (i)
    {
        case 0:  {card  = getMinCard(validCards);      } break;
        case 1:  {card  = getMaxCard(validCards);      } break;
        case 2:  {card  = getRandomCard(validCards);   } break;
        default: break;
    }

    return card;
}


std::vector <unsigned int> Player::getValidCardsForStep(unsigned int stepSuit)
{
    std::vector <unsigned int> validCards;
    unsigned int numberCards = cards.size();

    if(numberCards == 1)
    {
        return cards;
    }

    for(unsigned int i = 0; i < numberCards; i++)// look over cards
    {
        if(Card(cards.at(i)).getSuit() == stepSuit)   //are there cards with a suit of the step?
        {
            //if we have that suit push card to result
            validCards.push_back(cards.at(i));
        }
    }

    if(!validCards.empty())
    {
        return validCards;//return all cards whith step suit
    }

    if(stepSuit != trumpSuit)//Is step suit not equal trump suit?
    {
        for(unsigned int i = 0; i < numberCards; i++)
        {
            if(Card(cards.at(i)).getSuit() == trumpSuit)   //compare suit of my cards with trump
            {
                //if we have trump we must push trump card to result
                validCards.push_back(cards.at(i));
            }
        }

    }

    return (!validCards.empty()) ? validCards:  cards;
}

void Player::setCardBribe(std::vector <unsigned int> card)
{
    bribes.push_back(card);
}

void Player::printBribe(void)
{
    unsigned int sizeBribe = bribes.size();
    if(sizeBribe > 0)
    {
        for(unsigned int i = 0; i < sizeBribe; i++,std::cout<<std::endl)
        {
            if(i != 0)
            {
                std::cout<<"\t\t";
            }
            for(unsigned int j = 0; j < bribes[i].size(); j++)
            {
                Card(bribes[i][j]).print();
            }
        }
    }
    else
    {
        std::cout<<"0"<<std::endl;
    }
}

void Player::doScoring(void)
{
    numberPoints = 0;
    unsigned int countCard = bribes.size();
    for(unsigned int i = 0; i < countCard; i++)
    {
        for(unsigned int j = 0; j < bribes[i].size(); j++)
        {
            std::map <std::string, unsigned int> score;
            DebercCard card(bribes[i][j]);
            std::string cardView = card.getShortView();
            score[cardView] = card.getScore(this->trumpSuit);
            setScore(score);
        }
    }
}
