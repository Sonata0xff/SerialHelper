#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTextEdit>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QPalette>
#include <QCheckBox>
#include <QSpinBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QThread>
#include <QMutex>
QT_BEGIN_NAMESPACE
namespace Ui {
class serialHelper;
}
QT_END_NAMESPACE
class Model;
class Controller;
struct InitParam;
typedef struct InitParam InitParam;
struct RunParam;
typedef struct RunParam RunParam;
class serialHelper : public QMainWindow
{
    Q_OBJECT

public:
    serialHelper(QWidget *parent = nullptr);
    ~serialHelper();
    void paintEvent(QPaintEvent *event) override;
    void ChangeStatus(std::string status);
    bool FunctionInit(InitParam* param);
    void closeEvent(QCloseEvent * e) override;

private:
    Ui::serialHelper *ui;
    std::shared_ptr<QTextEdit> reciver;
    std::shared_ptr<QTextEdit> sender;
    std::shared_ptr<QLabel> sendContext;
    std::shared_ptr<QLabel> recvContext;

    std::shared_ptr<QLabel> serialConfigTitle;
    std::shared_ptr<QLabel> reciveTitle;
    std::shared_ptr<QLabel> sendTitle;

    std::shared_ptr<QLabel> portNumber;
    std::shared_ptr<QLabel> portBandBit;
    std::shared_ptr<QLabel> portDataBit;
    std::shared_ptr<QLabel> portStopBit;
    std::shared_ptr<QLabel> portCheckBit;
    std::shared_ptr<QPushButton> portCheckPort;
    std::shared_ptr<QPushButton> portStartPort;
    std::shared_ptr<QPushButton> portStopPort;


    std::shared_ptr<QPushButton> reciveClear;
    std::shared_ptr<QPushButton> sendClear;
    std::shared_ptr<QPushButton> sendOut;

    std::shared_ptr<QComboBox> portNumberC;
    std::shared_ptr<QComboBox> portBandBitC;
    std::shared_ptr<QComboBox> portDataBitC;
    std::shared_ptr<QComboBox> portStopBitC;
    std::shared_ptr<QComboBox> portCheckBitC;

    std::shared_ptr<QLabel> hexGet;
    std::shared_ptr<QCheckBox> hexGetC;
    std::shared_ptr<QLabel> rowAutoChange;
    std::shared_ptr<QCheckBox> rowAutoChangeC;
    std::shared_ptr<QLabel> reciveDivideChar;
    std::shared_ptr<QTextEdit> reciveDivideCharC;

    std::shared_ptr<QLabel> hexSend;
    std::shared_ptr<QCheckBox> hexSendC;
    std::shared_ptr<QLabel> sendDivideChar;
    std::shared_ptr<QTextEdit> sendDivideCharC;
    std::shared_ptr<QLabel> autoSend;
    std::shared_ptr<QCheckBox> autoSendC;
    std::shared_ptr<QLabel> ms;
    std::shared_ptr<QSpinBox> spin;

    std::shared_ptr<QLabel> statusCon;
    std::shared_ptr<QLabel> statusRes;

    QPalette palette;
    InitParam* param_;
private:
    //serial config
    std::string portName;
    std::string BaudRate;
    std::string DataSize;
    std::string stopBit;
    std::string CheckBit;

    //receive config
    bool getHex;
    bool autoChange;
    char recDivideChar;

    //send config
    bool sendHex;
    char senDivideChar;
    bool autoSend_;
    int msDelay;

public slots:
    void StartSerialFunc();
    void StopSerialFunc();
    void ReciveSectorClear();
    void SendSectorClear();
    void CheckPortNumber();
signals:
    bool InitSignal(InitParam* param);
    bool PortNumberRequest(std::shared_ptr<QStringList> ret);
    void PortNumberRequestReturn(bool ret);
};

#endif // SERIALHELPER_H
