/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Emil Rekola, 252822                                                       #
# Project 4: Korttipeli                                                     #
# File: card.cc                                                             #
# Description: Module for the project 'Korttipeli'                          #
#       This module creates and handels the cards that move around the UI   #
#############################################################################
*/

#include "card.hh"

#include <QPainter>
#include <QMouseEvent>
#include <QSizePolicy>

unsigned const FRONT_INDEX = 1;
unsigned const BACK_INDEX = 0;
unsigned const CARD_WIDTH = 177;
unsigned const CARD_HEIGHT = 249;
unsigned const DEFAULT_STACK_OFFSET = 35;
QColor const CARD_FRONT_COLOR = QColor(250,239,168,255);
QSize const SUIT_PIXMAP_SIZE = QSize(30,30);

// Korttien alustus pakkaan laittamista varten.
Card::Card(CardSuit suit, unsigned value, QWidget *parent) :
    QFrame(parent),
    suit_(suit),
    value_(value),
    open_(false),
    canOpen_(false),
    backPixmap_(":/cards/card-back-177x249.png"),
    stackedCard_(nullptr)
{
    setBaseSize(CARD_WIDTH, CARD_HEIGHT);
    setMinimumSize(CARD_WIDTH, CARD_HEIGHT);
    setMaximumHeight(CARD_HEIGHT);
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setSizePolicy(policy);
    setupLayout();

}

bool Card::isOpen()
{
    return open_;
}

void Card::allowOpen()
{
    canOpen_ = true;
}

// Määrää miten kortit menevät päällekkäin.
void Card::stackCard(Card *card)
{
    card->setParent(this);

    card->move(DEFAULT_STACK_OFFSET, 0);

    stackedCard_ = card;
    connect(stackedCard_, &Card::resized, this, &Card::expand);
    expand();

}

void Card::removeStackedCards()
{
    stackedCard_ = nullptr;
}

// Palauttaa stringin joka sisältää kyseessä olevan kortin kaikki tiedot.
std::string Card::getCardData()
{
    std::string rVal;
    if(stackedCard_ != nullptr) {
        rVal += stackedCard_->getCardData() + ";";
    }
    rVal += std::to_string(value_) +
            "," +
            std::to_string(suit_) +
            "," +
            std::to_string(open_)
            ;
    return rVal;
}

QLabel* Card::getCurrentSideLabel()
{
    if (open_){
        return findChild<QLabel*>(QString ("front"));
    } else {
        return findChild<QLabel*>(QString ("back"));
    }
}

int Card::getValue()
{
    return value_;
}

// Käännetään kortti ympäri.
void Card::turn()
{
    open_ = !open_;
    if (open_){
        findChild<QLabel*>(QString ("front"))->show();
        findChild<QLabel*>(QString ("back"))->hide();
    } else {
        findChild<QLabel*>(QString ("front"))->hide();
        findChild<QLabel*>(QString ("back"))->show();
    }
}

// Kasvatetaan widgetin piirtoalueen kokoa.
void Card::expand()
{
    setGeometry(x(), y(), width() + DEFAULT_STACK_OFFSET, height());
    emit resized();
}

// Suoritetaan, kun widgettiä kaksoisklikataan.
void Card::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(canOpen_){
        turn();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void Card::setupLayout()
{
    setSuitPixmap();
    setupBack();
    setupFront();
}

// Asettaa kortin attribuuttiin oikean maakuvan piirtämistä varten.
void Card::setSuitPixmap()
{
    switch (suit_) {
    case SPADE:
        suitPixmap_ = QPixmap(":/cards/spade-300px.png")
                .scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    case CLUB:
        suitPixmap_ = QPixmap(":/cards/club-300px.png")
                .scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    case DIAMOND:
        suitPixmap_ = QPixmap(":/cards/diamond-300px.png")
                .scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    case HEART:
        suitPixmap_ = QPixmap(":/cards/heart-300px.png")
                .scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    default:
        break;
    }
}

// Piirtääkortin takapuolen widgettiin.
void Card::setupBack()
{
    // Muodostetaan uusi QLabel-olio, jonka sisällöksi laitetaan kortiolion
    // attribuuttiin talletettu QPixmap-olio ja näytetään label widgetissä.
    QLabel* backImage = new QLabel(this);
    backImage->setObjectName("back");
    backImage->setPixmap(backPixmap_);
    backImage->show();
}

// Piirtää kortin etupuolen widgettiin.
void Card::setupFront()
{
    // Muodostetaan uusi QLabel-olio.
    QLabel* frontImage = new QLabel(this);
    frontImage->setObjectName("front");

    // Muodostetaan uusi QPixmap-olio, johon aletaan piirtää kortin etupuolta.
    QPixmap frontPixmap(backPixmap_.size());
    frontPixmap.fill(Qt::transparent);
    QPainter painter (&frontPixmap);

    // Piirretään kortin pohja, eli kulmista pyöristetty suorakaide.
    QPainterPath path;
    path.addRoundedRect(QRectF(1, 1, frontPixmap.width()-1,
                               frontPixmap.height()-2), 15,
                               15, Qt::RelativeSize);
    painter.fillPath(path, CARD_FRONT_COLOR);
    painter.drawPath(path);

    // Piirretään kortin arvo ja maan kuvio.
    painter.setPen(QPen(Qt::black));
    QFont font = painter.font();
    font.setPixelSize(30);
    painter.setFont(font);

    // Riippuen kortin arvosta, asetetaan tarvittaessa kortin numerollisen
    // arvon tilalle kirjain.
    QString card_value = QString::number(value_);

    if (value_ == 1) {
        card_value = "A";
    }

    else if (value_ == 11) {
        card_value = "J";
        value_ = 10;
    }

    else if (value_ == 12) {
        card_value = "Q";
        value_ = 10;
    }

    else if (value_ == 13) {
        card_value = "K";
        value_ = 10;
    }

    // Tallennetaan painterin nykytila asetusten palauttamista varten.
    painter.save();
    painter.translate(frontPixmap.width()/2, frontPixmap.height()/2);

    // Asetetaan blackjack logolle tarvittavat asetukset.
    blackjack_ = QPixmap(":/cards/Blackjack.png")
            .scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Asetetaan arvo, maa ja logo vasempaan yläkulmaan...
    painter.drawPixmap(-80, -90, suitPixmap_, 0, 0, 0, 0);
    painter.drawText(-80, -120, 30, 30, Qt::AlignCenter, card_value);
    painter.drawPixmap(-55, -55, blackjack_, 0, 0, 0, 0);

    // ...Sekä oikeaan alakulmaan ylösalaisin.
    painter.rotate(180);
    painter.drawPixmap(-80, -90, suitPixmap_, 0, 0, 0, 0);
    painter.drawText(-80, -120, 30, 30, Qt::AlignCenter, card_value);
    painter.drawPixmap(-55, -55, blackjack_, 0, 0, 0, 0);

    // Palautetaan painterin asetukset
    painter.restore();

    // Asetetaan piirretty kuva näkyviin widgetissä.
    frontImage->setPixmap(frontPixmap);
    frontImage->hide();
}
