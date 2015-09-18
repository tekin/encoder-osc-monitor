#include "EncoderOSCMonitor.h"

#define STEPS_PER_REVOLUTION 2500

EncoderOSCMonitor::EncoderOSCMonitor(EthernetUDP &u, uint8_t pin1, uint8_t pin2, char* rip, int rport)
  : udpConnection(u),
    encoder(Encoder(pin1, pin2)),
    remote_ip(rip),
    remote_port(rport),
    last_position(0),
    last_speed(0.0),
    last_time(millis()) {}

void EncoderOSCMonitor::update() {
  last_speed    = calculateSpeed();
  last_position = encoder.read();
  last_time     = millis();
}

float EncoderOSCMonitor::calculateSpeed(){
  int32_t position_difference = encoder.read() - last_position;
  int32_t time_difference     = millis() - last_time;
  float   revolutions         = (float) position_difference / STEPS_PER_REVOLUTION;
  float speed = (float) revolutions/time_difference * 1000;

  return(speed);
}

int32_t EncoderOSCMonitor::readPosition() {
  return(last_position);
}

float EncoderOSCMonitor::readSpeed() {

  return(last_speed);
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

  udpConnection.beginPacket(remote_ip, remote_port);
  Msg.send(udpConnection);
  udpConnection.endPacket();
  Msg.empty(); // free space occupied by message
}
