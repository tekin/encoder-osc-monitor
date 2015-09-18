#include "EncoderOSCMonitor.h"

#define RECEIVER_IP "192.168.1.4"
#define RECEIVER_PORT 5678

EncoderOSCMonitor::EncoderOSCMonitor(EthernetUDP &u, uint8_t pin1, uint8_t pin2): udpConnection(u), encoder(Encoder(pin1, pin2)) {}

void EncoderOSCMonitor::reportPosition(char* address) {
  sendMessage(address, encoder.read());
}

void EncoderOSCMonitor::sendMessage(char *address, int value) {
  OSCMessage Msg(address);
  Msg.add(value);

  udpConnection.beginPacket(RECEIVER_IP, RECEIVER_PORT);
  Msg.send(udpConnection);
  udpConnection.endPacket();
  Msg.empty(); // free space occupied by message
}
