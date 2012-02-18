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

/**
  \class PSchemaElement
  \brief An explicity shared element of a schema.
*/

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
    // test this
    PSchemaElement & operator =(const PSchemaElement &other);
    /** Set the schema element and check its validity. */
    bool setSchemaElement(const QDomElement &schemaElement);
    virtual bool isValid();
    bool isNull() const;
    bool isReference() const;
    /** @return the type of the schema element, e.g. data, search, etc. */
    QString type() const;
    /** @return the name of the schema element, i.e. the value of the attribute "name". */
    QString name() const;
    /** @return the attribute of the element */
    QString attribute(const QString &attributeName) const;
    /** @return the specified direct child of this element, a null element if not exists.
        @param elementType the element type, e.g. search or data
        @param elementName the element name, e.g foo */
    PSchemaElement directChild(const QString &elementType, const QString &elementName="") const;
    QList<PSchemaElement> switches() const;
    QList<PSchemaElement> cases() const;
    QList<PSchemaElement> requires() const;
    /** Each PSchemaElement has an unique ID setted when the schema is created.
        The id can be used as an index for storing data about the schema element in other classes. */
    //int id();
protected:
    QDomElement schemaElement() const;

private:
    friend class PSchemaElementPrivate;
    QExplicitlySharedDataPointer<PSchemaElementPrivate> d;
};

#endif // PSCHEMAELEMENT_H
