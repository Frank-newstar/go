#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "chaoshengbo.h"
#include "oled.h"
#include "duoji.h"
#include "voice.h"
#include "server.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


void *xiangzi() {
	FILE *f;
	int flag=0;
	ultraInit(24,25);//超声波引脚设置
	while(1){
	 if(disMeasure(24,24)<5){
		f=popen("python oled.py 请输入指纹","r");
	        fclose(f);	
		if(zhiwen(flag)==1){
			duoji(29,0);
			while(disMeasure(24,25)>5);
			delay(2000);
			duoji(29,90);
			flag=1;
		}//寄存
		else if(zhiwen(flag)==2){
		
			duoji(29,0);
			while(disMeasure(24,25)>5);
			delay(2000);
			duoji(29,90);
			flag=0;
		}//取件
	 }
	}
}
void *the_server() {

    
    server();
    
    return 0;
}

int main() {

    if (wiringPiSetup() ==-1) {
							// when initialize wiring failed,print messageto screen
        printf("setup wiringPi failed !");
        return -1;
    }


    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, xiangzi, NULL);
    pthread_create(&t2, NULL, the_server, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
