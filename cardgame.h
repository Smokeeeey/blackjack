#ifndef CARDGAME_H
#define CARDGAME_H

#include "card.h"
#include <vector>
#include <array>
#include <random>

using namespace std;

class Cardgame
{
public:
    Cardgame();

    void resetDeck();          // recrée le deck trié (52 cartes)
    void shuffle();            // mélange

    bool empty() const;
    int  size() const;

    Card draw();               // pioche 1 carte (retire du deck)

private:
    vector<Card> deck;
};

#endif // CARDGAME_H
