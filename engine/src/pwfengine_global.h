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

#ifndef PWFENGINE_GLOBAL_H
#define PWFENGINE_GLOBAL_H

// TODO:
// - risolvere le varie problematiche di directory da validare
// - inserire una gestione dei filename più elegante e sicura

/**
  @mainpage PWF Engine

PWF Engine is the engine of the PWF framework, used to create and use web wrappers based on generic schemas.

Let's suppose you want to navigate a page of a website to extract some information from it.
@note a general understanding of QT it is needed to use the engine.

We will create a class MyNavigator with some members:
@code
PEngine *engine;
PSiteWrapper *siteWrapper;
PPageWrapper *pageWrapper;
@endcode
and some slots:
@code
public slots:
void attemptSiteSchemaFinished(PAction::StatusType finishedStatus));
void attemptPageSchemaFinished(PAction::StatusType finishedStatus));
@endcode
We will see how to use them later.

The first thing you have to is to create the engine class specifying the schemas root directory:
@code
engine = new PEngine();
engine->setSchemasCandidatesDirectory("schemas/");
@endcode

Now you can create the site wrapper passing the engine to it:
@code
myWrapper = new PSiteWrapper(engine);
myWrapper->setUrl("http://www.sitename.com/");
@endcode

Now the critical part: setting a schema. You have two choices:

- Automatically detect the schema, use this if you don't know
what is the specific schema but you have a list of possible candidates.
@code
PAction *attemptSiteSchema = myWrapper->detectSchema();
@endcode
In this case you have only an idea of the site content, e.g. a forum, but you have schemas for the various
kinds, e.g. one for phpbb, one for smf, etc., so you let the system detects the right schema for you.

- Set the schema manually:
@code
PAction *attemptSiteSchema = myWrapper->setSchema("smf");
@endcode
In this case you already know that the site is an smf forum and so matches the schema written for it.

Obviously, these are only some examples of schema usages, (ideally) you could model a generic schema
that apply to all forums!

The PAction is a simple class that executes an action, in this case sets/detects the schema of a wrapper,
and emits a QT Signal when it has finished.
Check http://developer.qt.nokia.com/doc/signalsandslots.html for more information about the signal and slot mechanism.

Now we'll say to the system to call our attemptSiteSchemaFinished() slot when the schemaAction has
finished it's job, passing to it the status of the action.
@code
connect(attemptSchema, SIGNAL(finished(PAction::StatusType)),
        this, SLOT(attemptSiteSchemaFinished(PAction::StatusType)));
@endcode

If the action has finished without errors, we can create the wrapper for the page we want to navigate and repeat the
operation to set/detect its schema.
@code
void attemptSiteSchemaFinished(PAction::StatusType finishedStatus)) {
  if (finishedStatus == PAction:StatusSuccess) {
    // our schema is ready!
    pageWrapper = new PPAgeWrapper(engine, siteWrapper);
    PAction *attemptPageSchema = pageWrapper->setSchema("lastposts");
    connect(attemptPageSchema, SIGNAL(finished(PAction::StatusType)),
            this, SLOT(attemptPageSchemaFinished(PAction::StatusType)));
  } else {
    // error
  }
}
@endcode

When the page schema is ready, we can navigate it to extract the information we want:
@code
void attemptPageSchemaFinished(PAction::StatusType finishedStatus)) {
  if (finishedStatus == PAction:StatusSuccess) {
    // our schema is ready!
    PPageElement *lastsPosts = pageWrapper->mappedPage();
    PPageElement post;
    while ((post = lastsPosts->next("post"))) {
        cout << "Title: " << post.child("title").at(0).text() << endl;
        cout << "Description: " << post.child("description").at(0).text() << endl;
    }
  } else {
    // error
  }
}
@endcode
*/

#include <QtCore/qglobal.h>

#if defined(PWFENGINE_LIBRARY)
#  define PWFENGINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PWFENGINESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PWFENGINE_GLOBAL_H
