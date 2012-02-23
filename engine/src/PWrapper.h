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

#include "pwfengine_global.h"
#include <QObject>

class PWrapperPrivate;
class PEngine;
class PSchema;
class QString;
class PAction;
class PWrapperElement;
class TEvalWrapperData;

class PWFENGINESHARED_EXPORT PWrapper : public QObject
{   
Q_OBJECT

public:
    PWrapper(PEngine *engine, PWrapper *parent);
    virtual ~PWrapper();
    PEngine *engine() const;
    PWrapper *parentWrapper();

    bool setName(const QString &wrapperName);
    QString name() const;
    static bool isValidName(const QString &name);

    bool setUrl(const QString &url);
    QString url() const;

    void setSchemaCandidatesDirectory(const QString &directoryPath);
    QString schemaCandidatesDirectory();
    PAction *setSchema(const QString &schemaName);
    PAction *detectSchema();
    QString schemaName() const;
    /** Given a schema name, return the filename of the schema.
        If the schema name is not valid, return a null string.
    */
    virtual QString schemaFileName(const QString &schemaName) = 0;

    /** @return an evaluator for the data with the given name.
        \warning Requesting a data without a valid schema leads to undefined behavior.
    */
    TEvalWrapperData *evalData(const QString &name);

    /** @return the cache filename for this wrapper.
        @return an empty string if the wrapper url has not been specified (i.e it's empty) */
    virtual QString cacheFileName() = 0;

protected:
    /** @return a list containing the names of the schemas that must be checked by the detectSchema() method. */
    virtual QList<QString> schemaCandidateNames() = 0;
    PSchema *schema() const;

    PWrapperElement *rootElement() const;

    /*  @note the method is pure virtual because the parametric variables refer to wrapper-type dependent information.
        @return the variable correctly evaluated */
    //virtual QString parseParametricVariable(const QString &variable) = 0;

private slots:
    void finalizeSchema(PAction *action);
    void finalizeDetect();

protected: /* Members */
    friend class PWrapperPrivate;
    PWrapperPrivate *d;
};

#endif // PWRAPPER_H
