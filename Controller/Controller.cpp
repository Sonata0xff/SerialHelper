#include "Controller.h"
#include "../Model/Model.h"
#include "../serialhelper.h"
#include "../structure.h"

bool Controller::FunctionInit(InitParam* param)
{
    //multi connect init
    connect(this, &Controller::InitSignal, param->model, &Model::FunctionInit, Qt::BlockingQueuedConnection);
    connect(this, &Controller::RequestForPortNumberSignal, param->model, &Model::RequestForPortNumber, Qt::BlockingQueuedConnection);
    connect(this, &Controller::RequestForPortStartSignal, param->model, &Model::RequestForPortStart, Qt::BlockingQueuedConnection);
    connect(this, &Controller::RequestForPortStopSignal, param->model, &Model::RequestForPortStop, Qt::BlockingQueuedConnection);
    connect(this, &Controller::RequestForDataToViewSignal, param->serial_helper, &serialHelper::ShowRecString, Qt::BlockingQueuedConnection);
    connect(this, &Controller::RequestForDataToModelSignal, param->model, &Model::RequestForSend, Qt::BlockingQueuedConnection);
    connect(this, &Controller::SendFailSignal, param->serial_helper, &serialHelper::SendFailHandle);
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

bool Controller::RequestForPortStart(std::shared_ptr<RunParam> param)
{
    this->portStartRequestPtr = param;
    return emit RequestForPortStartSignal(this->portStartRequestPtr);
}
void Controller::RequestForPortStartPostHandle(bool ret)
{
    if (ret) this->portStartRequestPtr = nullptr;
}
bool Controller::RequestForPortStop()
{
    return emit RequestForPortStopSignal();
}

void Controller::RequestForDataToView(std::shared_ptr<QString> data)
{
    this->dataTransToView = data;
    bool ret = emit RequestForDataToViewSignal(data);
    if (ret) this->dataTransToView = nullptr;
}

void Controller::RequestForSendData(std::shared_ptr<QString> data)
{
    this->dataTransToModel = data;
    bool ret = emit RequestForDataToModelSignal(this->dataTransToModel);
    if (ret) this->dataTransToModel = nullptr;
    else emit SendFailSignal();
}


