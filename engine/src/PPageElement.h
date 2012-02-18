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

#ifndef PPAGEELEMENT_H
#define PPAGEELEMENT_H

#include "pwfengine_global.h"
#include <QList>
#include <QString>

class PPageElementPrivate;
class PPageElementList;
class QDomElement;

class PWFENGINESHARED_EXPORT PPageElement
{
public:
    PPageElement(int start, int startLength, int end, int endLength,
                 QDomElement *cTag, PPageElement *parent, PPageElementList *parentList);
    ~PPageElement();
    /** Set a page element as a child for this.
        @param child the page element to add as a child */
    void addChild(const PPageElement &child);
    /** Extract all the page elements of the child with the given xml element name
        @param xmlElement the xml element name */
    QList<PPageElement*> child(const QString &xmlElement);
    /** Return the next page element of the child with the given xml element name
        @param xmlElement the xml element name*/
    PPageElement *next(const QString &xmlElement);
    /** Return the html text of this page element */
    QString text();

private:
    friend class PPageElementPrivate;
    PPageElementPrivate *d;
};

#endif // PPAGEELEMENT_H
