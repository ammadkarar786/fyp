class Direction{
  
  private:
int m1=D0;
int m2=D5;
int m3=D7;
int m4=D1;
int en1=D6;
int speedm=110;
int delay_m=500;
int delayr=205;
int wait=2000;
  public:
  void Motor_Setup(){
    Serial.begin(115200);
    pinMode(en1,OUTPUT);
    pinMode(m1,OUTPUT);
    pinMode(m2,OUTPUT);
    pinMode(m3,OUTPUT);
    pinMode(m4,OUTPUT);
    }
  void Right(){
    Serial.println("RIGHT");
    analogWrite(en1,speedm);
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
    delay(delayr);
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    delay(wait);
    }  
  void Left(){
    Serial.println("LEFT");
    analogWrite(en1,speedm);
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    delay(delayr);
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    delay(wait);
    }
   
  void Forward(){
    Serial.println("Forward");
    analogWrite(en1,speedm);
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    delay(delay_m);
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    delay(wait);
    } 
  void Stop(){
    Serial.println("Stop");
    analogWrite(en1,speedm);
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    }

  void switch_function(char a,Direction b){
    switch(a){
      case 'R':
      b.Right();
      break;
      case 'L':
      b.Left();
      break;
      case 'F':
      b.Forward();
      break;
      case 'S':
      b.Stop();
      break;
      default:
      Serial.println("NO");
      b.Stop();
      break;
      }    
    }
  void function(char a,char b,char c,char d,Direction e){
    switch_function(a,e);
    switch_function(b,e);
    switch_function(c,e);
    switch_function(d,e);
    
    }
  void apply(char a,Direction b,char c,char d,char e,char f){

    switch(a){
      case 'R':
      b.Right();
      break;
      case 'L':
      b.Left();
      break;
      case 'F':
      b.Forward();
      break;
      case 'U':
      b.function(c,d,e,f,b);
      break;
      default:
      Serial.println("NO");
      b.Stop();
      break;
      }
    }    
  
  };
