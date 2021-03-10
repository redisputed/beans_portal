#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define NUM_LEDS 241
#define PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

class Ring
{
private:
  int startpos;
  int endpos;

public:
  Ring(int startval, int endval)
  {
    this->startpos = startval;
    this->endpos = endval;
  }
  void allOn()
  {
    for (int i = startpos; i < endpos; i++)
    {
      strip.setPixelColor(i, 255, 255, 255);
    }
    strip.show();
  }
  void allOff()
  {
    for (int i = startpos; i < endpos; i++)
    {
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
  }
  void allRed()
  {
    for (int i = startpos; i < endpos; i++)
    {
      strip.setPixelColor(i, 255, 0, 0);
    }
    strip.show();
  }
  void allGreen()
  {
    for (int i = startpos; i < endpos; i++)
    {
      strip.setPixelColor(i, 0, 255, 0);
    }
    strip.show();
  }
  void allBlue()
  {
    for (int i = startpos; i < endpos; i++)
    {
      strip.setPixelColor(i, 0, 0, 255);
    }
    strip.show();
  }
  void allRGB(int r, int g, int b)
  {
    for (int i = startpos; i < endpos; i++)
    {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
  }
};

class RingMaster
{
private:
  int id;
  static const int numRings = 9;
  Ring r0 = Ring(0, 60);
  Ring r1 = Ring(60, 108);
  Ring r2 = Ring(108, 148);
  Ring r3 = Ring(148, 180);
  Ring r4 = Ring(180, 204);
  Ring r5 = Ring(204, 220);
  Ring r6 = Ring(220, 232);
  Ring r7 = Ring(232, 240);
  Ring r8 = Ring(240, 241);
  Ring rings[numRings] = {r0, r1, r2, r3, r4, r5, r6, r7, r8};
  Ring ringsRev[numRings] = {r8, r7, r6, r5, r4, r3, r2, r1, r0};

public:
  RingMaster(int name) : id(name)
  {
  }

  void setAll(byte red, byte green, byte blue)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      strip.setPixelColor(i, red, green, blue);
    }
    strip.show();
  }

  void outsideIn(int delayTime)
  {
    for (int i = 0; i < numRings; i++)
    {
      rings[i].allOn();
      delay(delayTime);
    }
  }

  void outsideInOff(int delayTime)
  {
    for (int i = 0; i < numRings; i++)
    {
      rings[i].allOff();
      delay(delayTime);
    }
  }

  void insideOut(int delayTime)
  {
    for (int i = 0; i < numRings; i++)
    {
      ringsRev[i].allOn();
      delay(delayTime);
    }
  }

  void insideOutOff(int delayTime)
  {
    for (int i = 0; i < numRings; i++)
    {
      ringsRev[i].allOff();
      delay(delayTime);
    }
  }

  void ripplesIn(int delayTime)
  {
    for (int i = 0; i < numRings; i++)
    {
      rings[i].allOn();
      delay(delayTime);
      rings[i].allOff();
    }
  }
};

RingMaster light = RingMaster(1);

void setup()
{
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(3);
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  int flash = 10;
  light.insideOut(flash);
  light.insideOutOff(flash);
  light.ripplesIn(flash);
}
