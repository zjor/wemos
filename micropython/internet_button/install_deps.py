import upip
import time
import network

wifi_ssid = "UPC92A2B1A"
wifi_password = "X6ved8fseteu"

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
		print("Installing packages")
		upip.install("micropython-pkg_resources")
		upip.install("micropython-logging")
		upip.install("picoweb")		
	else:
		print("Not connected")

if __name__ == "__main__":
	install_deps()		