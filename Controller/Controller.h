#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <qobject.h>
#include <qtmetamacros.h>
#include <QThread>
class Model;
class serialHelper;
struct InitParam;
typedef struct InitParam InitParam;
class Controller : public QObject {
    Q_OBJECT
public slots:
    bool FunctionInit(InitParam* param);
    bool RequestForPortNumber(std::shared_ptr<QStringList> ret);
    void RequestForPortNumberPostHandle(bool ret);
signals:
    bool InitSignal(InitParam* param);
    bool RequestForPortNumberSignal(std::shared_ptr<QStringList> ret);
private:
    std::shared_ptr<QStringList> portNumberRequestPtr;
};
#endif // CONTROLLER_H
