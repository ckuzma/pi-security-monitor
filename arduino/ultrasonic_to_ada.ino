#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Credentials
#define WLAN_SSID       ""
#define WLAN_PASS       ""
#define AIO_USERNAME    ""
#define AIO_KEY         ""
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  8883

// Pins for Ultrasonic Range Sensor
const int TRIG_PIN = D1;
const int ECHO_PIN = D2;

// Set up limitation for sensor
const float MAX_DIST_CM = 400.0;
const float ALARM_DISTANCE_CHANGE = 2.0;

// Set up space to save previous value
float prev_measure_cm = 0.0;

// Create secure connection to the MQTT server
WiFiClientSecure client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Conect to feeds
Adafruit_MQTT_Publish security_feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/f/security_feed");

void setup() {
  Serial.begin(9600);
  delay(10);

  // Ultrasonic sensor trigger pin
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Get initial reading
  Serial.println("Starting...");
  prev_measure_cm = getDistance();
}

void loop() {
  // Reconnect if we hit the timeout
  MQTT_connect();

  // Get the distance
  float measured_cm = getDistance();
  
  // Print the distance
  //printDistance(measured_cm);

  // Check if alarm-worthy
  if (alarmTest(measured_cm)) {
    publishMessage();
    delay(2000);
    prev_measure_cm = getDistance();
  }
  else {
    // Set the new previous value
    prev_measure_cm = measured_cm;
  }
  
  // Delay
  delay(60);
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
    if (new_measure != MAX_DIST_CM) {
        if (prev_measure_cm - new_measure > ALARM_DISTANCE_CHANGE || new_measure - prev_measure_cm > ALARM_DISTANCE_CHANGE) {
            Serial.println("ALARM!!!");
            return true;
        }
    }
    return false;
}

void publishMessage() {
    Serial.println("Sending alarm announcement...");
    if (! security_feed.publish("nodemcu_ultrasonic,alarm,triggered")) {
        Serial.println(F("Failed"));
    } else {
        Serial.println(F("OK!"));
    }
}


void MQTT_connect() {
  // Place to store retry attempt count
  int8_t ret;

  // Check if connected
  if (mqtt.connected()) {
    return;
  }

  // Connect w/3 retries
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}