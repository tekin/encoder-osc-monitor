#include <EthernetUdp.h>
#include <Encoder.h>
#include <OSCMessage.h>

#ifndef ENCODEROSCMONITOR_H
#define ENCODEROSCMONITOR_H

  class EncoderOSCMonitor {
  public:
    EncoderOSCMonitor(EthernetUDP &u, uint8_t pin1, uint8_t pin2);
    void reportPosition(char *address);
  private:
    EthernetUDP &udpConnection;
    Encoder encoder;
    void sendMessage(char *address, int value);
  };

#endif
