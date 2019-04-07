#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
RCSwitch mySwitch;
int main(int argc, char *argv[]) {
     int PIN = 4;
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }
     int pulseLength = 0;
     if (argv[1] != NULL) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
     if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);
     while(1) {
      if (mySwitch.available()) {
        int value = mySwitch.getReceivedValue();
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {
          printf("%i\n", mySwitch.getReceivedValue() );
        }
        fflush(stdout);
        mySwitch.resetAvailable();
      }
      usleep(100);
  }
  exit(0);
}
