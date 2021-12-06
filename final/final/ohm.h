class Resistor_value
{
  private:
  int raw;
  int Vin;
  float Vout;
  float R1;
  float R2;
  float buffer;
public:
void ohms_setup(int in,float r1,int RAW)
{
    Vin=in;
    R1=r1;
    raw=RAW;
}

int calculate_ohms(){
  buffer= raw * Vin;
Vout= (buffer)/1024.0;

buffer= (Vin/Vout) -1;
R2= R1 * buffer;

Serial.print("Vout: ");

Serial.println(Vout);

Serial.print("R2: ");

Serial.println(R2);
return R2;
  }

char Compare(float a){
   
  
  
  }   
  };
