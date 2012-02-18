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

#ifndef PPAGEELEMENTLISTPRIVATE_H
#define PPAGEELEMENTLISTPRIVATE_H

class PPageElementList;
class PPageWrapper;
class QDomElement;

class PPageElementListPrivate
{
public:
    PPageElementListPrivate(PPageElementList *_q);

public: /* Members */
    PPageWrapper *m_pageWrapper;
    QDomElement *m_elementXML;
    /** used for iteration purpose */
    int m_currentPos;
public:
    PPageElementList *q;
};

#endif // PPAGEELEMENTLISTPRIVATE_H
