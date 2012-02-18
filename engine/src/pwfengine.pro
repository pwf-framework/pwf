##
##    Copyright 2011, 2012 Manuel Dell'Elce
##
##    This file is part of pwfengine.
##
##    pwfengine is free software: you can redistribute it and/or modify
##    it under the terms of the GNU Lesser General Public License as published by
##    the Free Software Foundation, either version 3 of the License, or
##    (at your option) any later version.
##
##    pwfengine is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU Lesser General Public License for more details.
##
##    You should have received a copy of the GNU Lesser General Public License
##    along with pwfengine.  If not, see <http://www.gnu.org/licenses/>.

#-------------------------------------------------
#
# Project created by QtCreator 2011-07-06T19:06:20
#
#-------------------------------------------------

QT       += network script xml
QT       -= gui

TARGET = pwfengine
TEMPLATE = lib

DESTDIR = ../bin/
INCLUDEPATH += schema wrapper_elements wrapper_actions

DEFINES += PWFENGINE_LIBRARY

SOURCES += PEngine.cpp \
    PEnginePrivate.cpp \
    PWrapper.cpp \
    PWrapperPrivate.cpp \
    PPageWrapper.cpp \
    PPageWrapperPrivate.cpp \
    PSiteWrapper.cpp \
    PSiteWrapperPrivate.cpp \
    PPageElementList.cpp \
    PPageElement.cpp \
    PPageElementPrivate.cpp \
    PPageElementListPrivate.cpp \
    schema/PSchema.cpp \
    schema/PSchemaPrivate.cpp \
    schema/PSchemaElement.cpp \
    schema/PSchemaElementPrivate.cpp \
    PAction.cpp \
    PActionPrivate.cpp \
    PActionGroup.cpp \
    PActionGroupPrivate.cpp \
    wrapper_elements/PWrapperRequire.cpp \
    wrapper_elements/PWrapperRequirePrivate.cpp \
    wrapper_elements/PWrapperData.cpp \
    wrapper_elements/PWrapperDataPrivate.cpp \
    wrapper_elements/PWrapperSearch.cpp \
    wrapper_elements/PWrapperSearchPrivate.cpp \
    wrapper_actions/PFindSchemaElement.cpp \
    wrapper_actions/PAttemptSchema.cpp \
    wrapper_actions/PEvalWrapperRequire.cpp \
    PWrapperCache.cpp \
    wrapper_elements/PWrapperElement.cpp \
    wrapper_elements/PWrapperElementPrivate.cpp

HEADERS += PEngine.h\
        pwfengine_global.h \
    PEnginePrivate.h \
    PWrapper.h \
    PWrapperPrivate.h \
    PPageWrapper.h \
    PPageWrapperPrivate.h \
    PSiteWrapper.h \
    PSiteWrapperPrivate.h \
    PPageElementList.h \
    PPageElement.h \
    PPageElementPrivate.h \
    PPageElementListPrivate.h \
    PSchema.h \
    PSchemaPrivate.h \
    PSchemaElement.h \
    PSchemaElementPrivate.h \
    PAction.h \
    PActionPrivate.h \
    PActionGroup.h \
    PActionGroupPrivate.h \
    PWrapperElement.h \
    PWrapperElementPrivate.h \
    PWrapperRequire.h \
    PWrapperRequirePrivate.h \
    PWrapperData.h \
    PWrapperDataPrivate.h \
    PWrapperSearch.h \
    PWrapperSearchPrivate.h \
    PFindSchemaElement.h \
    PAttemptSchema.h \
    PEvalWrapperRequire.h \
    PWrapperCache.h

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEDB35CA8
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = tawe.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
