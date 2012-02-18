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
  \brief A group of PAction that operate simultaneously. The class is a PAction itself.

  The class provides methods for managing group of PAction, allowing to specify when finish: on success or failure of
  an action or never, waiting that all the actions have finished.
  When the PActionGroup is stopped or finish, all its (active) PAction are stopped too.
  Each PAction object is automatically deleted when it finishes.

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
    /** Note: this object become parent of the action */
    void addAction(PAction *action);
    /** Set when to emit the finished signals and with which status
        @param singleStatus the type of the finished status of one PAction needed to stop. StatusNone means never stop prematurely
        @param groupStatus the finished status when the prematurely stop occurs
    */
    void setSingleStatusToStop(const PAction::StatusType &singleStatus, const PAction::StatusType &groupStatus);
    /** @return the number of added PAction that have not finished yet */
    int remainingActions() const;
private slots:
    /** Decrease the number of remaining PAction and check if the group has finished:
        if all the PAction have finished => finish with the opposite of the status needed to stop  (StatusSuccess => StatusFailure,
        StatusFailure => StatusSuccess, StatusNone => StatusNone) */
    void updateOnActionFinished(PAction *action);

private:
    friend class PActionGroupPrivate;
    PActionGroupPrivate *d;
};

#endif // PACTIONGROUP_H
