#include<Wire.h>
#include<String.h>
#define TX PD5
#define RX PD6

void setup() {
  // put your setup code here, to run once:
  pinMode(TX,OUTPUT);
  pinMode(RX,INPUT);
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Initializing...");
  Serial.println("initialized");
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()){
  String inp=Serial.readString();
  if(inp!='\0'){
  Serial.println(inp);
  Serial.println("Write \n");
  for(int i=0;i<16;i++)
  {
    deviceWriteOneByte(inp[i],inp[i]);
    delay(5);  
  }
  Serial.println("Write Finish!\r\n");
  }
 }
}

void deviceWriteOneByte(uint8_t addr, uint8_t data)
{
  Wire.beginTransmission(0x50);  //transmit to device AT24C02
  //Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}