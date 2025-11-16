#include "Model.h"
#include "../Controller/Controller.h"
#include "../serialhelper.h"
#include "../structure.h"
#include <QThread>

bool Model::FunctionInit(InitParam* param)
{
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

