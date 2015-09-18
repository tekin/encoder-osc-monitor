#include <EthernetUdp.h>
#include <Encoder.h>
#include <OSCMessage.h>

#ifndef ENCODEROSCMONITOR_H
#define ENCODEROSCMONITOR_H

  class EncoderOSCMonitor {
  public:
    EncoderOSCMonitor(EthernetUDP &u, uint8_t pin1, uint8_t pin2);
    int32_t readPosition();             // returns the current position of the encoder
    float readSpeed();                  // returns the current rotations per second of the encoder
    void reportPosition(char *address); // sends the current position via UDP
    void reportSpeed(char *address);    // sends the current speed via UDP
  private:
    int32_t current_position;
    long update_time;
    EthernetUDP &udpConnection;
    Encoder encoder;
    void sendMessage(char *address, float value);
  };

#endif
