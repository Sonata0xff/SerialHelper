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
    QSerialPort serialPort;
public slots:
    bool FunctionInit(InitParam* param);
    bool RequestForPortNumber(std::shared_ptr<QStringList> ret);

};
#endif // MODEL_H
