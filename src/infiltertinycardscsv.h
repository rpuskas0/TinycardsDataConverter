#ifndef INFILTERTINICARDSCSV_H
#define INFILTERTINICARDSCSV_H

#include "iinfilter.h"

class InFilterTinycardsCSV : public IInFilter
{
public:
    QList<Deck> convertData(QTextStream& textStream) const override;

private:
    static const QChar csvFieldDelimiter;
    static const QChar csvSpecialFieldDelimiter;
    static const QString cardParsePosNew;
    static const QString cardParsePosFront;
    static const QString cardParsePosBack;

    class Latch;
    enum TinycardsCsvField : short;
    enum class CardParsePos : short;

    static int countCsvFields(QTextStream& textStream, QChar csvFieldDelimiter);
    static QString getLegendLine(QTextStream& textStream);
    static QList<Deck> parseRawDeckData(const QList<QStringList>& rawDeckDataList);
    static QList<Card> parseCards(const QString& rawCardsData);
    static Deck parseDeck(const QStringList& rawDeckData);
    static QList<QStringList> parseText(QTextStream& textStream);
    static void copyValueToDeckDataField(Deck& deck, const QString& dataFieldVal, int dataFieldNum);
    static void setPosAfterLegend(QTextStream& textStream);

};


class InFilterTinycardsCSV::Latch {
public:
    bool operator()() const {return state;}

    void trigger() {state = state ? false : true;}

private:
    bool state = false;
};

#endif // INFILTERTINICARDSCSV_H
