#include "blackjackrules.h"

int BlackJackRules::pointsOfHand(const std::vector<Card>& hand)
{
    int total = 0;
    int aces = 0;

    for (const Card& c : hand)
    {
        switch (c.rank)
        {
        case Rank::Two:   total += 2; break;
        case Rank::Three: total += 3; break;
        case Rank::Four:  total += 4; break;
        case Rank::Five:  total += 5; break;
        case Rank::Six:   total += 6; break;
        case Rank::Seven: total += 7; break;
        case Rank::Eight: total += 8; break;
        case Rank::Nine:  total += 9; break;

        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            total += 10;
            break;

        case Rank::Ace:
            total += 11;
            aces++;
            break;
        }
    }

    // Ajustement des As
    while (total > 21 && aces > 0)
    {
        total -= 10;
        aces--;
    }

    return total;
}

bool BlackJackRules::isBust(const std::vector<Card>& hand)
{
    return pointsOfHand(hand) > 21;
}
