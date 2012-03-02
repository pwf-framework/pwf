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
  \class PWrapperCache
  \brief A private class that offers the cache system for a given wrapper.

  Each element is cached by storing its parsed value together with the hashed string representation of its schema,
  this last used to retrieve the value later.
*/
/* TODO: gestire il path alla cartella dove ci sono tutti i file di cache. Chi li setta, questa classe o il wrapper?
         RISPOSTA: il wrapper, in quanto c'è una cache per ogni wrapper, quindi ad es. una per il sito e tante per
                   le singole pagine ed ognuna salva in un file diverso; è il tipo di wrapper che gestisce la path
                   ed il suo formato, questa classe è solo il documento xml, allo stesso modo per il PSchema.
   TODO: impostare cache di livello più alto, infatti se ad es. chiedo un dato alla cache di una pagina,
         questa la cercherà al suo interno, se però non c'è, allora deve richiederla alla cache del sito.
         Ho un collegamento diretto alla cache padre e non ci passo tramite il wrapper in quanto la cache è una classe
         privata che non compare nell'interfaccia pubblica.
*/

#include "PWrapperCache.h"

PWrapperCache::PWrapperCache(PWrapper *wrapper, PWrapperCache *upperCache)
{
    m_wrapper = wrapper;
    m_upperCache = upperCache;
}
