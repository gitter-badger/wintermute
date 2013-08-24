/**
 * vim: ft=qt.cpp
 * Copyright (C) 2013 Jacky Alcine <me@jalcine.me>
 *
 * This file is part of Wintermute, the extensible AI platform.
 *
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

#include "Wintermute/logging.hpp"
#include "Wintermute/Procedure/module.hpp"
#include "Wintermute/private/Procedure/module.hpp"
#include "Wintermute/Procedure/lambda_call.hpp"

using Wintermute::Procedure::Module;
using Wintermute::Procedure::LambdaCall;
using Wintermute::Procedure::ModulePrivate;

QtZeroMQ::Context* Wintermute::Procedure::ModulePrivate::context = 0;

Module::Module(QObject* parent) : QObject(parent), d_ptr(new ModulePrivate(this)){
  Q_D(Module);
  winfo(this, "A new module has entered the guild.");
  d->connectToWire();
  d->sendHeartbeat();
}

// TODO: Wait for a response.
// TODO: Format and return the response.
QVariant
Module::dispatch(Call* call) {
  Q_D(Module);
  const QString callStr = call->toString();

  winfo(this, QString("Sending %1 over the wire to '%2'...").arg(callStr, call->recipient()));
  d->sendData(callStr);
  return d->receiveData();
}

QVariant
Module::invoke(const QString& callName, const QVariantList& arguments){
  Q_D(Module);

  if (!d->calls.contains(callName)) {
    werr(this, QString("The call '%1' doesn't exist in the module '%2'.").arg(callName, qualifiedName()));
    return QVariant(-1);
  }

  CallPointer call = d->calls[callName];
  return call->invoke(arguments);
}

void
Module::mount(CallPointer call){
  Q_D(Module);

  // TODO: Use a shared pointer to prevent a segfault.
  d->calls[call->name()].swap(call);
}

LambdaCall*
Module::mountLambda(Call::Signature lambda, const QString& name){
  CallPointer call = CallPointer(new LambdaCall(lambda, name));
  this->mount(call);
  return dynamic_cast<LambdaCall*>(&*call);
}

QString
Module::domain() const {
  Q_D(const Module);
  return d->domain;
}

QString
Module::package() const {
  Q_D(const Module);
  return d->package;
}

void
Module::setDomain(const QString& value) {
  Q_D(Module);
  d->domain = value;
}

void
Module::setPackage(const QString& value) {
  Q_D(Module);
  d->package = value;
}

Module::~Module() {
  // TODO: Report to world that you're leaving us.
  // TODO: Disconnect sockets.
}

#include "Wintermute/Procedure/module.moc"