#ifndef LOCALPACKAGEINSTALLER_H
#define LOCALPACKAGEINSTALLER_H

#include "IPackageInstaller.h"
#include <QObject>

class LocalPackageInstaller : public QObject, public IPackageInstaller {
    Q_OBJECT

public:
    explicit LocalPackageInstaller(QObject *parent = nullptr);
    bool install(const QString &packageId) override;
};

#endif // LOCALPACKAGEINSTALLER_H
