#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


#define PATH_ZERO 24 // strip0
#define PATH_ONE 37 // strip1
#define PATH_TWO 35 //strip2
#define PATH_THREE 2 //strip3
#define PATH_FOUR 46 //strip4
#define PATH_FIVE 45//strip5
#define PATH_SIX 13//strip6
#define PATH_SEVEN 12//strip7
#define PATH_EIGHT 47//strip8
#define PATH_NINE 48//strip9
#define PATH_TEN 41 // strip10
#define PATH_ELEVEN 3 // strip11
#define BRIGHTNESS 50


const int H0 = 22;
const int H1 = 30;
const int H2 = 31;
const int H3 = 32;
const int H4 = 33;
const int H5 = 34;
const int H6 = 36;
const int H7 = 39;
const int H8 = 38;
const int H9 = 42;
const int H10 = 40;
const int H11 = 43;
const int H12 = 44;

const int buttonPin = 51;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int warp = 0;



// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(9, PATH_ZERO, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(9, PATH_ONE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(6, PATH_TWO, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(6, PATH_THREE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(9, PATH_FOUR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(9, PATH_FIVE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(8, PATH_SIX, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(8, PATH_SEVEN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(6, PATH_EIGHT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(6, PATH_NINE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(8, PATH_TEN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip11 = Adafruit_NeoPixel(8, PATH_ELEVEN, NEO_GRB + NEO_KHZ800);



int state; // 0 close - 1 open wwitch
int incomingByte = 0;
int mode = 0;
int currentNode = 0;


void setup() {
  pinMode(buttonPin, INPUT);
  setupMagnets();
  setupLights();
  Serial.begin(9600);
}


void setupLights() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip0.begin();
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  strip6.begin();
  strip7.begin();
  strip8.begin();
  strip9.begin();
  strip10.begin();
  strip11.begin();

  strip0.setBrightness(BRIGHTNESS);
  strip1.setBrightness(BRIGHTNESS);
  strip2.setBrightness(BRIGHTNESS);
  strip3.setBrightness(BRIGHTNESS);
  strip4.setBrightness(BRIGHTNESS);
  strip5.setBrightness(BRIGHTNESS);
  strip6.setBrightness(BRIGHTNESS);
  strip7.setBrightness(BRIGHTNESS);
  strip8.setBrightness(BRIGHTNESS);
  strip9.setBrightness(BRIGHTNESS);
  strip10.setBrightness(BRIGHTNESS);
  strip11.setBrightness(BRIGHTNESS);

  strip0.show();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip7.show();
  strip8.show();
  strip9.show();
  strip10.show();
  strip11.show();
}


void setupMagnets() {
  pinMode(H0, INPUT_PULLUP);
  pinMode(H1, INPUT_PULLUP);
  pinMode(H2, INPUT_PULLUP);
  pinMode(H3, INPUT_PULLUP);
  pinMode(H4, INPUT_PULLUP);
  pinMode(H5, INPUT_PULLUP);
  pinMode(H6, INPUT_PULLUP);
  pinMode(H7, INPUT_PULLUP);
  pinMode(H8, INPUT_PULLUP);
  pinMode(H9, INPUT_PULLUP);
  pinMode(H10, INPUT_PULLUP);
  pinMode(H11, INPUT_PULLUP);
  pinMode(H12, INPUT_PULLUP);
}


void loop() {
  updateButton();
  if (warp) {
    buttonMode();
    delay(10);
    return;
  }
  if (mode == 0) {
    startMode();
  }
  else if (mode == 1) {
    playMode();
  }
  else if (mode == 2) {
    selectMode();
  }
  delay(18);
}

void buttonMode() {
  int changed = false;
  lightAll();
  if (digitalRead(H0) != 0) {
    currentNode = 0;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H1) != 0) {
    currentNode = 1;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H2) != 0) {
    currentNode = 2;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H3) != 0) {
    currentNode = 3;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H4) != 0) {
    currentNode = 4;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H5) != 0) {
    currentNode = 5;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H6) != 0) {
    currentNode = 6;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H7) != 0) {
    currentNode = 7;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H8) != 0) {
    currentNode = 8;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H9) != 0) {
    currentNode = 9;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H10) != 0) {
    currentNode = 10;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H11) != 0) {
    currentNode = 11;
    changed = true;
    mode = 1;
  }
  else if (digitalRead(H12) != 0) {
    currentNode = 12;
    changed = true;
    mode = 1;
  }
  if (changed) {
    Serial.println(currentNode, DEC);
    warp = 0;
    resetLights();
  }
}

void resetLights() {
  solidColor(&strip0, strip0.Color(0, 0, 0));
  solidColor(&strip1, strip0.Color(0, 0, 0));
  solidColor(&strip2, strip0.Color(0, 0, 0));
  solidColor(&strip3, strip0.Color(0, 0, 0));
  solidColor(&strip4, strip0.Color(0, 0, 0));
  solidColor(&strip5, strip0.Color(0, 0, 0));
  solidColor(&strip6, strip0.Color(0, 0, 0));
  solidColor(&strip7, strip0.Color(0, 0, 0));
  solidColor(&strip8, strip0.Color(0, 0, 0));
  solidColor(&strip9, strip0.Color(0, 0, 0));
  solidColor(&strip10, strip0.Color(0, 0, 0));
  solidColor(&strip11, strip0.Color(0, 0, 0));
  strip0.show();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip7.show();
  strip8.show();
  strip9.show();
  strip10.show();
  strip11.show();
}

void lightAll() {
  solidColor(&strip0, strip0.Color(255, 255, 255));
  solidColor(&strip1, strip0.Color(255, 255, 255));
  solidColor(&strip2, strip0.Color(255, 255, 255));
  solidColor(&strip3, strip0.Color(255, 255, 255));
  solidColor(&strip4, strip0.Color(255, 255, 255));
  solidColor(&strip5, strip0.Color(255, 255, 255));
  solidColor(&strip6, strip0.Color(255, 255, 255));
  solidColor(&strip7, strip0.Color(255, 255, 255));
  solidColor(&strip8, strip0.Color(255, 255, 255));
  solidColor(&strip9, strip0.Color(255, 255, 255));
  solidColor(&strip10, strip0.Color(255, 255, 255));
  solidColor(&strip11, strip0.Color(255, 255, 255));

  strip0.show();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip7.show();
  strip8.show();
  strip9.show();
  strip10.show();
  strip11.show();
}

void updateButton() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      if (reading) {
        warp = !warp;
        resetLights();
      }
      buttonState = reading;
    }
  }
  lastButtonState = reading;
}


void startMode() {
  rgbFadeInAndOut(&strip0, &strip1, 255, 255, 255, 5, H0); // White
  state = digitalRead(H0);


  if (state != 0) {
    strip0.setPixelColor(0, 0, 0, 0);
    strip1.setPixelColor(0, 0, 0, 0);
    strip0.show();
    strip1.show();
    mode = 1;
    currentNode = 0;
    Serial.println(currentNode, DEC);
  }
}


void playMode() {
  drawSolid();
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 127) {
      reset();

    }
    else {
      mode = 2;
    }
  }
}


void reset() {
  resetLights();
  mode = 0;
  currentNode = 0;
}

void selectMode() {
  drawCycle();
  if (currentNode == 0) {
    state = digitalRead(H1);
    if (state != 0) {
      currentNode = 1;
      mode = 1;
    }
    else {
      state = digitalRead(H2);
      if (state != 0) {
        currentNode = 2;
        mode = 1;
      }
    }
  }
  else if (currentNode == 1) {
    state = digitalRead(H3);
    if (state != 0) {
      currentNode = 3;
      mode = 1;
    }
    else {
      state = digitalRead(H6);
      if (state != 0) {
        currentNode = 6;
        mode = 1;
      }
    }
  }
  else if (currentNode == 2) {
    state = digitalRead(H4);
    if (state != 0) {
      currentNode = 4;
      mode = 1;
    }
    else {
      state = digitalRead(H5);
      if (state != 0) {
        currentNode = 5;
        mode = 1;
      }
    }
  }
  else if (currentNode == 3) {
    state = digitalRead(H7);
    if (state != 0) {
      currentNode = 7;
      mode = 1;
    }
    else {
      state = digitalRead(H8);
      if (state != 0) {
        currentNode = 8;
        mode = 1;
      }
    }
  }
  else if (currentNode == 4) {
    state = digitalRead(H12);
    if (state != 0) {
      currentNode = 12;
      mode = 1;
    }
    else {
      state = digitalRead(H11);
      if (state != 0) {
        currentNode = 11;
        mode = 1;
      }
    }
  }
  else if (currentNode == 6) {
    state = digitalRead(H10);
    if (state != 0) {
      currentNode = 10;
      mode = 1;
    }
    else {
      state = digitalRead(H9);
      if (state != 0) {
        currentNode = 9;
        mode = 1;
      }
    }
  }

  if (mode == 1) {
    Serial.println(currentNode, DEC);
  }
}


void drawSolid() {
  if (currentNode == 1) {
    solidColor(&strip0, strip0.Color(255, 255, 255));
  }
  else if (currentNode == 2) {
    solidColor(&strip1, strip1.Color(255, 255, 255));
  }
  else if (currentNode == 3) {
    solidColor(&strip0, strip0.Color(255, 255, 255));
    solidColor(&strip5, strip5.Color(255, 255, 255));
  }
  else if (currentNode == 4) {
    solidColor(&strip1, strip0.Color(255, 255, 255));
    solidColor(&strip2, strip5.Color(255, 255, 255));
  }
  else if (currentNode == 5) {
    solidColor(&strip3, strip0.Color(255, 255, 255));
    solidColor(&strip1, strip5.Color(255, 255, 255));
  }
  else if (currentNode == 6) {
    solidColor(&strip0, strip0.Color(255, 255, 255));
    solidColor(&strip4, strip5.Color(255, 255, 255));
  }
  else if (currentNode == 7) {
    solidColor(&strip0, strip0.Color(255, 255, 255));
    solidColor(&strip5, strip5.Color(255, 255, 255));
    solidColor(&strip6, strip5.Color(255, 255, 255));
  }
  else if (currentNode == 8) {
    solidColor(&strip0, strip0.Color(255, 255, 255));
    solidColor(&strip5, strip5.Color(255, 255, 255));
    solidColor(&strip7, strip7.Color(255, 255, 255));
  }
  else if (currentNode == 9) {
    solidColor(&strip0, strip0.Color(255, 255, 255));
    solidColor(&strip4, strip5.Color(255, 255, 255));
    solidColor(&strip8, strip7.Color(255, 255, 255));
  }
  else if (currentNode == 10) {
    solidColor(&strip0, strip0.Color(255, 255, 255));
    solidColor(&strip4, strip5.Color(255, 255, 255));
    solidColor(&strip9, strip7.Color(255, 255, 255));
  }
  else if (currentNode == 11) {
    solidColor(&strip1, strip0.Color(255, 255, 255));
    solidColor(&strip2, strip5.Color(255, 255, 255));
    solidColor(&strip10, strip7.Color(255, 255, 255));
  }
  else if (currentNode == 12) {
    solidColor(&strip1, strip0.Color(255, 255, 255));
    solidColor(&strip2, strip5.Color(255, 255, 255));
    solidColor(&strip11, strip7.Color(255, 255, 255));
  }
}


void drawCycle() {
  drawSolid();
  if (currentNode == 0) {
    colorWipe(&strip0, &strip1, strip0.Color(255, 255, 255), 50);
  }
  else if (currentNode == 1) {
    colorWipe(&strip4, &strip5, strip0.Color(255, 255, 255), 50);
  }
  else if (currentNode == 2) {
    colorWipe(&strip2, &strip3, strip1.Color(255, 255, 255), 50);
  }
  else if (currentNode == 3) {
    colorWipe(&strip6, &strip7, strip1.Color(255, 255, 255), 50);
  }
  else if (currentNode == 4) {
    colorWipe(&strip10, &strip11, strip1.Color(255, 255, 255), 50);
  }
  else if (currentNode == 6) {
    colorWipe(&strip9, &strip8, strip1.Color(255, 255, 255), 50);
  }
}


// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel *lightStripLeft, Adafruit_NeoPixel *lightStripRight, uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < lightStripLeft->numPixels(); i++) {
    lightStripLeft->setPixelColor(i, c);
    lightStripRight->setPixelColor(i, c);
    lightStripLeft->show();
    lightStripRight->show();
    delay(wait);
  }
  delay(200);
  c = strip0.Color(0, 0, 0);
  for (uint16_t i = 0; i < lightStripLeft->numPixels(); i++) {
    if (Serial.available() > 0) {
      return;
    }
    lightStripLeft->setPixelColor(i, c);
    lightStripRight->setPixelColor(i, c);
    lightStripLeft->show();
    lightStripRight->show();
    delay(wait);
  }
}


// Fill the dots one after the other with a color
void solidColor(Adafruit_NeoPixel *lightStrip, uint32_t c) {
  for (uint16_t i = 0; i < lightStrip->numPixels(); i++) {
    lightStrip->setPixelColor(i, c);
    lightStrip->show();
  }
}

void rgbFadeInAndOut(Adafruit_NeoPixel *lightStripLeft, Adafruit_NeoPixel *lightStripRight, uint8_t red, uint8_t green, uint8_t blue, uint8_t wait, uint8_t sensorNumber) {

  for (int n = 0; n < 255; n++) {
    lightStripLeft->setPixelColor(0, (red * n) / 255, (green * n) / 255, (blue * n) / 255);
    lightStripRight->setPixelColor(0, (red * n) / 255, (green * n) / 255, (blue * n) / 255);
    lightStripLeft->show();
    lightStripRight->show();
    state = digitalRead(sensorNumber);
    if (state != 0) {
      n = 255;
    }
    else {
      delay(wait);
    }
  }

  if (state != 0) {
    return;
  }

  for (int n = 255; n > 0; n--) {
    lightStripLeft->setPixelColor(0, (red * n) / 255, (green * n) / 255, (blue * n) / 255);
    lightStripRight->setPixelColor(0, (red * n) / 255, (green * n) / 255, (blue * n) / 255);
    lightStripLeft->show();
    lightStripRight->show();
    state = digitalRead(sensorNumber);
    if (state != 0) {
      n = 0;
    }
    else {
      delay(wait);
    }
  }
  if (state != 0) {
    return;
  }
}


