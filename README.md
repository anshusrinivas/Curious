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
![VSDSquadron mini](https://github.com/anshusrinivas/Curious/assets/156586065/ad57b387-5987-481b-a9b9-3e11fdf405fa)




# Pin Tables

## VSD Squadron mini to HC-05 Bluetooth Module

| VSD Squadron mini Pin | HC-05 Bluetooth Module Pin | Function  |
|-----------------------|----------------------------|-----------|
| PD5                   | Bluetooth TX               | INPUT     |
| PD6                   | Bluetooth RX               | OUTPUT    |
| 5V                    | Bluetooth VCC              | POWER     |
| GND                   | Bluetooth GND              | POWER     |

## VSD Squadron mini to Arduino

| VSD Squadron mini Pin | Arduino Pin | Function |
|-----------------------|-------------|----------|
| PC2                   | SCL         | INOUT    |
| PC1                   | SDA         | INOUT    |

## Arduino to LCD

| Arduino Pin | LCD Pin         | Function |
|-------------|-----------------|----------|
| GND         | VSS             | POWER    |
| 5V          | VCC             | POWER    |
| D12         | Register Select | OUTPUT   |
| GND         | Read / Write    | OUTPUT   |
| D11         | Enable          | OUTPUT   |
| D5          | DB4             | OUTPUT   |
| D4          | DB5             | OUTPUT   |
| D3          | DB6             | OUTPUT   |
| D2          | DB7             | OUTPUT   |
| GND         | Backlight(-)    | POWER    |
| VCC         | Backlight(+)    | POWER    |

## Potentiometer Connections

| LCD Pin       | Potentiometer Pin   |
|---------------|---------------------|
| VCC           | Terminal 1          |
| LCD Contrast  | Terminal 2 (Wiper)  |
| GND           | Terminal 3          |



## VSD Squadron mini code
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
  delay(500);
  Serial.println("initialized");
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()){
  String inp=Serial.readString();
  if(inp!='\0'){
  //Serial.println(inp);
  //Serial.println("Write \n");
  for(int i=0;i<16;i++)
  {
    deviceWriteOneByte(inp[i]);
    delay(5);  
  }
  //Serial.println("Write Finish!\r\n");
  }
 }
}

void deviceWriteOneByte(uint8_t data)
{
  Wire.beginTransmission(0x50);  //transmit to device AT24C02  
  Wire.write(data);
  Wire.endTransmission();
}
```

## Arduino Code
```
#include <Wire.h>
#include<LiquidCrystal.h>
#include<string.h>

#define SLAVE_ADDRESS 0x50
LiquidCrystal lcd( 12,11,5,4,3,2);
String inp;
int a;
void setup() {
  Wire.begin(SLAVE_ADDRESS); // Initialize the I2C bus as slave
  Wire.onReceive(receiveEvent); // Register a function to be called when data is received
  //Wire.onRequest(requestEvent); // Register a function to be called when data is requested
  lcd.begin(16,2);
  Serial.begin(9600); // Initialize serial communication for debugging
  lcd.clear();
  lcd.print("Initializing");
  delay(1000);
  lcd.clear();
  lcd.print("Initialized");
  delay(1000);
  lcd.clear();
}

void receiveEvent(int howMany) {
  inp="";
  a++;
  while (Wire.available()) {
    char c = Wire.read();
    if(c!='\0'){      
      inp+=c;      
    }
    if(a==17){
      lcd.clear();
      a=1;
    }
    //Serial.println(a);
    //lcd.print(c);    
    //Serial.print(c); // Print the received data to the serial monitor
  }
  print_lcd(); 
}

void print_lcd(){
  
  //Serial.println(inp);
  lcd.print(inp);
  
}

void loop() {
  
} 

```

https://github.com/anshusrinivas/Curious/assets/156586065/af056711-db7a-455d-96e9-50c8b261553a




https://github.com/anshusrinivas/Curious/assets/156586065/1c3925f0-aac9-4bee-85f9-dbd9a43ca737

