#include "qxtsignalwaiter.h"
#include <QCoreApplication>

namespace Qxt
{

class SignalWaiterPrivate
{
    Q_DECLARE_PUBLIC(SignalWaiter)
    SignalWaiter * const q_ptr;

public:
    SignalWaiterPrivate(SignalWaiter *q) :
        q_ptr(q), ready(false), timeout(false), emitted(false), timerId(0)
    {}

    void stopTimer()
    {
        if (timerId)
            q_ptr->killTimer(timerId);
        timerId = 0;
        waiting = false;
    }

    void signalCaught()
    {
        if (!waiting)
            return;
        ready = true;
        stopTimer();
    }

    bool ready;
    bool timeout;
    bool emitted;
    bool waiting;
    int timerId;
};


SignalWaiter::SignalWaiter(const QObject *sender, const char *signal) :
    QObject(), d_ptr(new SignalWaiterPrivate(this))
{
    Q_ASSERT(sender && signal);
    connect(sender, signal, this, SLOT(signalCaught()));
}

SignalWaiter::~SignalWaiter()
{
    delete d_ptr;
}

bool SignalWaiter::wait(const QObject *sender, const char *signal, int msec,
                        QEventLoop::ProcessEventsFlags flags)
{
    SignalWaiter waiter(sender, signal);
    return waiter.wait(msec, flags);
}

bool SignalWaiter::wait(int msec, QEventLoop::ProcessEventsFlags flags)
{
    Q_D(SignalWaiter);
    d->ready = false;
    d->emitted = false;

    if (msec < -1 || msec == 0)
        return false;

    if (msec != -1)
        d->timerId = startTimer(msec);
    else
        d->timerId = 0;

    // Make sure to wait for events.
    flags |= QEventLoop::WaitForMoreEvents;

    // Begin waiting.
    d->waiting = true;
    while (!d->ready && !d->timeout)
        QCoreApplication::processEvents(flags);

    // Clean up.
    d->stopTimer();
    d->emitted = d->ready;
    d->waiting = false;

    return d->ready;
}

bool SignalWaiter::hasCapturedSignal() const
{
    return d_ptr->emitted;
}

void SignalWaiter::cancelWait()
{
    Q_D(SignalWaiter);

    // Fake a signalCount() call to terminate wait.
    d->signalCaught();
}

void SignalWaiter::timerEvent(QTimerEvent *e)
{
    QObject::timerEvent(e);
    cancelWait();
}

}   // namespace Qxt

#include "moc_qxtsignalwaiter.cpp"
