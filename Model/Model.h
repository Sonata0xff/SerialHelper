#ifndef MODEL_H
#define MODEL_H
#include <qobject.h>
#include <qtmetamacros.h>
#include <QThread>
#include <QSerialPort>
class Controller;
class serialHelper;
struct InitParam;
typedef struct InitParam InitParam;
struct RunParam;
typedef struct RunParam RunParam;
class Model : public QObject {
    Q_OBJECT
private:
    std::shared_ptr<QSerialPort> serialPort;
    std::shared_ptr<RunParam> param_;
public slots:
    bool FunctionInit(InitParam* param);
    bool RequestForPortNumber(std::shared_ptr<QStringList> ret);
    bool RequestForPortStart(std::shared_ptr<RunParam> param);
    bool RequestForPortStop();
    void RequestForReceive();
    bool RequestForSend(std::shared_ptr<QString> data);
signals:
    void RequestForDataTrans(std::shared_ptr<QString> data);
};
#endif // MODEL_H
