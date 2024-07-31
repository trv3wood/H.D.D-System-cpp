#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#endif
#include <QColor>
#include <QMessageBox>
#include <QPainter>
#include <QScreen>
#include <QTimer>

#include "connectscreen.h"
#include "ui_connectscreen.h"
#include "uiconfig.h"

ConnectScreen::ConnectScreen(QWidget *parent)
    : QWidget(parent), ui(new Ui::connectScreen) {
    ui->setupUi(this);
    QSize screenSize = CustomWidget::adjustSize(this);
    ui->frame->resize(screenSize);
    this->m_paintWidget = new PaintWidget(ui->frame);
    this->m_paintWidget->resize(screenSize);
    int labelPointSize = screenSize.height() / 20;
    ui->label->setFont(QFont(ZZZFont::get(), labelPointSize));
    ui->label->setStyleSheet("color: white;");
    ui->label->setText("正在与邦布建立连接...");
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->resize(screenSize.width() * 0.8, screenSize.height() / 5);
}

ConnectScreen::~ConnectScreen() {
    delete ui;
    delete m_paintWidget;
}

// 查找米哈游启动器
// 查找注册表项
// 计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\HYP_1_1_cn\DisplayIcon
// 如果存在，则启动游戏
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
bool ConnectScreen::tryLauchZZZGame() {
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"
                     "HYP_1_1_cn",
                     0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        char path[MAX_PATH];
        DWORD size = sizeof(path);
        RegQueryValueEx(hKey, "DisplayIcon", NULL, NULL, (LPBYTE)path, &size);
        RegCloseKey(hKey);
        // 启动游戏
        ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);
        return true;
    }
    return false;
}

void ConnectScreen::processConnect() {
    bool result = this->tryLauchZZZGame();
    if (!result) {
        QMessageBox::warning(this, "提示", "未找到米哈游启动器");
    }
}
#else
bool ConnectScreen::tryLauchZZZGame() {
    QMessageBox::information(
        this, "操作系统不支持",
        "<font size='12' color='white'>无法启动绝区零</font>");
    return false;
}
void ConnectScreen::processConnect() { this->tryLauchZZZGame(); }
#endif
