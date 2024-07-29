#include "aboutscreen.h"
#include "ui_aboutscreen.h"
#include <QApplication>
#include <QFontDatabase>
#include <QSound>
#include <QPushButton>
#include <QScreen>

AboutScreen::AboutScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutScreen)
{
    ui->setupUi(this);
    initUI();
    connect(ui->pushButton_1, &QPushButton::clicked, this, &AboutScreen::showMoreInfo);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &AboutScreen::backToTitleScreen);
}

AboutScreen::~AboutScreen()
{
    disconnect(ui->pushButton_1, &QPushButton::clicked, this, &AboutScreen::showMoreInfo);
    disconnect(ui->pushButton_2, &QPushButton::clicked, this, &AboutScreen::backToTitleScreen);
    disconnect(ui->pushButton_1, &QPushButton::clicked, this, &AboutScreen::playClickSound);
    disconnect(ui->pushButton_2, &QPushButton::clicked, this, &AboutScreen::playClickSound);
    delete ui;
}

void AboutScreen::initUI() {
// 根据父窗口大小调整控件大小
    QSize screenSize;
    if (this->parentWidget()) {
        screenSize = parentWidget()->size();
    } else {
        screenSize = QApplication::screens().at(0)->size();
    }
    this->resize(screenSize);
    ui->frame->resize(screenSize);
    ui->layoutWidget->setGeometry(screenSize.width() * 0.25, screenSize.height() * 0.2,
                                  screenSize.width() * 0.5, screenSize.height() * 0.5);
    ui->label->resize(screenSize.width() * 0.3, screenSize.height() * 0.1);
    ui->label_2->resize(screenSize.width() * 0.3, screenSize.height() * 0.3);

    QSize btnSize(screenSize.width() / 5, screenSize.height() / 25);
    // 设置圆角
    int radius = btnSize.height() / 2;
    QString btnStyle = QString("border-radius: %1px;").arg(radius);
    // 设置按钮字体
    int fontID = QFontDatabase::addApplicationFont(":/res/zzzfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont btnFont(fontName, btnSize.height() / 3);
    // 设置按钮样式
    ui->pushButton_1->setFixedSize(btnSize);
    ui->pushButton_1->setFont(btnFont);
    ui->pushButton_1->setStyleSheet(btnStyle);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &AboutScreen::playClickSound);
    ui->pushButton_2->setFixedSize(btnSize);
    ui->pushButton_2->setFont(btnFont);
    ui->pushButton_2->setStyleSheet(btnStyle);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &AboutScreen::playClickSound);

    ui->label->setFont(QFont(fontName, btnSize.height()));
    ui->label_2->setFont(QFont(fontName, btnSize.height() / 3));
    ui->label_3->setFont(QFont(fontName, btnSize.height() / 3));
    ui->label_3->hide();
}

void AboutScreen::backToTitleScreen() {
    if (ui->label_3->isVisible()) {
        ui->label_3->hide();
        ui->pushButton_1->show();
        return;
    }
    this->hide();
}

void AboutScreen::showMoreInfo() {
    // html 作者b站主页 作者
    ui->label_3->setOpenExternalLinks(true);
    ui->label_3->setText("<p>作者：混沌之人1823</p>"
                         "<a href='https://space.bilibili.com/433370534'>"
                         "作者b站主页</a>");
    ui->label_3->show();
    ui->pushButton_1->hide();
}

void AboutScreen::playClickSound() {
    QSound::play(":/res/click.wav");
}