#include "serialhelper.h"
#include "./ui_serialhelper.h"
#include "./Controller/Controller.h"
#include "structure.h"
#include "./Model/Model.h"
#include "windowConfig.h"
#include <QThread>
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

bool serialHelper::FunctionInit(InitParam* param)
{
    this->param_ = param;
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
    //multi connect
    connect(this, &serialHelper::InitSignal, param_->controller, &Controller::FunctionInit, Qt::BlockingQueuedConnection);
    connect(this, &serialHelper::PortNumberRequest, param_->controller, &Controller::RequestForPortNumber, Qt::BlockingQueuedConnection);
    connect(this, &serialHelper::PortNumberRequestReturn, param_->controller, &Controller::RequestForPortNumberPostHandle);
    connect(this, &serialHelper::StartPortRequest, param_->controller, &Controller::RequestForPortStart, Qt::BlockingQueuedConnection);
    connect(this, &serialHelper::StartPortRequestReturn, param_->controller, &Controller::RequestForPortStartPostHandle);
    connect(this, &serialHelper::StopPortRequest, param_->controller, &Controller::RequestForPortStop, Qt::BlockingQueuedConnection);
    connect(this, &serialHelper::SendOutDataRequest, param_->controller, &Controller::RequestForSendData);
    connect(this->portCheckPort.get(), &QPushButton::clicked, this, &serialHelper::CheckPortNumber);
    connect(this->portStartPort.get(), &QPushButton::clicked, this, &serialHelper::StartSerialFunc);
    connect(this->portStopPort.get(), &QPushButton::clicked, this, &serialHelper::StopSerialFunc);
    connect(this->reciveClear.get(), &QPushButton::clicked, this, &serialHelper::ReciveSectorClear);
    connect(this->sendClear.get(), &QPushButton::clicked, this, &serialHelper::SendSectorClear);
    connect(this->sendOut.get(), &QPushButton::clicked,  this, &serialHelper::SendOutData);
    this->sendOut->setEnabled(false);
    this->portStopPort->setEnabled(false);
    //transport init signal
    param->controllerThread->start();
    bool ret = emit InitSignal(param_);
    return ret;
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

    //serial config
    portName = this->portNumberC->currentText().toStdString();
    if (portName == "") {
        QMessageBox::critical(this, "error hint", "No serial port detected!!!");
        StopSerialFunc();
        return;
    }
    BaudRate = this->portBandBitC->currentText().toStdString();
    DataSize = this->portDataBitC->currentText().toStdString();
    stopBit = this->portStopBitC->currentText().toStdString();
    CheckBit = this->portCheckBitC->currentText().toStdString();

    //receive config
    getHex = this->hexGetC->isChecked();
    autoChange = this->rowAutoChangeC->isChecked();
    if(this->reciveDivideCharC->toPlainText().toStdString().size() < 1) recDivideChar = ' ';
    else recDivideChar = this->reciveDivideCharC->toPlainText().toStdString()[0];

    //send config
    sendHex = this->hexSendC->isChecked();
    if (this->sendDivideCharC->toPlainText().toStdString().size() < 1) senDivideChar = ' ';
    else senDivideChar = this->sendDivideCharC->toPlainText().toStdString()[0];
    autoSend_ = this->autoSendC->isChecked();
    msDelay = this->spin->value();

    // set auto change row
    if (autoChange) this->reciver->setWordWrapMode(QTextOption::WrapAnywhere);
    else this->reciver->setWordWrapMode(QTextOption::NoWrap);

    //load run param
    std::shared_ptr<RunParam> runParam = std::make_shared<RunParam>();
    runParam->portName = portName;
    runParam->baudRate = BaudRate;
    runParam->dataSize = DataSize;
    runParam->stopBit = stopBit;
    runParam->checkBit = CheckBit;
    runParam->getHex = getHex;
    runParam->autoChange = autoChange;
    runParam->recDivideChar = recDivideChar;
    runParam->sendHex = sendHex;
    runParam->senDivideChar = senDivideChar;
    runParam->autoSend_ = autoSend_;
    runParam->msDelay = msDelay;
    bool ret = emit StartPortRequest(runParam);
    if (!ret) {
        runParam = nullptr;
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
        QMessageBox::critical(this, "system error", "start serial port failed!!!");
        return;
    }
    runParam = nullptr;
    emit StartPortRequestReturn(true);
    ChangeStatus(CONNECT);
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
    bool res = emit StopPortRequest();
    ChangeStatus(DISCONNECT);
    if (!res) QMessageBox::critical(this, "system error", "stop serial port failed!!!");
}

void serialHelper::ReciveSectorClear()
{
    this->reciver->setPlainText("");
}
void serialHelper::SendSectorClear()
{
    this->sender->setPlainText("");
}

void serialHelper::closeEvent(QCloseEvent * e)
{
    this->param_->controllerThread->exit();
    this->param_->modelThread->exit();
    this->param_->controllerThread->wait();
    this->param_->modelThread->wait();
    QMainWindow::closeEvent(e);
}

void serialHelper::CheckPortNumber()
{
    std::shared_ptr<QStringList> ret = std::make_shared<QStringList>();
    ret->clear();
    this->portNumberC->clear();
    bool res = emit PortNumberRequest(ret);
    if (!res) {
        ret = nullptr;
        QMessageBox::critical(this, "system error", "Get serial port failed!!!");
        return;
    }
    this->portNumberC->addItems(*ret);
    ret = nullptr;
    emit PortNumberRequestReturn(true);
}

bool serialHelper::ShowRecString(std::shared_ptr<QString> data)
{
    this->reciver->insertPlainText(*data);
    return true;
}

void serialHelper::SendOutData()
{
    std::shared_ptr<QString> tmpString = std::make_shared<QString>("");
    *tmpString = this->sender->toPlainText();
    emit SendOutDataRequest(tmpString);
    while(0);
}

void serialHelper::SendFailHandle()
{
    QMessageBox::critical(this, "comm error", "send data failed!!!");
}

serialHelper::~serialHelper()
{
    delete ui;
}

