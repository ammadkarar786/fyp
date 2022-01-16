/*
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
//Array
char Motion1[8];  
char Motion2[8];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
mult_setup(S0,S1,S2,en1,en2);
pinMode(A0,INPUT);
}

void loop() {

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
    Serial.println(i);
    Motion2[i-1]=change_into_char(r1.calculate_ohms());
    Serial.println(Motion2[i]);
    delay(50);
    }    
    Serial.println("Array");
     Serial.println("First Multiplexer"); 
    for (int i=0;i<=7;i++){
        
       
        Serial.print("Channel ");
        Serial.print(i);
        Serial.print(" :");
        Serial.println(Motion1[i]);
        }
         Serial.println("Second Multiplexer");
for (int i=0;i<=7;i++){
        
        
        Serial.print("Channel ");
        Serial.print(i+8);
        Serial.print(" :");
        Serial.println(Motion2[i]);
        }
delay(5000);
} */
