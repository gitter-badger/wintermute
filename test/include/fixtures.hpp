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

#include <wintermutecore/module.hpp>
#include <wintermutecore/logging.hpp>

#ifndef WINTERMUTE_TEST_SAMPLE_MODULE
# define WINTERMUTE_TEST_SAMPLE_MODULE

class SampleModule : public Wintermute::Module
{
public:
  explicit SampleModule(const unsigned int index = 1) :
    Wintermute::Module(
        Wintermute::Module::Designation("input", "test" + std::to_string(index) + ".wintermute.in", 3001 + index)
    )
  {
    winfo("SampleModule: My name is " + (string) designation());
  }
};

#endif
