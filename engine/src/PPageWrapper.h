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

// TODO: controllare d->m_siteWrapper e vedere se si può sostituire direttamente con parentWrapper()
// TODO: gestione dell'url

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
    PPageWrapper(PEngine *engine, PSiteWrapper *siteWrapper);
    ~PPageWrapper();

    QString schemaFileName(const QString &schemaName);

    bool map();
    /** Return the mapped root element  */
    PPageElement *mappedPage();
    /** Redownload the page. The method can be used when fresh data is needed,
        i.e when the page content might have been changed. */
    void refresh();

protected:
    QList<QString> schemaCandidateNames();

    QString cacheFileName();

    //QString parseParametricVariable(const QString &variable);

private:
    friend class PPageWrapperPrivate;
    PPageWrapperPrivate *d;
};

#endif // PPAGEWRAPPER_H
