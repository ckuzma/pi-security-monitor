import json
import paho.mqtt.client as mqtt
import yaml

## Import the credentials
CREDENTIALS = None
with open('util_creds.yaml', 'r') as file:
    CREDENTIALS = yaml.load(file)

class MQTTMonitor:
    def __init__(self):
        pass
    
    def run(self):
        ## Setup the MQTT client
        client = mqtt.Client()
        client.username_pw_set(CREDENTIALS['mqtt-server']['user'], CREDENTIALS['mqtt-server']['key'])
        client.on_connect = self._connected
        client.on_disconnect = self._disconnected
        client.on_message = self._new_event

        ## Connect to MQTT broker
        client.connect(CREDENTIALS['mqtt-server']['url'], port=CREDENTIALS['mqtt-server']['port'], keepalive=CREDENTIALS['mqtt-server']['keepalive'])

        ## Loop forever
        client.loop_forever()
    
    ## Below are the callbacks
    def _connected(self, client, userdata, flags, rc):
        print('Connected to MQTT broker!')
        client.subscribe(CREDENTIALS['mqtt-server']['feed'])
        print('Connected to feed!')
    
    def _disconnected(self, client, userdata, rc):
        print('Disconnected from MQTT broker!')
    
    def _new_event(self, client, userdata, msg):
        ## Decode and print the message
        msg = msg.payload.decode('utf-8')
        print('New event: ' + str(msg))


if __name__ == '__main__':
    monitor = MQTTMonitor()
    monitor.run()