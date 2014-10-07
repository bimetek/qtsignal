# QxtSignal

Signal-related classes extracted from LibQxt, namespaced and modernised for Qt 4.7+.

Includes:

* Signal waiter
* Signal group
* Multi-signal waiter

## Porting from LibQxt

This library requires Qt 4.7 or newer, instead of Qt 4.2 which is required by LibQxt. All classes are namespaced in `Qxt` and have `Qxt` prefix stripped from their class names. For example, LibQxt’s `QxtSignalWaiter` would correspond to `Qxt::SignalWaiter` in this library.

Please report any incompatibilities.

## License

QxtSignal is released under LGPL 2.1 and CPL 1.0 (same with LibQxt).
