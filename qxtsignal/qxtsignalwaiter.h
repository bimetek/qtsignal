#ifndef QXTSIGNALWAITER_H
#define QXTSIGNALWAITER_H

#include "qxtsignal_global.h"
#include <QObject>
#include <QEventLoop>

namespace Qxt
{

class SignalWaiterPrivate;

class QXTSIGNALSHARED_EXPORT SignalWaiter : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SignalWaiter)
    SignalWaiterPrivate * const d_ptr;

    Q_PRIVATE_SLOT(d_func(), void signalCaught())

public:
    explicit SignalWaiter(const QObject* sender, const char* signal);
    virtual ~SignalWaiter();
    static bool wait(const QObject* sender, const char* signal, int msec = -1,
                     QEventLoop::ProcessEventsFlags f = QEventLoop::AllEvents);
    bool wait(int msec = -1,
              QEventLoop::ProcessEventsFlags f = QEventLoop::AllEvents);
    bool hasCapturedSignal() const;

public Q_SLOTS:
    void cancelWait();

private:
    void timerEvent(QTimerEvent *e);
};

}   // namespace Qxt


#if QXTSIGNALGLOBALNAMESPACE
typedef Qxt::SignalWaiter QxtSignalWaiter;
#endif

#endif // QXTSIGNALWAITER_H
