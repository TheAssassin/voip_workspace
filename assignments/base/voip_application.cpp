/******************************************************************************/
/*
 *  Project: Voice-over-IP
 *  Author: Matthias Tessmann <matthias.tessmann@th-nuernberg.de
 *  Date: October, 5th 2015
 *
 *  Contents: Application wrapper class skeleton.
 *            Intended for educational purposes.
 *
 *  Additoinal notes:
 *         - There is very little error handling.
 *         - The implementation may contain bugs of any kind!
 *
 * The MIT License (MIT)
 *
 *  Copyright (c) 2015 Matthias Teßmann <matthias.tessmann@th-nuernberg.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/******************************************************************************/

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
      TCLAP::StdOutput().usage(cmd);
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
