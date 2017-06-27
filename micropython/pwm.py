import time

from machine import Pin, PWM

def fade_out(pwm):
	for i in range(0, 1024):
		pwm.duty(i)
		time.sleep_ms(5)

def fade_in(pwm):
	for i in range(0, 1024):
		pwm.duty(1024 - i)
		time.sleep_ms(5)

pwm = PWM(Pin(2))

print ("Blinking with PWM")

for i in range(0, 5):
	fade_in(pwm)
	time.sleep(1)
	fade_out(pwm)		

print("Done")