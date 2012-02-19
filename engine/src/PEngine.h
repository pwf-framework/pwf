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

#ifndef PENGINE_H
#define PENGINE_H

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

#include "pwfengine_global.h"
#include <QObject>

class PEnginePrivate;
class QNetworkAccessManager;
class QScriptEngine;
class QString;

class PWFENGINESHARED_EXPORT PEngine : public QObject {
Q_OBJECT

public:
    PEngine();
    ~PEngine();
    /** The network shared among all the wrappers */
    QNetworkAccessManager *network() const;
    /** The script engine shared among all the wrappers */
    QScriptEngine *scriptEngine() const;
    /** Sets the root directory where are located all the wrapper schemas.
        @note the final / is removed (if it's not the only character) */
    void setSchemaCandidatesDirectory(const QString &directoryPath);
    /** @see setSchemaCandidatesDirectory */
    QString schemaCandidatesDirectory() const;
    /** Sets the cache directory, shared by all sites unless otherwise specified.
        @note: the final / is removed  */
    void setCacheDirectory(const QString &directoryPath);
    /** @see setCacheDirectory */
    QString cacheDirectory() const;

private:
    friend class PEnginePrivate;
    PEnginePrivate *d;
};

#endif // PENGINE_H
