rpi-sr-button: rpi-sr-button.cpp
	g++ -std="c++1z" rpi-sr-button.cpp -lwiringPi -lwiringPi -lcrypt -lpthread -lm -lrt -o rpi-sr-button

