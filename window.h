#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <vector>

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
};

#endif // WINDOW_H
