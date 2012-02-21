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

#ifndef PSITEWRAPPER_H
#define PSITEWRAPPER_H

/**
  \class PSiteWrapper
  \brief A website wrapper.
*/

#include "pwfengine_global.h"
#include "PWrapper.h"

class PSiteWrapperPrivate;
class PEngine;
class PPageWrapper;
class QString;
class PAction;

class PWFENGINESHARED_EXPORT PSiteWrapper : public PWrapper
{
public:
    /** @note The site wrapper is a top level wrapper, i.e. its parent is NULL. */
    PSiteWrapper(PEngine *engine);
    ~PSiteWrapper();
    /** @param url the site url, in a format like http://www.sitename.com/
        @return true if url is valid. */
    // TODO: check if url matches the site format
    bool setUrl(const QString &url);
    /** Append the pageWrapper to the list if not already exists. */
    void addPageWrapper(PPageWrapper *pageWrapper);
    /** @return the directory of the schema as schemaCandidatesDirectory()/schemaName/
        @return a null string if the schema name is not valid
        @note: the final / is removed */
    QString schemaDirectory(const QString &schemaName);
    /** @return the filename as schemaDirectory()/siteschema.xml
        @return a null string if the schema is not valid.*/
    QString schemaFileName(const QString &schemaName);
public slots:
    /** Remove the pageWrapper from the list if exists */
    void removePageWrapper(PPageWrapper *pageWrapper);
protected:
    /** Loop through each subdirectory in the schemaCandidatesDirectory() looking for a valid
        site wrapper schema, appending it to the returned list when found. */
    QList<QString> schemaCandidateNames();
    /** @return the filename as engine->cacheDirectory()/name()/sitecache.xml */
    QString cacheFileName();
    //QString parseParametricVariable(const QString &variable);

private:
    friend class PSiteWrapperPrivate;
    PSiteWrapperPrivate *d;
};

#endif // PSITEWRAPPER_H
