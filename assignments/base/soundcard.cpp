
#include <iostream>

#include "RtAudio.h"

#include "soundcard.h"

namespace voip {

static std::string supportedSampleTypes(RtAudio::DeviceInfo const& info) {
  std::stringstream s;
  s << ((info.nativeFormats & RTAUDIO_SINT8)   ? "SINT8 "  :"");
  s << ((info.nativeFormats & RTAUDIO_SINT16)  ? "SINT16 " :"");
  s << ((info.nativeFormats & RTAUDIO_SINT24)  ? "SINT24 " :"");
  s << ((info.nativeFormats & RTAUDIO_SINT32)  ? "SINT32 " :"");
  s << ((info.nativeFormats & RTAUDIO_FLOAT32) ? "FLOAT32 ":"");
  s << ((info.nativeFormats & RTAUDIO_FLOAT64) ? "FLOAT64 ":"");
  return s.str();
}

void SoundCard::listDevices() {
    RtAudio audio;

    // Disable display of warning messages
    audio.showWarnings(false);

    const unsigned int nDevs = audio.getDeviceCount();

    RtAudio::DeviceInfo info;
    for (unsigned int i = 0; i < nDevs; ++i) {
      info = audio.getDeviceInfo(i);
      if (info.probed) {
        std::cerr << std::endl;
        std::cerr << "************************************************************" << std::endl;
        std::cerr << "Device ID = " << i << std::endl;
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
    }
    std::cerr << "************************************************************" << std::endl << std::endl;
}

SoundCard::SoundCard(AudioIO *audioIO) : audioIO_(audioIO) {
}

SoundCard::~SoundCard() {
}

}
