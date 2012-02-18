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

/**
  @mainpage PWF Engine

PWF Engine is the engine of the PWF framework, used to create web wrappers based on generic schemas.

Let's suppose you want to navigate a page of a website to extract some information from it.
The first thing you have to is to create the engine class specifying the schemas root directory:
@code
PEngine *engine = new PEngine();
engine->setSchemasCandidatesDirectory("schemas/");
@endcode
@see PEngine

Now you can create the site wrapper passing the engine to it:
@code
PSiteWrapper *myWrapper = new PSiteWrapper(engine);
myWrapper->setUrl("http://www.sitename.com/");
@endcode
@see PSiteWrapper

Now the critical part: setting a schema. You have two choices:

- Automatically detect the schema, use this if you don't know
what is the specific schema but you have a list of possible candidates.
@code
PAction *schemaAction = myWrapper->detectSchema();
@endcode
In this case you have only an idea of the site content, e.g. a forum, but you have schemas for the various
kinds, e.g. one for phpbb, one for smf, etc., so you let the system detects the right schema for you.

- Set the schema manually:
@code
PAction *schemaAction = myWrapper->setSchema("smf");
@endcode
In this case you already know that the site is an smf forum and so matches the schema written for it.

Obviously, these are only some examples of schema usages, (ideally) you could model a generic schema
that apply to all forums!
*/

#include <QtCore/qglobal.h>

#if defined(PWFENGINE_LIBRARY)
#  define PWFENGINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define PWFENGINESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PWFENGINE_GLOBAL_H
