#include "qxtsignalgroup.h"
#include <QVector>

namespace Qxt
{

class SignalGroupPrivate : public QObject
{
    Q_DECLARE_PUBLIC(SignalGroup)
    SignalGroup * const q_ptr;

public:
    SignalGroupPrivate(SignalGroup *q) :
        QObject(q), q_ptr(q), emitCount(0), disconnectCount(0),
        baseSignal(QObject::staticMetaObject.methodCount()) {}

    QVector<bool> emittedSignals;
    int emitCount, disconnectCount, baseSignal;

protected:
    // since we don't have a metaobject of our own due to not using the
    // Q_OBJECT macro, we need to find methodOffset on our own.
    int qt_metacall(QMetaObject::Call _c, int _id, void **_a)
    {
        Q_Q(SignalGroup);
        Q_UNUSED(_c);
        Q_UNUSED(_a);

        // We don't care about QObject's methods, so skip them.
        _id -= baseSignal;

        int ct = emittedSignals.count();
        if (_id < 0 || _id > ct)
            return _id;

        bool &state = emittedSignals[_id];
        if (!state)
        {
            if (emitCount == 0)
                q->firstSignalReceived();
            emitCount++;
            state = true;
            if (emitCount + disconnectCount == ct)
                q->allSignalsReceived();
        }
        return _id;
    }
};

SignalGroup::SignalGroup(QObject *parent) :
    QObject(parent), d_ptr(new SignalGroupPrivate(this))
{
}

void SignalGroup::addSignal(QObject *sender, const char *signal)
{
    Q_D(SignalGroup);
    int signalId = sender->metaObject()->indexOfSignal(signal);
    if (signalId < 0)
    {
        qWarning("Qxt::SignalGroup::addSignal: no such signal %s", signal);
        return;
    }
    int methodId = d->emittedSignals.count() + d->baseSignal;
    QMetaObject::connect(sender, signalId, d, methodId);
    d->emittedSignals.append(false);
}

void SignalGroup::removeSignal(QObject *sender, const char *signal)
{
    Q_D(SignalGroup);
    if (QObject::disconnect(sender, signal, d, 0))
        d->disconnectCount++;
}

void SignalGroup::clear()
{
    Q_D(SignalGroup);
    d->emittedSignals.clear();
    d->emitCount = 0;
    d->disconnectCount = 0;
}

bool SignalGroup::hasReceivedFirstSignal() const
{
    return d_ptr->emitCount > 0;
}

bool SignalGroup::hasReceivedAllSignals() const
{
    return ((d_ptr->emitCount + d_ptr->disconnectCount)
            >= d_ptr->emittedSignals.count());
}

void SignalGroup::reset()
{
    Q_D(SignalGroup);
    d->emittedSignals.fill(false);
    d->emitCount = 0;
}

}   // namespace Qxt
