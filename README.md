# DuboZero

> "Dubo Components" are lightweight, targeted c++ libraries meant for QT applications.
> They aim at providing *simple to use* interfaces for a range of functionality
(notification, crash reporting, zero conf, application update, torrent, etc).
> Fully scriptable, they are primarily meant for javascript (from a QWebEngine) - thought they are usable as well in plain QT.
> Put together, these components should provide a comprehensive foundation for these building a "WebRunner", similarly to Electron.

DuboZero is a (tentatively) cross-platform zeronconf library.

macOS only for now.

Licensed under BSD2.

## How to use

1. Build the library (static by default, see project.pri to change it to a shared library if you need)
2. Link it into your app
```
LIBS += -ldubozero
# If linking statically
DEFINES += LIBDUBOZERO_USE_STATIC
```
3. Use it
```
XXX fixme see demo
```

For more, see main.cpp in the demo repository.

## API

XXX

## WebView use

XXX

## Gotchas

XXX

Largely borrowed from: http://doc.qt.digia.com/qq/qq23-bonjour.html

