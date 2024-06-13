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


## Fault Injection
It is a way to test how strong an embedded system is against problems or attacks. We intentionally create problems in the system to see how it handles them. This helps us figure out if the system can stand up to real-world issues and keep working properly.
Purpose:                                                                                                                                                                                                           
It helps find weak spots and problems in how the system is built and set up, especially in things that need strong security.

## Methods of Fault Injection
Voltage Glitching:                                                                                                                                                                                                 
•	Description: Giving quick bursts or drops of electricity to mess with the microcontroller.
•	Effect: This can make the microcontroller do things wrong or act strangely.

Clock Glitching:                                                                                                                                                                                                    
•	Description: Changing the signal that controls the microcontroller's timing.
•	Effect: This might make the microcontroller not work correctly because its timing is off.

Electromagnetic Interference (EMI):                                                                                                                                                                                 
•	Description: Outside signals messing with how the microcontroller works.
•	Effect: This can make the microcontroller behave weirdly or do things wrong.

Faulty Inputs:                                                                                                                                                                                                      
•	Description: Giving the microcontroller inputs it wasn't expecting.
•	Effect: This can make the system malfunction because it's getting data or signals it doesn't understand.

Code Injection:                                                                                                                                                                                                     
•	Description: Sneaking harmful instructions into the microcontroller's memory or operations.
•	Effect: This can let someone access the system without permission, change data, or even stop the system from working.

Peripheral Fault Injection:                                                                                                                                                                                        
•	Description: Messing with devices connected to the microcontroller.
•	Effect: This can make those devices act up, causing communication problems or making them not work right, which can mess up how the whole system functions.

JTAG/SWD Manipulation:                                                                                                                                                                                              
•	Description: Tampering with the microcontroller's internal testing systems.
•	Effect: This can make it hard to figure out what's wrong with the system and open up a security risk by letting unauthorized people control the microcontroller's inner workings.

Injection via System Reset:                                                                                                                                                                                        
•	Description: Messing with how the microcontroller starts up or resets.
•	Effect: This can make the system unstable, lose data, or behave strangely during startup, and create vulnerabilities like bypassing security measures or messing with how the system boots up safely.

Radiation-induced Single Event Effects (SEE):                                                                                                                                                                      
•	Description: Exposing the microcontroller to radiation.
•	Effect: This can cause temporary faults in how the system works, making it act strangely or mess up data, especially in places with lots of radiation like aerospace or high-altitude areas.

Quantum-based Fault Injection:                                                                                                                                                                                     
•	Description: Using the strange behaviour of quantum physics to create problems in the microcontroller.
•	Effect: This can cause unpredictable errors, flip bits, or corrupt data in the microcontroller's memory or logic circuits, making the system less reliable and secure, especially in high-performance or quantum computing applications.

## Importance

Security Evaluation:                                                                                                                                                                                                
•	Definition: Examines the system to find weaknesses that hackers could use to break in.
•	Importance: Helps prevent unauthorized access or attacks on the system.

Reliability Assessment:                                                                                                                                                                                            
•	Definition: Tests how well the system performs under different types of faults.
•	Importance: Ensures the system works correctly even when things go wrong.

Compliance Testing:                                                                                                                                                                                                
• Definition: Checks if the system meets industry rules and standards, especially in safety-focused areas.
•	Importance: Ensures the system is legal and safe to use.

Risk Mitigation:                                                                                                                                                                                                    
•	Definition: Identifies and reduces potential risks before the system is used.
•	Importance: Helps prevent system failures or security breaches before they happen, saving time and money.

## Fault Injection in Bluetooth Messenger

1)	Disrupting I2C Communication protocol Clock

| Causes                        | Prevention                           |
|-------------------------------|--------------------------------------|
| Wire Discontinuity            | Use proper wires                     |
| Loose Connection              | Ensure Intact connection             |
| Electromagnetic Interference  | EM shielding (e.g., Faraday Cage)    |
| Multiple Master Declaration   | Ensure Proper Master Declaration     |
| Unstable Oscillator           | Use Stable Oscillator                |


2)	Unstable Power supply to HC05

| Causes                        | Prevention                           |
|-------------------------------|--------------------------------------|
| Improper wires                | Use proper wires                     |
| Loose Connection              | Ensure intact connection             |
| Electromagnetic Interference  | EM shielding (e.g., Faraday Cage)    |


3)! LCD Clear
No use of variable “a” to keep track of characters displayed on LCD.
```
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
    
  }
  print_lcd(); 
}
```


4)	Use of lcd.clear()  without condition
```
void receiveEvent(int howMany) {
  inp="";
  while (Wire.available()) {
    char c = Wire.read();
    if(c!='\0'){      
      inp+=c;      
    }

  lcd.clear();
  }
  print_lcd(); 
}
```
