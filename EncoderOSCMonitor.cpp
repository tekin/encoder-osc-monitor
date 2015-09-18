#include "EncoderOSCMonitor.h"

#define RECEIVER_IP "192.168.1.4"
#define RECEIVER_PORT 5678
#define STEPS_PER_REVOLUTION 2500

EncoderOSCMonitor::EncoderOSCMonitor(EthernetUDP &u, uint8_t pin1, uint8_t pin2)
  : udpConnection(u),
    encoder(Encoder(pin1, pin2)),
    current_position(0),
    update_time(millis()) {}

int32_t EncoderOSCMonitor::readPosition() {
  current_position = encoder.read();
  return(current_position);
}

float EncoderOSCMonitor::readSpeed() {
  int32_t old_position        = current_position;
  int32_t position_difference = readPosition() - old_position;
  int32_t time_difference     = millis() - update_time;
  float   revolutions         = (float) position_difference / STEPS_PER_REVOLUTION;
  float speed = (float) revolutions/time_difference * 1000;

  update_time = millis();
  return(speed);
}

void EncoderOSCMonitor::reportSpeed(char* address) {
  sendMessage(address, readSpeed());
}

void EncoderOSCMonitor::reportPosition(char* address) {
  sendMessage(address, readPosition());
}

void EncoderOSCMonitor::sendMessage(char *address, float value) {
  OSCMessage Msg(address);
  Msg.add(value);

  udpConnection.beginPacket(RECEIVER_IP, RECEIVER_PORT);
  Msg.send(udpConnection);
  udpConnection.endPacket();
  Msg.empty(); // free space occupied by message
}
