#ifndef DECK_H
#define DECK_H

#include <QStringList>

struct Card {
    QString front;
    QStringList back;
};

struct Deck
{
    QString name;
    QString description;
    QString coverImageLink;
    QString privacy;
    QString language;
    QString deleted;
    QString createdAt;
    QString updatedAt;
    QList<Card> cards;
};

#endif // DECK_H
