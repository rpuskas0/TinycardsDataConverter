#ifndef IINFILTER_H
#define IINFILTER_H

#include "deck.h"

#include <QList>
#include <QTextStream>

class IInFilter {
public:
    virtual ~IInFilter() = default;

    virtual QList<Deck> convertData(QTextStream& textStream) const = 0;
};

#endif // IINFILTER_H
