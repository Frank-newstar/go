#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define COMPORT "/dev/ttyUSB0"

int yuyin(int **cmd,int fd){
	int buf;
	int num;
	*cmd=&buf;

		
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
