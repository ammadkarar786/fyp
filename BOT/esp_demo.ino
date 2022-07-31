
#include<ESP8266WiFi.h>
#include<espnow.h>
#include "Direction.h"

#define MY_ROLE         ESP_NOW_ROLE_COMBO              // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_COMBO              // set the role of the receiver
#define WIFI_CHANNEL    1
Direction m;

///^^^^^^^^^^^^IR SENSOR ^^^^^^^^^^^^^^^
int ledPin = 9; // choose pin for the LED
int inputPin = 4; // choose input pin (for Infrared sensor)
int val = 0; // variable for reading the pin status

///// ARRAY FOR LOCAL USE
char local_motion[15];
bool local_ack;
//#define MY_NAME         "SENSOR NODE"
//uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0xBA, 0xFA, 0xB1};     // PC MAC
//''''''''''''''''''''''''''''''''''''''''''ESP-NOW''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define MY_NAME         "PC NODE"
uint8_t receiverAddress[] = {0xBC, 0xFF, 0x4D, 0x19, 0x7A, 0xAE};   // SENSOR MAC

struct __attribute__((packed)) dataPacket {
  char motion[16];
  bool ack = 0;
  bool reply = 0;
};

void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
  if (transmissionStatus == 0) {
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

  ///&&&&&&&&&&&&&&&&&&&&&&Get array from Interface Bot&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  for (int i = 0; i < 16; i++) {
    local_motion[i] = packet.motion[i];
 
  }
  for (int i = 0; i < 16; i++) {
   Serial.print("channel : ");
   Serial.print(i);
   Serial.print(" ");
    Serial.println(local_motion[i]);
  }
  local_ack = packet.ack;
  Serial.print("Acknowledge");
  Serial.println(packet.ack);
}
//''''''''''''''''''''''''''''''''''''''''''''''ESP-NOW'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void setup() {
  Serial.begin(115200);     // initialize serial port
  m.Motor_Setup();
  /////*********************Espnow Start**********************************************
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // we do not want to connect to a WiFi network

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^IR SENSOR^^^^^^^^^^^^^^^^^^^
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(inputPin, INPUT); // declare Infrared sensor as input  
  }

  esp_now_set_self_role(MY_ROLE);
  esp_now_register_send_cb(transmissionComplete);         // this function will get called once all data is sent
  esp_now_register_recv_cb(dataReceived);               // this function will get called whenever we receive data
  esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

  Serial.println("Initialized.");
  //////************************ESP NOW ENDED********************************************
}

void loop() {
  dataPacket packet;

  if (local_ack == 1) {
    for (int i = 0; i <= 11; i++)
    {
      packet.reply = 1;

      esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));
      m.apply(local_motion[i], m,local_motion[12],local_motion[13],local_motion[14],local_motion[15]);
      ////^^^^^^^^^^^^IR SENSOR^^^^^^^^^^^^^
      val = digitalRead(inputPin); // read input value
   if (val == HIGH)
   { // check if the input is HIGH
      digitalWrite(ledPin, LOW); // turn LED OFF  
   }
   else
   {
      digitalWrite(ledPin, HIGH); // turn LED ON
      delay(5000); //delay of 5 seconds
   }     
    }
  }

  for (int i = 0; i <= 15; i++) {
    local_motion[i] = 0;
  }
  local_ack = 0;
  digitalWrite(ledPin, LOW); 
  delay(100);

}
