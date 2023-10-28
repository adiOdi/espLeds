#include <Adafruit_NeoPixel.h>
#define LED1 0
int n = 0;
float x = 0;
float y = 0;
int b = 0;
int t = 0;
#define LEN 76
int brights[LEN];

Adafruit_NeoPixel strip(LEN, LED1, NEO_GRB + NEO_KHZ400);

void setupStrip(){
  strip.begin();
  strip.clear();
  strip.show();
  strip.setBrightness(255);
}
float sinus(float x){
  return sin(TWO_PI * x / LEN + HALF_PI);
}
void drawStrip(int * brights) {
  if(b<255){
    for (int i = 0; i < LEN; i++) {
      strip.setPixelColor(i, 0, brights[i], 0);
    }
  } else if (b<510){
    for (int i = 0; i < LEN; i++) {
      strip.setPixelColor(i, 0, (int)(brights[i]/2), (int)(brights[i]/2));
    }
  } else {
    for (int i = 0; i < LEN; i++) {
      strip.setPixelColor(i, (int)(brights[i]/3), (int)(brights[i]/3), (int)(brights[i]/3));
    }
  }
  
  strip.show();
}
void state(float t, int brightness, int n, float x, float y) {
  for (int i = 0; i < LEN; i++) {
    brights[i] = (int)((sinus(n * i + x * t) * sinus(y * t) + 1) / 2 * brightness);
  }
}
void draw() {
  if(x!=0 || y!=0)t++;
  if(t==4294967293) {t=0;}
  state(t/8, b, n, x, y);
  drawStrip(brights);
}