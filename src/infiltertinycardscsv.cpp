#include "infiltertinycardscsv.h"

#include <exception>

const QChar InFilterTinycardsCSV::csvFieldDelimiter = ',';
const QChar InFilterTinycardsCSV::csvSpecialFieldDelimiter = '"';
const QString InFilterTinycardsCSV::cardParsePosNew = "### Card";
const QString InFilterTinycardsCSV::cardParsePosFront = "Front";
const QString InFilterTinycardsCSV::cardParsePosBack = "Back";

enum InFilterTinycardsCSV::TinycardsCsvField : short {name, desc, coverImg, cards, priv, lang, del, created, updated};
enum class InFilterTinycardsCSV::CardParsePos : short {cardNew, front, back};


QList<Deck> InFilterTinycardsCSV::convertData(QTextStream& textStream) const
{
    if (!textStream.device()) throw std::runtime_error("There is no data to parse!");

    QList<QStringList> rawDeckDataList = parseText(textStream);
    return parseRawDeckData(rawDeckDataList);
}

int InFilterTinycardsCSV::countCsvFields(QTextStream& textStream, QChar fieldSeparator)
{
    QString legendLine = getLegendLine(textStream);
    return legendLine.count(fieldSeparator) + 1;
}

QString InFilterTinycardsCSV::getLegendLine(QTextStream& textStream)
{
    auto currStreamPos = textStream.pos();
    QString legendLine;

    textStream.seek(0);
    legendLine = textStream.readLine();
    textStream.seek(currStreamPos);

    return legendLine;
}

QList<Deck> InFilterTinycardsCSV::parseRawDeckData(const QList<QStringList>& rawDeckDataList)
{
    QList<Deck> decks;

    for (const auto& rawDeckData : rawDeckDataList) {
        decks.push_back(parseDeck(rawDeckData));
    }

    return decks;
}

QList<Card> InFilterTinycardsCSV::parseCards(const QString& rawCardsData)
{
    auto cardsDataList = rawCardsData.split(QChar::LineFeed, Qt::SkipEmptyParts);
    QList<Card> cardList;
    Card card;
    CardParsePos currCardPos = CardParsePos::cardNew;

    for (int i = 0; i < cardsDataList.size(); ++i) {
        const QString& item = cardsDataList[i];

        if (item.startsWith(cardParsePosNew)) {
            currCardPos = CardParsePos::cardNew;
            if (i != 0) cardList.push_back(card);  // don't push on first pass (an empty card)
            card.back.clear();                     // clear out leftovers of previous card
            continue;
        }

        if (item == cardParsePosFront) {
            currCardPos = CardParsePos::front;
            continue;
        }

        if (item == cardParsePosBack) {
            currCardPos = CardParsePos::back;
            continue;
        }

        if (currCardPos == CardParsePos::front) {
            card.front = item.mid(2);              // Store data without leading asterisk and space
        }

        if (currCardPos == CardParsePos::back) {
            card.back.push_back(item.mid(2));      // Ditto
        }
    }

    cardList.push_back(card);                      // push last processed card

    return cardList;
}

Deck InFilterTinycardsCSV::parseDeck(const QStringList& rawDeckData)
{
    Deck deck;

    for (int currCsvField = 0; currCsvField < rawDeckData.size(); ++currCsvField) {
        if (currCsvField != TinycardsCsvField::cards) {
            copyValueToDeckDataField(deck, rawDeckData[currCsvField], currCsvField);
        } else {
            deck.cards = parseCards(rawDeckData[currCsvField]);
        }
    }

    return deck;
}

QList<QStringList> InFilterTinycardsCSV::parseText(QTextStream &textStream)
{
    QList<QStringList> csvDoc;
    QStringList csvLine;
    QString csvField;
    Latch inSpecialCsvField;
    const int csvFieldsPerLine = countCsvFields(textStream, csvFieldDelimiter);
    int csvFieldCount = 0;
    QChar c;

    csvLine.reserve(csvFieldsPerLine);
    setPosAfterLegend(textStream);

    while (!textStream.atEnd()) {
        textStream >> c;

        if (c.isPrint()) {
            if (c == csvSpecialFieldDelimiter) {
                inSpecialCsvField.trigger();
                continue;
            }

            if (inSpecialCsvField()) {
                csvField.push_back(c);
            }

            if (!inSpecialCsvField() && c != csvFieldDelimiter) {
                csvField.push_back(c);
            }

            if (!inSpecialCsvField() && c == csvFieldDelimiter) {
                csvLine.push_back(csvField);
                csvField.clear();
                ++csvFieldCount;
            }
        } else {
            if (inSpecialCsvField()) {
                csvField.push_back(QChar::LineFeed);
            }

            if (!inSpecialCsvField() && c == QChar::LineFeed && csvFieldCount >= csvFieldsPerLine - 1) {
                csvLine.push_back(csvField);
                csvField.clear();
                csvDoc.push_back(csvLine);
                csvLine.clear();
                csvLine.reserve(csvFieldsPerLine);
                csvFieldCount = 0;
            }
        }
    }

    return csvDoc;
}

void InFilterTinycardsCSV::copyValueToDeckDataField(Deck& deck, const QString& dataFieldVal, int dataFieldNum)
{
    switch (dataFieldNum) {
        case TinycardsCsvField::name:
            deck.name = dataFieldVal;
            break;
        case TinycardsCsvField::desc:
            deck.description = dataFieldVal;
            break;
        case TinycardsCsvField::coverImg:
            deck.coverImageLink = dataFieldVal;
            break;
        case TinycardsCsvField::priv:
            deck.privacy = dataFieldVal;
            break;
        case TinycardsCsvField::lang:
            deck.language = dataFieldVal;
            break;
        case TinycardsCsvField::del:
            deck.deleted = dataFieldVal;
            break;
        case TinycardsCsvField::created:
            deck.createdAt = dataFieldVal;
            break;
        case TinycardsCsvField::updated:
            deck.updatedAt = dataFieldVal;
            break;
        default:
            return;
    }
}

void InFilterTinycardsCSV::setPosAfterLegend(QTextStream& textStream)
{
    textStream.seek(0);
    textStream.readLine();
}
