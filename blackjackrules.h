#ifndef BLACKJACKRULES_H
#define BLACKJACKRULES_H

#include "card.h"
#include "cardgame.h"
#include <vector>
#include <array>

using namespace std;

class BlackJackRules
{
public:
    static int pointsOfHand(const vector<Card>& hand);
    static bool isBust(const vector<Card>& hand);
};

#endif // BLACKJACKRULES_H
