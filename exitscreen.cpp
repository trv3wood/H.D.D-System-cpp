#include <QSize>
#include <QApplication>
#include <QDebug>

#include "exitscreen.h"
#include "ui_exitscreen.h"
#include "uiconfig.h"


ExitScreen::ExitScreen(QWidget *parent)
    : QWidget(parent), ui(new Ui::ExitScreen) {
    ui->setupUi(this);
    initUI();
    connect(ui->cancelBtn, &QPushButton::clicked, this, &ExitScreen::close);
    connect(ui->exitBtn, &QPushButton::clicked, this, QApplication::quit);
}

ExitScreen::~ExitScreen() {
    delete ui;
}

void ExitScreen::initUI() {
    QSize screenSize = CustomWidget::adjustSize(this);
    ui->frame->resize(screenSize);
    ui->widget->setGeometry(screenSize.width() * 0.25, screenSize.height() * 0.2,
        screenSize.width() * 0.5, screenSize.height() * 0.5);
    ui->label->setGeometry(screenSize.width() * 0.3, screenSize.height() * 0.3,
                           screenSize.width() * 0.2, screenSize.height() * 0.2);
    QString fontName = std::move(ZZZFont::get());
    QSize btnSize(screenSize.width() / 6, screenSize.height() / 25);
    int btnRadius = btnSize.height() / 2;
    QString btnStyle = QString("border-radius: %1px;").arg(btnRadius);
    QFont btnFont(fontName, btnSize.height() / 3);
    CustomBtn::setCustomBtn(ui->cancelBtn, btnSize, btnStyle, btnFont);
    CustomBtn::setCustomBtn(ui->exitBtn, btnSize, btnStyle, btnFont);
    ui->cancelBtn->setText("取消");
    ui->exitBtn->setText("退出");
    QFont titleFont(fontName, screenSize.height() / 25);
    ui->label->setFont(titleFont);
}
