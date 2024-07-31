// #include <cassert>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#endif

#include <QAbstractAnimation>
#include <QApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QFont>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QObject>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QScreen>
#include <QSize>
#include <QSound>
#include <QTimer>
#include <QUrl>

#include "aboutscreen.h"
#include "titlescreen.h"
#include "ui_titlescreen.h"
#include "uiconfig.h"

TitleScreen::TitleScreen(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::TitleScreen),
      m_opacityEffect(nullptr),
      m_opacityAnimation(nullptr),
      m_timer(nullptr),
      m_player(nullptr),
      m_volumeAnimation(nullptr),
      m_aboutScreen(nullptr),
      m_connectScreen(nullptr),
      m_exitScreen(nullptr) {
    ui->setupUi(this);
    initUI();
    // 启动游戏按钮
    connect(ui->pushButton_1, &QPushButton::clicked, this,
            &TitleScreen::jumpToConnectScreen);
    // 打开百科按钮
    connect(ui->pushButton_2, &QPushButton::clicked, this,
            &TitleScreen::openZZZWiki);
    // 关于按钮
    connect(ui->pushButton_3, &QPushButton::clicked, this,
            &TitleScreen::jumpToAboutScreen);
    // 退出按钮
    connect(ui->pushButton_4, &QPushButton::clicked, this,
            &TitleScreen::jumpToExitScreen);
    // 按钮透明度动画
    btnsOpacityEffect();
}

TitleScreen::~TitleScreen() {
    delete ui;
    delete m_player;
    delete m_volumeAnimation;
}

void TitleScreen::btnsOpacityEffect() {
    m_opacityEffect = new QGraphicsOpacityEffect(this);
    m_opacityAnimation = new QPropertyAnimation(m_opacityEffect, "opacity");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setStartValue(0);
    m_opacityAnimation->setEndValue(1);
    ui->layoutWidget->setGraphicsEffect(m_opacityEffect);
    m_timer = new QTimer(this);
    // 按钮透明度动画结束后，开始计时器
    connect(m_opacityAnimation, &QPropertyAnimation::finished, this,
            &TitleScreen::playThemeMusic);
    // 标题延时显示
    connect(m_timer, &QTimer::timeout, this, &TitleScreen::updateLabel);
    m_opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void TitleScreen::updateLabel() {
    static int count = 0;
    static QString title = "欢迎,「法厄同」";
    if (count < title.size()) {
        QString text = ui->label->text().insert(count, title[count]);
        ui->label->setText(text);
        count++;
    } else {
        QObject::disconnect(m_timer, &QTimer::timeout, this,
                            &TitleScreen::updateLabel);
        delete m_timer;
        m_timer = nullptr;
    }
}

void TitleScreen::playThemeMusic() {
    disconnect(m_opacityAnimation, &QPropertyAnimation::finished, this,
               &TitleScreen::playThemeMusic);
    delete m_opacityEffect;
    m_opacityEffect = nullptr;
    m_opacityAnimation = nullptr;
    ui->label->setText("_");
    m_timer->start(500);
    m_player = new QMediaPlayer;
    m_player->setMedia(QUrl("qrc:/res/zzzExplorer.mp3"));
    m_volumeAnimation = new QPropertyAnimation(m_player, "volume");
    // 音量降为0后，重新播放
    connect(m_volumeAnimation, &QPropertyAnimation::finished, this,
            &TitleScreen::rePlayThemeMusic);
    // 音量渐变
    connect(m_player, &QMediaPlayer::stateChanged, this,
            &TitleScreen::louderThemeMusic);
    m_player->play();
}

void TitleScreen::jumpToAboutScreen() {
    if (m_connectScreen) {
        m_connectScreen->hide();
        delete m_connectScreen;
        m_connectScreen = nullptr;
    }
    if (m_exitScreen) {
        m_exitScreen->hide();
        delete m_exitScreen;
        m_exitScreen = nullptr;
    }
    if (!m_aboutScreen) {
        m_aboutScreen = new AboutScreen(this);
    }
    m_aboutScreen->show();
}

void TitleScreen::jumpToConnectScreen() {
    if (m_aboutScreen) {
        m_aboutScreen->hide();
        delete m_aboutScreen;
        m_aboutScreen = nullptr;
    }
    if (m_exitScreen) {
        m_exitScreen->hide();
        delete m_exitScreen;
        m_exitScreen = nullptr;
    }
    if (!m_connectScreen) {
        m_connectScreen = new ConnectScreen(this);
    }
    m_connectScreen->show();
    QTimer::singleShot(5000, this, [this]() {
        m_connectScreen->processConnect();
        m_connectScreen->hide();
    });
}

void TitleScreen::jumpToExitScreen() {
    if (m_aboutScreen) {
        m_aboutScreen->hide();
        delete m_aboutScreen;
        m_aboutScreen = nullptr;
    }
    if (m_connectScreen) {
        m_connectScreen->hide();
        delete m_connectScreen;
        m_connectScreen = nullptr;
    }
    if (!m_exitScreen) {
        m_exitScreen = new ExitScreen(this);
    }
    m_exitScreen->show();
}

void TitleScreen::initUI() {
    // 根据父窗口大小调整控件大小
    QSize screenSize = CustomWidget::adjustSize(this);
    ui->frame->resize(screenSize);
    QSize btnSize(screenSize.width() / 5, screenSize.height() / 25);
    // 设置圆角
    int btnRadius = btnSize.height() / 2;
    QString btnStyle = QString("border-radius: %1px;").arg(btnRadius);
    // 设置按钮字体
    QString fontName = std::move(ZZZFont::get());
    QFont btnFont(fontName, btnSize.height() / 3);
    // 设置按钮样式
    CustomBtn::setCustomBtn(ui->pushButton_1, btnSize, btnStyle, btnFont);
    CustomBtn::setCustomBtn(ui->pushButton_2, btnSize, btnStyle, btnFont);
    CustomBtn::setCustomBtn(ui->pushButton_3, btnSize, btnStyle, btnFont);
    CustomBtn::setCustomBtn(ui->pushButton_4, btnSize, btnStyle, btnFont);
    // 四个按钮放在屏幕左下角
    ui->layoutWidget->setGeometry(btnSize.width() * 0.3,
                                  screenSize.height() - btnSize.height() * 12,
                                  btnSize.width(), btnSize.height() * 6);

    // 设置标题字体
    QFont titleFont(fontName, screenSize.height() / 15);
    ui->label->setFont(titleFont);
    // 标题位置
    ui->label->setGeometry(screenSize.width() * 0.1, screenSize.height() * 0.05,
                           screenSize.width() * 0.8, screenSize.height() / 5);
}

void TitleScreen::openZZZWiki() {
    QDesktopServices::openUrl(QUrl("https://baike.mihoyo.com/zzz/wiki"));
}

void TitleScreen::rePlayThemeMusic() {
    if (m_player->state() == QMediaPlayer::StoppedState) {
        m_player->play();
    }
}

void TitleScreen::louderThemeMusic() {
    // 开始播放后，音量渐趋上升
    m_volumeAnimation->setDuration(5000);
    m_volumeAnimation->setStartValue(0);
    m_volumeAnimation->setEndValue(30);
    m_volumeAnimation->start();
    // 将要结束时，音量渐趋下降
    QTimer::singleShot(48000, this, &TitleScreen::quieterThemeMusic);
}

void TitleScreen::quieterThemeMusic() {
    m_volumeAnimation->setStartValue(30);
    m_volumeAnimation->setEndValue(0);
    m_volumeAnimation->start();
}
