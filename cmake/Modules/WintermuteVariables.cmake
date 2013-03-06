## TODO: Add proper CMake module definition here.
###############################################################################
### Copyright (C) 2013 Jacky Alcine <jacky.alcine@thesii.org>
###
### This file is part of Wintermute, the extensible AI platform.
###
### Wintermute is free software; you can redistribute it and/or modify
### it under the terms of the GNU General Public License as published by
### the Free Software Foundation; either version 3 of the License, or
### (at your option) any later version.
###
### Wintermute is distributed in the hope that it will be useful,
### but WITHOUT ANY WARRANTY; without even the implied warranty of
### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
### GNU General Public License for more details.
###
### You should have received a copy of the GNU General Public License
### along with Wintermute.  If not, see <http://www.gnu.org/licenses/>.
###############################################################################

# Include some modules necessary for paths.
# NOTE: These paths are going to be fixed to GNU-compliant systems for now.
include(GNUInstallDirs)

# Define some Wintermute-specific variables.
set(WINTERMUTE_VERSION "${WINTERMUTE_MAJOR_VERSION}.${WINTERMUTE_MINOR_VERSION}.${WINTERMUTE_PATCH_VERSION}")
set(WINTERMUTE_INCLUDE_DIR ${CMAKE_INSTALL_FULL_INCLUDEDIR})
set(WINTERMUTE_LIBRARY_DIR ${CMAKE_INSTALL_FULL_LIBDIR})
set(WINTERMUTE_CMAKE_MODULES_DIR "${CMAKE_INSTALL_FULL_DATAROOTDIR}/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules")
set(WINTERMUTE_COMPILE_DEFINITIONS "WINTERMUTE_NDEBUG")
set(WINTERMUTE_COMPILE_DEFINITIONS_DEBUG "WINTERMUTE_DEBUG")
set(WINTERMUTE_COMPILE_FLAGS "-O0 -Wall -g -std=c++11")
set(WINTERMUTE_LIBRARIES ${QT_LIBRARIES} 
  ${QCOMMANDLINE_LIBRARIES})
set(WINTERMUTE_INCLUDE_DIRS ${QT_INCLUDE_DIR}
  ${QCOMMANDLINE_INCLUDE_DIR})

# Change some CMake settings.
set(CMAKE_USE_RELATIVE_PATHS true)
set(CMAKE_VERBOSE_MAKEFILE false)