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

#include "test_suite.hpp"
#include "libwintermutecore/plugin.hpp"

using Wintermute::Plugin;

class PluginTestSuite : public CxxTest::TestSuite
{
public:
  void testCreatePlugin(void)
  {
    // Check the ABI version of the plugin against this instance.
  }

  void testDestroyPlugin(void)
  {
    // Ensure plugin is not discoverable via lookup.
  }

  void testStartPlugin(void)
  {
    // Ensure that plugin's startup code is run after internal work.
  }

  void testStopPlugin(void)
  {
    // Ensure that plugin's shutdown code is run before internal work.
  }

};
