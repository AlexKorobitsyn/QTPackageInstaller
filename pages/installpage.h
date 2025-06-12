#ifndef INSTALLPAGE_H
#define INSTALLPAGE_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include "../interfaces/IPage.h"
#include "../installer/IPackageInstaller.h"

class InstallPage : public QWidget, public IPage {
    Q_OBJECT

public:
    explicit InstallPage(QWidget *parent = nullptr);
    QWidget* widget() override;
    void onShow() override;
    void startInstallation();

private:
    QComboBox *comboBox;
    IPackageInstaller *installer;
};

#endif
