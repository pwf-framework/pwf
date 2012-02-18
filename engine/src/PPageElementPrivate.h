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

#ifndef PPAGEELEMENTPRIVATE_H
#define PPAGEELEMENTPRIVATE_H

#include <QList>

class PPageElement;
class PPageElementList;
class QDomElement;

class PPageElementPrivate
{
public:
    PPageElementPrivate(PPageElement *_q);

public: /* Members */
    int m_start;
    int m_startLength;
    int m_end;
    int m_endLength;
    /** The associated ctag (htag or code) */
    QDomElement *m_cTag;
    /** The page element that contain this in the html page */
    PPageElement *m_parent;
    /** The list that contains all the page elements of the associated xml element */
    PPageElementList *m_parentList;
    /** The page elements that are inside this page element in the html page */
    QList<PPageElement*> m_childs;
public:
    PPageElement *q;
};

#endif // PPAGEELEMENTPRIVATE_H
