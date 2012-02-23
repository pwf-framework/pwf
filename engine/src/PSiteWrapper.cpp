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
  \class PSiteWrapper
  \brief A website wrapper.
*/

#include "PSiteWrapper.h"
#include "PSiteWrapperPrivate.h"
#include "PEngine.h"
#include "PPageWrapper.h"
#include <QString>
#include <QDir>
#include "PAction.h"
#include "PActionGroup.h"
#include "PEnginePrivate.h" // for the static function removeFinalSlash

const QString _siteSchemaRelativeFileName = "siteschema.xml";
const QString _siteCacheRelativeFileName = "sitecache.xml";
// _namePattern defined in PWrapper.h

/** @note The site wrapper is a top level wrapper, i.e. its parent is NULL. */
PSiteWrapper::PSiteWrapper(PEngine *engine) : PWrapper(engine, NULL)
{
    d = new PSiteWrapperPrivate(this);
}

PSiteWrapper::~PSiteWrapper()
{
    delete d;
}

/** @param url the site url, in a format like http://www.sitename.com/
    @return true if url is valid.
 */
// TODO: check if url matches the site format
bool PSiteWrapper::setUrl(const QString &url)
{
    // TODO: check if url matches the site format
    if (true /* STUB */) {
        return PWrapper::setUrl(PSiteWrapperPrivate::fixUrl(url));
    }

    return false;
}

/** Append the pageWrapper to the list if not already exists. */
void PSiteWrapper::addPageWrapper(PPageWrapper *pageWrapper)
{
    if (pageWrapper == NULL) { return; }

    // check if the page wrapper already exists
    for (int i=0; i<d->m_pageWrappers.length(); i++) {
        if (d->m_pageWrappers.at(i) == pageWrapper) { return; }
    }

    d->m_pageWrappers.append(pageWrapper);
}

/** Remove the pageWrapper from the list if exists */
void PSiteWrapper::removePageWrapper(PPageWrapper *pageWrapper)
{
    if (pageWrapper == NULL) { return; }

    for (int i=0; i<d->m_pageWrappers.length(); i++) {
        if (d->m_pageWrappers.at(i) == pageWrapper) {
            d->m_pageWrappers.removeAt(i);
        }
    }
}

/** @return the filename as schemaDirectory()/siteschema.xml
    @return a null string if the schema is not valid.*/
QString PSiteWrapper::schemaFileName(const QString &schemaName)
{
    QString schemaDir = schemaDirectory(schemaName);
    if (schemaDir.isEmpty()) {
        // invalid schema name or directory
        return QString();
    }

    return schemaDir + "/" + _siteSchemaRelativeFileName;
}

/** @return the directory of the schema as schemaCandidatesDirectory()/schemaName/
    @return a null string if the schema name is not valid
    @note: the final / is removed
*/
QString PSiteWrapper::schemaDirectory(const QString &schemaName)
{
    // Disallow illegal characters for the schema name
    if (!PWrapper::isValidName(schemaName)) {
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

/** Loop through each subdirectory in the schemaCandidatesDirectory() looking for a valid
    site wrapper schema, appending it to the returned list when found. */
QList<QString> PSiteWrapper::schemaCandidateNames()
{
    QList<QString> candidates;

    // get all the site schemas directories
    QDir engineDir(schemaCandidatesDirectory());
    candidates = engineDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    return candidates;
}

/** @return the filename as engine->cacheDirectory()/name()/sitecache.xml */
//  Note: Assumes that the url and other filename components have already been checked for illegal or
//  strange (anti security) characters.
QString PSiteWrapper::cacheFileName()
{
    return engine()->cacheDirectory() + "/" + name() + "/" + _siteCacheRelativeFileName;
}
