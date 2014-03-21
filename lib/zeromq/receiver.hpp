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

#ifndef WINTERMUTE_PLUGIN_ZEROMQ_RECEIVER_HPP
#define WINTERMUTE_PLUGIN_ZEROMQ_RECEIVER_HPP

#include <Wintermute/Procedure/Receiver>

namespace Wintermute
{
namespace ZeroMQ
{
class Module;
class Receiver : public Wintermute::Procedure::Receiver
{
  Q_OBJECT;
  Q_DISABLE_COPY ( Receiver );
  QtZeroMQ::PollingSocket* m_socket;

public:
  explicit Receiver ( Wintermute::ZeroMQ::Module* module );
  virtual ~Receiver();

private:
  Q_SLOT void onMessageReceived ( const QList<QByteArray>& data );
};
}
}

#endif