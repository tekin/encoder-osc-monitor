#include <EthernetUdp.h>
#include <Encoder.h>
#include <OSCMessage.h>

#ifndef ENCODEROSCMONITOR_H
#define ENCODEROSCMONITOR_H

  class EncoderOSCMonitor {
  public:
    EncoderOSCMonitor(EthernetUDP &u, uint8_t pin1, uint8_t pin2, char* rip, int rport);
    int32_t readPosition();             // returns the current position of the encoder
    float readSpeed();                  // returns the current rotations per second of the encoder
    void update();                      // call this to recalclulate the position and speed values
    float calculateSpeed();
    void reportPosition(char *address); // report the last recorded position via UDP
    void reportSpeed(char *address);    // report the last calculated speed via UDP
    void reset();                       // resets the position of the encoder to zero
  private:
    int32_t last_position;
    long last_time;
    float last_speed;
    char * remote_ip;
    int remote_port;
    EthernetUDP &udpConnection;
    Encoder encoder;
    void sendMessage(char *address, float value);
  };

#endif
