/**
 * vim: ft=cpp tw=78
 * Copyright (C) 2014 Jacky Alciné <me@jalcine.me>
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

#include <QtDBus/QDBusConnection>
#include <QtCore/QCoreApplication>
#include <Wintermute/Logging>
#include "receiver.hpp"
#include "adaptor.hpp"
#include "adaptor.moc"

using Wintermute::DBus::Adaptor;
using Wintermute::DBus::Receiver;

Adaptor::Adaptor( Receiver* receiver ) :
    QDBusAbstractAdaptor( receiver)
{
  winfo (this, "Adaptor created.");
}

void
Adaptor::registerOnDBus()
{
  QDBusConnection bus = QDBusConnection::sessionBus();
  bus.registerObject( "/Process" +
    QString::number ( QCoreApplication::applicationPid() ), parent() 
  );
  winfo ( this, "Registered this process into D-Bus." );
}

Adaptor::~Adaptor()
{
}
