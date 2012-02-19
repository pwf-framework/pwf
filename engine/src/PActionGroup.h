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

#ifndef PACTIONGROUP_H
#define PACTIONGROUP_H

/**
  \class PActionGroup
  \brief A group of actions that operate simultaneously. Note: the class is an action itself.

  The class provides methods for managing a group of actions, allowing to specify when finish: on success or failure of
  an action or never, waiting that all the actions have finished. @see setSingleStatusToStop()

  When the action group is stopped or finish, all its (active) actions are stopped too.
  Each action is automatically deleted when it finishes.

  The actions can be added with the addAction() method. The start() method will in turn execute all the added actions.
*/

#include "pwfengine_global.h"
#include "PAction.h"

class PActionGroupPrivate;

class PWFENGINESHARED_EXPORT PActionGroup : public PAction
{
    Q_OBJECT

public:
    PActionGroup(QObject *parent = 0);
    ~PActionGroup();
    /** @note the group become parent of the action */
    void addAction(PAction *action);
    /** Sets when to emit the finished signals and with which status
        @param singleStatus the finished status, that, if emitted by just one action,
               will leads to the prematurely group finish.
        @param groupStatus the finished status of the group to use if the premature finish occurs
    */
    void setSingleStatusToStop(const PAction::StatusType &singleStatus, const PAction::StatusType &groupStatus);
    /** @return the number of added actions that have not finished yet */
    int remainingActions() const;
private slots:
    /** Decreases the number of the remaining actions and check if the conditions
        to prematurely stop took place, if not:
        if all the actions have finished => finish with the opposite of the status needed to stop
        (StatusSuccess => StatusFailure, StatusFailure => StatusSuccess, StatusNone => StatusNone) */
    void updateOnActionFinished(PAction *action);

private:
    friend class PActionGroupPrivate;
    PActionGroupPrivate *d;
};

#endif // PACTIONGROUP_H
