#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QTimer>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
private:
    void initUI();
    int m_startAngle = 0;
    QTimer* m_timer;
    void paintEvent(QPaintEvent *event);
    void repaintCircle();

signals:
};

#endif // PAINTWIDGET_H
