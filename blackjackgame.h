#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "card.h"
#include "cardgame.h"
#include <vector>

class BlackJackGame
{
public:
    BlackJackGame();

    void newGame();          // distribue 2 cartes joueur + 1 dealer
    void playerHit();        // joueur pioche
    void dealerPlay();       // dealer joue automatique

    int playerScore() const;
    int dealerScore() const;

    bool playerBust() const;
    bool dealerBust() const;

    const std::vector<Card>& getPlayerHand() const;
    const std::vector<Card>& getDealerHand() const;

private:
    Cardgame deck;
    std::vector<Card> playerHand;
    std::vector<Card> dealerHand;
};

#endif // BLACKJACKGAME_H
