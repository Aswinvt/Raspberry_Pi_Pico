from machine import Pin
import time

led = Pin(25, Pin.OUT)

while True:
    led(1)
    print("LED ON")
    time.sleep(1)
    led(0)
    print("LED OFF")
    time.sleep(1)