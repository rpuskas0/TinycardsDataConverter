#include "outfilterjson.h"

#include <QJsonDocument>

QByteArray OutFilterJson::convertData(const QList<Deck>& decks) const
{
    QJsonDocument deckJsonDoc(convertDeckList(decks));
    return deckJsonDoc.toJson();
}

QJsonObject OutFilterJson::convertCard(const Card& card)
{
    QJsonObject jsonObj;
    QJsonArray cardBackArray;

    for (const auto& b : card.back) {
        cardBackArray.push_back(b);
    }

    jsonObj.insert("front", card.front);
    jsonObj.insert("back", cardBackArray);

    return jsonObj;
}

QJsonArray OutFilterJson::convertCardList(const QList<Card>& cardList)
{
    QJsonArray cardJsonArray;

    for (const auto& card : cardList) {
        cardJsonArray.push_back(convertCard(card));
    }

    return cardJsonArray;
}

QJsonObject OutFilterJson::convertDeck(const Deck& deck)
{
    QJsonObject jsonObj;

    jsonObj.insert("name", deck.name);
    jsonObj.insert("description", deck.description);
    jsonObj.insert("coverImage", deck.coverImageLink);
    jsonObj.insert("privacy", deck.privacy);
    jsonObj.insert("language", deck.language);
    jsonObj.insert("deleted", deck.deleted);
    jsonObj.insert("createdAt", deck.createdAt);
    jsonObj.insert("updatedAt", deck.updatedAt);
    jsonObj.insert("cards", convertCardList(deck.cards));

    return jsonObj;
}

QJsonArray OutFilterJson::convertDeckList(const QList<Deck>& deckList)
{
    QJsonArray deckJsonArray;

    for (const auto& deck : deckList) {
        deckJsonArray.push_back(convertDeck(deck));
    }

    return deckJsonArray;
}
