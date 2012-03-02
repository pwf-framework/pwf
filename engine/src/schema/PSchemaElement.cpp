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
  \class PSchemaElement
  \brief An explicity shared element of a schema.
*/

#include "PSchemaElement.h"
#include "PSchemaElementPrivate.h"

PSchemaElement::PSchemaElement(const QDomElement &schemaElement)
{
    d = new PSchemaElementPrivate(this);

    if (!setSchemaElement(schemaElement)) {
        // error
        return;
    }
}

PSchemaElement::PSchemaElement(const PSchemaElement &other)
    : d(other.d)
{
}

PSchemaElement::~PSchemaElement()
{
}

PSchemaElement & PSchemaElement::operator =(const PSchemaElement &other)
{
    d = other.d;
}

/** Set the schema element and check its validity. */
bool PSchemaElement::setSchemaElement(const QDomElement &schemaElement)
{
    d->m_schemaElement = schemaElement;
    if (!isValid()) {
        qDebug("Invalid schema element");
        d->m_schemaElement = QDomElement();
        return false;
    }

    return true;
}

QDomElement PSchemaElement::schemaElement() const
{
    return d->m_schemaElement;
}

bool PSchemaElement::isValid()
{
    // a null schema element is valid because it's a placeholder
    if (d->m_schemaElement.isNull()) {
        return true;
    }

    // STUB
    return true;
}

bool PSchemaElement::isNull() const
{
    return d->m_schemaElement.isNull();
}

bool PSchemaElement::isReference() const
{
    return (d->m_schemaElement.attribute("ref") == "true");
}

/** @return the type of the schema element, e.g. data, search, etc. */
QString PSchemaElement::type() const
{
    /** Example: an element <foo>...</foo> will return foo */
    return d->m_schemaElement.tagName();
}

/** @return the name of the schema element, i.e. the value of the attribute "name". */
QString PSchemaElement::name() const
{
    return attribute("name");
}

/** @return the attribute of the element */
QString PSchemaElement::attribute(const QString &attributeName) const
{    
    return d->m_schemaElement.attribute(attributeName);
}

/** @return the specified direct child of this element, a null element if not exists.
    @param elementType the element type, e.g. search or data
    @param elementName the element name, e.g foo
*/
PSchemaElement PSchemaElement::directChild(const QString &elementType, const QString &elementName) const
{
    for (QDomElement el = d->m_schemaElement.firstChildElement(elementType);
         !el.isNull();
         el = el.nextSiblingElement(elementType))
    {
        if (el.attribute("name") == elementName) {
            return PSchemaElement(el);
        }
    }

    return PSchemaElement();
}

QList<PSchemaElement> PSchemaElement::switches() const
{
    return PSchemaElementPrivate::directChildsList(d->m_schemaElement, "switch");
}

QList<PSchemaElement> PSchemaElement::cases() const
{
    return PSchemaElementPrivate::directChildsList(d->m_schemaElement, "case");
}

QList<PSchemaElement> PSchemaElement::requires() const
{
    return PSchemaElementPrivate::directChildsList(d->m_schemaElement, "require");
}
