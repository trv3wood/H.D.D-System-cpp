#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsEffect>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QTextEdit>
#include <sstream>

#include "sysinfo.h"
#include "titlescreen.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QTimer* m_timer = nullptr;
    SYSinfo* m_sysinfo = nullptr;
    // QPixmap* m_bootScreen = nullptr;
    QGraphicsOpacityEffect* m_effect = nullptr;
    QPropertyAnimation* m_animation = nullptr;
    QLabel* m_label = nullptr;
    TitleScreen* m_titlescreen = nullptr;
    std::stringstream m_codePrintStream;

    void selfTestUpdate();
    void codePrintUpdate();
    void loadBootScreen();
    void loadTitleScreen();
    void fadeOut();
    void fadeIn();
signals:
    void bootCompleted();
    // void animationFinished();
};
#endif  // MAINWINDOW_H
