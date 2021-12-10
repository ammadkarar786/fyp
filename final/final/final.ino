
#include<ESP8266WiFi.h>
#include<espnow.h>
///multiplexer start
///***************************************************************************************************************
#include "ohm.h"
#include "mult.h"
Resistor_value r1;
int Vin=3.3;
int R1=1000;
int raw=0;
//MULTPLEXER
  int S0=D5;
  int S1=D6;
  int S2=D7;
  int en1=D2;
  int en2=D1;
//Motion array
char Motion1[8];  
char Motion2[8];
///multiplexer end
//****************************************************************************************************************
//esp-now
#define MY_ROLE         ESP_NOW_ROLE_COMBO              // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_COMBO              // set the role of the receiver
#define WIFI_CHANNEL    1

//#define MY_NAME         "SENSOR NODE"
//uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0xBA, 0xFA, 0xB1};     // PC MAC

#define MY_NAME         "PC NODE"
uint8_t receiverAddress[] = {0xBC, 0xFF, 0x4D, 0x19, 0x1D, 0x33};   // SENSOR MAC


struct __attribute__((packed)) dataPacket {
 char motion[15];
 bool ack=0;
 bool reply=0;
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
  
  Serial.print("Reply $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
  Serial.println(packet.reply);
}

//ESPnow END
int button=D3;
 
void setup() {
  Serial.begin(115200);     // initialize serial port
//espnow start
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
//espnow end  
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MULTIPLEXER START%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mult_setup(S0,S1,S2,en1,en2);
pinMode(A0,INPUT);
///%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MULTIPLEXER STOP%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
pinMode(button,INPUT);
}

void loop() {
  dataPacket packet;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::Start Multiplexer:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //MULTIPLEXER PART
 int itr=0; //iteration 
  //enable first multplexer
  digitalWrite(en1,0);
  digitalWrite(en2,1);
  //First Multiplexer
  Serial.println("First Multiplexer");
  for (int i = 0; i <= 8; i++){
    raw=analogRead(A0);
    r1.ohms_setup(Vin,R1,raw);  

    digitalWrite(S0, HIGH && (i & B00000001));
    digitalWrite(S1, HIGH && (i & B00000010));
    digitalWrite(S2, HIGH && (i & B00000100));
    delay(50);
   
    Serial.print("channel");
    Serial.println(i);
    Motion1[i-1]=change_into_char(r1.calculate_ohms());
    
    Serial.println(Motion1[i]);
    delay(50);
    }
 //Second Multiplexer
  digitalWrite(en1,1);
  digitalWrite(en2,0);
  Serial.println("Second Multiplexer");
for (int i = 0; i <= 8; i++){
    raw=analogRead(A0);
    r1.ohms_setup(Vin,R1,raw);  

    digitalWrite(S0, HIGH && (i & B00000001));
    digitalWrite(S1, HIGH && (i & B00000010));
    digitalWrite(S2, HIGH && (i & B00000100));
    delay(50);
    
    Serial.print("channel");
    Serial.println(i+8);
    Motion2[i-1]=change_into_char(r1.calculate_ohms());
    Serial.println(Motion2[i]);
    delay(50);
    }    
    Serial.println("Array");
    ///$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$Put values in packet$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
     int j=0;
        for(int i=0;i<=15;i++){
          if(i>=0 && i<=7){
            packet.motion[i]=Motion1[i];
            }
           else if (i>=8 && i<=15){
            packet.motion[i]=Motion2[j];
            j++;}
            } 
         
    /*  for(int i=0;i<=8;i++){
        Serial.print("channel");
        Serial.print(":  ");
        Serial.print(i+8);
        Serial.println(Motion2[i]);
      }
      */
          
   //print array
      for(int i=0;i<=15;i++){
        Serial.print("channel");
        Serial.print(":  ");
        Serial.print(i);
        Serial.println(packet.motion[i]);
        } 
 
   ////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 

        
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Multiplexer Ended::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  
 
 
  
  ///Send data after button is press
  if(digitalRead(button)==0){
    packet.ack=1;
    
    esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));
   }
    
  delay(100);
}
