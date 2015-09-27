
/* This is a simple demo that enumerates all audio devices on the system. */

#include <iostream>
#include <sstream>
#include "RtAudio.h"

std::string supportedSampleTypes(RtAudio::DeviceInfo const& info) {
  std::stringstream s;
  s << ((info.nativeFormats & RTAUDIO_SINT8)   ? "SINT8 "  :"");
  s << ((info.nativeFormats & RTAUDIO_SINT16)  ? "SINT16 " :"");
  s << ((info.nativeFormats & RTAUDIO_SINT24)  ? "SINT24 " :"");
  s << ((info.nativeFormats & RTAUDIO_SINT32)  ? "SINT32 " :"");
  s << ((info.nativeFormats & RTAUDIO_FLOAT32) ? "FLOAT32 ":"");
  s << ((info.nativeFormats & RTAUDIO_FLOAT64) ? "FLOAT64 ":"");
  return s.str();
}

void printDeviceInfo(RtAudio::DeviceInfo const& info) {
  std::cerr << std::endl;
  std::cerr << "************************************************************" << std::endl;
  std::cerr << "Device Name = " << info.name << std::endl;
  std::cerr << "Supported Channels (in/out/duplex) = ";
  std::cerr << info.inputChannels << "/" << info.outputChannels << "/" << info.duplexChannels << std::endl;
  std::cerr << "Native sample rates = ";
  for (unsigned int i = 0; i < info.sampleRates.size(); ++i) {
    std::cerr << info.sampleRates[i] << "Hz" << (i == info.sampleRates.size()-1 ? " ":", ");
  }
  std::cerr << std::endl;
  std::cerr << "Native sample types = " << supportedSampleTypes(info) << std::endl;

  std::cerr << "Is default input/output device = " << (info.isDefaultInput ? "YES":"NO") << " / ";
  std::cerr << (info.isDefaultOutput ? "YES":"NO") << std::endl;
}

int main() {
  std::cerr << std::endl << "Available audio devices on this system: " << std::endl;
  RtAudio audio;

  // Disable display of warning messages
  audio.showWarnings(false);

  const unsigned int nDevs = audio.getDeviceCount();

  RtAudio::DeviceInfo info;
  for (unsigned int i = 0; i < nDevs; ++i) {
    info = audio.getDeviceInfo(i);
    if (info.probed) {
      printDeviceInfo(info);
    }
  }
  std::cerr << std::endl << "************************************************************" << std::endl;
  std::cerr << "Done." << std::endl;
  return 0;
}
