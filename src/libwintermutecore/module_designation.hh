#include <string>
#include "globals.hpp"
#include "module.hpp"

using std::string;

namespace Wintermute
{
class DesignationPrivate
{
public:
  PID pid;
  string name;
  string domain;

  void clone(const SharedPtr<DesignationPrivate>& other);
};
}