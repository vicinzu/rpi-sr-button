# pi-shutdown
Shutdown Raspberry Pi if a defined pin is pulled down.
This can for example be used to shutdown a headless
Raspberry Pi (including Raspberry Pi zero) gracefully
(without risking to damage the file system on the sd card).

The background program, which monitors the pin, is automatically started
during bootup of the system. It is written in C and very small to minimize the
overhead. It polls the pin once per second.

To install:

You must have admin rights, such as "pi" in Raspbian!

- Download the repository to your pi-top:

```
  cd Downloads
  git clone git://github.com/rricharz/pi-shutdown
  sudo apt-get install wiringpi
  cd pi-shutdown
  chmod +x install
  sudo ./install
```

- Reboot your pi

The default pin is pin 40 of the gpio connector. This makes it easy to
connect pin 40 to pin 39 (ground) to force a shutdown. If the two pins
are connected, for example with a push button, "sudo shutdown -h now" is
executed.

You can change the pin number in "pi-shutdown.c", line 17, constant PIN. 
But be aware that wiringPi pin numbers need to be defined there, see
http://wiringpi.com/pins or type:
```
  gpio readall
```

Afterwards, recompile the program and install it again
```
  make
  sudo ./install
```
