#include <Adafruit_NeoPixel.h>
#define PINLED           6

#define NUMPIXELS      7
#define beta 4090 //beta del termistor

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINLED, NEO_GRB + NEO_KHZ800);
int delayval = 25; // delay for half a second


///////////////////variables de luis /////////////////////
const int groundpin = 5;             // analog input pin 5 -- ground
const int powerpin = 7;              // analog input pin 7 -- voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A4;                  // z-axis (only on 3-axis models)
////////////////////////////////////////////////////////////////////////

void setup() {
  pixels.begin(); // This initializes the NeoPixel library;
  Serial.begin(9600);
  
  
  ////////////////////////// set de luis para xbee//////////////
  // Provide ground and power by using the analog inputs as normal
  // digital pins.  This makes it possible to directly connect the
  // breakout board to the Arduino.  If you use the normal 5V and
  // GND pins on the Arduino, you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW); 
  digitalWrite(powerpin, HIGH);
  /////////////////////////////////////////////////////////////////
}

int temp=25;
int temp_anterior=0;
float tempC=0;

int a=0;
int red=10;
int green=245;
int blue=0;

void loop() {
 
  
  
  ////////////////////////impresiones seriales de luis
  // print the sensor values:
  Serial.print("x:");
  Serial.print(analogRead(xpin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print("y:");
  Serial.print(analogRead(ypin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print("z:");
  Serial.print(analogRead(zpin));
  Serial.println();
  // delay before next reading:
  delay(100);
  ///////////////////////////////////////////////////////////////
  
  temp_anterior=temp;
  temp= analogRead (1); /// cambie el pin de lectura de grabriel de 0 a 1
  RGB(temp,temp_anterior,tempC,red,green,blue);

  //Serial.println(temp);
  for(int i=0;i<NUMPIXELS;i++){
    
    pixels.setPixelColor(i, pixels.Color(red,green,blue));
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  delay(50);
}

void RGB(int &temp,int &temp_anterior,float &tempC, int &red,int &green, int &blue){
  
  a =1023 - temp;
  tempC = map(temp, 0, 1023, 20, 40);
  temp = map(temp, 0, 1023, 0, 255);
  
  if(temp<25){
  red=0;
  green=255;
  }
  if(temp>=25 && temp <50){
    red=25;
    green=225;
  }
  if(temp>=50 && temp <75){
    red=50;
    green=200;
  }
  if(temp>=75 && temp <100){
    red=75;
    green=175;
  }
  if(temp>=100 && temp <125){
    red=100;
    green=150;
  }  
    if(temp>=125 && temp <150){
    red=125;
    green=125;
  }
  if(temp>=150 && temp <175){
    red=150;
    green=100;
  }
if(temp>=175 && temp <200){
    red=175;
    green=75;
  }
  
  if(temp>=200 && temp <175){
    red=200;
    green=50;
  }
if(temp>=225 && temp <200){
    red=225;
    green=25;
  }
  
  if(temp>=225 && temp <200){
    red=250;
    green=15;
  }
if(temp>=225 && temp <255){
    red=255;
    green=0;
  }
  /*
  
  if (temp>=temp_anterior){
    if(red<250){
      red=red+5;
      if(green>0){
      green=green-5;
      }else{
      green=0;
      }
    }else{
      red=255;  
    }
    
  }else{
      
    if(red>0){
    red=red-5;
    if(green<255){
      green=green+5;
      }else{
      green=255;
      }
    }else{
    red=0;
    }
    
  }*/
}
