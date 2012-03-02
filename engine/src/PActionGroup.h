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

#include "pwfengine_global.h"
#include "PAction.h"

class PActionGroupPrivate;

class PWFENGINESHARED_EXPORT PActionGroup : public PAction
{
    Q_OBJECT

public:
    PActionGroup(QObject *parent = 0);
    ~PActionGroup();

    void addAction(PAction *action);
    void setSingleStatusToStop(const PAction::StatusType &singleStatus, const PAction::StatusType &groupStatus);

    int remainingActions() const;

private slots:
    void updateOnActionFinished(PAction *action);

private:
    friend class PActionGroupPrivate;
    PActionGroupPrivate *d;
};

#endif // PACTIONGROUP_H
