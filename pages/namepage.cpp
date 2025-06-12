#include "..\pages\namepage.h"

NamePage::NamePage(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Коробицын", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(label);
    layout->addStretch();
}

QWidget* NamePage::widget() {
    return this;
}
