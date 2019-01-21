#include "libdubozero/dubozero.h"

#include "libdubozero/registrar.h"
#include "libdubozero/browser.h"
#include "libdubozero/resolver.h"
#include <QSocketNotifier>
#include <dns_sd.h>


namespace DuboZero {

DuboZero::DuboZero(QObject *parent) :
    QObject(parent)
{
}

void DuboZero::registerService(const QString &name, const QString &regType, int port, const QString &domain = "")
{
    // Call upon the registrar
    Registrar * registrar = new Registrar();
    // Create our record (name+hostname+port, type)
    Record ourselves = Record(name + " (" + QHostInfo::localHostName() + ")", regType, domain);
    // And register ourselves
    registrar->registerService(ourselves, static_cast<quint16>(port));
    // Connect to be notified that registration went through
    connect(registrar, SIGNAL(registered(const Record &)), this, SLOT(registeredSlot(const Record &)));
}

void DuboZero::browse(const QString &serviceType)
{
    // Now, start a browser
    Browser * browser = new Browser(this);
    // And discover for our serviceType
    browser->browse(serviceType);
    // Connect the browser to our slot
    connect(browser, SIGNAL(changed(const QList<Record>)), this, SLOT(newAnnounceSlot(const QList<Record>)));
}

void DuboZero::resolve(const QString &name, const QString &regType, const QString &domain)
{
    Resolver * r = new Resolver(this);
    Record * record = new Record(name, regType, domain);
    r->connect(r, SIGNAL(resolved(const QHostInfo,int)), this, SLOT(resolveCompleteSlot(const QHostInfo, int)));
    r->resolve(* record);
}

void DuboZero::resolveCompleteSlot(const QHostInfo & qhi,int port)
{
    QStringList listing;
    // Get signaled when we end resolving some discovered stuff
    QList<QHostAddress> list = qhi.addresses();
    foreach(QHostAddress addr, list){
        listing << (addr.toString() + ":" + QString::number(port));
    }
    emit resolved(listing);
}

void DuboZero::registeredSlot(const Record & record)
{
    emit registered(record.serviceName, record.registeredType, record.replyDomain);
}

void DuboZero::newAnnounceSlot(const QList<Record> list)
{
    QStringList listing;
    qDebug() << "Got stuff";
    for(int x = 0; x < list.length(); x++){
        Record rec = list.at(x);
        listing << rec.serviceName << rec.registeredType << rec.replyDomain;
    }
    emit discovered(listing);
}

}


