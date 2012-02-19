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

void PAction::start()
{
    emit started();
}

void PAction::stop()
{
    finish(StatusNone, true);
}

PAction::StatusType PAction::finishedStatus() const
{
    return d->m_finishedStatus;
}

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

bool PAction::hasFinished() const
{
    return d->m_hasFinished;
}
