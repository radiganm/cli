/// Cli.h
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include <signal.h>
  #include <type_traits>
  #include <functional>
  #include <boost/property_tree/ptree.hpp>
  #include <boost/property_tree/xml_parser.hpp>
  #include <boost/foreach.hpp>
  #include <boost/program_options.hpp>

#pragma once

  #define CLI__ENABLE_STACKTRACE

namespace rad::cli {

  namespace po = boost::program_options;

  static void interrupt(int signo);

  enum class Interrupt_Signal 
  {
    Sigint = SIGINT
  };

  class Cli
  {
      
    public:
      using cli_interrupt_fn_t = std::function<bool (Interrupt_Signal &sig)>;
      
      Cli();
      virtual ~Cli();
      
      void parse(int argc, char* argv[]);
      po::options_description_easy_init set_options();
      po::variables_map get_options() { return vm_; }
      
      void interrupt(int signo);
      void set_interrupt(cli_interrupt_fn_t &fn);

      po::options_description_easy_init operator()();
      int count(std::string name);
      bool exists(std::string name);
      const po::variable_value& operator[](std::string name) const;
      
    private:
      
      int argc_                      {0};
      char** argv_                   {nullptr};
      std::atomic<bool> verbose_     {false};
      po::options_description desc_  {"options"};
      po::variables_map vm_;
      cli_interrupt_fn_t signal_fn_;
      
      friend std::ostream& operator<<(std::ostream &os, Cli &o);
      
  };

} // namespace

/// *EOF*
