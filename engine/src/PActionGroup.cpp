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

#include "PActionGroup.h"
#include "PActionGroupPrivate.h"

PActionGroup::PActionGroup(QObject *parent) :
    PAction(parent)
{
    d = new PActionGroupPrivate(this);

    d->m_remainingActions = 0;
    d->m_singleStatusToStop = StatusNone;
    d->m_groupStatusWhenStop = StatusNone;
}

PActionGroup::~PActionGroup()
{
    delete d;
}

void PActionGroup::addAction(PAction *action)
{
    // start the action when the group starts
    connect(this, SIGNAL(started()), action, SLOT(start()));
    // if the group finish stop the PAction (if it's active)
    connect(this, SIGNAL(finished(PAction *)), action, SLOT(stop()));

    connect(action, SIGNAL(finished(PAction *)), this, SLOT(updateOnActionFinished(PAction *)));
    connect(action, SIGNAL(finished(PAction *)), action, SLOT(deleteLater()));

    action->setParent(this); // the PAction is automatically removed on destruction of this
    d->m_remainingActions++;
}

void PActionGroup::setSingleStatusToStop(const PAction::StatusType &singleStatus, const PAction::StatusType &groupStatus)
{
    d->m_singleStatusToStop = singleStatus;
    d->m_groupStatusWhenStop = groupStatus;
}

int PActionGroup::remainingActions() const
{
    return d->m_remainingActions;
}

void PActionGroup::updateOnActionFinished(PAction *action)
{
    d->m_remainingActions--;
    PAction::StatusType actionStatus = action->finishedStatus();

    // Check if the group has finished
    if (d->m_singleStatusToStop != StatusNone) { // there is the possibility to prematurely stop
        if (actionStatus == d->m_singleStatusToStop) {
            finish(d->m_groupStatusWhenStop);
        } else if (d->m_remainingActions == 0) {
            // all the PAction have finished with a status different from the one needed to stop
            // => finish with the opposite of the status needed to stop
            PAction::StatusType finishedStatus = (d->m_singleStatusToStop == StatusSuccess) ? StatusFailure :
                                                                                            StatusSuccess;
            finish(finishedStatus);
        }
    } else if (d->m_remainingActions == 0) {
        // there is not the possibility to prematurely stop but all the PAction have finished
        finish(StatusNone);
    }
}
