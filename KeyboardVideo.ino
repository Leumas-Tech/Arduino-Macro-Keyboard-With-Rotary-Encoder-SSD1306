//Include libraries for SSD1306 12C

#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <SPI.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include<Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>



//Include Keyboard Library. 

#include <Keyboard.h>
#include <KeyboardLayout.h>



//Define our rotary encoder inputs

#define CLK 16
#define DT 4
#define SW 14


//Counter and the last state of our variables from the rotary encoder
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir="";
unsigned long lastButtonPress = 0;


//Screen Inputs
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);






void setup() {
if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  
}
delay(2000);

Keyboard.begin();

pinMode(CLK,INPUT);
pinMode(DT, INPUT);
pinMode(SW, INPUT_PULLUP);

Serial.begin(9600);

lastStateCLK = digitalRead(CLK);

}






void loop() {
  
  currentStateCLK = digitalRead(CLK);

if(currentStateCLK != lastStateCLK && currentStateCLK ==1){
  if(digitalRead(DT) != currentStateCLK) {
    counter++;
    currentDir = "CW";
  } else {
    counter--;
    currentDir = "CCW";
  }


  // Always make these one less than the amount of items in your arrays
  if(counter > 5 || counter < -5){
    counter = 0;
  }
  if(counter < 0){
    counter = 5;
  }

  Serial.print("Direction: ");
    Serial.print(currentDir);
      Serial.print(" | Counter: ");
        Serial.println(counter);




//Array where we title all of our links so we can see them on the OLED
        String nameArray [6] = {
          "Facebook Link", "My Wordpress Password", "Link 3", "Link 4","For Loops", "Github Link" 
        };

        
//commands
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("Press to print");

//Display browser counter
display.setTextSize(2);
display.setCursor(50,25);
display.print(counter);


//Display browser page
display.setTextSize(1);
display.setCursor(0,55);
display.println(nameArray[counter]);
display.display();
}

lastStateCLK = currentStateCLK;

int btnState = digitalRead(SW);


// If our rotary encoder is pressed
if(btnState == LOW){
  if(millis() - lastButtonPress > 50){
    
        String commandArray[6] = {
          "https://facebook.com", "dsikfabdsibfuewvfbalif", "Link or Text 3", "Link or Text 4", "for(let i = 0; i < variable; i++){}" , "ljhgdfsblkjfbdslibflasiud"
        };

    String WhatToPrint = commandArray[counter];
    Keyboard.print(WhatToPrint);

//printing
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("Printing !");

display.setTextSize(3);
display.setCursor(50,25);
display.print(counter);

display.setTextSize(1);
display.setCursor(0,55);
display.print("Please be patient :)");

display.display();

delay(1000);

//printed
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(5,0);
display.print("Printed !");

display.setTextSize(3);
display.setCursor(50,25);
display.print(counter);

display.setTextSize(1);
display.setCursor(20,55);
display.print("Thx 4 Waiting :)");

display.display();
    
  }
  lastButtonPress = millis();
}
delay(1);
}
