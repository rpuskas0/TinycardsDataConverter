#include "controller.h"

#include "deck.h"
#include "infiltertinycardscsv.h"
#include "outfiltercsv.h"
#include "outfilterjson.h"
#include "outfilterxml.h"

#include <exception>

Controller::Controller()
{
    mInputFilter = std::make_unique<InFilterTinycardsCSV>();
    mOutputFilter = std::make_unique<OutFilterJson>();
    mOutputOption = ConvOutOption::toSingleFile;
    mTextStream.setDevice(&mFile);
}

void Controller::openFile(const QString& fileName, QIODevice::OpenMode openMode)
{
    if (fileName.isNull()) {
        throw std::runtime_error("A file must be selected before proceeding");
    } else {
        mFile.setFileName(fileName);
        if (!mFile.open(openMode | QIODevice::Text))
            throw std::runtime_error("File could not be opened! Do you have enough permissions?");
    }
}

void Controller::convertToSeparateFiles(const QString& fileName)
{
    QString incrFileName = fileName;
    QList<Deck> singleDeck;

    for (int i = 0; i < mDecks.size(); ++i) {
        insertFileCountIntoName(incrFileName, i);
        openFile(incrFileName, QIODevice::WriteOnly);
        singleDeck.push_back(mDecks[i]);

        mTextStream << mOutputFilter->convertData(singleDeck);

        singleDeck.clear();
        flushAndClose();
        incrFileName = fileName;
    }
}

void Controller::convertToSingleFile(const QString &fileName)
{
    openFile(fileName, QIODevice::WriteOnly);
    mTextStream << mOutputFilter->convertData(mDecks);
    flushAndClose();
}

void Controller::insertFileCountIntoName(QString& fileName, int count) const
{
    QString fileExtension = '.' + getOutFileExtension();
    QString fileCount = '-' + QString().setNum(count);

    if (fileName.endsWith(fileExtension)) {
        fileName.insert(fileName.length() - fileExtension.length(), fileCount);
    } else {
        fileName.append(fileCount);
    }
}

void Controller::loadDeckDataFromFile(const QString& fileName)
{
    openFile(fileName, QIODevice::ReadOnly);
    mDecks = mInputFilter->convertData(mTextStream);
    flushAndClose();
}

void Controller::selectOutputFilter(int filterType)
{
    switch (filterType) {
        case OutFilterType::JSON:
            mOutputFilter = std::make_unique<OutFilterJson>();
            break;
        case OutFilterType::XML:
            mOutputFilter = std::make_unique<OutFilterXML>();
            break;
        case OutFilterType::CSV:
            mOutputFilter = std::make_unique<OutFilterCSV>();
            break;
        default:
            mOutputFilter = std::make_unique<OutFilterJson>();
    }
}

void Controller::selectOutputOption(int outputOption)
{
    switch (outputOption) {
        case ConvOutOption::toSingleFile:
            mOutputOption = ConvOutOption::toSingleFile;
            break;
        case ConvOutOption::toSeparateFiles:
            mOutputOption = ConvOutOption::toSeparateFiles;
            break;
        default:
            mOutputOption = ConvOutOption::toSingleFile;
    }
}

void Controller::startConversion(const QString& fileName)
{
    if (mDecks.empty()) {
        throw std::runtime_error("No data was loaded. Please open a file before proceeding.");
    }

    if (fileName.isNull())
        throw std::runtime_error("A file must be selected before proceeding");

    if (mOutputOption == ConvOutOption::toSingleFile) {
        convertToSingleFile(fileName);
    } else {
        convertToSeparateFiles(fileName);
    }
}

void Controller::flushAndClose()
{
    mTextStream.flush();
    mFile.close();
}
