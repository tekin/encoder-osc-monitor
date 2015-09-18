#include <EthernetUdp.h>
#include <Encoder.h>
#include <OSCMessage.h>

#ifndef ENCODEROSCMONITOR_H
#define ENCODEROSCMONITOR_H

  class EncoderOSCMonitor {
  public:
    EncoderOSCMonitor(EthernetUDP &);
  private:
    EthernetUDP &udpConnection;
  };

#endif
