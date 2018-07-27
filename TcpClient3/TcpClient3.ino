
#include <UIPEthernet.h>
#include <EEPROM.h>
#define EEPROM_MAX 4095
#define relay1 5
#define relay2 6
#define relay3 7
#define relay4 8
String cmd;
EthernetClient client;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 5000;  //the value is a number of milliseconds
int addr = 0;


void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  Serial.begin(9600);

  uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
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
  //  while(1)
  //{
  //      if (client.connect(IPAddress(192,168,137,1),23))
  //        {
  //          Serial.println("Client connected");
  //          break;
  //        }
  //         else
  //        Serial.println("Client connect failed");
  //        delay(500);
  //}

}

void loop() {
  while (1)
    //check wheather client is connected or not
  { if (!client.connected())
    {
      if (client.connect(IPAddress(192, 168, 137, 1), 23))  //ip adddress of server and port
      {
        Serial.println("Client connected");
        break;
      }
      else
      {
        Serial.println("Client connect failed");
      }

    }

    currentMillis = millis();
    while (currentMillis - startMillis >= period)         //using timer to send data every  5sec
    {
      client.println("D");
      startMillis = currentMillis;

    }

    int size;
    while ((size = client.available()) > 0)           //check the data is being send from server or not
    {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      Serial.println(size);
      Serial.write(msg, size);
      for (int i = 0; i < size; i++)
      { Serial.print("cmd");
        Serial.println(msg[i]);
        cmd += (char)msg[i];
        Serial.println(cmd);
      }

      if (cmd == "")
      {
        write_eeprom();
      }
      if (cmd == "A0")
      {
        Serial.println("ON");
        digitalWrite(relay1, HIGH);

      }
      else if (cmd == "A1")
      {
        Serial.println("off");
        digitalWrite(relay1, LOW);

      }
      if (cmd == "B0")
      {
        Serial.println("ON");
        digitalWrite(relay2, HIGH);

      }
      else if (cmd == "B1")
      {
        Serial.println("off");
        digitalWrite(relay2, LOW);

      }
      if (cmd == "C0")
      {
        Serial.println("ON");
        digitalWrite(relay3, HIGH);

      }
      else if (cmd == "C1")
      {
        Serial.println("off");
        digitalWrite(relay3, LOW);

      }
      if (cmd == "D0")
      {
        Serial.println("ON");
        digitalWrite(relay4, HIGH);

      }
      else if (cmd == "D1")
      {
        Serial.println("off");
        digitalWrite(relay4, LOW);

      }
      free(msg);
      cmd = "";

    }
  }
}
void write_eeprom()
{
  EEPROM.write(addr, 0);
  addr += 1;

}
void erase_eerprom()
{
  for (int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
  }
}
