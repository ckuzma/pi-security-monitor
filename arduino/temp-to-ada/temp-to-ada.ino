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

// Constants for temp sensor
const int TEMPERATURE = A0;
const int B = 4275;
const int R0 = 100000;

// Create secure connection to the MQTT server
WiFiClientSecure client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Conect to feeds
Adafruit_MQTT_Publish security_feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/f/security_feed");

void setup() {
  Serial.begin(9600);
  delay(10);

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
}

void loop() {
  // Reconnect if we hit the timeout
  MQTT_connect();

  // Get the distance
  float temp = getTemp();

  // Publish to ADA
  publishMessage(temp);
  
  // Delay
  delay(5000); // 5 minutes, don't need temp that often
}

float getTemp() {
  int raw = analogRead(TEMPERATURE);
  float R = 1023.0/raw-1.0;
  R = R0*R;
  return 1.0/(log(R/R0)/B+1/298.15)-273.15; // celsius
}

void publishMessage(float tempValue) {
    Serial.println("Sending temp value...");
    if (! security_feed.publish(tempValue)) {
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
