import paho.mqtt.client as mqtt
import sys

## Set up where the MQTT broker is
broker = "localhost"
port = 1883

## Set up the connection to the broker
conn = mqtt.Client("virtual_device")
conn.connect(broker, port)

## Publish some data
try:
    print("Publishing data: " + str(sys.argv[1]))
    conn.publish("security_feed", sys.argv[1])
    print("Sent!")
except:
    print("Something went wrong. Did you give data as a parameter?")