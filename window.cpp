#include "window.h"
#include "blackjackgame.h"
#include "blackjackrules.h"
#include "cardgame.h"

#include <QIcon>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    setupGUI();
}

Window::~Window()
{
    // sécurité : libère les labels si la fenêtre se ferme
    for (QLabel* lbl : cardLabels) delete lbl;
    cardLabels.clear();
}

void Window::displayHand(const std::vector<Card>& hand, int y)
{
    for (int i = 0; i < (int)hand.size(); i++)
    {
        const Card& c = hand[i];

        QLabel *lbl = new QLabel(this);

        QPixmap pix(c.imagePath());
        if (pix.isNull())
        {
            lbl->setText(c.toString());
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setStyleSheet("border: 1px solid black; background: white;");
            lbl->setFixedSize(cardW, cardH);
        }
        else
        {
            lbl->setPixmap(pix.scaled(cardW, cardH, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            lbl->setFixedSize(cardW, cardH);
        }

        int row = i / cols;
        int col = i % cols;

        lbl->move(startX + col * (cardW + gapX),
                  y      + row * (cardH + gapY));

        lbl->show();
        cardLabels.push_back(lbl);
    }
}

void Window::refreshHands()
{
    // supprimer les anciens labels
    for (QLabel* lbl : cardLabels)
        delete lbl;
    cardLabels.clear();

    // ré-afficher
    displayHand(game.getDealerHand(), 30);
    displayHand(game.getPlayerHand(), 250);
}

void Window::updateScores()
{
    playerScoreLabel->setText(
        "Player score: " + QString::number(game.playerScore())
        );

    dealerScoreLabel->setText(
        "Dealer score: " + QString::number(game.dealerScore())
        );
}

void Window::setupGUI()
{
    //----------------------------------------------
    // ***Paramètre de la fenêtre***
    setWindowTitle("BlackJack");
    setWindowIcon(QIcon(":/images/spades_A.png"));
    setGeometry(200, 200, 1000, 750);

    //----------------------------------------------
    // ***Affichage score***
    playerScoreLabel = new QLabel(this);
    playerScoreLabel->setGeometry(20, 210, 300, 30);
    playerScoreLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    dealerScoreLabel = new QLabel(this);
    dealerScoreLabel->setGeometry(20, 10, 300, 30);
    dealerScoreLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    //----------------------------------------------
    // ***Affiche le premier jeu***
    cardLabels.reserve(52);

    game.newGame();     //start
    updateScores();

    displayHand(game.getDealerHand(), 30);
    displayHand(game.getPlayerHand(), 250);

    //----------------------------------------------
    // ***HIT***
    hitBtn = new QPushButton("Player hit", this);
    hitBtn->setGeometry(400, 600, 150, 40);

    connect(hitBtn, &QPushButton::clicked, this, [this]() {
        if (!playerTurn) return;

        game.playerHit();
        refreshHands();
        updateScores();

        if (game.playerBust()) {
            playerTurn = false;
            hitBtn->setEnabled(false);
            if (standBtn) standBtn->setEnabled(false);
        }
    });

    //----------------------------------------------
    // ***STAND***
    standBtn = new QPushButton("Stand", this);
    standBtn->setGeometry(600, 600, 150, 40);

    connect(standBtn, &QPushButton::clicked, this, [this]() {
        if (!playerTurn) return;

        playerTurn = false;
        hitBtn->setEnabled(false);
        standBtn->setEnabled(false);

        game.dealerPlay();
        refreshHands();
        updateScores();
    });

    //----------------------------------------------
    // ***STAND***
    QPushButton* newBtn = new QPushButton("New game", this);
    newBtn->setGeometry(50, 600, 150, 40);

    connect(newBtn, &QPushButton::clicked, this, [this]() {
        game.newGame();
        playerTurn = true;
        hitBtn->setEnabled(true);
        if (standBtn) standBtn->setEnabled(true);
        refreshHands();
        updateScores();
    });

}




