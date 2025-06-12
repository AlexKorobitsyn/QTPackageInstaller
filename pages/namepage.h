#ifndef NAMEPAGE_H
#define NAMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "../interfaces/IPage.h"

class NamePage : public QWidget, public IPage {
    Q_OBJECT

public:
    explicit NamePage(QWidget *parent = nullptr);
    QWidget* widget() override;
};

#endif // NAMEPAGE_H
