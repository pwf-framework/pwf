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

#ifndef PSCHEMA_H
#define PSCHEMA_H

#include "pwfengine_global.h"
#include "PSchemaElement.h"

class PSchemaPrivate;

class PWFENGINESHARED_EXPORT PSchema : public PSchemaElement
{
public:
    PSchema(const QString &name);
    ~PSchema();
    void setName(const QString &name);
    QString name() const;

    bool isNull() const;
    bool setDocument(const QString &fileName);
    //virtual bool isValid();
    QString directory() const;

private: /* Members */
    friend class PSchemaPrivate;
    PSchemaPrivate *d;
};

#endif // PSCHEMA_H
