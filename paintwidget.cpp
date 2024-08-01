#include "paintwidget.h"
#include <QPainter>
#include "uiconfig.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), m_startAngle(0), m_timer(new QTimer(this)) {
    initUI();
    m_timer->start(100);
    connect(m_timer, &QTimer::timeout, this, &PaintWidget::repaintCircle);
}

void PaintWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(QColorConstants::Svg::deepskyblue, 5));
    const int radius = 50;
    QRect rectangle(this->width() / 2 - radius, this->height() / 2 - radius,
                    2 * radius, 2 * radius);
    painter.drawArc(rectangle, m_startAngle * 16, 270 * 16);
}

void PaintWidget::repaintCircle() {
    update(); // Request a repaint
    m_startAngle += 30;
    if (m_startAngle >= 360) {
        m_startAngle = 0;
    }
}

void PaintWidget::initUI() {
    CustomWidget::adjustSize(this);
}
