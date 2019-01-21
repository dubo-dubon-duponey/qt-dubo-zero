/**
 * Copyright (c) 2019, Dubo Dubon Duponey <dubodubonduponey+github@pm.me>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "zero.h"
#include <libdubozero/browser.h>
#include <libdubozero/registrar.h>
#include <QTime>

using namespace DuboZero;

Zero::Zero(QObject *parent) :
    QObject(parent)
{
    // Service type
    QString serviceType = QString("_dubo._tcp");
    // Service name
    QString sayMyNameBaby = QString("Raymond");

    // Take a port (XXX should really be your service port)
    int high = 50000;
    int low = 8080;
    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));
    int port = qrand() % ((high + 1) - low) + low;

    // Call upon the registrar
    registrar = new Registrar(this);
    // Create our record (name+hostname+port, type)
    Record ourselves = Record(sayMyNameBaby.append(QHostInfo::localHostName()).append(QString::number(port)), serviceType, "");
    // And register ourselves
    registrar->registerService(ourselves, static_cast<quint16>(port));
    // Connect to be notified that registration went through
    connect(registrar, SIGNAL(registered(const Record &)), this, SLOT(registeredSlot(const Record &)));

    // Now, start a browser
    Browser * browser = new Browser();
    // And discover for our serviceType
    browser->browse(serviceType);
    // Connect the browser to our slot
    connect(browser, SIGNAL(changed(const QList<Record>)), this, SLOT(newAnnounceSlot(const QList<Record>)));
}

void Zero::newAnnounceSlot(const QList<Record> &list)
{
    // Get signaled when we discover new stuff
    qDebug() << "Hohoho, there is somebody in there! Vous voulez du chocolat?";
    foreach (DuboZero::Record record, list) {
        if(registrar->record() == record){
            qDebug() << "Not interested by our own record";
        }else{
            qDebug() << " **** FOUND ****";
            qDebug() << record.registeredType;
            qDebug() << record.replyDomain;
            qDebug() << record.serviceName;

            // And resolve it as well
            Resolver * r = new Resolver(this);
            r->connect(r, SIGNAL(resolved(const QHostInfo,int)), this, SLOT(resolveCompleteSlot(const QHostInfo, int)));
            r->resolve(record);
        }
    }
}

void Zero::resolveCompleteSlot(const QHostInfo & qhi,int port)
{
    // Get signaled when we end resolving some discovered stuff
    qDebug() << "Something was resolved tada!";
    QList<QHostAddress> list = qhi.addresses();
    foreach(QHostAddress addr, list){
        qDebug() << addr.toString() << port;
    }
}

void Zero::registeredSlot(const Record &)
{
    qDebug() << "Yeah, we registered ourselves properly. Kind of cool.";
}
