#include <EthernetUdp.h>
#include <Encoder.h>
#include <OSCMessage.h>

#ifndef ENCODEROSCMONITOR_H
#define ENCODEROSCMONITOR_H

  class EncoderOSCMonitor {
  public:
    EncoderOSCMonitor(EthernetUDP &u, uint8_t pin1, uint8_t pin2);
    int32_t readPosition();
    void reportPosition(char *address);
  private:
    int32_t current_position;
    EthernetUDP &udpConnection;
    Encoder encoder;
    void sendMessage(char *address, float value);
  };

#endif
