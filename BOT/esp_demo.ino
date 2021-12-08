#include<ESP8266WiFi.h>
#include<espnow.h>
#include "Direction.h"

#define MY_ROLE         ESP_NOW_ROLE_COMBO              // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_COMBO              // set the role of the receiver
#define WIFI_CHANNEL    1
Direction m;

char local_motion[3];
//#define MY_NAME         "SENSOR NODE"
//uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0xBA, 0xFA, 0xB1};     // PC MAC

#define MY_NAME         "PC NODE"
uint8_t receiverAddress[] = {0xC4, 0x5B, 0xBE, 0x55, 0x93, 0xA0};   // SENSOR MAC

struct __attribute__((packed)) dataPacket {
  char motion[3];
  int ack=0;
  //int sensor1;
  //int sensor2;
  //float sensor3;
};

void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
  if(transmissionStatus == 0) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error code: ");
    Serial.println(transmissionStatus);
  }
}

void dataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength) {
  char macStr[18];
  dataPacket packet;  

  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);

  Serial.println();
  Serial.print("Received data from: ");
  Serial.println(macStr);
  
  memcpy(&packet, data, sizeof(packet));
  
  Serial.print("sensor1: ");
  Serial.println(packet.motion[0]);
  Serial.print("sensor2: ");
  Serial.println(packet.motion[1]);
  Serial.print("sensor3: ");
  Serial.println(packet.motion[2]);
  Serial.print("sensor4: ");
  Serial.println(packet.motion[3]);
  for(int i=0;i<3;i++){
    local_motion[i]=packet.motion[i];
    }
}
 
void setup() {
  Serial.begin(115200);     // initialize serial port
  m.Motor_Setup();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print(MY_NAME);
  Serial.println("...initializing...");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // we do not want to connect to a WiFi network

  if(esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_set_self_role(MY_ROLE);   
  esp_now_register_send_cb(transmissionComplete);         // this function will get called once all data is sent
  esp_now_register_recv_cb(dataReceived);               // this function will get called whenever we receive data
  esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

  Serial.println("Initialized.");
}

void loop() {
  dataPacket packet;
  
  packet.ack = 1;

  
    for(int i=0;i<4;i++)
    {
     m.apply(local_motion[i],m);
     delay(3000); 
      }
   
  
  

  esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

  delay(3000);
}
