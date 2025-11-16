#include "Controller.h"
#include "../Model/Model.h"
#include "../serialhelper.h"
#include "../structure.h"

bool Controller::FunctionInit(InitParam* param)
{
    //multi connect init
    connect(this, &Controller::InitSignal, param->model, &Model::FunctionInit, Qt::BlockingQueuedConnection);
    param->modelThread->start();
    return emit InitSignal(param);
}

