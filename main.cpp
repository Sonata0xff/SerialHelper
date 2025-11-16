#include "structure.h"
#include "serialhelper.h"
#include "./Controller/Controller.h"
#include "./Model/Model.h"
#include <QApplication>
#include <QLocale>
#include <QThread>
int main(int argc, char *argv[])
{
    //Start
    QApplication runner(argc, argv);
    serialHelper ui;
    Model model;
    Controller controller;
    QThread controllerThread;
    QThread modelThread;
    InitParam param = {
        .serial_helper = &ui,
        .model = &model,
        .controller = &controller,
        .modelThread = &modelThread,
        .controllerThread = &controllerThread
    };
    controller.moveToThread(&controllerThread);
    model.moveToThread(&modelThread);
    bool ret = ui.FunctionInit(&param);
    if (!ret) return 0;
    //update
    ui.show();
    return runner.exec();
    //Stop
    //nothing here actually
}
