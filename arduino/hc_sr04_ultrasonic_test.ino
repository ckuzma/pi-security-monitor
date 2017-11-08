// Pins for Ultrasonic Range Sensor
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

// Set up limitation for sensor
const float MAX_DIST_CM = 400.0;
const float ALARM_DISTANCE_CHANGE = 1.0;

// Set up space to save previous value
float prev_measure_cm = 0.0;

void setup() {
  // Ultrasonic sensor trigger pin
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Start Serial debugging
  Serial.begin(9600);

  // Delay for sensor to be installed properly
  Serial.println("Waiting 5 seconds...");
  delay(5000);

  // Get initial reading
  Serial.println("Starting...");
  prev_measure_cm = getDistance();
}

void loop() {
  // Get the distance
  float measured_cm = getDistance();

  // Print the distance
  //printDistance(measured_cm);

  // Check if alarm-worthy
  alarmTest(measured_cm);
  
  // Set the new previous value
  prev_measure_cm = measured_cm;
  
  // 60 millis delay
  delay(60);
}

float getDistance() {
  long t1;
  long t2;

  // Hold the trigger pin high for 10 millis
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure the distance
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  return (t2 - t1) / 58.0;
}

void printDistance(float cm) {
  if (cm > MAX_DIST_CM) {
    Serial.println("Too far...");
  } else {
    Serial.print(cm);
    Serial.println(" cm");
  }
}

void alarmTest(float new_measure) {
  if (prev_measure_cm - new_measure > ALARM_DISTANCE_CHANGE || new_measure - prev_measure_cm > ALARM_DISTANCE_CHANGE) {
    Serial.println("ALARM!!!");
    delay(2000);
  }
}
