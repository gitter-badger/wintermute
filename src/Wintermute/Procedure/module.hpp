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

#ifndef WINTERMUTE_CORE_PROCEDURE_MODULE_HPP
#define WINTERMUTE_CORE_PROCEDURE_MODULE_HPP

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QScopedPointer>
#include <QtCore/QCoreApplication>
#include <Wintermute/Procedure/Call>

namespace Wintermute {
  namespace Procedure {
    class ModulePrivate;
    class Module : public QObject {
      Q_OBJECT;
      Q_DISABLE_COPY(Module);
      Q_DECLARE_PRIVATE(Module);
      Q_PROPERTY(QString Domain READ domain);
      Q_PROPERTY(QString Package READ package);

      QScopedPointer<ModulePrivate> d_ptr;

      public:
      explicit Module(QObject* parent);
      virtual ~Module();

      /**
       * @fn domain
       * Obtains the domain name that this module lives under.
       */
      virtual QString domain() const = 0;

      /**
       * @fn domain
       * Obtains the package name that identifies this module from other
       * modules.
       */
      virtual QString package() const = 0;

      virtual inline QString qualifiedName() const final {
        return domain() + QString(".") + package() + QString("/") + QString::number(qApp->applicationPid());
      }

      /**
       * @fn dispatch
       * @brief Collects and crafts a call for sending.
       *
       * Uses the arguments to craft a Call to send over the wire.
       */
      QVariant dispatch(const QString& module, const QVariantList& arguments);

      protected:
        /**
         * @fn mountCall
         * @brief Registers the call into the system.
         */
        void mount(CallPointer call);
    };
  } /*  Procedure */
} /*  Wintermute */

#endif /* WINTERMUTE_CORE_PROCEDURE_MODULE_HPP */
