#include <QApplication>
#include <QDebug>
#include <QWidget>

#include <libdubozero/root.h>

#include <QtWebEngine>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QFileInfo>
#include <QDir>
#include <QWebChannel>

#include "zero.h"

QWebChannel * SetupWebView()
{
    QFileInfo jsFileInfo(QDir::currentPath() + "/qwebchannel.js");

    if (!jsFileInfo.exists())
        QFile::copy(":/qtwebchannel/qwebchannel.js", jsFileInfo.absoluteFilePath());

    QtWebEngine::initialize();
    QWebEngineView * view = new QWebEngineView();

    QWebChannel * channel = new QWebChannel(view->page());
    view->page()->setWebChannel(channel);

    view->load(QUrl("qrc:/demo.html"));
    view->show();

    return channel;
}

void OutputLibraryInfo(){
    DuboZero::Root * root = new DuboZero::Root();
    qDebug() << root->property("NAME");
    qDebug() << root->property("VENDOR");
    qDebug() << root->property("VERSION");
    qDebug() << root->property("REVISION");
    qDebug() << root->property("CHANGESET");
    qDebug() << root->property("BUILD");
    qDebug() << root->property("LINK");
    qDebug() << root->property("QT");
    qDebug() << root->property("PLUGIN_NAME");
    qDebug() << root->property("PLUGIN_VERSION");
    qDebug() << root->property("PLUGIN_REVISION");
}

int mainNoJavascript(int argc, char *argv[])
{
    // Get your app going
    QApplication app(argc, argv);

    // From QT side
    QWidget * w = new QWidget();
    w->show();

    // Just spit out library info
    OutputLibraryInfo();

    return app.exec();
}

void inject(QWebChannel * channel){
    // Instanciate the notifier
    // XXX DuboZero::Notifier * notifier = new DuboZero::Notifier(channel);

    // Attach objects to the javascript context
    DuboZero::Root * root = new DuboZero::Root();
    channel->registerObject("Root", root);
    // XXX channel->registerObject("Notifier", notifier);
}

int mainJavascript(int argc, char *argv[])
{
    // Get your app going
    QApplication app(argc, argv);

    // Display the webview
    QWebChannel * chan = SetupWebView();

    // Instanciate the notifier
    // XXX DuboZero::Notifier * notifier = new DuboZero::Notifier(chan);

    // Instanciate
    new Zero();


    // Attach objects to the javascript context
    DuboZero::Root * root = new DuboZero::Root();
    chan->registerObject("Root", root);
    // XXX chan->registerObject("Notifier", notifier);

    return app.exec();
}

int main(int argc, char *argv[]){
    // Delegated to javascript
    return mainJavascript(argc, argv);
    // Purely c++
    // return mainNoJavascript(argc, argv);
}