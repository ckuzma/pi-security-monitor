// Microphone settings
const int micPin = 0;
const int sampleWindow = 50; // 50 milliseconds = 20Hz
const int alarmThreshold = 210;
 
void setup() {
   Serial.begin(9600);
}
 
void loop() {
   int noiseValue = getVolume();
   if(noiseValue >= alarmThreshold) {
    Serial.print("ALARM!");
   }
   Serial.println(noiseValue);
}

float getVolume() {
  // Set static sound bite stuff
  int noiseMax = 0;
  int noiseMin = 1024;

  // Take the sample
  long startTime = millis();
  while(millis() - startTime < sampleWindow) {
    int sample = analogRead(micPin);
    if(sample < 1024) {
      if(sample > noiseMax) {
        noiseMax = sample;
      }
      else if(sample < noiseMin) {
        noiseMin = sample;
      }
    }
  }

  // Calculate the amplitude
  int amp = noiseMax - noiseMin;
  return amp;
}
