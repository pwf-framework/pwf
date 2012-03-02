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

#include "PFindSchemaElement.h"
#include "PActionGroup.h"
#include "PEvalWrapperRequire.h"
#include "PWrapperElement.h"
#include "PSchemaElement.h"
#include <QList>

/** Used to find an element by specifying its type and name.
    The "from" schema is visited in a top-down fashion: at each step, the element is searched and saved and
    the requires evaluation took place, if it fails, then the finder fails too,
    otherwise, new finders for each child case and switch schema element are created;
    the found element will be that of the first child finder to have succeded, or if they all fail,
    the previously saved element, otherwise, if no element is saved, the find action will fail.
*/
PFindSchemaElement::PFindSchemaElement(PWrapperElement &from, const QString &elementType,
                                       const QString &elementName, QObject *parent)
    : PAction(parent), m_from(from),
      m_elementType(elementType), m_elementName(elementName)
{
}

/* MOVE THIS IN ANOTHER CLASS LIKE TFindReferenced */
/*
PFindSchemaElement::PFindSchemaElement(PWrapper *wrapper, const PSchemaElement &reference, QObject *parent)
    : PAction(parent), m_wrapper(wrapper), m_startingSchemaElement(reference),
      m_elementType(reference.type()), m_elementName(reference.name())
{
}
*/

/** @return m_startingSchemaElement */
PWrapperElement & PFindSchemaElement::from() const
{
    return m_from;
}

/** @return the type of the element to find */
QString PFindSchemaElement::elementType() const
{
    return m_elementType;
}

/** @return the name of the element to find */
QString PFindSchemaElement::elementName() const
{
    return m_elementName;
}

void PFindSchemaElement::start()
{
    /* 1) add actions
       2) start actions
       3) wait signals */

    // Evalutate requires
    QList<PSchemaElement> childRequireSchemas = m_from.schema().requires();
    if (!childRequireSchemas.isEmpty()) {
        // there is at least one require to evaluate
        PActionGroup *evalRequireGroup = new PActionGroup(this);
        evalRequireGroup->setSingleStatusToStop(PAction::StatusFailure, PAction::StatusFailure);
        for (int i=0; i<childRequireSchemas.length(); i++) {
            // add the require evaluator for the current require to the action group
            PWrapperRequire *require = m_from.childRequire(childRequireSchemas.at(i));
            PEvalWrapperRequire *evalRequire = new PEvalWrapperRequire(require);
            evalRequireGroup->addAction(evalRequire);
            // fail if the group fails
            connect(evalRequireGroup, SIGNAL(failure(PAction::StatusType)), this, SLOT(finish(PAction::StatusType)));
        }

    }
}
