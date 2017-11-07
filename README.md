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
7. Enable VNC by running `raspi-config` in a terminal and toggling VNC under the interfaces menu.
8. You are now ready to VNC into your Pi!

# Acquire credentials for an MQTT broker

# Run the Python test apps

# Set up your alarm devices