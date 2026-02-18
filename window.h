#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
#include <QPushButton>

#include "blackjackgame.h"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(QWidget *parent = nullptr);
    ~Window();
    void setupGUI();

private:
    void displayHand(const std::vector<Card>& hand, int y);
    void refreshHands();

    BlackJackGame game;
    std::vector<QLabel*> cardLabels;

    // Paramètres d'affichage
    const int cols  = 9;
    const int cardW = 80;
    const int cardH = 120;
    const int startX = 20;
    const int gapX = 10;
    const int gapY = 10;

    bool playerTurn = true;
    QPushButton* hitBtn = nullptr;   // pour pouvoir disable
    QPushButton* standBtn = nullptr;
};

#endif // WINDOW_H
