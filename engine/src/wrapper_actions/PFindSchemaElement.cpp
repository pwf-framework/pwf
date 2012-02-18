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

#include "PFindSchemaElement.h"
#include "PActionGroup.h"
#include "PEvalWrapperRequire.h"
#include "PWrapperElement.h"
#include "PSchemaElement.h"
#include <QList>

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

PWrapperElement & PFindSchemaElement::from() const
{
    return m_from;
}


QString PFindSchemaElement::elementType() const
{
    return m_elementType;
}

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
