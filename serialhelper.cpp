#include "serialhelper.h"
#include "./ui_serialhelper.h"
#include "windowConfig.h"
//global param mutex, uesd for multi process
namespace ProcessParam {
QMutex StatusTex_;
}
//global recive param mutex, uesd for multi process
namespace ReceiveProcessParam {
QMutex recTextTex_;
} //global send param mutex, uesd for multi process
namespace SendProcessParam {
QMutex senTextTex_;
QMutex startSendTex_;
}
serialHelper::serialHelper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::serialHelper)
{
    ui->setupUi(this);
    this->setFixedSize(winConfig::win_width, winConfig::win_higth);
    //textBox init
    this->reciver = std::make_shared<QTextEdit>(this);
    this->reciver->setReadOnly(true);
    this->reciver->resize(winConfig::textBlockwidth, winConfig::textBlockHigth);
    this->reciver->move(winConfig::textBlockstartPosX,
                        winConfig::textBlockstartPosY);
    this->sender = std::make_shared<QTextEdit>(this);
    this->sender->resize(winConfig::textBlockwidth, winConfig::textBlockHigth);
    this->sender->move(winConfig::textBlockstartPosX,
                       winConfig::textBlockstartPosY * 2 + winConfig::textBlockHigth);
    this->reciveDivideCharC = std::make_shared<QTextEdit>(this);
    this->reciveDivideCharC->move(winConfig::serialReciveConfigStartX + 90,
                                  winConfig::serialReciveConfigStartY + 50 * 2 + 5);
    this->reciveDivideCharC->resize(80, 20);
    this->sendDivideCharC = std::make_shared<QTextEdit>(this);
    this->sendDivideCharC->move(winConfig::serialSendConfigStartX + 90,
                                winConfig::serialSendConfigStartY + 55);
    this->sendDivideCharC->resize(80, 20);

    //context init
    this->recvContext = std::make_shared<QLabel>("recive sector:", this);
    this->recvContext->move(winConfig::textBlockstartPosX - 10, winConfig::textBlockstartPosY - 40);
    this->sendContext = std::make_shared<QLabel>("send sector:", this);
    this->sendContext->move(winConfig::textBlockstartPosX - 10, winConfig::textBlockstartPosY * 2 + winConfig::textBlockHigth - 40);

    this->serialConfigTitle = std::make_shared<QLabel>("SerialConfig:", this);
    this->serialConfigTitle->move(winConfig::serialConfigStartPosX,
                                  winConfig::serialConfigStartPosY - 25);
    this->sendTitle = std::make_shared<QLabel>("ReciveConfig:", this);
    this->sendTitle->move(winConfig::serialConfigStartPosX,
                          winConfig::serialConfigStartPosY + winConfig::serialConfigHigth);
    this->reciveTitle = std::make_shared<QLabel>("SendConfig:", this);
    this->reciveTitle->move(winConfig::serialConfigStartPosX,
                            winConfig::serialConfigStartPosY + winConfig::serialConfigHigth * 2 + 25);

    this->portNumber = std::make_shared<QLabel>("Port:", this);
    this->portNumber->move(winConfig::serialConfigStartPosX + 10,
                           winConfig::serialConfigStartPosY);
    this->portBandBit = std::make_shared<QLabel>("BaudRate:", this);
    this->portBandBit->move(winConfig::serialConfigStartPosX + 10,
                            winConfig::serialConfigStartPosY + 30);
    this->portDataBit = std::make_shared<QLabel>("DataSize:", this);
    this->portDataBit->move(winConfig::serialConfigStartPosX + 10,
                            winConfig::serialConfigStartPosY + 30 * 2);
    this->portStopBit = std::make_shared<QLabel>("StopBit:", this);
    this->portStopBit->move(winConfig::serialConfigStartPosX + 10,
                            winConfig::serialConfigStartPosY + 30 * 3);
    this->portCheckBit = std::make_shared<QLabel>("CheckBit:", this);
    this->portCheckBit->move(winConfig::serialConfigStartPosX + 10,
                             winConfig::serialConfigStartPosY + 30 * 4);
    this->hexGet = std::make_shared<QLabel>("GetHex:", this);
    this->hexGet->move(winConfig::serialReciveConfigStartX + 10,
                       winConfig::serialReciveConfigStartY);
    this->rowAutoChange = std::make_shared<QLabel>("AutoChange:", this);
    this->rowAutoChange->move(winConfig::serialReciveConfigStartX + 10,
                              winConfig::serialReciveConfigStartY + 50);
    this->reciveDivideChar = std::make_shared<QLabel>("DivideChar:", this);
    this->reciveDivideChar->move(winConfig::serialReciveConfigStartX + 10,
                                 winConfig::serialReciveConfigStartY + 50 * 2);
    this->hexSend = std::make_shared<QLabel>("SendHex:", this);
    this->hexSend->move(winConfig::serialSendConfigStartX + 10,
                        winConfig::serialSendConfigStartY);
    this->sendDivideChar = std::make_shared<QLabel>("DivideChar:", this);
    this->sendDivideChar->move(winConfig::serialSendConfigStartX + 10,
                               winConfig::serialSendConfigStartY + 50);
    this->autoSend = std::make_shared<QLabel>("AutoSend:", this);
    this->autoSend->move(winConfig::serialSendConfigStartX + 10,
                         winConfig::serialSendConfigStartY + 50 * 2);
    this->ms = std::make_shared<QLabel>("ms", this);
    this->ms->move(winConfig::serialSendConfigStartX + 190,
                   winConfig::serialSendConfigStartY + 50 * 2);
    this->statusCon = std::make_shared<QLabel>("STATUS:", this);
    this->statusCon->move(winConfig::serialConfigStartPosX,
                          winConfig::win_higth - 40);
    this->statusRes = std::make_shared<QLabel>(DISCONNECT, this);
    this->statusRes->move(winConfig::serialConfigStartPosX + 50,
                          winConfig::win_higth - 40);
    ChangeStatus(DISCONNECT);

    //Combobox init
    this->portNumberC = std::make_shared<QComboBox>(this);
    this->portNumberC->move(winConfig::serialConfigStartPosX + 80,
                            winConfig::serialConfigStartPosY);
    this->portBandBitC = std::make_shared<QComboBox>(this);
    this->portBandBitC->move(winConfig::serialConfigStartPosX + 80,
                             winConfig::serialConfigStartPosY + 30);
    this->portDataBitC = std::make_shared<QComboBox>(this);
    this->portDataBitC->move(winConfig::serialConfigStartPosX + 80,
                             winConfig::serialConfigStartPosY + 30 * 2);
    this->portStopBitC = std::make_shared<QComboBox>(this);
    this->portStopBitC->move(winConfig::serialConfigStartPosX + 80,
                             winConfig::serialConfigStartPosY + 30 * 3);
    this->portCheckBitC = std::make_shared<QComboBox>(this);
    this->portCheckBitC->move(winConfig::serialConfigStartPosX + 80,
                              winConfig::serialConfigStartPosY + 30 * 4);

    //button init
    this->reciveClear = std::make_shared<QPushButton>("reciveClear", this);
    this->reciveClear->move(winConfig::textBlockstartPosX + 70, winConfig::textBlockstartPosY - 40);
    this->sendClear = std::make_shared<QPushButton>("sendClear", this);
    this->sendClear->move(winConfig::textBlockstartPosX + 70, winConfig::textBlockstartPosY * 2 + winConfig::textBlockHigth - 40);
    this->sendOut = std::make_shared<QPushButton>("send", this);
    this->sendOut->move(winConfig::textBlockstartPosX - 10, winConfig::textBlockstartPosY * 2 + winConfig::textBlockHigth*2 + 20);
    this->portCheckPort = std::make_shared<QPushButton>("check port", this);
    this->portCheckPort->resize(winConfig::serialCheckBtnWidth,
                                winConfig::serialCheckBtnHigth);
    this->portCheckPort->move(winConfig::serialConfigStartPosX + 180,
                              winConfig::serialConfigStartPosY);
    this->portStartPort = std::make_shared<QPushButton>("port start", this);
    this->portStartPort->resize(winConfig::serialCheckBtnWidth,
                                winConfig::serialCheckBtnHigth / 2);
    this->portStartPort->move(winConfig::serialConfigStartPosX + 180,
                              winConfig::serialConfigStartPosY +
                                  winConfig::serialCheckBtnHigth);
    this->portStopPort = std::make_shared<QPushButton>("port stop", this);
    this->portStopPort->resize(winConfig::serialCheckBtnWidth,
                               winConfig::serialCheckBtnHigth / 2);
    this->portStopPort->move(winConfig::serialConfigStartPosX + 180,
                             winConfig::serialConfigStartPosY +
                                 winConfig::serialCheckBtnHigth +
                                 winConfig::serialCheckBtnHigth / 2);
    //checkbox init
    this->hexGetC = std::make_shared<QCheckBox>(this);
    this->hexGetC->move(winConfig::serialReciveConfigStartX + 90,
                        winConfig::serialReciveConfigStartY);
    this->rowAutoChangeC = std::make_shared<QCheckBox>(this);
    this->rowAutoChangeC->move(winConfig::serialReciveConfigStartX + 90,
                               winConfig::serialReciveConfigStartY + 50);
    this->hexSendC = std::make_shared<QCheckBox>(this);
    this->hexSendC->move(winConfig::serialSendConfigStartX + 90,
                         winConfig::serialSendConfigStartY);
    this->autoSendC = std::make_shared<QCheckBox>(this);
    this->autoSendC->move(winConfig::serialSendConfigStartX + 90,
                          winConfig::serialSendConfigStartY + 50 * 2);
    //spinBox init
    this->spin = std::make_shared<QSpinBox>(this);
    this->spin->move(winConfig::serialSendConfigStartX + 110,
                     winConfig::serialSendConfigStartY + 50 * 2 + 5);
    this->spin->setLocale(QLocale::English);
    this->spin->resize(80, 20);
    this->spin->setRange(0, 500);

    //palette init
    this->palette.setColor(QPalette::Window, Qt::lightGray);
    this->setPalette(this->palette);

    //func init
    FunctionInit();
}

void serialHelper::paintEvent(QPaintEvent* event)
{
    std::shared_ptr<QPainter> painter = std::make_shared<QPainter>(this);
    //draw simple ui
    painter->setPen(QPen(Qt::gray, 3));
    painter->drawRect(winConfig::textBlockstartPosX - 5,
                      winConfig::textBlockstartPosY - 5,
                      winConfig::textBlockwidth + 10,
                      winConfig::textBlockHigth + 10);
    painter->drawRect(winConfig::textBlockstartPosX - 5,
                      winConfig::textBlockstartPosY * 2 + winConfig::textBlockHigth - 5,
                      winConfig::textBlockwidth + 10,
                      winConfig::textBlockHigth + 10);
    painter->drawRect(winConfig::serialConfigStartPosX,
                      winConfig::serialConfigStartPosY,
                      winConfig::serialConfigwidth,
                      winConfig::serialConfigHigth);
    painter->drawRect(winConfig::serialReciveConfigStartX,
                      winConfig::serialReciveConfigStartY,
                      winConfig::serialReciveConfigWidth,
                      winConfig::serialReciveConfigHigth);
    painter->drawRect(winConfig::serialSendConfigStartX,
                      winConfig::serialSendConfigStartY,
                      winConfig::serialSendConfigWidth,
                      winConfig::serialSendConfigHigth);
}

void serialHelper::ChangeStatus(std::string status)
{
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    if (status == DISCONNECT || status == CONNECT) {
        this->statusRes->setText(status.c_str());
    } else {
        this->statusRes->setText("ERROR");
    }
    this->statusRes->setPalette(pe);
}

void serialHelper::FunctionInit()
{
    QStringList baudbit = {
        "1200",
        "2400",
        "4800",
        "9600",
        "19200",
        "38400",
        "57600",
        "115200"
    };
    this->portBandBitC->addItems(baudbit);
    QStringList dataSizeBit = {
        "5",
        "6",
        "7",
        "8"
    };
    this->portDataBitC->addItems(dataSizeBit);
    QStringList stopBit = {
        "1"
    };
    this->portStopBitC->addItems(stopBit);
    QStringList checkBit = {
        "False",
        "Odd",
        "Even"
    };
    this->portCheckBitC->addItems(checkBit);
    connect(this->portCheckPort.get(), &QPushButton::clicked, this, &serialHelper::CheckPort);
    connect(this->portStartPort.get(), &QPushButton::clicked, this, &serialHelper::StartSerialFunc);
    connect(this->portStopPort.get(), &QPushButton::clicked, this, &serialHelper::StopSerialFunc);
    connect(this->reciveClear.get(), &QPushButton::clicked, this, &serialHelper::ReciveSectorClear);
    connect(this->sendClear.get(), &QPushButton::clicked, this, &serialHelper::SendSectorClear);
    connect(this->sendOut.get(), &QPushButton::clicked, this, &serialHelper::SendFunc);
    this->sendOut->setEnabled(false);
    this->portStopPort->setEnabled(false);
    //recive process init
    ReciveParam rec_param = {
        .serialStaus = this->statusRes,
        .serialPort = &this->serialPort,
        .text = this->reciver,
        .getHex = &this->getHex,
        .autoChange = &this->autoChange,
        .recDivideChar = &this->recDivideChar
    };
    if (this->rec_handler != nullptr) delete this->rec_handler;
    this->rec_handler = new ReciveThread(rec_param);
    //send process init
    SendParam sen_param = {
        .serialStaus = this->statusRes,
        .serialPort = &this->serialPort,
        .text = this->sender,
        .sendHex = &this->sendHex,
        .senDivideChar = &this->senDivideChar,
        .autoSended = &this->autoSended,
        .msDelay = &this->msDelay,
        .startSend = &startSend
    };
    if (this->sen_handler != nullptr) delete this->sen_handler;
    this->sen_handler = new SendThread(sen_param);
    this->rec_handler->start();
    this->sen_handler->start();
}

void serialHelper::CheckPort()
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    this->portNumberC->clear();
    for (auto& item : portList) {
        this->portNumberC->addItem(item.portName());
    }
}

void serialHelper::StartSerialFunc()
{
    this->portNumberC->setEnabled(false);
    this->portBandBitC->setEnabled(false);
    this->portDataBitC->setEnabled(false);
    this->portStopBitC->setEnabled(false);
    this->portCheckBitC->setEnabled(false);
    this->portCheckPort->setEnabled(false);
    this->portStartPort->setEnabled(false);
    this->portStopPort->setEnabled(true);
    this->sendOut->setEnabled(true);
    this->portNumberC->setEnabled(false);
    this->portBandBitC->setEnabled(false);
    this->portDataBitC->setEnabled(false);
    this->portStopBitC->setEnabled(false);
    this->portCheckBitC->setEnabled(false);
    this->hexGetC->setEnabled(false);
    this->rowAutoChangeC->setEnabled(false);
    this->reciveDivideCharC->setEnabled(false);
    this->hexSendC->setEnabled(false);
    this->sendDivideCharC->setEnabled(false);
    this->autoSendC->setEnabled(false);
    this->spin->setEnabled(false);
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;
    portName = this->portNumberC->currentText().toStdString();
    if (portName == "") {
        QMessageBox::critical(this, "error hint", "No serial port detected!!!");
        StopSerialFunc();
        return;
    }
    //serial recive config
    this->getHex = this->hexGetC->isChecked();
    this->autoChange = this->rowAutoChangeC->isChecked();
    this->recDivideChar = this->reciveDivideCharC->toPlainText().toStdString()[0];
    //serial send config
    this->sendHex = this->hexSendC->isChecked();
    this->senDivideChar = this->sendDivideCharC->toPlainText().toStdString()[0];
    this->autoSended = this->autoSendC->isChecked();
    this->msDelay = this->spin->value();
    //serial config
    BaudRate = this->portBandBitC->currentText().toStdString();
    DataSize = this->portDataBitC->currentText().toStdString();
    stopBit = this->portStopBitC->currentText().toStdString();
    CheckBit = this->portCheckBitC->currentText().toStdString();
    if (BaudRate == "1200") baudRate = QSerialPort::Baud1200;
    else if (BaudRate == "2400") baudRate = QSerialPort::Baud2400;
    else if (BaudRate == "4800") baudRate = QSerialPort::Baud4800;
    else if (BaudRate == "9600") baudRate = QSerialPort::Baud9600;
    else if (BaudRate == "19200") baudRate = QSerialPort::Baud19200;
    else if (BaudRate == "38400") baudRate = QSerialPort::Baud38400;
    else if (BaudRate == "57600") baudRate = QSerialPort::Baud57600;
    else if (BaudRate == "115200") baudRate = QSerialPort::Baud115200;

    if (DataSize == "5") dataBits = QSerialPort::Data5;
    else if (DataSize == "6") dataBits = QSerialPort::Data6;
    else if (DataSize == "7") dataBits = QSerialPort::Data7;
    else if (DataSize == "8") dataBits = QSerialPort::Data8;

    if (stopBit == "1") stopBits = QSerialPort::OneStop;

    if (CheckBit == "False") checkBits = QSerialPort::NoParity;
    else if (CheckBit == "Odd") checkBits = QSerialPort::OddParity;
    else if (CheckBit == "Even") checkBits = QSerialPort::EvenParity;
    this->serialPort.setPortName(portName.c_str());
    this->serialPort.setBaudRate(baudRate);
    this->serialPort.setDataBits(dataBits);
    this->serialPort.setStopBits(stopBits);
    this->serialPort.setParity(checkBits);
    if (this->serialPort.open(QIODevice::ReadWrite) != true) {
        QMessageBox::critical(this, "error hint", "open serial failed!!!");
        StopSerialFunc();
        return;
    }
    ProcessParam::StatusTex_.lock();
    ChangeStatus(CONNECT);
    ProcessParam::StatusTex_.unlock();
}
void serialHelper::StopSerialFunc()
{
    this->portNumberC->setEnabled(true);
    this->portBandBitC->setEnabled(true);
    this->portDataBitC->setEnabled(true);
    this->portStopBitC->setEnabled(true);
    this->portCheckBitC->setEnabled(true);
    this->portCheckPort->setEnabled(true);
    this->portStartPort->setEnabled(true);
    this->portStopPort->setEnabled(false);
    this->sendOut->setEnabled(false);
    this->portNumberC->setEnabled(true);
    this->portBandBitC->setEnabled(true);
    this->portDataBitC->setEnabled(true);
    this->portStopBitC->setEnabled(true);
    this->portCheckBitC->setEnabled(true);
    this->hexGetC->setEnabled(true);
    this->rowAutoChangeC->setEnabled(true);
    this->reciveDivideCharC->setEnabled(true);
    this->hexSendC->setEnabled(true);
    this->sendDivideCharC->setEnabled(true);
    this->autoSendC->setEnabled(true);
    this->spin->setEnabled(true);
    if (this->serialPort.isOpen()) {
        this->serialPort.close();
    }
    ProcessParam::StatusTex_.lock();
    ChangeStatus(DISCONNECT);
    ProcessParam::StatusTex_.unlock();
}

void serialHelper::ReciveSectorClear()
{
    ReceiveProcessParam::recTextTex_.lock();
    this->reciver->setText("");
    ReceiveProcessParam::recTextTex_.unlock();
}
void serialHelper::SendSectorClear()
{
    SendProcessParam::senTextTex_.lock();
    this->sender->setText("");
    SendProcessParam::senTextTex_.unlock();
}

void serialHelper::SendFunc()
{
    SendProcessParam::startSendTex_.lock();
    this->startSend = true;
    SendProcessParam::startSendTex_.unlock();
}

serialHelper::~serialHelper()
{
    if (this->rec_handler != nullptr) {
        this->rec_handler->requestInterruption();
        this->rec_handler->wait();
        delete this->rec_handler;
        this->rec_handler = nullptr;
    }
    if (this->sen_handler != nullptr) {
        this->sen_handler->requestInterruption();
        this->sen_handler->wait();
        delete this->sen_handler;
        this->sen_handler = nullptr;
    }
    delete ui;
}

ReciveThread::ReciveThread(ReciveParam param) : param_(param) {}
void ReciveThread::run()
{
    std::string status;
    bool recivedData = false;
    QByteArray data = "";
    while(!this->isInterruptionRequested()) {
        ProcessParam::StatusTex_.lock();
        status = this->param_.serialStaus->text().toStdString();
        ProcessParam::StatusTex_.unlock();
        if (status == CONNECT) {
            if (this->param_.serialPort->waitForReadyRead(100)) recivedData = true;
            else if (recivedData) {
                recivedData = false;
                data = this->param_.serialPort->readAll();
                QString rec_str;
                if (*this->param_.autoChange) this->param_.text->setWordWrapMode(QTextOption::WrapAnywhere);
                else this->param_.text->setWordWrapMode(QTextOption::NoWrap);
                if (*this->param_.getHex) {
                    rec_str = "";
                    QString tmp = data.toHex().toUpper();
                    for (int i = 0; i < tmp.length(); i += 2) {
                        rec_str += tmp.mid(i, 2);
                        rec_str += (*this->param_.recDivideChar);
                    }
                } else rec_str = QString(data).append(this->param_.recDivideChar);
                ReceiveProcessParam::recTextTex_.lock();
                this->param_.text->insertPlainText(rec_str);
                ReceiveProcessParam::recTextTex_.unlock();
            }
        } else msleep(1);
    }
}

SendThread::SendThread(SendParam param) : param_(param) {}
void SendThread::run()
{
// send logic
    std::string status;
    bool startSend;
    while(!this->isInterruptionRequested()) {
        ProcessParam::StatusTex_.lock();
        status = this->param_.serialStaus->text().toStdString();
        ProcessParam::StatusTex_.unlock();
        if (status == CONNECT) {
            SendProcessParam::startSendTex_.lock();
            startSend = *this->param_.startSend;
            SendProcessParam::startSendTex_.unlock();
            if (startSend) {
                if (*this->param_.autoSended) {
                    //auto send logic
                } else {
                    //send once logic
                }
            } else msleep(1);
        } else msleep(1);
    }
}
