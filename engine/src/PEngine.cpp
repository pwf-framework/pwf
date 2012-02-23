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
  @class PEngine
  @brief The main class.

  This is the first class to instantiate when using the library,
  its purpose is to mantain all the wrappers common data, such as:

  - the network access manager, see network()
  - the (javascript) script engine, see scriptEngine()
  - the schemas root directory, see setSchemaCandidatesDirectory()
  - the cache root directory, see setCacheDirectory()

  The first two are automatically created on construction and automatically managed by wrappers,
  so there is no need to worry about them at all. However you could want to get them for specifying some special option,
  althrough this is not explicitally required.
 */

#include "PEngine.h"
#include "PEnginePrivate.h"
#include <QNetworkAccessManager>
#include <QScriptEngine>
#include <QString>
#include <QDir>

PEngine::PEngine()
{
    d = new PEnginePrivate(this);

    d->m_net = new QNetworkAccessManager(this);
    d->m_scriptEng = new QScriptEngine(this);
}

PEngine::~PEngine()
{    
    delete d;
}

/** The network shared among all the wrappers */
QNetworkAccessManager *PEngine::network() const
{
    return d->m_net;
}

/** The script engine shared among all the wrappers */
QScriptEngine *PEngine::scriptEngine() const
{
    return d->m_scriptEng;
}

/** Sets the root directory where are located all the wrapper schemas.
    @note the path is cleaned by using QDir::cleanPath()
    @warning always use the "/" separator, example: "c:/foo/bar" OK, "c:\foo\bar" NO.
*/
// TODO: sanitize input!!!!
void PEngine::setSchemaCandidatesDirectory(const QString &directoryPath)
{
    d->m_schemaCandidatesDirectory = QDir::cleanPath(directoryPath);
}

/** @see setSchemaCandidatesDirectory() */
// TODO: what to do with symbolic links? (apply also to cacheDirectory())
QString PEngine::schemaCandidatesDirectory() const
{
    return d->m_schemaCandidatesDirectory;
}

/** Sets the cache directory, shared by all sites unless otherwise specified.
    @note the path is cleaned by using QDir::cleanPath()
    @warning always use the "/" separator, example: "c:/foo/bar" OK, "c:\foo\bar" NO.
*/
// TODO: sanitize input!!!!!
void PEngine::setCacheDirectory(const QString &directoryPath)
{
    d->m_cacheDirectory = QDir::cleanPath(directoryPath);
}

    /** @see setCacheDirectory */
QString PEngine::cacheDirectory() const
{
    return d->m_cacheDirectory;
}
