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

#include "PWrapper.h"
#include "PWrapperPrivate.h"
#include "PEngine.h"
#include "PSchema.h"
#include "PWrapperElement.h"
#include <QString>
#include "PAction.h"
#include "PActionGroup.h"
#include "PAttemptSchema.h"
#include "PEnginePrivate.h" // for the static function removeFinalSlash
#include <QRegExp>
#include <QDir>

// _namePattern defined in PWrapper.h

PWrapper::PWrapper(PEngine *engine, PWrapper *parent)
    : QObject(parent)
{
    if (engine == 0) {
        // fatal error
        qFatal("Please specify a valid PEngine for the wrapper");
        return;
    }

    d = new PWrapperPrivate(this);

    d->m_eng = engine;
    d->m_parent = parent;
    d->m_schema = 0;
    d->m_rootElement = 0;
    d->m_detectSchemaIsRunning = false;
}

PWrapper::~PWrapper()
{
    delete d;
}

PEngine *PWrapper::engine() const
{
    return d->m_eng;
}

PWrapper * PWrapper::parentWrapper()
{
    return d->m_parent;
}

PWrapperElement * PWrapper::rootElement() const
{
    return d->m_rootElement;
}

bool PWrapper::setName(const QString &wrapperName)
{
    // Prevent illegal names
    QRegExp dirPattern(_namePattern);
    if (!dirPattern.exactMatch(wrapperName)) {
        return false;
    }

    d->m_name = wrapperName;
    return true;
}

QString PWrapper::name() const
{
    return d->m_name;
}

void PWrapper::setUrl(const QString &url)
{
    d->m_url = PWrapperPrivate::fixUrl(url);
}


QString PWrapper::url() const
{
    return d->m_url;
}


void PWrapper::setSchemaCandidatesDirectory(const QString &directoryPath)
{
    // Note: remove the last / if exists
    d->m_schemaCandidatesDirectory = QDir::cleanPath(directoryPath);
}

QString PWrapper::schemaCandidatesDirectory()
{
    return (d->m_schemaCandidatesDirectory.isNull()) ? d->m_eng->schemaCandidatesDirectory()
                                                   : d->m_schemaCandidatesDirectory;
}

PAction *PWrapper::setSchema(const QString &schemaName)
{  
    PAttemptSchema *attemptSchema = new PAttemptSchema(schemaName, this, d->m_cache);
    // in case of failure the schema will be deleted automatically by the action
    connect(attemptSchema, SIGNAL(success(PAction*)), this, SLOT(finalizeSchema(PAction*)));
    attemptSchema->start();
    return attemptSchema;
}

/** @param action is of type PAction to hide the real (and private) subclass from the public interface. */
void PWrapper::finalizeSchema(PAction *action)
{
    // set the schema
    if (d->m_schema != 0) {
        delete d->m_schema;
    }
    PAttemptSchema *attemptSchema = static_cast<PAttemptSchema *>(action);
    d->m_schema = attemptSchema->schema();

    // set the root element accordingly
    if (d->m_rootElement != 0) {
        d->m_rootElement->deleteLater();
    }
    // the parent of the root element is the parent wrapper root element, or NULL if this is the top level wrapper.
    PWrapperElement *parentElement = (parentWrapper() != 0) ? parentWrapper()->rootElement() : 0;
    d->m_rootElement = new PWrapperElement(this, parentElement, *(d->m_schema));
}

PAction *PWrapper::detectSchema()
{
    PActionGroup *actionGroup = new PActionGroup(this);

    if (d->m_detectSchemaIsRunning) {
        /* avoid multiple executions */
        qDebug("Detection process already in execution");
        //actionGroup->finish(PAction::StatusFailure, true);
        return actionGroup;
    }

    // get all the schema names
    QList<QString> candidates = schemaCandidateNames();
    if (candidates.isEmpty()) {
        // no schemas
        qDebug("no schemas found");
        //actionGroup->finish(PAction::StatusFailure, true);
        return actionGroup;
    }

    // add all the PAction to the group
    actionGroup->setSingleStatusToStop(PAction::StatusSuccess, PAction::StatusSuccess);
    for (int i=0; i<candidates.length(); i++) {
        actionGroup->addAction(setSchema(candidates.at(i)));
    }

    d->m_detectSchemaIsRunning = true;
    connect(actionGroup, SIGNAL(finished(PAction *)), this, SLOT(finalizeDetect()));
    return actionGroup;
}

void PWrapper::finalizeDetect()
{
    d->m_detectSchemaIsRunning = false;
}

PSchema *PWrapper::schema() const
{
    return d->m_schema;
}

QString PWrapper::schemaName() const
{
    if (d->m_schema == NULL) {
        return "";
    }

    return d->m_schema->name();
}
