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
  \class PAttemptSchema
  \brief The action creates a new schema given its name and check its validity for the given wrapper.

  It's duty of the user to take and delete the schema if the action succeded, otherwise, if the action has failed or
  has been stopped, the schema will deleted at destruction time.
  \note if the action has been already used and is started again, then the old schema is intended as useless and will
  be destructed.
*/

#include "PAttemptSchema.h"
#include "PWrapper.h"
#include "PSchema.h"
#include <QList>
#include "PWrapperRequire.h"
#include "PEvalWrapperRequire.h"
#include "PActionGroup.h"

/** @note the wrapper becomes the parent of this object. */
PAttemptSchema::PAttemptSchema(const QString &schemaName, PWrapper *wrapper, PWrapperCache *wrapperCache)
    : PAction(wrapper)
{
    m_schemaName = schemaName;
    m_wrapper = wrapper;
    m_wrapperCache = wrapperCache;
    m_schema = NULL;
}

/** Delete the schema if the attempt has not succeded. */
PAttemptSchema::~PAttemptSchema()
{
    if (finishedStatus() != PAction::StatusSuccess) {
        delete m_schema;
    }
}

/** @warning the method deletes the old schema if exists. */
void PAttemptSchema::start()
{
    PAction::start();

    QString schemaFileName = m_wrapper->schemaFileName(m_schemaName);
    if (schemaFileName.isEmpty()) {
        // TODO: impostare errore magari prendendolo dallo schemaFileName del wrapper
        finish(PAction::StatusFailure, true);
        return;
    }

    // Create the new schema
    if (m_schema != NULL) {
        // The action has been reused (not intended usage, but one must deal with it)
        delete m_schema;
    }
    m_schema = new PSchema(m_schemaName);
    if (!m_schema->setDocument(schemaFileName)) {
        // TODO: impostare errore
        finish(PAction::StatusFailure, true);
        return;
    }

    // Check if the new schema match the wrapper
    QList<PSchemaElement> schemaRequires = m_schema->requires();
    if (schemaRequires.isEmpty()) {
        // no main requires => success
        finish(PAction::StatusSuccess, true);
        return;
    }
    PActionGroup *schemaRequiresParser = new PActionGroup(this);
    for (int i=0; i<schemaRequires.length(); i++) {
        // create a new parser for this require and add it to the group
        /*
        TParseRequire *parseRequire = new TParseRequire(schemaRequires.at(i), m_wrapper, m_wrapperCache, this);
        schemaRequiresParser->addAction(parseRequire);
        */
    }
    // the failure of even just one main require means that the schema is not valid for this wrapper
    schemaRequiresParser->setSingleStatusToStop(PAction::StatusFailure, PAction::StatusFailure);
    connect(schemaRequiresParser, SIGNAL(finished(PAction::StatusType)), this, SIGNAL(finished(PAction::StatusType)));
    connect(schemaRequiresParser, SIGNAL(finished(PAction*)), schemaRequiresParser, SLOT(deleteLater()));
}

PSchema *PAttemptSchema::schema() const
{
    return m_schema;
}

