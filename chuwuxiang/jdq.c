#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void jdq(int x,int value){
	if(wiringPiSetup()==-1){
		    printf("wiringPiSetup failed\n");
		        return;
			    }
	pinMode(x,OUTPUT);
	digitalWrite(x,value);
}
