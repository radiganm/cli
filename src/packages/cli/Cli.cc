/// Cli.cc
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/cli/Cli.h"
  #include <iostream>
  #include <iomanip>
  #include <cstring>
  #include <atomic>
  #include <sstream>
  #include <cstdlib>
  #include <stdexcept>

#ifdef CLI__ENABLE_STACKTRACE
  #include <boost/stacktrace.hpp>
#endif

namespace rad::cli {

  namespace po = boost::program_options;

  using std::cout;
  using std::cerr;
  using std::endl;
  using std::flush;

  Cli *theCli = nullptr;

  static void interrupt(int signo)
  {
    theCli->interrupt(signo);
  }

  void Cli::interrupt(int signo)
  {
    auto sig = static_cast<Interrupt_Signal>(signo);
    const auto ok = signal_fn_(sig);
    if (not ok)
    {
#ifdef CLI__ENABLE_STACKTRACE
      cerr << boost::stacktrace::stacktrace() << endl << flush;
#endif
      exit(EXIT_SUCCESS);
    }
  }

  Cli::Cli()
  {
    /// default interrupt
    cli_interrupt_fn_t interrupt_fn = [&](Interrupt_Signal &sig) -> bool {
      return true;
    };
    set_interrupt(interrupt_fn);
  }

  po::options_description_easy_init Cli::operator()()
  { 
    return set_options(); 
  }

  int Cli::count(std::string name)
  {
    return vm_.count(name.c_str());
  }

  bool Cli::exists(std::string name)
  {
    return 0 != vm_.count(name.c_str());
  }

  const po::variable_value& Cli::operator[](std::string name) const
  {
    if (not vm_.count(name.c_str())) 
      throw std::runtime_error("invalid option access");
    return vm_[name.c_str()];
  }

  Cli::~Cli()
  {
  }

  po::options_description_easy_init Cli::set_options() 
  { 
    return desc_.add_options()
      ("help,h", "print this help message")
    ;
  }

  void Cli::parse(int argc, char* argv[])
  {
    argc_ = argc;
    argv_ = argv;
    po::store(po::parse_command_line(argc, argv, desc_), vm_);
    po::notify(vm_);
    if(argc_ < 2)
    { 
      cout << desc_ << endl;
      exit(EXIT_FAILURE);
    }
    if(vm_.count("help")) 
    { 
      cout << desc_ << endl;
      exit(EXIT_SUCCESS);
    }
  }

  void Cli::set_interrupt(cli_interrupt_fn_t &fn)
  {
    theCli = this;
    if(SIG_ERR == signal(SIGINT, ::rad::cli::interrupt)) {
      perror("unable to set signal");
      throw std::runtime_error("unable to set signal handler");
    }
  }

  std::ostream& operator<<(std::ostream &os, const rad::cli::Cli &o)
  {
    std::ios::fmtflags flags(os.flags());
    for (const auto& it : o.get_options()) 
    {
      os << it.first.c_str() << ": ";
      auto &value = it.second.value();
      if (auto v = boost::any_cast<uint32_t>(&value))
      {
        os << *v;
      }
      else if (auto v = boost::any_cast<bool>(&value))
      {
        os << std::boolalpha << *v;
      }
      else if (auto v = boost::any_cast<std::string>(&value))
      {
        os << *v;
      }
      os << std::endl;
    }
    os.flags(flags);
    return os;
  }

} // namespace

  using namespace rad::cli;

/// *EOF*
