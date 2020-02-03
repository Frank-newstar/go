#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define COMPORT "/dev/ttyUSB0"


//录入图像
int PS_GetImage(int fd){

	int cmd[12]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x01,0x00,0x05};
	int *pcmd=cmd;
	int i;
	unsigned int str[12]={'\0'};
	unsigned int *pstr=str;

	printf("录入图像\n");
	for(i=0;i<12;i++){	
		write(fd,pcmd,1);
		pcmd++;
	}
	
	for(i=0;i<12;i++){
		read(fd,pstr,1);
		pstr++;
	}

	for(i=0;i<12;i++){
		printf("%02X",str[i]);
	}
	printf("\n");
	return str[9];
}

//生成特征
int PS_GenChar(int fd){

	int cmd[13]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x04,0x02,0x01,0x00,0x08};
	int *pcmd=cmd;
	int i;
	unsigned int str[12]={'\0'};
	unsigned int *pstr=str;

	printf("生成特征\n");
	for(i=0;i<13;i++){
		write(fd,pcmd,1);
		pcmd++;
	}
	for(i=0;i<12;i++){
		read(fd,pstr,1);
		pstr++;
	}
	
	return str[9];
}


//存储模板
int PS_StoreChar(int fd){

	int cmd[15]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x06,0x06,0x01,0x00,0x00,0x00,0x0E};
	int *pcmd=cmd;
	int i;
	unsigned int str[12]={'\0'};
	unsigned int *pstr=str;

	printf("存储模板\n");
	for(i=0;i<15;i++){
		write(fd,pcmd,1);
		
		pcmd++;
	}
	for(i=0;i<12;i++){
		read(fd,pstr,1);
		pstr++;
	}
	
	return str[9];
}

//搜索指纹
int PS_Search(int fd){

	int cmd[17]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x01,0x2B,0x00,0x3A};
	int *pcmd=cmd;
	int i;
	unsigned int str[16]={'\0'};
	unsigned int *pstr=str;
	
	printf("搜索指纹\n");

	for(i=0;i<17;i++){
		write(fd,pcmd,1);
		pcmd++;
	}
	for(i=0;i<16;i++){
		read(fd,pstr,1);
		pstr++;
	}
	
	return str[9];
}


//清空指纹库
int PS_Empty(int fd){

	int cmd[12]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x0d,0x00,0x11};
	int *pcmd=cmd;
	int i;
	unsigned int str[12]={'\0'};
	unsigned int *pstr=str;

	printf("清空指纹库\n");
	for(i=0;i<12;i++){
		write(fd,pcmd,1);
		pcmd++;
	}
	for(i=0;i<12;i++){
		read(fd,pstr,1);
		pstr++;
	}
	return str[9];
}

int zhiwen(int flag){
	int fd;
	int buf;
	
	if(wiringPiSetup()<0){
		printf("init sys fail\n");
		return -1;
	}
	if((fd=serialOpen(COMPORT,115200))<0){
		printf("open serial fail\n");
		return -1;
	}
	if(PS_GetImage(fd)==0x00){
	 if(PS_GenChar(fd)==0x00){
	  if(PS_Search(fd)==0x00){
	   printf("open\n");
	   while(PS_Empty(fd)!=0x00);
	  }else if(flag==0){
	   if(PS_StoreChar(fd)==0x00){
	    printf("用户注册成功，开箱\n");
	   }else printf("存储模板失败\n");
	  }else printf("已有存放\n"); 
	 }else printf("生成特征失败\n");
   	}else printf("录入图像失败\n");

	return 0;
}	
