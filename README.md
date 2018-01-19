# pi-security-monitor
Raspberry Pi + Hologram Nova + NodeMCUs = Portable Security System

# Pi Headless Setup
1. Flash Pi with Raspbian Jessie. (Note: Stretch has proven very finicky to setup in a truly headless manner.)
2. Create an empty file named `ssh` (no extension) in the root of the `boot` partition.
3. Create a file called `wpa_supplicant.conf` and copy it to the root of the `boot` partition. Its contents should look like this, except with your own WiFi information:
```
network={
	ssid="YOUR_SSID_HERE"
	psk="YOUR_PASSWORD_HERE"
}
```
4. After the Pi has booted, figure out its IP address by looking at the list of devices connected to your WiFi access point.
5. SSH into your Pi: `ssh pi@xxx.xxx.xxx.xxx`
6. Change the default password as suggested at login. (Better yet, create a new account and password and delete the default (`pi`) user.)
7. Ensure that the VNC server is installed:
```
sudo apt-get update
sudo apt-get install realvnc-vnc-server
```
8. Enable VNC by running `raspi-config` in a terminal and toggling VNC under the interfaces menu.
9. You are now ready to VNC into your Pi!

# Install CLI for Hologram.io / Nova Modem
1. Follow the instructions found here to add the Hologram Command Line Interface for Linux devices: [Hologram Developer Tools](https://hologram.io/docs/guide/nova/developer-tools/)

# Install necessary Arduino libraries for NodeMCU & MQTT
1. Follow the instructions found here to add the ESP8266 / NodeMCU board libraries to the Arduino IDE: [ESP8266 on Arduino (GitHub)](https://github.com/esp8266/Arduino)
2. Install this [Adafruit](https://www.adafruit.com) library for MQTT on ESP8266: [Adafruit MQTT Library (GitHub)](https://github.com/adafruit/Adafruit_MQTT_Library)

# Acquire credentials for an MQTT broker
1. While any MQTT broker will work, for sheer simplicity of getting off of the ground we began with the [Adafruit IO IoT](https://io.adafruit.com) platform.

# Run the Python test apps

# Set up your alarm devices

# Acknowledgements
The Hologram team created a wealth of documentation including easy-to-read example tutorials. Perhaps the
[most helpful](https://www.hackster.io/hologram/raspberry-pi-cellular-gateway-1acd6a) of which was found
on the [Hackster](https://www.hackster.io) website itself, detailing exactly how to set up a Raspberry Pi
Zero W in headless mode as an AP while also running an MQTT broker for interacting with NodeMCU devices.