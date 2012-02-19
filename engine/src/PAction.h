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

  The action can be started with start() and asynchronously stopped with stop().
  Once the action has been started, it'll perform its job and will emits the finished signal when has finished, along
  with the success or failure signals if the action has successfully finished or if has failed, respectively.

  If the action is stopped, it will finish with the StatusNone status.
  If still active, the action will be automatically stopped at destruction time.

  \warning when subclassing PAction, remember to call the parent method as the first statement in the overrided start()
  and stop() to ensure right behaviour.
*/

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
    /** The action finished status. */
    PAction::StatusType finishedStatus() const;
    /** @return true if the action has finished or is about to finish (in case of an asynchronous finish) */
    bool hasFinished() const;
public slots:
    /** Starts the execution of the action and immediately emits the started signal. */
    virtual void start();
    /** Stops the execution of the action, asynchronously finishing with a StatusNone status. */
    virtual void stop();
protected slots:
    /** \note calling this method if the action has already finished has no effect.
        @param asyncSignals if true asynchronously emits the finished signals, allowing a receiver to connect
               even if the method is called before the object is returned to it. */
    void finish(const PAction::StatusType &status, const bool &asyncSignals=false);
private slots:
    /** Emits the finished and success/failure signals */
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
