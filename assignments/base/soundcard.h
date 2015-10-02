
#ifndef VOIP_SOUNDCARD_H
#define VOIP_SOUNDCARD_H

namespace voip {

class AudioIO {
public:
  virtual ~AudioIO() = 0;
  virtual int process() = 0;
};

class SoundCard {
public:
  static void listDevices();
  
public:
  SoundCard(AudioIO *audioIO);
  ~SoundCard();

private:

  AudioIO *audioIO_;
};


}

#endif /* VOIP_SOUNDCARD_H */
