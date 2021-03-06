#!/usr/bin/env sh

alias addpkg="sudo apt-get install -qq"

sudo pip install cpp-coveralls --use-mirrors

echo -en "Running tests on $(uname -a)."

# Install pkg-config.
addpkg pkg-config cmake

# Install CxxTest.
addpkg cxxtest

# Install memory and coverage tools.
addpkg valgrind
addpkg lcov

# Install app dependecies.
addpkg libjsoncpp-dev
addpkg liblog4cxx10-dev
addpkg libboost1.54-dev
addpkg libboost-filesystem1.54-dev
addpkg libclang-3.4-common-dev

echo "Done loading dependencies."

sudo ln -s /usr/lib/llvm-3.4/lib/libprofile_rt.a /usr/lib/libprofile_rt.a
