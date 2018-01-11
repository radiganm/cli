/// test_cli.cc
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/cli/Cli.h"
  #include <iostream>

  using namespace rad::cli;

  int main(int argc, char *argv[])
  {
    Cli cli;

    Cli::cli_interrupt_fn_t interrupt_fn = [&](Interrupt_Signal &sig) -> bool {
      std::cerr << "interrupt" << std::endl;
      return true;
    };
    cli.set_interrupt(interrupt_fn);

    cli.options()
      ("verbose,v", "verbose printing to stdout")
      ;

    cli.parse(argc, argv);
    return EXIT_SUCCESS;
  }

/// *EOF*
