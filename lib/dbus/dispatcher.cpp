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

#include <Wintermute/Logging>
#include <Wintermute/Procedure/Call>
#include "dispatcher.hpp"
#include "module.hpp"
#include "dispatcher.moc"

using Wintermute::DBus::Dispatcher;
using Wintermute::DBus::Module;
using Wintermute::Procedure::Call;

Dispatcher::Dispatcher() :
  Wintermute::Procedure::Dispatcher::Dispatcher() {
  winfo(this, "Yo, waddup?");
}

Dispatcher::~Dispatcher()
{
  winfo(this, "Buh-bye DBus!");
}

void
Dispatcher::sendMessage(const Call* message)
{
  const QByteArray data = message->toString().toUtf8();
  winfo(this, QString("Sending %1").arg(QString(data)));
}