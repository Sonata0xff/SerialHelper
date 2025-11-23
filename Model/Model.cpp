#include "Model.h"
#include "../Controller/Controller.h"
#include "../serialhelper.h"
#include "../structure.h"
#include <QThread>
bool Model::FunctionInit(InitParam* param)
{
    this->serialPort = std::make_shared<QSerialPort>();
    connect(this->serialPort.get(), &QSerialPort::readyRead, this, &Model::RequestForReceive);
    connect(this, &Model::RequestForDataTrans, param->controller, &Controller::ReequestForDataToView);
    return true;
}

bool Model::RequestForPortNumber(std::shared_ptr<QStringList> ret)
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    for (auto& item : portList) {
        ret->append(item.portName());
    }
    return true;
}

bool Model::RequestForPortStart(std::shared_ptr<RunParam> param)
{
    this->param_ = nullptr;
    this->param_ = std::make_shared<RunParam>();
    param_->portName = param->portName;
    param_->baudRate = param->baudRate;
    param_->dataSize = param->dataSize;
    param_->stopBit = param->stopBit;
    param_->checkBit = param->checkBit;
    param_->getHex = param->getHex;
    param_->autoChange = param->autoChange;
    param_->recDivideChar = param->recDivideChar;
    param_->sendHex = param->sendHex;
    param_->senDivideChar = param->senDivideChar;
    param_->autoSend_ = param->autoSend_;
    param_->msDelay = param->msDelay;
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;
    if (param_->baudRate == "1200") baudRate = QSerialPort::Baud1200;
    else if (param_->baudRate == "2400") baudRate = QSerialPort::Baud2400;
    else if (param_->baudRate == "4800") baudRate = QSerialPort::Baud4800;
    else if (param_->baudRate == "9600") baudRate = QSerialPort::Baud9600;
    else if (param_->baudRate == "19200") baudRate = QSerialPort::Baud19200;
    else if (param_->baudRate == "38400") baudRate = QSerialPort::Baud38400;
    else if (param_->baudRate == "57600") baudRate = QSerialPort::Baud57600;
    else if (param_->baudRate == "115200") baudRate = QSerialPort::Baud115200;

    if (param_->dataSize == "5") dataBits = QSerialPort::Data5;
    else if (param_->dataSize == "6") dataBits = QSerialPort::Data6;
    else if (param_->dataSize == "7") dataBits = QSerialPort::Data7;
    else if (param_->dataSize == "8") dataBits = QSerialPort::Data8;

    if (param_->checkBit == "1") stopBits = QSerialPort::OneStop;

    if (param_->checkBit == "False") checkBits = QSerialPort::NoParity;
    else if (param_->checkBit == "Odd") checkBits = QSerialPort::OddParity;
    else if (param_->checkBit == "Even") checkBits = QSerialPort::EvenParity;

    this->serialPort->setPortName(param_->portName.c_str());
    this->serialPort->setBaudRate(baudRate);
    this->serialPort->setDataBits(dataBits);
    this->serialPort->setStopBits(stopBits);
    this->serialPort->setParity(checkBits);
    this->serialPort->setParity(checkBits);
    if (this->serialPort->open(QIODevice::ReadWrite) != true) return false;
    else return true;
}

bool Model::RequestForPortStop()
{
    if (this->serialPort->isOpen()) {
        this->serialPort->clear();
        this->serialPort->close();
    }
    return true;
}


void Model::RequestForReceive()
{
    if (!this->serialPort->isOpen()) return;
    QString recBuf = this->serialPort->readAll();
    std::shared_ptr<QString> transData = std::make_shared<QString>("");
    if (this->param_->getHex) {
        QByteArray tmpBuf = recBuf.toUtf8().toHex().toUpper();
        recBuf = QString::fromUtf8(tmpBuf);
        for (int i = 0; i < recBuf.size(); ++i) {
            if (i != 0 && i % 2 == 0) transData->append(this->param_->recDivideChar);
            transData->append(recBuf[i]);
        }
    } else {
        for (int i = 0; i < recBuf.size();  ++i) {
            if (i != 0) transData->append(this->param_->recDivideChar);
            transData->append(recBuf[i]);
        }
    }
    emit RequestForDataTrans(transData);
    while(0);
}





