#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVector>
#include "interfaces\IPage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNextClicked();
    void onBackClicked();

private:
    QWidget *mainWidget;
    QStackedWidget *pageStack;
    QPushButton *nextButton;
    QPushButton *backButton;

    QVector<IPage*> pages;
    int currentPageIndex = 0;

    void setupUI();
    void updateNavigation();
};

#endif // MAINWINDOW_H
