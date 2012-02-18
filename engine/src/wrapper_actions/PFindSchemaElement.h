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

/**
  \class PFindSchemaElement
  \brief Given a number of possible alternatives, emit a status success with the valid schema element for the
         given wrapper, status failure otherwise.

  This class is actually used as a tree of action groups, each path from the root to a leaf being
  an alternative for the given schema element.
  Each tree node can contains both another instances of this class or a number of
  require parser, but not mixed. The first type of nodes represents a schema <switch> (switch action), while
  the second a <case> (case action).
  The case action must have the success schema element, e.g the schema element that is valid if all the requires are
  evaluated succesfully.
  The switch action could only have the shared schema element, e.g the schema element that is valid if all
  its child case actions fail, if it's not specified, the action will just emit a status failure.

  This class is actually used as a growing tree of finders, each of them starting its search from a
  descendent/ancestor of the schema element to find.
  The schema is visited in some way, at each step the element is searched and the encountered requires are evaluated,
  continuing the visit if needed.

  If the visit ends without having found the element, the search continues in the parent schema by using
  a top-down visit, continuing to going up to the parent schemas until possible or needed.
*/

#include "PAction.h"
#include "PSchemaElement.h"
#include <QString>

class PWrapperElement;

class PFindSchemaElement : public PAction
{

public:
    /** Used to find an element by specifying its type and name.
        The "from" schema is visited in a top-down fashion: at each step, the element is searched and saved and
        the requires evaluation took place, if it fails, then the finder fails too,
        otherwise, new finders for each child case and switch schema element are created;
        the found element will be that of the first child finder to have succeded, or if they all fail,
        the previously saved element, otherwise, if no element is saved, the find action will fail.
 */
    PFindSchemaElement(PWrapperElement &from, const QString &elementType,
                       const QString &elementName="", QObject *parent=NULL);
    /** Used to find the element that is referenced by the specified reference element.
        The search goes by alternating top-down searches in the parent siblings and checks (for the element)
        on the parent, i.e. visiting the tree like an incremental fountain's jet. */
    //PFindSchemaElement(PWrapper *wrapper, const PSchemaElement &reference, QObject *parent=NULL);
    /** @return m_startingSchemaElement */
    PWrapperElement &from() const;
    /** @return the type of the element to find */
    QString elementType() const;
    /** @return the name of the element to find */
    QString elementName() const;
    void start();
    void setSharedSchemaElement(const PSchemaElement &schemaElement);
    PSchemaElement foundSchemaElement() const;

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
