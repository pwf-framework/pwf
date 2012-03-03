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
  \class PSchema
  \brief The schema of a PWrapper.

  The root element of the schema document.
*/

#include "PSchema.h"
#include "PSchemaPrivate.h"
#include <QFile>
#include <QDomDocument>


/** The PSchemaPrivate is searched in the PEngine and used if found, otherwise a new one will be
    created.
*/
PSchema::PSchema(const QString &name)
{
    // TODO: set the private (d) for this name to the one saved on PEngine, if exists.

    d = new PSchemaPrivate(this);

    setName(name);
}

PSchema::~PSchema()
{
    delete d;
}

/** Set the schema name. */
void PSchema::setName(const QString &name)
{
    d->m_name = name;
}

/** @return the schema name. */
QString PSchema::name() const
{
    return d->m_name;
}

/** @return true if no valid document has been set */
bool PSchema::isNull() const
{
    return d->m_document.isNull();
}

/** @param fileName the document filename
    @note the element will be the document root.
    @return true if the document has been successfully loaded.
*/
bool PSchema::setDocument(const QString &fileName)
{
    QFile schemaFile(fileName);
    if (!schemaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error message here: cannot open schema file
        qDebug("cannot open schema file");
        return false;
    }

    QByteArray schemaContent = schemaFile.readAll();
    if (schemaContent.isEmpty()) {
        // error message here: empty file or read error
        qDebug("empty file or read error");
        return false;
    }

    if (!d->m_document.setContent(schemaContent)) {
        // error message here: xml parsing failed, invalid xml file
        qDebug("xml parsing failed, invalid xml file");
        return false;
    }

    // replace the include nodes
    if (!d->parseIncludeNodes()) {
        // error message here: parsing of include nodes failed
        qDebug("parsing of include nodes failed");
        return false;
    }

    // set the root element of the schema as the document root
    d->rootElement.setSchemaElement(d->m_document.documentElement());

    // set the schema directory
    if (!fileName.contains("/")) {
        // just a relative file, e.g. "schema.xml"
        d->m_directory = "";
    } else {
        d->m_directory = fileName.left(fileName.lastIndexOf("/")); // e.g "tawe/schema.xml" -> "tawe"
    }

    return true;
}

/** @return the directory of the schema. */
QString PSchema::directory() const
{
    return d->m_directory;
}

/** @return the root element of the schema. The element is null if the schema document has not been
            (successfully) set. */
PSchemaElement PSchema::rootElement()
{
    return d->rootElement;
}
