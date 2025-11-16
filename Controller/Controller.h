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
signals:
    bool InitSignal(InitParam* param);

};
#endif // CONTROLLER_H
