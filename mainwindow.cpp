#include "mainwindow.h"
#include "pages/namepage.h"
#include "pages/installpage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    pages.append(new NamePage(this));
    pages.append(new InstallPage(this));

    for (auto *page : pages) {
        pageStack->addWidget(page->widget());
    }

    pages[0]->onShow();
    updateNavigation();
}

MainWindow::~MainWindow() {
    // удалять страницы не нужно — Qt удалит по иерархии родителя
}

void MainWindow::setupUI() {
    mainWidget = new QWidget(this);
    this->setCentralWidget(mainWidget);

    pageStack = new QStackedWidget(this);
    nextButton = new QPushButton("Далее", this);
    backButton = new QPushButton("Назад", this);
    backButton->setVisible(false);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(backButton);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(nextButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(pageStack);
    mainLayout->addLayout(buttonsLayout);

    connect(nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(backButton, &QPushButton::clicked, this, &MainWindow::onBackClicked);
}

void MainWindow::onNextClicked() {
    pages[currentPageIndex]->onHide();

    if (currentPageIndex + 1 < pages.size()) {
        currentPageIndex++;
        pages[currentPageIndex]->onShow();
        pageStack->setCurrentIndex(currentPageIndex);
        updateNavigation();
    } else {
        auto *installPage = dynamic_cast<InstallPage *>(pages.last());
        if (installPage) {
            installPage->startInstallation();
        }
    }
}

void MainWindow::onBackClicked() {
    if (currentPageIndex > 0) {
        pages[currentPageIndex]->onHide();
        currentPageIndex--;
        pages[currentPageIndex]->onShow();
        pageStack->setCurrentIndex(currentPageIndex);
        updateNavigation();
    }
}

void MainWindow::updateNavigation() {
    backButton->setVisible(currentPageIndex > 0);
    if (currentPageIndex == pages.size() - 1) {
        nextButton->setText("Установить");
    } else {
        nextButton->setText("Далее");
    }
}
