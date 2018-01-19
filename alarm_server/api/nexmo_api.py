import json
import nexmo

## Change this out later
CREDENTIALS = {
  'key': '',
  'secret': '',
  'num': 18002255288
}

class NexmoAPI:
    def __init__(self):
        self.client = nexmo.Client(
            key=CREDENTIALS['key'],
            secret=CREDENTIALS['secret']
        )
        self.from_num = CREDENTIALS['num']
    
    def send_sms(self, to_num, msg):
        try:
            response = self.client.send_message({
                'from': self.from_num,
                'to': to_num,
                'text': msg
            })
            if response['status'] == '0':
                print('Sent message: ' + response['message-id'])
                print('Remaining balance: ' + response['remaining-balance'])
            else:
                print('ERROR: ' + response['error-text'])
        except:
            print("FAIL: Unable to send SMS via Nexmo. (Credentials wrong?)")

"""
===========
-- Tests --
===========
"""
## Instantiate
# api = NexmoAPI()

## Send a message
# number = 18002255288
# message = 'Hello, this is a test!'
# api.send_sms(number, message)