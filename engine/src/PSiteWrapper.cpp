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

#include "PSiteWrapper.h"
#include "PSiteWrapperPrivate.h"
#include "PEngine.h"
#include "PPageWrapper.h"
#include <QString>
#include <QDir>
#include <QRegExp>
#include "PAction.h"
#include "PActionGroup.h"
#include "PEnginePrivate.h" // for the static function removeFinalSlash

const QString _siteSchemaRelativeFileName = "siteschema.xml";
const QString _siteCacheRelativeFileName = "sitecache.xml";
// _namePattern defined in PWrapper.h

PSiteWrapper::PSiteWrapper(PEngine *engine) : PWrapper(engine, NULL)
{
    d = new PSiteWrapperPrivate(this);
}

PSiteWrapper::~PSiteWrapper()
{
    delete d;
}

bool PSiteWrapper::setUrl(const QString &url)
{
    // TODO: check if url matches the site format
    if (true /* STUB */) {
        return PWrapper::setUrl(PSiteWrapperPrivate::fixUrl(url));
    }

    return false;
}

void PSiteWrapper::addPageWrapper(PPageWrapper *pageWrapper)
{
    if (pageWrapper == 0) { return; }
    // check if the page wrapper already exists
    for (int i=0; i<d->m_pageWrappers.length(); i++) {
        if (d->m_pageWrappers.at(i) == pageWrapper) { return; }
    }

    d->m_pageWrappers.append(pageWrapper);
}

QString PSiteWrapper::schemaFileName(const QString &schemaName)
{
    QString schemaDir = schemaDirectory(schemaName);
    if (schemaDir.isEmpty()) {
        // invalid schema name or directory
        return "";
    }

    return schemaDir + "/" + _siteSchemaRelativeFileName;
}

QString PSiteWrapper::schemaDirectory(const QString &schemaName)
{
    // Disallow illegal characters for the schema name
    QRegExp dirPattern(_namePattern);
    if (!dirPattern.exactMatch(schemaName)) {
        return "";
    }

    QString fileName;
    QString schemaCandidatesDir = schemaCandidatesDirectory();
    if (!schemaCandidatesDir.isEmpty()) {
        fileName = schemaCandidatesDir + "/";
    }
    fileName += schemaName;
    return fileName;
}

QList<QString> PSiteWrapper::schemaCandidateNames()
{
    QList<QString> candidates;

    // get all the site schemas directories
    QDir engineDir(schemaCandidatesDirectory());
    candidates = engineDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    return candidates;
}

//  Note: Assumes that the url and other filename components have already been checked for illegal or
//  strange (anti security) characters.
QString PSiteWrapper::cacheFileName()
{
    return engine()->cacheDirectory() + "/" + name() + "/" + _siteCacheRelativeFileName;
}
