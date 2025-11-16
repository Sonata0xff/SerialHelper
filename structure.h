#ifndef STRUCTURE_H
#define STRUCTURE_H
class Model;
class serialHelper;
class Controller;
class QThread;
typedef struct InitParam {
    serialHelper* serial_helper;
    Model* model;
    Controller* controller;
    QThread* modelThread;
    QThread* controllerThread;
} InitParam;
#endif // STRUCTURE_H
