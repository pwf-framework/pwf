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

#ifndef PACTION_H
#define PACTION_H

#include "pwfengine_global.h"
#include <QObject>

class PActionPrivate;

class PWFENGINESHARED_EXPORT PAction : public QObject
{
    Q_OBJECT

public: enum StatusType {
    /** The action has finished succesfully. */
    StatusSuccess,
    /** The action has failed. */
    StatusFailure,
    /** The initial value. The action finishes with this status if it has been stopped by the user or
        for some other reason. */
    StatusNone
};

public:
    PAction(QObject *parent = 0);
    virtual ~PAction();

    PAction::StatusType finishedStatus() const;
    bool hasFinished() const;

public slots:
    virtual void start();
    virtual void stop();
protected slots:
    void finish(const PAction::StatusType &status, const bool &asyncSignals=false);
private slots:
    void emitFinished();
    ///** Set the error from another action */
    //void setError(PAction *action);
    ///** Directly set the error */
    //void setError(QString &error);

signals:
    void started();

    void finished(PAction *action);
    /** The signal that could be connected to the finish slot of another action */
    void finished(PAction::StatusType finishedStatus);

    void success(PAction *action);
    /** The signal that could be connected to the finish slot of another action */
    void success(PAction::StatusType successStatus);

    void failure(PAction *action);
    /** The signal that could be connected to a finished slot of another action */
    void failure(PAction::StatusType failureStatus);

private:
    friend class PActionPrivate;
    PActionPrivate *d;
};

#endif // PACTION_H
