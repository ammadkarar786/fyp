int ECHO=D2;
int Trig=9;

void setup() {
  // put your setup code here, to run once:

pinMode(ECHO,INPUT);
pinMode(Trig,OUTPUT);
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  Read_value(Trig, ECHO);
}


int Read_value(int Trig, int ECHO){
digitalWrite(Trig,LOW);
delay(5);
digitalWrite(Trig,HIGH);
delay(50);
digitalWrite(Trig,LOW);
int duration= pulseIn(ECHO,HIGH);
  int cm=duration/29/2;
Serial.println(cm);
}
