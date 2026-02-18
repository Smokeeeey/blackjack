#include "blackjackgame.h"
#include "blackjackrules.h"
#include "cardgame.h"

BlackJackGame::BlackJackGame()
{
    newGame();
}
//-----------------------------------------
// distribue 2 cartes joueur + 1 dealer
void BlackJackGame::newGame()
{
    deck.resetDeck();
    deck.shuffle();

    playerHand.clear();
    dealerHand.clear();

    playerHand.push_back(deck.draw());
    dealerHand.push_back(deck.draw());
    playerHand.push_back(deck.draw());
}
//-----------------------------------------
// joueur pioche
void BlackJackGame::playerHit()
{
    playerHand.push_back(deck.draw());
}
//-----------------------------------------
// dealer joue automatique tant qu'il n'a pas 17
void BlackJackGame::dealerPlay()
{
    while (BlackJackRules::pointsOfHand(dealerHand) < 17)
    {
        dealerHand.push_back(deck.draw());
    }
}
//-----------------------------------------
int BlackJackGame::playerScore() const
{
    return BlackJackRules::pointsOfHand(playerHand);
}
//-----------------------------------------
int BlackJackGame::dealerScore() const
{
    return BlackJackRules::pointsOfHand(dealerHand);
}
//-----------------------------------------
bool BlackJackGame::playerBust() const
{
    return BlackJackRules::isBust(playerHand);
}
//-----------------------------------------
bool BlackJackGame::dealerBust() const
{
    return BlackJackRules::isBust(dealerHand);
}
//-----------------------------------------
const vector<Card>& BlackJackGame::getPlayerHand() const
{
    return playerHand;
}
//-----------------------------------------
const vector<Card>& BlackJackGame::getDealerHand() const
{
    return dealerHand;
}
