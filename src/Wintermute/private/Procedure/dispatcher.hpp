/**
 * vim: ft=cpp tw=78
 * Copyright (C) 2011 - 2013 Jacky Alciné <me@jalcine.me>
 *
 * Wintermute is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Wintermute is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wintermute.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "Wintermute/Procedure/dispatcher.hpp"
#include "Wintermute/logging.hpp"

namespace Wintermute {
  namespace Procedure {
    class Dispatcher;
    class DispatcherPrivate {
      public:
        static QList<Dispatcher*> dispatchers;

        static bool isDispatcherKnown(Dispatcher* dispatcher)
        {
          Q_FOREACH(Dispatcher* aDispatcher, DispatcherPrivate::dispatchers){
            if (aDispatcher->metaObject()->className() == dispatcher->metaObject()->className())
              return true;
          }

          return false;
        }

        static bool addDispatcher(Dispatcher* dispatcher)
        {
          if (isDispatcherKnown(dispatcher))
            return false;

          DispatcherPrivate::dispatchers << dispatcher;
          wdebug(dispatcher, QString("%1 added to dispatcher pool.").arg(dispatcher->metaObject()->className()));
          return true;
        }

        static bool removeDispatcher(Dispatcher* dispatcher)
        {
          if (!isDispatcherKnown(dispatcher))
            return false;

          DispatcherPrivate::dispatchers.removeAll(dispatcher);
          wdebug(dispatcher, QString("%1 removed from dispatcher pool.").arg(dispatcher->metaObject()->className()));
          return true;
        }
    };
  }
}
