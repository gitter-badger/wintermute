/*
 * Wintermute is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Wintermute is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with Wintermute; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef WINTERMUTE_CORE_LOGGING_HPP
# define WINTERMUTE_CORE_LOGGING_HPP

#include <string>
#include <wintermutecore/globals.hpp>

using std::string;

namespace Wintermute
{

/*
 * @brief Basis of logging in Wintermute.
 * This class holds the foundational aspects of Wintermute's logging and
 * abstracts it out so that the logging service can be swapped to and fro
 * without much discomfort to the codebase.
 */
class Logging
{
  explicit Logging();
public:
  virtual ~Logging();
  /* Levels at which Wintermute is capable of reporting its log messages. */
  enum Level
  {
    Disabled = 0x0,
    Trace = 0x01,
    Debug = 0x10,
    Info  = 0x20,
    Warn  = 0x30,
    Error = 0x40,
    Fatal = 0x50
  };

  /* Sets the level of logging that Wintermute uses globally. */
  void setLevel(const Level& level = Level::Error);

  /* Obtains the level of logging that Wintermute is using. */
  Level level() const;

  /* Outputs a Level::Debug message into Wintermute's logger. */
  void debug(const string& message, const string& name);

  /* Outputs a Level::Error message into Wintermute's logger. */
  void error(const string& message, const string& name);

  /* Outputs a Level::Info message into Wintermute's logger. */
  void info(const string& message, const string& name);

  /* Outputs a Level::Warn message into Wintermute's logger. */
  void warn(const string& message, const string& name);

  /* Outputs a Level::Trace message into Wintermute's logger. */
  void trace(const string& message, const string& name);

  W_DEF_SINGLETON(Logging);
};
}

#define wlog        Wintermute::Logging::instance()
#define winfo(msg)  wlog->info(msg, WINTERMUTE_LOGGER_ROOT_NAME);
#define werror(msg) wlog->error(msg, WINTERMUTE_LOGGER_ROOT_NAME);
#define wwarn(msg)  wlog->warn(msg, WINTERMUTE_LOGGER_ROOT_NAME);

#ifdef WINTERMUTE_DEBUG
# define wtrace(msg) wlog->trace(msg, WINTERMUTE_LOGGER_ROOT_NAME);
# define wdebug(msg) wlog->debug(msg, WINTERMUTE_LOGGER_ROOT_NAME);
#else
# define wdebug(msg) w_noop();
# define wtrace(msg) w_noop();
#endif

#define DISABLE_LOGGING Wintermute::Logging::instance()->setLevel(Logging::Disabled)
#define ENABLE_LOGGING(Level)  Wintermute::Logging::instance()->setLevel(Logging::#Level)

#endif
