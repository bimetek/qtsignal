#ifndef QXTMULTISIGNALWAITER_H
#define QXTMULTISIGNALWAITER_H

#include "qxtsignal_global.h"
#include "qxtsignalgroup.h"
#include <QEventLoop>

namespace Qxt
{

class QXTSIGNALSHARED_EXPORT MultiSignalWaiter : public SignalGroup
{
    Q_OBJECT

public:
    MultiSignalWaiter(QObject *parent = 0);
    bool waitForAny(int msec = -1,
                    QEventLoop::ProcessEventsFlags f = QEventLoop::AllEvents);
    bool waitForAll(int msec = -1,
                    QEventLoop::ProcessEventsFlags f = QEventLoop::AllEvents);
};

}   // namespace Qxt

#if QXTSIGNALGLOBALNAMESPACE
typedef Qxt::MultiSignalWaiter QxtMultiSignalWaiter;
#endif

#endif // QXTMULTISIGNALWAITER_H
