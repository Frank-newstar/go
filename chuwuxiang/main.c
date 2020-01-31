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


void *chaoshengbo() {
	
   int fd;
   int sound;
   float dis1;
   
   ultraInit(24,25);

/*
        if((fd=serialOpen("/dev/ttyUSB0",115200))<0){
            printf("open serial fail\n");
            return NULL;
        }
*/
    while (1) {
	
   // pthread_mutex_lock(&mutex);
	sound=voice(fd);
	
	//if(sound==03){
	//	duoji(29,90);
	//	delay(3000);

	//	int flag=1;
	//	while(flag){
        		dis1 = disMeasure(24,25);
        		printf("distance = %0.2f cm\n", dis1);
        		if (dis1<10) {
        			duoji(29,90);// opendoor
       			}else{
				duoji(29,0);//closedoor
			}

	//		sound=voice(fd);
	//		if(sound==04){
	//			duoji(29,0);
	//			flag=0;
	//		}
	//	}

   // pthread_mutex_unlock(&mutex);
//      	 }
    }
}

void *oled() {
    init();
    qingping();
    while (1) 
    {
        shijian();
        wendu();
        ascii();
        delay(100);
    }
}

void *the_server() {

    
    pthread_mutex_lock(&mutex);
    server();
    pthread_mutex_unlock(&mutex);
    return 0;
}

int main() {

    if (wiringPiSetup() ==
        -1) {  // when initialize wiring failed,print messageto screen
        printf("setup wiringPi failed !");
        return -1;
    }


    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

//    pthread_create(&t1, NULL, chaoshengbo, NULL);
    pthread_create(&t2, NULL, oled, NULL);
    pthread_create(&t3, NULL, the_server, NULL);

  //  pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
