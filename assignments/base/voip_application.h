
#ifndef VOIP_APPLICATION_H
#define VOIP_APPLICATION_H

namespace voip {

class Application {
public:
  Application();
  ~Application();

  int exec(int argc, char *argv[]);

private:
  Application(Application const&);
  Application& operator=(Application const&);

  bool init(int argc, char *argv[]);
  void listDevices();
};

}

#endif /* VOIP_APPLICATION_H */
