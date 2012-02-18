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

/**
  \class PAction
  \brief Implements the command-pattern design technique for asynchronous operations. NOTE: The action is disposable.

  The action can be started with the start() method, stopped with stop() that will asynchronously finish
  with the StatusNone status.
  Anyway, the finished signals are emitted when the action finishes.

  If still active, the action will be automatically stopped at destruction time.

  \warning If you subclass PAction, remember to call the parent method as the first statement in the overrided start()
  and stop() methods to assure right behaviour.
*/

#include "pwfengine_global.h"
#include <QObject>

class PActionPrivate;

class PWFENGINESHARED_EXPORT PAction : public QObject
{
    Q_OBJECT

public: enum StatusType {
    /** Means that the action has finished succesfully. */
    StatusSuccess,
    /** Means that the action has failed. */
    StatusFailure,
    /** The initial value. The action finishes with this status if it has been stopped by the user or
        for some other reasons. */
    StatusNone
};

public:
    PAction(QObject *parent = 0);
    virtual ~PAction();
    PAction::StatusType finishedStatus() const;
    /** @return true if the PAction has finished or is about to finish (the timer is running) */
    bool hasFinished() const;
public slots:
    /** Start the execution of the action and immediately emit the started signal. */
    virtual void start();
    /** Stop the execution of the action, asynchronously finishing with a StatusNone status. */
    virtual void stop();
protected slots:
    /** \note calling this method if the action has already finished has no effect.
        @param asyncSignal if true asynchronously emit the finished signals, allowing listeners to connect even if them
               are emitted before the object is returned to the handler */
    void finish(const PAction::StatusType &status, const bool &asyncSignal=false);
private slots:
    /** Emit the finished and success/failure signals */
    void emitFinished();
    /** Set the error from another action */
    //void setError(PAction *action);
    /** Directly set the error */
    //void setError(QString &error);

signals:
    void started();
    void finished(PAction *action);
    /** The signal be connected to a finish slot of another action */
    void finished(PAction::StatusType finishedStatus);
    void success(PAction *action);
    /** The signal be connected to a finish slot of another action */
    void success(PAction::StatusType successStatus);
    void failure(PAction *action);
    /** The signal be connected to a finished slot of another action */
    void failure(PAction::StatusType failureStatus);

private:
    friend class PActionPrivate;
    PActionPrivate *d;
};

#endif // PACTION_H
