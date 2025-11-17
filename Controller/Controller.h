#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <qobject.h>
#include <qtmetamacros.h>
#include <QThread>
class Model;
class serialHelper;
struct InitParam;
typedef struct InitParam InitParam;
struct RunParam;
typedef struct RunParam RunParam;
class Controller : public QObject {
    Q_OBJECT
public slots:
    bool FunctionInit(InitParam* param);
    bool RequestForPortNumber(std::shared_ptr<QStringList> ret);
    void RequestForPortNumberPostHandle(bool ret);
    bool RequestForPortStart(std::shared_ptr<RunParam> param);
    void RequestForPortStartPostHandle(bool ret);
signals:
    bool InitSignal(InitParam* param);
    bool RequestForPortNumberSignal(std::shared_ptr<QStringList> ret);
    bool RequestForPortStartSignal(std::shared_ptr<RunParam> param);
private:
    std::shared_ptr<QStringList> portNumberRequestPtr;
    std::shared_ptr<RunParam> portStartRequestPtr;
};
#endif // CONTROLLER_H
