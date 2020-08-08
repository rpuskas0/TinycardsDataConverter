#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "iinfilter.h"
#include "ioutfilter.h"

#include <QFile>
#include <QTextStream>

#include <memory>


class Controller : public QObject
{
public:
    Controller();
    inline QString getOutFileExtension() const;
    inline QString getOutFileTypeName() const;
    void loadDeckDataFromFile(const QString& fileName);
    void selectOutputFilter(int filterType);
    void selectOutputOption(int outputOption);
    void startConversion(const QString& fileName);

private:
    enum ConvOutOption : short {toSingleFile, toSeparateFiles};
    enum OutFilterType : short {JSON, XML, CSV};

    QList<Deck> mDecks;
    QTextStream mTextStream;
    QFile mFile;
    std::unique_ptr<IInFilter> mInputFilter;
    std::unique_ptr<IOutFilter> mOutputFilter;
    ConvOutOption mOutputOption;

    void flushAndClose();
    void openFile(const QString& fileName, QIODevice::OpenMode openMode);
    void convertToSeparateFiles(const QString& fileName);
    void convertToSingleFile(const QString& fileName);
    void insertFileCountIntoName(QString& fileName, int count) const;
};

QString Controller::getOutFileExtension() const
{
    return mOutputFilter->fileExtension();
}

QString Controller::getOutFileTypeName() const
{
    return mOutputFilter->fileTypeName();
}

#endif // CONTROLLER_H
