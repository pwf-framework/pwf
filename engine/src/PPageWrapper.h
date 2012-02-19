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

#ifndef PPAGEWRAPPER_H
#define PPAGEWRAPPER_H

/**
  \class PPageWrapper
  \brief A website page wrapper.

  A page wrapper must refer to a site wrapper with a valid schema.
  The schema candidates directory is automatically setted to the site wrapper active schema directory.

  @see setPageName
*/

// TODO: controllare d->m_siteWrapper e vedere se si può sostituire direttamente con parentWrapper()

#include "pwfengine_global.h"
#include "PWrapper.h"

class PPageWrapperPrivate;
class PEngine;
class PSiteWrapper;
class PPageElement;
class PAction;

class PWFENGINESHARED_EXPORT PPageWrapper : public PWrapper
{
public:
    /** The siteWrapper must have a valid schema or the execution will be halted.
        The default schema candidate directory will be the directory of the siteWrapper current schema. */
    PPageWrapper(PEngine *engine, PSiteWrapper *siteWrapper);
    ~PPageWrapper();
    /** @return the filename as schemaCandidatesDirectory()/pageschema_schemaName.xml
                or an empty string if the schema is not valid. */
    QString schemaFileName(const QString &schemaName);
    bool map();
    /** Return the mapped root element  */
    PPageElement *mappedPage();
    /** Redownload the page. The method can be used when fresh data is needed,
        i.e when the page content might have been changed. */
    void refresh();
protected:
    /** Append to the list each page wrapper schema in the schemaCandidatesDirectory() */
    QList<QString> schemaCandidateNames();
    /** @return the filename as engine->cacheDirectory()/siteWrapper->name()/pagecache_name().xml */
    QString cacheFileName();
    //QString parseParametricVariable(const QString &variable);

private:
    friend class PPageWrapperPrivate;
    PPageWrapperPrivate *d;
};

#endif // PPAGEWRAPPER_H
