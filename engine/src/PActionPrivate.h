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

#ifndef PACTIONPRIVATE_H
#define PACTIONPRIVATE_H

#include "PAction.h"
#include <QString>
#include <QTimer>

class PActionPrivate
{
public:
    PActionPrivate(PAction *_q);

public: /* Members */
    PAction::StatusType m_finishedStatus;
    bool m_hasFinished;
    /** The single shot timer that emit the finished signal, making it asynchronous */
    QTimer m_finishedTimer;

public:
    PAction *q;
};

#endif // PACTIONPRIVATE_H
