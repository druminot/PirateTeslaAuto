  //Libraries for LoRa


  
#include <SPI.h>
#include <LoRa.h>
#include "String.h"

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 866E6

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

String LoRaData;

void setup() { 
  //initialize Serial Monitor


    pinMode(16,OUTPUT);
     pinMode(17,OUTPUT);
        pinMode(13,OUTPUT);
           pinMode(2,OUTPUT);
           
  Serial.begin(57600);

 
    
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  
  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LORA RECEIVER ");
  display.display();

  Serial.println("LoRa Receiver Test");
  
  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.println("LoRa Initializing OK!");
  display.display();  
}

void loop() {



  

  //try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //received a packet
    

    //read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      
int End = LoRaData.indexOf("\n");
LoRaData[End]='A';
int StartX = LoRaData.indexOf("X");
int EndX = LoRaData.indexOf("\n");
LoRaData[EndX]='A';
int StartY = LoRaData.indexOf("Y");
int EndY = LoRaData.indexOf("\n");
LoRaData[EndY]='A';
int StartZ = LoRaData.indexOf("Z");
int EndZ = LoRaData.indexOf("\n");
LoRaData[EndZ]='A';

String X = LoRaData.substring(StartX+1, EndX);
String Y = LoRaData.substring(StartY+1, EndY);
String Z = LoRaData.substring(StartZ+1, EndZ);

float X1 =X.toFloat();
float Y1 = Y.toFloat();
float Z1 = Z.toFloat();
Serial.println(X1);



  


if(X1>8 && Z1<4){
  Serial.println("adelante");
  digitalWrite(16,1);
  }
  else{digitalWrite(16,0);}
  
  if(X1<-8 && Z1<4){
  Serial.println("atras");
    digitalWrite(13,1);
  }
    else{digitalWrite(13,0);}
 
  if(Y1>8 && Z1<4){
  Serial.println("izquierda");
  digitalWrite(17,1);
  }
    else{digitalWrite(17,0);}
    
  if(Y1<-8 && Z1<4){
  Serial.println("Derecha");
  digitalWrite(2,1);
  }
    else{digitalWrite(2,0);}

     
    

      

      
    //  mySerial.write(LoRaData);
    }

    //print RSSI of packet
    int rssi = LoRa.packetRssi();
      
    Serial.println(" ");

   // Dsiplay information
   display.clearDisplay();
   display.setCursor(0,0);
   display.print("LORA RECEIVER");
   display.setCursor(0,20);
   display.print("Received packet:");
   display.setCursor(0,30);
   display.print(LoRaData);
   display.setCursor(0,50);
  // display.print("RSSI:");
   //display.setCursor(30,50);
   //display.print(rssi);
   display.display();   
  }
}
