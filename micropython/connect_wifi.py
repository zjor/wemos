import network
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
print(sta_if.scan())                             # Scan for available access points
ssid = 'UPC92A2B1A'
password = 'X6ved8fseteu'
sta_if.connect(ssid, password) # Connect to an AP
print('Connected: {!r}'.format(sta_if.isconnected()))