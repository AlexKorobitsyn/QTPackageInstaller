#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Установщик пакетов");
    window.resize(600, 400);
    window.show();

    return app.exec();
}
