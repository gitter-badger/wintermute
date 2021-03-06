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
#include <wintermutecore/module.hpp>

using Wintermute::Module;

class ModuleDesignationTestSuite : public CxxTest::TestSuite
{
public:
  void testConstruct(void)
  {
    Module::Designation des("local", "in.wintermute.test");
    TSM_ASSERT_EQUALS ( "Matches name()", des.name(), "local" );
    TSM_ASSERT_EQUALS ( "Matches domain()", des.domain(), "in.wintermute.test" );
    TSM_ASSERT_EQUALS ( "Matches pid()", des.pid(), getpid() );
  }

  void testConstructWithCustomPID(void)
  {
    Module::Designation des("local", "in.wintermute.test", 300);
    TS_ASSERT_EQUALS ( des.name(), "local" );
    TS_ASSERT_EQUALS ( des.domain(), "in.wintermute.test" );
    TS_ASSERT_EQUALS ( des.pid(), 300 );
  }

  void testAttemptDeserialization(void)
  {
    const string jsonForDesignation = "{\"name\":\"wintermute\", \"domain\":\"me.jalcine\", \"pid\":\"300\"}";
    Module::Designation des(jsonForDesignation);
    Module::Designation desBuilt("wintermute", "me.jalcine", 300);
    TS_ASSERT ( !des.isNull() );
    TS_ASSERT_EQUALS ( des.name(), "wintermute" );
    TS_ASSERT_EQUALS ( des.domain(), "me.jalcine" );
    TS_ASSERT_EQUALS ( des.pid(), 300 );
    TS_ASSERT_EQUALS ( desBuilt, des );
  }

  void testCheckComparsionOperator(void)
  {
    TS_ASSERT_EQUALS ( Module::Designation("foo", "bar", 300), Module::Designation("foo", "bar", 300) );
    TS_ASSERT ( Module::Designation("foo", "foo", 300) != Module::Designation("foo", "bar", 300) );
    TS_ASSERT ( Module::Designation("baz", "bar", 300) != Module::Designation("foo", "bar", 300) );
    TS_ASSERT ( Module::Designation("foo", "bar", 301) != Module::Designation("foo", "bar", 300) );
  }

  void testLocalByDefault(void)
  {
    Module::Designation des("foo", "bar.nation");
    TS_ASSERT_EQUALS ( des.pid(), getpid() );
    TS_ASSERT ( static_cast<std::string>(des).find(std::to_string(getpid())) != std::string::npos );
  }

  void testIsActuallyNull(void)
  {
    Module::Designation des("foo", "bar.nation");
    TS_ASSERT ( !des.isNull() );

    Module::Designation des2;
    TS_ASSERT ( des2.isNull() );
  }
};
