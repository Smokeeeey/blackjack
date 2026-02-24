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
    displayHand(game.getDealerHand(), y_deal);
    displayHand(game.getPlayerHand(), y_player);
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
    setGeometry(100, 30, 1675, 999);
    setFixedSize(this->size());
    setStyleSheet("background-image: url(:/images/table.png);");

    //----------------------------------------------
    // ***Affichage score***
    playerScoreLabel = new QLabel(this);
    playerScoreLabel->setGeometry(1675/2.3, 750, 300, 30);
    playerScoreLabel->setStyleSheet("font-size: 18px; "
                                    "font-weight: bold;"
                                    "background-color: #FFFFFF;"
                                    "color: white;");

    dealerScoreLabel = new QLabel(this);
    dealerScoreLabel->setGeometry(1675/2.3, 10, 300, 30);
    dealerScoreLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    //----------------------------------------------
    // ***Affiche le premier jeu***
    cardLabels.reserve(52);

    game.newGame();     //start
    updateScores();

    displayHand(game.getDealerHand(), y_deal);
    displayHand(game.getPlayerHand(), y_player);

    //----------------------------------------------
    // ***HIT***
    hitBtn = new QPushButton("Player hit", this);
    hitBtn->setGeometry(400, 600, 150, 40);
    hitBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #ffffff;"
        "border: 1px solid #27ae60;"
        "color: white;"
        "font-size: 16px;"
        "border-radius: 10px;"
        "}"
        );

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
    standBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #3498db;"
        "color: white;"
        "font-size: 16px;"
        "border-radius: 10px;"
        "}"
        );

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
    // ***NEWGAME***
    QPushButton* newBtn = new QPushButton("New game", this);
    newBtn->setGeometry(50, 600, 150, 40);
    newBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #3498db;"
        "color: white;"
        "font-size: 16px;"
        "border-radius: 10px;"
        "}"
        );

    connect(newBtn, &QPushButton::clicked, this, [this]() {
        game.newGame();
        playerTurn = true;
        hitBtn->setEnabled(true);
        if (standBtn) standBtn->setEnabled(true);
        refreshHands();
        updateScores();
    });

}




