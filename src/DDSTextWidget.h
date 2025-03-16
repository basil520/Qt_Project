#pragma once

#include <QWidget>

class StringMessageType;
class DomainParticipant;
class StringMessageTypeDataWriter;

class QThread;
class QTextEdit;
class QPushButton;

class UDDSSender;

class DDSTextWidget final: public QWidget{
    Q_OBJECT
public:
    explicit DDSTextWidget(QWidget* parent = nullptr);
    ~DDSTextWidget() override;
Q_SIGNALS:
    void startSending();
    void stopSending();
private Q_SLOTS:
    void updateSendText(const QString& message);
    void updateStatusText(int status);
private:
    int sendStatus{0};

    UDDSSender* m_Sender{nullptr};

    QThread* m_Thread{nullptr};
    QWidget* m_Widget{nullptr};
    QTextEdit* m_TextEdit{nullptr};
    QPushButton* m_PushButton{nullptr};
};
