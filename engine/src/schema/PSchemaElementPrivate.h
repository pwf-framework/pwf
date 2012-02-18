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

#ifndef PSCHEMAELEMENTPRIVATE_H
#define PSCHEMAELEMENTPRIVATE_H

#include <QSharedData>
#include <QDomElement>
#include <QString>

class PSchemaElement;

class PSchemaElementPrivate : public QSharedData
{
public:
    PSchemaElementPrivate(PSchemaElement *_q);
    PSchemaElementPrivate(const PSchemaElementPrivate &other);
    ~PSchemaElementPrivate();
    /** @return a list with the direct childs of from. */
    static QList<PSchemaElement> directChildsList(const QDomElement &from, const QString &elementType,
                                                  const QString &elementName="");

public: /* Members */
    QDomElement m_schemaElement;
public:
    PSchemaElement *q;
};

#endif // PSCHEMAELEMENTPRIVATE_H
