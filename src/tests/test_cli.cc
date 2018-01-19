/// test_cli.cc
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/cli/Cli.h"
  #include "packages/environment/Environment.h"
  #include <iostream>

  using namespace rad::cli;
  using namespace std;

  int main(int argc, char *argv[])
  {
    Cli cli;
    Environment env;

    Cli::cli_interrupt_fn_t interrupt_fn = [&](Interrupt_Signal &sig) -> bool {
      cerr << "interrupt" << endl;
      switch (sig)
      {
        case Interrupt_Signal::Sigint:
          return false;
        case Interrupt_Signal::Sigtstp:
          return false;
        case Interrupt_Signal::Sigusr1:
          return false;
        default:
          return true;
      }
    };
    cli.set_interrupt(interrupt_fn);

    cli.set_options()
      ("file,f", po::value<string>(), "input data file")
      ("verbose,v", po::value<bool>()->default_value(false)->implicit_value(false), "verbose printing to stdout")
      ;

    cli.parse(argc, argv);

    cout << env << endl;

    cout << cli << endl;

    cerr << "verbose => " << std::boolalpha << cli.exists("verbose") << endl;

    if (cli.count("file"))
    {
      const auto filename = cli["file"].as<string>();
      cerr << "file => " << filename << endl;
    }

    cout << flush;
    cerr << flush;

    return EXIT_SUCCESS;
  }

/// *EOF*
