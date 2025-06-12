#include "localpackageinstaller.h"
#include <QProcess>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

LocalPackageInstaller::LocalPackageInstaller(QObject *parent)
    : QObject(parent) {}

bool LocalPackageInstaller::install(const QString &packageId) {
    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/installer_temp";
    QDir().mkpath(tempDir);

    QString resourcePath = ":/packages/" + packageId + ".tar.gz";
    QString localArchive = tempDir + "/" + packageId + ".tar.gz";

    QFile file(resourcePath);
    if (!file.exists() || !file.copy(localArchive)) {
        return false;
    }

    QProcess proc;
    proc.setWorkingDirectory(tempDir);
    proc.start("tar", QStringList() << "-xzf" << localArchive);
    proc.waitForFinished();

    QString installScript = tempDir + "/" + packageId + "/install.sh";
    if (!QFile::exists(installScript)) {
        return false;
    }

    proc.start("bash", QStringList() << installScript);
    proc.waitForFinished();
    qDebug() << "Trying to extract:" << resourcePath;
    qDebug() << "Copy to:" << localArchive;
    qDebug() << "Unpacking to:" << tempDir;
    qDebug() << "Running: tar -xzf" << localArchive;

    qDebug() << "Running: bash" << installScript;

    return proc.exitCode() == 0;
}
