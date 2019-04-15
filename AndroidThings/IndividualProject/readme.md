Mircea Sorin-Sebastian
GR 935

On average, the typical person opens up their phone 150 times per day, and this number can easily increase to 300, this means once every 5 minutes.

Even though the total time we spend on the phone is important, we cannot focus for a long time because we cannot keep ourselves distanced from the phone, even with an interaction of seconds, for me at least it was enough to pull me out of focus.

To tackle this problem and also solve a school project, I have build an android app that counts the number of phone pickups and brights up an led each time you do this, there are 144 leds and when all of them ar light up, you know that you should stop.

# ARCHITECTURE
Using a Raspberry PI that runs android things and exposes an API through you can control the individual leds.

The  Raspberry PI talks through a serial port with the Arduino that actually controls the LEDS. At first, I have tried to achieve this directly using the Raspberry PI but I ran into problems.



The client android app just sends a request to the Raspberry PI to keep lighting up an LED.

# How to link the Wires
red pin = power, 3.3V pin
green pin =  data pin, on ARDUINO 6th digital pin
black pin = on the ground (GND)
