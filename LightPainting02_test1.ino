#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERNAL
#include <FastLED.h>

#define DATA_PIN    5
const int BRIGHTNESS_PIN = 15;
#define LED_TYPE    WS2812B
#define COLOR_ORDER BRG
#define NUM_LEDS    399
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          0
#define FRAMES_PER_SECOND  120
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 10 

long frameCount = 0;
 
int overallDelay = 10;
int overallTime = 1000; //time in ms * delay (ex 1000 would be 10 seconds if our overall delay is 10)

int aTime = overallTime;
int bTime = overallTime;
int cTime = overallTime/2;
int dTime = overallTime;
int eTime = overallTime;
int fTime = overallTime;
int gTime = overallTime;

int bColor = 0;

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  delay(3000); // 3 second delay for recovery
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }  
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  pinMode(BRIGHTNESS_PIN, INPUT);
  }



void loop() {
  
  FastLED.clear();
 
//stuff for averaging readings from the pot
// subtract the last reading:
//  total = total - readings[readIndex];
//  // read from the sensor:
//  readings[readIndex] = analogRead(BRIGHTNESS_PIN);
//  // add the reading to the total:
//  total = total + readings[readIndex];
//  // advance to the next position in the array:
//  readIndex = readIndex + 1;
//
//  // if we're at the end of the array...
//  if (readIndex >= numReadings) {
//    // ...wrap around to the beginning:
//    readIndex = 0;
//  }
//
//  // calculate the average:
//  average = total / numReadings;
  
  int mappedValue = map(analogRead(BRIGHTNESS_PIN), 0, 1023, 0, 255); //map knob to bightness range
  //overallTime = mappedValue;
  
  Serial.println(mappedValue);
  FastLED.setBrightness(constrain(mappedValue, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
  frameCount++;
  frameCount % overallTime; //overall delay is 10, so this number * 10 is our timebase
  
  for(int i=0;i<49;i++){    //A
    int aCount = frameCount % aTime;
    int aHue = map(aCount, 0, aTime, 0, 255);
    leds[i] = CHSV(aHue+(i*4),255,255);
  }
   for(int i=49;i<115;i++){    //B
    int bCount = frameCount % bTime;
    int bHue = map(bCount, 0, bTime, 0, 255);
    leds[i] = CHSV(bHue+(i*1),255,255);
  }
    for(int i=116;i<167;i++){    //C
    int cCount = frameCount % cTime;
    int cHue = map(cCount, 0, cTime, 0, 255);
    leds[i] = CHSV(cHue+(i*1),255,255);
  }
  for(int i=168;i<200;i++){    //D
    int dCount = frameCount % dTime;
    int dHue = map(dCount, 0, dTime, 0, 255);
    leds[i] = CHSV(dHue+(i*3),255,255);
  }
   for(int i=201;i<280;i++){    //E
    int eCount = frameCount % eTime;
    int eHue = map(eCount, 0, eTime, 0, 255);
    leds[i] = CHSV(eHue+(i*2),255,255);
  }
  for(int i=281;i<320;i++){    //F
    int fCount = frameCount % fTime;
    int fHue = map(fCount, 0, fTime, 0, 255);
    leds[i] = CHSV(fHue+(i*1),255,255);
  }
  for(int i=321;i<399;i++){    //G
    int gCount = frameCount % gTime;
    int gHue = map(gCount, 0, gTime, 0, 255);
    leds[i] = CHSV(gHue+(i*1),255,255);
  }
  
  
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  delay(overallDelay);
}
