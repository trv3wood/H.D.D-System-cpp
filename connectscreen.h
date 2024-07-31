#ifndef CONNECTSCREEN_H
#define CONNECTSCREEN_H

#include <QPainter>
#include <QWidget>

#include "paintwidget.h"


namespace Ui {
class connectScreen;
}

class ConnectScreen : public QWidget {
    Q_OBJECT

public:
    explicit ConnectScreen(QWidget *parent = nullptr);
    ~ConnectScreen();
    void processConnect();

private:
    Ui::connectScreen *ui;
    PaintWidget *m_paintWidget;
    bool tryLauchZZZGame();
};

#endif  // CONNECTSCREEN_H
