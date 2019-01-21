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

#ifndef DUBOZERO_ZEROHELLO_RECORD_H
#define DUBOZERO_ZEROHELLO_RECORD_H

#include "libdubozero/global.h"

#include <QObject>
//#include <QVariant>

namespace DuboZero {

class LIBDUBOZEROSHARED_EXPORT Record
{
public:
    explicit Record() {}
    explicit Record(const QString &name, const QString &regType,const QString &domain):
        serviceName(name), registeredType(regType), replyDomain(domain)
    {
    }

    explicit Record(const char *name, const char *regType, const char *domain)
    {
        serviceName = QString::fromUtf8(name);
        registeredType = QString::fromUtf8(regType);
        replyDomain = QString::fromUtf8(domain);
    }

    QString serviceName;
    QString registeredType;
    QString replyDomain;

    bool operator==(const Record &other) const {
        return  serviceName == other.serviceName
                && registeredType == other.registeredType
                && replyDomain == other.replyDomain;
    }

//    operator QVariant() const
//    {
//        return QVariant::fromValue(*this);
//    }
};

}


//Q_DECLARE_METATYPE(DuboZero::Record)


#endif // DUBOZERO_ZEROHELLO_RECORD_H
