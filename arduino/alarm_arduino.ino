#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"

// Constants for buzzer
const int BUZZER = 6;

// Constants for LCD screen
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

// Constants for microphone
const int MICROPHONE = A2;

// Constants for light sensor
const int PHOTOCELL = A1;

// Constants for temp sensor
const int TEMPERATURE = A0;
const int B = 4275;
const int R0 = 100000;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
//  beep();
  float temp = getTemp();
  Serial.println(temp);
  int light = getLight();
  Serial.println(light);
  float noise = getNoise();
  Serial.println(noise);
  if (light < 600) {
    beep();
    displayText("Low light!");
  }
  else {
    displayText("");
  }
  delay(1000);
}

void beep() {
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
}

int getLight() {
  return analogRead(PHOTOCELL);
}

float getNoise() {
  float maxNoise = 0;
  float minNoise = 0;
  for(int i=0; i<15; i++) {
    float sample = _getNoiseSample();
    if(sample > maxNoise) {
      maxNoise = sample;
    }
    if(sample < minNoise) {
      minNoise = sample;
    }
  }
  return maxNoise - minNoise;
}

float _getNoiseSample() {
  float sum = 0;
  for(int i=0; i<32; i++) {
    sum += analogRead(MICROPHONE);
  }
//  sum >>= 5;
  sum = sum / 100;
  return sum;
}

float getTemp() {
  int raw = analogRead(TEMPERATURE);
  float R = 1023.0/raw-1.0;
  R = R0*R;
  return 1.0/(log(R/R0)/B+1/298.15)-273.15; // celsius
}

void displayText(String text) {
  lcd.clear();
  lcd.print(text);
}

