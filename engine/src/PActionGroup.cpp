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
  \class PActionGroup
  \brief A group of actions that operate simultaneously. Note: the class is an action itself.

  The class provides methods for managing a group of actions, allowing to specify when finish: on success or failure of
  an action or never, waiting that all the actions have finished. @see setSingleStatusToStop()

  When the action group is stopped or finish, all its (active) actions are stopped too.
  Each action is automatically deleted when it finishes.

  The actions can be added with the addAction() method. The start() method will in turn execute all the added actions.
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

/** @note the group become parent of the action */
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

/** Sets when to emit the finished signals and with which status
    @param singleStatus the finished status, that, if emitted by just one action,
           will leads to the prematurely group finish.
    @param groupStatus the finished status of the group to use if the premature finish occurs
*/
void PActionGroup::setSingleStatusToStop(const PAction::StatusType &singleStatus, const PAction::StatusType &groupStatus)
{
    d->m_singleStatusToStop = singleStatus;
    d->m_groupStatusWhenStop = groupStatus;
}

/** @return the number of added actions that have not finished yet */
int PActionGroup::remainingActions() const
{
    return d->m_remainingActions;
}

/** Decreases the number of the remaining actions and check if the conditions
    to prematurely stop took place, if not:
    if all the actions have finished => finish with the opposite of the status needed to stop
    (StatusSuccess => StatusFailure, StatusFailure => StatusSuccess, StatusNone => StatusNone) */
void PActionGroup::updateOnActionFinished(PAction *action)
{
    d->m_remainingActions--;
    PAction::StatusType actionStatus = action->finishedStatus();

    // Check if the group has finished
    if (d->m_singleStatusToStop != StatusNone) { // there is the possibility to prematurely stop
        if (actionStatus == d->m_singleStatusToStop) {
            // prematurely stop
            finish(d->m_groupStatusWhenStop);
        } else if (d->m_remainingActions == 0) {
            // all the actions have finished with a status different from the one needed to stop
            // => finish with the opposite of the status needed to stop
            PAction::StatusType finishedStatus = (d->m_singleStatusToStop == StatusSuccess) ? StatusFailure :
                                                                                            StatusSuccess;
            finish(finishedStatus);
        }
    } else if (d->m_remainingActions == 0) {
        // there is not the possibility to prematurely stop but all the actions have finished
        finish(StatusNone);
    }
}
