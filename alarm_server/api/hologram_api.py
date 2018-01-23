import json
from Hologram.HologramCloud import HologramCloud

class HologramAPI:
    def __init__(self):
        self.client = HologramCloud(
            dict(),
            network='cellular',
            authentication_type='csrpsk'
        )
    
    def send_sms(self, to_num, msg):
        try:
            response = self.client.sendSMS(
                to_num,
                msg
            )
            print(response)
        except:
            print("FAIL: Unable to send SMS via Hologram. (Modem disconnected?)")

"""
===========
-- Tests --
===========
"""
## Instantiate
# api = HologramAPI()

## Send a message
# number = 18002255288
# message = 'Hello, this is a test!'
# api.send_sms(number, message)