
/*
  Ultrasonic/LED Array. LED turns on when the corresponding ultrasonic sensor destects an object within range
  by L. Savage, February 2023
*/

// Neo Pixel setup
#include <Adafruit_NeoPixel.h>
#include "ultrasonicClass.h" 
#define N_LEDS 4

// Define Pins
const int ledPin = 3;
Ultrasonic* ultrasonicSensor0 = new Ultrasonic(4,5);// (Trig PIN,Echo PIN)
Ultrasonic* ultrasonicSensor1 = new Ultrasonic(6,7);// (Trig PIN,Echo PIN)
Ultrasonic* ultrasonicSensor2 = new Ultrasonic(8,9);// (Trig PIN,Echo PIN)
Ultrasonic* ultrasonicSensor3 = new Ultrasonic(10,11);// (Trig PIN,Echo PIN)  

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, ledPin, NEO_GRB + NEO_KHZ800);

//Range variable in cm. LEDs turn on when object is within range of sensor
int objectRange = 20;   


//Define pins as input or output, start serial
void setup() {
  Serial.begin(9600);
  strip.begin();
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  
checkDistance(ultrasonicSensor0, 0);
checkDistance(ultrasonicSensor1, 1);
checkDistance(ultrasonicSensor2, 2);
checkDistance(ultrasonicSensor3, 3);   
  
}

void checkDistance(Ultrasonic* UltrasonicSensor, int i){
  
  int distance = UltrasonicSensor->Ranging(CM);
  
//  Serial.print(distance); 
//  Serial.println(" cm" );
//  delay(100);

   if (distance >= objectRange){
    setLEDstrip(strip.Color(0, 0, 0));
  }

  else if (distance < objectRange) {
     setSingleLEDcolor(i, strip.Color(10, 10, 10));   //figure out how to implement i
  }

  else {
    setLEDstrip(strip.Color(0, 0, 0));
  }
  
}


// Sets all LEDs one color
static void setLEDstrip(uint32_t c) {
     for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
    }
}


// Sets single LED one color. i is the LED number
static void setSingleLEDcolor(int i, uint32_t c) {
  strip.setPixelColor(i, c);
  strip.show();
}

