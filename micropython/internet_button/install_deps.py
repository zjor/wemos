import upip
import time
import network

wifi_ssid = "Grgic1"
wifi_password = "brankagrgic"

def ensure_wifi(ssid, password):
	
	sta_if = network.WLAN(network.STA_IF)
	sta_if.active(True)
	if not sta_if.isconnected():
		sta_if.connect(ssid, password)
		for i in range(5):
			if not sta_if.isconnected():
				time.sleep_ms(1000)
				print("Connecting...")
	return sta_if.isconnected()

def install_deps():
	if ensure_wifi(wifi_ssid, wifi_password):
		upip.install("micropython-pkg_resources")
		upip.install("micropython-logging")
		upip.install("picoweb")		
	else:
		print("Not connected")