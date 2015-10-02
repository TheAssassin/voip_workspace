
#include <iostream>

#include "voip_application.h"
#include "soundcard.h"

#include "tclap/CmdLine.h"

namespace voip {

Application::Application() {}
Application::~Application() {}

int Application::exec(int argc, char *argv[]) {

  if (!init(argc, argv)) {
    std::cerr << "Error initializing!" << std::endl;
    return -1;
  }

  std::cout << "Hello World!" << std::endl;

  return 0;
}

bool Application::init(int argc, char *argv[]) {

  /* Set up command line arguments */
  try {

    TCLAP::CmdLine cmd("VoIP Real-Time Communication Project", ' ', "0.1");

    TCLAP::SwitchArg listDevices("l", "list-devices", "List audio devices", cmd, false);

    TCLAP::ValueArg<int> inDev("i", "input-device", "Select input device", false, -1, "int", cmd);
    TCLAP::ValueArg<int> outDev("o", "output-device", "Select output device", false, -1, "int", cmd);

    TCLAP::ValueArg<unsigned int> inCh("", "inCh", "Number of input channels (default: 1)", false, 1, "unsigned int", cmd);
    TCLAP::ValueArg<unsigned int> outCh("", "outCh", "Number of output channels (default 1)", false, 1, "unsigned int", cmd);

    TCLAP::ValueArg<unsigned int> fs("f", "Framesize", "Framesize (default: 512)", false, 512, "unsigned int", cmd);

    TCLAP::ValueArg<unsigned int> s("s", "samplerate", "Samplerate (default: 44100)", false, 44100, "unsigned int", cmd);

    TCLAP::ValueArg<unsigned int> rPort("", "rPort", "Remote Port (default: 1976)", false, 1976, "unsigned int", cmd);
    TCLAP::ValueArg<unsigned int> lPort("", "lPort", "Local Port (default: 1976)", false, 1976, "unsigned int", cmd);

    TCLAP::UnlabeledValueArg<std::string> destIp("destIp", "Destination IP address", false, "", "std::string", cmd);

    cmd.parse(argc, argv);

    /* Add argument processing here */
    if (listDevices.getValue()) {
      this->listDevices();
      exit(0);
    }

    // if -l is not specified, the IP is mandatory
    if (destIp.getValue() == "") {
      TCLAP::StdOutput out;
      out.usage(cmd);
      exit(-1);
    }


  } catch (TCLAP::ArgException& argEx) {
    std::cerr << "Error parsing command line arguments: " << argEx.error() << " for argument " << argEx.argId() << std::endl;
    return false;
  }

  return true;
}

void Application::listDevices() {
  SoundCard::listDevices();
}

}
