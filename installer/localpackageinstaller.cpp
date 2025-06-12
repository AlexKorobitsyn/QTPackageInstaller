#include "localpackageinstaller.h"
#include <QProcess>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <QMessageBox>

LocalPackageInstaller::LocalPackageInstaller(QObject *parent)
    : QObject(parent) {}

bool LocalPackageInstaller::install(const QString &packageId) {
    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/installer_temp_" + packageId;
    QDir().mkpath(tempDir);

    QString resourcePath = "../resources/" + packageId + ".tar.gz";
    QString localArchive = tempDir + "/" + packageId + ".tar.gz";

    qDebug() << "📦 Resource:" << resourcePath;
    qDebug() << "📦 Copying to:" << localArchive;

    QFile file(resourcePath);
    if (!file.exists()) {
        QMessageBox::critical(nullptr, "Ошибка", "Файл ресурса не найден: " + resourcePath);
        return false;
    }

    if (!file.copy(localArchive)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось скопировать в temp: " + localArchive);
        return false;
    }

    QProcess unpack;
    unpack.setWorkingDirectory(tempDir);
    unpack.start("tar", QStringList() << "-xzf" << localArchive);
    unpack.waitForFinished();
    qDebug() << "📂 tar stdout:" << unpack.readAllStandardOutput();
    qDebug() << "📂 tar stderr:" << unpack.readAllStandardError();

    QString installScript = tempDir + "/" + packageId + "/install.sh";
    if (!QFile::exists(installScript)) {
        QMessageBox::critical(nullptr, "Ошибка", "Файл install.sh не найден: " + installScript);
        return false;
    }

    QProcess installer;
    installer.setWorkingDirectory(tempDir + "/" + packageId);
    installer.start("bash", QStringList() << "install.sh");
    installer.waitForFinished();

    QString out = installer.readAllStandardOutput();
    QString err = installer.readAllStandardError();

    qDebug() << "🛠️ install stdout:" << out;
    qDebug() << "🛠️ install stderr:" << err;

    if (installer.exitCode() != 0) {
        QMessageBox::critical(nullptr, "Установка не удалась", err.isEmpty() ? out : err);
        return false;
    }

    return true;
}
