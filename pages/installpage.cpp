#include "installpage.h"
#include "../installer/localpackageinstaller.h"
#include <QMessageBox>
#include <QErrorMessage>

InstallPage::InstallPage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    comboBox = new QComboBox(this);
    comboBox->addItem("postgresql");
    comboBox->addItem("wine");
    comboBox->addItem("slapd");
    comboBox->setCurrentIndex(0);
    layout->addStretch();
    layout->addWidget(comboBox);
    layout->addStretch();

    installer = new LocalPackageInstaller(this);
}

QWidget* InstallPage::widget() {
    return this;
}

void InstallPage::onShow() {
    comboBox->setFocus();
}

void InstallPage::startInstallation() {
    QString selected = comboBox->currentText();
    bool ok = installer->install(selected);
    if (ok) {
        QMessageBox::information(this, "Установка", "Успешно установлено: " + selected);
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось установить: " + selected);
    }
}
