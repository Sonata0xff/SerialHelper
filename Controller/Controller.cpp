#include "Controller.h"
#include "../Model/Model.h"
#include "../serialhelper.h"
#include "../structure.h"

bool Controller::FunctionInit(InitParam* param)
{
    //multi connect init
    connect(this, &Controller::InitSignal, param->model, &Model::FunctionInit, Qt::BlockingQueuedConnection);
    connect(this, &Controller::RequestForPortNumberSignal, param->model, &Model::RequestForPortNumber, Qt::BlockingQueuedConnection);
    param->modelThread->start();
    return emit InitSignal(param);
}

bool Controller::RequestForPortNumber(std::shared_ptr<QStringList> ret)
{
    this->portNumberRequestPtr = ret;
    return emit RequestForPortNumberSignal(this->portNumberRequestPtr);
}

void Controller::RequestForPortNumberPostHandle(bool ret)
{
    if (ret) this->portNumberRequestPtr = nullptr;
}



