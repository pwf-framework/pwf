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

#ifndef PWRAPPERPRIVATE_H
#define PWRAPPERPRIVATE_H

#include <QString>

class PWrapper;
class PEngine;
class PSchema;
class PWrapperElement;
class PWrapperCache;

class PWrapperPrivate
{
public:
    PWrapperPrivate(PWrapper *_q);
    /** Uniformize the url to the pattern http(s)://www.sitename.com/path/ */
    static QString &fixUrl(QString &m_url);

public: /* Members */
    PEngine *m_eng;
    PWrapper *m_parent;
    QString m_name;
    QString m_url;
    QString m_schemaCandidatesDirectory;
    PSchema *m_schema;
    /** The wrapper element for the schema root element.
        It's parent is the the main element of the parent wrapper. */
    PWrapperElement *m_rootElement;
    /** True if the detectSchema() process is already running */
    bool m_detectSchemaIsRunning;
    PWrapperCache *m_cache;
public:
    PWrapper *q;
};

#endif // PWRAPPERPRIVATE_H
