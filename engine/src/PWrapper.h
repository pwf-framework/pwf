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

#ifndef PWRAPPER_H
#define PWRAPPER_H

/**
  \class PWrapper
  \brief An abstract wrapper. It is associated to an url and has a schema that can be automatically detected.

  Each wrapper is univocally identified by its name that must be setted as soon as having created the wrapper.
  Two wrappers referring to different urls but having the same name will be treated as the same and so will share the
  same cache.
  @see setName

  @see setUrl
  @see setSchema
  @see detectSchema
*/

#include "pwfengine_global.h"
#include <QObject>
#include "PAction.h"
#include "PActionGroup.h"

class PWrapperPrivate;
class PEngine;
class PSchema;
class QString;
class PSchemaElement;
class PWrapperElement;
class TEvalWrapperData;

/** The pattern for all the names (schema, cache, etc.) */
const QString _namePattern = "[a-zA-Z0-9_\\-!@#$%^()]+";

class PWFENGINESHARED_EXPORT PWrapper : public QObject
{   
Q_OBJECT

public:
    /** \warning Passing a null value for the engine parameter leads to undefined behavior */
    PWrapper(PEngine *engine, PWrapper *parent);
    virtual ~PWrapper();
    PEngine *engine() const;
    /** @return the parent wrapper, or NULL if this is a top level wrapper. */
    PWrapper *parentWrapper();
    /** The name can contains only alphanumeric characters and the special characters _-!@#$%^()
        @return false if the name is an illegal string. */
    bool setName(const QString &wrapperName);
    QString name() const;
    /** Set the wrapper target url
        @param url the url in an encoded format,
        \warning The current schema might become invalid, immediately call detectSchema() or setSchema() if you are not sure or
                 if you are setting the wrapper url for the first time.
        @return true if the url is valid. */
    bool setUrl(const QString &url);
    /** Return the wrapper target url */
    QString url() const;
    /** Set the directory where are located all the wrapper schemas. Overwrite the directory setted in the PEngine.
        @note the path is cleaned by using QDir::cleanPath()
        @warning always use the "/" separator, example: "c:/foo/bar" OK, "c:\foo\bar" NO.  */
    // TODO: sanitize input!!!!
    void setSchemaCandidatesDirectory(const QString &directoryPath);
    /** @return if not null, the directory setted by the setSchemaCandidatesDirectory() or, otherwise,
        the engine schemas directory */
    // TODO: save engine directory as default member and overwite if needed, instead of checking for null
    QString schemaCandidatesDirectory();
    /** Set the wrapper schema specifying its name (e.g. phpbb3). The library will in turn locate the file.
        This is the only method the user can use to 'directly' set the wrapper schema, this allow to set only schemas
        that are in the wrapper schemas folder.

        @return a PAction whose actionTarget is the new created PSchema.
    */
    PAction *setSchema(const QString &schemaName);
    /** Automatically detect a valid schema for this wrapper by checking all the schema names returned by the schemaCandidateNames()
        method.
        @note Calling this method if there is already another detect running has no effect. */
    PAction *detectSchema();
    PSchema *schema() const;
    /** @return the active schema name or an empty string if it has not yet been set */
    QString schemaName() const;
    /** Given a schema name, return the filename of the schema.
        If the schema name is not valid, return an empty string. */
    virtual QString schemaFileName(const QString &schemaName) = 0;
    /** @return an evaluator for the data with the given name.
        \warning Requesting a data without a valid schema leads to undefined behavior. */
    TEvalWrapperData *evalData(const QString &name);
protected:
    /** @return the root wrapper element, i.e. the element with the whole wrapper schema as its schema. */
    PWrapperElement *rootElement() const;
    /** Return a list containing the names of the schemas that must be checked by the detectSchema() method. */
    virtual QList<QString> schemaCandidateNames() = 0;
    /** @return the cache filename for this wrapper.
        @return an empty string if the wrapper url has not been specified (i.e it's empty) */
    virtual QString cacheFileName() = 0;
    /** Note: the method is pure virtual because the parametric variables refer to wrapper-type dependent information.
        @return the variable correctly evaluated */
    //virtual QString parseParametricVariable(const QString &variable) = 0;
private slots:
    /** Called when a new schema has been checked. If the schema match the wrapper (status==StatusSuccess) then
        it's choosen as the "official" wrapper schema, otherwise it's deleted to avoid memory leaks. */
    void finalizeSchema(PAction *action);
    /** Called when the detection process has finished running. Allow to start a new detection process when needed. */
    void finalizeDetect();

protected:
    friend class PWrapperPrivate;
    PWrapperPrivate *d;
};

#endif // PWRAPPER_H
