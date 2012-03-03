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

#ifndef PSCHEMAPRIVATE_H
#define PSCHEMAPRIVATE_H

#include <QDomDocument>
#include <QString>
#include "PSchemaElement.h"

class PSchema;

class PSchemaPrivate
{
public:
    PSchemaPrivate(PSchema *_q);
    bool parseIncludeNodes();

public:
    QDomDocument m_document;
    QString m_directory;
    QString m_name;
    PSchemaElement rootElement;
public:
    PSchema *q;
};

#endif // PSCHEMAPRIVATE_H
