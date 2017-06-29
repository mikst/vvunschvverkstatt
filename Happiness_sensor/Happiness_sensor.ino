#include <CapacitiveSensor.h>

#include <Adafruit_NeoPixel.h>

//#include <Firmata.h>


#define PIN 6
#define PIXEL_COUNT 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN, NEO_GRB + NEO_KHZ800);


//---------------------------------


// Input pin configuration
int distancePin=A0;
int handPin=A2;
int LDRPin=A1;

// capacitive sensor
//CapacitiveSensor   cs_7_8 = CapacitiveSensor(7,8);  


int LightVal;
int DistVal;
int CapVal;
int handVal;

int happinessVal;


  int Red;
  int Green;
  int Blue;

  int pixelPos;
  int pixelNum;

  int inc=1;
  int cnt;

  unsigned long previousMillis = 0;        // will store last time LED was updated
  
  long delaytime = 10; 



void setup() {

    Serial.begin(9600);
    Serial1.begin(57600);
 // Firmata.begin(Serial1);
 
    // neopixel LED stripe related setup
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'

    pixelNum=PIXEL_COUNT;

    //Serial.println("hello");

    // setup capacitive sensing
   // cs_7_8.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example


}

void loop() {
    //--------------------------------
    // read all the sensors
 
    
    LightVal=analogRead(LDRPin);    
    DistVal=analogRead(distancePin);
    handVal =analogRead(handPin);
    //handVal=1023-handVal;
    LightVal=1023-LightVal;

   
     
    
    //--------------------------------
    // capTouch
  // long capVal =  cs_7_8.capacitiveSensor(30);

                        // print sensor output 1
  
    //--------------------------------
  // calculate the Happiness
    

//DistVal=map(DistVal,0,700,0,255);
//LightVal=map(LightVal,800,600,0,255);
//handVal=map(handVal,200,800,0,255);

happinessVal=(DistVal)+ (LightVal-400) + handVal;

happinessVal=constrain(happinessVal,0,1023);
Serial.println(happinessVal);
Serial1.println(happinessVal);
//cnt++;
//cnt=cnt%1023;

//Firmata.sendAnalog(1, happinessVal);

delaytime= map (happinessVal,0,1023,60,2);


 //--------------------------------
    // control LED

 
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= delaytime) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;



 strip.clear();

 for(int i=0; i<10; i++){
     // strip.setPixelColor(pixelPos+i, rainbow(happinessVal));
      strip.setPixelColor(pixelPos+i, Wheel(((pixelPos+i) * 256 / pixelNum) & 255));      
 }
strip.show();
      if(pixelPos>pixelNum) inc=-1;
      if(pixelPos<0) inc=1;
      pixelPos=pixelPos+inc;
     // if(pixelPos>pixelNum) pixelPos=0;
      
      if(pixelPos>pixelNum) inc=-1;
      if(pixelPos<0) inc=1;
  }
  
delay(10);
}





uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    
  }
  WheelPos -= 170;
  
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
