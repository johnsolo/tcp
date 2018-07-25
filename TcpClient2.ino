#include <UIPEthernet.h>

EthernetClient client;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 5000;  //the value is a number of milliseconds


void setup() {

  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  Ethernet.begin(mac);

  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println("Client connect");
      // replace hostname with name of machine running tcpserver.pl
//      if (client.connect("server.local",5000))
while(1)
{
      if (client.connect(IPAddress(192,168,137,1),23))
        {
          Serial.println("Client connected");
          break;
        }
         else
        Serial.println("Client connect failed");
}
  


}

void loop() {
long int initial,final;
currentMillis = millis();
      while(currentMillis - startMillis >= period)
      {
          client.println("DATA from Client");
          startMillis = currentMillis; 
         
      }
          int size;
          while((size = client.available()) > 0)
            {
              uint8_t* msg = (uint8_t*)malloc(size);
              size = client.read(msg,size);
              Serial.write(msg,size);
              free(msg);
            }
         //client.stop();
         //delay(1000);
        }
     
    

