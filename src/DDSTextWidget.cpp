#include "DDSTextWidget.h"

#include "IDL/IDL_TypeSupport.h"

#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

class UDDSSender final: public QObject {
    Q_OBJECT
public:
    explicit UDDSSender(QObject* parent = nullptr) {
        publisherInit();
        m_Timer = new QTimer(this);
        connect(m_Timer, &QTimer::timeout, this, &UDDSSender::sendStringMessage);
    }
    ~UDDSSender() override {
        // ReturnCode_t retcode = StringMessageTypeTypeSupport::delete_data(m_Instance);
        // if (retcode != RETCODE_OK) {
        //     fprintf(stderr, "StringMessageTypeTypeSupport::delete_data error %d\n", retcode);
        // }
        publisherShutdown();
    }
public Q_SLOTS:
    void start() {
        m_Timer->start(500);
        Q_EMIT statusUpdated(1);
    }
    void stop() {
        m_Timer->stop();
        Q_EMIT statusUpdated(0);
    }
private Q_SLOTS:
    void sendStringMessage() {
        static int count = 0;
        m_Instance->message = "hello world";
        InstanceHandle_t instanceHandle = HANDLE_NIL;
        ReturnCode_t retcode = m_StringMessageTypeWriter->write(*m_Instance, instanceHandle);
        if (retcode != RETCODE_OK) {
            fprintf(stderr, "write error %d\n", retcode);
            Q_EMIT dataSent("write error");
        }
        else{
            fprintf(stderr, "%d : write  successfully . . \n", 1);
            Q_EMIT dataSent(m_Instance->message);
        }
    }
Q_SIGNALS:
    void dataSent(const QString& message);
    void statusUpdated(int status);
private:
    int publisherInit() {
        m_Participant = DomainParticipantFactory::get_instance()->create_participant(
0, PARTICIPANT_QOS_DEFAULT,NULL, STATUS_MASK_NONE);
        if (m_Participant == NULL) {
            fprintf(stderr, "create_participant error\n");
            publisherShutdown();
            return -1;
        }

        Publisher* publisher = m_Participant->create_publisher(
        PUBLISHER_QOS_DEFAULT, NULL, STATUS_MASK_NONE);
        if (publisher == NULL) {
            fprintf(stderr, "create_publisher error\n");
            publisherShutdown();
            return -1;
        }

        const char* type_name = StringMessageTypeTypeSupport::get_type_name();
        ReturnCode_t retcode = StringMessageTypeTypeSupport::register_type(m_Participant, type_name);
        if (retcode != RETCODE_OK) {
            fprintf(stderr, "register_type error %ld\n", retcode);
            publisherShutdown();
            return -1;
        }

        Topic* topic = m_Participant->create_topic(
        "Example StringMessageType", type_name, TOPIC_QOS_DEFAULT,
        NULL, STATUS_MASK_NONE);
        if (topic == NULL) {
            fprintf(stderr, "create_topic error\n");
            publisherShutdown();
            return -1;
        }

        DataWriter* writer = publisher->create_datawriter(
            topic , DATAWRITER_QOS_DEFAULT, NULL, STATUS_MASK_NONE);
        if (writer == NULL) {
            fprintf(stderr, "create_datawriter error\n");
            publisherShutdown();
            return -1;
        }

        m_StringMessageTypeWriter = StringMessageTypeDataWriter::narrow(writer);
        if (m_StringMessageTypeWriter == NULL) {
            fprintf(stderr, "DataWriter narrow error\n");
            publisherShutdown();
            return -1;
        }

        m_Instance = StringMessageTypeTypeSupport::create_data();
        if (m_Instance == NULL) {
            fprintf(stderr, "StringMessageTypeTypeSupport::create_data error\n");
            publisherShutdown();
            return -1;
        }


        return 0;
    }

    int publisherShutdown() {
        ReturnCode_t retcode;
        int status = 0;

        if (m_Participant != NULL) {
            retcode = m_Participant->delete_contained_entities();
            if (retcode != RETCODE_OK) {
                fprintf(stderr, "delete_contained_entities error %d\n", retcode);
                status = -1;
            }

            retcode = DomainParticipantFactory::get_instance()->delete_participant(m_Participant);
            if (retcode != RETCODE_OK) {
                fprintf(stderr, "delete_participant error %d\n", retcode);
                status = -1;
            }
        }
        return status;
    }

    QTimer* m_Timer{nullptr};

    StringMessageType* m_Instance{NULL};
    DomainParticipant* m_Participant{NULL};
    StringMessageTypeDataWriter* m_StringMessageTypeWriter{NULL};
};

DDSTextWidget::DDSTextWidget(QWidget* parent)
    :QWidget(parent)
{
    m_TextEdit = new QTextEdit(this);
    m_TextEdit->setReadOnly(true);

    m_Widget = new QWidget(this);
    m_PushButton = new QPushButton(QString::fromUtf8("send"), m_Widget);
    QSpacerItem* spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding);

    QHBoxLayout* layout = new QHBoxLayout(m_Widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_PushButton);
    layout->addSpacerItem(spacerItem);

    QVBoxLayout* aLayout = new QVBoxLayout(this);
    aLayout->setContentsMargins(0, 0, 0, 0);
    aLayout->addWidget(m_Widget, 1);
    aLayout->addWidget(m_TextEdit, 10);

    m_Thread = new QThread(this);
    m_Sender = new UDDSSender();
    m_Sender->moveToThread(m_Thread);
    m_Thread->start();

    connect(m_PushButton, &QPushButton::clicked, this, [this](bool on) {
        Q_UNUSED(on);
        if (sendStatus) {
            Q_EMIT stopSending();
            m_PushButton->setText("send");
        }
        else {
            Q_EMIT startSending();
            m_PushButton->setText("stop");
        }
        sendStatus = !sendStatus;
    });
    connect(m_Sender, &UDDSSender::dataSent, this, &DDSTextWidget::updateSendText, Qt::QueuedConnection);
    connect(m_Sender, &UDDSSender::statusUpdated, this, &DDSTextWidget::updateStatusText, Qt::QueuedConnection);
    connect(this, &DDSTextWidget::startSending, m_Sender, &UDDSSender::start, Qt::QueuedConnection);
    connect(this, &DDSTextWidget::stopSending, m_Sender, &UDDSSender::stop, Qt::QueuedConnection);
}

DDSTextWidget::~DDSTextWidget() {
    m_Thread->quit();
    m_Thread->wait();
    Q_EMIT stopSending();
    delete m_Sender;
}

void DDSTextWidget::updateSendText(const QString& message) {
    m_TextEdit->append(message);
}

void DDSTextWidget::updateStatusText(int status) {
    if (status)
        m_TextEdit->append("start");
    else
        m_TextEdit->append("stop");
}


#include "DDSTextWidget.moc"
