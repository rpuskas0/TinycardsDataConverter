#ifndef IOUTFILTER_H
#define IOUTFILTER_H

#include "deck.h"

#include <QByteArray>

class IOutFilter {
public:
    virtual ~IOutFilter() = default;

    virtual QByteArray convertData(const QList<Deck>& decks) const = 0;
    virtual QString fileExtension() const = 0;
    virtual QString fileTypeName() const = 0;
};


#endif // IOUTFILTER_H
