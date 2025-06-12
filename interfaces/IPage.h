#ifndef IPAGE_H
#define IPAGE_H

#include <QWidget>

class IPage {
public:
    virtual QWidget* widget() = 0;
    virtual void onShow() {}
    virtual void onHide() {}
    virtual ~IPage() = default;
};

#endif // IPAGE_H
