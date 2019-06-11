#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <chrono>
#include <iostream>
 
// Use GPIO Pin 17, which is Pin 0 for wiringPi library
 
#define BUTTON_PIN 2
#define MIN_DURATION_SHUTDOWN 6000
#define MIN_DURATION_REBOOT 2000
#define REFRESH_TIME 2000
#define MAX_TIME std::chrono::time_point<std::chrono::system_clock>::max()
 
// the event counter 
volatile std::chrono::time_point startTime = MAX_TIME;
volatile double elapsed = 0.0;
 
// -------------------------------------------------------------------------
 
void buttonInterrupt(void) {
	if(startTime == MAX_TIME) {
		startTime = std::chrono::high_resolution_clock::now();
	} else {
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()- startTime).count();
		startTime = MAX_TIME;
	}
}
 
// -------------------------------------------------------------------------
 
int main(void) {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }
  pinMode (BUTTON_PIN, INPUT);
  pullUpDnControl (BUTTON_PIN, PUD_UP);

  if ( wiringPiISR (BUTTON_PIN, INT_EDGE_BOTH, &buttonInterrupt) < 0 ) {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }

  do {
	  delay(REFRESH_TIME);
 	if(elapsed>0) {
		if(elapsed>MIN_DURATION_SHUTDOWN) {
			printf("Shutdown!\n");
			system("shutdown -h now");
		} else if (elapsed>MIN_DURATION_REBOOT) {
			printf("Reboot!\n");
			system("shutdown -r now");
		}

		elapsed=0.0;
	}
} while(1);

  return 0;
}
