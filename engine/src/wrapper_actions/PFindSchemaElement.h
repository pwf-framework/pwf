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

#ifndef PFINDSCHEMAELEMENT_H
#define PFINDSCHEMAELEMENT_H

#include "PAction.h"
#include "PSchemaElement.h"
#include <QString>

class PWrapperElement;

class PFindSchemaElement : public PAction
{

public:
    PFindSchemaElement(PWrapperElement &from, const QString &elementType,
                       const QString &elementName="", QObject *parent=NULL);
    /* Used to find the element that is referenced by the specified reference element.
        The search goes by alternating top-down searches in the parent siblings and checks (for the element)
        on the parent, i.e. visiting the tree like an incremental fountain's jet. */
    //PFindSchemaElement(PWrapper *wrapper, const PSchemaElement &reference, QObject *parent=NULL);

    PWrapperElement &from() const;
    QString elementType() const;
    QString elementName() const;

    void setSharedSchemaElement(const PSchemaElement &schemaElement);
    PSchemaElement foundSchemaElement() const;

public slots:
    void start();

signals:
    void found(const PSchemaElement &);

private: /* Members */
    /** The search starting point. */
    PWrapperElement &m_from;
    QString m_elementType;
    QString m_elementName;
    /** It's NULL until found. */
    PSchemaElement m_foundSchemaElement;
    /** The found element if the search on the childs fails. */
    PSchemaElement m_sharedSchemaElement;
};

#endif // PFINDSCHEMAELEMENT_H
