//
// pi-shutdown.c
// 


#include <wiringPi.h>

#include <stdio.h>

#define PIN 29       // pin 40, wiring pi 29

int main (int argc, char **argv)
{

	printf("Monitoring wiringPi pin %i for shutdown\n", PIN);

	wiringPiSetup();
	pinMode (PIN, INPUT);
	pullUpDnControl (PIN, PUD_UP);

	do {
		if(digitalRead(PIN) == 0) {
			printf("Shutting down...\n");
			system("shutdown -h now");
		}
		delay(1000);
	}
	while (1);
}
