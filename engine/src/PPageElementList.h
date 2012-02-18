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

#ifndef PPAGEELEMENTLIST_H
#define PPAGEELEMENTLIST_H

#include "pwfengine_global.h"
#include <QList>
#include "PPageElement.h"

class PPageElementListPrivate;
class PPageWrapper;
class QDomElement;

class PWFENGINESHARED_EXPORT PPageElementList : public QList<PPageElement>
{
public:
    PPageElementList(PPageWrapper *pageWrapper, QDomElement *elementXML);
    int currentPosition();
    void setCurrentPosition(int pos);

private:
    friend class PPageElementPrivate;
    PPageElementListPrivate *d;
};

#endif // PPAGEELEMENTLIST_H
