#ifndef OUTFILTERJSON_H
#define OUTFILTERJSON_H

#include "ioutfilter.h"

#include <QJsonArray>
#include <QJsonObject>

class OutFilterJson : public IOutFilter
{
public:
    QByteArray convertData(const QList<Deck>& decks) const override;
    inline QString fileExtension() const override;
    inline QString fileTypeName() const override;

private:
    static QJsonObject convertCard(const Card& card);
    static QJsonArray convertCardList(const QList<Card>& cardList);
    static QJsonObject convertDeck(const Deck& deck);
    static QJsonArray convertDeckList(const QList<Deck>& deckList);
};

QString OutFilterJson::fileExtension() const
{
    return QString("json");
}

QString OutFilterJson::fileTypeName() const
{
    return QString("JSON file");
}

#endif // OUTFILTERJSON_H
