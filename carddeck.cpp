#include "carddeck.h"
#include "card.h"


cardDeck::cardDeck(unsigned int minRank = 0)
{
    for(unsigned j = 0; j < 4; j++)
    {
        for(unsigned int i = (13*j + minRank); i < (13 + 13*j); i++)
        {
            cards.push_back(i);
        }
    }
}

unsigned int cardDeck::pullOut(void)
{
    unsigned int card;

    std::srand(time(0));
    unsigned int randNum = 0 + rand() % cards.size();
    card = cards.at(randNum);
    cards.erase(cards.begin()+randNum);

    return card;
}

void cardDeck::print(void)
{
    unsigned int suit = 0;
    for(unsigned int i = 0; i < cards.size(); i++)
    {
        Card card(cards.at(i));

        if(suit != card.getSuit())
        {
            std::cout<<std::endl;
            suit = card.getSuit();
        }
        card.shortPrint();
    }
    std::cout<<std::endl;
}
