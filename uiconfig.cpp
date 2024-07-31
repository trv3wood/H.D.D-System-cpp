#include <QApplication>
#include <QFontDatabase>
#include <QPushButton>
#include <QScreen>
#include <QSound>

#include "uiconfig.h"


QString ZZZFont::get() {
    int fontID = QFontDatabase::addApplicationFont(":/res/zzzfont.ttf");
    return QFontDatabase::applicationFontFamilies(fontID).at(0);
}

void CustomBtn::setCustomBtn(QPushButton* btn, const QSize& btnSize,
                             const QString& btnStyle, const QFont& fontName) {
    btn->setFixedSize(btnSize);
    btn->setFont(fontName);
    btn->setStyleSheet(btnStyle);
    QAbstractButton::connect(btn, &QPushButton::clicked,
                             &CustomBtn::playClickSound);
}

void CustomBtn::playClickSound() { QSound::play(":/res/click.wav"); }

QSize CustomWidget::adjustSize(QWidget* widget) {
    QSize screenSize;
    screenSize = QApplication::screens().at(0)->size();
    widget->resize(screenSize);
    return screenSize;
}