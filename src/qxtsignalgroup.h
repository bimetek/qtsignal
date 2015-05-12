#ifndef QXTSIGNALGROUP_H
#define QXTSIGNALGROUP_H

#include "qxtsignal_global.h"
#include <QObject>

namespace Qxt
{

class SignalGroupPrivate;

class QXTSIGNALSHARED_EXPORT SignalGroup : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SignalGroup)
    SignalGroupPrivate * const d_ptr;

public:
    explicit SignalGroup(QObject *parent = 0);
    void addSignal(QObject *sender, const char *signal);
    void removeSignal(QObject* sender, const char* signal = 0);
    void clear();

    bool hasReceivedFirstSignal() const;
    bool hasReceivedAllSignals() const;

public Q_SLOTS:
    void reset();

Q_SIGNALS:
    void firstSignalReceived();
    void allSignalsReceived();
};

}   // namespace Qxt


#if QXTSIGNALGLOBALNAMESPACE
typedef Qxt::SignalGroup QxtSignalGroup;
#endif

#endif // QXTSIGNALGROUP_H
