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

#ifndef PSCHEMAELEMENT_H
#define PSCHEMAELEMENT_H

#include "pwfengine_global.h"
#include <QExplicitlySharedDataPointer>
#include <QDomElement>
#include <QList>

class PSchemaElementPrivate;

class PSchemaElement
{
public:
    PSchemaElement(const QDomElement &schemaElement = QDomElement());
    PSchemaElement(const PSchemaElement &other);
    ~PSchemaElement();
    PSchemaElement & operator =(const PSchemaElement &other); // test this
    bool setSchemaElement(const QDomElement &schemaElement);

    virtual bool isValid();
    bool isNull() const;
    bool isReference() const;

    QString type() const;
    QString name() const;
    QString attribute(const QString &attributeName) const;
    PSchemaElement directChild(const QString &elementType, const QString &elementName="") const;
    QList<PSchemaElement> switches() const;
    QList<PSchemaElement> cases() const;
    QList<PSchemaElement> requires() const;

protected:
    QDomElement schemaElement() const;

private:
    friend class PSchemaElementPrivate;
    QExplicitlySharedDataPointer<PSchemaElementPrivate> d;
};

#endif // PSCHEMAELEMENT_H
