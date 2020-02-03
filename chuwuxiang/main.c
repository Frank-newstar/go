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
#include "duoji.h"
#include "zhiwen.h"
#include "server.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


void *xiangzi() {
	FILE *f;
	int flag=0;
	int i;
	int resualt;
	ultraInit(24,25);//超声波引脚设置
	while(1){
		printf("flag=%d\n",flag);
	 if(disMeasure(24,25)<5){
		f=popen("python oled.py 请输入指纹","r");
	        fclose(f);	
		//delay(1000);
		for(i=0;i<3;i++){
			delay(1000);
		 resualt=zhiwen(flag);
		 if(resualt==1){

			duoji(29,90);
			while(disMeasure(24,25)<5);
			delay(1000);
			duoji(29,0);
			f=popen("python oled.py 寄存成功","r");
			fclose(f);
			flag=1;
			break;
		 }
		 else if(resualt==0){
			 
			duoji(29,90);
			while(disMeasure(24,25)<5);
			delay(1000);
			duoji(29,0);
			f=popen("python oled.py 取件成功","r");
			fclose(f);
			flag=0;
			printf("%d\n",flag);
			break;
		 }
		}
		
		if(resualt==-1){
			f=popen("python oled.py 失败","r");
			fclose(f);
		}
		delay(1000);
		f=popen("python oled.py  ","r");
		fclose(f);
		
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
    //pthread_t t2;

    pthread_create(&t1, NULL, xiangzi, NULL);
    //pthread_create(&t2, NULL, the_server, NULL);

    pthread_join(t1, NULL);
    //pthread_join(t2, NULL);

    return 0;
}
