#ifndef OUTFILTERCSV_H
#define OUTFILTERCSV_H

#include "ioutfilter.h"

class OutFilterCSV : public IOutFilter
{
public:
    QByteArray convertData(const QList<Deck>& decks) const override;
    inline QString fileExtension() const override;
    inline QString fileTypeName() const override;

private:
    static const QChar csvDelimiter;

    static void convertCard(const Card& card, QByteArray& byteArray);
    static void convertCardList(const QList<Card>& cardList, QByteArray& byteArray);
    static void convertDeckList(const QList<Deck>& deckList, QByteArray& byteArray);
    static void initializeCsvDoc(QByteArray& byteArray);
};

QString OutFilterCSV::fileExtension() const
{
    return QString("csv");
}

QString OutFilterCSV::fileTypeName() const
{
    return QString("CSV file");
}

#endif // OUTFILTERCSV_H
