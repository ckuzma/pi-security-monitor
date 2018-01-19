import paho.mqtt.client as mqtt
import sys
import yaml

## Import the credentials
CREDENTIALS = None
with open('util_creds.yaml', 'r') as file:
    CREDENTIALS = yaml.load(file)

## Set up where the MQTT broker is
broker = CREDENTIALS['mqtt-server']['url']
port = CREDENTIALS['mqtt-server']['port']

## Set up the connection to the broker
conn = mqtt.Client(CREDENTIALS['mqtt-server']['user'])
conn.connect(broker, port)

## Publish some data
try:
    print("Publishing data: " + str(sys.argv[1]))
    conn.publish("security_feed", sys.argv[1])
    print("Sent!")
except:
    print("Something went wrong. Did you give data as a parameter?")