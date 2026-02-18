#include "window.h"
#include "blackjackgame.h"
#include "blackjackrules.h"
#include "cardgame.h"

#include <QIcon>
#include <QPixmap>
#include <QPushButton>

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    setupGUI();
}

Window::~Window() {}

void Window::displayHand(const std::vector<Card>& hand, int y)
{
    //Paramètre de l'affichage des cartes
    const int cols = 9;
    const int cardW = 80;
    const int cardH = 120;
    const int startX = 20;
    const int startY = 20;
    const int gapX = 10;
    const int gapY = 10;

    // Si image manquante => affiche le texte au lieu de planter
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

    int row = cardIndex / cols;
    int col = cardIndex % cols;

    lbl->move(startX + col * (cardW + gapX),
              startY + row * (cardH + gapY));

    lbl->show();
    cardLabels.push_back(lbl);
}

void Window::refreshHands(){}

void Window::setupGUI()
{
    //Paramètre de la fenêtre
    setWindowTitle("BlackJack");
    setWindowIcon(QIcon(":/images/spades_A.png"));
    setGeometry(200, 200, 1000, 750);

    cardLabels.reserve(52);

    game.newGame();     //start

    displayHand(game.getDealerHand(), 30);
    displayHand(game.getPlayerHand(), 250);

    QPushButton* hitBtn = new QPushButton("Player hit", this);
    hitBtn->setGeometry(400, 600, 150, 40);

    connect(hitBtn, &QPushButton::clicked, this, [this]() {
        if (game.playerBust()) return;  // optionnel

        game.playerHit();

        if (game.playerBust()) {
            qDebug() << "Player bust!";
        }
    });

    QPushButton* standBtn = new QPushButton("Stand", this);
    standBtn->setGeometry(600, 600, 150, 40);

    connect(standBtn, &QPushButton::clicked, this, [this]() {
        game.dealerPlay();
        qDebug() << "Player:" << game.playerScore()
                 << "Dealer:" << game.dealerScore();
    });

    QPushButton* newBtn = new QPushButton("New game", this);
    newBtn->setGeometry(50, 600, 150, 40);

    connect(newBtn, &QPushButton::clicked, this, [this]() {
        game.newGame();
    });
}

    /*
    QPushButton* btn = new QPushButton("Player hit", this);
    btn->setGeometry(50, 50, 150, 40);
    btn->move(400, 600);

    connect(btn, &QPushButton::clicked, this, [this, cols, cardW, cardH, startX, startY, gapX, gapY](){
        qDebug("Bouton pressé !");

        Card c = game.draw(); // prend une carte du deck

        // Si image manquante => affiche le texte au lieu de planter
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

        int row = cardIndex / cols;
        int col = cardIndex % cols;

        lbl->move(startX + col * (cardW + gapX),
                  startY + row * (cardH + gapY));

        lbl->show();
        cardLabels.push_back(lbl);

        cardIndex++;

    });

    QPushButton* newBtn = new QPushButton("New game", this);
    newBtn->setGeometry(600, 600, 150, 40);

    connect(newBtn, &QPushButton::clicked, this, [this]() {
        game.newGame();
    });
    */

            /*
            const int cols = 9;     // 9 par ligne => 4 lignes (9*4=36)
            const int cardW = 80;
            const int cardH = 120;
            const int startX = 20;
            const int startY = 20;
            const int gapX = 10;
            const int gapY = 10;

            cardLabels.reserve(52);

            for (int i = 0; i < 52; ++i)
            {
                Card c = game.draw(); // prend une carte du deck

                // Si image manquante => affiche le texte au lieu de planter
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
                          startY + row * (cardH + gapY));

                lbl->show();
                cardLabels.push_back(lbl);

                QPushButton* btn = new QPushButton("Nouvelle partie", this);
                btn->setGeometry(50, 50, 150, 40);
                btn->move(400, 600);

                connect(btn, &QPushButton::clicked, this, [](){
                    qDebug("Bouton pressé !");
                });
            }
            */

