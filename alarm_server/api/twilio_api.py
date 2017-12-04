import json
import twilio.rest

CREDENTIALS = {
  'account': '',
  'token': '',
  'num': 18002255288
}

class TwilioAPI:
    def __init__(self):
        self.client = twilio.rest.Client(
            CREDENTIALS['account'],
            CREDENTIALS['token']
        )
        self.from_num = CREDENTIALS['num']

    def send_sms(self, to_num, msg):
        response = self.client.messages.create(
            to=to_num,
            from_=self.from_num,
            body=msg
        )
        print(response)
        # print(json.dumps(response, indent=2))

"""
===========
-- Tests --
===========
"""
## Instantiate
api = TwilioAPI()

## Send a message
number = 18002255288
message = 'Hello, this is a test!'
api.send_sms(number, message)