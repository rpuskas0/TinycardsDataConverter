#include "outfilterxml.h"

#define XMLVERSION "1.0"
#define XMLSTANDALONE true

const QString OutFilterXML::xmlDTD = QString("\n<!DOCTYPE deck_list [\n"
                                             "    <!ELEMENT deck_list (deck+)>\n"
                                             "    <!ELEMENT deck (name?, description?, coverImage?, privacy?,"
                                             " language?, deleted?, createdAt?, updatedAt?, cards)>\n"
                                             "    <!ELEMENT cards (card+)>\n"
                                             "    <!ELEMENT card (front, back+)>\n"
                                             "]>\n");
const QString OutFilterXML::xmlDeckNamespace = "tinycards.duolingo.com";

QByteArray OutFilterXML::convertData(const QList<Deck>& decks) const
{
    QByteArray deckXMLDoc;
    QXmlStreamWriter xml(&deckXMLDoc);

    setupXmlWriter(xml);

    initializeXmlDoc(xml);
    convertDeckList(decks, xml);
    finalizeXmlDoc(xml);

    return deckXMLDoc;
}

void OutFilterXML::convertCard(const Card& card, QXmlStreamWriter& xml)
{
    xml.writeStartElement("card");
    xml.writeTextElement(xmlDeckNamespace, "front", card.front);

    for (const auto& b : card.back) {
        xml.writeTextElement(xmlDeckNamespace, "back", b);
    }
    xml.writeEndElement();
}

void OutFilterXML::convertCardList(const QList<Card>& cardList, QXmlStreamWriter& xml)
{
    xml.writeStartElement(xmlDeckNamespace, "cards");

    for (const auto& card : cardList) {
        convertCard(card, xml);
    }

    xml.writeEndElement();
}

void OutFilterXML::convertDeck(const Deck& deck, QXmlStreamWriter& xml)
{
    xml.writeStartElement(xmlDeckNamespace, "deck");

    xml.writeTextElement(xmlDeckNamespace, "name", deck.name);
    xml.writeTextElement(xmlDeckNamespace, "description", deck.description);
    xml.writeTextElement(xmlDeckNamespace, "coverImage", deck.coverImageLink);
    xml.writeTextElement(xmlDeckNamespace, "privacy", deck.privacy);
    xml.writeTextElement(xmlDeckNamespace, "language", deck.language);
    xml.writeTextElement(xmlDeckNamespace, "deleted", deck.deleted);
    xml.writeTextElement(xmlDeckNamespace, "createdAt", deck.createdAt);
    xml.writeTextElement(xmlDeckNamespace, "updatedAt", deck.updatedAt);
    convertCardList(deck.cards, xml);

    xml.writeEndElement();
}

void OutFilterXML::convertDeckList(const QList<Deck>& deckList, QXmlStreamWriter& xml)
{
    xml.writeStartElement(xmlDeckNamespace, "deck_list");

    for (const auto& deck : deckList) {
        convertDeck(deck, xml);
    }

    xml.writeEndElement();
}

void OutFilterXML::finalizeXmlDoc(QXmlStreamWriter &xml)
{
    xml.writeEndDocument();
}

void OutFilterXML::initializeXmlDoc(QXmlStreamWriter& xml)
{
    xml.writeStartDocument(XMLVERSION, XMLSTANDALONE);
    xml.writeDTD(xmlDTD);
}

void OutFilterXML::setupXmlWriter(QXmlStreamWriter &xml)
{
    xml.setAutoFormatting(true);
}
