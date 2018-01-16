import json
import twilio.rest
import yaml

## Import the credentials
CREDENTIALS = None
with open('creds.yaml', 'r') as file:
    CREDENTIALS = yaml.load(file)

class TwilioAPI:
    def __init__(self):
        self.client = twilio.rest.Client(
            CREDENTIALS['twilio']['account'],
            CREDENTIALS['twilio']['token']
        )
        self.from_num = CREDENTIALS['twilio']['num']

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
# ## Instantiate
# api = TwilioAPI()

# ## Send a message
# number = 18002255288
# message = 'Hello, this is a test!'
# api.send_sms(number, message)