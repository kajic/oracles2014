// Amadeus 2 by daniel@phu.se
// blink neopixels with a spectrum analyzer
// circuit based on http://nuewire.com/wp-content/uploads/2011/07/schem1.png
// pinout in code for a adafruit trinket 
#include <Adafruit_NeoPixel.h>

#define PIN 1
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int analogPin = 1;
int strobePin = 0;
int resetPin = 3;
int spectrumValue[7];

void setup()
{
  
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  analogReference, DEFAULT;
  
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop()
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(strobePin, LOW);
    delayMicroseconds(30); //to allow the output to settle
    spectrumValue[i] = analogRead(analogPin);
    if (spectrumValue[i] < 70)
    {
     strip.setPixelColor(i, 0);
     strip.setPixelColor(14-i, 0);
    }
    else
    {
      strip.setPixelColor(i, spectrumValue[i]*16000-70*16000);
      strip.setPixelColor(14-i, spectrumValue[i]/3,0,spectrumValue[i-1]/2);
      
    }
    
    
    digitalWrite(strobePin, HIGH);
  }
    strip.show();
    delay(20);
  
}
      
