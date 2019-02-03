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

#ifndef DUBOZERO_ZEROHELLO_ZERO_H
#define DUBOZERO_ZEROHELLO_ZERO_H

#include "libdubozero/global.h"
#include "libdubozero/record.h"

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QStringList>
#include <QtNetwork/QHostInfo>

namespace DuboZero {

class LIBDUBOZEROSHARED_EXPORT DuboZero : public QObject
{
    Q_OBJECT
public:
    explicit DuboZero(QObject * parent = nullptr);
    Q_INVOKABLE void registerService(const QString &name, const QString &regType, int port, const QString &domain);
    Q_INVOKABLE void resolve(const QString &name, const QString &regType, const QString &domain);
    Q_INVOKABLE void browse(const QString & serviceType);

signals:
    void registered(const QString &name, const QString &regType, const QString &domain);
    void resolved(QStringList list);
    void discovered(QStringList list);

private slots:
    void resolveCompleteSlot(const QHostInfo & qhi,int port);
    void registeredSlot(const Record & record);
    void newAnnounceSlot(const QList<Record> list);

};

}


#endif // DUBOZERO_ZEROHELLO_ZERO_H
