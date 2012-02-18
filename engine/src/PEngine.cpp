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

#include "PEngine.h"
#include "PEnginePrivate.h"
#include <QNetworkAccessManager>
#include <QScriptEngine>
#include <QString>

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

QNetworkAccessManager *PEngine::network() const
{
    return d->m_net;
}

QScriptEngine *PEngine::scriptEngine() const
{
    return d->m_scriptEng;
}

// TODO: sanitize input!!!!
void PEngine::setSchemaCandidatesDirectory(const QString &directoryPath)
{
    // Note: remove the last / if exists
    d->m_schemaCandidatesDirectory = PEnginePrivate::removeFinalSlash(directoryPath);
}

QString PEngine::schemaCandidatesDirectory() const
{
    return d->m_schemaCandidatesDirectory;
}

// TODO: sanitize input!!!!!
void PEngine::setCacheDirectory(const QString &directoryPath)
{
    // Note: remove the last / if exists
    d->m_cacheDirectory = PEnginePrivate::removeFinalSlash(directoryPath);
}

QString PEngine::cacheDirectory() const
{
    return d->m_cacheDirectory;
}
