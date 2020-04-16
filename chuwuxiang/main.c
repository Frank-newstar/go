#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <string.h>
#include <softPwm.h>
#include "server.h"
#include "jdq.h"
#include "yuyin.h"
#include "chaoshengbo.h"
#include "duoji.h"
#include "dht11.h"

#define COMPORT "/dev/ttyUSB0"
#define door 1
#define light 0
#define fengshan 2

pthread_mutex_t mutex =PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int fd;
int *y_cmd;
int *s_cmd;

int *RH;
int *TMP;



void *the_listen(){

yuyin(&y_cmd,fd);

}

void *the_server(){
	pthread_mutex_lock(&mutex);
	server(&s_cmd);
	pthread_mutex_unlock(&mutex);
}

void *modular(){

	int cmd;
	FILE *f;
	int RH;
	int TMP;
	char buffer[200];
	int databuf;
	int dis;

	ultraInit(24,25);
	softPwmCreate(door,16,200);
	
while(1){
	if((*y_cmd==0x01||*s_cmd==1)&&(cmd!=1)){
		cmd=1;
		f=popen("python oled.py 开门","r");
		pclose(f);
		duoji(door,0);
		//开门	
	}else if((*y_cmd==0x02||*s_cmd==2)&&(cmd!=2)){
		cmd=2;
		f=popen("python oled.py 关门","r");
		pclose(f);
		duoji(door,1);
		//关门
	}else if((*y_cmd==0x03||*s_cmd==3)&&(cmd!=3)){
		cmd=3;
		f=popen("python oled.py 开灯","r");
		pclose(f);
		jdq(light,1);
		//开灯
	}else if((*y_cmd==0x04||*s_cmd==4)&&(cmd!=4)){
		cmd=4;
		f=popen("python oled.py 关门","r");
		pclose(f);
		jdq(light,0);
		//关灯
	}else if((*y_cmd==0x05||*s_cmd==5)&&(cmd!=5)){
		cmd=5;
		f=popen("python oled.py 开始除湿","r");
		pclose(f);
		jdq(fengshan,1);
		//开风扇
	}else if((*y_cmd==0x06||*s_cmd==6)&&(cmd!=6)){
		cmd=6;
		f=popen("python oled.py 停止除湿","r");
		pclose(f);
		jdq(fengshan,0);
		//关风扇
	}else if((*s_cmd==7)&&(cmd!=7)){
		cmd=7;
		f=popen("python oled.py 启动感应门","r");
		pclose(f);
		while(*y_cmd!=0x08&&*s_cmd!=8){
			dis=disMeasure(24,25);
			if(dis<10){
				duoji(door,0);
				delay(500);
				while(1){
					dis=disMeasure(24,25);
					if(dis>10){
					break;
					}
				}
				duoji(door,1);
			}
			
		}
		
		
	}
	*y_cmd=0;
	*s_cmd=0;

	databuf=dht11();
	RH=((databuf>>24)&0xff);
	TMP=((databuf>>8)&0xff);
	printf("%d,%d\n",RH,TMP);
	sprintf(buffer,"python oled.py %d%,%d℃",RH,TMP);
	f=popen(buffer,"r");
	pclose(f);
		

 }
}

int main(){
	
if(wiringPiSetup()==-1){
	printf("setup wiringPi failed !");
	return -1;
}
if((fd=serialOpen(COMPORT,115200))<0){
	printf("open serial fail\n");
	return -1;
}

pthread_t t1;
pthread_t t2;
pthread_t t3;


pthread_create(&t1,NULL,the_listen,NULL);
pthread_create(&t2,NULL,the_server,NULL);
pthread_create(&t3,NULL,modular,NULL);


pthread_join(t1,NULL);
pthread_join(t2,NULL);
pthread_join(t3,NULL);



return 0;
}
