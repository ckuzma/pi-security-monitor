import json
import paho.mqtt.client as mqtt
import yaml

## SMS broker selection (needs to match in init below):
# from api.twilio_api import TwilioAPI
# from api.nexmo_api import NexmoAPI # Incompatible with RPi
from api.hologram_api import HologramAPI

## Import the credentials
CREDENTIALS = None
with open('creds.yaml', 'r') as file:
    CREDENTIALS = yaml.load(file)

class SecurityService:
    def __init__(self):
        self.armed = False
        # self.phone = TwilioAPI()
        # self.phone = NexmoAPI()
        self.phone = HologramAPI()
    
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
        print('System Armed: ' + str(self.armed))
    
    def _disconnected(self, client, userdata, rc):
        print('Disconnected from MQTT broker!')
    
    def _new_event(self, client, userdata, msg):
        ## Decode and print the message
        msg = msg.payload.decode('utf-8')
        print('New event: ' + str(msg))

        ## If statements to arm/disarm alarm
        if msg == '_enable_alarm_':
            self.armed = True
        elif msg == '_disable_alarm_':
            self.armed = False
        ## Do something if armed
        elif self.armed == True:
            print('Sending SMS alert!')
            self.phone.send_sms(CREDENTIALS['owner']['num'], msg)

        ## Print armed status to console
        print('System Armed: ' + str(self.armed))


if __name__ == '__main__':
    sec = SecurityService()
    sec.run()