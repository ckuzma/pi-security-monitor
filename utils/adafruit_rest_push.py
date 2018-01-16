import sys
import yaml

## Import the AdafruitIO REST library
from Adafruit_IO import Client

## Import the credentials
CREDENTIALS = None
with open('../alarm_server/creds.yaml', 'r') as file:
    CREDENTIALS = yaml.load(file)

## Connect to Adafruit IO RESTful service
aio = Client(CREDENTIALS['mqtt-server']['key'])

## Get data from the runtime arguments and send it
data = sys.argv[1]
aio.send('security_feed', data)

