/// test_cli.cc
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/cli/Cli.h"
  #include <iostream>

  using namespace rad::cli;
  using namespace std;

  int main(int argc, char *argv[])
  {
    Cli cli;

    Cli::cli_interrupt_fn_t interrupt_fn = [&](Interrupt_Signal &sig) -> bool {
      cerr << "interrupt" << endl;
      return true;
    };
    cli.set_interrupt(interrupt_fn);

    cli.set_options()
      ("file,f", po::value<string>(), "input data file")
      ("help,h", "print this help message")
      ;

    cli.parse(argc, argv);

    auto vm = cli.get_options();

    cerr << "verbose: " << vm.count("verbose") << endl;

    if (vm.count("file"))
    {
      const auto filename = vm["file"].as<string>();
      cerr << "file: " << filename << endl;
    }

    cout << flush;
    cerr << flush;

    return EXIT_SUCCESS;
  }

/// *EOF*
