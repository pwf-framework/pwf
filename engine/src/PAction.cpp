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

#include "PAction.h"
#include "PActionPrivate.h"
#include <QTimer>

PAction::PAction(QObject *parent) :
    QObject(parent)
{
    d = new PActionPrivate(this);

    d->m_finishedStatus = StatusNone;
    d->m_hasFinished = false;

    d->m_finishedTimer.setSingleShot(true);
    d->m_finishedTimer.setInterval(0);
    connect(&d->m_finishedTimer, SIGNAL(timeout()), this, SLOT(emitFinished()));
}

PAction::~PAction()
{
    stop();

    delete d;
}

/** Starts the execution of the action and immediately emits the started signal. */
void PAction::start()
{
    emit started();
}

/** Stops the execution of the action, asynchronously finishing with a StatusNone status. */
void PAction::stop()
{
    finish(StatusNone, true);
}

/** The action finished status. */
PAction::StatusType PAction::finishedStatus() const
{
    return d->m_finishedStatus;
}

/** \note calling this method if the action has already finished has no effect.
    @param asyncSignals if true asynchronously emits the finished signals, allowing a receiver to connect
           even if the method is called before the object is returned to it. */
void PAction::finish(const PAction::StatusType &status, const bool &asyncSignals)
{
    if (d->m_hasFinished) {
        // avoid to overwrite the finished status and to double emit the finished signal
        return;
    }

    d->m_finishedStatus = status;
    d->m_hasFinished = true;

    if (asyncSignals) {
        d->m_finishedTimer.start();
    } else {
        emitFinished();
    }
}

/** Emits the finished and success/failure signals */
void PAction::emitFinished()
{
    emit finished(this);
    emit finished(finishedStatus());

    if (d->m_finishedStatus == PAction::StatusSuccess) {
        emit success(this);
        emit success(PAction::StatusSuccess);
    } else if (d->m_finishedStatus == PAction::StatusFailure) {
        emit failure(this);
        emit failure(PAction::StatusFailure);
    }
}

/** @return true if the action has finished or is about to finish (in case of an asynchronous finish) */
bool PAction::hasFinished() const
{
    return d->m_hasFinished;
}
