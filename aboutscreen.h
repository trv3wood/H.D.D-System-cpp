#ifndef ABOUTSCREEN_H
#define ABOUTSCREEN_H

#include <QObject>
#include <QWidget>

namespace Ui {
class AboutScreen;
}

class AboutScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AboutScreen(QWidget *parent = nullptr);
    ~AboutScreen();

private:
    Ui::AboutScreen *ui;
    void initUI();
    void backToTitleScreen();
    void showMoreInfo();
};

#endif // ABOUTSCREEN_H
