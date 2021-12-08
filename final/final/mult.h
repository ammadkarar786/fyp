void mult_setup(int S0,int S1, int S2,int en1,int en2){
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
}

char change_into_char(int a){
  
  
  }


/*
#include "ohm.h"
Resistor_value r; 
int read_a0=analogRead(A0);
float ref_resistance=1000;

class mult{
  private:
  int S0=D5;
  int S1=D6;
  int S2=D7;
  int en1=D0;
  int en2=D1;
  float val=A0;
  public:
  void mult_setup(){
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(A0,INPUT);
  r.ohms_setup(3.3,ref_resistance,read_a0);
  }
  void take_value1(int movement[8]){
   
  int itr=0; //iteration 
  //enable first multplexer
  digitalWrite(en1,0);
  digitalWrite(en2,1);
  Serial.println("First Multiplexer");
  for (int i = 0; i < 8; i++){
    digitalWrite(S0, HIGH && (i & B00000001));
    digitalWrite(S1, HIGH && (i & B00000010));
    digitalWrite(S2, HIGH && (i & B00000100));
    delay(1000);
    movement[itr]=r.calculate_ohms();
    itr++;
    Serial.print("channel");
    Serial.println(itr);
    }}
   void take_value2(int movement[8]){
   
  int itr1=0; //iteration 
  //enable second multplexer
  digitalWrite(en1,1);
  digitalWrite(en2,0);
  Serial.println("second Multiplexer");
  for (int i = 0; i < 8; i++){
    digitalWrite(S0, HIGH && (i & B00000001));
    digitalWrite(S1, HIGH && (i & B00000010));
    digitalWrite(S2, HIGH && (i & B00000100));
    delay(500);
    movement[itr1]=r.calculate_ohms();
    itr1++;
    Serial.print("itr");
    Serial.println(itr1);
    }  
  }
  void Display_array(int array1[8]){
      Serial.println("array");
      for (int i=0;i<=8;i++){
        Serial.println(array1[i]);
        }
        }
  };*/
