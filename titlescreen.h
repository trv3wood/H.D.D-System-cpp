#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "aboutscreen.h"
#include "connectscreen.h"
#include "exitscreen.h"


namespace Ui {
class TitleScreen;
}

class TitleScreen : public QWidget {
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = nullptr);
    ~TitleScreen();

private:
    Ui::TitleScreen *ui;
    QGraphicsOpacityEffect *m_opacityEffect;
    QPropertyAnimation *m_opacityAnimation;
    QTimer *m_timer;
    QMediaPlayer *m_player;
    QPropertyAnimation *m_volumeAnimation;
    AboutScreen *m_aboutScreen;
    ConnectScreen *m_connectScreen;
    ExitScreen *m_exitScreen;

    void initUI();
    void btnsOpacityEffect();
    void updateLabel();
    void playThemeMusic();
    void jumpToAboutScreen();
    void jumpToConnectScreen();
    bool tryLauchZZZGame();
    void openZZZWiki();
    void jumpToExitScreen();
    void rePlayThemeMusic();
    void louderThemeMusic();
    void quieterThemeMusic();
};

#endif  // TITLESCREEN_H
