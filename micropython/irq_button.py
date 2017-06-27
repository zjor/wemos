from machine import enable_irq, Pin

d3 = Pin(0, Pin.IN)

def falling(p):
	print(p, "1 -> 0")

def rising(p):
	print(p, "0 -> 1")

d3.irq(handler=falling, trigger=Pin.IRQ_FALLING)
d3.irq(handler=rising, trigger=Pin.IRQ_RISING)

print("Interrupt handlers are set")

