#ifndef EXITSCREEN_H
#define EXITSCREEN_H

#include <QWidget>

namespace Ui {
class ExitScreen;
}

class ExitScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ExitScreen(QWidget *parent = nullptr);
    ~ExitScreen();

private:
    Ui::ExitScreen *ui;
    void initUI();
};

#endif // EXITSCREEN_H
