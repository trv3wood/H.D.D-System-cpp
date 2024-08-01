#include <QApplication>
#include <QFontDatabase>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QScreen>
#include <QString>
#include <QTextEdit>
#include <QTimer>
// #include <cassert>
#include <chrono>
#include <cstddef>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

#include "code.h"
#include "mainwindow.h"
#include "sysinfo.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_timer(new QTimer(this)),
      m_sysinfo(new SYSinfo()),
      m_effect(nullptr),
      m_animation(nullptr),
      m_label(nullptr),
      m_titlescreen(nullptr),
      m_codePrintStream(std::move(HDD_CODE)) {
    ui->setupUi(this);
    this->setWindowTitle("H.D.D System");

    // 获取屏幕大小
    QSize screen_size = QApplication::screens().at(0)->size();
    // 设置窗口大小
    this->showFullScreen();
    this->centralWidget()->resize(screen_size);

    // 设置文本框
    QFont font("Microsoft Yahei", 14);
    ui->textEdit->setFont(font);
    ui->textEdit->setStyleSheet("color: white;");
    ui->textEdit->setAlignment(Qt::AlignLeft);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->resize(screen_size * 0.9);
    ui->textEdit->setFrameShape(QFrame::NoFrame);

    // 将定时器绑定到自检更新函数
    connect(m_timer, &QTimer::timeout, this, &MainWindow::selfTestUpdate);
    // 将自检完成信号绑定到加载启动画面函数
    connect(this, &MainWindow::bootCompleted, this,
            &MainWindow::loadBootScreen);
    // 启动定时器
    m_timer->start(700);
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_titlescreen;
    // assert(m_sysinfo == nullptr);
    // assert(m_effect == nullptr);
    // assert(m_animation == nullptr);
    // assert(m_label == nullptr);
    // assert(m_timer == nullptr);
}

void MainWindow::selfTestUpdate() {
    QTextEdit *textEdit = ui->textEdit;
    static size_t count = 0;
    if (count < m_sysinfo->m_data.size()) {
        // 显示系统信息
        textEdit->append(m_sysinfo->m_data[count].c_str());
        // 更新索引
        count++;
        return;
    }
    // 如果索引超出范围，停止定时器，开始打印代码
    disconnect(m_timer, &QTimer::timeout, this, &MainWindow::selfTestUpdate);
    delete m_sysinfo;
    m_sysinfo = nullptr;
    textEdit->clear();
    // 将定时器绑定到代码打印更新函数
    connect(m_timer, &QTimer::timeout, this, &MainWindow::codePrintUpdate);
    // 启动定时器
    m_timer->start(100);
}

void MainWindow::codePrintUpdate() {
    QTextEdit *textEdit = ui->textEdit;
    std::string buf;
    // 逐行打印代码
    if (std::getline(m_codePrintStream, buf)) {
        textEdit->append(buf.c_str());
    } else {
        // 打印完成后，停止定时器，等待0.5秒后发出启动完成信号
        disconnect(m_timer, &QTimer::timeout, this,
                   &MainWindow::codePrintUpdate);
        delete m_timer;
        m_timer = nullptr;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        emit bootCompleted();
    }
}

void MainWindow::loadBootScreen() {
    disconnect(this, &MainWindow::bootCompleted, this, &MainWindow::loadBootScreen);
    ui->textEdit->hide();
    // 设置启动画面
    m_label = new QLabel(this);
    QPixmap bootScreen(":/res/bootScreen.png");
    bootScreen = bootScreen.scaled(this->size(), Qt::KeepAspectRatio,
                                   Qt::SmoothTransformation);
    m_label->setPixmap(bootScreen);
    m_label->setScaledContents(true);
    m_label->resize(this->size());
    m_label->show();

    // 淡入图片动画
    fadeIn();

    // 淡出图片动画
    QTimer::singleShot(5000, this, &MainWindow::fadeOut);
}

void MainWindow::loadTitleScreen() {
    disconnect(m_animation, &QPropertyAnimation::finished, this, &MainWindow::loadTitleScreen);
    delete m_animation;
    delete m_effect;
    delete m_label;
    m_animation = nullptr;
    m_effect = nullptr;
    m_label = nullptr;
    m_titlescreen = new TitleScreen(this);
    m_titlescreen->show();
    this->centralWidget()->hide();
}

void MainWindow::fadeOut() {
    connect(m_animation, &QPropertyAnimation::finished, this,
            &MainWindow::loadTitleScreen);
    m_animation->setDuration(3000);
    m_animation->setStartValue(1);
    m_animation->setEndValue(0);
    m_animation->start();
}

void MainWindow::fadeIn() {
    m_effect = new QGraphicsOpacityEffect(this);
    m_label->setGraphicsEffect(m_effect);
    m_animation = new QPropertyAnimation(m_effect, "opacity");
    m_animation->setDuration(3000);
    m_animation->setStartValue(0);
    m_animation->setEndValue(1);
    m_animation->start();
}
