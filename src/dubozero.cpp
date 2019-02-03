/*
 * Copyright (c) 2019, Dubo Dubon Duponey <dubodubonduponey+github@pm.me>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

void DuboZero::registerService(const QString &name, const QString &regType, int port, const QString &domain = QString())
{
    // Call upon the registrar
    Registrar * registrar = new Registrar();
    // Create our record (name+hostname+port, type)
    Record ourselves = Record(name + QString::fromLatin1(" (") + QHostInfo::localHostName() + QString::fromLatin1(")"), regType, domain);
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
        listing << (addr.toString() + QString::fromLatin1(":") + QString::number(port));
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


