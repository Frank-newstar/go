#include<stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

void duoji(int pin,int value) {
    int i; 
    if(value==0){
	i=10;
	while(i--){
        	softPwmWrite(pin, 5+i); 
		delay(100);
	}
    }
    if(value==1){
    	i=10;
	while(i--){
		softPwmWrite(pin,16-i);
		delay(100);
	}
    }
}

