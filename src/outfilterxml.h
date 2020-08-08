#ifndef OUTFILTERXML_H
#define OUTFILTERXML_H

#include "ioutfilter.h"

#include <QXmlStreamWriter>

class OutFilterXML : public IOutFilter
{
public:
    QByteArray convertData(const QList<Deck>& decks) const override;
    inline QString fileExtension() const override;
    inline QString fileTypeName() const override;

private:
    static const QString xmlDTD;
    static const QString xmlDeckNamespace;

    static void convertCard(const Card& card, QXmlStreamWriter& xml);
    static void convertCardList(const QList<Card>& cardList, QXmlStreamWriter& xml);
    static void convertDeck(const Deck& deck, QXmlStreamWriter& xml);
    static void convertDeckList(const QList<Deck>& deckList, QXmlStreamWriter& xml);
    static void finalizeXmlDoc(QXmlStreamWriter& xml);
    static void initializeXmlDoc(QXmlStreamWriter& xml);
    static void setupXmlWriter(QXmlStreamWriter& xml);
};

QString OutFilterXML::fileExtension() const
{
    return QString("xml");
}

QString OutFilterXML::fileTypeName() const
{
    return QString("XML file");
}

#endif // OUTFILTERXML_H
