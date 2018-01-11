/// Environment.h
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include <cstdlib>
  #include <atomic>
  #include <stdexcept>
  #include <cassert>
  #include <cerrno>
  #include <iostream>
  #include <iomanip>
  #include <map>

#pragma once

namespace rad::cli {

  class Environment
  {
    public:
      using string_t = std::string;
      using map_t = std::map<string_t, string_t>;
      Environment();
      virtual ~Environment();
      void initialize();
      map_t::iterator begin();
      map_t::iterator end();
      bool exists(const string_t key) { return env_.count(key) > 0; };
      const string_t& operator[](const string_t key) { return env_[key]; };
    private:
      map_t env_;
      std::pair<const std::string, const std::string> split_pair(std::string str, char delimiter);
  
      friend std::ostream& operator<<(std::ostream &os, Environment &o);
  }; // Environment

} // namespace

/// *EOF*
