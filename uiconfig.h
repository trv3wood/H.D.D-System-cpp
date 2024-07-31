#ifndef UICONFIG_H
#define UICONFIG_H
#include <QWidget>
#include <QPushButton>
#include <QSize>
#include <QFont>
#include <QString>

class ZZZFont
{
public:
    static QString get();
};

class CustomBtn
{
public:
    static void setCustomBtn(QPushButton* btn, const QSize& btnSize, const QString& btnStyle, const QFont& fontName);
    static void playClickSound();
};

class CustomWidget
{
public:
    static QSize adjustSize(QWidget* widget);
};
#endif // UICONFIG_H
