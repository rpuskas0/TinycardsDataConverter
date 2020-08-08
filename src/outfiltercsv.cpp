#include "outfiltercsv.h"


const QChar OutFilterCSV::csvDelimiter = ';';

QByteArray OutFilterCSV::convertData(const QList<Deck>& decks) const
{
    QByteArray deckCsvDoc;

    initializeCsvDoc(deckCsvDoc);
    convertDeckList(decks, deckCsvDoc);

    return deckCsvDoc;
}

void OutFilterCSV::convertCard(const Card& card, QByteArray& byteArray)
{
    byteArray.append(card.front);

    for (const auto& b : card.back) {
        byteArray.append(csvDelimiter);
        byteArray.append(b);
    }

    byteArray.append(QChar::LineFeed);
}

void OutFilterCSV::convertCardList(const QList<Card>& cardList, QByteArray& byteArray)
{
    for (const auto& card : cardList) {
        convertCard(card, byteArray);
    }
}

void OutFilterCSV::convertDeckList(const QList<Deck>& deckList, QByteArray& byteArray)
{
    for (const auto& deck : deckList) {
        convertCardList(deck.cards, byteArray);
    }
}

void OutFilterCSV::initializeCsvDoc(QByteArray& byteArray)
{
    byteArray.append(QString("front")
                     + csvDelimiter
                     + QString("back1")
                     + csvDelimiter
                     + QString("back2")
                     + csvDelimiter
                     + QString("back3"));
    byteArray.append(QChar::LineFeed);
}
