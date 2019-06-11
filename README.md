# rpi-sr-button
---
The 'RaspberryPi Shutdown&Reboot Button' alias rpi-sr-button is a fork of pi-shutdown. You can configure the program to monitor a predefined pin that will serve as a button.

This can for example be used to shutdown (press more than 6 seconds) or reboot (press less than 6, but more than 2 seconds) a headless Raspberry Pi (including Raspberry Pi zero) gracefully
(without risking to damage the file system on the sd card).

The background program, which monitors the pin, is automatically started during bootup of the system. It is written in C++ and very small to minimize the overhead. It checks if the button has been pressed once every 2 seconds.

To install:
You must have admin rights, such as "pi" in Raspbian!

The program also works with arm64 architecture. At this moment it only works by using a modified version of wiringPi (eg. [wiringPi-arm64](https://github.com/Vicinzu/wiringPi-arm64)).

## Download the repository to your Pi

```
  cd Downloads
  git clone https://github.com/Vicinzu/rpi-sr-button.git
  sudo apt-get install wiringpi
  cd rpi-sr-button
  make
  chmod +x install
  sudo ./install
```

## Reboot your pi

The default pin is pin 13 of the gpio connector. This makes it easy to connect pin 13 to pin 14 (ground) to force a shutdown or reboot. If the two pins are connected and depending on the duration of the pressure, either "sudo shutdown -h now" or "sudo shutdown -r now" is executed.

## Customize the background program
You can change the pin number in "rpi-sr-button.cpp", line 11, constant PIN. But be aware that wiringPi pin numbers need to be defined there, see
http://wiringpi.com/pins or type:
```
  gpio readall
```

If you are using the desktop on a rpi 2, 3 or zero, you can install the following gpio display, which will also give you the current actual logic state of each pin as well as the gpio and wiringPi pin numbers:
https://github.com/rricharz/pi-gpio-display

You can also change the minimum press time by changing the constants MIN_DURATION_SHUTDOWN and MIN_DURATION_REBOOT. Be aware that MIN_DURATION_SHUTDOWN has always be greater than MIN_DURATION_REBOOT.

Afterwards, recompile the program and install it again
```
  make
  sudo ./install
```
