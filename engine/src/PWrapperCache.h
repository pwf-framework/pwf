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

#ifndef PWRAPPERCACHE_H
#define PWRAPPERCACHE_H

#include <QDomDocument>
#include "PSchemaElement.h"

class PWrapper;

class PWrapperCache : public QDomDocument
{
public:
    PWrapperCache(PWrapper *wrapper, PWrapperCache *upperCache = 0);

    /** @return the cached schema name, empty if not exists. */
    QString schemaName();

    /** The element schema string representation is hashed and compared to the ones saved in the cache.
        @return empty string if not found. */
    QString elementValue(PSchemaElement elementSchema);
    /** The element is cached by storing its value together with the hashed string representation of its schema */
    void setElementValue(PSchemaElement elementSchema, QString value);

private: /* Members */
    PWrapper *m_wrapper;
    PWrapperCache *m_upperCache;
};

#endif // PWRAPPERCACHE_H
