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
  \class PPageWrapper
  \brief A website page wrapper.

  A page wrapper must refer to a site wrapper with a valid schema.
  The schema candidates directory is automatically setted to the site wrapper active schema directory.

  @see setPageName
*/

#include "PPageWrapper.h"
#include "PPageWrapperPrivate.h"
#include "PEngine.h"
#include "PSiteWrapper.h"
#include "PPageElement.h"
#include "PAction.h"
#include <QDir>

const QString _pageSchemaPrefix = "pageschema_";
const QString _pageCachePrefix = "pagecache_";
// _namePattern defined in PWrapper.h

/** The siteWrapper must have a valid schema or the execution will be halted.
    The default schema candidates directory will be the directory of the siteWrapper current schema.
*/
// TODO: and what to do if the site schema candidates directory changes? maybe use an approach like that of TWrapper
// TODO: to allow page wrappers without a site wrapper?
PPageWrapper::PPageWrapper(PEngine *engine, PSiteWrapper *siteWrapper) : PWrapper(engine, siteWrapper)
{
    d = new PPageWrapperPrivate(this);

    if (siteWrapper == NULL) {
        qFatal("PPageWrapper: the site wrapper can't be NULL.");
    }
    d->m_siteWrapper = siteWrapper;

    // set default schema directory
    QString siteWrapperSchemaDirectory = siteWrapper->schemaDirectory(siteWrapper->schemaName());
    if (siteWrapperSchemaDirectory.isEmpty()) {
        qFatal("PPageWrapper(): the site wrapper does not have a correct schema name or directory");
        return;
    }
    setSchemaCandidatesDirectory(siteWrapperSchemaDirectory);

    d->m_cTags = NULL;

    // add the page wrapper to the site wrapper
    d->m_siteWrapper->addPageWrapper(this);
}

PPageWrapper::~PPageWrapper()
{
    d->m_siteWrapper->removePageWrapper(this);

    delete d;
}

/** @return the filename as schemaCandidatesDirectory()/pageschema_schemaName.xml
    @return a null string if the schema is not valid.
*/
QString PPageWrapper::schemaFileName(const QString &schemaName)
{
    // Disallow illegal characters for the schema name
    if (!PWrapper::isValidName(schemaName)) {
        return QString();
    }

    return schemaCandidatesDirectory() + "/" + _pageSchemaPrefix + schemaName + ".xml";
}

/** Append to the list each page wrapper schema in the schemaCandidatesDirectory() */
QList<QString> PPageWrapper::schemaCandidateNames()
{
    QList<QString> candidates;

    // get all the page schema names in the schema directory
    QDir engineDir(schemaCandidatesDirectory());
    candidates = engineDir.entryList(QStringList(_pageSchemaPrefix + "*.xml"), QDir::Files);
    return candidates;
}

/** @return the filename as engine->cacheDirectory()/siteWrapper->name()/pagecache_name().xml */
QString PPageWrapper::cacheFileName()
{
    return PWrapper::engine()->cacheDirectory() + "/" + d->m_siteWrapper->name() + "/"
            + _pageCachePrefix + name() + ".xml";
}
