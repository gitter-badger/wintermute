# Installing Wintermute

This file documents the process of installing Wintermute onto your operating 
system. These instructions apply to Linux, more specificially Kubuntu Raring 
Ringtail 13.04.

## Requirements
Wintermute requires a few dependencies at this version. Right now, the only
targeted platform is `Linux` due to its heavy dependency on D-Bus but work 
provided by contributors of other platforms.

> Work is being done to refactor out the logic originally used for D-Bus and
> to use [ZeroMQ](http://zeromq.org) instead for cross-platform support.

  * CMake 2.8
  * Qt 4.7 or greater - http://qt-project.org
  * QCommandLine - https://github.com/jalcine/qcommandline
  * QLogger - https://gitorious.org/log4qt/log4qt
  * Qt bindings to [ZeroMQ](http://zeromq.org) - https://github.com/jonnydee/nzmqt

If you want to test Wintermute, you'll need the following:

  * gcov 4.6
  * lcov 1.9
  * valgrind 3.8.1

Once you've satisfied those dependencies, building is a breeze. Seriously.

## Procedure

```bash
$ mkdir build && cd build              # Create and enter build directory.
$ cmake .. -DCMAKE_BUILD_TYPE=Debug    # Configure Wintermute for debugging.
$ make                                 # Build Wintermute.
$ make test                            # (optional) Test Wintermute.
$ make coverage                        # (optional) Get coverage information.
$ make memorycheck                     # (optional) Checks for memory leaks.
$ make install                         # Install Wintermute if `CMAKE_INSTALL_PREFIX` is user writable. 
# make install                         # Install Wintermute system-wide.
```

Once you've satisfied those dependencies, building is a breeze. Seriously.
The instructions above install Wintermute to a local binary directory (my personal setup)
and can be executed like so:

```bash
$ ~/.local/bin/wintermute
$ wintermute # If ~/.local/bin is in your $PATH
```
