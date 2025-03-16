#pragma once

#include <QWidget>

class QPixMap;

class MyWidget final: public QWidget{
public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget() override = default;
    void paintEvent(QPaintEvent *event) override;
private:
    QPixmap m_Image;
};
