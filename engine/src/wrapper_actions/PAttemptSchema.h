/*
    Copyright 2011, 2012 Manuel Dell'Elce

    This file is part of pwfengine.

    pwfengine is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    pwfengine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with pwfengine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PATTEMPTSCHEMA_H
#define PATTEMPTSCHEMA_H

#include "PAction.h"
#include <QString>

class PWrapper;
class PSchema;
class PWrapperCache;

class PAttemptSchema : public PAction
{

public:
    PAttemptSchema(const QString &schemaName, PWrapper *wrapper, PWrapperCache *wrapperCache);
    ~PAttemptSchema();

    PSchema *schema() const;

public slots:
    virtual void start();
    //virtual void stop();

private: /* Members */
    QString m_schemaName;
    PWrapper *m_wrapper;
    PWrapperCache *m_wrapperCache;
    PSchema *m_schema;
};

#endif // PATTEMPTSCHEMA_H
