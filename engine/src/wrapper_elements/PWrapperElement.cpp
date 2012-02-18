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

#include "PWrapperElement.h"
#include "PWrapperElementPrivate.h"
#include "PWrapper.h"
#include "PFindSchemaElement.h"

PWrapperElement::PWrapperElement(PWrapper *wrapper, PWrapperElement *parent, PSchemaElement elementSchema)
    : QObject(parent)
{
    d = new PWrapperElementPrivate(this);

    d->m_wrapper = wrapper;
    d->m_parentElement = parent;
    setSchema(elementSchema);
}

// since the search starts from parent, passing a null value for it is meaningless, so a reference is used.
PWrapperElement::PWrapperElement(PWrapper *wrapper, PWrapperElement &parent,
                                 const QString &elementType, const QString &elementName)
{
    d = new PWrapperElementPrivate(this);

    d->m_wrapper = wrapper;
    d->m_parentElement = &parent;

    // create the find element object
    d->m_schemaFinder = new PFindSchemaElement(parent, elementType, elementName, this);
    connect(d->m_schemaFinder, SIGNAL(found(PSchemaElement)), this, SLOT(setSchema(PSchemaElement)));
    d->m_schemaFinder->start();
}

PWrapperElement::~PWrapperElement()
{
    d->m_schemaFinder->deleteLater();

    delete d;
}


PWrapper * PWrapperElement::wrapper() const
{
    return d->m_wrapper;
}

void PWrapperElement::setSchema(const PSchemaElement &elementSchema)
{
    d->m_schema = elementSchema;
    // TODO: delete all the old schema stuff (child elements, etc.)
}

PSchemaElement PWrapperElement::schema() const
{
    return d->m_schema;
}

QString PWrapperElement::type() const
{
    if (d->m_schema.isNull()) {
        return d->m_schemaFinder->elementType();
    }

    return d->m_schema.type();
}

// get it from the element schema or from the TFindElement
QString PWrapperElement::name() const
{
    if (d->m_schema.isNull()) {
        return d->m_schemaFinder->elementName();
    }

    return d->m_schema.name();
}

PFindSchemaElement * PWrapperElement::schemaFinder() const
{
    return d->m_schemaFinder;
}

PWrapperElement * PWrapperElement::childElement(const PSchemaElement &elementSchema)
{
    /*
    if (elementSchema.isNull()) { return NULL; }

    PWrapperElement *element = d->elementsWithSchema[elementSchema];
    if (element->schema().isNull()) {
        // new element
        // rationale: if the element with the specified schema doesn't exist, the [] operator
        // insert a default constructed value into the hash table and return a reference to it
        element->setSchema(elementSchema);
    }
    return element;
    */
}

PWrapperRequire * PWrapperElement::childRequire(const PSchemaElement &requireSchema)
{
    // DUMMY
}
