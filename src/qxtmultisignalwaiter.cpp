#include "qxtmultisignalwaiter.h"
#include "qxtsignalwaiter.h"

namespace Qxt
{

MultiSignalWaiter::MultiSignalWaiter(QObject *parent) : SignalGroup(parent)
{
}

bool MultiSignalWaiter::waitForAny(int msec, QEventLoop::ProcessEventsFlags f)
{
    if (hasReceivedFirstSignal())
        return true;
    return SignalWaiter::wait(this, SIGNAL(firstSignalReceived()), msec, f);
}

bool MultiSignalWaiter::waitForAll(int msec, QEventLoop::ProcessEventsFlags f)
{
    if (hasReceivedAllSignals())
        return true;
    return SignalWaiter::wait(this, SIGNAL(allSignalsReceived()), msec, f);
}

}   // namespace Qxt
