#ifndef CARD_H
#define CARD_H

#include <QString>

enum class Suit {Hearts, Diamonds, Clubs, Spades};
enum class Rank {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};

struct Card
{
    Suit suit;
    Rank rank;

    //Name of my card
    QString toString() const
    {
        static const char* suits[]  = {"Coeur", "Carreau", "Pique", "Trefle"};
        static const char* ranks[]  = {"2","3","4","5","6","7","8","9","10","Valet","Dame","Roi","As"};
        return QString("%1 %2").arg(suits[(int)suit]).arg(ranks[(int)rank]);
    }

    //Path of the image
    QString imagePath() const
    {
        //":/images/hearts_ace.png"
        static const char* suitKey[] = {"hearts","diamonds","clubs","spades"};
        static const char* rankKey[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
        return QString(":/images/%1_%2.png").arg(suitKey[(int)suit]).arg(rankKey[(int)rank]);
    }
};

#endif // CARD_H
