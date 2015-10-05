/******************************************************************************/
/*
 *  Project: Voice-over-IP
 *  Author: Matthias Tessmann <matthias.tessmann@th-nuernberg.de
 *  Date: October, 5th 2015
 *
 *  Contents: Sound card wrapper class skeleton.
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
