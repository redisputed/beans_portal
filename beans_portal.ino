#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 2


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(241, PIN, NEO_GRB + NEO_KHZ800);

class Ring{
  private:
  int startpos;
  int endpos;
  public:
   Ring(int startval, int endval){
      this->startpos = startval;
      this->endpos = endval;
    }
    void allOn(){
      for( int i = startpos; i < endpos; i++){
        strip.setPixelColor(i, 255,255,255);
      }
      strip.show();
    }
    void allOff(){
      for(int i=startpos; i < endpos; i++){
        strip.setPixelColor(i, 0,0,0);
      }
      strip.show();
    }
    void allRed(){
      for(int i=startpos; i<endpos; i++){
        strip.setPixelColor(i, 255,0,0);
      }
      strip.show();
    }
    void allGreen(){
      for(int i=startpos; i<endpos; i++){
        strip.setPixelColor(i, 0,255,0);
      }
      strip.show();
    }
    void allBlue(){
      for(int i=startpos; i<endpos; i++){
        strip.setPixelColor(i, 0,0,255);
      }
      strip.show();
    }
    void allRGB(int r, int g, int b){
      for(int i=startpos; i<endpos; i++){
        strip.setPixelColor(i, r,g,b);
      }
      strip.show();
    }
};

class RingMaster{
  private:
  int id;
  Ring r0 = Ring(0,60);
  Ring r1 = Ring(60,108);
  Ring r2 = Ring(108,148);
  Ring r3 = Ring(148,180);
  Ring r4 = Ring(180,204);
  Ring r5 = Ring(204,220);
  Ring r6 = Ring(220,232);
  Ring r7 = Ring(232,240);
  Ring r8 = Ring(240,241);
  Ring rings[9] = {r0, r1, r2, r3, r4, r5, r6, r7, r8};
  Ring ringsRev[9] = {r8, r7, r6, r5, r4, r3, r2, r1, r0};


  public:
  RingMaster(int name){
    this->id = name;
  }

  void outsideIn(int delayTime){
    for( int i = 0; i < (sizeof(rings)-1); i++){
      rings[i].allOn();
      delay(delayTime);
    }
  }

  void outsideInOff(int delayTime){
    for( int i = 0; i < (sizeof(rings)-1); i++){
      rings[i].allOff();
      delay(delayTime);
    }
  }

  void insideOut(int delayTime){
    for( int i = 0; i < (sizeof(ringsRev)-1); i++){
      ringsRev[i].allOn();
      delay(delayTime);
    }
  }

  void insideOutOff(int delayTime){
    for( int i = 0; i < (sizeof(ringsRev)-1); i++){
      ringsRev[i].allOff();
      delay(delayTime);
    }
  }
};

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(3);
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  RingMaster light = RingMaster(1);
  light.outsideIn(50);
  light.outsideInOff(50);
  light.insideOut(50);
  light.insideOutOff(50);

  }
