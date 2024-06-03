# Bluetooth Messenger
# Introduction
In recent years, the integration of wireless communication into embedded systems has significantly expanded the scope and capabilities of modern technology. One prominent wireless technology is Bluetooth, which offers a reliable and efficient means of data transmission over short distances.
This project involves developing a simple embedded system that utilizes a Bluetooth module for wireless communication. The goal is to create a basic yet functional prototype that demonstrates how Bluetooth can facilitate remote data exchange between devices. By integrating a Bluetooth module with a microcontroller, we can enable seamless and efficient communication over short distances, paving the way for various practical applications such as remote sensing, home automation, and wireless data transfer.

# Overview
This project involves creating a simple embedded system using an HC-05 Bluetooth module, a VSD Squadron Mini microcontroller, and a 16x2 LCD display. The system receives messages via the Bluetooth module and VSD Squadron Mini processes the incoming data and updates the LCD in real-time. This project serves as an educational tool for understanding the basics of wireless communication and embedded system design, highlighting the ease of integrating different components to achieve a functional and practical solution.

# Components Required
•	HC05 Bluetooth module
•	16x2 LCD Module
•	VSD Squadron Mini
•	Jumper Cables
•	Breadboard
•	Message Transmission device



# Circuit Connection
 ![pin diagram](https://github.com/anshusrinivas/Curious/assets/156586065/b6dab56a-855f-42ad-ab48-a7e9fbf816bb)



# Pin Connection Table
LCD module pin table

![image](https://github.com/anshusrinivas/Curious/assets/156586065/cf746de7-786b-4bc3-899e-3118145b7f15)

Bluetooth pin table

![image](https://github.com/anshusrinivas/Curious/assets/156586065/dbe894bf-1bd8-4f92-a75f-e7ab313e20a5)


Potentiometer connections

![image](https://github.com/anshusrinivas/Curious/assets/156586065/3e4ad1a1-efa7-4600-9165-087ebd18ab5b)


VSD Squadron mini code
```
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
```

Arduino Code
```
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
```

https://github.com/anshusrinivas/Curious/assets/156586065/af056711-db7a-455d-96e9-50c8b261553a




https://github.com/anshusrinivas/Curious/assets/156586065/1c3925f0-aac9-4bee-85f9-dbd9a43ca737

