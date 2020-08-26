#include <SPI.h>
#include <Ethernet.h>

// network configuration. gateway and subnet are optional.

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // the media access control (ethernet hardware) address for the shield 
byte ip[] = { 192,168,1,180 }; //the IP address for the shield
byte gateway[] = { 192, 168, 1, 1 }; // the routers gateway address
byte subnet[] = { 255, 255, 255, 0 }; // the subnet

EthernetServer server = EthernetServer(10001);

void setup(){
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);
  // start listening for clients
  server.begin();
}

void loop(){
  // if an incoming client connects, there will be bytes available to read:
  EthernetClient client = server.available();
  if (client == true) {
    // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    server.write(client.read());
  }
}
