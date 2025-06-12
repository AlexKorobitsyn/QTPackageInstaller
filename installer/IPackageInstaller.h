#ifndef IPACKAGEINSTALLER_H
#define IPACKAGEINSTALLER_H

#include <QString>

class IPackageInstaller {
public:
    virtual bool install(const QString &packageId) = 0;
    virtual ~IPackageInstaller() = default;
};

#endif // IPACKAGEINSTALLER_H
