#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define COMPORT "/dev/ttyUSB0"

int yuyin(int **cmd){
	int fd;
	int buf;
	*cmd=&buf;
	if(wiringPiSetup()<0){
		printf("init sys fail\n");
		return -1;
	}
	if((fd=serialOpen(COMPORT,115200))<0){
		printf("open serial fail\n");
		return -1;
	}
	while(1)
	{
		if(serialDataAvail(fd)>0){
			buf=serialGetchar(fd);
			printf("%02x\n",buf);
		}
	}
	serialClose(fd);
	return 0;

}
