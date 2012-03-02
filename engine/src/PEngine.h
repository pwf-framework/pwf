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
    QNetworkAccessManager *network() const;
    QScriptEngine *scriptEngine() const;

    void setSchemaCandidatesDirectory(const QString &directoryPath);
    QString schemaCandidatesDirectory() const;
    void setCacheDirectory(const QString &directoryPath);
    QString cacheDirectory() const;

private: /* Members */
    friend class PEnginePrivate;
    PEnginePrivate *d;
};

#endif // PENGINE_H
