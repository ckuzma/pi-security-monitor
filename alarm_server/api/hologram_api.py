import json
import Hologram

## Change this later
CREDENTIALS = {
    'device_key': ''
}

class HologramAPI:
    def __init__(self):
        self.client = Hologram.HologramCloud.HologramCloud(
            CREDENTIALS['device_key'],
            network='cellular',
            authentication_type='csrpsk'
        )
    
    def send_sms(self, to_num, msg):
        response = self.client.sendSMS(
            to_num,
            msg
        )
        print(response)

"""
===========
-- Tests --
===========
"""
## Instantiate
api = HologramAPI()

## Send a message
number = None
message = 'Hello, this is a test!'
api.send_sms(number, message)