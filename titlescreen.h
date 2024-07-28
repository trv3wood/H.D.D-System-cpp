#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "aboutscreen.h"
#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

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

    void initUI();
    void btnsOpacityEffect();
    void updateLabel();
    void playThemeMusic();
    void jumpToAboutScreen();
    bool tryLauchZZZGame();
};

#endif  // TITLESCREEN_H
