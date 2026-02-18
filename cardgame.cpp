#include "cardgame.h"
#include <iostream>
#include <algorithm>


using namespace std;

//Initilise le jeu de cartes
Cardgame::Cardgame()
{
    resetDeck();
}

void Cardgame::resetDeck()
{
    deck.clear();
    deck.reserve(52);   //Alloue la mémoire

    for (int a = 0; a < 4; a++)
    {
        for (int b = 0; b < 13; b++)
        {
            deck.push_back(Card{(Suit)a,(Rank)b});
        }
    }
}

//-----------------------------------------

//Mélanger le paquet
void Cardgame::shuffle()
{
    static random_device rd;       // source really random
    static mt19937 mix(rd());      // Mersenne Twister

    std::shuffle(deck.begin(), deck.end(), mix);
}

//-----------------------------------------

//Retourne si le paquet est vide
bool Cardgame::empty() const
{
    return deck.empty();
}

//-----------------------------------------

//Retourne la taille en int donc conversion depuis le size_t de .size
int Cardgame::size() const
{
    return static_cast<int>(deck.size());
}

//-----------------------------------------

//Distribuer une carte
Card Cardgame::draw()
{
    if (deck.empty())
    {
        throw runtime_error("Deck is empty");
    }

    Card c = deck.back();   //Copie la dernière carte
    deck.pop_back();        //Retire la dernière carte
    return c;
}

//-----------------------------------------



