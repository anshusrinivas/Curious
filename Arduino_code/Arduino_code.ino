#include <Wire.h>
#include<LiquidCrystal.h>
#include<string.h>

#define SLAVE_ADDRESS 0x50
LiquidCrystal lcd( 12,11,5,4,3,2);
String inp;
void setup() {
  Wire.begin(SLAVE_ADDRESS); // Initialize the I2C bus as slave
  Wire.onReceive(receiveEvent); // Register a function to be called when data is received
  Wire.onRequest(requestEvent); // Register a function to be called when data is requested
  lcd.begin(16,2);
  Serial.begin(9600); // Initialize serial communication for debugging
  lcd.clear();
}

void receiveEvent(int howMany) {
  inp="";
  while (Wire.available()) {
    char c = Wire.read();
    if(c!='\0'){
      
      inp+=c;
    }
    //lcd.print(c);    
    //Serial.print(c); // Print the received data to the serial monitor
  }
  
  Serial.print(inp);
  lcd.print(inp);
  
}

void requestEvent() {
  Wire.write("Ack!"); // Respond with 6 bytes
}

void loop() {
} 
