/// Environment.cc
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/environment/Environment.h"
  #include <string>
  #include <utility>

  extern char **environ;

namespace rad::cli {

  Environment::Environment()
  {
    initialize();
  }

  Environment::~Environment()
  {
  }

  void Environment::initialize()
  {
    env_.clear();
    for (char **env = environ; *env != 0; ++env)
    {
      std::string envstr = *env;
      const std::pair<const std::string, const std::string> kvp = split_pair(envstr, '=');
      const string_t key   = kvp.first;
      const string_t value = kvp.second;
      env_[key] = value;
    } // foreach entry
  }

  Environment::map_t::iterator Environment::begin()
  {
    return env_.begin();
  }

  Environment::map_t::iterator Environment::end()
  {
    return env_.end();
  }

  std::ostream& operator<<(std::ostream &os, Environment &o)
  {
    std::ios::fmtflags flags(os.flags());
    for(const auto &x : o) os << x.first << "=" << x.second << std::endl;
    os.flags(flags);
    return os;
  }

  std::pair<const std::string, const std::string> Environment::split_pair(std::string str, char delimiter)
  {
    const auto idx    = str.find_first_of(delimiter);
    const auto first  = str.substr(0, idx);
    const auto second = str.substr(idx + 1);
    return std::make_pair(first, second);
  }

} // namespace

  using namespace rad::cli;

/// *EOF*
