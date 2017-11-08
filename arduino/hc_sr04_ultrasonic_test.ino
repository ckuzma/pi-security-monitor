// Pins for Ultrasonic Range Sensor
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;

// Set up limitation for sensor
const float MAX_DIST_CM = 400.0;
const float ALARM_DISTANCE_CHANGE = 2.0;

// Set up memory buffer for sensor average values
const int distance_count = 6;
long recent_distances[distance_count];
int distance_selector = 0;
int alarm_worthiness = 0;

void setup() {
  // Ultrasonic sensor trigger pin
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Start Serial debugging
  Serial.begin(9600);

  // Get initial reading
  Serial.println("Starting...");
  
  // Fill the distance memory buffer with initial values
  for (int x=0; x < distance_count; x++) {
    recent_distances[x] = getDistance();
  }
}

void loop() {
  // Get the distance
  float measured_cm = getDistance();

  // Print the distance
  printDistance(measured_cm);

  // Check if alarm-worthy
  alarmTest(measured_cm);

  // 150 millis delay
  delay(150);
}
float getDistance() {
    long t1;
    long t2;
    float distance;

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
    distance = (t2 - t1) / 58.0;
    if (distance < MAX_DIST_CM) {
        return distance;
    }
    return MAX_DIST_CM;
}
  
void printDistance(float cm) {
    Serial.print(cm);
    Serial.println(" cm");
}

bool alarmTest(float new_measure) {
  float average_distance = 0.0;
  for (int x=0; x < distance_count; x++) {
    average_distance += recent_distances[x];
  }
  average_distance = average_distance / distance_count;
  
  if (average_distance - new_measure > ALARM_DISTANCE_CHANGE || new_measure - average_distance > ALARM_DISTANCE_CHANGE) {
    alarm_worthiness += 1;
  }

  // Add new distance value, update selector
  recent_distances[distance_selector] = new_measure;
  if (distance_selector == distance_count) {
    distance_selector = 0; 
  }

  // Check if we had enough alarm things go off
  if (alarm_worthiness == 2) {
    alarm_worthiness = 0;
    Serial.println("ALARM!");
    delay(2000);
    // Refill the buffer
    for (int x=0; x < distance_count; x++) {
      recent_distances[x] = getDistance();
    }
    return true;
  }
  else {
    return false;
  }

}
