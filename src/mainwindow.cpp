#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <exception>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    customizeUi();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "This is a simple program for converting Duolingo's\n"
                                      "Tinycards csv document to a more convenient format.\n\n"
                                      "Licensed under GPLv3\n"
                                      "Copyright (C) Robert Puskas");
}

void MainWindow::on_actionOpen_triggered()
{
    loadDeckData();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
void MainWindow::on_actionStart_triggered()
{
    startConversion();
}

void MainWindow::on_openButton_clicked()
{
    loadDeckData();
}

void MainWindow::on_startButton_clicked()
{
    startConversion();
}

void MainWindow::on_deckBreakCBox_currentIndexChanged(int index)
{
    controller.selectOutputOption(index);
}

void MainWindow::on_fileFormatCBox_currentIndexChanged(int index)
{
    controller.selectOutputFilter(index);
}

void MainWindow::correctFileExtension(QString& fileName)
{
    if (fileName.isEmpty()) return;
    if (!hasExtension(fileName)) {
        fileName.append('.' + controller.getOutFileExtension());
    }
}

void MainWindow::loadDeckData()
{
    mainStatusBar->showMessage("Select a file to open");
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open file",
                                                    QDir::homePath(),
                                                    "Tinycards CSV (*.csv)");
    try {
        controller.loadDeckDataFromFile(fileName);
        mainStatusBar->showMessage("File opened and parsed successfully");
    }  catch (std::runtime_error& err) {
        QMessageBox::warning(this, "An error occured", err.what());
        mainStatusBar->showMessage("Error");
    }

}

void MainWindow::customizeUi()
{
    mainStatusBar->showMessage("Welcome");
    deckBreakCBox->addItems({"1 File / All decks", "1 File / 1 Deck"});
    fileFormatCBox->addItems({"JSON file", "XML file", "CSV file"});
}

QString MainWindow::genFileFilterString() const
{
    return controller.getOutFileTypeName() + " (*." + controller.getOutFileExtension() + ")";
}

bool MainWindow::hasExtension(const QString& fileName)
{
    return fileName.endsWith('.' + controller.getOutFileExtension(), Qt::CaseInsensitive);
}

void MainWindow::startConversion()
{
    mainStatusBar->showMessage("Select file to save data to");
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save file",
                                                    QDir::homePath(),
                                                    genFileFilterString());
    correctFileExtension(fileName);

    try {
        controller.startConversion(fileName);
        mainStatusBar->showMessage("Data converted successfully");
    }  catch (std::runtime_error& err) {
        QMessageBox::warning(this, "An error occured", err.what());
        mainStatusBar->showMessage("Error");
    }


}
