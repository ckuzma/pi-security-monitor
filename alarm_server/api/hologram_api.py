import json
import Hologram

class HologramAPI:
    def __init__(self):
        self.client = Hologram.HologramCloud.HologramCloud(
            dict(),
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
number = 18002255288
message = 'Hello, this is a test!'
api.send_sms(number, message)