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
  \class PWrapper
  \brief An abstract wrapper. It is associated to an url and has a schema that can be automatically detected.

  Each wrapper is univocally identified by its name that must be setted with setName() as soon as
  having created the wrapper.
  Two wrappers referring to different urls but having the same name will be treated as the same and so will share the
  same cache.

  The wrapper url can be setted with setUrl().

  The schema can be setted directly with setSchema() or detected with
  detectSchema().
  The current schema name can be obtained by calling schemaName(), its filename with schemaFileName().
*/

// TODO: gestione cache (creazione, etc)

#include "PWrapper.h"
#include "PWrapperPrivate.h"
#include "PEngine.h"
#include "PSchema.h"
#include "PWrapperElement.h"
#include <QString>
#include "PAction.h"
#include "PActionGroup.h"
#include "PAttemptSchema.h"
#include <QRegExp>
#include <QDir>
#include <QUrl>

/** The pattern for all the names (schema, cache, etc.) used in isValidName() */
const QString _namePattern = "[a-zA-Z0-9_\\-!@#$%^()]+";

/** @warning engine can't be NULL or the execution will be halted. */
PWrapper::PWrapper(PEngine *engine, PWrapper *parent)
    : QObject(parent)
{
    if (engine == NULL) {
        // fatal error
        qFatal("PWrapper(): engine is NULL, please specify a valid engine for the wrapper");
        return;
    }

    d = new PWrapperPrivate(this);

    d->m_eng = engine;
    d->m_parent = parent;
    d->m_schemaCandidatesDirectory = QString(); // null string (isNull() returns true)
    d->m_schema = NULL;
    d->m_rootElement = NULL;
    d->m_cache = NULL;
    d->m_detectSchemaIsRunning = false;
}

PWrapper::~PWrapper()
{
    delete d->m_schema;

    delete d;
}

PEngine *PWrapper::engine() const
{
    return d->m_eng;
}

/** @return the parent wrapper, or NULL if this is a top level wrapper. */
PWrapper * PWrapper::parentWrapper()
{
    return d->m_parent;
}

/** @return the root wrapper element, i.e. the element with the whole wrapper schema as its schema. */
PWrapperElement * PWrapper::rootElement() const
{
    return d->m_rootElement;
}

/** @param wrapperName the wrapper name that must be valid, see isValidName()
    @return false if the name is an illegal string.
*/
bool PWrapper::setName(const QString &wrapperName)
{
    // Prevent illegal names
    if (!isValidName(wrapperName)) {
        return false;
    }

    d->m_name = wrapperName;
    return true;
}

QString PWrapper::name() const
{
    return d->m_name;
}

/** @return true if the name contains only alphanumeric characters and the special characters _-!@#$%^() */
bool PWrapper::isValidName(const QString &name)
{
    QRegExp dirPattern(_namePattern);
    return dirPattern.exactMatch(name);
}

/** Set the wrapper target url
    @param url the url in an encoded format,
    \warning The current schema might become invalid, immediately call detectSchema() or setSchema() if you are not sure or
             if you are setting the wrapper url for the first time.
    @return true if the url is valid.
*/
bool PWrapper::setUrl(const QString &url)
{
    if (QUrl(d->m_url).isValid()) {
        d->m_url = url;
        return true;
    }

    return false;
}

/** @return the wrapper target url */
QString PWrapper::url() const
{
    return d->m_url;
}

/** Set the directory where are located all the wrapper schemas. Overwrite the directory setted in the PEngine.
    @note the path is cleaned by using QDir::cleanPath()
    @warning always use the "/" separator, example: "c:/foo/bar" OK, "c:\foo\bar" NO.
*/
// TODO: sanitize input!!!!
void PWrapper::setSchemaCandidatesDirectory(const QString &directoryPath)
{
    // Note: remove the last / if exists
    d->m_schemaCandidatesDirectory = QDir::cleanPath(directoryPath);
}


/** @return if not null, the directory setted by the setSchemaCandidatesDirectory() or, otherwise,
    the current engine schemas directory
*/
// The engine schema candidates directory is not saved as a member on construction because in this way we can
// obtain the updated directory if the user change it in the engine.
QString PWrapper::schemaCandidatesDirectory()
{
    return (d->m_schemaCandidatesDirectory.isNull()) ? d->m_eng->schemaCandidatesDirectory()
                                                   : d->m_schemaCandidatesDirectory;
}

/** Set the wrapper schema specifying its name (e.g. phpbb3). The library will in turn locate the file.
    This is the only method the user can use to 'directly' set the wrapper schema, this allow to set only schemas
    that are in the wrapper schemas folder.

    @return an already started action that will checks if the schema matches the wrapper.
*/
PAction *PWrapper::setSchema(const QString &schemaName)
{  
    PAttemptSchema *attemptSchema = new PAttemptSchema(schemaName, this, d->m_cache);
    // note: in case of failure the schema will be deleted automatically by the action

    connect(attemptSchema, SIGNAL(success(PAction*)), this, SLOT(finalizeSchema(PAction*)));
    attemptSchema->start();
    return attemptSchema;
}


/** Called when a new schema has been checked. If the schema match the wrapper (status == success) then
    it's choosen as the "official" wrapper schema and the root element is created.
*/
// the parameter is of type PAction to hide the real (and private) subclass from the public interface.
void PWrapper::finalizeSchema(PAction *action)
{    
    if (d->m_schema != NULL) {
        // delete the old schema
        delete d->m_schema;
    }
    // retrieve and set the schema
    PAttemptSchema *attemptSchema = static_cast<PAttemptSchema *>(action);
    d->m_schema = attemptSchema->schema();

    // set the root element accordingly
    if (d->m_rootElement != NULL) {
        d->m_rootElement->deleteLater();
    }
    // the parent of the root element is the root element of the parent wrapper,
    // or NULL if this is the top level wrapper.
    PWrapperElement *parentElement = (parentWrapper() != NULL) ? parentWrapper()->rootElement() : NULL;
    d->m_rootElement = new PWrapperElement(this, parentElement, *(d->m_schema));
}


/** Automatically detects a valid schema for this wrapper by checking all the schema names returned by the
    schemaCandidateNames() method.
    @note calling this method if there is already another detection running has no effect.
*/
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

    // add each action returned by setSchema(candidate) to the group
    actionGroup->setSingleStatusToStop(PAction::StatusSuccess, PAction::StatusSuccess);
    for (int i=0; i<candidates.length(); i++) {
        QString candidate = candidates.at(i);
        actionGroup->addAction(setSchema(candidate));
    }

    d->m_detectSchemaIsRunning = true;
    connect(actionGroup, SIGNAL(finished(PAction *)), this, SLOT(finalizeDetect()));
    return actionGroup;
}

/** Called when the detection process has finished running. Allow to start a new detection process when needed. */
void PWrapper::finalizeDetect()
{
    d->m_detectSchemaIsRunning = false;
}

PSchema *PWrapper::schema() const
{
    return d->m_schema;
}

/** @return the active schema name or an empty string if it has not yet been set */
QString PWrapper::schemaName() const
{
    if (d->m_schema == NULL) {
        return "";
    }

    return d->m_schema->name();
}
