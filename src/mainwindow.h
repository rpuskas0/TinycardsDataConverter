#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

#include "ui_mainwindow.h"


class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


private slots:
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionStart_triggered();

    void on_openButton_clicked();
    void on_startButton_clicked();

    void on_deckBreakCBox_currentIndexChanged(int index);
    void on_fileFormatCBox_currentIndexChanged(int index);


private:
    Controller controller;

    void correctFileExtension(QString& fileName);
    void loadDeckData();
    void customizeUi();
    QString genFileFilterString() const;
    bool hasExtension(const QString& fileName);
    void startConversion();
};

#endif // MAINWINDOW_H
