#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <string>
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
typedef struct RunParam {
    //serial config
    std::string portName;
    std::string baudRate;
    std::string dataSize;
    std::string stopBit;
    std::string checkBit;
    //receive config
    bool getHex;
    bool autoChange;
    char recDivideChar;
    //sned config
    bool sendHex;
    char senDivideChar;
    bool autoSend_;
    int msDelay;
} RunParam;
#endif // STRUCTURE_H
