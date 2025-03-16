#include "MyWidget.h"

#include <QDebug>
#include <QPixmap>
#include <QPainter>

MyWidget::MyWidget(QWidget *parent)
    :QWidget(parent)
{
    m_Image.load(":/images/images/WindowIcon.webp");
}

void MyWidget::paintEvent(QPaintEvent *event) {
    if(!m_Image.isNull()) {
        QPainter painter(this);
        const QPixmap scaledImages = m_Image.scaled(size(), Qt::KeepAspectRatio);
        int x = (scaledImages.width() - this->width()) / 2;
        int y = (scaledImages.height() - this->height()) / 2;
        painter.drawPixmap(0, 0, scaledImages, x, y, this->width(), this->height());
    }
    QWidget::paintEvent(event);
}
